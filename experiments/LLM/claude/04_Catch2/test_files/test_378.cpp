#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test fixture for BoundValueRef with vector<T> specialization
class BoundValueRefVectorTest_378 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that setValue successfully parses and appends an integer to a vector
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsIntToVector_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    auto result = ref.setValue("42");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], 42);
}

// Test that multiple setValue calls append multiple values
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsMultipleInts_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    ref.setValue("1");
    ref.setValue("2");
    ref.setValue("3");
    
    ASSERT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// Test that setValue with invalid input does not modify the vector
TEST_F(BoundValueRefVectorTest_378, SetValueWithInvalidInputDoesNotAppend_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    auto result = ref.setValue("not_a_number");
    
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(vec.size(), 0u);
}

// Test that setValue works with string vectors
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsStringToVector_378) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    
    auto result = ref.setValue("hello");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], "hello");
}

// Test that setValue with empty string works for string vector
TEST_F(BoundValueRefVectorTest_378, SetValueWithEmptyStringForStringVector_378) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    
    auto result = ref.setValue("");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], "");
}

// Test that isContainer returns true for vector specialization
TEST_F(BoundValueRefVectorTest_378, IsContainerReturnsTrue_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    EXPECT_TRUE(ref.isContainer());
}

// Test setValue with double vector
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsDoubleToVector_378) {
    std::vector<double> vec;
    BoundValueRef<double> ref(vec);
    
    auto result = ref.setValue("3.14");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_DOUBLE_EQ(vec[0], 3.14);
}

// Test setValue with negative integer
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsNegativeInt_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    auto result = ref.setValue("-5");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], -5);
}

// Test setValue with zero
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsZero_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    auto result = ref.setValue("0");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], 0);
}

// Test that failed conversion does not affect previously added elements
TEST_F(BoundValueRefVectorTest_378, FailedConversionPreservesPreviousElements_378) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    
    ref.setValue("10");
    auto result = ref.setValue("invalid");
    
    EXPECT_FALSE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], 10);
}

// Test for non-vector (single value) BoundValueRef
class BoundValueRefSingleTest_378 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that setValue for a single value ref sets the value
TEST_F(BoundValueRefSingleTest_378, SetValueSetsInt_378) {
    int val = 0;
    BoundValueRef<int> ref(val);
    
    auto result = ref.setValue("99");
    
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(val, 99);
}

// Test that isContainer returns false for single value ref
TEST_F(BoundValueRefSingleTest_378, IsContainerReturnsFalse_378) {
    int val = 0;
    BoundValueRef<int> ref(val);
    
    EXPECT_FALSE(ref.isContainer());
}

// Test that setValue with invalid input for single ref returns error
TEST_F(BoundValueRefSingleTest_378, SetValueWithInvalidInputReturnsError_378) {
    int val = 0;
    BoundValueRef<int> ref(val);
    
    auto result = ref.setValue("not_valid");
    
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test multiple string appends to vector
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsMultipleStrings_378) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    
    ref.setValue("alpha");
    ref.setValue("beta");
    ref.setValue("gamma");
    
    ASSERT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], "alpha");
    EXPECT_EQ(vec[1], "beta");
    EXPECT_EQ(vec[2], "gamma");
}

// Test bool vector
TEST_F(BoundValueRefVectorTest_378, SetValueAppendsBoolToVector_378) {
    std::vector<bool> vec;
    BoundValueRef<bool> ref(vec);
    
    auto result = ref.setValue("true");
    
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], true);
}
