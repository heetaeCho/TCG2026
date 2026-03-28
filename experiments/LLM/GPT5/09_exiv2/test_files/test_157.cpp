#include <gtest/gtest.h>
#include "exiv2/value.hpp"

namespace Exiv2 {

class ValueTypeDoubleTest_157 : public ::testing::Test {
protected:
    // Test fixture can be extended if necessary, but not needed for simple tests of toInt64
};

TEST_F(ValueTypeDoubleTest_157, toInt64_NormalOperation_157) {
    // Test a normal double value conversion to int64_t
    ValueType<double> value(3.14, TypeId(100)); // Example initialization
    int64_t result = value.toInt64(0); // Call toInt64 on normal value

    // Expected behavior: the result should be the integer part of 3.14
    EXPECT_EQ(result, 3) << "Expected 3 for the conversion of 3.14 to int64_t";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_ZeroValue_157) {
    // Test conversion of zero to int64_t
    ValueType<double> value(0.0, TypeId(100)); // Example initialization
    int64_t result = value.toInt64(0); // Call toInt64 on zero value

    // Expected behavior: the result should be 0
    EXPECT_EQ(result, 0) << "Expected 0 for the conversion of 0.0 to int64_t";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_NegativeValue_157) {
    // Test conversion of a negative double value
    ValueType<double> value(-3.14, TypeId(100)); // Example initialization
    int64_t result = value.toInt64(0); // Call toInt64 on negative value

    // Expected behavior: the result should be the integer part of -3.14
    EXPECT_EQ(result, -3) << "Expected -3 for the conversion of -3.14 to int64_t";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_BoundaryCondition_Max_157) {
    // Test boundary case for maximum double value
    ValueType<double> value(std::numeric_limits<double>::max(), TypeId(100)); // Maximum double
    int64_t result = value.toInt64(0); // Call toInt64 on max double value

    // Expected behavior: the result should be the maximum int64_t value
    EXPECT_EQ(result, std::numeric_limits<int64_t>::max()) << "Expected max int64_t for the conversion of max double";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_BoundaryCondition_Min_157) {
    // Test boundary case for minimum double value
    ValueType<double> value(std::numeric_limits<double>::min(), TypeId(100)); // Minimum positive normal double
    int64_t result = value.toInt64(0); // Call toInt64 on min double value

    // Expected behavior: the result should be 0 (since this value is very small)
    EXPECT_EQ(result, 0) << "Expected 0 for the conversion of min double to int64_t";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_Nan_157) {
    // Test conversion of NaN value
    ValueType<double> value(std::numeric_limits<double>::quiet_NaN(), TypeId(100)); // NaN value
    int64_t result = value.toInt64(0); // Call toInt64 on NaN

    // Expected behavior: since NaN is not a number, the result should not be a valid int64_t value
    EXPECT_EQ(result, 0) << "Expected 0 for the conversion of NaN to int64_t";
}

TEST_F(ValueTypeDoubleTest_157, toInt64_Infinity_157) {
    // Test conversion of positive infinity
    ValueType<double> value(std::numeric_limits<double>::infinity(), TypeId(100)); // Positive infinity
    int64_t result = value.toInt64(0); // Call toInt64 on infinity

    // Expected behavior: the result should be the maximum int64_t value
    EXPECT_EQ(result, std::numeric_limits<int64_t>::max()) << "Expected max int64_t for the conversion of infinity to int64_t";
}

} // namespace Exiv2