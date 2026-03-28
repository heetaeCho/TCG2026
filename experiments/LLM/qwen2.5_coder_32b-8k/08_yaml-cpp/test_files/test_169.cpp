#include <gtest/gtest.h>

#include <istream>

#include "stream.cpp" // Assuming the stream.cpp file contains the necessary implementation



namespace YAML {

    enum UtfIntroCharType { uict00 = 0, uictBB = 1, uictBF = 2, uictEF = 3, uictFE = 4, uictFF = 5, uictAscii = 6, uictOther = 7, uictMax = 8 };

}



TEST(IntroCharTypeOfTest_169, EofReturnsOther_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(std::istream::traits_type::eof()), YAML::uictOther);

}



TEST(IntroCharTypeOfTest_169, NullCharacterReturns00_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0), YAML::uict00);

}



TEST(IntroCharTypeOfTest_169, BbCharacterReturnsBB_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0xBB), YAML::uictBB);

}



TEST(IntroCharTypeOfTest_169, BfCharacterReturnsBF_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0xBF), YAML::uictBF);

}



TEST(IntroCharTypeOfTest_169, EfCharacterReturnsEF_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0xEF), YAML::uictEF);

}



TEST(IntroCharTypeOfTest_169, FeCharacterReturnsFE_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0xFE), YAML::uictFE);

}



TEST(IntroCharTypeOfTest_169, FfCharacterReturnsFF_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0xFF), YAML::uictFF);

}



TEST(IntroCharTypeOfTest_169, AsciiCharactersReturnAscii_169) {

    for (int i = 1; i < 0xFF; ++i) {

        EXPECT_EQ(YAML::IntroCharTypeOf(i), YAML::uictAscii);

    }

}



TEST(IntroCharTypeOfTest_169, CharactersAboveFFReturnOther_169) {

    EXPECT_EQ(YAML::IntroCharTypeOf(0x100), YAML::uictOther);

    EXPECT_EQ(YAML::IntroCharTypeOf(0xFFFF), YAML::uictOther);

}
