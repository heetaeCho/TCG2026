#include <gtest/gtest.h>

#include "re2/compile.cc"

#include "re2/prog.h"



using namespace re2;



class CompilerTest_292 : public ::testing::Test {

protected:

    void SetUp() override {

        compiler = new Compiler();

    }



    void TearDown() override {

        delete compiler;

    }



    Compiler* compiler;

};



TEST_F(CompilerTest_292, CatNormalOperation_292) {

    Frag a(1, PatchList::Mk(3), false);

    Frag b(4, PatchList::Mk(5), true);



    Frag result = compiler->Cat(a, b);

    

    EXPECT_EQ(result.begin, 1);

    EXPECT_EQ(result.end.head, 5);

    EXPECT_FALSE(result.nullable);

}



TEST_F(CompilerTest_292, CatNoMatchA_292) {

    Frag a = compiler->NoMatch();

    Frag b(4, PatchList::Mk(5), true);



    Frag result = compiler->Cat(a, b);

    

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_292, CatNoMatchB_292) {

    Frag a(1, PatchList::Mk(3), false);

    Frag b = compiler->NoMatch();



    Frag result = compiler->Cat(a, b);

    

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_292, CatBothNoMatch_292) {

    Frag a = compiler->NoMatch();

    Frag b = compiler->NoMatch();



    Frag result = compiler->Cat(a, b);

    

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_292, CatNopInstructionReversed_292) {

    compiler->reversed_ = true;

    Prog::Inst* inst = new Prog::Inst();

    inst->InitNop(0);

    compiler->inst_[1] = *inst;



    Frag a(1, PatchList::Mk(3), false);

    Frag b(4, PatchList::Mk(5), true);



    Frag result = compiler->Cat(a, b);

    

    EXPECT_EQ(result.begin, 4);

    EXPECT_EQ(result.end.head, 3);

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_292, CatNopInstructionNotReversed_292) {

    compiler->reversed_ = false;

    Prog::Inst* inst = new Prog::Inst();

    inst->InitNop(0);

    compiler->inst_[1] = *inst;



    Frag a(1, PatchList::Mk(3), false);

    Frag b(4, PatchList::Mk(5), true);



    Frag result = compiler->Cat(a, b);

    

    EXPECT_EQ(result.begin, 1);

    EXPECT_EQ(result.end.head, 5);

    EXPECT_FALSE(result.nullable);

}
