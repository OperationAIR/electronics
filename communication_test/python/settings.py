import struct
import binascii
import crcmod

class Settings():
    def __init__(self, peep, freq, tidal_vol, pressure, max_pressure, min_pressure, max_tv, min_tv, max_fio2, min_fio2):
        self.peep = int(peep)
        self.freq = int(freq)
        self.tidal_vol = int(tidal_vol)
        self.pressure = int(pressure)
        self.max_pressure = int(max_pressure)
        self.min_pressure = int(min_pressure)
        self.max_tv = int(max_tv)
        self.min_tv = int(min_tv)
        self.max_fio2 = int(max_fio2)
        self.min_fio2 = int(min_fio2)
        self.crc = crcmod.predefined.mkPredefinedCrcFun('crc-16-usb')

    def get_bit_string(self):
        #B = unsigned char
        #H = unsigned short
        start_flag = 0x41424344 #= ABCD in ascii
        #values = (0x5A59, start_flag, self.peep, self.freq, self.tidal_vol, self.pressure, self.max_pressure, self.min_pressure, self.max_tv, self.min_tv, self.max_fio2, self.min_fio2, 0x1111, end_flag)
        #s = struct.Struct('=H I H H H H H H H H H H H B')
        values = (start_flag, self.peep, self.freq, self.tidal_vol, self.pressure, self.max_pressure,self.min_pressure,self.max_tv,self.min_tv, self.max_fio2, self.min_fio2)
        s = struct.Struct('=I H H H H H H H H H H')
        packed_data = s.pack(*values)
        checksum = self.crc(packed_data)

        print('crc:', checksum, checksum.to_bytes(2, byteorder='little'))
        bitstring = packed_data + checksum.to_bytes(2, byteorder='little')
        return bitstring
    #return binascii.hexlify(packed_data)

def handle_data(data):
    print(data)

def read_from_port(ser):
    while not connected:
        #serin = ser.read()
        connected = True

        while True:
           print("test")
           reading = ser.readline().decode()
           handle_data(reading)

if __name__ == "__main__":
    import serial
    import threading
    N = 100
    s = Settings(
        peep=20,
        freq=20,
        tidal_vol=120,
        pressure=20,
        max_pressure=45,
        min_pressure=5,
        max_tv=400,
        min_tv=200,
        max_fio2=50,
        min_fio2=20)
    message =  s.get_bit_string()[:N]
    print('sending settings: ', len(message), message)
    print('in ascii: ', binascii.hexlify(message))

    TTY = '/dev/cu.SLAB_USBtoUART'

    with serial.Serial(TTY, 115200, timeout=1) as ser:
        ser.write(message)
        thread = threading.Thread(target=read_from_port, args=(ser,))
        thread.start()

    print('done, bye')

    time.sleep(10)
    thread.join()



