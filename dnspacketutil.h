#include <bits/stdint-uintn.h>

#pragma once

/// @brief Query or Response, 1 bit, 0 -> 問い合わせ, 1 -> 応答
enum class QR : uint8_t
{
	QUERY = 0,
	RESPONSE = 1
};

/// @brief Opcode, 4 bits, 問い合わせの種類, 0 -> 標準問い合わせ, 1 -> 反問い合わせ, 2 -> サーバステータス問い合わせ, 4 -> 通知, 5 -> 更新
enum class OPCode : uint8_t
{
	QUERY = 0,
	IQUERY = 1,
	STATUS = 2,
	NOTIFY = 4,
	UPDATE = 5
};

/// @brief Authoritative Answer, 1 bit, 0 -> 権威なし, 1 -> 権威あり
enum class AA : uint8_t
{
	NOT_AUTHORITATIVE = 0,
	AUTHORITATIVE = 1
};

/// @brief Truncated, 1 bit, 0 -> 通常 (512byte 以内) , 1 -> 切り詰め (512byte を超える)
enum class TC : uint8_t
{
	NOT_TRUNCATED = 0,
	TRUNCATED = 1
};

/// @brief Recursion Desired, 1 bit, 0 -> 再帰問い合わせ不要, 1 -> 再帰問い合わせ希望
enum class RD : uint8_t
{
	NO_RECURSION = 0,
	RECURSION = 1
};

/// @brief Recursion Available, 1 bit, 0 -> 再帰問い合わせ不可, 1 -> 再帰問い合わせ可
enum class RA : uint8_t
{
	NO_RECURSION = 0,
	RECURSION = 1
};

/// @brief Reserved, 1 bits, 予約
enum class Z : uint8_t
{
	RESERVED_0 = 0,
	RESERVED_1 = 1
};

/// @brief Authentic Data, 1 bit, 0 -> データが信頼できない, 1 -> データが信頼できる
enum class AD : uint8_t
{
	UNTRUSTED = 0,
	TRUSTED = 1
};

/// @brief Checking Disabled, 1 bit, 0 -> データが検証される, 1 -> データが検証されない
enum class CD : uint8_t
{
	ENABLED = 0,
	DISABLED = 1
};

/// @brief Response Code, 4 bits, 応答の種類, 0 -> 正常, 1 -> エラー, 2 -> エラー, 3 -> エラー, 4 -> エラー, 5 -> エラー, 6 -> エラー, 7 -> エラー, 8 -> エラー, 9 -> エラー, 10 -> エラー, 11 -> エラー, 12 -> エラー, 13 -> エラー, 14 -> エラー, 15 -> エラー
enum class RCode : uint8_t
{
	NO_ERROR = 0,
	FORMAT_ERROR = 1,
	SERVER_FAILURE = 2,
	NAME_ERROR = 3,
	NOT_IMPLEMENTED = 4,
	REFUSED = 5,
	YXDOMAIN = 6,
	YXRRSET = 7,
	NXRRSET = 8,
	NOTAUTH = 9,
	NOTZONE = 10,
	DSOTYPENI = 11,
	BADVERS = 16,
	BADKEY = 17,
	BADTIME = 18,
	BADMODE = 19,
	BADNAME = 20,
	BADALG = 21,
	BADTRUNC = 22,
	BADCOOKIE = 23
};

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