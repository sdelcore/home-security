import subprocess
from SimpleWebSocketServer import SimpleWebSocketServer, WebSocket

acceptableIP = ['192.168.0.20', '192.168.0.21']

def shell(command):
    try:
        output = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT)
    except Exception, e:
        output = str(e.output)
    finished = output.split('\n')
    for line in finished:
        print line
    return

class HomeSecurityServer(WebSocket):
    armed = False;

    def handleMessage(self):
        print(self.data + " " + str(HomeSecurityServer.armed))
        if(self.data == "STATUS"):
            if HomeSecurityServer.armed:
                self.sendMessage("1")
            elif not HomeSecurityServer.armed:
                self.sendMessage("0")
        elif(self.data == "1"):
            HomeSecurityServer.armed = True
            shell('killall motion')
            shell('motion -b')
            self.sendMessage("1")
        elif(self.data == "0"):
            HomeSecurityServer.armed = False
            shell('killall motion')
            self.sendMessage("0")

    def handleConnected(self):
        print(self.address, 'connected')
        if self.address[0] not in acceptableIP:
            print('Rejected')
            self.close()

    def handleClose(self):
        print(self.address, 'closed')
        

shell('killall motion')
server = SimpleWebSocketServer('', 8081, HomeSecurityServer)
server.serveforever()
