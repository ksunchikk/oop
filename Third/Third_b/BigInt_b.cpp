#include "BigInt_b.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

namespace Prog3b {

	BigInt::BigInt()
	{
		Int[0] = 0;
		for (int i = 1; i < SZ + 1; ++i) Int[i] = 0;
		n = 1;
	}
	BigInt::BigInt(long int x) {
		try {
			long int a = abs(x);
			n = 0;
			while (a) {
				++n;
				a /= 10;
			}
			if (x < 0) Int[0] = 1;
			else Int[0] = 0;
			if (n > SZ)
				throw "Overflow";
			a = x;
			for (int i = 1; i <= n; i++) {
				Int[i] = (a % 10);
				a /= 10;
			}
			for (int i = SZ; i >= (n + 1); i--)
				Int[i] = 0;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
	}
	BigInt::BigInt(const char* str) {
		try {
			Set(str);
		}
		catch (std::exception& a) {
			throw std::exception("Wrong data");
		}
	}
	BigInt& BigInt::Set(const char* str) {
		try {
			if (str == nullptr)
				throw "Nullptr";
			int l = strlen(str);
			n = l;
			int z = 0;
			if (str[0] == '-') {
				Int[0] = 1;
				z++;
				n--;
			}
			else Int[0] = 0;
			int pr1 = strspn(str,"0123456789");
			if (pr1 != l) {
				Int[0] = 0;
				throw "Incorrect data. Your number can begin only from - or 0-9 chars and contain 0-9 chars";
			}
			int i = 0;
			i = l - 1;
			bool tmp = true;
			for (int k = 1; k <= n; k++) {
				Int[k] = str[i] - '0';
				i--;
				if (tmp && Int[k] != 0)
					tmp = false;
			}
			if (tmp)
				Int[0] = 0;
			for (int k = SZ; k >= n + 1; k--)
				Int[k] = 0;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		return *this;
	}
	BigInt BigInt::operator ()(long int x) const {
		BigInt a(x);
		return a;
	}
	BigInt BigInt::operator ()(const char* str) const {
		BigInt a(str);
		return a;
	}
	const BigInt BigInt::operator~() const {
		BigInt a;
		if (Int[0] == 0)
			return *this;
		int pr = 1;
		for (int i = 1; i <= SZ; i++) {
			if (pr && Int[i] != 0) {
				a.Int[i] = 10 - Int[i];
				pr = 0;
			}
			else if (!pr)
				a.Int[i] = 9 - Int[i];
		}
		if (Int[1] == 0) a.Int[1] = 0;
		a.Int[0] = 0;
		return a;
	}
	BigInt BigInt::operator -() const {
		BigInt neg = *this;
			if ((n == 1 && Int[1]!=0)||(n!=1)) {
				neg.Int[0] = Int[0] == 0 ? 1 : 0;
			}
		neg.n = n;
		return neg;
	}
    bool operator >(const BigInt& first, const BigInt& second) {
		if (first.n > second.n) return true;
		if (first.n > second.n) return false;
		if (second.n == first.n) {
			for (int i = first.n; i >= 1; i--) {
				if (first.Int[i] > second.Int[i]) return true;
				if (second.Int[i] > first.Int[i]) return false;
			}
		}
		return false;
	}
    bool operator <(const BigInt& first, const BigInt& second) {
			if (first.n < second.n) return true;
			if (first.n < second.n) return false;
			if (second.n == first.n) {
				for (int i = first.n; i >= 1; i--) {
					if (first.Int[i] < second.Int[i]) return true;
					if (second.Int[i] < first.Int[i]) return false;
				}
			}
			return false;
		}
	bool operator ==(const BigInt& first, const BigInt& second) {
			if (first.n != second.n) return false;
			if (second.n == first.n) {
				for (int i = first.n; i >= 1; i--) {
					if (first.Int[i] != second.Int[i]) return false;
				}
			}
			return true;
		}
	BigInt operator +(const BigInt& fir, const BigInt& sec){
		try {
			int dop = 0;
			bool index = (fir.Int[0] == sec.Int[0]);
			int j = fir.n >= sec.n ? fir.n : sec.n;
			BigInt s1 = ~fir, s2=~sec;
			for (int i = 0; i <= fir.SZ; i++) {
				if (s1.Int[i] + s2.Int[i] + dop < 10) {
					s1.Int[i] = s1.Int[i] + s2.Int[i] + dop;
					dop = 0;
				}
				else {
					s1.Int[i] = s1.Int[i] + s2.Int[i] + dop - 10;
					dop = 1;
				}
			}
			if (dop > 0 && index)
				throw "Overflow";
			if (!index) {
				if (fir>sec) {
					s1.Int[0] = fir.Int[0];
				}
				else s1.Int[0] = sec.Int[0];
			}
			if (index)s1.Int[0] = fir.Int[0];
			s1 = ~s1;
			for (int i = j; i > 0; i--) {
				if (s1.Int[i] != 0) {
					s1.n = i;
					break;
				}
			}
			return s1;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
			BigInt inc;
			return inc;
		}
	}
	BigInt& BigInt::operator <<=(int pr){
		try {
			BigInt inc;
			inc.n = n + pr;
			inc.Int[0] = Int[0];
			if (Int[SZ-pr] != 0)
				throw "Overflow";
			for (int i = 1; i <= pr; i++) inc.Int[i] = 0;
			for (int i = n; i >= 1; i--)
				inc.Int[i + pr] = Int[i];
			return inc;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
			return *this;
		}
	}
	BigInt& BigInt::operator >>=(int pr) {
		BigInt inc;
		if (n - pr > 0) inc.n = n - pr;
		else return inc;
		inc.Int[0] = Int[0];
		for (int i = n; i >= pr+1; i--)
			inc.Int[i - pr] = Int[i];
		return inc;
	}
	std::istream& operator >>(std::istream& s, BigInt& t) {
		try {
			char ptr[t.SZ]="";
			int n;
			int len = 0;
			s >> ptr;
			if (strlen(ptr) > t.SZ + 1)
			{
				std::cout << "Overflow. You enter too big number" << std::endl;
			}
			std::cin.clear();
			t.Set(ptr);
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		return s;
	}
	std::ostream& operator <<(std::ostream& s, const BigInt& t) {
		if (t.Int[0] == 1)
			s << "-";
		bool k = false;
		if (t.n == 1) {
			if (t.Int[1] == 0) k = true;
		}
		if (k) s << 0;
		else {
			for (int i = t.n; i >= 1; i--) {
				int print = t.Int[i];
				s << print;
			}
		}
		return s;
	}
	
}