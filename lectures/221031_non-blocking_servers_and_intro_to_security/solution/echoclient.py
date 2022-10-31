import socket

while (1):

    print("Enter command: ", end='')
    command = input()
    if command in ["exit", "quit", "q"]:
        print("Exiting...")
        exit()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect(("0.0.0.0", 5678))

        request = bytearray(command.encode())
        client_socket.sendall(request)

        response = client_socket.recv(1024)
        print(response)

