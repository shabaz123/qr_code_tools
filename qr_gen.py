#!/usr/bin/python3

# #########################################################
# QR code generator, creates a C array!
# rev 1 - shabaz - oct 2023
# requires 'pip install qrcode' and 'pip install pypng'
# usage: python qr_gen.py https://my.url/or/text
# #########################################################

import sys
import qrcode
import png
import array

if len(sys.argv) > 1:
	qr_data = sys.argv[1]
else:
	qr_data = 'https://bbc.co.uk/news/'

qr = qrcode.QRCode(version=None,
	error_correction=qrcode.constants.ERROR_CORRECT_L,
	box_size=1,
	border=4,
)

qr.add_data(qr_data)
qr.make(fit=True)

img = qr.make_image(fill_color="black", back_color="white")

type(img)

img.save('temp.png')

reader = png.Reader(filename='temp.png')
w, h, pixels, metadata = reader.read_flat()
pixel_byte_width = 4 if metadata['alpha'] else 3


# pixels is an array of 0 and 1 values
# mash up each set of 8 into a single byte
# Note: we only want w values per line

w_fullbytes = w//8  # number of fully usable bytes per line
w_fullbits = w_fullbytes*8  # number of bits which are within fully used bytes
w_pad = w % 8  # remainder number of bits per line, which will need padding with zeros

numbytes = w_fullbytes
if w_pad > 0:
	numbytes = w_fullbytes + 1
numbytes = numbytes * h

print("")
print("")
print("/************************************************************")
print(" ******************** QR Code data  *************************")
print(" ******* Machine-generated, using qr_gen.py. Data is: *******")
print(f"{qr_data}")
print(" ************************************************************/")
print(f"const uint8_t qr_bits_width = {w};")
print(f"const uint8_t qr_bits_height = {h};")
print(f"const uint8_t qr_code[{numbytes}]", end="")
print(" = {")
bit_idx = 0
last_bit_idx = len(pixels)
for i in range(0, h):
	colnum = 0
	for j in range(0, w_fullbits, 8):
		# read 8 pixels
		b = 0
		for k in range(0,8):
			b = b << 1
			b = b | pixels[bit_idx]
			bit_idx = bit_idx + 1
		if colnum == 0:
			print ("    0x%02x," % b, end='')
		else:
			print ("0x%02x" % b, end='')
			if bit_idx < last_bit_idx:
				print(",", end='')
			else:
				print("")
				print("};")
		colnum = colnum + 1
	# read the padding bits
	if w_pad > 0:
		b = 0
		for k in range(0,w_pad):
			b = b << 1
			b = b | pixels[bit_idx]
			bit_idx = bit_idx + 1
		for k in range(0,8-w_pad):
			b = b << 1
		print ("0x%02x" % b, end='')
		if bit_idx < last_bit_idx:
			print(",", end='')
		else:
			print("")
			print("};")
	print ("")
print("/************* end of machine-generated section *************/")
print("")
print("")










