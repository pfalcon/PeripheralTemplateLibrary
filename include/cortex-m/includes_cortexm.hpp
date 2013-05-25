// TODO: make target MCU dependent
#ifdef LIBPERIPHA
//#include <arm/cortex-m/systick.h>
    #if defined(CORTEX_M0)
    #include <arm/cortex-m/arm-cmsis/Device/ARM/ARMCM0/Include/ARMCM0.h>
    #elif defined(CORTEX_M0PLUS)
    #include <arm/cortex-m/arm-cmsis/Device/ARM/ARMCM0plus/Include/ARMCM0plus.h>
    #elif defined(CORTEX_M3)
    #include <arm/cortex-m/arm-cmsis/Device/ARM/ARMCM3/Include/ARMCM3.h>
    #elif defined(CORTEX_M4)
    #include <arm/cortex-m/arm-cmsis/Device/ARM/ARMCM4/Include/ARMCM4.h>
    #else
    #error Unknown Cortex-M Core
    #endif
#else
// Assume that complete vendor CMSIS is used
//#error Undefined
#endif
