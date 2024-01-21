import socket
import curses.ascii
import struct
import time
import copy

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
	def __init__(self, packetId:int = 0, queryResponse:bool = False, opcode:int = 0, authoritativeAnswer:bool = False, truncation:bool = False, recursionDesired:bool = False, recursionAvailable:bool = False, reserved:bool = False, authenticData:bool = False, checkingDisabled:bool = False, responseCode:int = 0, questionCount:int = 0, answerCount:int = 0, authorityCount:int = 0, additionalCount:int = 0):
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
	
	def __str__(self) -> str:
		return f'packetId: {self.packetId}, queryResponse: {self.queryResponse}, opcode: {self.opcode}, authoritativeAnswer: {self.authoritativeAnswer}, truncation: {self.truncation}, recursionDesired: {self.recursionDesired}, recursionAvailable: {self.recursionAvailable}, reserved: {self.reserved}, authenticData: {self.authenticData}, checkingDisabled: {self.checkingDisabled}, responseCode: {self.responseCode}, questionCount: {self.questionCount}, answerCount: {self.answerCount}, authorityCount: {self.authorityCount}, additionalCount: {self.additionalCount}'
	
	def toBytes(self) -> bytes:
		flag = 0
		flag |= (self.queryResponse << 15)
		flag |= (self.opcode << 11)
		flag |= (self.authoritativeAnswer << 10)
		flag |= (self.truncation << 9)
		flag |= (self.recursionDesired << 8)
		flag |= (self.recursionAvailable << 7)
		flag |= (self.reserved << 6)
		flag |= (self.authenticData << 5)
		flag |= (self.checkingDisabled << 4)
		flag |= self.responseCode

		return struct.pack('!HHHHHH', self.packetId, flag, self.questionCount, self.answerCount, self.authorityCount, self.additionalCount)

	@staticmethod
	def fromBytes(data:bytes):
		header = DNSPacketHeader()

		header.packetId, flag, header.questionCount, header.answerCount, header.authorityCount, header.additionalCount = struct.unpack('!HHHHHH', data)
		header.queryResponse = (flag & 0b1000000000000000) >> 15 == 1
		header.opcode = (flag & 0b0111100000000000) >> 11
		header.authoritativeAnswer = (flag & 0b0000010000000000) >> 10 == 1
		header.truncation = (flag & 0b0000001000000000) >> 9 == 1
		header.recursionDesired = (flag & 0b0000000100000000) >> 8 == 1
		header.recursionAvailable = (flag & 0b0000000010000000) >> 7 == 1
		header.reserved = (flag & 0b0000000001000000) >> 6 == 1
		header.authenticData = (flag & 0b0000000000100000) >> 5 == 1
		header.checkingDisabled = (flag & 0b0000000000010000) >> 4 == 1
		header.responseCode = (flag & 0b0000000000001111)

		return header

class DNSQuestion:
	def __init__(self, name:str = "", type:int = 0, class_:int = 0):
		self.name = name
		self.type = type
		self.class_ = class_
	
	def __str__(self) -> str:
		return f'name: {self.name}, type: {self.type}, class: {self.class_}'
	
	def toBytes(self) -> bytes:
		return self.name.encode(encoding='utf-8') + struct.pack('!HH', self.type, self.class_)
	
	@staticmethod
	def fromBytes(data:bytes):
		name = data[:data.find(b'\x00')]
		type, class_ = struct.unpack('!HH', data[len(name) + 1:])

		return DNSQuestion(name, type, class_)
	
class DNSResourceRecord:
	def __init__(self, name:str = "", type:int = 0, class_:int = 0, ttl:int = 0, length:int = 0, ip:bytes = b'\x00\x00\x00\x00'):
		self.name = name
		self.type = type
		self.class_ = class_
		self.ttl = ttl
		self.length = length
		self.ip = ip
	
	def __str__(self) -> str:
		return f'name: {self.name}, type: {self.type}, class: {self.class_}, ttl: {self.ttl}, length: {self.length}, ip: {self.ip}'
	
	def toBytes(self) -> bytes:
		return self.name.encode(encoding='utf-8') + struct.pack('!HHIH', self.type, self.class_, self.ttl, self.length) + self.ip
	
	@staticmethod
	def fromBytes(data:bytes):
		name = data[:data.find(b'\x00')]
		type, class_, ttl, length = struct.unpack('!HHIH', data[len(name) + 1:])
		ip = data[len(name) + 1 + 10:len(name) + 1 + 10 + length]

		return DNSResourceRecord(name, type, class_, ttl, length, ip)

