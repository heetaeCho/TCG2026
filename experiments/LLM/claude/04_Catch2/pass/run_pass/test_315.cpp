#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"

// Since we're testing Catch2's SingleValueGenerator, we need to understand
// that it wraps a single value and:
// - get() returns the stored value
// - next() returns false (since there's only one value)

TEST(SingleValueGeneratorTest_315, ConstructWithLValue_315) {
    int value = 42;
    Catch::Generators::SingleValueGenerator<int> gen(value);
    EXPECT_EQ(gen.get(), 42);
}

TEST(SingleValueGeneratorTest_315, ConstructWithRValue_315) {
    Catch::Generators::SingleValueGenerator<int> gen(42);
    EXPECT_EQ(gen.get(), 42);
}

TEST(SingleValueGeneratorTest_315, NextReturnsFalse_315) {
    Catch::Generators::SingleValueGenerator<int> gen(42);
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, GetReturnsCorrectValue_315) {
    Catch::Generators::SingleValueGenerator<int> gen(100);
    const int& val = gen.get();
    EXPECT_EQ(val, 100);
}

TEST(SingleValueGeneratorTest_315, GetReturnsConstReference_315) {
    Catch::Generators::SingleValueGenerator<int> gen(55);
    const int& ref1 = gen.get();
    const int& ref2 = gen.get();
    EXPECT_EQ(&ref1, &ref2);
}

TEST(SingleValueGeneratorTest_315, NextAlwaysReturnsFalseOnMultipleCalls_315) {
    Catch::Generators::SingleValueGenerator<int> gen(10);
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, StringValue_315) {
    std::string s = "hello";
    Catch::Generators::SingleValueGenerator<std::string> gen(s);
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, StringRValue_315) {
    Catch::Generators::SingleValueGenerator<std::string> gen(std::string("world"));
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, ZeroValue_315) {
    Catch::Generators::SingleValueGenerator<int> gen(0);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, NegativeValue_315) {
    Catch::Generators::SingleValueGenerator<int> gen(-1);
    EXPECT_EQ(gen.get(), -1);
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, DoubleValue_315) {
    Catch::Generators::SingleValueGenerator<double> gen(3.14);
    EXPECT_DOUBLE_EQ(gen.get(), 3.14);
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, BoolValue_315) {
    Catch::Generators::SingleValueGenerator<bool> gen(true);
    EXPECT_EQ(gen.get(), true);
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, GetAfterNextStillReturnsValue_315) {
    Catch::Generators::SingleValueGenerator<int> gen(42);
    EXPECT_EQ(gen.get(), 42);
    gen.next();
    // Value should still be accessible after next() returns false
    EXPECT_EQ(gen.get(), 42);
}

TEST(SingleValueGeneratorTest_315, EmptyString_315) {
    Catch::Generators::SingleValueGenerator<std::string> gen(std::string(""));
    EXPECT_EQ(gen.get(), "");
    EXPECT_FALSE(gen.next());
}

TEST(SingleValueGeneratorTest_315, LargeIntValue_315) {
    Catch::Generators::SingleValueGenerator<long long> gen(9223372036854775807LL);
    EXPECT_EQ(gen.get(), 9223372036854775807LL);
    EXPECT_FALSE(gen.next());
}
