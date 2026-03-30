#include <gtest/gtest.h>

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



TEST(ParseFlagsTest_171, TestNoParseFlagsComplement_171) {

    EXPECT_EQ(~Regexp::NoParseFlags, Regexp::AllParseFlags);

}



TEST(ParseFlagsTest_171, TestFoldCaseComplement_171) {

    EXPECT_EQ(~Regexp::FoldCase, Regexp::AllParseFlags ^ Regexp::FoldCase);

}



TEST(ParseFlagsTest_171, TestLiteralComplement_171) {

    EXPECT_EQ(~Regexp::Literal, Regexp::AllParseFlags ^ Regexp::Literal);

}



TEST(ParseFlagsTest_171, TestClassNLComplement_171) {

    EXPECT_EQ(~Regexp::ClassNL, Regexp::AllParseFlags ^ Regexp::ClassNL);

}



TEST(ParseFlagsTest_171, TestDotNLComplement_171) {

    EXPECT_EQ(~Regexp::DotNL, Regexp::AllParseFlags ^ Regexp::DotNL);

}



TEST(ParseFlagsTest_171, TestMatchNLComplement_171) {

    EXPECT_EQ(~Regexp::MatchNL, Regexp::AllParseFlags ^ Regexp::MatchNL);

}



TEST(ParseFlagsTest_171, TestOneLineComplement_171) {

    EXPECT_EQ(~Regexp::OneLine, Regexp::AllParseFlags ^ Regexp::OneLine);

}



TEST(ParseFlagsTest_171, TestLatin1Complement_171) {

    EXPECT_EQ(~Regexp::Latin1, Regexp::AllParseFlags ^ Regexp::Latin1);

}



TEST(ParseFlagsTest_171, TestNonGreedyComplement_171) {

    EXPECT_EQ(~Regexp::NonGreedy, Regexp::AllParseFlags ^ Regexp::NonGreedy);

}



TEST(ParseFlagsTest_171, TestPerlClassesComplement_171) {

    EXPECT_EQ(~Regexp::PerlClasses, Regexp::AllParseFlags ^ Regexp::PerlClasses);

}



TEST(ParseFlagsTest_171, TestPerlBComplement_171) {

    EXPECT_EQ(~Regexp::PerlB, Regexp::AllParseFlags ^ Regexp::PerlB);

}



TEST(ParseFlagsTest_171, TestPerlXComplement_171) {

    EXPECT_EQ(~Regexp::PerlX, Regexp::AllParseFlags ^ Regexp::PerlX);

}



TEST(ParseFlagsTest_171, TestUnicodeGroupsComplement_171) {

    EXPECT_EQ(~Regexp::UnicodeGroups, Regexp::AllParseFlags ^ Regexp::UnicodeGroups);

}



TEST(ParseFlagsTest_171, TestNeverNLComplement_171) {

    EXPECT_EQ(~Regexp::NeverNL, Regexp::AllParseFlags ^ Regexp::NeverNL);

}



TEST(ParseFlagsTest_171, TestNeverCaptureComplement_171) {

    EXPECT_EQ(~Regexp::NeverCapture, Regexp::AllParseFlags ^ Regexp::NeverCapture);

}



TEST(ParseFlagsTest_171, TestWasDollarComplement_171) {

    EXPECT_EQ(~Regexp::WasDollar, Regexp::AllParseFlags ^ Regexp::WasDollar);

}



TEST(ParseFlagsTest_171, TestAllParseFlagsComplement_171) {

    EXPECT_EQ(~Regexp::AllParseFlags, Regexp::NoParseFlags);

}
