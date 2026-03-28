#include <gtest/gtest.h>
#include <catch2/generators/catch_generators.hpp>
#include <string>
#include <vector>

// Test that value() creates a generator wrapper for an integer
TEST(CatchGeneratorsValueTest_318, ValueCreatesGeneratorForInt_318) {
    auto gen = Catch::Generators::value(42);
    // The generator should provide the value we passed in
    EXPECT_EQ(gen.get(), 42);
}

// Test that value() creates a generator wrapper for a double
TEST(CatchGeneratorsValueTest_318, ValueCreatesGeneratorForDouble_318) {
    auto gen = Catch::Generators::value(3.14);
    EXPECT_DOUBLE_EQ(gen.get(), 3.14);
}

// Test that value() creates a generator wrapper for a string
TEST(CatchGeneratorsValueTest_318, ValueCreatesGeneratorForString_318) {
    auto gen = Catch::Generators::value(std::string("hello"));
    EXPECT_EQ(gen.get(), "hello");
}

// Test that value() works with an lvalue
TEST(CatchGeneratorsValueTest_318, ValueWorksWithLvalue_318) {
    int x = 99;
    auto gen = Catch::Generators::value(x);
    EXPECT_EQ(gen.get(), 99);
}

// Test that value() works with a const lvalue
TEST(CatchGeneratorsValueTest_318, ValueWorksWithConstLvalue_318) {
    const int x = 77;
    auto gen = Catch::Generators::value(x);
    EXPECT_EQ(gen.get(), 77);
}

// Test that value() works with rvalue (move semantics)
TEST(CatchGeneratorsValueTest_318, ValueWorksWithRvalue_318) {
    auto gen = Catch::Generators::value(std::string("moved"));
    EXPECT_EQ(gen.get(), "moved");
}

// Test that a single value generator returns false on next() since it has only one value
TEST(CatchGeneratorsValueTest_318, SingleValueGeneratorNextReturnsFalse_318) {
    auto gen = Catch::Generators::value(10);
    // A single value generator should not have more values after the first
    EXPECT_FALSE(gen.next());
}

// Test boundary: value with zero
TEST(CatchGeneratorsValueTest_318, ValueWithZero_318) {
    auto gen = Catch::Generators::value(0);
    EXPECT_EQ(gen.get(), 0);
}

// Test boundary: value with negative number
TEST(CatchGeneratorsValueTest_318, ValueWithNegativeNumber_318) {
    auto gen = Catch::Generators::value(-1);
    EXPECT_EQ(gen.get(), -1);
}

// Test boundary: value with empty string
TEST(CatchGeneratorsValueTest_318, ValueWithEmptyString_318) {
    auto gen = Catch::Generators::value(std::string(""));
    EXPECT_EQ(gen.get(), "");
}

// Test boundary: value with max int
TEST(CatchGeneratorsValueTest_318, ValueWithMaxInt_318) {
    auto gen = Catch::Generators::value(std::numeric_limits<int>::max());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::max());
}

// Test boundary: value with min int
TEST(CatchGeneratorsValueTest_318, ValueWithMinInt_318) {
    auto gen = Catch::Generators::value(std::numeric_limits<int>::min());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::min());
}

// Test that value() works with bool true
TEST(CatchGeneratorsValueTest_318, ValueWithBoolTrue_318) {
    auto gen = Catch::Generators::value(true);
    EXPECT_EQ(gen.get(), true);
}

// Test that value() works with bool false
TEST(CatchGeneratorsValueTest_318, ValueWithBoolFalse_318) {
    auto gen = Catch::Generators::value(false);
    EXPECT_EQ(gen.get(), false);
}

// Test that value() works with char
TEST(CatchGeneratorsValueTest_318, ValueWithChar_318) {
    auto gen = Catch::Generators::value('A');
    EXPECT_EQ(gen.get(), 'A');
}

// Test that the decayed type works correctly (e.g., const char* decays properly)
TEST(CatchGeneratorsValueTest_318, ValueDecaysConstCharPointer_318) {
    const char* str = "test";
    auto gen = Catch::Generators::value(str);
    EXPECT_STREQ(gen.get(), "test");
}

// Test that get() is consistent (calling get() multiple times without next() returns the same value)
TEST(CatchGeneratorsValueTest_318, GetIsConsistentWithoutNext_318) {
    auto gen = Catch::Generators::value(55);
    EXPECT_EQ(gen.get(), 55);
    EXPECT_EQ(gen.get(), 55);
    EXPECT_EQ(gen.get(), 55);
}

// Test with float type
TEST(CatchGeneratorsValueTest_318, ValueWithFloat_318) {
    auto gen = Catch::Generators::value(1.5f);
    EXPECT_FLOAT_EQ(gen.get(), 1.5f);
}

// Test with unsigned int
TEST(CatchGeneratorsValueTest_318, ValueWithUnsignedInt_318) {
    auto gen = Catch::Generators::value(42u);
    EXPECT_EQ(gen.get(), 42u);
}

// Test with long long
TEST(CatchGeneratorsValueTest_318, ValueWithLongLong_318) {
    auto gen = Catch::Generators::value(123456789LL);
    EXPECT_EQ(gen.get(), 123456789LL);
}
