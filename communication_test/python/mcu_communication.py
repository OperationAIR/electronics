
import serial
import threading
import time
import signal

BAUDRATE = 115200
TTY = '/dev/cu.usbmodemC1DDCDF83'

class SerialConnection:

    def __init__(self):

        self.serial = None
        self.alive = False
        self._reader_alive = False
        self.receiver_thread = None

        self.connect()

    def connect(self):
        self.serial = serial.Serial(TTY, BAUDRATE, timeout=10)
        print('open port: ', self.serial, self.serial.port)
        self._start_reader()

    def disconnect(self):
        self._stop_reader()

    def _start_reader(self):
        """Start reader thread"""
        print('Start reader thread')
        self._reader_alive = True
        # start serial->console thread
        self.receiver_thread = threading.Thread(target=self.reader, name='rx')
        self.receiver_thread.daemon = True
        self.receiver_thread.start()

    def _stop_reader(self):
        """Stop reader thread only, wait for clean exit of thread"""
        self._reader_alive = False
        if self.serial and hasattr(self.serial, 'cancel_read'):
            self.serial.cancel_read()

        if self.receiver_thread:
            self.receiver_thread.join()

    def send_buffer(self, buffer: bytes):
        if self.serial:
            self.serial.write(buffer)


    def reader(self):
        """loop and copy serial->console"""
        try:
            while self._reader_alive:
                data = self.serial.readline()
                if data:
                    print('got {} bytes back'.format(len(data)), type(data))
                    try:
                        if chr(data[-1]) == '\n':
                            text = ''.join([chr(c) for c in data])
                            print(text)
                        else:
                            print("Got bytes: ", data)
                    except e:
                        print('parse error:', e)
                        pass

        except serial.SerialException:
            self.alive = False
            # self.console.cancel()
            raise       # XXX handle instead of re-raise?




if __name__ == "__main__":
    import serial
    import threading
    from settings import Settings

    conn = SerialConnection()

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
    message = s.get_bit_string()
    print('sending settings: ', len(message), message)
    # print('in ascii: ', binascii.hexlify(message))
    conn.send_buffer(message)

    exit = False

    def exitFunc(_signal=None, _=None):
        global exit
        conn.disconnect()
        exit = True
        print('bye')

    signal.signal(signal.SIGINT, exitFunc)


    while not exit:
        time.sleep(0.1)
    # TTY = '/dev/cu.SLAB_USBtoUART'


    # with serial.Serial(TTY, 115200, timeout=1) as ser:
    #     ser.write(message)
    #     thread = threading.Thread(target=read_from_port, args=(ser,))
    #     thread.start()

    # print('done, bye')

    # time.sleep(10)
    # thread.join()



