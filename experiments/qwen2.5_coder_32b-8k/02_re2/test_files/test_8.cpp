#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using ::testing::_;

using ::testing::Return;

using ::absl::string_view;



class RE2Test : public ::testing::Test {

protected:

    re2::RE2 regex_pattern{"\\d+"};

};



TEST_F(RE2Test_8, PartialMatch_ValidInput_ReturnsTrue_8) {

    EXPECT_TRUE(re2::RE2::PartialMatch("abc123", regex_pattern));

}



TEST_F(RE2Test_8, PartialMatch_NoMatch_ReturnsFalse_8) {

    EXPECT_FALSE(re2::RE2::PartialMatch("abcdef", regex_pattern));

}



TEST_F(RE2Test_8, PartialMatch_EmptyText_ReturnsFalse_8) {

    EXPECT_FALSE(re2::RE2::PartialMatch("", regex_pattern));

}



TEST_F(RE2Test_8, PartialMatch_NullPattern_ReturnsFalse_8) {

    re2::RE2 null_pattern{""};

    EXPECT_FALSE(re2::RE2::PartialMatch("abc123", null_pattern));

}



TEST_F(RE2Test_8, PartialMatch_ValidInputWithAnchors_ReturnsTrue_8) {

    string_view submatch;

    EXPECT_TRUE(regex_pattern.Match("123abc", 0, 6, re2::RE2_ANCHOR_START, &submatch, 1));

}



TEST_F(RE2Test_8, PartialMatch_ValidInputWithEndAnchor_ReturnsFalse_8) {

    string_view submatch;

    EXPECT_FALSE(regex_pattern.Match("abc123", 0, 6, re2::RE2_ANCHOR_END, &submatch, 1));

}
