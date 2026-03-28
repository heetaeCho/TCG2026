#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp"

// Mocking external dependencies if necessary (none here as of now)

namespace Exiv2 {

class ValueTypeTest_154 : public ::testing::Test {
protected:
    void SetUp() override {
        // Any setup if needed
    }

    void TearDown() override {
        // Any cleanup if needed
    }
};

// Normal Operation Test Case: Testing the toString function
TEST_F(ValueTypeTest_154, toString_NormalOperation_154) {
    ValueType<int> valueType(42, TypeId::Int);
    std::string result = valueType.toString(0);
    EXPECT_EQ(result, "42");
}

// Boundary Condition Test Case: Testing toString with an out-of-bounds index
TEST_F(ValueTypeTest_154, toString_BoundaryCondition_154) {
    ValueType<int> valueType(42, TypeId::Int);
    EXPECT_THROW(valueType.toString(1), std::out_of_range);
}

// Normal Operation Test Case: Testing toInt64 for valid conversion
TEST_F(ValueTypeTest_154, toInt64_NormalOperation_154) {
    ValueType<int> valueType(42, TypeId::Int);
    EXPECT_EQ(valueType.toInt64(0), 42);
}

// Boundary Condition Test Case: Testing toInt64 for an out-of-bounds index
TEST_F(ValueTypeTest_154, toInt64_BoundaryCondition_154) {
    ValueType<int> valueType(42, TypeId::Int);
    EXPECT_THROW(valueType.toInt64(1), std::out_of_range);
}

// Normal Operation Test Case: Testing toFloat for valid conversion
TEST_F(ValueTypeTest_154, toFloat_NormalOperation_154) {
    ValueType<double> valueType(42.0, TypeId::Double);
    EXPECT_FLOAT_EQ(valueType.toFloat(0), 42.0f);
}

// Exceptional Case: Testing toFloat with an out-of-bounds index
TEST_F(ValueTypeTest_154, toFloat_ExceptionalCase_154) {
    ValueType<double> valueType(42.0, TypeId::Double);
    EXPECT_THROW(valueType.toFloat(1), std::out_of_range);
}

// Verifying external interaction: Verifying if `count` method works as expected
TEST_F(ValueTypeTest_154, count_InteractionVerification_154) {
    ValueType<int> valueType(42, TypeId::Int);
    EXPECT_EQ(valueType.count(), 1);  // Assuming count returns the number of values in `value_`
}

// Verifying external interaction: Verifying if `write` function writes correctly to ostream
TEST_F(ValueTypeTest_154, write_InteractionVerification_154) {
    ValueType<int> valueType(42, TypeId::Int);
    std::ostringstream os;
    valueType.write(os);
    EXPECT_EQ(os.str(), "42");  // Assuming write writes the string representation of the value
}

// Exceptional Case: Verifying behavior when an invalid `ValueType` is created (invalid type or malformed data)
TEST_F(ValueTypeTest_154, InvalidValueType_ExceptionalCase_154) {
    EXPECT_THROW(ValueType<int> valueType(nullptr, 0, ByteOrder::BigEndian, TypeId::Unknown), std::invalid_argument);
}

// Normal Operation: Testing the size function
TEST_F(ValueTypeTest_154, size_NormalOperation_154) {
    ValueType<int> valueType(42, TypeId::Int);
    EXPECT_EQ(valueType.size(), 1);  // Assuming size returns 1 as there's one item in value_
}

} // namespace Exiv2