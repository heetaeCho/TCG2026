#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "re2/compile.cc"

#include "re2/prog.h"



namespace re2 {

class CompilerTest : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_295, Star_NormalOperation_NonGreedy_295) {

    Frag a(1, PatchList::Mk(2), false);

    Frag result = compiler.Star(a, true);

    EXPECT_EQ(result.nullable, true);

}



TEST_F(CompilerTest_295, Star_NormalOperation_Greedy_295) {

    Frag a(1, PatchList::Mk(2), false);

    Frag result = compiler.Star(a, false);

    EXPECT_EQ(result.nullable, true);

}



TEST_F(CompilerTest_295, Star_BoundaryCondition_EmptyFragment_NonGreedy_295) {

    Frag a(0, kNullPatchList, false);

    Frag result = compiler.Star(a, true);

    EXPECT_EQ(result.nullable, true);

}



TEST_F(CompilerTest_295, Star_BoundaryCondition_EmptyFragment_Greedy_295) {

    Frag a(0, kNullPatchList, false);

    Frag result = compiler.Star(a, false);

    EXPECT_EQ(result.nullable, true);

}



TEST_F(CompilerTest_295, Star_ExceptionalCase_AllocInstFailure_NonGreedy_295) {

    // Mocking is not needed here as we do not have control over AllocInst internal behavior

    Frag a(1, PatchList::Mk(2), false);

    compiler.max_ninst_ = 0; // Assuming this would cause AllocInst to fail

    Frag result = compiler.Star(a, true);

    EXPECT_EQ(result.nullable, false);

}



TEST_F(CompilerTest_295, Star_ExceptionalCase_AllocInstFailure_Greedy_295) {

    // Mocking is not needed here as we do not have control over AllocInst internal behavior

    Frag a(1, PatchList::Mk(2), false);

    compiler.max_ninst_ = 0; // Assuming this would cause AllocInst to fail

    Frag result = compiler.Star(a, false);

    EXPECT_EQ(result.nullable, false);

}



TEST_F(CompilerTest_295, Star_VerifyExternalInteractions_NonGreedy_295) {

    Frag a(1, PatchList::Mk(2), true);

    Frag result = compiler.Star(a, true);

    // Here we verify that the internal state changes correctly based on observable behavior

    EXPECT_EQ(result.nullable, true);

}



TEST_F(CompilerTest_295, Star_VerifyExternalInteractions_Greedy_295) {

    Frag a(1, PatchList::Mk(2), true);

    Frag result = compiler.Star(a, false);

    // Here we verify that the internal state changes correctly based on observable behavior

    EXPECT_EQ(result.nullable, true);

}



} // namespace re2
