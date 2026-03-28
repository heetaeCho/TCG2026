#include <gtest/gtest.h>

#include "tags_int.hpp"



using namespace Exiv2::Internal;



class TagDetailsTest_176 : public ::testing::Test {

protected:

    void SetUp() override {

        tagDetails = new TagDetails{42, "example"};

    }



    void TearDown() override {

        delete tagDetails;

    }



    TagDetails* tagDetails;

};



TEST_F(TagDetailsTest_176, EqualityOperatorWithMatchingKey_176) {

    EXPECT_TRUE(*tagDetails == 42);

}



TEST_F(TagDetailsTest_176, EqualityOperatorWithNonMatchingKey_176) {

    EXPECT_FALSE(*tagDetails == 99);

}



TEST_F(TagDetailsTest_176, BoundaryConditionMinimumInt64_176) {

    TagDetails minTag{-9223372036854775808, "min"};

    EXPECT_TRUE(minTag == -9223372036854775808);

}



TEST_F(TagDetailsTest_176, BoundaryConditionMaximumInt64_176) {

    TagDetails maxTag{9223372036854775807, "max"};

    EXPECT_TRUE(maxTag == 9223372036854775807);

}
