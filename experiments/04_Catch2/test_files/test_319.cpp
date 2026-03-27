#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



namespace {



TEST(CatchGenerators_319, ValuesGenerator_ReturnsCorrectValues_319) {

    auto gen = values({1, 2, 3});

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 3);

    EXPECT_FALSE(gen.next());

}



TEST(CatchGenerators_319, ValuesGenerator_EmptyList_ReturnsFalseOnNext_319) {

    auto gen = values<int>({});

    EXPECT_FALSE(gen.next());

}



TEST(CatchGenerators_319, ValuesGenerator_SingleValue_ReturnsCorrectly_319) {

    auto gen = values({42});

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 42);

    EXPECT_FALSE(gen.next());

}



TEST(CatchGenerators_319, ValuesGenerator_MultipleTypes_ReturnsCorrectValues_319) {

    auto gen = values({'a', 'b', 'c'});

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 'a');

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 'b');

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 'c');

    EXPECT_FALSE(gen.next());

}



TEST(CatchGenerators_319, ValuesGenerator_StringValues_ReturnsCorrectly_319) {

    auto gen = values({"hello", "world"});

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), "hello");

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), "world");

    EXPECT_FALSE(gen.next());

}



TEST(CatchGenerators_319, ValuesGenerator_RepeatedValues_ReturnsCorrectly_319) {

    auto gen = values({5, 5, 5});

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 5);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 5);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(gen.get(), 5);

    EXPECT_FALSE(gen.next());

}



} // namespace
