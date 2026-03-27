#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"

#include "absl/strings/string_view.h"



namespace re2 {

namespace {



class PCRETest : public ::testing::Test {

protected:

    std::string output;

};



TEST_F(PCRETest_195, Extract_NoMatch_ReturnsFalse_195) {

    PCRE pattern("abc");

    EXPECT_FALSE(pattern.Extract("def", pattern, "xyz", &output));

}



TEST_F(PCRETest_195, Extract_Match_Successful_195) {

    PCRE pattern("(\\d+)");

    EXPECT_TRUE(pattern.Extract("The number is 42", pattern, "Number: $1", &output));

    EXPECT_EQ(output, "Number: 42");

}



TEST_F(PCRETest_195, Extract_EmptyText_ReturnsFalse_195) {

    PCRE pattern("abc");

    EXPECT_FALSE(pattern.Extract("", pattern, "xyz", &output));

}



TEST_F(PCRETest_195, Extract_EmptyPattern_ReturnsFalse_195) {

    PCRE pattern("");

    EXPECT_FALSE(pattern.Extract("def", pattern, "xyz", &output));

}



TEST_F(PCRETest_195, Extract_NoRewrite_ReturnsTrueAndEmptyOutput_195) {

    PCRE pattern("(\\d+)");

    EXPECT_TRUE(pattern.Extract("The number is 42", pattern, "", &output));

    EXPECT_EQ(output, "");

}



} // namespace

} // namespace re2
