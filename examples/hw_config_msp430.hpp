//typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
typedef UART<1 MHZ, 9600, USCI> uart;
