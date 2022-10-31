from socketserver import ThreadingTCPServer, StreamRequestHandler
from time import sleep

from threading import Event


class MyServer(ThreadingTCPServer):
    def __init__(self, server_address, request_handler_class):
        super().__init__(server_address, request_handler_class)
        self.var = None

class MyHandler(StreamRequestHandler):
    def handle(self) -> None:
        message = self.request.recv(1024).decode()
        if (message == "ping"):
            response = "pong"
        elif (message == "GET"):
            while self.server.var == None:
                sleep(3)
            response = self.server.var
        elif (message.startswith("PUT ")):
            self.server.var = message[4:]
            response = "OK"
        else:
            response = "BAD RESPONSE"
        self.request.sendall(bytearray(response.encode()))

if __name__ == "__main__":
    with MyServer(("0.0.0.0", 5678), MyHandler) as my_server:
        try:
            my_server.serve_forever()
        finally:
            my_server.server_close()
