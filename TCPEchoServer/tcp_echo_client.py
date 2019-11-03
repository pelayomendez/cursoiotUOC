import socket
import sys

# Creamos un socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectamos el socket al servidor que está escuchando:
server_address = ('localhost', 10000)
print('conectando al servidor:',  server_address)
sock.connect(server_address)

try:
    
    # Enviamo un mensaje de prueba:
    message = b'Ecooooo.  Repite este mensaje.'
    print('Enviando: ', message)
    sock.sendall(message)

    # Esperamos la respuesta:
    amount_received = 0
    amount_expected = len(message)
    
    while amount_received < amount_expected:
        data = sock.recv(1024)
        amount_received += len(data)
        print('Recibido: ', data)

finally:
    print('Cerrando el socket del cliente.')
    sock.close()
