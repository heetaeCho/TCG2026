#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/image.cpp"



namespace Exiv2Tests {



class TypeValidTest_1064 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed

};



TEST_F(TypeValidTest_1064, ValidTypeLowerBound_1064) {

    EXPECT_TRUE(typeValid(1));

}



TEST_F(TypeValidTest_1064, ValidTypeUpperBound_1064) {

    EXPECT_TRUE(typeValid(13));

}



TEST_F(TypeValidTest_1064, InvalidTypeBelowLowerBound_1064) {

    EXPECT_FALSE(typeValid(0));

}



TEST_F(TypeValidTest_1064, InvalidTypeAboveUpperBound_1064) {

    EXPECT_FALSE(typeValid(14));

}



TEST_F(TypeValidTest_1064, ValidTypeMidRange_1064) {

    EXPECT_TRUE(typeValid(7));

}



}  // namespace Exiv2Tests
