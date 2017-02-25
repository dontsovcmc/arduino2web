__author__ = 'dontsov'

import time
import requests
import argparse

from signal import signal, SIGINT, SIGTERM, SIGABRT

from client import ArduinoClient
from areader import AReader
from logger import log, Logger

class CoffeeClient(ArduinoClient):

    def __init__(self, url):
        super(CoffeeClient, self).__init__(self.loop)
        self.url = url
        self.update = False
        self.data = ''

    def loop(self):
        if self.update:
            self.update = False
            log.debug('try send data')
            r = requests.get(self.url, params={'data': self.data})
            log.info('send data to server ok')
            log.debug(r.text)
        time.sleep(0.3)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Arduino to web data converter')
    parser.add_argument('-u', '--url', default='http://127.0.0.1:45000/data', help='URL to send data')
    parser.add_argument('-p', '--port', default='/dev/tty.usbmodem1411', help='arduino port')
    parser.add_argument('-b', '--baud', type=int, default=9600, help='arduino port speed')
    parser.add_argument('-l', '--log', default='INFO', help='logging level: INFO, DEBUG, etc')
    args = parser.parse_args()

    log.info('arguments: %s', str(args))

    Logger(args.log)

    with CoffeeClient(args.url) as client:

        def signal_handler(signum, frame):
            client.stop()

        for sig in [SIGINT, SIGTERM, SIGABRT]:
            signal(sig, signal_handler)

        while client.working:
            try:
                with AReader(args.port, args.baud) as ser:
                    try:
                        while client.working:
                            client.data = ser.read_line()
                            log.info("read: %s" % client.data)
                            client.update = True

                    except Exception, err:
                        log.error(str(err))

            except Exception, err:
                log.error(str(err))
            time.sleep(2)