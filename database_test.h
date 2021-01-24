#pragma once
#include "test_runner.h"
#include "database.h"
#include "condition_parser.h"

int DoRemove(Database& db, const string& str);
string DoFind(Database& db, const string& str);

void TestDbAdd();
void TestDbFind();
void TestDbLast();
void TestDbRemoveIf();
void TestInsertionOrder();
void TestDatabase();
void TestDateComparisonNode();
void TestEventComparisonNode();
void TestEmptyNode();
void TestsMyCustom();
//void TestLogicalOperationNode();