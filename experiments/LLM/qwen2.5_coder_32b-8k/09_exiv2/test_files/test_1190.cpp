#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/bmffimage.cpp"



namespace {



class BMFFImageTest_1190 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function test.

};



TEST_F(BMFFImageTest_1190, EnableBMFF_ReturnsFalseWhenDisabled_1190) {

    EXPECT_FALSE(Exiv2::enableBMFF(false));

}



TEST_F(BMFFImageTest_1190, EnableBMFF_ReturnsTrueWhenEnabled_1190) {

#ifdef EXV_ENABLE_BMFF

    EXPECT_TRUE(Exiv2::enableBMFF(true));

#else

    EXPECT_FALSE(Exiv2::enableBMFF(true));

#endif

}



} // namespace
