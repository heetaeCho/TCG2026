#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/compile.cc"

#include "re2/prog.h"

#include "re2/regexp.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class MockRegexp : public Regexp {

public:

    MOCK_METHOD(int, NumCaptures, (), (const override));

};



class CompilerTest_599 : public ::testing::Test {

protected:

    void SetUp() override {

        compiler = std::make_unique<Compiler>();

    }



    std::unique_ptr<Compiler> compiler;

    MockRegexp mock_regexp;

};



TEST_F(CompilerTest_599, CompileSet_Success_599) {

    RE2::Anchor anchor = RE2::UNANCHORED;

    int64_t max_mem = 1024;



    Prog* result = Compiler::CompileSet(&mock_regexp, anchor, max_mem);

    EXPECT_NE(result, nullptr);

}



TEST_F(CompilerTest_599, Compile_Success_599) {

    bool reversed = false;

    int64_t max_mem = 1024;



    Prog* result = Compiler::Compile(&mock_regexp, reversed, max_mem);

    EXPECT_NE(result, nullptr);

}



TEST_F(CompilerTest_599, NoMatch_ReturnsValidFrag_599) {

    Frag frag = compiler->NoMatch();

    EXPECT_EQ(frag.start, -1);

    EXPECT_EQ(frag.out.ops.empty(), true);

}



TEST_F(CompilerTest_599, Match_ReturnsValidFrag_599) {

    int32_t match_id = 42;

    Frag frag = compiler->Match(match_id);



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 1);

}



TEST_F(CompilerTest_599, Nop_ReturnsValidFrag_599) {

    Frag frag = compiler->Nop();



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 1);

}



TEST_F(CompilerTest_599, ByteRange_ReturnsValidFrag_599) {

    int lo = 'a';

    int hi = 'z';

    bool foldcase = false;



    Frag frag = compiler->ByteRange(lo, hi, foldcase);



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 1);

}



TEST_F(CompilerTest_599, EmptyWidth_ReturnsValidFrag_599) {

    EmptyOp op = kEmptyWordBoundary;



    Frag frag = compiler->EmptyWidth(op);



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 1);

}



TEST_F(CompilerTest_599, Capture_ReturnsValidFrag_599) {

    Frag frag_in;

    int capture_num = 3;



    Frag frag_out = compiler->Capture(frag_in, capture_num);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Cat_ReturnsValidFrag_599) {

    Frag frag_a;

    Frag frag_b;



    Frag frag_out = compiler->Cat(frag_a, frag_b);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Alt_ReturnsValidFrag_599) {

    Frag frag_a;

    Frag frag_b;



    Frag frag_out = compiler->Alt(frag_a, frag_b);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Plus_ReturnsValidFrag_599) {

    Frag frag;

    bool nongreedy = false;



    Frag frag_out = compiler->Plus(frag, nongreedy);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Star_ReturnsValidFrag_599) {

    Frag frag;

    bool nongreedy = false;



    Frag frag_out = compiler->Star(frag, nongreedy);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Quest_ReturnsValidFrag_599) {

    Frag frag;

    bool nongreedy = false;



    Frag frag_out = compiler->Quest(frag, nongreedy);



    EXPECT_NE(frag_out.start, -1);

    EXPECT_EQ(frag_out.out.ops.size(), 2);

}



TEST_F(CompilerTest_599, Literal_ReturnsValidFrag_599) {

    Rune r = 'a';

    bool foldcase = false;



    Frag frag = compiler->Literal(r, foldcase);



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 1);

}



TEST_F(CompilerTest_599, DotStar_ReturnsValidFrag_599) {

    Frag frag = compiler->DotStar();



    EXPECT_NE(frag.start, -1);

    EXPECT_EQ(frag.out.ops.size(), 2);

}
