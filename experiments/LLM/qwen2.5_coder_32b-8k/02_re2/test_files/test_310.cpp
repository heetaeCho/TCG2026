#include <gtest/gtest.h>

#include "re2/compile.h"

#include "re2/prog.h"



namespace re2 {



class CompilerTest_310 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

        compiler = new Compiler();

    }



    void TearDown() override {

        delete compiler;

        delete prog;

    }



    Prog* prog;

    Compiler* compiler;

};



TEST_F(CompilerTest_310, ByteRangeEqual_SameRanges_310) {

    int id1 = compiler->AllocInst(1);

    int id2 = compiler->AllocInst(1);



    prog->inst_[id1].InitByteRange(10, 20, false, 0);

    prog->inst_[id2].InitByteRange(10, 20, false, 0);



    EXPECT_TRUE(compiler->ByteRangeEqual(id1, id2));

}



TEST_F(CompilerTest_310, ByteRangeEqual_DifferentRanges_310) {

    int id1 = compiler->AllocInst(1);

    int id2 = compiler->AllocInst(1);



    prog->inst_[id1].InitByteRange(10, 20, false, 0);

    prog->inst_[id2].InitByteRange(30, 40, false, 0);



    EXPECT_FALSE(compiler->ByteRangeEqual(id1, id2));

}



TEST_F(CompilerTest_310, ByteRangeEqual_SameRangesWithFoldCase_310) {

    int id1 = compiler->AllocInst(1);

    int id2 = compiler->AllocInst(1);



    prog->inst_[id1].InitByteRange(10, 20, true, 0);

    prog->inst_[id2].InitByteRange(10, 20, true, 0);



    EXPECT_TRUE(compiler->ByteRangeEqual(id1, id2));

}



TEST_F(CompilerTest_310, ByteRangeEqual_DifferentFoldCase_310) {

    int id1 = compiler->AllocInst(1);

    int id2 = compiler->AllocInst(1);



    prog->inst_[id1].InitByteRange(10, 20, false, 0);

    prog->inst_[id2].InitByteRange(10, 20, true, 0);



    EXPECT_FALSE(compiler->ByteRangeEqual(id1, id2));

}



TEST_F(CompilerTest_310, ByteRangeEqual_OutOfBounds_310) {

    int id1 = compiler->AllocInst(1);

    int id2 = compiler->AllocInst(2); // Out of bounds as size is 1



    prog->inst_[id1].InitByteRange(10, 20, false, 0);



    EXPECT_FALSE(compiler->ByteRangeEqual(id1, id2));

}



} // namespace re2
