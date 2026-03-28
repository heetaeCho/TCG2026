#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"

#include "re2/regexp.h"

#include "re2/compile.cc"



using namespace re2;

using ::testing::NiceMock;



class MockRegexp : public Regexp {

public:

    MOCK_METHOD(bool, RequiredPrefixForAccel, (std::string*, bool*), (const, override));

};



class CompilerTest_326 : public ::testing::Test {

protected:

    void SetUp() override {

        compiler = std::make_unique<Compiler>();

        mock_regexp = new NiceMock<MockRegexp>(RegexpOp::kEmpty, Regexp::ParseFlags(0));

    }



    void TearDown() override {

        delete mock_regexp;

    }



    std::unique_ptr<Compiler> compiler;

    MockRegexp* mock_regexp;

};



TEST_F(CompilerTest_326, Finish_ReturnsNullWhenFailed_326) {

    compiler->failed_ = true;

    EXPECT_EQ(compiler->Finish(mock_regexp), nullptr);

}



TEST_F(CompilerTest_326, Finish_SetsStartAndUnanchoredStartCorrectly_326) {

    compiler->prog_->set_start(0);

    compiler->prog_->set_start_unanchored(0);



    Prog* result = compiler->Finish(mock_regexp);

    EXPECT_EQ(result->start(), 1);

    EXPECT_EQ(result->start_unanchored(), 1);

}



TEST_F(CompilerTest_326, Finish_ConfiguresPrefixAccelWhenRequired_326) {

    std::string prefix = "abc";

    bool prefix_foldcase = false;

    ON_CALL(*mock_regexp, RequiredPrefixForAccel(::testing::_, ::testing::_))

        .WillByDefault([prefix, &prefix_foldcase](std::string* p_prefix, bool* p_foldcase) {

            *p_prefix = prefix;

            *p_foldcase = prefix_foldcase;

            return true;

        });



    compiler->Finish(mock_regexp);

    EXPECT_EQ(std::string(compiler->prog_->PrefixAccel(nullptr, 0)), "abc");

}



TEST_F(CompilerTest_326, Finish_CalculatesDfaMemCorrectly_326) {

    compiler->max_mem_ = 1024;

    compiler->ninst_ = 5;

    compiler->prog_->set_dfa_mem(0);



    Prog* result = compiler->Finish(mock_regexp);

    int64_t expected_dfa_mem = 1024 - sizeof(Prog) - (5 * sizeof(Prog::Inst)) - (5 * sizeof(uint16_t));

    EXPECT_EQ(result->dfa_mem(), expected_dfa_mem > 0 ? expected_dfa_mem : 0);

}



TEST_F(CompilerTest_326, Finish_DoesNotConfigurePrefixAccelWhenNotRequired_326) {

    ON_CALL(*mock_regexp, RequiredPrefixForAccel(::testing::_, ::testing::_))

        .WillByDefault([](::testing::Unused, bool* p_foldcase) { *p_foldcase = false; return false; });



    compiler->Finish(mock_regexp);

    EXPECT_EQ(compiler->prog_->prefix_size_, 0);

}



TEST_F(CompilerTest_326, Finish_HandlesMaxMemLessThanMinimum_326) {

    compiler->max_mem_ = -1;

    compiler->prog_->set_dfa_mem(0);



    Prog* result = compiler->Finish(mock_regexp);

    EXPECT_EQ(result->dfa_mem(), 1 << 20);

}



TEST_F(CompilerTest_326, Finish_HandlesDfaMemNegative_326) {

    compiler->max_mem_ = sizeof(Prog) + (5 * sizeof(Prog::Inst)) + (5 * sizeof(uint16_t));

    compiler->ninst_ = 5;

    compiler->prog_->set_dfa_mem(0);



    Prog* result = compiler->Finish(mock_regexp);

    EXPECT_EQ(result->dfa_mem(), 0);

}
