#define BOOTROM 0x1fff0000
#define BOOTROM_SIZE 8192
// ROM In-Application Programming routine
// +1 to signify this is Thumb code
#define BOOTROM_IAP (BOOTROM + BOOTROM_SIZE - 16 + 1)
#define BOOTROM_DEVICE_DRIVER_TABLE (BOOTROM + BOOTROM_SIZE - 8)

// cmd and result can point to same area of memory (UM10601 p.269)
typedef void (*IAPFuncPtr)(uint32_t *cmd, uint32_t *result);

#define DEVICE_DRIVER_FUNC_TABLE(device_no) ((*(uint32_t**)BOOTROM_DEVICE_DRIVER_TABLE)[device_no])

struct LPC800_PWRD {
    void (*set_pll)(unsigned int cmd[4], unsigned int resp[2]);
    void (*set_power)(unsigned int cmd[4], unsigned int resp[2]);
};

struct LPC800_DeviceDrivers {
    void *res0;
    void *res1;
    void *res2;
    struct LPC800_PWRD *PWRD;
    void *res4;
    struct LPC800_I2CD *I2CD;
    void *res6;
    void *res7;
    void *res8;
    struct LPC800_USARTD *USARTD;
};

#define DeviceDrivers (*(struct LPC800_DeviceDrivers**)BOOTROM_DEVICE_DRIVER_TABLE)

// Example usage:
//DeviceDrivers->PWRD->set_power();
