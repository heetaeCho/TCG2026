#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <vector>
#include <functional>

using namespace Catch::Generators;

class MapGeneratorTest_931 : public ::testing::Test {
protected:
};

// Helper to create a generator from fixed values
template <typename T>
GeneratorWrapper<T> makeValues(std::initializer_list<T> values) {
    return Catch::Generators::values(values);
}

TEST_F(MapGeneratorTest_931, MapTransformsIntToInt_931) {
    auto gen = map([](int x) { return x * 2; }, values({1, 2, 3}));
    
    // First value should be transformed
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapTransformsIntToString_931) {
    auto gen = map([](int x) { return std::to_string(x); }, values({10, 20, 30}));
    
    EXPECT_EQ(gen.get(), "10");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "20");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "30");
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapWithSingleElement_931) {
    auto gen = map([](int x) { return x + 100; }, values({5}));
    
    EXPECT_EQ(gen.get(), 105);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapWithIdentityFunction_931) {
    auto gen = map([](int x) { return x; }, values({42, 99}));
    
    EXPECT_EQ(gen.get(), 42);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 99);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapStringToInt_931) {
    auto gen = map([](const std::string& s) { return static_cast<int>(s.size()); }, 
                   values({std::string("hi"), std::string("hello"), std::string("")}));
    
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapWithNegation_931) {
    auto gen = map([](int x) { return -x; }, values({1, -2, 0, 100}));
    
    EXPECT_EQ(gen.get(), -1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -100);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapChained_931) {
    auto gen = map([](int x) { return x * 10; },
                   map([](int x) { return x + 1; }, values({0, 1, 2})));
    
    EXPECT_EQ(gen.get(), 10);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapIntToDouble_931) {
    auto gen = map([](int x) { return x * 0.5; }, values({2, 4, 6}));
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.0);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.0);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, MapIntToBool_931) {
    auto gen = map([](int x) { return x > 0; }, values({-1, 0, 1, 5}));
    
    EXPECT_EQ(gen.get(), false);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), false);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), true);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), true);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_931, GetWithoutNextReturnsFirstMappedValue_931) {
    auto gen = map([](int x) { return x * 3; }, values({7}));
    
    // Calling get multiple times without next should return the same value
    EXPECT_EQ(gen.get(), 21);
    EXPECT_EQ(gen.get(), 21);
}
