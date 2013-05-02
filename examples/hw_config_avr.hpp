typedef board::uart uart;

typedef ParBus<board::D5, board::D4, board::D3, board::D2> hd44780_data;
typedef Signal<board::D6> hd44780_en_sig;
typedef Signal<board::D7> hd44780_regsel_sig;
