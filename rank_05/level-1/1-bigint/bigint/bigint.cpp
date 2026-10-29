#include "bigint.hpp"

// -------------------- 1.BLOCK --------------------
bigint::bigint() : digits("0") 
{
}

bigint::bigint(unsigned int value) 
{
	std::stringstream ss;
	ss << value;
	digits = ss.str();
}

bigint::bigint(const std::string& value) {
	if (value.empty())
		throw std::invalid_argument("invalid input");

	std::string::const_iterator start 	= value.begin();
	std::string::const_iterator end 	= value.end();

	while (start != end) 
	{
		if (!std::isdigit(*start))
			throw std::invalid_argument("invalid input");
		++start;
	}
	digits = value;
	removeZeros();
}

bigint::bigint(const bigint& other) : digits(other.digits) 
{
}

bigint& bigint::operator=(const bigint& other) 
{
	if (this != &other)
		digits = other.digits;
	return (*this);
}

void	bigint::removeZeros() 
{
	std::string::size_type pos = digits.find_first_not_of('0');

	if (pos == std::string::npos)
		digits = "0";
	else
		digits.erase(0, pos);
}

// -------------------- 2.BLOCK --------------------
bigint bigint::operator+(const bigint& other) const 
{
	std::string result;
	int i = digits.size() - 1;
	int j = other.digits.size() - 1;
	int carry = 0;

	while (i >= 0 || j >= 0 || carry > 0) 
	{
		int digit1 = (i >= 0) ? digits[i--] - '0' : 0;
		int digit2 = (j >= 0) ? other.digits[j--] - '0' : 0;
		int sum = digit1 + digit2 + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
	}
	std::reverse(result.begin(), result.end());
	return (bigint(result));
}

bigint& bigint::operator+=(const bigint& other) 
{
	*this = *this + other;
	return (*this);
}


// -------------------- 3.BLOCK --------------------
bigint& bigint::operator++(void) 
{
	*this = *this + bigint(1);
	return (*this);
}

bigint bigint::operator++(int) 
{
	bigint temp(*this);
	*this = *this + bigint(1);
	return (temp);
}

// ----------------- (6)
bool bigint::operator>(const bigint& other) const 
{
	if (digits.size() != other.digits.size())
		return (digits.size() > other.digits.size());

	return (digits > other.digits);
}

bool bigint::operator<(const bigint& other) const 
{
	return (other > *this);
}

bool bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
}

bool bigint::operator<=(const bigint& other) const 
{
	return !(*this > other);
}

bool bigint::operator==(const bigint& other) const 
{
	return (digits == other.digits);
}

bool bigint::operator!=(const bigint& other) const 
{
	return !(*this == other);
}

// -------------------- 4.BLOCK --------------------
// ----------------- (6)
bigint bigint::operator<<(int i) const 
{
	bigint result(*this);
	result <<= i;
	return (result);
}

bigint bigint::operator>>(int i) const 
{
	bigint result(*this);
	result >>= i;
	return (result);
}

bigint& bigint::operator<<=(int i)
{
	if (digits != "0")
		digits += std::string(i, '0');
	return (*this);
}

bigint& bigint::operator>>=(int i)
{
	if ((size_t)i >= digits.size())
		digits = "0";
	else
		digits.erase(digits.size() - i);
	return (*this);
}

bigint& bigint::operator<<=(const bigint& other) 
{
	std::istringstream iss(other.digits);
	int shift;
	iss >> shift;
	return (*this <<= shift);
}

bigint& bigint::operator>>=(const bigint& other) 
{
	std::istringstream iss(other.digits);
	int shift;
	iss >> shift;
	return (*this >>= shift);
}

// -----------------
const std::string& bigint::getDigits(void) const 
{
	return (digits);
}

std::ostream& operator<<(std::ostream& os, const bigint& n) 
{
	os << n.getDigits();
	return (os);
}
