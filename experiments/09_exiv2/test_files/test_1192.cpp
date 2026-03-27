#include <gtest/gtest.h>

#include "bmffimage.cpp"



namespace Exiv2 {



class SkipBoxTest_1192 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(SkipBoxTest_1192, NormalOperation_BoxNotSkipped_1192) {

    EXPECT_FALSE(skipBox(TAG::ftyp));

}



TEST_F(SkipBoxTest_1192, NormalOperation_BoxSkipped_mdat_1192) {

    EXPECT_TRUE(skipBox(TAG::mdat));

}



TEST_F(SkipBoxTest_1192, BoundaryCondition_ZeroBox_1192) {

    EXPECT_TRUE(skipBox(0));

}



TEST_F(SkipBoxTest_1192, ExceptionalCase_UnrecognizedBox_1192) {

    EXPECT_FALSE(skipBox(999999999)); // Some arbitrary value not defined in TAG

}



}  // namespace Exiv2
