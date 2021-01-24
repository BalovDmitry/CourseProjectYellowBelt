#include "database.h"

void Database::Add(const Date& date, const string& event) {
	auto it_success = date_to_event_set_[date].insert(event);
	if (it_success.second == true) {
		date_to_event_[date].push_back(event);
	}
}

void Database::Print(ostream& output) const {
	for (const auto& record : date_to_event_) {
		output << record;
	}
}

pair<Date, string> Database::Last(const Date& date) const {
	auto last_record_it = date_to_event_.upper_bound(date);
	if (last_record_it == date_to_event_.begin()) {
		throw invalid_argument("");
	}
	auto last_record = prev(last_record_it);
	return { last_record->first, last_record->second.back() };
}

vector<pair<Date, string>> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {
	vector<pair<Date, string>> result;
	for (const auto& [date, events] : date_to_event_) {
		Date date_lambda = date;
		auto current = date_to_event_.at(date).begin();

		while (true) {
			auto it = find_if(
				current,
				date_to_event_.at(date).end(),
				[&](const string& event) {return predicate(date_lambda, event); }
			);
			if (it == date_to_event_.at(date).end()) {
				break;
			}
			result.push_back({ date_lambda, *it });
			current = it + 1;
		}
	}
	return result;
}

//С помощью итераторов

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
	int count = 0;
	for (auto it = date_to_event_.begin(); it != date_to_event_.end(); ) {
		auto it_remove = stable_partition(
			date_to_event_.at(it->first).begin(),
			date_to_event_.at(it->first).end(),
			[&](const string& event) {
				return !predicate(it->first, event); });
		for (auto it_value = it_remove; it_value != date_to_event_.at(it->first).end(); ++it_value) {
			date_to_event_set_.at(it->first).erase(*it_value);
			count++;
		}
		date_to_event_.at(it->first).erase(it_remove, date_to_event_.at(it->first).end());
		it = next(it);
		if (date_to_event_.at(prev(it)->first).empty()) {
			date_to_event_set_.erase(prev(it)->first);
			date_to_event_.erase(prev(it)->first);
		}
	}
	return count;
}


/*
int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
	int count = 0;	
	for (const auto& [date, events] : date_to_event_) {
		Date date_lambda = date;
		auto it_remove = stable_partition(
			date_to_event_.at(date).begin(),
			date_to_event_.at(date).end(),
			[&](const string& event) {
				return !predicate(date_lambda, event); });
		for (auto it_value = it_remove; it_value != date_to_event_.at(date).end(); ++it_value) {
			date_to_event_set_.at(date).erase(*it_value);
			count++;
		}
		date_to_event_.at(date).erase(it_remove, date_to_event_.at(date).end());
		if (date_to_event_.at(date).empty()) {
			date_to_event_set_.erase(date);
		}
	}
	
	while (true) {
		auto it_empty = find_if(
			date_to_event_.begin(),
			date_to_event_.end(),
			[](pair<const Date, vector<string>>& record) {return record.second.empty(); });
		if (it_empty == date_to_event_.end()) {
			break;
		}
		date_to_event_.erase(it_empty);
	}
	return count;
}
*/
/*
int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
	int count = 0;
	// Находим итераторы на все события в оставшмихся датах
	for (const auto& [date, events] : date_to_event_) {
		Date date_lambda = date;
		while (true) {
			auto it_event = find_if(
				date_to_event_.at(date).begin(),
				date_to_event_.at(date).end(),
				[&](const string& event) {
					return predicate(date_lambda, event);
				});
			if (it_event == date_to_event_.at(date).end()) {
				break;
			}
			auto it_event_value = *it_event;
			date_to_event_.at(date).erase(it_event);
			date_to_event_set_.at(date).erase(it_event_value);
			count++;
		}
	}

	while (true) {
		auto it_empty = find_if(
			date_to_event_.begin(),
			date_to_event_.end(),
			[](pair<const Date, deque<string>>& record) {return record.second.empty(); });
		if (it_empty == date_to_event_.end()) {
			break;
		}
		Date it_empty_value = it_empty->first;
		date_to_event_.erase(it_empty);
		date_to_event_set_.erase(it_empty_value);
	}
	return count;
}
*/
// Для вывода Last
ostream& operator<<(ostream& output, const pair<Date, string>& record) {
	output << record.first << " " << record.second;
	return output;
}

// Для вывода Print
ostream& operator<<(ostream& output, const pair <Date, vector<string>>& record) {
	for (const auto& event : record.second) {
		output << record.first << " " << event << endl;
	}
	return output;
}