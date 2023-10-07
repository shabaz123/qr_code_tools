QR Code Tools

## qr_gen.py
This single file of Python code can be used to create a QR code as a C array of data.

Pre-requisites:

    pip install qrcode
    pip install pypng

Usage:

    python qr_gen.py https://my.web/url/

Example output:

~~~
/************************************************************
 ******************** QR Code data  *************************
 ******* Machine-generated, using qr_gen.py. Data is: *******
https://bbc.co.uk/news/
 ************************************************************/
const uint8_t qr_bits_width = 33;
const uint8_t qr_bits_height = 33;
const uint8_t qr_code[165] = {
    0xff,0xff,0xff,0xff,0x80,
    0xff,0xff,0xff,0xff,0x80,
    0xff,0xff,0xff,0xff,0x80,
...truncated...
    0xff,0xff,0xff,0xff,0x80,
    0xff,0xff,0xff,0xff,0x80
};

/************* end of machine-generated section *************/
~~~
