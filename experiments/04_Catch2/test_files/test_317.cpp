#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/generators/catch_generators.hpp>



using namespace Catch::Generators;



class FixedValuesGeneratorTest_317 : public ::testing::Test {

protected:

    void SetUp() override {

        values = {1, 2, 3, 4, 5};

        generator = std::make_unique<FixedValuesGenerator<int>>(values);

    }



    std::vector<int> values;

    std::unique_ptr<FixedValuesGenerator<int>> generator;

};



TEST_F(FixedValuesGeneratorTest_317, NextReturnsTrueForValidIndex_317) {

    for (size_t i = 0; i < values.size() - 1; ++i) {

        EXPECT_TRUE(generator->next());

    }

}



TEST_F(FixedValuesGeneratorTest_317, NextReturnsFalseWhenExhausted_317) {

    for (size_t i = 0; i < values.size(); ++i) {

        generator->next();

    }

    EXPECT_FALSE(generator->next());

}



TEST_F(FixedValuesGeneratorTest_317, GetReturnsCorrectValue_317) {

    for (const auto& value : values) {

        EXPECT_EQ(generator->get(), value);

        generator->next();

    }

}



TEST_F(FixedValuesGeneratorTest_317, BoundaryConditionSingleElement_317) {

    std::vector<int> singleValue = {42};

    FixedValuesGenerator<int> singleGenerator(singleValue);

    EXPECT_TRUE(singleGenerator.next());

    EXPECT_EQ(singleGenerator.get(), 42);

    EXPECT_FALSE(singleGenerator.next());

}



TEST_F(FixedValuesGeneratorTest_317, BoundaryConditionEmptyList_317) {

    std::vector<int> emptyValues;

    FixedValuesGenerator<int> emptyGenerator(emptyValues);

    EXPECT_FALSE(emptyGenerator.next());

}
