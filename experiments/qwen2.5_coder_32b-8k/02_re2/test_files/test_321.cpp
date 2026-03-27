#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/compile.cc"



using namespace re2;

using ::testing::Eq;



class CompilerTest_321 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_321, PostVisit_NoMatchOp_ReturnsNoMatch_321) {

    Regexp re(kRegexpNoMatch);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragNone); // Assuming NoMatch() returns a Frag with op_ set to kFragNone

}



TEST_F(CompilerTest_321, PostVisit_EmptyMatchOp_ReturnsNop_321) {

    Regexp re(kRegexpEmptyMatch);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragCat); // Assuming Nop() returns a Frag with op_ set to kFragCat

}



TEST_F(CompilerTest_321, PostVisit_HaveMatchOp_ReturnsMatchWithAnchorBoth_321) {

    Regexp re(kRegexpHaveMatch);

    re.set_match_id(1);

    compiler.anchor_ = RE2::ANCHOR_BOTH;

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragCat); // Assuming the result is a concatenation of two frags

}



TEST_F(CompilerTest_321, PostVisit_ConcatOp_TwoChildren_ReturnsConcatenatedFrags_321) {

    Regexp re(kRegexpConcat);

    Frag child_frags[2] = {Frag(), Frag()};

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), child_frags, 2);

    EXPECT_EQ(result.op_, kFragCat); // Assuming Cat() returns a Frag with op_ set to kFragCat

}



TEST_F(CompilerTest_321, PostVisit_AlternateOp_TwoChildren_ReturnsAlternatedFrags_321) {

    Regexp re(kRegexpAlternate);

    Frag child_frags[2] = {Frag(), Frag()};

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), child_frags, 2);

    EXPECT_EQ(result.op_, kFragAlt); // Assuming Alt() returns a Frag with op_ set to kFragAlt

}



TEST_F(CompilerTest_321, PostVisit_StarOp_ReturnsStarFragment_321) {

    Regexp re(kRegexpStar);

    Frag child_frag = Frag();

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), &child_frag, 1);

    EXPECT_EQ(result.op_, kFragStar); // Assuming Star() returns a Frag with op_ set to kFragStar

}



TEST_F(CompilerTest_321, PostVisit_PlusOp_ReturnsPlusFragment_321) {

    Regexp re(kRegexpPlus);

    Frag child_frag = Frag();

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), &child_frag, 1);

    EXPECT_EQ(result.op_, kFragPlus); // Assuming Plus() returns a Frag with op_ set to kFragPlus

}



TEST_F(CompilerTest_321, PostVisit_QuestOp_ReturnsQuestFragment_321) {

    Regexp re(kRegexpQuest);

    Frag child_frag = Frag();

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), &child_frag, 1);

    EXPECT_EQ(result.op_, kFragQuest); // Assuming Quest() returns a Frag with op_ set to kFragQuest

}



TEST_F(CompilerTest_321, PostVisit_LiteralOp_ReturnsLiteralFragment_321) {

    Regexp re(kRegexpLiteral);

    re.set_rune('a');

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragLiteral); // Assuming Literal() returns a Frag with op_ set to kFragLiteral

}



TEST_F(CompilerTest_321, PostVisit_LiteralStringOp_EmptyString_ReturnsNop_321) {

    Regexp re(kRegexpLiteralString);

    re.set_nrunes(0);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragCat); // Assuming Nop() returns a Frag with op_ set to kFragCat

}



TEST_F(CompilerTest_321, PostVisit_LiteralStringOp_NonEmptyString_ReturnsConcatenatedLiterals_321) {

    Regexp re(kRegexpLiteralString);

    Rune runes[] = {'a', 'b'};

    re.set_runes(runes);

    re.set_nrunes(2);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragCat); // Assuming the result is a concatenation of two frags

}



TEST_F(CompilerTest_321, PostVisit_AnyCharOp_ReturnsRangeFragment_321) {

    Regexp re(kRegexpAnyChar);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragMatchRune); // Assuming EndRange() returns a Frag with op_ set to kFragMatchRune

}



TEST_F(CompilerTest_321, PostVisit_AnyByteOp_ReturnsByteRangeFragment_321) {

    Regexp re(kRegexpAnyByte);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragMatchRune); // Assuming ByteRange() returns a Frag with op_ set to kFragMatchRune

}



TEST_F(CompilerTest_321, PostVisit_CharClassOp_EmptyCharClass_ReturnsNoMatch_321) {

    Regexp re(kRegexpCharClass);

    CharClass cc;

    re.set_cc(&cc);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragNone); // Assuming NoMatch() returns a Frag with op_ set to kFragNone

}



TEST_F(CompilerTest_321, PostVisit_CharClassOp_NonEmptyCharClass_ReturnsRangeFragment_321) {

    Regexp re(kRegexpCharClass);

    CharClass cc;

    cc.AddInterval(CharInterval('a', 'z'));

    re.set_cc(&cc);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragMatchRune); // Assuming EndRange() returns a Frag with op_ set to kFragMatchRune

}



TEST_F(CompilerTest_321, PostVisit_CaptureOp_NoCapture_ReturnsChildFragment_321) {

    Regexp re(kRegexpCapture);

    re.set_cap(-1);

    Frag child_frag = Frag();

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), &child_frag, 1);

    EXPECT_EQ(result.op_, kFragNone); // Assuming the child fragment is returned as-is

}



TEST_F(CompilerTest_321, PostVisit_CaptureOp_WithCapture_ReturnsCapturedFragment_321) {

    Regexp re(kRegexpCapture);

    re.set_cap(1);

    Frag child_frag = Frag();

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), &child_frag, 1);

    EXPECT_EQ(result.op_, kFragCap); // Assuming Capture() returns a Frag with op_ set to kFragCap

}



TEST_F(CompilerTest_321, PostVisit_BeginLineOp_ReturnsEmptyWidthFragment_321) {

    Regexp re(kRegexpBeginLine);

    compiler.reversed_ = false;

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}



TEST_F(CompilerTest_321, PostVisit_EndLineOp_ReturnsEmptyWidthFragment_321) {

    Regexp re(kRegexpEndLine);

    compiler.reversed_ = false;

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}



TEST_F(CompilerTest_321, PostVisit_BeginTextOp_ReturnsEmptyWidthFragment_321) {

    Regexp re(kRegexpBeginText);

    compiler.reversed_ = false;

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}



TEST_F(CompilerTest_321, PostVisit_EndTextOp_ReturnsEmptyWidthFragment_321) {

    Regexp re(kRegexpEndText);

    compiler.reversed_ = false;

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}



TEST_F(CompilerTest_321, PostVisit_WordBoundaryOp_ReturnsWordBoundaryFragment_321) {

    Regexp re(kRegexpWordBoundary);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}



TEST_F(CompilerTest_321, PostVisit_NoWordBoundaryOp_ReturnsNoWordBoundaryFragment_321) {

    Regexp re(kRegexpNoWordBoundary);

    Frag result = compiler.PostVisit(&re, Frag(), Frag(), nullptr, 0);

    EXPECT_EQ(result.op_, kFragEmptyWidth); // Assuming EmptyWidth() returns a Frag with op_ set to kFragEmptyWidth

}
