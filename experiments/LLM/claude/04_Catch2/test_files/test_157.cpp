#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Simple custom matcher for testing purposes
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const { return true; }
    std::string describe() const override { return "is always true"; }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T&&) const { return false; }
    std::string describe() const override { return "is always false"; }
};

struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val > 0; }
    std::string describe() const override { return "is positive"; }
};

struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

struct IsLessThan100Matcher : Catch::Matchers::MatcherGenericBase {
    bool match(int val) const { return val < 100; }
    std::string describe() const override { return "is less than 100"; }
};

struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
    StringContainsMatcher(std::string substr) : m_substr(std::move(substr)) {}
    bool match(const std::string& val) const { return val.find(m_substr) != std::string::npos; }
    std::string describe() const override { return "contains \"" + m_substr + "\""; }
};

struct StringStartsWithMatcher : Catch::Matchers::MatcherGenericBase {
    std::string m_prefix;
    StringStartsWithMatcher(std::string prefix) : m_prefix(std::move(prefix)) {}
    bool match(const std::string& val) const { return val.substr(0, m_prefix.size()) == m_prefix; }
    std::string describe() const override { return "starts with \"" + m_prefix + "\""; }
};

class MatchAllOfGenericTest_157 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: All matchers return true => match returns true
TEST_F(MatchAllOfGenericTest_157, AllMatchersTrue_ReturnsTrue_157) {
    AlwaysTrueMatcher m1;
    AlwaysTrueMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysTrueMatcher, AlwaysTrueMatcher>(m1, m2);
    EXPECT_TRUE(combined.match(42));
}

// Test: One matcher returns false => match returns false
TEST_F(MatchAllOfGenericTest_157, OneMatcherFalse_ReturnsFalse_157) {
    AlwaysTrueMatcher m1;
    AlwaysFalseMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysTrueMatcher, AlwaysFalseMatcher>(m1, m2);
    EXPECT_FALSE(combined.match(42));
}

// Test: All matchers return false => match returns false
TEST_F(MatchAllOfGenericTest_157, AllMatchersFalse_ReturnsFalse_157) {
    AlwaysFalseMatcher m1;
    AlwaysFalseMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysFalseMatcher, AlwaysFalseMatcher>(m1, m2);
    EXPECT_FALSE(combined.match(42));
}

// Test: First matcher false, second true => match returns false
TEST_F(MatchAllOfGenericTest_157, FirstFalseSecondTrue_ReturnsFalse_157) {
    AlwaysFalseMatcher m1;
    AlwaysTrueMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysFalseMatcher, AlwaysTrueMatcher>(m1, m2);
    EXPECT_FALSE(combined.match(42));
}

// Test: describe() contains "and"
TEST_F(MatchAllOfGenericTest_157, DescribeContainsAnd_157) {
    AlwaysTrueMatcher m1;
    AlwaysFalseMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysTrueMatcher, AlwaysFalseMatcher>(m1, m2);
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("and"), std::string::npos);
}

// Test: describe() includes descriptions of individual matchers
TEST_F(MatchAllOfGenericTest_157, DescribeIncludesIndividualDescriptions_157) {
    AlwaysTrueMatcher m1;
    AlwaysFalseMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysTrueMatcher, AlwaysFalseMatcher>(m1, m2);
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is always true"), std::string::npos);
    EXPECT_NE(desc.find("is always false"), std::string::npos);
}

// Test: Matching with semantically meaningful matchers - positive and even
TEST_F(MatchAllOfGenericTest_157, PositiveAndEven_MatchesPositiveEvenNumber_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>(m1, m2);
    EXPECT_TRUE(combined.match(4));   // positive and even
    EXPECT_FALSE(combined.match(3));  // positive but odd
    EXPECT_FALSE(combined.match(-2)); // even but negative
    EXPECT_FALSE(combined.match(-3)); // neither positive nor even
}

