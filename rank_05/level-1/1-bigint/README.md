# BigInt

## Overview

An arbitrary-precision **unsigned integer** implemented using `std::string`.

```shell
		bigint(1337)
			↓
		digits = "1337"
```

---

<details>
<summary><b>Class Structure</b></summary>

```cpp
	class bigint
	{
		private:
			std::string digits;
			void removeZeros();

		public:
			bigint();
			bigint(unsigned int value);
			bigint(const std::string& value);

			bigint(const bigint& other);
			bigint& operator=(const bigint& other);

			bigint  operator+(const bigint& other) const;
			bigint& operator+=(const bigint& other);
};
```

</details>

---

<details>
<summary><b>Storage</b></summary>

- The number is stored as a `std::string`:

	```cpp
		std::string digits;
	```

	```cpp
		Number: 1337

		digits = "1337"
				││││
				1337
	```

- This allows numbers larger than normal integer types.

</details>

---

<details>
<summary><b>Constructors</b></summary>

### Default

```cpp
	bigint::bigint()
	: digits("0")
	{
	}
```

```shell
	bigint a;
		↓
	digits = "0"
```

### Unsigned Integer

```cpp
	bigint::bigint(unsigned int value)
	{
		std::stringstream ss;

		ss << value;
		digits = ss.str();
	}
```

```shell
	42
	↓
	stringstream
	↓
	"42"
```

### String

```cpp
	bigint::bigint(const std::string& value)
	{
		if (value.empty())
			throw std::invalid_argument("invalid input");

		std::string::const_iterator start = value.begin();
		std::string::const_iterator end = value.end();

		while (start != end)
		{
			if (!std::isdigit(*start))
				throw std::invalid_argument("invalid input");
			++start;
		}

		digits = value;
		removeZeros();
	}
```

Flow:

```shell
	value
	│
	├─ empty? ──────→ throw
	│
	└─ check chars
		│
		├─ not digit → throw
		│
		└─ valid
				↓
		digits = value
				↓
		removeZeros()
```

</details>

---

<details>
<summary><b>Copy Constructor & Assignment</b></summary>

### Copy Constructor

```cpp
	bigint::bigint(const bigint& other)
	: digits(other.digits)
	{
	}
```

```shell
	a = "42"
		↓ copy
	b = "42"
```

### Assignment

```cpp
	bigint& bigint::operator=(const bigint& other)
	{
		if (this != &other)
			digits = other.digits;

		return (*this);
	}
```

</details>

---

<details>
<summary><b>Remove Leading Zeros</b></summary>

```cpp
	void bigint::removeZeros()
	{
		std::string::size_type pos = digits.find_first_not_of('0');

		if (pos == std::string::npos)
			digits = "0";
		else
			digits.erase(0, pos);
	}
```

Example:

```shell
	"0001337"
		↓
	find first non-zero
		↓
	pos = 3
		↓
	erase(0, 3)
		↓
	"1337"
```

All zeros:

```shell
	"0000"
	↓
	npos
	↓
	"0"
```

</details>

---

<details>
<summary><b>Addition +</b></summary>

Addition works **right → left**, just like addition on paper.

```cpp
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
```

### Example: `999 + 1`

```shell
	  999
	+   1
	-----
	 1000
```

Internally:

```shell
	9 + 1     = 10 → digit 0, carry 1
	9 + 0 + 1 = 10 → digit 0, carry 1
	9 + 0 + 1 = 10 → digit 0, carry 1
	carry     = 1

	result = "0001"

	reverse
	↓
	"1000"
```

### Important Formula

```cpp
	carry = sum / 10;
	result.push_back((sum % 10) + '0');
```

Example:

```shell
	8 + 7 = 15

	15 / 10 = 1  → carry
	15 % 10 = 5  → digit
```

</details>

---

<details>
<summary><b>Addition +=</b></summary>

```cpp
	bigint& bigint::operator+=(const bigint& other)
	{
		*this = *this + other;

		return (*this);
	}
```

Simply:

```shell
	a += b

	↓

	a = a + b
```

</details>

---

<details>
<summary><b>Simple Test</b></summary>

```cpp
	#include "bigint.hpp"

	int main(void)
	{
		const bigint a(42);
		bigint b(21);

		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
		std::cout << "a + b = " << a + b << std::endl;

		return (0);
	}
```

Expected:

```shell
	a: 42
	b: 21
	a + b = 63
```

</details>

---

<details>
<summary><b>Memorization Map</b></summary>

```shell
	BIGINT
	│
	├── digits
	│
	├── CONSTRUCT
	│   ├── ()         → "0"
	│   ├── (int)      → stringstream
	│   ├── (string)   → validate → removeZeros
	│   └── (bigint)   → copy digits
	│
	├── removeZeros()
	│
	└── ADDITION
		├── start RIGHT
		├── digit1 + digit2 + carry
		├── carry = sum / 10
		├── digit = sum % 10
		├── reverse
		└── += uses +
```

### 🔑 One-line memory

```shell
	digits → construct → remove zeros → add right-to-left
		→ carry → reverse → += uses +
```

</details>