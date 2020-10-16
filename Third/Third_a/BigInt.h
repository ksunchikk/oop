#pragma once
#ifndef _BIGINT_
#define _BIGINT_
#include <iostream>
namespace Prog3a {
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
		BigInt Inc() const;
		BigInt Dec() const;
		const BigInt Dopcode() const;
		int Large(BigInt& t) const;
		BigInt Summa(BigInt& t) const;
		BigInt Subtraction(BigInt) const;
		BigInt InputStr() const;
		void Print() const;
	};
}
#endif

