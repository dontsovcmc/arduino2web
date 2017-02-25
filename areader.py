__author__ = 'dontsov'

from serial import Serial
from logger import log

class AReader():

    def __init__(self, port, baudrate=9600, timeout=1):
        self.port = Serial(port=port, baudrate=baudrate, timeout=timeout)
        self.title = port

    def __enter__(self):
        self.port.isOpen()
        log.info("port %s open" % self.title)
        return self

    def read_line(self, endl='\n'):
        out = ch = ''
        while ch != endl:
            ch = self.port.read(1)
            if ch and ch != endl:
                out += ch
                log.debug("port received: %s" % str(hex(ord(ch))))
        return out

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.port.close()
        log.info("port %s closed" % self.title)