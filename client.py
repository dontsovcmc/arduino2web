__author__ = 'dontsov'

from logger import log
from threading import Thread

class ArduinoClient(object):

    def __init__(self, func):
        self.working = False
        self.func = func

    def start(self):
        self.thread = Thread(target=self.run)
        self.thread.setDaemon(True)
        self.working = True
        self.thread.start()
        log.info("client started")

    def run(self):
        while self.working:
            try:
                self.func()
            except Exception, err:
                log.error(str(err))

    def stop(self):
        if not self.thread:
            return

        self.working = False
        self.thread.join(5.0)
        log.info("client stopped")

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()

