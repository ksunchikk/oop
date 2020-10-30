#include "BigInt_c.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

namespace Prog3c {
		BigInt::BigInt() {
			Int = new char[2];
			n = 1;
			Int[0] = '0';
			Int[1] = '0';
		}
		BigInt::BigInt(long int x) {
			long int a = abs(x);
			n = 0;
			while (a) {
				++n;
				a /= 10;
			}
			if (n > SZ)
				throw std::runtime_error("Overflow");
			Int = new char[n + 1];
			if (x < 0) Int[0] = '1';
			else Int[0] = '0';
			int i = 1;
			a = abs(x);
			while (a) {
				Int[i] = (a % 10) + '0';
				a /= 10;
				i++;
			}
		}
		BigInt::BigInt(const char* str) {
			Set(str);
		}
		BigInt& BigInt::Set(const char* str) {
			std::string STR = str;
			int l = STR.std::string::length();
			n = l;
			if (str[0] == '-') {
				n--;
			}
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
					Int = new char[2];
					Int[0] = '0';
					n = 1;
					Int[1] = '0';
					return *this;
				}
			}
			n -= z;
			Int = new char[n + 1];
			i = l - 1;
			for (int k = 1; k <= n; k++) {
				Int[k] = str[i];
				i--;
			}
			if (str[0] == '-') {
				Int[0] = '1';
			}
			else Int[0] = '0';
			return *this;
		}
		BigInt::BigInt(const BigInt& t) {
			try {
				n = t.n;
				Int = new char[n + 1];
				for (int i = 0; i < n + 1; i++)
					Int[i] = t.Int[i];
			}
			catch (...) {
				std::cout << "Empty initialization";
				n = 1;
				Int = new char[2];
				Int[0] = Int[1] = '0';
			}
		}

		BigInt& BigInt::Resize(int amount, bool flag) {
			char* tmp = new char[n + 1];
			for (int i = 0; i <= n; i++) tmp[i] = Int[i];
			delete[] Int;
			Int = new char[amount + 1];
			Int[0] = tmp[0];
			if (flag) {
				if (amount > n) {
					int pr = amount - n;
					for (int i = n; i >= 1; i--) Int[i + pr] = tmp[i];
					for (int i = 1; i <= pr; i++) Int[i] = '0';
				}
				if (amount < n) {
					int pr = n - amount;
					for (int i = n; i >= pr + 1; i--) Int[i - pr] = tmp[i];
				}
			}
			if (!flag) {
				for (int i = n; i >= 1; i--) Int[i] = tmp[i];
				for (int i = amount; i > n; i--) Int[i] = '0';
			}
			n = amount;
			delete[] tmp;
			return *this;
		}
		BigInt operator +(const BigInt& fir, const BigInt& sec) {
			int dop = 0;
			bool index = (fir.Int[0] == sec.Int[0]);
			int j = fir.n >= sec.n ? fir.n : sec.n;
			BigInt s1 = fir, s2 = sec;
			if (!(j + 1 >= fir.SZ)) {
				s1.Resize(j + 1, false), s2.Resize(j + 1, false);
				j++;
			}
			else {
				if (s1.n < fir.SZ)s1.Resize(j, false);
				else s2.Resize(j, false);
			}
			s1 = ~s1, s2 = ~s2;
			for (int i = 0; i <= j; i++) {
				if (s1.Int[i] - '0' + s2.Int[i] - '0' + dop < 10) {
					s1.Int[i] = s1.Int[i] - '0' + s2.Int[i] - '0' + dop + '0';
					dop = 0;
				}
				else {
					s1.Int[i] = s1.Int[i] - '0' + s2.Int[i] - '0' + dop - 10 + '0';
					dop = 1;
				}
			}
			if ((dop > 0) && index && (j + 1 >= fir.SZ))
				throw std::runtime_error("Overflow!");
			if (!index) {
				if (fir.CompareAbs(sec)) s1.Int[0] = fir.Int[0];
				else if (sec.CompareAbs(fir)) s1.Int[0] = sec.Int[0];
				else {
					s1.Int[0] = '0';
					s1.n = 1;
					return s1;
				}
			}
			else s1.Int[0] = fir.Int[0];
			s1 = ~s1;
			if (!(j < fir.SZ)) j -= 1;
			for (int i = j; i > 0; i--) {
				if (s1.Int[i] != '0') {
					char* tmp = new char[i + 1];
					for (int k = 0; k <= i; k++) tmp[k] = s1.Int[k];
					delete[] s1.Int;
					s1.Int = new char[i + 1];
					for (int k = 0; k <= i; k++) s1.Int[k] = tmp[k];
					s1.n = i;
					break;
				}
			}
			return s1;
		}
		BigInt& BigInt::operator = (const BigInt& t) {
			if (this->Int != t.Int) {
				if (Int != nullptr)
					delete[]Int;
				if (t.n != 0) {
					n = t.n;
					Int = new char[t.n + 1];
					for (int i = 0; i <= n; i++)
						Int[i] = t.Int[i];
				}
			}
			return*this;
		}
		BigInt& BigInt::operator = (BigInt&& t) {
			if (Int != nullptr) {
				delete[]Int;
				Int = t.Int;
				n = t.n;
				t.Int = nullptr;
			}
			return*this;
		}

		BigInt& BigInt::operator >>=(int pr) {
			if (!(n - pr > 0)) {
				delete[]Int;
				Int = new char[2];
				Int[0] = '0';
				Int[1] = '0';
				n = 1;
				return *this;
			}
			this->Resize(n - pr, true);
			return *this;
		}
		BigInt& BigInt::operator <<=(int pr) {
			if (n == 1 && Int[1] == 0) {
				return *this;
			}
			if (n + pr >= SZ)
				throw std::runtime_error("Overflow");
			this->Resize(n + pr, true);
			return *this;
		}
		const BigInt BigInt::operator~() const {
			BigInt a;
			if (Int[0] == '0')
				return *this;
			int pr = 1;
			a.Int = new char[n + 1];
			for (int i = 1; i <= n; i++) {
				if (pr && Int[i] != 0) {
					a.Int[i] = 10 - (Int[i] - '0') + '0';
					pr = 0;
				}
				else if (!pr)
					a.Int[i] = 9 - (Int[i] - '0') + '0';
			}
			a.n = n;
			a.Int[0] = Int[0];
			return a;
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
		bool BigInt::operator >(const BigInt& second) {
			if (Int[0] == '1' && second.Int[0] == '0') return false;
			if (Int[0] == '0' && second.Int[0] == '1') return true;
			if (n > second.n) return true;
			if (n < second.n) return false;
			if (second.n == n && Int[0] == '0') {
				for (int i = n; i >= 1; i--) {
					if (Int[i] > second.Int[i]) return true;
					if (second.Int[i] > Int[i]) return false;
				}
			}
			if (second.n == n && Int[0] == '1') {
				for (int i = n; i >= 1; i--) {
					if (Int[i] > second.Int[i]) return false;
					if (second.Int[i] > Int[i]) return true;
				}
			}
			return false;
		}
		bool BigInt::operator <(const BigInt& second) {
			if (Int[0] == '1' && second.Int[0] == '0') return true;
			if (Int[0] == '0' && second.Int[0] == '1') return false;
			if (n < second.n) return true;
			if (n > second.n) return false;
			if (second.n == n && Int[0] == '0') {
				for (int i = n; i >= 1; i--) {
					if (Int[i] < second.Int[i]) return true;
					if (second.Int[i] < Int[i]) return false;
				}
			}
			if (second.n == n && Int[0] == '1') {
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
		const BigInt BigInt::operator -() const {
			BigInt neg = *this;
			if ((n == 1 && Int[1] != '0') || (n != 1)) {
				neg.Int[0] = Int[0] == '0' ? '1' : '0';
			}
			neg.n = n;
			return neg;
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
			if (t.Int[0] == '1')
				s << "-";
			if (t.n == 1 && t.Int[1] == '0') s << '0';
			else {
				for (int i = t.n; i >= 1; i--) {
					s << t.Int[i];
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
				i += (Int[k] - '0') * pow;
				pow *= 10;
			}
			i = Int[0] == '0' ? i : -i;
			return i;
		}
}