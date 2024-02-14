#include <bits/stdint-uintn.h>

#pragma once

namespace headerflag
{

	/// @brief Query or Response, 1 bit, 0 -> 問い合わせ, 1 -> 応答
	enum class QR : uint16_t
	{
		QUERY = 0x0000,
		RESPONSE = 0x8000
	};

	/// @brief Opcode, 4 bits, 問い合わせの種類, 0 -> 標準問い合わせ, 1 -> 反問い合わせ, 2 -> サーバステータス問い合わせ, 4 -> 通知, 5 -> 更新
	enum class OPCode : uint16_t
	{
		QUERY = 0x0000,
		IQUERY = 0x0800,
		STATUS = 0x1000,
		NOTIFY = 0x2000,
		UPDATE = 0x2800
	};

	/// @brief Authoritative Answer, 1 bit, 0 -> 権威なし, 1 -> 権威あり
	enum class AA : uint16_t
	{
		NOT_AUTHORITATIVE = 0x0000,
		AUTHORITATIVE = 0x0400
	};

	/// @brief Truncated, 1 bit, 0 -> 通常 (512byte 以内) , 1 -> 切り詰め (512byte を超える)
	enum class TC : uint16_t
	{
		NOT_TRUNCATED = 0x0000,
		TRUNCATED = 0x0200
	};

	/// @brief Recursion Desired, 1 bit, 0 -> 再帰問い合わせ不要, 1 -> 再帰問い合わせ希望
	enum class RD : uint16_t
	{
		NO_RECURSION = 0x0000,
		RECURSION = 0x0100
	};

	/// @brief Recursion Available, 1 bit, 0 -> 再帰問い合わせ不可, 1 -> 再帰問い合わせ可
	enum class RA : uint16_t
	{
		NO_RECURSION = 0x0000,
		RECURSION = 0x0080
	};

	/// @brief Reserved, 1 bits, 予約
	enum class Z : uint16_t
	{
		RESERVED_0 = 0x0000,
		RESERVED_1 = 0x0040,
	};

	/// @brief Authentic Data, 1 bit, 0 -> データが信頼できない, 1 -> データが信頼できる
	enum class AD : uint16_t
	{
		UNTRUSTED = 0x0000,
		TRUSTED = 0x0020
	};

	/// @brief Checking Disabled, 1 bit, 0 -> データが検証される, 1 -> データが検証されない
	enum class CD : uint16_t
	{
		ENABLED = 0x0000,
		DISABLED = 0x0010
	};

	/// @brief Response Code, 4 bits, 応答の種類, 0 -> 正常, 1 -> エラー, 2 -> エラー, 3 -> エラー, 4 -> エラー, 5 -> エラー, 6 -> エラー, 7 -> エラー, 8 -> エラー, 9 -> エラー, 10 -> エラー, 11 -> エラー, 12 -> エラー, 13 -> エラー, 14 -> エラー, 15 -> エラー
	enum class RCode : uint16_t
	{
		NO_ERROR = 0x0000,
		FORMAT_ERROR = 0x0001,
		SERVER_FAILURE = 0x0002,
		NAME_ERROR = 0x0003,
		NOT_IMPLEMENTED = 0x0004,
		REFUSED = 0x0005,
		YXDOMAIN = 0x0006,
		YXRRSET = 0x0007,
		NXRRSET = 0x0008,
		NOTAUTH = 0x0009,
		NOTZONE = 0x000a
	};
}

enum DNSRecordType
{
	A = 1,
	NS = 2,
	MD = 3,
	MF = 4,
	CNAME = 5,
	SOA = 6,
	MB = 7,
	MG = 8,
	MR = 9,
	NULL_ = 10,
	WKS = 11,
	PTR = 12,
	HINFO = 13,
	MINFO = 14,
	MX = 15,
	TXT = 16,
	AAAA = 28,
	SRV = 33,
	OPT = 41,
	AXFR = 252,
	MAILB = 253,
	MAILA = 254,
	ANY = 255
};