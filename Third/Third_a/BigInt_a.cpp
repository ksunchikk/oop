#include "BigInt_a.h"
#include <iostream>
#include <string.h>

namespace Prog3a {
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
		for (int i = SZ; i >= SZ - n + 1; i--) Int[i] = 0;
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
	const BigInt BigInt::AddCode() const {
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
	bool BigInt::Large(const BigInt& t) const {
		if (n > t.n) return true;
		if (t.n > n) return false;
		if (t.n == n) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] > t.Int[i]) return true;
				if (t.Int[i] > Int[i]) return false;
			}
		}
	}
	BigInt BigInt::Sum(const BigInt& t)const {
		int dop = 0;
		bool index = (Int[0] == t.Int[0]);
		int j = n >= t.n ? n : t.n;
		BigInt s1 = (this)->AddCode(), s2(t.AddCode());
		for (int i = 0; i < SZ; i++) {
			if (s1.Int[i] + s2.Int[i] + dop < 10) {
				s1.Int[i] = s1.Int[i] + s2.Int[i] + dop;
				dop = 0;
			}
			else {
				s1.Int[i] = s1.Int[i] + s2.Int[i] + dop - 10;
				dop = 1;
			}
		}
		if ((dop > 0) && index && ((Int[SZ] != 0) || (t.Int[SZ] != 0)))
			throw std::runtime_error("Overflow!");
		if (!index) {
			if ((this)->Large(t)) {
				s1.Int[0] = Int[0];
			}
			else if (t.Large(*this)) {
				s1.Int[0] = t.Int[0];
			}
			else {
				s1.Int[0] = 0;
				s1.n = 1;
				return s1;
			}
		}
		else s1.Int[0] = Int[0];
		s1 = s1.AddCode();
		if (j < SZ) j += 1;
		for (int i = j; i > 0; i--) {
			if (s1.Int[i] != 0) {
				s1.n = i;
				break;
			}
		}
		return s1;
	}
	BigInt BigInt::Subtraction(BigInt t) const {
		BigInt s2 = t, s1 = *this;
		if (s2.Int[0] == 0) s2.Int[0] = 1;
		else s2.Int[0] = 0;
		s1 = s1.Sum(s2);
		return s1;
	}
	BigInt BigInt::Inc() const
	{
		BigInt inc;
		inc.n = n + 1;
		if (n == 1 && Int[1] == 0) {
			inc.n = 1;
			return inc;
		}
		if (Int[SZ] != 0)
			throw std::runtime_error("Overflow!");
		inc.Int[0] = Int[0];
		inc.Int[1] = 0;
		for (int i = n; i >= 1; i--)
			inc.Int[i + 1] = Int[i];
		return inc;
	}
	BigInt BigInt::Dec() const
	{
		BigInt inc;
		inc.n = n - 1;
		if (n == 1) {
			inc.n = 1;
			return inc;
		}
		inc.Int[0] = Int[0];
		for (int i = n; i >= 2; i--)
			inc.Int[i - 1] = Int[i];
		return inc;
	}
	BigInt BigInt::InputStr() const {
		const char* ptr = "";
		int n;
		std::string ss;
		std::cin >> ss;
		if (ss.std::string::length() > SZ + 1) {
			throw std::runtime_error("Overflow!");
		}
		ptr = ss.c_str();
		std::cin.clear();
		BigInt a(ptr);
		return a;
	}
	void BigInt::Print() const
	{
		if (Int[0] == 1)
			std::cout << "-";
		bool k = false;
		if (n == 1 && Int[1] == 0) std::cout << 0;
		else {
			for (int i = n; i >= 1; i--) {
				int t = Int[i];
				std::cout << t;
			}
		}
	}
	int BigInt::ToInt() const {
		int i = 0;
		int pow = 1;
		if (n > 8)
			throw - 1;
		for (int k = 1; k <= n; k++) {
			i += Int[k] * pow;
			pow *= 10;
		}
		i = Int[0] == 0 ? i : -i;
		return i;
	}
}