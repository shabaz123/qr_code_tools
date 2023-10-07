

/****************************************************************************************************
 * qr_display_function.c
 * rev 1 - oct 2023 - shabaz
 * This file contains a single function that can be dropped into any
 * microcontroller code, for displaying a QR code on an LCD screen.
 * The function is qr_display(), and it takes the following three parameters:
 * - qr_data: pointer to the QR code data
 * - qr_bits_width: number of bits wide the QR code is
 * - qr_bits_height: number of bits high the QR code is
 * The three items above are from machine-generated output from the gen_qr.py code.
 * The function assumes that the LCD screen is already initialized and
 * ready to receive data.
 * The function will paint the QR code on the LCD screen, centered.
 * The function will paint the QR code in black, on a white background.
 * The user needs to supply the following definitions:
 * - LCD_WIDTH: width of the LCD screen in pixels
 * - LCD_HEIGHT: height of the LCD screen in pixels
 * The following macros or functions are also required:
 * - LCD_CLEAR(white): macro or function to clear the LCD screen to white color
 * - LCD_RECT(x1, y1, x2, y2, BLACK): macro or function to paint a rectangle on the LCD screen,
 *  with the top-left corner at (x1, y1) and the bottom-right corner at (x2, y2), in black color
 * - LCD_SEND_BUF(): Optional. This is the placeholder for if your LCD uses a function to
 * refresh the display. 
****************************************************************************************************/


void qr_display(uint8_t *qr_data, uint8_t qr_bits_width, uint8_t qr_bits_height) {
    uint16_t x, y; // for iterating through the QR code data
    int b; // bit index within a byte of the QR code data
    int byte_index = 0; // byte index through the entire QR code data
    uint8_t byte_chunk; // one byte of the QR code data
    uint8_t xbit_index; // bit index within a whole line of the QR code
    int square_len; // number of horiz or vert pixels that each bit will be painted as
    uint16_t startx; // left border width for the QR code
    uint16_t starty;  // top border height for the QR code

    // determine the length of the square size that each bit will be painted as
    if (LCD_WIDTH <= LCD_HEIGHT) {
        square_len = LCD_WIDTH / qr_bits_width;
    } else {
        square_len = LCD_HEIGHT / qr_bits_height;
    }

    // determine the border width and height so that the QR code is centered
    startx = (LCD_WIDTH - (square_len * qr_bits_width)) / 2;
    starty = (LCD_HEIGHT - (square_len * qr_bits_height)) / 2;

    // set the background of the entire LCD screen to be white
    LCD_CLEAR(WHITE);

    // paint the QR code
    for (y=0; y<qr_bits_height; y++) {
        xbit_index = 0;
        for (x=0; x<qr_bits_width; x = x+8) { // traverse the QR code data 8 bits at a time
            byte_chunk = qr_data[byte_index];
            for (b=0; b<8; b++) { // inspect each bit in the byte
                if (byte_chunk & 0x80) {
                    // white square on a white background, don't need to do anything!
                }
                else {
                    // paint a black square!
                    // parameters in this example are: x1, y1, x2, y2, color
                    LCD_RECT(startx+(square_len*(x+b)), starty+(square_len*y), 
                            startx+(square_len*(x+b+1)), starty+(square_len*(y+1)), 
                            BLACK);
                }
                byte_chunk <<= 1;
                xbit_index++;
                if (xbit_index >= qr_bits_width) {
                    break;
                }
            } // end of 8 bits loop
            byte_index++;
        } // end of x loop
    } // end of y loop

    // send RAM buffer to LCD
    LCD_SEND_BUF();
}

