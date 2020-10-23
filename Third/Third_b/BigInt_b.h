#pragma once
#ifndef _BIGINT_
#define _BIGINT_
#include <iostream>
namespace Prog3b {
	class BigInt {
	private:
		static const int SZ = 47;
		char Int[SZ + 1];
		int n;
	public:
		BigInt();
		BigInt(long int x);
		BigInt(const char* str);
		BigInt& Set(const char* str);
		BigInt operator ()(long int) const;
		BigInt operator ()(const char*) const;
		friend BigInt operator +(const BigInt&, const BigInt&);
		friend BigInt operator -(const BigInt& first, const BigInt& second) { return first + (-second); };
		BigInt operator -() const;
		const BigInt operator~() const;
		BigInt& operator <<=(int);
		BigInt& operator >>=(int);
		bool operator >(const BigInt&);
		bool operator <(const BigInt&);
		bool operator ==(const BigInt&);
		friend std::ostream& operator <<(std::ostream&, const BigInt&);
		friend std::istream& operator >>(std::istream&, BigInt&);
		bool CompareAbs(const BigInt&) const;
		operator int() const;
	};
}
#endif
