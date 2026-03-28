#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"

#include <vector>



using namespace Catch::Generators;

using ::testing::ElementsAre;



class IteratorGeneratorTest_940 : public ::testing::Test {

protected:

    std::vector<int> elements = {1, 2, 3, 4, 5};

    IteratorGenerator<int> generator{elements.begin(), elements.end()};

};



TEST_F(IteratorGeneratorTest_940, InitialStateReturnsFirstElement_940) {

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(IteratorGeneratorTest_940, NextAdvancesToNextElement_940) {

    generator.next();

    EXPECT_EQ(generator.get(), 2);

}



TEST_F(IteratorGeneratorTest_940, EndOfIterationReturnsFalse_940) {

    for (size_t i = 0; i < elements.size(); ++i) {

        generator.next();

    }

    EXPECT_FALSE(generator.next());

}



TEST_F(IteratorGeneratorTest_940, FullIterationRetrievesAllElements_940) {

    std::vector<int> retrieved_elements;

    do {

        retrieved_elements.push_back(generator.get());

    } while (generator.next());



    EXPECT_THAT(retrieved_elements, ElementsAre(1, 2, 3, 4, 5));

}



TEST_F(IteratorGeneratorTest_940, GetBeforeFirstNextReturnsInitialElement_940) {

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(IteratorGeneratorTest_940, NextPastEndDoesNotChangeLastElement_940) {

    for (size_t i = 0; i < elements.size(); ++i) {

        generator.next();

    }

    generator.next(); // Move past end

    EXPECT_EQ(generator.get(), 5);

}
