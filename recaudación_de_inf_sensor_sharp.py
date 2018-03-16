import serial

ser = serial.Serial(
	port='/dev/ttyUSB0',
	baudrate=115200,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)
dat_num = 0
data = 0
data_file = open("data_sharp.csv", 'w')
cont = 0
while cont < 500 :
	dat_num = 0
	dat_num = ser.inWaiting()
	if dat_num > 0:
		data = ser.read(dat_num)
		ser.flushInput()
		data_file.write(data)
		cont = cont + 1
		print "% Completado = ", cont*100/500
data_file.close()
print "Terminado!\n"
	
