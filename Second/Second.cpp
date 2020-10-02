#include "Lemniscate.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
double const PI = 3.141592;

namespace Second {
	Lemniscate::Lemniscate(double focus) {
		if (focus == 0)
			throw std::exception("Invalid focus");
		f = abs(focus);
	}

	Lemniscate& Lemniscate::setFocus(double focus) {
		if (focus == 0)
			throw std::exception("Invalid focus");
		f = abs(focus);
		return *this;
	}

	double Lemniscate::Ssector(double ang) const {
		if (ang >= 360 || ang < 0)
			throw std::exception("Invalid angle");
		if (ang == 0) return 0;
		if (ang == 180) return f * f;
		if (ang == 360) return 2 * f * f;
		double ang1=ang, s=0;
		if (ang1 >= 180) {
			s = s + f * f;
			ang1 = ang1 - 180;
		}
		if (ang1 >= 45) {
			s = s + f * f/2;
			ang1 = ang1 - 135;
			if (ang1 > 0) {
				ang1 = ang1 * PI / 180;
				s = s + f * f / 2 - (f * f * sin(2 * (PI / 4 - ang1)) / 2);
			}
		}
		else {
			ang1 = ang1 * PI / 180;
			s =s+ f * f * sin(2 * ang1) / 2;
		}
		return s;
	}

	double Lemniscate::polardist(double ang) const {
		if (ang >= 360 || ang < 0)
			throw std::exception("Invalid angle");
		if ((ang>45 && ang<135)||(ang>225 && ang<315))
			throw std::exception("Invalid angle");
		double ang1=ang;
		if (ang > 135 && ang < 180) ang1 = 180 - ang1;
		else if (ang > 180 && ang < 225) ang1 = ang - 180;
		else if(ang<45 || ang>315) ang1 = ang;
		ang1 = ang1 * PI / 180;
		return sqrt(2 * f * f * cos(2 * ang1));
	}

	double Lemniscate::radAngle(double ang) const {
		if (ang >= 360 || ang < 0)
			throw std::exception("Invalid angle");
		if ((ang > 45 && ang < 135) || (ang > 225 && ang < 315))
			throw std::exception("Invalid angle");
		double ang1=ang;
		if (ang > 135 && ang < 180) ang1 = 180 - ang1;
		else if (ang > 180 && ang < 225) ang1 = ang - 180;
		else if (ang < 45 || ang>315) ang1 = ang;
		ang1 = ang1 * PI / 180;
		return ((2 * f )/ (3 * sqrt(2 * cos(2 * ang1))));
	}
	double Lemniscate::radRad(double rad) const {
		if (rad <0 )
			throw std::exception("Invalid radius");
		if(rad>abs(sqrt(2 * f * f * cos(0))))
			throw std::exception("Invalid radius");
		return 2 * f * f /( 3 * rad);
	}
	char* Lemniscate::formula() const {
		const char* s1 = " (x ^ 2 + y ^ 2) ^ 2 = 2 *  ^ 2 * (x ^ 2 - y ^ 2)";
		int l = strlen(s1) + 1;
		char num[20];
		sprintf_s(num, 20, "%.2f", f);
		l += strlen(num);
		char* s = new char[l];
		sprintf_s(s, l, "(x ^ 2 + y ^ 2) ^ 2 = 2 * %.2f ^ 2 * (x ^ 2 - y ^ 2)", f);
		return s;
	}
}