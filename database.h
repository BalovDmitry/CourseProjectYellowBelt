#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <functional>

#include "node.h"
#include "date.h"

using namespace std;

class Database {
private:
	map<Date, set<string>> date_to_event_set_;
	map<Date, vector<string>> date_to_event_;
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& output) const;
	pair<Date, string> Last(const Date& date) const;
	vector<pair<Date, string>> FindIf(function<bool(const Date&, const string&)> predicate) const;
	int RemoveIf(function<bool(const Date&, const string&)> predicate);
};

ostream& operator<<(ostream& output, const pair<Date, vector<string>>& record);
ostream& operator<<(ostream& output, const pair <Date, string>& last_record);