#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest_413 : public ::testing::Test {

protected:

    Optional<int> emptyOptional;

    Optional<int> nonEmptyOptional;



    void SetUp() override {

        emptyOptional = Optional<int>();

        nonEmptyOptional = Optional<int>(42);

    }

};



TEST_F(OptionalTest_413, None_ReturnsTrueForEmptyOptional_413) {

    EXPECT_TRUE(emptyOptional.none());

}



TEST_F(OptionalTest_413, None_ReturnsFalseForNonEmptyOptional_413) {

    EXPECT_FALSE(nonEmptyOptional.none());

}



TEST_F(OptionalTest_413, Some_ReturnsFalseForEmptyOptional_413) {

    EXPECT_FALSE(emptyOptional.some());

}



TEST_F(OptionalTest_413, Some_ReturnsTrueForNonEmptyOptional_413) {

    EXPECT_TRUE(nonEmptyOptional.some());

}



TEST_F(OptionalTest_413, OperatorBool_ReturnsFalseForEmptyOptional_413) {

    EXPECT_FALSE(static_cast<bool>(emptyOptional));

}



TEST_F(OptionalTest_413, OperatorBool_ReturnsTrueForNonEmptyOptional_413) {

    EXPECT_TRUE(static_cast<bool>(nonEmptyOptional));

}



TEST_F(OptionalTest_413, OperatorNot_ReturnsTrueForEmptyOptional_413) {

    EXPECT_TRUE(!emptyOptional);

}



TEST_F(OptionalTest_413, OperatorNot_ReturnsFalseForNonEmptyOptional_413) {

    EXPECT_FALSE(!nonEmptyOptional);

}



TEST_F(OptionalTest_413, ValueOr_ReturnsDefaultValueForEmptyOptional_413) {

    int defaultValue = 0;

    EXPECT_EQ(emptyOptional.valueOr(defaultValue), defaultValue);

}



TEST_F(OptionalTest_413, ValueOr_ReturnsStoredValueForNonEmptyOptional_413) {

    int expectedValue = 42;

    EXPECT_EQ(nonEmptyOptional.valueOr(0), expectedValue);

}



TEST_F(OptionalTest_413, Reset_MakesOptionalEmpty_413) {

    nonEmptyOptional.reset();

    EXPECT_TRUE(nonEmptyOptional.none());

}
