#include <gtest/gtest.h>

#include "re2/compile.cc"



using namespace re2;



class CompilerTest_294 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_294, Plus_NormalOperation_Nongreedy_294) {

    Frag a(1, PatchList::Mk(2), false);

    Frag result = compiler.Plus(a, true);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_NormalOperation_Greedy_294) {

    Frag a(1, PatchList::Mk(2), false);

    Frag result = compiler.Plus(a, false);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_NullableFragment_Nongreedy_294) {

    Frag a(1, PatchList::Mk(2), true);

    Frag result = compiler.Plus(a, true);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_NullableFragment_Greedy_294) {

    Frag a(1, PatchList::Mk(2), true);

    Frag result = compiler.Plus(a, false);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_BoundaryCondition_EmptyFrag_Nongreedy_294) {

    Frag a(0, PatchList::Mk(kNullPatchList.head), false);

    Frag result = compiler.Plus(a, true);

    EXPECT_EQ(result.begin, 0);

    EXPECT_EQ(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_BoundaryCondition_EmptyFrag_Greedy_294) {

    Frag a(0, PatchList::Mk(kNullPatchList.head), false);

    Frag result = compiler.Plus(a, false);

    EXPECT_EQ(result.begin, 0);

    EXPECT_EQ(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_294, Plus_ExceptionalCase_AllocInstFailure_294) {

    // Assuming AllocInst returns -1 on failure

    Frag a(1, PatchList::Mk(2), false);

    compiler.ninst_ = compiler.max_ninst_;

    EXPECT_EQ(compiler.Plus(a, true), compiler.NoMatch());

}



TEST_F(CompilerTest_294, Plus_ExceptionalCase_AllocInstFailure_Greedy_294) {

    // Assuming AllocInst returns -1 on failure

    Frag a(1, PatchList::Mk(2), false);

    compiler.ninst_ = compiler.max_ninst_;

    EXPECT_EQ(compiler.Plus(a, false), compiler.NoMatch());

}
