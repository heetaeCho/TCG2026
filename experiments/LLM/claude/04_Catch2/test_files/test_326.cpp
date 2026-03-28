#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <type_traits>

// We need to test the Catch2 generators interface through Google Test
// by invoking the functions and checking observable return types and values

using namespace Catch::Generators;

class MakeGeneratorsTest_326 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MakeGeneratorsTest_326, SingleIntValue_326) {
    // Test that makeGenerators with a single int value produces a valid Generators<int>
    auto gen = makeGenerators(as<int>{}, 42);
    // The generator should produce at least one value
    auto const& val = gen.get();
    EXPECT_EQ(val, 42);
}

TEST_F(MakeGeneratorsTest_326, SingleDoubleValue_326) {
    // Test with a double type
    auto gen = makeGenerators(as<double>{}, 3.14);
    auto const& val = gen.get();
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(MakeGeneratorsTest_326, ImplicitConversionIntToDouble_326) {
    // Test that an int value is converted to double via the as<T> tag
    auto gen = makeGenerators(as<double>{}, 5);
    auto const& val = gen.get();
    EXPECT_DOUBLE_EQ(val, 5.0);
}

TEST_F(MakeGeneratorsTest_326, MultipleValues_326) {
    // Test makeGenerators with multiple values
    auto gen = makeGenerators(as<int>{}, 1, 2, 3);
    
    // First value
    EXPECT_EQ(gen.get(), 1);
    
    // Advance and check subsequent values
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    // No more values
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, StringValue_326) {
    // Test with string type
    auto gen = makeGenerators(as<std::string>{}, "hello");
    auto const& val = gen.get();
    EXPECT_EQ(val, std::string("hello"));
}

TEST_F(MakeGeneratorsTest_326, MultipleStringValues_326) {
    auto gen = makeGenerators(as<std::string>{}, "foo", "bar", "baz");
    
    EXPECT_EQ(gen.get(), std::string("foo"));
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), std::string("bar"));
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), std::string("baz"));
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, MixedValueAndGenerator_326) {
    // Test combining a plain value with an existing generator
    auto gen = makeGenerators(as<int>{}, 10, value(20));
    
    EXPECT_EQ(gen.get(), 10);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, SingleValueNextReturnsFalse_326) {
    // A generator with only one value should return false on next()
    auto gen = makeGenerators(as<int>{}, 99);
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, NegativeValues_326) {
    auto gen = makeGenerators(as<int>{}, -1, -100, 0);
    
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, BoundaryIntValues_326) {
    auto gen = makeGenerators(as<int>{}, 
        std::numeric_limits<int>::min(), 
        std::numeric_limits<int>::max());
    
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::min());
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::max());
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_326, ZeroValue_326) {
    auto gen = makeGenerators(as<int>{}, 0);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}
