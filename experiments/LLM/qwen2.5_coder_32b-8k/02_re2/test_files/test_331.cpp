#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"

#include "re2/regexp.h"



using namespace re2;



class ProgTest_331 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary preconditions here

    }



    void TearDown() override {

        // Cleanup actions can go here

    }

};



TEST_F(ProgTest_331, CompileSet_ReturnsNonNullPtr_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = re->CompileToProg(1024);

    EXPECT_NE(prog, nullptr);



    prog->Decref();

    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_AnchorStart_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_START, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());



    prog->Decref();

    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_AnchorEnd_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_END, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_end());



    prog->Decref();

    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_AnchorBoth_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_TRUE(prog->anchor_start());

    EXPECT_TRUE(prog->anchor_end());



    prog->Decref();

    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_AnchorNone_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1024);

    EXPECT_NE(prog, nullptr);

    EXPECT_FALSE(prog->anchor_start());

    EXPECT_FALSE(prog->anchor_end());



    prog->Decref();

    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_MaxMemZero_ReturnsNullPtr_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 0);

    EXPECT_EQ(prog, nullptr);



    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_MaxMemNegative_ReturnsNullPtr_331) {

    Regexp* re = Regexp::Parse("abc", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, -1024);

    EXPECT_EQ(prog, nullptr);



    re->Decref();

}



TEST_F(ProgTest_331, CompileSet_ComplexPattern_331) {

    Regexp* re = Regexp::Parse("(abc|def)+", Regexp::Simple, nullptr);

    ASSERT_NE(re, nullptr);



    Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1024);

    EXPECT_NE(prog, nullptr);



    prog->Decref();

    re->Decref();

}