class DNSAnswer(DNSResourceRecord):
	def __init__(self, name:str = "", type:int = 0, class_:int = 0, ttl:int = 0, length:int = 0, ip:bytes = b'\x00\x00\x00\x00'):
		super().__init__(name, type, class_, ttl, length, ip)
	
	@staticmethod
	def fromResourceRecord(resourceRecord:DNSResourceRecord):
		return DNSAnswer(resourceRecord.name, resourceRecord.type, resourceRecord.class_, resourceRecord.ttl, resourceRecord.length, resourceRecord.ip)
	
class DNSAuthority(DNSResourceRecord):
	def __init__(self, name:str = "", type:int = 0, class_:int = 0, ttl:int = 0, length:int = 0, ip:bytes = b'\x00\x00\x00\x00'):
		super().__init__(name, type, class_, ttl, length, ip)
	
	@staticmethod
	def fromResourceRecord(resourceRecord:DNSResourceRecord):
		return DNSAuthority(resourceRecord.name, resourceRecord.type, resourceRecord.class_, resourceRecord.ttl, resourceRecord.length, resourceRecord.ip)
	
class DNSAdditional(DNSResourceRecord):
	def __init__(self, name:str = "", type:int = 0, class_:int = 0, ttl:int = 0, length:int = 0, ip:bytes = b'\x00\x00\x00\x00'):
		super().__init__(name, type, class_, ttl, length, ip)
	
	@staticmethod
	def fromResourceRecord(resourceRecord:DNSResourceRecord):
		return DNSAdditional(resourceRecord.name, resourceRecord.type, resourceRecord.class_, resourceRecord.ttl, resourceRecord.length, resourceRecord.ip)		

class DNSPacket:
	def __init__(self, header:DNSPacketHeader = None, question:DNSQuestion = None, answer:DNSAnswer = None, authority:DNSAuthority = None, additional:DNSAdditional = None):
		self.header = header
		self.question = question
		self.answer = answer
		self.authority = authority
		self.additional = additional
	
	def AnserNameCompression(self) -> None:
		if not self.question:
			return
		if not self.answer:
			return
		
		qName = self.question.name
		aName = self.answer.name
		if qName != aName:
			return
		
		offset = len(self.question.name)
		# 2 bytes
		# 0b11000000 00000000 & offset
		self.answer.name = struct.pack('!H', 0b1100000000000000 & offset) + self.answer.name[offset + 1:]

	@staticmethod
	def fromBytes(data:bytes):
		header = DNSPacketHeader.fromBytes(data[:12])
		question = DNSQuestion.fromBytes(data[12:])

		return DNSPacket(header, question)

while True:
	try :
		print('Waiting message')
		data, cli_addr = sock.recvfrom(M_SIZE)
		print(f"Received message from {cli_addr} : at {time.time()}")

		print("\nBinary\n")
		print(data)
		print()

		cnsPacket = DNSPacket.fromBytes(data)

		# Header

		print("\nHeader\n")
		header = cnsPacket.header
		print(str(header).replace(', ', '\n'))
		print()

		# Question
		print("\nQuestion\n")
		question = cnsPacket.question
		print(str(question).replace(', ', '\n'))
		print()

		print("\nQuestion Name\n")
		print(question.name[1:])
		print(question.name[1:].replace(str(curses.ascii.EOT), '.').encode(encoding='utf-8'))
		host = socket.gethostbyname(question.name[1:].replace(b'\x03', '.').encode(encoding='utf-8'))

		# Response
		dnsResponsePacket = DNSPacket()
		dnsResponsePacket.header = copy.deepcopy(header)
		dnsResponsePacket.header.queryResponse = True
		dnsResponsePacket.header.recursionAvailable = True
		dnsResponsePacket.header.authenticData = True
		dnsResponsePacket.header.answerCount = 1

		dnsResponsePacket.question = copy.deepcopy(question)

		dnsResponsePacket.answer = DNSAnswer()
		dnsResponsePacket.answer.name = question.name
		dnsResponsePacket.answer.type = 1
		dnsResponsePacket.answer.class_ = 1
		dnsResponsePacket.answer.ttl = 255
		dnsResponsePacket.answer.length = 4
		dnsResponsePacket.answer.ip = socket.inet_aton(host)
		dnsResponsePacket.AnserNameCompression()

		print("\nResponse\n")
		print(dnsResponsePacket)
		



		# ④Clientへ受信完了messageを送信
		# header = 
		# sock.sendto('Success to receive message'.encode(encoding='utf-8'), cli_addr)

	except KeyboardInterrupt:
		print ('\n . . .\n')
		sock.close()
		break