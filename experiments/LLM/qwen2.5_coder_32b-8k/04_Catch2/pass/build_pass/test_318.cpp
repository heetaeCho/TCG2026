#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



class GeneratorTest_318 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed.

};



TEST_F(GeneratorTest_318, SingleValueGeneratorReturnsCorrectValue_318) {

    auto generator = value(42);

    EXPECT_TRUE(generator.next());

    EXPECT_EQ(generator.get(), 42);

}



TEST_F(GeneratorTest_318, SingleValueGeneratorDoesNotAdvanceFurther_318) {

    auto generator = value(42);

    EXPECT_TRUE(generator.next());

    EXPECT_FALSE(generator.next());

}



TEST_F(GeneratorTest_318, SingleValueGeneratorReturnsSameValueOnMultipleGets_318) {

    auto generator = value(42);

    EXPECT_TRUE(generator.next());

    EXPECT_EQ(generator.get(), 42);

    EXPECT_EQ(generator.get(), 42); // Subsequent gets should return the same value

}



TEST_F(GeneratorTest_318, SingleValueGeneratorHandlesDifferentTypes_318) {

    auto intGen = value(10);

    EXPECT_TRUE(intGen.next());

    EXPECT_EQ(intGen.get(), 10);



    auto stringGen = value(std::string("test"));

    EXPECT_TRUE(stringGen.next());

    EXPECT_EQ(stringGen.get(), "test");

}



TEST_F(GeneratorTest_318, SingleValueGeneratorBoundaryConditionEmpty_318) {

    auto generator = value("");

    EXPECT_TRUE(generator.next());

    EXPECT_EQ(generator.get(), "");

}
