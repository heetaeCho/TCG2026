#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



using namespace YAML;

using namespace YAML::Exp;



class ScanScalarEndInFlowTest_147 : public ::testing::Test {

protected:

    void SetUp() override {

        regex = &ScanScalarEndInFlow();

    }



    const RegEx* regex;

};



TEST_F(ScanScalarEndInFlowTest_147, MatchesEndOfScalar_147) {

    EXPECT_TRUE(regex->Matches("\n"));

}



TEST_F(ScanScalarEndInFlowTest_147, MatchesCommentStart_147) {

    EXPECT_TRUE(regex->Matches("#"));

}



TEST_F(ScanScalarEndInFlowTest_147, MatchesWhitespaceFollowedByComment_147) {

    EXPECT_TRUE(regex->Matches(" #"));

}



TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchAlphanumericCharacters_147) {

    EXPECT_FALSE(regex->Matches("abc"));

    EXPECT_FALSE(regex->Matches("123"));

}



TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchWhitespaceOnly_147) {

    EXPECT_FALSE(regex->Matches(" "));

    EXPECT_FALSE(regex->Matches("\t"));

}



TEST_F(ScanScalarEndInFlowTest_147, MatchesEmptyString_147) {

    EXPECT_TRUE(regex->Matches(""));

}



TEST_F(ScanScalarEndInFlowTest_147, MatchPositionForNewline_147) {

    EXPECT_EQ(regex->Match("\n"), 1);

}



TEST_F(ScanScalarEndInFlowTest_147, MatchPositionForCommentStart_147) {

    EXPECT_EQ(regex->Match("#"), 1);

}



TEST_F(ScanScalarEndInFlowTest_147, MatchPositionForWhitespaceFollowedByComment_147) {

    EXPECT_EQ(regex->Match(" #"), 2);

}



TEST_F(ScanScalarEndInFlowTest_147, NoMatchReturnsZero_147) {

    EXPECT_EQ(regex->Match("abc"), 0);

    EXPECT_EQ(regex->Match(""), 0);

}
