#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



TEST_F(RE2ConsumeTest_9, Consume_SuccessfulMatch_9) {

    absl::string_view input("hello world");

    RE2 re("hello (\\w+)");

    std::string captured;

    EXPECT_TRUE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, " world");

    EXPECT_EQ(captured, "world");

}



TEST_F(RE2ConsumeTest_9, Consume_NoMatch_9) {

    absl::string_view input("hello world");

    RE2 re("goodbye (\\w+)");

    std::string captured;

    EXPECT_FALSE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, "hello world");

}



TEST_F(RE2ConsumeTest_9, Consume_EmptyInput_9) {

    absl::string_view input("");

    RE2 re("hello (\\w+)");

    std::string captured;

    EXPECT_FALSE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, "");

}



TEST_F(RE2ConsumeTest_9, Consume_EmptyPattern_9) {

    absl::string_view input("hello world");

    RE2 re("");

    std::string captured;

    EXPECT_TRUE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, "hello world");

}



TEST_F(RE2ConsumeTest_9, Consume_MultipleCaptures_9) {

    absl::string_view input("abc123def456");

    RE2 re("(\\w+)(\\d+)(\\w+)(\\d+)");

    std::string captured1, captured2, captured3, captured4;

    EXPECT_TRUE(RE2::Consume(&input, re, &captured1, &captured2, &captured3, &captured4));

    EXPECT_EQ(input, "");

    EXPECT_EQ(captured1, "abc");

    EXPECT_EQ(captured2, "123");

    EXPECT_EQ(captured3, "def");

    EXPECT_EQ(captured4, "456");

}



TEST_F(RE2ConsumeTest_9, Consume_ErrorPattern_9) {

    absl::string_view input("hello world");

    RE2 re("(\\w+");

    std::string captured;

    EXPECT_FALSE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, "hello world");

}



TEST_F(RE2ConsumeTest_9, Consume_PartialMatch_9) {

    absl::string_view input("hello world");

    RE2 re("world");

    std::string captured;

    EXPECT_FALSE(RE2::Consume(&input, re, &captured));

    EXPECT_EQ(input, "hello world");

}
