#include "date.h"

Date ParseDate(istream& is) {
	int year;
	uint16_t month;
	uint16_t day;
	bool ok = true;

	ok = ok && (is >> year);
	ok = ok && (is.peek() == '-');
	is.ignore(1);

	ok = ok && (is >> month);
	ok = ok && (is.peek() == '-');
	is.ignore(1);

	ok = ok && (is >> day);
	if (ok) {
		return Date(year, month, day);
	}
	else {
		throw invalid_argument("Invalid Date");
	}
}

bool operator<(const Date& lhs, const Date& rhs) {
	return tie(lhs.year_, lhs.month_, lhs.day_) < tie(rhs.year_, rhs.month_, rhs.day_);
}

ostream& operator<<(ostream& output, const Date& date) {
	output << setw(4) << setfill('0') << date.year_ << "-"
		<< setw(2) << setfill('0') << date.month_ << "-"
		<< setw(2) << setfill('0') << date.day_;
	return output;
}