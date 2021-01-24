#include "node.h"

EmptyNode::EmptyNode() {};
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) {
	cmp_ = cmp;
	date_ = date;
}
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	tuple tie_date = tie(date.year_, date.month_, date.day_);
	tuple tie_date_ = tie(date_.year_, date_.month_, date_.day_);
	if (cmp_ == Comparison::Equal) {
		return tie_date == tie_date_;
	}
	else if (cmp_ == Comparison::Greater) {
		return tie_date > tie_date_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual) {
		return tie_date >= tie_date_;
	}
	else if (cmp_ == Comparison::Less) {
		return tie_date < tie_date_;
	}
	else if (cmp_ == Comparison::LessOrEqual) {
		return tie_date <= tie_date_;
	}
	else if (cmp_ == Comparison::NotEqual) {
		return tie_date != tie_date_;
	}
	else {
		throw logic_error("Unknown operand");
	}
}


EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) {
	cmp_ = cmp;
	event_ = event;
}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (cmp_ == Comparison::Equal) {
		return event == event_;
	}
	else if (cmp_ == Comparison::Greater) {
		return event > event_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual) {
		return event >= event_;
	}
	else if (cmp_ == Comparison::Less) {
		return event < event_;
	}
	else if (cmp_ == Comparison::LessOrEqual) {
		return event <= event_;
	}
	else if (cmp_ == Comparison::NotEqual) {
		return event != event_;
	}
	else {
		throw logic_error("Unknown operand");
	}
}

LogicalOperationNode::LogicalOperationNode(
	LogicalOperation logical_operation,
	shared_ptr<Node> left,
	shared_ptr<Node> right) {
	logical_operation_ = logical_operation;
	left_ = left;
	right_ = right;
}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (logical_operation_ == LogicalOperation::And) {
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}
	else if (logical_operation_ == LogicalOperation::Or) {
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	}
	else {
		throw logic_error("Unknown operation");
	}
}