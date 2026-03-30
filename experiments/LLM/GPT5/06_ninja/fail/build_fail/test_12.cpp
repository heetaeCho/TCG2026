#include <gtest/gtest.h>
#include "explanations.h"

class ExplanationsTest_12 : public ::testing::Test {
protected:
    Explanations ex_;
};

/***********************************************
 * TEST 1 — Normal: Single Record call stores 1 message
 ***********************************************/
TEST_F(ExplanationsTest_12, SingleRecordStoresMessage_12) {
    int obj = 123;
    ex_.Record(&obj, "hello %d", 42);

    std::vector<std::string> out;
    ex_.LookupAndAppend(&obj, &out);

    ASSERT_EQ(out.size(), 1u);
}

/***********************************************
 * TEST 2 — Multiple Record calls accumulate messages
 ***********************************************/
TEST_F(ExplanationsTest_12, MultipleRecordAccumulates_12) {
    int obj = 123;

    ex_.Record(&obj, "first");
    ex_.Record(&obj, "second %d", 99);

    std::vector<std::string> out;
    ex_.LookupAndAppend(&obj, &out);

    ASSERT_EQ(out.size(), 2u);
}

/***********************************************
 * TEST 3 — Different items remain isolated
 ***********************************************/
TEST_F(ExplanationsTest_12, DifferentItemsDoNotInterfere_12) {
    int objA = 1;
    int objB = 2;

    ex_.Record(&objA, "msgA1");
    ex_.Record(&objB, "msgB1");
    ex_.Record(&objA, "msgA2");

    std::vector<std::string> outA;
    std::vector<std::string> outB;

    ex_.LookupAndAppend(&objA, &outA);
    ex_.LookupAndAppend(&objB, &outB);

    ASSERT_EQ(outA.size(), 2u);
    ASSERT_EQ(outB.size(), 1u);
}

/***********************************************
 * TEST 4 — Lookup with no messages returns empty output
 ***********************************************/
TEST_F(ExplanationsTest_12, LookupEmptyIsEmpty_12) {
    int obj = 123;

    std::vector<std::string> out;
    ex_.LookupAndAppend(&obj, &out);

    ASSERT_TRUE(out.empty());
}

/***********************************************
 * TEST 5 — Recording with nullptr item is allowed
 ***********************************************/
TEST_F(ExplanationsTest_12, RecordWithNullptrKey_12) {
    ex_.Record(nullptr, "null message");

    std::vector<std::string> out;
    ex_.LookupAndAppend(nullptr, &out);

    ASSERT_EQ(out.size(), 1u);
}

/***********************************************
 * TEST 6 — RecordArgs is also usable via interface
 ***********************************************/
TEST_F(ExplanationsTest_12, RecordArgsStoresMessage_12) {
    int obj = 55;

    va_list args;
    va_start(args, obj);  // Not actually reading variadic arguments
    ex_.RecordArgs(&obj, "format", args);
    va_end(args);

    std::vector<std::string> out;
    ex_.LookupAndAppend(&obj, &out);

    ASSERT_EQ(out.size(), 1u);
}
