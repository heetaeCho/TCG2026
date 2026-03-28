// File: exception_message_matcher_describe_tests_244.cpp

#include <gtest/gtest.h>
#include <string>

// Include the provided (project) header
#include "catch2/matchers/catch_matchers_exception.hpp"

using Catch::Matchers::ExceptionMessageMatcher;

class ExceptionMessageMatcherTest_244 : public ::testing::Test {};

// [Normal] Basic formatting with a simple message
TEST_F(ExceptionMessageMatcherTest_244, DescribeFormatsMessage_244) {
    const std::string msg = "something went wrong";
    ExceptionMessageMatcher matcher(msg);

    // Observable behavior: exact formatting of describe()
    EXPECT_NO_THROW({
        const std::string d = matcher.describe();
        EXPECT_EQ(d, std::string("exception message matches \"") + msg + "\"");
    });
}

// [Boundary] Empty message should still be quoted and formatted correctly
TEST_F(ExceptionMessageMatcherTest_244, DescribeHandlesEmptyMessage_244) {
    const std::string msg; // empty
    ExceptionMessageMatcher matcher(msg);

    EXPECT_NO_THROW({
        const std::string d = matcher.describe();
        EXPECT_EQ(d, "exception message matches \"\"");
    });
}

// [Boundary] Message containing quotes should be preserved verbatim inside outer quotes
TEST_F(ExceptionMessageMatcherTest_244, DescribePreservesInnerQuotes_244) {
    const std::string msg = "he said \"oops\"";
    ExceptionMessageMatcher matcher(msg);

    EXPECT_NO_THROW({
        const std::string d = matcher.describe();
        // No escaping beyond the outer quotes is specified/observable
        EXPECT_EQ(d, std::string("exception message matches \"") + msg + "\"");
    });
}

// [Boundary] Non-ASCII / Unicode content should be preserved
TEST_F(ExceptionMessageMatcherTest_244, DescribeHandlesUnicode_244) {
    const std::string msg = u8"오류 메시지 🚫";
    ExceptionMessageMatcher matcher(msg);

    EXPECT_NO_THROW({
        const std::string d = matcher.describe();
        EXPECT_EQ(d, std::string("exception message matches \"") + msg + "\"");
    });
}

// [Stability] Multiple calls should be consistent and side-effect free
TEST_F(ExceptionMessageMatcherTest_244, DescribeIsStableAcrossCalls_244) {
    const std::string msg = "repeatable";
    ExceptionMessageMatcher matcher(msg);

    EXPECT_NO_THROW({
        const std::string d1 = matcher.describe();
        const std::string d2 = matcher.describe();
        EXPECT_EQ(d1, d2);
        EXPECT_EQ(d1, std::string("exception message matches \"") + msg + "\"");
    });
}
