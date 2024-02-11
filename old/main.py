import socket
import curses.ascii
import struct
import time
from dnspackets import DNSPacketHeader, DNSQuestion, DNSResourceRecord, DNSAnswer, DNSPacket

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
		print('Waiting message')
		data, cli_addr = sock.recvfrom(M_SIZE)
		print(f"Received message from {cli_addr} : at {time.time()}")

		print("\nBinary\n")
		print(data)
		print()
		
		dnspacket = DNSPacket.fromBytes(data)
		print("Header\n")
		print(dnspacket.header)
		print()

		print("Question\n")
		for question in dnspacket.question:
			print(question)
		print()

		response = DNSPacket(dnspacket.header)
		response.header.setQR(1)

		# ④Clientへ受信完了messageを送信
		# header = 
		# sock.sendto('Success to receive message'.encode(encoding='utf-8'), cli_addr)

	except KeyboardInterrupt:
		print ('\n . . .\n')
		sock.close()
		break