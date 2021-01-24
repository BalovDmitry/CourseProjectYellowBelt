#pragma once

#include <cstdint>
#include <iostream>
#include <tuple>
#include <iomanip>
#include <memory>
#include <vector>
using namespace std;

struct Date {
	Date() : year_(0), month_(0), day_(0) {};
	Date(int Year, uint16_t Month, uint16_t Day)
		: year_(Year), month_(Month), day_(Day) {};

	int year_;
	uint16_t month_;
	uint16_t day_;
};

Date ParseDate(istream& is);
bool operator<(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& output, const Date& date);

