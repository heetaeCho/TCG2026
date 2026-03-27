#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class RegexpTest_347 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RegexpTest_347, LiteralString_ZeroRunes_ReturnsEmptyMatch_347) {

    Rune runes[] = {};

    ParseFlags flags = 0;

    Regexp* result = Regexp::LiteralString(runes, 0, flags);

    EXPECT_EQ(result->op(), kRegexpEmptyMatch);

    delete result;

}



TEST_F(RegexpTest_347, LiteralString_OneRune_ReturnsLiteral_347) {

    Rune runes[] = {'a'};

    ParseFlags flags = 0;

    Regexp* result = Regexp::LiteralString(runes, 1, flags);

    EXPECT_EQ(result->op(), kRegexpLiteral);

    delete result;

}



TEST_F(RegexpTest_347, LiteralString_MultipleRunes_ReturnsLiteralString_347) {

    Rune runes[] = {'a', 'b', 'c'};

    ParseFlags flags = 0;

    Regexp* result = Regexp::LiteralString(runes, 3, flags);

    EXPECT_EQ(result->op(), kRegexpLiteralString);

    delete result;

}



TEST_F(RegexpTest_347, LiteralString_NegativeRunes_ReturnsNull_347) {

    Rune runes[] = {'a', 'b', 'c'};

    ParseFlags flags = 0;

    Regexp* result = Regexp::LiteralString(runes, -1, flags);

    EXPECT_EQ(result->op(), kRegexpEmptyMatch);

    delete result;

}



TEST_F(RegexpTest_347, LiteralString_Incref_Decref_347) {

    Rune runes[] = {'a', 'b', 'c'};

    ParseFlags flags = 0;

    Regexp* result = Regexp::LiteralString(runes, 3, flags);

    int ref_count_before = result->Ref();

    result->Incref();

    EXPECT_EQ(result->Ref(), ref_count_before + 1);

    result->Decref();

    EXPECT_EQ(result->Ref(), ref_count_before);

    delete result;

}



} // namespace re2
