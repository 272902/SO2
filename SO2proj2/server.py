import threading
import socket

localhost = '127.0.0.1'
port = 12345

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((localhost,port))
server.listen()

clients = []

def broadcast(message):
    for client in clients:
        client.send(message)

def handle(client):
    while True:
        try:
            message = client.recv(1024) #
            broadcast(message)
        except:
            index = clients.index(client)
            clients.remove(client)
            broadcast(f'A user left the chat.'.encode('ascii'))
            client.close()
            break

def recieve():
    while True:
        client, address = server.accept()
        print(f"Connected with {str(address)}")

        clients.append(client)
        client.send(str(clients.index(client)).encode('ascii'))
        broadcast(f'User {clients.index(client)} joined the chat. '.encode('ascii'))
        client.send('Connected to the server'.encode('ascii'))

        thread = threading.Thread(target=handle,args=(client,))
        thread.start()


print("Server started")
recieve()