#include <signal.hpp>

using namespace PTL;

typedef board::uart uart;

typedef ParBus<board::D5, board::D4, board::D3, board::D2> hd44780_data;
typedef Signal<board::D6> hd44780_en_sig;
typedef Signal<board::D7> hd44780_regsel_sig;

typedef board::D3 pcd8544_sclk;
typedef board::D4 pcd8544_sdin;
typedef board::D5 pcd8544_dc;
typedef board::D6 pcd8544_reset;
typedef board::D7 pcd8544_sce;
