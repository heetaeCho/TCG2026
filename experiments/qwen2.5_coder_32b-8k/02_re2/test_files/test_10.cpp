#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include "absl/strings/string_view.h"



using ::testing::_;

using ::testing::Return;

using namespace re2;



class RE2Test_10 : public ::testing::Test {

protected:

    RE2 re2_valid_pattern{"^abc$"};

    RE2 re2_invalid_pattern{R"((a|b}"};

    absl::string_view input_normal = "abc";

    absl::string_view input_empty = "";

    absl::string_view input_mismatch = "abcd";

};



TEST_F(RE2Test_10, FindAndConsume_NormalMatch_10) {

    absl::string_view input = input_normal;

    EXPECT_TRUE(re2::RE2::FindAndConsume(&input, re2_valid_pattern));

    EXPECT_EQ(input, "");

}



TEST_F(RE2Test_10, FindAndConsume_NoMatch_10) {

    absl::string_view input = input_mismatch;

    EXPECT_FALSE(re2::RE2::FindAndConsume(&input, re2_valid_pattern));

    EXPECT_EQ(input, "abcd");

}



TEST_F(RE2Test_10, FindAndConsume_EmptyInput_10) {

    absl::string_view input = input_empty;

    EXPECT_FALSE(re2::RE2::FindAndConsume(&input, re2_valid_pattern));

    EXPECT_EQ(input, "");

}



TEST_F(RE2Test_10, FindAndConsume_InvalidPattern_10) {

    absl::string_view input = input_normal;

    EXPECT_FALSE(re2::RE2::FindAndConsume(&input, re2_invalid_pattern));

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_10, FindAndConsume_PartialMatch_10) {

    absl::string_view input = "abcde";

    EXPECT_TRUE(re2::RE2::FindAndConsume(&input, re2_valid_pattern));

    EXPECT_EQ(input, "de");

}
