import struct
import binascii

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

    def get_bit_string(self):
        #B = unsigned char
        #H = unsigned short
        start_flag = 0x41424344 #= AABB in ascii
        end_flag = 0xAF
        values = (0x0123, start_flag, self.peep, self.freq, self.tidal_vol, self.pressure, self.max_pressure,self.min_pressure,self.max_tv,self.min_tv, self.max_fio2, self.min_fio2, end_flag)
        s = struct.Struct('H I H H H H H H H H H H B')
        # values = (start_flag, self.peep, self.freq, self.tidal_vol, self.pressure, self.max_pressure,self.min_pressure,self.max_tv,self.min_tv, self.max_fio2, self.min_fio2, end_flag)
        # s = struct.Struct('I H H H H H H H H H H B')
        packed_data = s.pack(*values)
        return packed_data
    #return binascii.hexlify(packed_data)

if __name__ == "__main__":
    import serial
    N = 100

    s = Settings(0x4343, 0x4444, 0x4545, 0x4646, 0x4747, 0x4848, 0x4949, 0x5050, 0x5151, 0x5252)
    message =  s.get_bit_string()[:N]
    print('sending settings: ', len(message), message)
    print('in ascii: ', binascii.hexlify(message))

    TTY = '/dev/cu.SLAB_USBtoUART'

    with serial.Serial(TTY, 9600, timeout=1) as ser:
        ser.write(message)

    print('done, bye')



