#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the header under test
#include "catch2/generators/catch_generators.hpp"

using namespace Catch::Generators;

// Test that SingleValueGenerator stores and returns an int value correctly
TEST(SingleValueGeneratorTest_314, GetReturnsStoredIntValue_314) {
    SingleValueGenerator<int> gen(42);
    EXPECT_EQ(gen.get(), 42);
}

// Test that SingleValueGenerator stores and returns a string value correctly (copy constructor)
TEST(SingleValueGeneratorTest_314, GetReturnsStoredStringValue_314) {
    std::string value = "hello";
    SingleValueGenerator<std::string> gen(value);
    EXPECT_EQ(gen.get(), "hello");
}

// Test that SingleValueGenerator works with move constructor
TEST(SingleValueGeneratorTest_314, GetReturnsMovedStringValue_314) {
    SingleValueGenerator<std::string> gen(std::string("moved_value"));
    EXPECT_EQ(gen.get(), "moved_value");
}

// Test that next() returns false since there's only a single value
TEST(SingleValueGeneratorTest_314, NextReturnsFalse_314) {
    SingleValueGenerator<int> gen(100);
    EXPECT_FALSE(gen.next());
}

// Test that get() returns the same value after calling next()
TEST(SingleValueGeneratorTest_314, GetReturnsSameValueAfterNext_314) {
    SingleValueGenerator<int> gen(7);
    EXPECT_EQ(gen.get(), 7);
    gen.next();
    EXPECT_EQ(gen.get(), 7);
}

// Test with zero value
TEST(SingleValueGeneratorTest_314, GetReturnsZeroValue_314) {
    SingleValueGenerator<int> gen(0);
    EXPECT_EQ(gen.get(), 0);
}

// Test with negative value
TEST(SingleValueGeneratorTest_314, GetReturnsNegativeValue_314) {
    SingleValueGenerator<int> gen(-999);
    EXPECT_EQ(gen.get(), -999);
}

// Test with double value
TEST(SingleValueGeneratorTest_314, GetReturnsDoubleValue_314) {
    SingleValueGenerator<double> gen(3.14159);
    EXPECT_DOUBLE_EQ(gen.get(), 3.14159);
}

// Test with empty string
TEST(SingleValueGeneratorTest_314, GetReturnsEmptyString_314) {
    SingleValueGenerator<std::string> gen(std::string(""));
    EXPECT_EQ(gen.get(), "");
}

// Test that get() returns a const reference (multiple calls return same value)
TEST(SingleValueGeneratorTest_314, GetReturnsConsistentReference_314) {
    SingleValueGenerator<int> gen(55);
    const int& ref1 = gen.get();
    const int& ref2 = gen.get();
    EXPECT_EQ(ref1, ref2);
    EXPECT_EQ(&ref1, &ref2);
}

// Test calling next() multiple times always returns false
TEST(SingleValueGeneratorTest_314, MultipleNextCallsReturnFalse_314) {
    SingleValueGenerator<int> gen(1);
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
}

// Test with a vector as the value type
TEST(SingleValueGeneratorTest_314, GetReturnsVectorValue_314) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    SingleValueGenerator<std::vector<int>> gen(vec);
    EXPECT_EQ(gen.get(), vec);
}

// Test with bool value true
TEST(SingleValueGeneratorTest_314, GetReturnsBoolTrue_314) {
    SingleValueGenerator<bool> gen(true);
    EXPECT_EQ(gen.get(), true);
}

// Test with bool value false
TEST(SingleValueGeneratorTest_314, GetReturnsBoolFalse_314) {
    SingleValueGenerator<bool> gen(false);
    EXPECT_EQ(gen.get(), false);
}

// Test with char value
TEST(SingleValueGeneratorTest_314, GetReturnsCharValue_314) {
    SingleValueGenerator<char> gen('A');
    EXPECT_EQ(gen.get(), 'A');
}

// Test with max int value (boundary)
TEST(SingleValueGeneratorTest_314, GetReturnsMaxIntValue_314) {
    SingleValueGenerator<int> gen(std::numeric_limits<int>::max());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::max());
}

// Test with min int value (boundary)
TEST(SingleValueGeneratorTest_314, GetReturnsMinIntValue_314) {
    SingleValueGenerator<int> gen(std::numeric_limits<int>::min());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::min());
}
