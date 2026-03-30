#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;



class RangeGeneratorTest_1111 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RangeGeneratorTest_1111, ConstructorWithStepIncreases_1111) {

    RangeGenerator<int> generator(0, 5, 1);

    EXPECT_EQ(generator.get(), 0);

}



TEST_F(RangeGeneratorTest_1111, ConstructorWithStepDecreases_1111) {

    RangeGenerator<int> generator(5, 0, -1);

    EXPECT_EQ(generator.get(), 5);

}



TEST_F(RangeGeneratorTest_1111, NextReturnsTrueUntilEnd_1111) {

    RangeGenerator<int> generator(0, 3, 1);

    EXPECT_TRUE(generator.next());

    EXPECT_TRUE(generator.next());

    EXPECT_FALSE(generator.next());

}



TEST_F(RangeGeneratorTest_1111, GetIncrementsWithNext_1111) {

    RangeGenerator<int> generator(0, 5, 2);

    EXPECT_EQ(generator.get(), 0);

    generator.next();

    EXPECT_EQ(generator.get(), 2);

    generator.next();

    EXPECT_EQ(generator.get(), 4);

}



TEST_F(RangeGeneratorTest_1111, GetDecrementsWithNext_1111) {

    RangeGenerator<int> generator(5, 0, -2);

    EXPECT_EQ(generator.get(), 5);

    generator.next();

    EXPECT_EQ(generator.get(), 3);

    generator.next();

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(RangeGeneratorTest_1111, ConstructorWithoutStepPositive_1111) {

    RangeGenerator<int> generator(0, 3);

    EXPECT_EQ(generator.get(), 0);

    EXPECT_TRUE(generator.next());

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(RangeGeneratorTest_1111, ConstructorWithoutStepNegative_1111) {

    RangeGenerator<int> generator(3, 0);

    EXPECT_EQ(generator.get(), 3);

    EXPECT_TRUE(generator.next());

    EXPECT_EQ(generator.get(), 2);

}



TEST_F(RangeGeneratorTest_1111, BoundaryConditionStartEqualsEndThrows_1111) {

    EXPECT_THROW({

        RangeGenerator<int> generator(5, 5);

    }, std::exception);

}



TEST_F(RangeGeneratorTest_1111, BoundaryConditionZeroStepThrows_1111) {

    EXPECT_THROW({

        RangeGenerator<int> generator(0, 5, 0);

    }, std::exception);

}



TEST_F(RangeGeneratorTest_1111, StepMovesAwayFromEndThrows_1111) {

    EXPECT_THROW({

        RangeGenerator<int> generator(0, 5, -1);

    }, std::exception);



    EXPECT_THROW({

        RangeGenerator<int> generator(5, 0, 1);

    }, std::exception);

}
