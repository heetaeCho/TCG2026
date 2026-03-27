#include <gtest/gtest.h>

#include "re2/compile.cc"

#include "re2/prog.h"



namespace re2 {



class CompilerTest_296 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_296, Quest_NonGreedy_Success_296) {

    Frag a(1, PatchList::Mk(0), false);

    Frag result = compiler.Quest(a, true);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_296, Quest_Greedy_Success_296) {

    Frag a(1, PatchList::Mk(0), false);

    Frag result = compiler.Quest(a, false);

    EXPECT_EQ(result.begin, 1);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_296, Quest_EmptyFrag_NonGreedy_Success_296) {

    Frag a(0, kNullPatchList, true);

    Frag result = compiler.Quest(a, true);

    EXPECT_EQ(result.begin, 0);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_296, Quest_EmptyFrag_Greedy_Success_296) {

    Frag a(0, kNullPatchList, true);

    Frag result = compiler.Quest(a, false);

    EXPECT_EQ(result.begin, 0);

    EXPECT_NE(result.end.head, kNullPatchList.head);

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_296, Quest_AllocInstFailure_ReturnsNoMatch_296) {

    Frag a(1, PatchList::Mk(0), false);

    compiler.ninst_ = compiler.max_ninst_;  // Force AllocInst to fail

    Frag result = compiler.Quest(a, true);

    EXPECT_EQ(result.begin, kInvalidInstId);

}



TEST_F(CompilerTest_296, Quest_AllocInstFailure_ReturnsNoMatch_296) {

    Frag a(1, PatchList::Mk(0), false);

    compiler.ninst_ = compiler.max_ninst_;  // Force AllocInst to fail

    Frag result = compiler.Quest(a, false);

    EXPECT_EQ(result.begin, kInvalidInstId);

}



TEST_F(CompilerTest_296, Quest_NoMatch_ReturnsNoMatch_296) {

    Frag a(kInvalidInstId, PatchList::Mk(0), false);

    Frag result = compiler.Quest(a, true);

    EXPECT_EQ(result.begin, kInvalidInstId);

}



}  // namespace re2
