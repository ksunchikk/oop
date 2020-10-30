#ifndef _BIG_DEC_
#define _BIG_DEC_
#include <iostream>

namespace Prog3c {
	class BigInt {
	private:
		static const int SZ = 47;
		char* Int;
		int n;
	public:
		BigInt();
		BigInt(long int x);
		BigInt(const char* str);
		BigInt& Set(const char* str);
		BigInt(BigInt&& t) :n(t.n), Int(t.Int) { t.Int = nullptr; }
		~BigInt() { delete[]Int; }
		BigInt(const BigInt&);
		friend BigInt operator +(const BigInt&, const BigInt&);
		BigInt& operator=(const BigInt&);
		BigInt& operator=(BigInt&&);
		BigInt& operator <<=(int);
		BigInt& operator >>=(int);
		bool operator >(const BigInt&);
		bool operator <(const BigInt&);
		bool operator ==(const BigInt&);
		bool CompareAbs(const BigInt&) const;
		friend BigInt operator -(const BigInt& first, const BigInt& second) { return first + (-second); };
		const BigInt operator~() const;
		const BigInt operator -() const;
		friend std::ostream& operator <<(std::ostream&, const BigInt&);
		friend std::istream& operator >> (std::istream&, BigInt&);
		operator int() const;
		BigInt& Resize(int, bool);
	};
}
#endif
