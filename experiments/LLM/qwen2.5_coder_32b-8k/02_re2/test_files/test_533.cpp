#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{Regexp::ParseFlags::PerlX, "", &status};



    void SetUp() override {

        // Initialize the state if necessary

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(ParseStateTest_533, NormalOperationWithValidFlag_i_533) {

    absl::string_view s = "(?i)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithValidFlag_m_533) {

    absl::string_view s = "(?m)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithValidFlag_s_533) {

    absl::string_view s = "(?s)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithValidFlag_U_533) {

    absl::string_view s = "(?U)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithNegatedFlag_i_533) {

    absl::string_view s = "(?-i)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithMultipleFlags_533) {

    absl::string_view s = "(?ims)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, NormalOperationWithNamedCapture_533) {

    absl::string_view s = "(?P<name>)";

    EXPECT_TRUE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpSuccess);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, BoundaryConditionWithEmptyString_533) {

    absl::string_view s = "";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpInternalError);

    EXPECT_EQ(s, "");

}



TEST_F(ParseStateTest_533, BoundaryConditionWithShortString_533) {

    absl::string_view s = "(";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpInternalError);

    EXPECT_EQ(s, "(");

}



TEST_F(ParseStateTest_533, BoundaryConditionWithInvalidPrefix_533) {

    absl::string_view s = "(?";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpInternalError);

    EXPECT_EQ(s, "(?");

}



TEST_F(ParseStateTest_533, BoundaryConditionWithInvalidFlag_533) {

    absl::string_view s = "(?x)";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpBadPerlOp);

    EXPECT_EQ(s, "?x");

}



TEST_F(ParseStateTest_533, BoundaryConditionWithInvalidNamedCapture_533) {

    absl::string_view s = "(?P<name";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpBadNamedCapture);

    EXPECT_EQ(s, "?P<name");

}



TEST_F(ParseStateTest_533, ExceptionalCaseWithNegatedWithoutFlag_533) {

    absl::string_view s = "(?-)";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpBadPerlOp);

    EXPECT_EQ(s, "?-");

}



TEST_F(ParseStateTest_533, ExceptionalCaseWithDoubleNegation_533) {

    absl::string_view s = "(?--i)";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpBadPerlOp);

    EXPECT_EQ(s, "?-");

}
