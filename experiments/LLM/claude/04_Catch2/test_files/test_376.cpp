#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test fixture
class BoundValueRefTest_376 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Tests for BoundValueRef<int> ====================

TEST_F(BoundValueRefTest_376, SetValueInt_ValidPositiveNumber_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("42");
    EXPECT_EQ(value, 42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_ValidNegativeNumber_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("-10");
    EXPECT_EQ(value, -10);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_Zero_376) {
    int value = 99;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("0");
    EXPECT_EQ(value, 0);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_InvalidString_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("not_a_number");
    // Conversion should fail
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_EmptyString_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("");
    // Empty string should fail conversion to int
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_FloatString_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue("3.14");
    // Float string to int may fail or truncate depending on implementation
    // We just check it doesn't crash - behavior is implementation-defined
}

// ==================== Tests for BoundValueRef<double> ====================

TEST_F(BoundValueRefTest_376, SetValueDouble_ValidNumber_376) {
    double value = 0.0;
    BoundValueRef<double> ref(value);
    auto result = ref.setValue("3.14");
    EXPECT_DOUBLE_EQ(value, 3.14);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueDouble_IntegerString_376) {
    double value = 0.0;
    BoundValueRef<double> ref(value);
    auto result = ref.setValue("42");
    EXPECT_DOUBLE_EQ(value, 42.0);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueDouble_NegativeNumber_376) {
    double value = 0.0;
    BoundValueRef<double> ref(value);
    auto result = ref.setValue("-2.5");
    EXPECT_DOUBLE_EQ(value, -2.5);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueDouble_InvalidString_376) {
    double value = 0.0;
    BoundValueRef<double> ref(value);
    auto result = ref.setValue("abc");
    EXPECT_FALSE(static_cast<bool>(result));
}

// ==================== Tests for BoundValueRef<std::string> ====================

TEST_F(BoundValueRefTest_376, SetValueString_NormalString_376) {
    std::string value;
    BoundValueRef<std::string> ref(value);
    auto result = ref.setValue("hello");
    EXPECT_EQ(value, "hello");
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueString_EmptyString_376) {
    std::string value = "initial";
    BoundValueRef<std::string> ref(value);
    auto result = ref.setValue("");
    EXPECT_EQ(value, "");
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueString_StringWithSpaces_376) {
    std::string value;
    BoundValueRef<std::string> ref(value);
    auto result = ref.setValue("hello world");
    EXPECT_EQ(value, "hello world");
    EXPECT_TRUE(static_cast<bool>(result));
}

// ==================== Tests for BoundValueRef<bool> ====================

TEST_F(BoundValueRefTest_376, SetValueBool_TrueString_376) {
    bool value = false;
    BoundValueRef<bool> ref(value);
    auto result = ref.setValue("true");
    EXPECT_TRUE(value);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueBool_FalseString_376) {
    bool value = true;
    BoundValueRef<bool> ref(value);
    auto result = ref.setValue("false");
    EXPECT_FALSE(value);
    EXPECT_TRUE(static_cast<bool>(result));
}

// ==================== Tests for BoundValueRef<unsigned int> ====================

TEST_F(BoundValueRefTest_376, SetValueUnsignedInt_ValidNumber_376) {
    unsigned int value = 0;
    BoundValueRef<unsigned int> ref(value);
    auto result = ref.setValue("100");
    EXPECT_EQ(value, 100u);
    EXPECT_TRUE(static_cast<bool>(result));
}

// ==================== Tests for multiple setValue calls ====================

TEST_F(BoundValueRefTest_376, SetValueInt_MultipleCalls_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    
    ref.setValue("10");
    EXPECT_EQ(value, 10);
    
    ref.setValue("20");
    EXPECT_EQ(value, 20);
    
    ref.setValue("30");
    EXPECT_EQ(value, 30);
}

// ==================== Tests for BoundValueRef with vector ====================

TEST_F(BoundValueRefTest_376, SetValueVectorInt_AddElements_376) {
    std::vector<int> values;
    BoundValueRef<int> ref(values);
    
    auto result1 = ref.setValue("1");
    EXPECT_TRUE(static_cast<bool>(result1));
    
    auto result2 = ref.setValue("2");
    EXPECT_TRUE(static_cast<bool>(result2));
    
    auto result3 = ref.setValue("3");
    EXPECT_TRUE(static_cast<bool>(result3));
    
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

TEST_F(BoundValueRefTest_376, IsContainer_VectorRef_ReturnsTrue_376) {
    std::vector<int> values;
    BoundValueRef<int> ref(values);
    EXPECT_TRUE(ref.isContainer());
}

TEST_F(BoundValueRefTest_376, IsContainer_ScalarRef_ReturnsFalse_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    EXPECT_FALSE(ref.isContainer());
}

// ==================== Boundary tests for int ====================

TEST_F(BoundValueRefTest_376, SetValueInt_MaxInt_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue(std::to_string(std::numeric_limits<int>::max()));
    EXPECT_EQ(value, std::numeric_limits<int>::max());
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueInt_MinInt_376) {
    int value = 0;
    BoundValueRef<int> ref(value);
    auto result = ref.setValue(std::to_string(std::numeric_limits<int>::min()));
    EXPECT_EQ(value, std::numeric_limits<int>::min());
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BoundValueRefTest_376, SetValueVectorString_AddElements_376) {
    std::vector<std::string> values;
    BoundValueRef<std::string> ref(values);
    
    ref.setValue("hello");
    ref.setValue("world");
    
    ASSERT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], "hello");
    EXPECT_EQ(values[1], "world");
}
