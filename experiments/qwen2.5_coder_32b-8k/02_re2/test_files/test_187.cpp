#include <gtest/gtest.h>

#include "TestProjects/re2/util/pcre.cc"



class PCRETest_187 : public ::testing::Test {

protected:

    const pcre* regex = nullptr;

    const pcre_extra* extra = nullptr;

};



TEST_F(PCRETest_187, FullInfoReturnsZeroForCaptureCount_187) {

    int capture_count;

    EXPECT_EQ(pcre_fullinfo(regex, extra, PCRE_INFO_CAPTURECOUNT, &capture_count), 0);

}



TEST_F(PCRETest_187, FullInfoReturnsZeroForMatchLimit_187) {

    unsigned long match_limit = 0;

    EXPECT_EQ(pcre_fullinfo(regex, extra, PCRE_EXTRA_MATCH_LIMIT, &match_limit), 0);

}



TEST_F(PCRETest_187, FullInfoReturnsZeroForMatchLimitRecursion_187) {

    unsigned long match_limit_recursion = 0;

    EXPECT_EQ(pcre_fullinfo(regex, extra, PCRE_EXTRA_MATCH_LIMIT_RECURSION, &match_limit_recursion), 0);

}



TEST_F(PCRETest_187, FullInfoReturnsZeroForAnchored_187) {

    int anchored_option = 0;

    EXPECT_EQ(pcre_fullinfo(regex, extra, PCRE_ANCHORED, &anchored_option), 0);

}



TEST_F(PCRETest_187, FullInfoReturnsZeroForNotEmpty_187) {

    int not_empty_option = 0;

    EXPECT_EQ(pcre_fullinfo(regex, extra, PCRE_NOTEMPTY, &not_empty_option), 0);

}
