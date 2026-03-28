#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::_;
using ::testing::Mock;

// Assuming GooString is a class
class GooString {
public:
    explicit GooString(const std::string &str) : str_(str) {}
    const std::string &getString() const { return str_; }

private:
    std::string str_;
};

// Mock class to simulate the external collaborator
class MockEntryGooStringComparer {
public:
    MOCK_METHOD(const std::string &, get, (const GooString *string), (const));
    MOCK_METHOD(const std::string &, get, (const GooString &entry), (const));
    MOCK_METHOD(bool, operator(), (const GooString &lhs, const GooString &rhs), ());
};

// Test Fixture for EntryGooStringComparer
class EntryGooStringComparerTest : public ::testing::Test {
protected:
    MockEntryGooStringComparer mockComparer;
};

// Normal Operation Test
TEST_F(EntryGooStringComparerTest, Operator_ComparerComparesStrings_1898) {
    GooString gooString1("Apple");
    GooString gooString2("Banana");

    EXPECT_CALL(mockComparer, get(gooString1))
        .WillOnce(testing::ReturnRef(gooString1.getString()));
    EXPECT_CALL(mockComparer, get(gooString2))
        .WillOnce(testing::ReturnRef(gooString2.getString()));

    EXPECT_CALL(mockComparer, operator()(gooString1, gooString2))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(mockComparer.operator()(gooString1, gooString2));
}

// Boundary Condition Test - Empty Strings
TEST_F(EntryGooStringComparerTest, Operator_ComparerComparesEmptyStrings_1899) {
    GooString gooString1("");
    GooString gooString2("");

    EXPECT_CALL(mockComparer, get(gooString1))
        .WillOnce(testing::ReturnRef(gooString1.getString()));
    EXPECT_CALL(mockComparer, get(gooString2))
        .WillOnce(testing::ReturnRef(gooString2.getString()));

    EXPECT_CALL(mockComparer, operator()(gooString1, gooString2))
        .WillOnce(testing::Return(false));

    EXPECT_FALSE(mockComparer.operator()(gooString1, gooString2));
}

// Boundary Condition Test - Compare Empty String with Non-empty String
TEST_F(EntryGooStringComparerTest, Operator_ComparerComparesEmptyAndNonEmptyStrings_1900) {
    GooString gooString1("");
    GooString gooString2("Banana");

    EXPECT_CALL(mockComparer, get(gooString1))
        .WillOnce(testing::ReturnRef(gooString1.getString()));
    EXPECT_CALL(mockComparer, get(gooString2))
        .WillOnce(testing::ReturnRef(gooString2.getString()));

    EXPECT_CALL(mockComparer, operator()(gooString1, gooString2))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(mockComparer.operator()(gooString1, gooString2));
}

// Exceptional Case Test - Null Pointer Handling
TEST_F(EntryGooStringComparerTest, Operator_ComparerHandlesNullPointer_1901) {
    GooString gooString("Test");

    // Expect the get function to be called with nullptr
    EXPECT_CALL(mockComparer, get(nullptr))
        .WillOnce(testing::ReturnRef(gooString.getString()));

    EXPECT_CALL(mockComparer, operator()(gooString, nullptr))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(mockComparer.operator()(gooString, nullptr));
}

// Verification of External Interaction - Verifying Mock Call Parameters
TEST_F(EntryGooStringComparerTest, Operator_VerifyMockCallParameters_1902) {
    GooString gooString1("Orange");
    GooString gooString2("Apple");

    EXPECT_CALL(mockComparer, get(gooString1))
        .WillOnce(testing::ReturnRef(gooString1.getString()));
    EXPECT_CALL(mockComparer, get(gooString2))
        .WillOnce(testing::ReturnRef(gooString2.getString()));

    EXPECT_CALL(mockComparer, operator()(gooString1, gooString2))
        .WillOnce(testing::Return(true));

    mockComparer.operator()(gooString1, gooString2);
    
    // Verify that the mock method was called with correct parameters
    Mock::VerifyAndClearExpectations(&mockComparer);
}