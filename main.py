import socket
import curses.ascii
import struct

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

class DNSPacketHeader:
	def __init__(self, packetId:int, queryResponse:bool, opcode:int, authoritativeAnswer, truncation, recursionDesired, recursionAvailable, reserved, authenticData, checkingDisabled, responseCode, questionCount, answerCount, authorityCount, additionalCount):
		self.packetId = packetId
		self.queryResponse = queryResponse
		self.opcode = opcode
		self.authoritativeAnswer = authoritativeAnswer
		self.truncation = truncation
		self.recursionDesired = recursionDesired
		self.recursionAvailable = recursionAvailable
		self.reserved = reserved
		self.authenticData = authenticData
		self.checkingDisabled = checkingDisabled
		self.responseCode = responseCode
		self.questionCount = questionCount
		self.answerCount = answerCount
		self.authorityCount = authorityCount
		self.additionalCount = additionalCount

# class DNSPacket:
# 	def __init__(self, header, question, answer, authority, additional):
# 		self.header = header
# 		self.question = question
# 		self.answer = answer
# 		self.authority = authority
# 		self.additional = additional

while True:
	try :
		# ③Clientからのmessageの受付開始
		print('Waiting message')
		da
		ta, cli_addr = sock.recvfrom(M_SIZE)

		# Header

		# # 16 bit
		# packetId = struct.unpack('!H', data[:2])[0]
		
		# # 1 bit request:0 response:1
		# queryResponse = struct.unpack('!B', data[2:3])[0] >> 7
		
		# # 4 bit opcode
		# opcode = struct.unpack('!B', data[2:3])[0] & 0b01111000

		# # 1 bit authoritative answer
		# authoritativeAnswer = struct.unpack('!B', data[2:3])[0] & 0b00000100

		# # 1 bit truncation
		# truncation = struct.unpack('!B', data[2:3])[0] & 0b00000010

		# # 1 bit recursion desired
		# recursionDesired = struct.unpack('!B', data[2:3])[0] & 0b00000001

		# # 1 bit recursion available
		# recursionAvailable = struct.unpack('!B', data[3:4])[0] >> 7

		# # 3 bit reserved
		# reserved = struct.unpack('!B', data[3:4])[0] & 0b01110000

		# # 1 bit authentic data
		# authenticData = struct.unpack('!B', data[3:4])[0] & 0b00001000

		# # 1 bit checking disabled
		# checkingDisabled = struct.unpack('!B', data[3:4])[0] & 0b00000100

		# # 4 bit response code
		# responseCode = struct.unpack('!B', data[3:4])[0] & 0b00000011

		# # 16 bit question count
		# questionCount = struct.unpack('!H', data[4:6])[0]

		# # 16 bit answer count
		# answerCount = struct.unpack('!H', data[6:8])[0]

		# # 16 bit authority count
		# authorityCount = struct.unpack('!H', data[8:10])[0]

		# # 16 bit additional count
		# additionalCount = struct.unpack('!H', data[10:12])[0]


		# Question



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
		# header = 
		# sock.sendto('Success to receive message'.encode(encoding='utf-8'), cli_addr)

	except KeyboardInterrupt:
		print ('\n . . .\n')
		sock.close()
		break