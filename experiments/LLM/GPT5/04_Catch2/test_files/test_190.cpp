// NoneTrueMatcher_tests_190.cpp
#include <gtest/gtest.h>

// Include the provided headers (adjust include paths as needed).
// Using the "known or inferred" header as the public interface.
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

namespace {

using Catch::Matchers::NoneTrueMatcher;

class NoneTrueMatcherTest_190 : public ::testing::Test {};

TEST_F(NoneTrueMatcherTest_190, DescribeReturnsExpectedString_190) {
    NoneTrueMatcher matcher;
    EXPECT_EQ(matcher.describe(), "contains no true");
}

TEST_F(NoneTrueMatcherTest_190, DescribeIsStableAcrossCalls_190) {
    NoneTrueMatcher matcher;
    const std::string first = matcher.describe();
    const std::string second = matcher.describe();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "contains no true");
}

TEST_F(NoneTrueMatcherTest_190, CopyConstructedMatcherKeepsBehavior_190) {
    NoneTrueMatcher original;
    NoneTrueMatcher copy = original;  // copy construction
    EXPECT_EQ(copy.describe(), original.describe());
    EXPECT_EQ(copy.describe(), "contains no true");
}

TEST_F(NoneTrueMatcherTest_190, CopyAssignedMatcherKeepsBehavior_190) {
    NoneTrueMatcher a;
    NoneTrueMatcher b;
    b = a;  // copy assignment
    EXPECT_EQ(b.describe(), a.describe());
    EXPECT_EQ(b.describe(), "contains no true");
}

} // namespace
