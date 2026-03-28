#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest_290 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_290, NoMatch_ReturnsDefaultFrag_290) {

    Frag result = compiler.NoMatch();

    // Assuming default constructed Frag has some known state that can be verified

    EXPECT_EQ(result.start, -1);

    EXPECT_EQ(result.out_.size(), 0);

}



TEST_F(CompilerTest_290, Cat_ReturnsCombinedFrag_290) {

    Frag fragA = compiler.NoMatch();

    Frag fragB = compiler.NoMatch();

    Frag result = compiler.Cat(fragA, fragB);

    // Assuming Cat combines the fragments in a way that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Alt_ReturnsAlternativeFrag_290) {

    Frag fragA = compiler.NoMatch();

    Frag fragB = compiler.NoMatch();

    Frag result = compiler.Alt(fragA, fragB);

    // Assuming Alt creates an alternative fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Plus_ReturnsPlusFrag_290) {

    Frag frag = compiler.NoMatch();

    Frag result = compiler.Plus(frag, false);

    // Assuming Plus creates a plus fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Star_ReturnsStarFrag_290) {

    Frag frag = compiler.NoMatch();

    Frag result = compiler.Star(frag, false);

    // Assuming Star creates a star fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Quest_ReturnsQuestFrag_290) {

    Frag frag = compiler.NoMatch();

    Frag result = compiler.Quest(frag, false);

    // Assuming Quest creates a quest fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Capture_ReturnsCapturedFrag_290) {

    Frag frag = compiler.NoMatch();

    Frag result = compiler.Capture(frag, 1);

    // Assuming Capture creates a captured fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, ByteRange_ReturnsByteRangeFrag_290) {

    Frag result = compiler.ByteRange(0, 255, false);

    // Assuming ByteRange creates a byte range fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, Nop_ReturnsNopFrag_290) {

    Frag result = compiler.Nop();

    // Assuming Nop creates a nop fragment that can be verified

    EXPECT_EQ(result.start, -1);

}



TEST_F(CompilerTest_290, Match_ReturnsMatchFrag_290) {

    Frag result = compiler.Match(0);

    // Assuming Match creates a match fragment that can be verified

    EXPECT_NE(result.start, -1);

}



TEST_F(CompilerTest_290, EmptyWidth_ReturnsEmptyWidthFrag_290) {

    Frag result = compiler.EmptyWidth(EmptyOp::kNone);

    // Assuming EmptyWidth creates an empty width fragment that can be verified

    EXPECT_NE(result.start, -1);

}



}  // namespace re2
