#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>

class bigint
{
// ---------- 1.BLOCK ----------
    private:
        std::string digits;
        void        removeZeros();

    public:
        // --- constr
        bigint();
        bigint(unsigned int value);
        bigint(const std::string& value);

        bigint(const bigint& other);
        bigint& operator=(const bigint& other);

// ---------- 2.BLOCK ----------

        // --- arith
        bigint  operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);

// ---------- 3.BLOCK ----------
        // --- incr
        bigint& operator++(void);
        bigint  operator++(int);

        // --- comp
        bool operator>(const bigint& other) const;
        bool operator<(const bigint& other) const;

        bool operator>=(const bigint& other) const;
        bool operator<=(const bigint& other) const;

        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;

// ---------- 4.BLOCK ----------
        // --- shift
        bigint  operator<<(int i) const;
        bigint  operator>>(int i) const;

        bigint&  operator<<=(int i);
        bigint&  operator>>=(int i);

        bigint&  operator<<=(const bigint& other);
        bigint&  operator>>=(const bigint& other);

        // --- getter
        const std::string& getDigits(void) const;
};

// ---
std::ostream&    operator<<(std::ostream& os, const bigint& n);

#endif