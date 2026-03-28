#include <gtest/gtest.h>

#include "re2/compile.cc"

#include "re2/prog.h"



namespace re2 {



class CompilerTest_297 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_297, ByteRange_NormalOperation_297) {

    Frag frag = compiler.ByteRange('a', 'z', false);

    EXPECT_GE(frag.id_, 0);

}



TEST_F(CompilerTest_297, ByteRange_BoundaryConditions_LowerBound_297) {

    Frag frag = compiler.ByteRange(0, 0, false);

    EXPECT_GE(frag.id_, 0);

}



TEST_F(CompilerTest_297, ByteRange_BoundaryConditions_UpperBound_297) {

    Frag frag = compiler.ByteRange(255, 255, false);

    EXPECT_GE(frag.id_, 0);

}



TEST_F(CompilerTest_297, ByteRange_ExceptionalCase_OutOfBounds_297) {

    Frag frag = compiler.ByteRange(-1, -1, false);

    EXPECT_EQ(frag.id_, -1); // Assuming NoMatch() returns a Frag with id -1

}



TEST_F(CompilerTest_297, ByteRange_FoldcaseEnabled_297) {

    Frag frag = compiler.ByteRange('A', 'Z', true);

    EXPECT_GE(frag.id_, 0);

}



TEST_F(CompilerTest_297, ByteRange_FoldcaseDisabled_297) {

    Frag frag = compiler.ByteRange('A', 'Z', false);

    EXPECT_GE(frag.id_, 0);

}



} // namespace re2
