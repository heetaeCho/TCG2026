#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/compile.cc"



using namespace re2;



class CompilerTest_301 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_301, Capture_ReturnsNoMatch_WhenInputIsNoMatch_301) {

    Frag input = compiler.NoMatch();

    Frag result = compiler.Capture(input, 1);

    EXPECT_EQ(result.begin, 0u);

    EXPECT_EQ(result.end.head, 0u);

    EXPECT_EQ(result.nullable, false);

}



TEST_F(CompilerTest_301, Capture_ReturnsValidFrag_WhenInputIsValid_301) {

    Frag input = Frag(1, PatchList::Mk(2), true);

    Frag result = compiler.Capture(input, 1);

    EXPECT_NE(result.begin, 0u);

    EXPECT_NE(result.end.head, 0u);

}



TEST_F(CompilerTest_301, Capture_AllocatesTwoInstructions_WhenInputIsValid_301) {

    Frag input = Frag(1, PatchList::Mk(2), true);

    Frag result = compiler.Capture(input, 1);

    EXPECT_EQ(result.begin + 1, result.end.head >> 1);

}



TEST_F(CompilerTest_301, Capture_SetsCaptureInstructionsCorrectly_WhenInputIsValid_301) {

    Frag input = Frag(1, PatchList::Mk(2), true);

    Frag result = compiler.Capture(input, 1);

    Prog::Inst& inst1 = compiler.inst_[result.begin];

    Prog::Inst& inst2 = compiler.inst_[result.end.head >> 1];



    EXPECT_EQ(inst1.cap(), 2);

    EXPECT_EQ(inst1.out(), input.begin);



    EXPECT_EQ(inst2.cap(), 3);

    EXPECT_EQ(inst2.out(), 0);

}



TEST_F(CompilerTest_301, Capture_PatchesEndListCorrectly_WhenInputIsValid_301) {

    Frag input = Frag(1, PatchList::Mk(2), true);

    Frag result = compiler.Capture(input, 1);



    EXPECT_EQ(compiler.inst_[input.end.head >> 1].out(), (result.end.head >> 1));

}



TEST_F(CompilerTest_301, Capture_HandlesLargeCaptureIndex_WhenInputIsValid_301) {

    Frag input = Frag(1, PatchList::Mk(2), true);

    int large_index = 65535;

    Frag result = compiler.Capture(input, large_index);



    Prog::Inst& inst1 = compiler.inst_[result.begin];

    Prog::Inst& inst2 = compiler.inst_[result.end.head >> 1];



    EXPECT_EQ(inst1.cap(), 2 * large_index);

    EXPECT_EQ(inst2.cap(), 2 * large_index + 1);

}
