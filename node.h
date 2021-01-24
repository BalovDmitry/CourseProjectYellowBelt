#pragma once
#include "date.h"

#include <tuple>

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode();
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, const string& event);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Comparison cmp_;
	string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(
		LogicalOperation logical_operation,
		shared_ptr<Node> left,
		shared_ptr<Node> right);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation logical_operation_;
	shared_ptr<Node> left_, right_;
};