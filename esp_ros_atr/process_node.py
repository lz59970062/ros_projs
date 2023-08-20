import socket
import sys
import time
import threading
import struct


class Node():
    def __init__(self, name, ip, port, f):
        self.name = name
        self.neighbors = {}
        self.lock = threading.Lock()
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST,1)#(SOL_SOCKET, SO_BROADCAST, 1)
        self.sock.bind((ip, port))
        self.sock.settimeout(1)
        self.sock.setblocking(0)
        self.broadcast_ip = '<broadcast>'
        
        self.process_function = f
        self.port = port
        self.ip = ip
        self.broadcast_thread = threading.Thread(
            target=self.broadcast, args=())
        self.receive_thread = threading.Thread(target=self.receive, args=())
        self.broadcast_thread.daemon = True
        self.receive_thread.daemon = True
        self.broadcast_thread.start()
        self.receive_thread.start()

    def broadcast(self):
        # find the neighbors and send the message to them
        
        msg = "Node:" + self.name + "," + str(self.ip)+"," + str(self.port)
        try:
            self.lock.acquire()
            self.sock.sendto(msg.encode(), (self.broadcast_ip, self.port))
            self.lock.release()
        except socket.error as e:
            print(f"Error occured while sending data: {e}")
        
        time.sleep(2)

    def receive(self):
        try:
            while True:
                data, addr = self.sock.recvfrom(1024)
                self.process_function(data, addr)
                time.sleep(0.001)
        except socket.error:
            pass


def process_fun(data, addr):
    # print(data,addr
    #data = struct.unpack('fffffffff', data)
    print(data, addr)


def get_ip():

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(('8.8.8.8', 80))
    print(s.getsockname()[0])
    str = s.getsockname()[0]
    s.close()
    return str


if __name__ == '__main__':
    node = Node('process_node', get_ip(),28288, process_fun)
    while True:
        time.sleep(1)
