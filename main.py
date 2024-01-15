import socket
import curses.ascii

M_SIZE = 1024

# 
host = '127.0.0.1'
port = 53

locaddr = (host, port)

# ①ソケットを作成する
sock = socket.socket(socket.AF_INET, type=socket.SOCK_DGRAM)
print('create socket')

# ②自ホストで使用するIPアドレスとポート番号を指定
sock.bind(locaddr)

while True:
	try :
		# ③Clientからのmessageの受付開始
		print('Waiting message')
		data, cli_addr = sock.recvfrom(M_SIZE)
		print(f'Received message')
		print("length: ", len(data))
		print("Heders: ", data[:12])
		question = data[12:]
		type = question[-4:-2]
		class_ = question[-2:]
		name = question[:-4]
		print("Name: ", name.decode(encoding='utf-8').replace(chr(curses.ascii.ETX), '.'))
		print("Type: ", type)
		print("Class: ", class_)
		print()

		# ④Clientへ受信完了messageを送信
		header = 
		sock.sendto('Success to receive message'.encode(encoding='utf-8'), cli_addr)

	except KeyboardInterrupt:
		print ('\n . . .\n')
		sock.close()
		break