#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "TestProjects/re2/re2/compile.cc"

#include "TestProjects/re2/re2/prog.h"



using namespace re2;



class CompilerFixture_311 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before tests

        prog = new Prog();

        compiler = new Compiler();

        compiler->prog_ = prog;

    }



    void TearDown() override {

        delete compiler;

        delete prog;

    }



    Prog* prog;

    Compiler* compiler;

};



TEST_F(CompilerFixture_311, FindByteRange_MatchesByteRange_311) {

    int root = compiler->AllocInst(1);

    prog->inst_[root].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 70); // 'F'

    EXPECT_EQ(result.start(), root);

}



TEST_F(CompilerFixture_311, FindByteRange_OutOfRange_311) {

    int root = compiler->AllocInst(1);

    prog->inst_[root].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 91); // ']'

    EXPECT_EQ(result.start(), -1);

}



TEST_F(CompilerFixture_311, FindByteRange_ReversedMode_MatchesAlt_311) {

    compiler->reversed_ = true;

    int root = compiler->AllocInst(2);

    prog->inst_[root].InitAlt(root + 1, kNullPatchList.head);

    prog->inst_[root + 1].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 70); // 'F'

    EXPECT_EQ(result.start(), root + 1);

}



TEST_F(CompilerFixture_311, FindByteRange_ReversedMode_OutOfRange_311) {

    compiler->reversed_ = true;

    int root = compiler->AllocInst(2);

    prog->inst_[root].InitAlt(root + 1, kNullPatchList.head);

    prog->inst_[root + 1].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 91); // ']'

    EXPECT_EQ(result.start(), -1);

}



TEST_F(CompilerFixture_311, FindByteRange_NonAltOpcode_311) {

    int root = compiler->AllocInst(1);

    prog->inst_[root].InitCapture(1, kNullPatchList.head);



    Frag result = compiler->FindByteRange(root, 70); // 'F'

    EXPECT_EQ(result.start(), -1);

}



TEST_F(CompilerFixture_311, FindByteRange_EmptyAltChain_311) {

    int root = compiler->AllocInst(2);

    prog->inst_[root].InitAlt(root + 1, kNullPatchList.head);

    prog->inst_[root + 1].InitNop(kNullPatchList.head);



    Frag result = compiler->FindByteRange(root, 70); // 'F'

    EXPECT_EQ(result.start(), -1);

}



TEST_F(CompilerFixture_311, FindByteRange_DeepAltChain_Matches_311) {

    int root = compiler->AllocInst(4);

    prog->inst_[root].InitAlt(root + 1, kNullPatchList.head);

    prog->inst_[root + 1].InitNop(kNullPatchList.head);

    prog->inst_[root + 2].InitAlt(root + 3, kNullPatchList.head);

    prog->inst_[root + 3].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 70); // 'F'

    EXPECT_EQ(result.start(), root + 3);

}



TEST_F(CompilerFixture_311, FindByteRange_DeepAltChain_OutOfRange_311) {

    int root = compiler->AllocInst(4);

    prog->inst_[root].InitAlt(root + 1, kNullPatchList.head);

    prog->inst_[root + 1].InitNop(kNullPatchList.head);

    prog->inst_[root + 2].InitAlt(root + 3, kNullPatchList.head);

    prog->inst_[root + 3].InitByteRange(65, 90, 0, kNullPatchList.head); // A-Z



    Frag result = compiler->FindByteRange(root, 91); // ']'

    EXPECT_EQ(result.start(), -1);

}
