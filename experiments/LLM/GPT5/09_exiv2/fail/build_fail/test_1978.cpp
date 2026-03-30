#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ctime>

// Assuming the existence of IsLeapYear function for this test
extern bool IsLeapYear(int year);

// Mock function for IsLeapYear
class MockIsLeapYear {
public:
    MOCK_METHOD(bool, IsLeapYear, (int year), ());
};

// Test fixture class
class XMPUtilsTest_1978 : public ::testing::Test {
protected:
    MockIsLeapYear mockLeapYearChecker;
    
    XMPUtilsTest_1978() {
        // Set up default mock behavior here if needed
    }
    
    void SetUp() override {
        // Additional setup if necessary
    }

    void TearDown() override {
        // Clean up any resources if necessary
    }
};

// Normal operation tests
TEST_F(XMPUtilsTest_1978, DaysInMonth_NormalCases_1978) {
    // Test normal days in each month (non-leap year).
    EXPECT_EQ(DaysInMonth(2021, 1), 31); // January
    EXPECT_EQ(DaysInMonth(2021, 4), 30); // April
    EXPECT_EQ(DaysInMonth(2021, 12), 31); // December
}

// Boundary condition tests
TEST_F(XMPUtilsTest_1978, DaysInMonth_FebruaryBoundary_1978) {
    // Test February days in leap and non-leap years.
    EXPECT_CALL(mockLeapYearChecker, IsLeapYear(2020)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockLeapYearChecker, IsLeapYear(2021)).WillOnce(testing::Return(false));
    
    // February 2020 (Leap year) should have 29 days
    EXPECT_EQ(DaysInMonth(2020, 2), 29);
    // February 2021 (Non-Leap year) should have 28 days
    EXPECT_EQ(DaysInMonth(2021, 2), 28);
}

// Exceptional case tests
TEST_F(XMPUtilsTest_1978, DaysInMonth_InvalidMonth_1978) {
    // Test invalid month (greater than 12 or less than 1)
    EXPECT_EQ(DaysInMonth(2021, 0), -1); // Invalid month 0
    EXPECT_EQ(DaysInMonth(2021, 13), -1); // Invalid month 13
}

// Boundary condition: Testing for edge case months (December and January)
TEST_F(XMPUtilsTest_1978, DaysInMonth_EdgeCaseMonths_1978) {
    // Testing for December and January
    EXPECT_EQ(DaysInMonth(2021, 12), 31); // December (31 days)
    EXPECT_EQ(DaysInMonth(2022, 1), 31);  // January (31 days)
}