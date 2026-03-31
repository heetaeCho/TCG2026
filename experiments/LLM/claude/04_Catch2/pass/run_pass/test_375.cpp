#include <catch2/internal/catch_clara.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <string>
#include <optional>

using namespace Catch::Clara::Detail;

class ConvertIntoOptionalTest_375 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test converting a valid integer string into optional<int>
TEST_F(ConvertIntoOptionalTest_375, ValidIntConversion_375) {
    std::string source = "42";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), 42);
}

// Test converting a negative integer string into optional<int>
TEST_F(ConvertIntoOptionalTest_375, NegativeIntConversion_375) {
    std::string source = "-17";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), -17);
}

// Test converting zero string into optional<int>
TEST_F(ConvertIntoOptionalTest_375, ZeroIntConversion_375) {
    std::string source = "0";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), 0);
}

// Test converting an invalid string into optional<int> should fail
TEST_F(ConvertIntoOptionalTest_375, InvalidIntConversion_375) {
    std::string source = "not_a_number";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(target.has_value());
}

// Test converting a valid float string into optional<double>
TEST_F(ConvertIntoOptionalTest_375, ValidDoubleConversion_375) {
    std::string source = "3.14";
    std::optional<double> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_NEAR(target.value(), 3.14, 0.001);
}

// Test converting an invalid string into optional<double>
TEST_F(ConvertIntoOptionalTest_375, InvalidDoubleConversion_375) {
    std::string source = "abc";
    std::optional<double> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(target.has_value());
}

// Test converting a valid string into optional<std::string>
TEST_F(ConvertIntoOptionalTest_375, ValidStringConversion_375) {
    std::string source = "hello";
    std::optional<std::string> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), "hello");
}

// Test converting an empty string into optional<std::string>
TEST_F(ConvertIntoOptionalTest_375, EmptyStringConversion_375) {
    std::string source = "";
    std::optional<std::string> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), "");
}

// Test converting "true" into optional<bool>
TEST_F(ConvertIntoOptionalTest_375, ValidBoolTrueConversion_375) {
    std::string source = "true";
    std::optional<bool> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), true);
}

// Test converting "false" into optional<bool>
TEST_F(ConvertIntoOptionalTest_375, ValidBoolFalseConversion_375) {
    std::string source = "false";
    std::optional<bool> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), false);
}

// Test that target remains unchanged on failed conversion
TEST_F(ConvertIntoOptionalTest_375, TargetUnchangedOnFailure_375) {
    std::string source = "invalid";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(target.has_value());
}

// Test converting a large integer string into optional<unsigned int>
TEST_F(ConvertIntoOptionalTest_375, ValidUnsignedIntConversion_375) {
    std::string source = "4294967295";
    std::optional<unsigned int> target;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), 4294967295u);
}

// Test converting a string with whitespace into optional<int>
TEST_F(ConvertIntoOptionalTest_375, StringWithTrailingCharsIntConversion_375) {
    std::string source = "42abc";
    std::optional<int> target;
    
    auto result = convertInto(source, target);
    
    // The behavior depends on the underlying convertInto implementation
    // We just check consistency: if result is ok, target should have value
    if (result) {
        EXPECT_TRUE(target.has_value());
    } else {
        EXPECT_FALSE(target.has_value());
    }
}

// Test that a previously-set optional gets overwritten on success
TEST_F(ConvertIntoOptionalTest_375, OverwriteExistingOptionalValue_375) {
    std::string source = "100";
    std::optional<int> target = 50;
    
    auto result = convertInto(source, target);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), 100);
}

// Test that a previously-set optional remains on failure
TEST_F(ConvertIntoOptionalTest_375, ExistingOptionalUnchangedOnFailure_375) {
    std::string source = "not_a_number";
    std::optional<int> target = 50;
    
    auto result = convertInto(source, target);
    
    EXPECT_FALSE(result);
    // On failure, the target should not be modified
    EXPECT_TRUE(target.has_value());
    EXPECT_EQ(target.value(), 50);
}
