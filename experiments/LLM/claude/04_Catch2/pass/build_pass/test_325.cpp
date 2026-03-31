#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Generators;

class MakeGeneratorsTest_325 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MakeGeneratorsTest_325, SingleValueGenerator_325) {
    auto gen = makeGenerators(42);
    // The generator should produce at least the first value
    EXPECT_EQ(gen.get(), 42);
}

TEST_F(MakeGeneratorsTest_325, MultipleValues_325) {
    auto gen = makeGenerators(1, 2, 3);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, StringValues_325) {
    auto gen = makeGenerators(std::string("hello"), std::string("world"));
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, SingleValueExhaustsAfterOne_325) {
    auto gen = makeGenerators(99);
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, DoubleValues_325) {
    auto gen = makeGenerators(1.5, 2.5, 3.5);
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, NegativeValues_325) {
    auto gen = makeGenerators(-1, -2, -3);
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, ZeroValue_325) {
    auto gen = makeGenerators(0);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, MixedWithValueWrapper_325) {
    auto gen = makeGenerators(10, value(20), value(30));
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, LargeNumberOfValues_325) {
    auto gen = makeGenerators(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 10) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

TEST_F(MakeGeneratorsTest_325, BoolValues_325) {
    auto gen = makeGenerators(true, false);
    EXPECT_EQ(gen.get(), true);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), false);
    EXPECT_FALSE(gen.next());
}

TEST_F(MakeGeneratorsTest_325, BoundaryIntValues_325) {
    auto gen = makeGenerators(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::min());
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), std::numeric_limits<int>::max());
    EXPECT_FALSE(gen.next());
}
