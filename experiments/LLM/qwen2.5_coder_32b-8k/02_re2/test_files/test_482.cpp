#include <gtest/gtest.h>

#include "regexp.h"

#include "parse.cc"



namespace re2 {



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{kParseFlagNone, absl::string_view(""), &status};



    std::unique_ptr<Regexp> CreateRegexp(RegexpOp op) {

        return std::make_unique<Regexp>(op, kParseFlagNone);

    }



    std::unique_ptr<CharClassBuilder> CreateCCB() {

        return std::make_unique<CharClassBuilder>();

    }

};



TEST_F(ParseStateTest_482, FinishRegexpNullPtrInput_482) {

    Regexp* result = parse_state.FinishRegexp(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(ParseStateTest_482, FinishRegexpNonCharClassOp_482) {

    auto regexp = CreateRegexp(kRegexpLiteral);

    Regexp* result = parse_state.FinishRegexp(regexp.get());

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->down_, nullptr);

}



TEST_F(ParseStateTest_482, FinishRegexpCharClassWithCCB_482) {

    auto regexp = CreateRegexp(kRegexpCharClass);

    auto ccb = CreateCCB();

    regexp->ccb_ = ccb.get();



    Regexp* result = parse_state.FinishRegexp(regexp.get());

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->down_, nullptr);

    EXPECT_NE(result->cc_, nullptr);

    EXPECT_EQ(regexp->ccb_, nullptr);

}



TEST_F(ParseStateTest_482, FinishRegexpCharClassWithoutCCB_482) {

    auto regexp = CreateRegexp(kRegexpCharClass);

    Regexp* result = parse_state.FinishRegexp(regexp.get());

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->down_, nullptr);

    EXPECT_EQ(result->cc_, nullptr);

}



}  // namespace re2
