#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



TEST(Utf8_ByteOrderMarkTest_127, MatchesValidUtf8Bom_127) {

    const RegEx& utf8_bom = Utf8_ByteOrderMark();

    EXPECT_TRUE(utf8_bom.Matches("\xEF\xBB\xBF"));

}



TEST(Utf8_ByteOrderMarkTest_127, DoesNotMatchEmptyString_127) {

    const RegEx& utf8_bom = Utf8_ByteOrderMark();

    EXPECT_FALSE(utf8_bom.Matches(""));

}



TEST(Utf8_ByteOrderMarkTest_127, DoesNotMatchShorterSequence_127) {

    const RegEx& utf8_bom = Utf8_ByteOrderMark();

    EXPECT_FALSE(utf8_bom.Matches("\xEF\xBB"));

}



TEST(Utf8_ByteOrderMarkTest_127, DoesNotMatchLongerSequence_127) {

    const RegEx& utf8_bom = Utf8_ByteOrderMark();

    EXPECT_FALSE(utf8_bom.Matches("\xEF\xBB\xBF\x00"));

}



TEST(Utf8_ByteOrderMarkTest_127, DoesNotMatchDifferentBytes_127) {

    const RegEx& utf8_bom = Utf8_ByteOrderMark();

    EXPECT_FALSE(utf8_bom.Matches("\x00\x00\x00"));

}
