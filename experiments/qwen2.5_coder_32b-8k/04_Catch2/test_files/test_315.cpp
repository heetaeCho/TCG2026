#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



class SingleValueGeneratorTest_315 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects if needed

    }

};



TEST_F(SingleValueGeneratorTest_315, NextReturnsFalseOnce_315) {

    SingleValueGenerator<int> generator(42);

    EXPECT_FALSE(generator.next());

}



TEST_F(SingleValueGeneratorTest_315, GetReturnsInitialValue_315) {

    int initialValue = 42;

    SingleValueGenerator<int> generator(initialValue);

    EXPECT_EQ(generator.get(), initialValue);

}



TEST_F(SingleValueGeneratorTest_315, GetConsistentAfterNext_315) {

    int initialValue = 42;

    SingleValueGenerator<int> generator(initialValue);

    generator.next(); // This should return false

    EXPECT_EQ(generator.get(), initialValue); // get should still return the initial value

}



TEST_F(SingleValueGeneratorTest_315, NextReturnsFalseMultipleCalls_315) {

    SingleValueGenerator<int> generator(42);

    EXPECT_FALSE(generator.next());

    EXPECT_FALSE(generator.next()); // Subsequent calls to next should also return false

    EXPECT_FALSE(generator.next());

}
