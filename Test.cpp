#pragma once
#define _USE_MATH_DEFINES
#include "cadexlib.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>

double random(double min, double max);

int main()
{
	using namespace std;
	using type = double;
	srand(time(NULL));


	/* 2. Populate a container(e.g.vector or list) of objects of these types created in random manner with random parameters.*/
	vector<shared_ptr<Curve<type>>> Curves;

	for (int i = 0; i < 10; i++)
	{
		switch (0 + rand() % 3)
		{
		case 0:
			Curves.push_back(make_shared<Circle<type>>(random(0, 10), random(-10, 10), random(-10, 10)));
		case 1:
			Curves.push_back(make_shared<Ellipse<type>>(random(0, 10), random(0, 10), random(-10, 10), random(-10, 10)));
		case 2:
			Curves.push_back(make_shared<Helix<type>>(random(0, 10), random(0, 10), random(-10, 10), random(-10, 10), random(-10, 10)));
		}
	}

	/* 3. Print coordinates of points and derivatives of all curves in the container at t = PI / 4.*/
	for (auto& curve_ptr : Curves)
	{
		auto *curve = curve_ptr.get();
		cout << fixed << setprecision(2) << typeid(*curve).name() << "| dC(t)/dt = " << curve->derivative(M_PI_4) << "| c(t) = " << curve->calculate(M_PI_4) << "| t = PI/4" << endl;
	}
	
	/*  class Helix<double> dC(t) / dt = (-0.08, 0.08, 0.52) c(t) = (5.29, -9.33, 10.28) t = PI / 4
		class Ellipse<double> dC(t) / dt = (-5.72, 1.40, 0.00) c(t) = (2.14, -3.01, 0.00) t =PI / 4
		class Helix<double> dC(t) / dt = (-1.93, 1.93, 0.11) c(t) = (4.56, 5.53, 9.86) t = PI /4
		class Helix<double> dC(t) / dt = (-4.76, 4.76, 0.86) c(t) = (-0.58, 14.36, -5.10) t =PI / 4
		class Circle<double> dC(t) / dt = (-3.46, 3.46, 0.00) c(t) = (-2.70, 13.05, 0.00) t =PI / 4
		class Ellipse<double> dC(t) / dt = (-5.01, 4.77, 0.00) c(t) = (-4.33, 10.06, 0.00) t =PI / 4
		class Helix<double> dC(t) / dt = (-5.07, 5.07, 0.41) c(t) = (-1.29, -2.81, -3.36) t =PI / 4
		class Helix<double> dC(t) / dt = (-6.05, 6.05, 0.44) c(t) = (7.93, 10.45, -8.00) t = PI / 4
		class Helix<double> dC(t) / dt = (-1.10, 1.10, 0.16) c(t) = (-2.12, -2.52, 3.13) t = PI / 4
		class Circle<double> dC(t) / dt = (-4.85, 4.85, 0.00) c(t) = (9.56, 3.91, 0.00) t = PI / 4
		class Ellipse<double> dC(t) / dt = (-7.02, 1.98, 0.00) c(t) = (-2.08, -7.22, 0.00) t =PI / 4
		class Helix<double> dC(t) / dt = (-0.77, 0.77, 0.69) c(t) = (-7.94, -8.82, 2.56) t = PI / 4
		class Circle<double> dC(t) / dt = (-0.01, 0.01, 0.00) c(t) = (6.80, 9.68, 0.00) t = PI / 4
		class Ellipse<double> dC(t) / dt = (-1.28, 1.96, 0.00) c(t) = (3.65, 3.02, 0.00) t = PI / 4
		class Helix<double> dC(t) / dt = (-1.85, 1.85, 0.18) c(t) = (2.60, -5.94, 9.67) t = PI / 4
		class Circle<double> dC(t) / dt = (-2.91, 2.91, 0.00) c(t) = (1.10, 9.44, 0.00) t = PI / 4
		class Ellipse<double> dC(t) / dt = (-6.86, 1.06, 0.00) c(t) = (7.37, -4.27, 0.00) t =PI / 4
		class Helix<double> dC(t) / dt = (-5.18, 5.18, 0.81) c(t) = (10.80, 4.01, -2.45) t = PI / 4
		class Helix<double> dC(t) / dt = (-0.69, 0.69, 1.47) c(t) = (3.79, 3.42, 7.30) t = PI / 4   */






	/* 4. Populate a second container that would contain only circles from the first container.Make sure the
		second container shares(i.e. not clones) circles of the first one, e.g.via pointers.*/
	vector<shared_ptr<Circle<type>>> Circles;

	for (auto& curve_ptr : Curves) {
		if (auto circle = dynamic_pointer_cast<Circle<type>>(curve_ptr)) {
			Circles.push_back(circle);
		}

	/* 5. Sort the second container in the ascending order of circles’ radii.That is, the first element has the
			smallest radius, the last - the greatest.*/
		sort(Circles.begin(), Circles.end(), [](shared_ptr<Circle<type>> l, shared_ptr<Circle<type>> r) {return l->a < r->a; });

	/* 6. Compute the total sum of radii of all curves in the second container.*/
		type sum_of_r = 0;
		for (auto& circle : Circles)
			sum_of_r += circle->a;
		
		return 0;
	}
}
double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX*(max - min) + min;
}
