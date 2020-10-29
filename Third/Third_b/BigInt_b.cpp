#include "BigInt_b.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

namespace Prog3b {
	BigInt::BigInt() {
		Int[0] = 0;
		for (int i = 1; i < SZ + 1; ++i) Int[i] = 0;
		n = 1;
	}
	BigInt::BigInt(long int x) {
		if (x < 0) Int[0] = 1;
		else Int[0] = 0;
		long int a = abs(x);
		int i = 1;
		n = 0;
		while (a) {
			++n;
			Int[i] = (a % 10);
			a /= 10;
			i++;
			if (n > SZ)
				throw std::runtime_error("Overflow");
		}
		for (int i = SZ; i >= n + 1; i--) Int[i] = 0;
	}
	BigInt::BigInt(const char* str) {
		Set(str);
	}
	BigInt& BigInt::Set(const char* str) {
		std::string STR = str;
		int l = STR.std::string::length();
		n = l;
		if (str[0] == '-') {
			Int[0] = 1;
			n--;
		}
		else Int[0] = 0;
		if (n > SZ) {
			throw std::runtime_error("Overflow");
		}
		int check = STR.std::string::find_first_not_of("-0123456789");
		if (check >= 0) {
			throw std::runtime_error("Incorrect data");
		}
		int z = 0, i = str[0] == '-' ? 1 : 0;
		if ((str[0] == '-' && str[1] == '0') || str[0] == '0') {
			while (str[i] == '0') {
				i++;
				z++;
			}
			if (i == l) {
				Int[0] = 0;
				n = 1;
				for (int i = 1; i < SZ + 1; ++i) Int[i] = 0;
				return *this;
			}
		}
		n -= z;
		i = l - 1;
		for (int k = 1; k <= n; k++) {
			Int[k] = str[i] - '0';
			i--;
		}
		for (int k = SZ; k >= n + 1; k--) Int[k] = 0;
		return *this;
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
		a.n = n;
		if (Int[1] == 0) a.Int[1] = 0;
		a.Int[0] = Int[0];
		return a;
	}
	BigInt BigInt::operator -() const {
		BigInt neg = *this;
		if ((n == 1 && Int[1] != 0) || (n != 1)) {
			neg.Int[0] = Int[0] == 0 ? 1 : 0;
		}
		neg.n = n;
		return neg;
	}
	bool BigInt::CompareAbs(const BigInt& t) const {
		if (n > t.n) return true;
		if (t.n > n) return false;
		if (t.n == n) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] > t.Int[i]) return true;
				if (t.Int[i] > Int[i]) return false;
			}
		}
		return false;
	}
	BigInt operator +(const BigInt fir, const BigInt sec) {
		int dop = 0;
		bool index = (fir.Int[0] == sec.Int[0]);
		int j = fir.n >= sec.n ? fir.n : sec.n;
		BigInt s1 = ~fir, s2 = ~sec;
		for (int i = 0; i < fir.SZ; i++) {
			if (s1.Int[i] + s2.Int[i] + dop < 10) {
				s1.Int[i] = s1.Int[i] + s2.Int[i] + dop;
				dop = 0;
			}
			else {
				s1.Int[i] = s1.Int[i] + s2.Int[i] + dop - 10;
				dop = 1;
			}
		}
		if ((dop > 0) && index && ((fir.Int[fir.SZ] != 0) || (sec.Int[sec.SZ] != 0)))
			throw std::runtime_error("Overflow!");
		if (!index) {
			if (fir.CompareAbs(sec)) s1.Int[0] = fir.Int[0];
			else if (sec.CompareAbs(fir)) s1.Int[0] = sec.Int[0];
			else {
				s1.Int[0] = 0;
				s1.n = 1;
				return s1;
			}
		}
		else s1.Int[0] = fir.Int[0];
		s1 = ~s1;
		if (j < fir.SZ) j += 1;
		for (int i = j; i > 0; i--) {
			if (s1.Int[i] != 0) {
				s1.n = i;
				break;
			}
		}
		return s1;
	}
	bool BigInt::operator >(const BigInt& second) {
		if (Int[0] == '1' && second.Int[0] == 0) return false;
		if (Int[0] == '0' && second.Int[0] == 1) return true;
		if (n > second.n) return true;
		if (n < second.n) return false;
		if (second.n == n && Int[0] == 0) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] > second.Int[i]) return true;
				if (second.Int[i] > Int[i]) return false;
			}
		}
		if (second.n == n && Int[0] == 1) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] > second.Int[i]) return false;
				if (second.Int[i] > Int[i]) return true;
			}
		}
		return false;
	}
	bool BigInt::operator <(const BigInt& second) {
		if (Int[0] == 1 && second.Int[0] == 0) return true;
		if (Int[0] == 0 && second.Int[0] == 1) return false;
		if (n < second.n) return true;
		if (n > second.n) return false;
		if (second.n == n && Int[0] == 0) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] < second.Int[i]) return true;
				if (second.Int[i] < Int[i]) return false;
			}
		}
		if (second.n == n && Int[0] == 1) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] < second.Int[i]) return false;
				if (second.Int[i] < Int[i]) return true;
			}
		}
		return false;
	}
	bool BigInt::operator ==(const BigInt& first) {
		if (n != first.n) return false;
		if (first.n == n && Int[0] == first.Int[0]) {
			for (int i = n; i >= 0; i--) {
				if (Int[i] != first.Int[i]) return false;
			}
			return true;
		}
		return false;
	}
	BigInt& BigInt::operator <<=(int pr) {
		if (n == 1 && Int[1] == 0) {
			n = 1;
			return *this;
		}
		Int[0] = Int[0];
		if (Int[SZ - pr] != 0)
			throw std::runtime_error("Overflow");
		for (int i = n; i >= 1; i--) Int[i + pr] = Int[i];
		for (int i = 1; i <= pr; i++) Int[i] = 0;
		n = n + pr;
		return *this;
	}
	BigInt BigInt::operator >>=(int pr) {
		if (!(n - pr > 0)) {
			for (int i = 0; i <= n; i++) {
				Int[i] = 0;
			}
			n = 1;
			return *this;
		}
		for (int i = 1; i <= n; i++) Int[i] = Int[i+pr];
		n = n - pr;
		return *this;
	}
	std::istream& operator >>(std::istream& s, BigInt& t) {
		try {
			char ptr[t.SZ] = "";
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
		if (t.n == 1) {
			if (t.Int[1] == 0) s << 0;
		}
		else {
			for (int i = t.n; i >= 1; i--) {
				int print = t.Int[i];
				s << print;
			}
		}
		return s;
	}
	BigInt::operator int() const {
		int i = 0;
		int pow = 1;
		if (n > 50)
			throw - 1;
		for (int k = 1; k <= n; k++) {
			i += Int[k] * pow;
			pow *= 10;
		}
		i = Int[0] == 0 ? i : -i;
		return i;
	}
}