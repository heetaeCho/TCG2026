#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



class SingleValueGeneratorTest_314 : public ::testing::Test {

protected:

    template<typename T>

    void TestSingleValueGenerator(T value) {

        SingleValueGenerator<T> generator(value);

        EXPECT_EQ(generator.get(), value);

        EXPECT_FALSE(generator.next());

    }

};



TEST_F(SingleValueGeneratorTest_314, GetReturnsInitialValueForInt_314) {

    TestSingleValueGenerator(42);

}



TEST_F(SingleValueGeneratorTest_314, GetReturnsInitialValueForDouble_314) {

    TestSingleValueGenerator(3.14);

}



TEST_F(SingleValueGeneratorTest_314, GetReturnsInitialValueForString_314) {

    TestSingleValueGenerator(std::string("Hello, World!"));

}



TEST_F(SingleValueGeneratorTest_314, NextReturnsFalseAfterFirstCall_314) {

    SingleValueGenerator<int> generator(0);

    EXPECT_FALSE(generator.next());

}



TEST_F(SingleValueGeneratorTest_314, GetConsistentAfterNext_314) {

    SingleValueGenerator<std::string> generator("Test");

    generator.next();

    EXPECT_EQ(generator.get(), "Test");

}



TEST_F(SingleValueGeneratorTest_314, MoveConstructorWorksForInt_314) {

    int value = 10;

    SingleValueGenerator<int> generator(std::move(value));

    EXPECT_EQ(generator.get(), 10);

}



TEST_F(SingleValueGeneratorTest_314, MoveConstructorWorksForString_314) {

    std::string value = "Moved";

    SingleValueGenerator<std::string> generator(std::move(value));

    EXPECT_EQ(generator.get(), "Moved");

}
