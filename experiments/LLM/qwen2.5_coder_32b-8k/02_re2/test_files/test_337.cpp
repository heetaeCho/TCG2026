#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class RegexpTest_337 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_337, HaveMatch_ReturnsNonNullPointer_337) {

    Regexp* re = Regexp::HaveMatch(1, ParseFlags());

    ASSERT_NE(re, nullptr);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_CorrectOpType_337) {

    Regexp* re = Regexp::HaveMatch(1, ParseFlags());

    EXPECT_EQ(re->op(), kRegexpHaveMatch);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_MatchIdSetCorrectly_337) {

    int match_id = 42;

    Regexp* re = Regexp::HaveMatch(match_id, ParseFlags());

    EXPECT_EQ(re->match_id(), match_id);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_ParseFlagsSetCorrectly_337) {

    ParseFlags flags = 0x1234;

    Regexp* re = Regexp::HaveMatch(1, flags);

    EXPECT_EQ(re->parse_flags(), flags);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_ZeroMatchId_337) {

    Regexp* re = Regexp::HaveMatch(0, ParseFlags());

    EXPECT_EQ(re->match_id(), 0);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_MaxMatchId_337) {

    int max_match_id = std::numeric_limits<int>::max();

    Regexp* re = Regexp::HaveMatch(max_match_id, ParseFlags());

    EXPECT_EQ(re->match_id(), max_match_id);

    delete re;

}



TEST_F(RegexpTest_337, HaveMatch_DefaultParseFlags_337) {

    Regexp* re = Regexp::HaveMatch(1, 0);

    EXPECT_EQ(re->parse_flags(), 0);

    delete re;

}



} // namespace re2
