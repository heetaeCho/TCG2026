#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Eq;



class StringValueBaseTest_812 : public ::testing::Test {

protected:

    TypeId typeId = static_cast<TypeId>(0); // Assuming 0 is a valid TypeId for testing

    std::string testString = "testString";

    StringValueBase valueBase{typeId, testString};



    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(StringValueBaseTest_812, ConstructorInitializesOkFlag_812) {

    EXPECT_TRUE(valueBase.ok());

}



TEST_F(StringValueBaseTest_812, ToRationalReturnsExpectedValueForValidIndex_812) {

    Rational expected{static_cast<int32_t>(testString.size()), 1};

    EXPECT_EQ(expected, valueBase.toRational(0));

}



TEST_F(StringValueBaseTest_812, ToRationalSetsOkFlagToTrue_812) {

    valueBase.toRational(0);

    EXPECT_TRUE(valueBase.ok());

}



TEST_F(StringValueBaseTest_812, ToRationalThrowsNoExceptionForValidIndex_812) {

    EXPECT_NO_THROW(valueBase.toRational(0));

}



TEST_F(StringValueBaseTest_812, ToRationalThrowsOutOfRangeExceptionForInvalidIndex_812) {

    EXPECT_THROW(valueBase.toRational(1), std::out_of_range);

}
