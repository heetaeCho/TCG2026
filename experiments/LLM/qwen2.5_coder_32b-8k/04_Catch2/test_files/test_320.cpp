#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



class GeneratorsTest_320 : public ::testing::Test {

protected:

    Generators<int> gen;

    

    GeneratorsTest_320() : gen(1, 2, 3) {}

};



TEST_F(GeneratorsTest_320, GetReturnsFirstElement_320) {

    EXPECT_EQ(gen.get(), 1);

}



TEST_F(GeneratorsTest_320, NextAdvancesToNextElement_320) {

    gen.next();

    EXPECT_EQ(gen.get(), 2);

}



TEST_F(GeneratorsTest_320, NextReturnsFalseAtEnd_320) {

    gen.next();

    gen.next();

    gen.next();

    EXPECT_FALSE(gen.next());

}



TEST_F(GeneratorsTest_320, GetThrowsWhenBeyondLastElement_320) {

    gen.next();

    gen.next();

    gen.next();

    gen.next(); // Move beyond the last element

    EXPECT_THROW(gen.get(), std::runtime_error); // Assuming it throws an exception when out of bounds

}



TEST_F(GeneratorsTest_320, SingleElementGenerator_320) {

    Generators<int> singleGen(42);

    EXPECT_EQ(singleGen.get(), 42);

    EXPECT_FALSE(singleGen.next());

}



TEST_F(GeneratorsTest_320, MultipleNextCallsStayAtLastElement_320) {

    gen.next();

    gen.next();

    gen.next(); // This should be the last element

    gen.next();

    gen.next();

    EXPECT_EQ(gen.get(), 3);

}
