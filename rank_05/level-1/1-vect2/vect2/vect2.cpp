#include "vect2.hpp"

vect2::vect2()
{
	value[0] = 0;
	value[1] = 0;
}

vect2::vect2(int x, int y)
{
	value[0] = x;
	value[1] = y;
}

vect2::vect2(const vect2 &other)
{
	value[0] = other.value[0];
	value[1] = other.value[1];
}

vect2&	vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		value[0] = other.value[0];
		value[1] = other.value[1];
	}
	return (*this);
}

int&	vect2::operator[](int i)
{
	return (value[i]);
}

const int&	vect2::operator[](int i) const
{
	return (value[i]);
}

vect2	vect2::operator+(const vect2 &other) const
{
	return (vect2(value[0] + other[0], value[1] + other[1]));
}

vect2	vect2::operator-(const vect2 &other) const
{
	return (vect2(value[0] - other[0], value[1] - other[1]));
}

vect2	vect2::operator*(int scalar) const
{
	return (vect2(value[0] * scalar, value[1] * scalar));
}

vect2&	vect2::operator+=(const vect2 &other)
{
	value[0] += other[0];
	value[1] += other[1];
	return (*this);
}

vect2&	vect2::operator-=(const vect2 &other)
{
	value[0] -= other[0];
	value[1] -= other[1];
	return (*this);
}

vect2&	vect2::operator*=(int scalar)
{
	value[0] *= scalar;
	value[1] *= scalar;
	return (*this);
}

vect2	vect2::operator-() const
{
	return (vect2(-value[0], -value[1]));
}

vect2&	vect2::operator++()
{
	++value[0];
	++value[1];
	return (*this);
}

vect2&	vect2::operator--()
{
	--value[0];
	--value[1];
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2 tmp(*this);
	++(*this);
	return (tmp);
}

vect2	vect2::operator--(int)
{
	vect2 tmp(*this);
	--(*this);
	return (tmp);
}

bool	vect2::operator==(const vect2 &other) const
{
	return (value[0] == other[0] && value[1] == other[1]);
}

bool	vect2::operator!=(const vect2 &other) const
{
	return (!(*this == other));
}

vect2	operator*(int scalar, const vect2 &value)
{
	return (value * scalar);
}

std::ostream&	operator<<(std::ostream &os, const vect2 &value)
{
	os << "{" << value[0] << ", " << value[1] << "}";
	return (os);
}