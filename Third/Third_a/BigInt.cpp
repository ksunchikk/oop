#include "BigInt.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
namespace Prog3a {

	BigInt::BigInt()
	{
		Int[0] = '0';
		for (int i = 1; i < SZ + 1; ++i) Int[i] = '0';
		n = 1;
	}
	BigInt::BigInt(long int x){
		try {
			long int a = abs(x);
			while (a){
				++n;
				a /= 10;
			}
			if (x < 0) Int[0] = '1';
			else Int[0]='0'; 
			if (n > SZ)
				throw "Overflow";
			for (int i = 1; i <= n; i++) {
				Int[i] = (a % 10 + '0');
				a /= 10;
			}
			for (int i = SZ; i >= SZ - n + 1; i--)
				Int[i] = '0';
		}
		catch (const std::exception & msg) {
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
	BigInt& BigInt::Set(const char* str){
		try {
			if (str == nullptr)
				throw "Nullptr";
			int l = strlen(str);
			n = l;
			int z=0;
			if (str[0] == '-') {
				Int[0] = '1';
				z++;
				n--;
			}
			else Int[0] = '0';
			int pr1 = strspn(str, "0123456789-");
			if (l != pr1) {
				Int[0] = '0';
				throw "Incorrect data. Your number can begin only from - or 0-9 chars and contain 0-9 chars";
			}
			int i = l-1;
			bool tmp = true;
			for (int k = 1; k <= n; k++) {
				Int[k] = str[i];
				i--;
				if (tmp && Int[k] != '0')
					tmp = false;
			}
			if (tmp)
				Int[0] = '0';
			for (int k = SZ; k >= n + 1; k--)
				Int[k] = '0';
		}
		catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		return *this;
		}
	
	const BigInt BigInt::Dopcode() const{
		BigInt a;
		if (Int[0] == '0')
			return *this;
		int pr = 1;
		for (int i = 1; i <= SZ; i++) {
			if (pr && Int[i] != '0') {
					a.Int[i] = (char)10 - (Int[i] - '0') + '0';
					pr=0;
			}
			else if (!pr)
				a.Int[i] = (char)9 - (Int[i] - '0') + '0';
		}
		if (Int[1] == '0') a.Int[1] = '0';
		a.Int[0] = '1';
		return a;
	}
	int BigInt::Large(BigInt& t) const {
		if (n > t.n) return 1;
		if (t.n > n) return 0;
		if (t.n == n) {
			for (int i = n; i >= 1; i--) {
				if (Int[i] > t.Int[i]) return 1;
				if (t.Int[i] > Int[i])return 0;
			}
		}
	}
	BigInt BigInt::Summa(BigInt& t)const
	{
		try {
			int dop = 0;
			bool index = (Int[0] == t.Int[0]);
			int j = n >= t.n ? n : t.n;
			BigInt s1 = (this)->Dopcode(), s2(t.Dopcode());
			for(int i = 0; i <= SZ; i++) {
				if (s1.Int[i] - '0' + s2.Int[i] - '0' + dop < 10) {
					s1.Int[i] = (char)s1.Int[i] - '0' + s2.Int[i] - '0' + dop + '0';
					dop = 0;
				}
				else {
					s1.Int[i] = (char)s1.Int[i] - '0' + s2.Int[i] - '0' + dop + '0' - 10;
					dop = 1;
				}
			}
			if (dop > 0 && index)
				throw "Overflow";
			if (!index) {
				if ((this)->Large(t)) {
					s1.Int[0] = Int[0];
				}
				else s1.Int[0] = t.Int[0];
			}
			if (index)s1.Int[0] = Int[0];
			s1 = s1.Dopcode();
			if (s1.Int[j + 1] != '0') s1.n = j + 1;
			else s1.n = j;
			return s1;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
			return '0';
		}
	}

	BigInt BigInt::Subtraction(BigInt t) const
	{
		BigInt s2 = t, s1 = *this;
		if (s2.Int[0] == '0') s2.Int[0] = '1';
		else s2.Int[0] = '0';
		s1 = s1.Summa(s2);
		return s1;
	}
	BigInt BigInt::Inc() const
	{
		try {
			BigInt inc;
			inc.n = n + 1;
			inc.Int[0] = Int[0];
			if (Int[SZ] != '0')
				throw "Overflow";
			inc.Int[1] = '0';
			for (int i = n; i >= 1; i--)
				inc.Int[i+1] = Int[i];
			return inc;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
			return *this;
		}
	}
	BigInt BigInt::Dec() const
	{
			BigInt inc;
			inc.n = n - 1;
			inc.Int[0] = Int[0];
			if (strspn(Int, "123456789") == 0) return *this;
			if (n == 1) return inc;
			for (int i = n; i >= 2; i--)
				inc.Int[i - 1] = Int[i];
			return inc;
	
	}

	BigInt BigInt::InputStr() const{
		try {
			char* ptr = (char*)malloc(1);
			*ptr = '\0';
			char buf[81];
			int n;
			int len = 0;
			do
			{
				n = scanf_s("%80[^\n]", buf, 81);
				if (n < 0)
				{
					free(ptr);
					ptr = NULL;
					continue;
				}
				if (n == 0)
					scanf_s("%*c");
				else
				{
					len += strlen(buf);
					ptr = (char*)realloc(ptr, len + 1);
					strcat_s(ptr, len + 1, buf);
				}
			} while (n > 0);
			if (strlen(ptr) > SZ + 1)
			{
				std::cout << "Overflow. You enter too big number" << std::endl;
				return *this;
			}
			BigInt a(ptr);
			return a;
		    
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
	}
	void BigInt::Print() const
	{
		if (Int[0] == '1')
			std::cout << "-";
		bool k = false;
		if (n == 1) {
			if (Int[1] == '0') k = true;
		}
		if (k) std::cout << '0';
		else {
			for (int i = n; i >= 1; i--)
				std::cout << Int[i];
		}
	}

}