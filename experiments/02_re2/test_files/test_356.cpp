#include <gtest/gtest.h>

#include <re2/regexp.h>



using namespace re2;



class RegexpTest : public ::testing::Test {

protected:

    Regexp* ParseRegexp(const std::string& pattern) {

        RegexpStatus status;

        return Regexp::Parse(pattern, Regexp::DefaultFlags(), &status);

    }

};



TEST_F(RegexpTest_356, NumCaptures_ZeroCaptures_356) {

    Regexp* regexp = ParseRegexp("abc");

    EXPECT_EQ(regexp->NumCaptures(), 0);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_OneCapture_356) {

    Regexp* regexp = ParseRegexp("(abc)");

    EXPECT_EQ(regexp->NumCaptures(), 1);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_MultipleCaptures_356) {

    Regexp* regexp = ParseRegexp("((ab)(c(d)))");

    EXPECT_EQ(regexp->NumCaptures(), 4);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_NestedCaptures_356) {

    Regexp* regexp = ParseRegexp("(a(b(c)d))");

    EXPECT_EQ(regexp->NumCaptures(), 3);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_EmptyString_356) {

    Regexp* regexp = ParseRegexp("");

    EXPECT_EQ(regexp->NumCaptures(), 0);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_CaptureAtEnd_356) {

    Regexp* regexp = ParseRegexp("abc(def)");

    EXPECT_EQ(regexp->NumCaptures(), 1);

    delete regexp;

}



TEST_F(RegexpTest_356, NumCaptures_NoCaptureGroups_356) {

    Regexp* regexp = ParseRegexp("a|b|c");

    EXPECT_EQ(regexp->NumCaptures(), 0);

    delete regexp;

}
