#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashFTFont.cc"



class GetFTLoadFlagsTest_2606 : public ::testing::Test {

protected:

    bool type1 = false;

    bool trueType = false;

    bool aa = false;

    bool enableFreeTypeHinting = false;

    bool enableSlightHinting = false;



    FT_Int32 callGetFTLoadFlags() {

        return getFTLoadFlags(type1, trueType, aa, enableFreeTypeHinting, enableSlightHinting);

    }

};



TEST_F(GetFTLoadFlagsTest_2606, DefaultFlags_2606) {

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT);

}



TEST_F(GetFTLoadFlagsTest_2606, AntiAliasingEnabled_2606) {

    aa = true;

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP);

}



TEST_F(GetFTLoadFlagsTest_2606, FreeTypeHintingDisabled_2606) {

    enableFreeTypeHinting = false;

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING);

}



TEST_F(GetFTLoadFlagsTest_2606, Type1FontWithSlightHinting_2606) {

    type1 = true;

    enableFreeTypeHinting = true;

    enableSlightHinting = true;

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT | FT_LOAD_TARGET_LIGHT);

}



TEST_F(GetFTLoadFlagsTest_2606, TrueTypeFontWithAntiAliasingAndNoAutohint_2606) {

    trueType = true;

    aa = true;

    enableFreeTypeHinting = true;

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT | FT_LOAD_NO_AUTOHINT);

}



TEST_F(GetFTLoadFlagsTest_2606, Type1FontWithoutSlightHinting_2606) {

    type1 = true;

    enableFreeTypeHinting = true;

    EXPECT_EQ(callGetFTLoadFlags(), FT_LOAD_DEFAULT | FT_LOAD_TARGET_LIGHT);

}
