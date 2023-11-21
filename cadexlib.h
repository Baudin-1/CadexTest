#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <iterator>

template<class T>
class MyVector3d {
public:

	MyVector3d(T x, T y, T z) : x(x), y(y), z(z) {}

	std::string to_str() const {
		ostringstream os;
		os << std::fixed << std::setprecision(2) << "(" << x << "," << y << "," << z << ")";
		return os.str();
	}

	friend std::ostream &operator<<(std::ostream &os, const MyVector3d &mv) {
		os << "(" << mv.x << "," << mv.y << "," << mv.z << ")";
		return os;
	}

	T x, y, z;
};

template<class T>
class Curve {
public:
	Curve(T x, T y, T z) : pos(x, y, z) {}

	virtual MyVector3d<T> derivative(double angle) const = 0;

	virtual MyVector3d<T> calculate(double angle) const = 0;

	virtual ~Curve() = default;

	MyVector3d<T> pos;
};

template<class T>
class Ellipse : public Curve<T> {
public:

	Ellipse(T a, T b, T x, T y, T z) : a(a), b(b), Curve<T>(x, y, z) {}

	Ellipse(T a, T b, T x, T y) : Ellipse(a, b, x, y, static_cast<T>(0)) {}


	MyVector3d<T> derivative(double angle) const override {
		return MyVector3d<T>(static_cast<T>(a * -sin(angle)), static_cast<T>(b * cos(angle)), 0);
	}
	MyVector3d<T> calculate(double angle) const override {
		return MyVector3d<T>(static_cast<T>(a * cos(angle) + this->pos.x), static_cast<T>(b * sin(angle) + this->pos.y), this->pos.z);
	}

	T a,b;
};

template<class T>
class Circle : public Ellipse<T> {
public:
	explicit Circle(T r, T x, T y, T z) : Ellipse<T>(r, r, x, y, z) {}
	explicit Circle(T r, T x, T y) : Circle(r, x, y, 0) {}

};

template<class T>
class Helix : public Curve<T> {
public:

	explicit Helix(T a, T b, T step, T x, T y, T z, double start_angle) : a(a), b(b), step(step), Curve<T>(x, y, z), start_angle(start_angle) {}
	explicit Helix(T r, T step, T x, T y, T z) : Helix<T>(r, r, step, x, y, z, 0) {}

	MyVector3d<T> derivative(double angle) const override {
		return MyVector3d<T>(static_cast<T>(a * -sin(angle)), static_cast<T>(b * cos(angle)), step / (M_PI * 2));
	}
	MyVector3d<T> calculate(double angle) const override {
		return MyVector3d<T>(static_cast<T>(a * cos(angle) + this->pos.x), static_cast<T>(b * sin(angle) + this->pos.y), (start_angle + angle) / (M_PI * 2)*step + this->pos.z);
	}

	T step, a, b;
	double start_angle;
};
