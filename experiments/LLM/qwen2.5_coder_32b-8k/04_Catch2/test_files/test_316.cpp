#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"

#include <vector>



using namespace Catch::Generators;



class FixedValuesGeneratorTest : public ::testing::Test {

protected:

    std::initializer_list<int> values = {1, 2, 3, 4, 5};

    FixedValuesGenerator<int> generator{values};



    void SetUp() override {

        generator.next(); // Start with the first element

    }

};



TEST_F(FixedValuesGeneratorTest_316, GetReturnsFirstValue_316) {

    EXPECT_EQ(generator.get(), 1);

}



TEST_F(FixedValuesGeneratorTest_316, NextAdvancesToNextValue_316) {

    generator.next();

    EXPECT_EQ(generator.get(), 2);

}



TEST_F(FixedValuesGeneratorTest_316, NextWrapsAroundAtEnd_316) {

    for (size_t i = 0; i < values.size(); ++i) {

        generator.next();

    }

    EXPECT_EQ(generator.get(), 1); // Wrap around to the first element

}



TEST_F(FixedValuesGeneratorTest_316, BoundaryConditionSingleElement_316) {

    FixedValuesGenerator<int> singleGenerator({42});

    EXPECT_EQ(singleGenerator.get(), 42);

    singleGenerator.next();

    EXPECT_EQ(singleGenerator.get(), 42); // Should still return the same value

}



TEST_F(FixedValuesGeneratorTest_316, BoundaryConditionEmptyList_316) {

    FixedValuesGenerator<int> emptyGenerator({});

    EXPECT_THROW(emptyGenerator.get(), std::out_of_range);

}
