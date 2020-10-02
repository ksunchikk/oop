#ifndef LEMNISCATE_H_
#define LEMNISCATE_H_
#include <math.h>
#include <sstream>

namespace Second {
	class Lemniscate{
	private:
		double f;
	public:
		Lemniscate (double focus = 1.0);
		Lemniscate& setFocus(double focus);
		double getFocus() const { return f; };
		double focusdist() const { return 2 * f; };
		double rad() const { return sqrt(2) * f; };
		double polardist(double ang) const;
		std::string formula() const;
		double S() const { return 2 * (f * f); };
		double radAngle(double ang) const;
		double radRad(double rad) const;

		double Ssector(double ang) const;

		
	};
}
#endif