// Test: Three matchers combined
TEST_F(MatchAllOfGenericTest_157, ThreeMatchers_AllMustMatch_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    IsLessThan100Matcher m3;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher, IsLessThan100Matcher>(m1, m2, m3);
    EXPECT_TRUE(combined.match(4));    // positive, even, < 100
    EXPECT_FALSE(combined.match(102)); // positive, even, but >= 100
    EXPECT_FALSE(combined.match(3));   // positive, < 100, but odd
    EXPECT_FALSE(combined.match(-4));  // even, < 100, but not positive
}

// Test: Three matchers describe contains both "and" separators
TEST_F(MatchAllOfGenericTest_157, ThreeMatchersDescribe_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    IsLessThan100Matcher m3;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher, IsLessThan100Matcher>(m1, m2, m3);
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
    EXPECT_NE(desc.find("is less than 100"), std::string::npos);
}

// Test: Single matcher in MatchAllOfGeneric
TEST_F(MatchAllOfGenericTest_157, SingleMatcher_BehavesLikeSingleMatcher_157) {
    IsPositiveMatcher m1;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher>(m1);
    EXPECT_TRUE(combined.match(5));
    EXPECT_FALSE(combined.match(-1));
}

// Test: Single matcher describe
TEST_F(MatchAllOfGenericTest_157, SingleMatcherDescribe_157) {
    IsPositiveMatcher m1;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher>(m1);
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is positive"), std::string::npos);
}

// Test: String matchers combined
TEST_F(MatchAllOfGenericTest_157, StringMatchers_BothMustMatch_157) {
    StringContainsMatcher m1("hello");
    StringStartsWithMatcher m2("hello");
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<StringContainsMatcher, StringStartsWithMatcher>(m1, m2);
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("say hello")));  // contains hello but doesn't start with it
    EXPECT_FALSE(combined.match(std::string("world")));       // neither
}

// Test: Move construction is allowed
TEST_F(MatchAllOfGenericTest_157, MoveConstruction_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>(m1, m2);
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match(4));
    EXPECT_FALSE(moved.match(3));
}

// Test: Boundary - zero is not positive
TEST_F(MatchAllOfGenericTest_157, BoundaryZero_IsNotPositive_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>(m1, m2);
    EXPECT_FALSE(combined.match(0)); // 0 is even but not positive
}

// Test: Boundary - value exactly 100
TEST_F(MatchAllOfGenericTest_157, BoundaryExactly100_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    IsLessThan100Matcher m3;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher, IsLessThan100Matcher>(m1, m2, m3);
    EXPECT_FALSE(combined.match(100)); // positive, even, but not < 100
    EXPECT_TRUE(combined.match(98));   // positive, even, < 100
}

// Test: Copy construction is deleted (compile-time check via type trait)
TEST_F(MatchAllOfGenericTest_157, CopyConstructionIsDeleted_157) {
    using CombinedType = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>;
    EXPECT_FALSE(std::is_copy_constructible<CombinedType>::value);
}

// Test: Copy assignment is deleted
TEST_F(MatchAllOfGenericTest_157, CopyAssignmentIsDeleted_157) {
    using CombinedType = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>;
    EXPECT_FALSE(std::is_copy_assignable<CombinedType>::value);
}

// Test: Match with const reference argument
TEST_F(MatchAllOfGenericTest_157, MatchWithConstRefArg_157) {
    IsPositiveMatcher m1;
    IsEvenMatcher m2;
    auto combined = Catch::Matchers::Detail::MatchAllOfGeneric<IsPositiveMatcher, IsEvenMatcher>(m1, m2);
    const int val = 6;
    EXPECT_TRUE(combined.match(val));
}

// Test: Using operator&& to combine generic matchers (if available via ADL or Catch2 operators)
TEST_F(MatchAllOfGenericTest_157, OperatorAndCombination_157) {
    AlwaysTrueMatcher m1;
    IsPositiveMatcher m2;
    auto combined = m1 && m2;
    EXPECT_TRUE(combined.match(5));
    EXPECT_FALSE(combined.match(-1));
}
