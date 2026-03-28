#include <gtest/gtest.h>

#include "re2/compile.cc"

#include "re2/prog.h"



using namespace re2;



class CompilerTest : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_EmptyWidth_300, NormalOperation_ReturnsValidFrag_300) {

    Frag result = compiler.EmptyWidth(kEmptyWordBoundary);

    EXPECT_GE(result.start_, 0);

}



TEST_F(CompilerTest_EmptyWidth_300, BoundaryCondition_ZeroNinst_ReturnsNoMatch_300) {

    compiler.ninst_ = 0;

    compiler.max_ninst_ = 0;

    Frag result = compiler.EmptyWidth(kEmptyWordBoundary);

    EXPECT_EQ(result.start_, -1);

}



TEST_F(CompilerTest_EmptyWidth_300, BoundaryCondition_MaxNinst_ReturnsValidFrag_300) {

    compiler.ninst_ = compiler.max_ninst_ - 1;

    Frag result = compiler.EmptyWidth(kEmptyWordBoundary);

    EXPECT_GE(result.start_, 0);

}



TEST_F(CompilerTest_EmptyWidth_300, BoundaryCondition_ExceedMaxNinst_ReturnsNoMatch_300) {

    compiler.ninst_ = compiler.max_ninst_;

    Frag result = compiler.EmptyWidth(kEmptyWordBoundary);

    EXPECT_EQ(result.start_, -1);

}
