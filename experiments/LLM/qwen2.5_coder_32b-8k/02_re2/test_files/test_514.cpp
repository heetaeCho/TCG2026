#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"



namespace re2 {



// Assuming ParseInteger is a function that parses an integer from absl::string_view

// and updates the string view to remove the parsed integer.

bool ParseInteger(absl::string_view* sp, int* val);



class MaybeParseRepetitionTest_514 : public ::testing::Test {

protected:

    absl::string_view input;

    int lo;

    int hi;



    bool CallMaybeParseRepetition() {

        return MaybeParseRepetition(&input, &lo, &hi);

    }

};



TEST_F(MaybeParseRepetitionTest_514, NormalOperationSingleNumber_514) {

    input = "{3}";

    EXPECT_TRUE(CallMaybeParseRepetition());

    EXPECT_EQ(lo, 3);

    EXPECT_EQ(hi, 3);

}



TEST_F(MaybeParseRepetitionTest_514, NormalOperationRange_514) {

    input = "{2,5}";

    EXPECT_TRUE(CallMaybeParseRepetition());

    EXPECT_EQ(lo, 2);

    EXPECT_EQ(hi, 5);

}



TEST_F(MaybeParseRepetitionTest_514, OpenEndedRange_514) {

    input = "{3,}";

    EXPECT_TRUE(CallMaybeParseRepetition());

    EXPECT_EQ(lo, 3);

    EXPECT_EQ(hi, -1);

}



TEST_F(MaybeParseRepetitionTest_514, EmptyString_514) {

    input = "";

    EXPECT_FALSE(CallMaybeParseRepetition());

}



TEST_F(MaybeParseRepetitionTest_514, NoOpeningBrace_514) {

    input = "3}";

    EXPECT_FALSE(CallMaybeParseRepetition());

}



TEST_F(MaybeParseRepetitionTest_514, MissingCommaInRange_514) {

    input = "{2 5}";

    EXPECT_FALSE(CallMaybeParseRepetition());

}



TEST_F(MaybeParseRepetitionTest_514, NoClosingBrace_514) {

    input = "{3";

    EXPECT_FALSE(CallMaybeParseRepetition());

}



TEST_F(MaybeParseRepetitionTest_514, InvalidNumber_514) {

    input = "{abc}";

    EXPECT_FALSE(CallMaybeParseRepetition());

}



TEST_F(MaybeParseRepetitionTest_514, BoundaryConditionZero_514) {

    input = "{0}";

    EXPECT_TRUE(CallMaybeParseRepetition());

    EXPECT_EQ(lo, 0);

    EXPECT_EQ(hi, 0);

}



TEST_F(MaybeParseRepetitionTest_514, LargeNumber_514) {

    input = "{99999}";

    EXPECT_TRUE(CallMaybeParseRepetition());

    EXPECT_EQ(lo, 99999);

    EXPECT_EQ(hi, 99999);

}



} // namespace re2
