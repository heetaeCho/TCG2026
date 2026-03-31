#include <gtest/gtest.h>
#include <cmath>

// Declaration of the function under test
double GetLoadAverage();

class GetLoadAverageTest_157 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that GetLoadAverage returns a finite number
TEST_F(GetLoadAverageTest_157, ReturnsFiniteValue_157) {
    double result = GetLoadAverage();
    EXPECT_TRUE(std::isfinite(result));
}

// Test that GetLoadAverage returns a non-negative value or negative zero on success
// On a valid system, load average should be >= 0. If getloadavg fails, it returns -0.0.
TEST_F(GetLoadAverageTest_157, ReturnsNonNegativeOrNegativeZero_157) {
    double result = GetLoadAverage();
    // Either the result is >= 0 (valid load average) or it's -0.0 (failure case)
    bool is_valid = (result >= 0.0) || (result == 0.0 && std::signbit(result));
    EXPECT_TRUE(is_valid) << "GetLoadAverage returned unexpected value: " << result;
}

// Test that GetLoadAverage returns a reasonable load average value
// On most systems, load average should be between 0 and some large number (e.g., 10000)
TEST_F(GetLoadAverageTest_157, ReturnsReasonableValue_157) {
    double result = GetLoadAverage();
    if (!std::signbit(result) || result != 0.0) {
        // If it's not -0.0 (i.e., getloadavg succeeded), check reasonable range
        EXPECT_GE(result, 0.0);
        EXPECT_LT(result, 100000.0) << "Load average seems unreasonably high";
    }
}

// Test that calling GetLoadAverage multiple times is consistent (doesn't crash, returns valid)
TEST_F(GetLoadAverageTest_157, MultipleCallsAreStable_157) {
    double result1 = GetLoadAverage();
    double result2 = GetLoadAverage();
    
    // Both should be finite
    EXPECT_TRUE(std::isfinite(result1));
    EXPECT_TRUE(std::isfinite(result2));
    
    // Both should be non-negative or -0.0
    bool valid1 = (result1 >= 0.0) || (result1 == 0.0 && std::signbit(result1));
    bool valid2 = (result2 >= 0.0) || (result2 == 0.0 && std::signbit(result2));
    EXPECT_TRUE(valid1);
    EXPECT_TRUE(valid2);
}

// Test that the result is not NaN
TEST_F(GetLoadAverageTest_157, ResultIsNotNaN_157) {
    double result = GetLoadAverage();
    EXPECT_FALSE(std::isnan(result));
}

// Test that the result is not positive infinity
TEST_F(GetLoadAverageTest_157, ResultIsNotInfinity_157) {
    double result = GetLoadAverage();
    EXPECT_FALSE(std::isinf(result));
}

// Test that on a running system, load average is typically > 0
// (This test is informational - a system could theoretically have 0 load)
TEST_F(GetLoadAverageTest_157, TypicallyPositiveOnRunningSystem_157) {
    double result = GetLoadAverage();
    // We expect at least some load on a system running tests
    // But we only warn, not fail, since 0.0 load is theoretically possible
    if (result == 0.0 && !std::signbit(result)) {
        // Load is exactly 0, which is unusual but valid
        SUCCEED() << "Load average is exactly 0.0 - unusual but valid";
    } else if (std::signbit(result) && result == 0.0) {
        // -0.0 means getloadavg failed
        SUCCEED() << "getloadavg failed (returned -0.0)";
    } else {
        EXPECT_GT(result, 0.0);
    }
}
