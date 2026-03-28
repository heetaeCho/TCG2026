#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include <vector>



using namespace Catch::Generators;



class IteratorGeneratorTest_939 : public ::testing::Test {

protected:

    std::vector<int> elements;

    IteratorGenerator<int> generator;



    void SetUp() override {

        elements = {1, 2, 3, 4, 5};

        generator = IteratorGenerator<int>(elements.begin(), elements.end());

    }

};



TEST_F(IteratorGeneratorTest_939, GetReturnsFirstElementInitially_939) {

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(IteratorGeneratorTest_939, NextAdvancesToNextElement_939) {

    generator.next();

    EXPECT_EQ(generator.get(), 2);

}



TEST_F(IteratorGeneratorTest_939, NextReturnsFalseAtEnd_939) {

    for (size_t i = 0; i < elements.size(); ++i) {

        generator.next();

    }

    EXPECT_FALSE(generator.next());

}



TEST_F(IteratorGeneratorTest_939, GetDoesNotAdvanceOnGetCall_939) {

    int initialElement = generator.get();

    generator.get();

    EXPECT_EQ(generator.get(), initialElement);

}



TEST_F(IteratorGeneratorTest_939, BoundaryCondition_EmptyRange_939) {

    std::vector<int> emptyElements;

    IteratorGenerator<int> emptyGenerator(emptyElements.begin(), emptyElements.end());

    EXPECT_FALSE(emptyGenerator.next());

}



TEST_F(IteratorGeneratorTest_939, ExceptionalCase_OutOfBoundsAccess_939) {

    for (size_t i = 0; i < elements.size(); ++i) {

        generator.next();

    }

    EXPECT_THROW(generator.get(), std::out_of_range);

}
