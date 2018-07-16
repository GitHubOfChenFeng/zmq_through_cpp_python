import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
port = "8888"
socket.connect ("tcp://10.0.180.158:8888")# % port)

while True:
    # client_message = input("client: ")
    socket.send_string("yhello")
    message = socket.recv()
    print("server:", message.decode("utf-8"))
