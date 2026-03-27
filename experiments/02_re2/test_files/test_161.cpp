#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace re2 {



class RegexpTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state here if needed.

    }



    void TearDown() override {

        // Cleanup any common state here if needed.

    }

};



TEST_F(RegexpTest_161, nrunes_ReturnsCorrectValueForLiteralString_161) {

    Rune runes[] = {'a', 'b', 'c'};

    Regexp* regexp = Regexp::LiteralString(runes, 3, 0);

    EXPECT_EQ(regexp->nrunes(), 3);

    delete regexp;

}



TEST_F(RegexpTest_161, nrunes_ThrowsAssertionForNonLiteralString_161) {

    Regexp* regexp = Regexp::NewLiteral('a', 0);

    // Since the implementation is a black box and we assume op_ is set correctly,

    // we can only test the observable behavior. If op_ is not kRegexpLiteralString,

    // nrunes() should assert or behave in an undefined way, but we can't directly

    // check for assertions in Google Test.

    EXPECT_DEATH(regexp->nrunes(), ".*");

    delete regexp;

}



TEST_F(RegexpTest_161, nrunes_ReturnsZeroForEmptyLiteralString_161) {

    Rune runes[] = {};

    Regexp* regexp = Regexp::LiteralString(runes, 0, 0);

    EXPECT_EQ(regexp->nrunes(), 0);

    delete regexp;

}



TEST_F(RegexpTest_161, nrunes_ReturnsCorrectValueForMaxRunes_161) {

    // Assuming the maximum number of runes is a reasonable large number.

    int max_runes = 1024; // Example value, adjust as necessary.

    Rune* runes = new Rune[max_runes];

    for (int i = 0; i < max_runes; ++i) {

        runes[i] = 'a';

    }

    Regexp* regexp = Regexp::LiteralString(runes, max_runes, 0);

    EXPECT_EQ(regexp->nrunes(), max_runes);

    delete[] runes;

    delete regexp;

}



} // namespace re2
