#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::ElementsAre;



class IteratorGeneratorTest_1112 : public ::testing::Test {

protected:

    std::vector<int> testVector = {1, 2, 3, 4, 5};

};



TEST_F(IteratorGeneratorTest_1112, InitializationWithValidValues_1112) {

    IteratorGenerator<int> generator(testVector.begin(), testVector.end());

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(IteratorGeneratorTest_1112, IteratesThroughAllElements_1112) {

    IteratorGenerator<int> generator(testVector.begin(), testVector.end());

    std::vector<int> result;

    while (true) {

        result.push_back(generator.get());

        if (!generator.next()) break;

    }

    EXPECT_THAT(result, ElementsAre(1, 2, 3, 4, 5));

}



TEST_F(IteratorGeneratorTest_1112, ReturnsFalseWhenNoMoreElements_1112) {

    IteratorGenerator<int> generator(testVector.begin(), testVector.end());

    while (generator.next()) {}

    EXPECT_FALSE(generator.next());

}



TEST_F(IteratorGeneratorTest_1112, InitializationWithEmptyRangeThrowsException_1112) {

    EXPECT_THROW(IteratorGenerator<int>(testVector.end(), testVector.end()), Catch::Detail::generators::GeneratorException);

}



TEST_F(IteratorGeneratorTest_1112, GetDoesNotAdvancePosition_1112) {

    IteratorGenerator<int> generator(testVector.begin(), testVector.end());

    EXPECT_EQ(generator.get(), 1);

    EXPECT_EQ(generator.get(), 1);

}
