import struct
import curses

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

	def isNameCompression(self) -> bool:
		# name to bytes
		namebytes = self.name.encode(encoding='utf-8')
		return namebytes[0] & 0b11000000 == 0b11000000

	def unCompressionName(self) -> str:
		if not self.isNameCompression():
			return self.name
		
		offset = (self.name[0] & 0b00111111) << 8 | self.name[1]
		return self.name[2:] + self.name[:offset].decode(encoding='utf-8').replace(chr(curses.ascii.ETX), '.')

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
	def __init__(self, header:DNSPacketHeader = None):
		self.header = header
		self.question:list[DNSQuestion] = []
		self.answer:list[DNSAnswer] = []
		self.authority:list[DNSAuthority] = []
		self.additional:list[DNSAdditional] = []
	
	@staticmethod
	def fromBytes(data:bytes):
		header = DNSPacketHeader.fromBytes(data[:12])
		question = []
		answer = []
		authority = []
		additional = []
		
		for i in range(header.questionCount):
			questionbytes = DNSQuestion.fromBytes(data[12 + i * 4:])
			question.append(questionbytes)
		
		for i in range(header.answerCount):
			answerbytes = DNSAnswer.fromBytes(data[12 + header.questionCount * 4 + i * 16:])
			answer.append(answerbytes)

		for i in range(header.authorityCount):
			authoritybytes = DNSAuthority.fromBytes(data[12 + header.questionCount * 4 + header.answerCount * 16 + i * 16:])
			authority.append(authoritybytes)

		for i in range(header.additionalCount):
			additionalbytes = DNSAdditional.fromBytes(data[12 + header.questionCount * 4 + header.answerCount * 16 + header.authorityCount * 16 + i * 16:])
			additional.append(additionalbytes)

		packet = DNSPacket(header)
		packet.question = question
		packet.answer = answer
		packet.authority = authority
		packet.additional = additional

		return packet
	
	def toBytes(self) -> bytes:
		data = self.header.toBytes()

		for question in self.question:
			data += question.toBytes()

		for answer in self.answer:
			data += answer.toBytes()

		for authority in self.authority:
			data += authority.toBytes()

		for additional in self.additional:
			data += additional.toBytes()

		return data
	
	def addQuestion(self, question:DNSQuestion):
		self.question.append(question)
		self.header.questionCount += 1

	def addAnswer(self, answer:DNSAnswer):
		self.answer.append(answer)
		self.header.answerCount += 1

	def addAuthority(self, authority:DNSAuthority):
		self.authority.append(authority)
		self.header.authorityCount += 1

	def addAdditional(self, additional:DNSAdditional):
		self.additional.append(additional)
		self.header.additionalCount += 1

	def __str__(self) -> str:
		return f'header: {self.header}, question: {self.question}, answer: {self.answer}, authority: {self.authority}, additional: {self.additional}'
