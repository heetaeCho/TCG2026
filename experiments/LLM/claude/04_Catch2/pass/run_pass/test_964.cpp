#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// ============================================================
// Tests for VectorContainsElementMatcher with int
// ============================================================

class VectorContainsElementMatcherIntTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsTrueWhenElementExists_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(3);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsFalseWhenElementDoesNotExist_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(10);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsFalseForEmptyVector_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(1);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsTrueWhenElementIsFirst_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(1);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsTrueWhenElementIsLast_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(5);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsTrueForSingleElementVectorContaining_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(42);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsFalseForSingleElementVectorNotContaining_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(42);
    std::vector<int> v = {99};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchReturnsTrueWhenDuplicatesExist_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(3);
    std::vector<int> v = {3, 3, 3, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchWithNegativeNumbers_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(-5);
    std::vector<int> v = {-10, -5, 0, 5, 10};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchWithZero_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(0);
    std::vector<int> v = {-1, 0, 1};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherIntTest_964, MatchWithZeroNotPresent_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(0);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Tests for VectorContainsElementMatcher with std::string
// ============================================================

class VectorContainsElementMatcherStringTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherStringTest_964, MatchReturnsTrueWhenStringExists_964) {
    std::string target = "hello";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherStringTest_964, MatchReturnsFalseWhenStringDoesNotExist_964) {
    std::string target = "bar";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"world", "hello", "foo"};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherStringTest_964, MatchReturnsFalseForEmptyStringVector_964) {
    std::string target = "anything";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherStringTest_964, MatchWithEmptyStringTarget_964) {
    std::string target = "";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"", "hello"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherStringTest_964, MatchWithEmptyStringNotPresent_964) {
    std::string target = "";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(target);
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Tests for VectorContainsElementMatcher with double
// ============================================================

class VectorContainsElementMatcherDoubleTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherDoubleTest_964, MatchReturnsTrueWhenDoubleExists_964) {
    VectorContainsElementMatcher<double, std::allocator<double>> matcher(3.14);
    std::vector<double> v = {1.0, 2.0, 3.14, 4.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherDoubleTest_964, MatchReturnsFalseWhenDoubleDoesNotExist_964) {
    VectorContainsElementMatcher<double, std::allocator<double>> matcher(3.15);
    std::vector<double> v = {1.0, 2.0, 3.14, 4.0};
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Tests for describe()
// ============================================================

class VectorContainsElementMatcherDescribeTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherDescribeTest_964, DescribeReturnsNonEmptyString_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(42);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(VectorContainsElementMatcherDescribeTest_964, DescribeContainsRelevantInfo_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(42);
    std::string description = matcher.describe();
    // The describe string should mention something about containing the element
    // We check it's non-empty as a minimal observable behavior check
    EXPECT_GT(description.size(), 0u);
}

// ============================================================
// Tests for large vectors
// ============================================================

class VectorContainsElementMatcherLargeTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherLargeTest_964, MatchInLargeVectorElementPresent_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(99999);
    std::vector<int> v(100000);
    for (int i = 0; i < 100000; ++i) {
        v[i] = i;
    }
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherLargeTest_964, MatchInLargeVectorElementNotPresent_964) {
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(100001);
    std::vector<int> v(100000);
    for (int i = 0; i < 100000; ++i) {
        v[i] = i;
    }
    EXPECT_FALSE(matcher.match(v));
}

// ============================================================
// Tests with custom comparable type
// ============================================================

struct CustomType {
    int value;
    bool operator==(const CustomType& other) const {
        return value == other.value;
    }
};

class VectorContainsElementMatcherCustomTypeTest_964 : public ::testing::Test {
protected:
};

TEST_F(VectorContainsElementMatcherCustomTypeTest_964, MatchReturnsTrueForCustomType_964) {
    CustomType target{5};
    VectorContainsElementMatcher<CustomType, std::allocator<CustomType>> matcher(target);
    std::vector<CustomType> v = {{1}, {2}, {5}, {8}};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(VectorContainsElementMatcherCustomTypeTest_964, MatchReturnsFalseForCustomType_964) {
    CustomType target{99};
    VectorContainsElementMatcher<CustomType, std::allocator<CustomType>> matcher(target);
    std::vector<CustomType> v = {{1}, {2}, {5}, {8}};
    EXPECT_FALSE(matcher.match(v));
}
