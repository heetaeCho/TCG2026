#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpTest_369 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before tests (if needed)

    }



    void TearDown() override {

        // Cleanup any common state after tests (if needed)

    }

};



TEST_F(RegexpTest_369, RequiredPrefixForAccel_Literal_ReturnsTrue_369) {

    std::string prefix;

    bool foldcase;

    Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "a");

    EXPECT_FALSE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_LiteralString_ReturnsTrue_369) {

    std::string prefix;

    bool foldcase;

    Rune runes[] = {'a', 'b'};

    Regexp* re = Regexp::LiteralString(runes, 2, Regexp::NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "ab");

    EXPECT_FALSE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_NonLiteral_ReturnsFalse_369) {

    std::string prefix;

    bool foldcase;

    Regexp* re = Regexp::Star(Regexp::NewLiteral('a', Regexp::NoParseFlags), Regexp::NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_Capture_Literal_ReturnsTrue_369) {

    std::string prefix;

    bool foldcase;

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "a");

    EXPECT_FALSE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_Capture_NonLiteral_ReturnsFalse_369) {

    std::string prefix;

    bool foldcase;

    Regexp* sub = Regexp::Star(Regexp::NewLiteral('a', Regexp::NoParseFlags), Regexp::NoParseFlags);

    Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);

    EXPECT_FALSE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_Latin1_ReturnsTrueWithLatin1Conversion_369) {

    std::string prefix;

    bool foldcase;

    Regexp* re = Regexp::NewLiteral('a', Regexp::Latin1);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "a");

    EXPECT_FALSE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_FoldCase_ReturnsTrueWithFoldcaseSet_369) {

    std::string prefix;

    bool foldcase;

    Regexp* re = Regexp::NewLiteral('A', Regexp::FoldCase);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "a");

    EXPECT_TRUE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_EmptyString_ReturnsTrueWithEmptyPrefix_369) {

    std::string prefix;

    bool foldcase;

    Regexp* re = Regexp::LiteralString(nullptr, 0, Regexp::NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "");

    EXPECT_FALSE(foldcase);

    delete re;

}



TEST_F(RegexpTest_369, RequiredPrefixForAccel_MultipleCaptures_ReturnsTrueWithInnerLiteral_369) {

    std::string prefix;

    bool foldcase;

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* sub2 = Regexp::Capture(sub1, Regexp::NoParseFlags, 1);

    Regexp* re = Regexp::Concat(&sub2, 1, Regexp::NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));

    EXPECT_EQ(prefix, "a");

    EXPECT_FALSE(foldcase);

    delete re;

}
