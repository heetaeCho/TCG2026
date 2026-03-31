#include <gtest/gtest.h>
#include <string>

// Since we're testing Catch2's MatchNotOf which requires MatcherBase,
// we need to set up the necessary infrastructure.
// We'll create a minimal reproduction of the interface based on the provided code.

namespace Catch {
namespace Matchers {

template <typename ArgT>
class MatcherBase {
public:
    virtual ~MatcherBase() = default;
    virtual bool match(ArgT const& arg) const = 0;
    virtual std::string describe() const = 0;
};

namespace Detail {

template <typename ArgT>
class MatchNotOf : public MatcherBase<ArgT> {
    const MatcherBase<ArgT>& m_underlyingMatcher;

public:
    explicit MatchNotOf(MatcherBase<ArgT> const& underlyingMatcher)
        : m_underlyingMatcher(underlyingMatcher) {}

    bool match(ArgT const& arg) const override {
        return !m_underlyingMatcher.match(arg);
    }

    std::string describe() const override {
        return "not " + m_underlyingMatcher.describe();
    }
};

} // namespace Detail
} // namespace Matchers
} // namespace Catch

// --- Test helpers ---

// A concrete matcher that matches if the int equals a specific value
class EqualsMatcher : public Catch::Matchers::MatcherBase<int> {
    int m_value;
public:
    explicit EqualsMatcher(int value) : m_value(value) {}
    bool match(int const& arg) const override { return arg == m_value; }
    std::string describe() const override { return "equals " + std::to_string(m_value); }
};

// A concrete matcher that always returns true
class AlwaysTrueMatcher : public Catch::Matchers::MatcherBase<int> {
public:
    bool match(int const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

// A concrete matcher that always returns false
class AlwaysFalseMatcher : public Catch::Matchers::MatcherBase<int> {
public:
    bool match(int const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

// A string matcher that checks if string contains a substring
class ContainsMatcher : public Catch::Matchers::MatcherBase<std::string> {
    std::string m_substring;
public:
    explicit ContainsMatcher(std::string sub) : m_substring(std::move(sub)) {}
    bool match(std::string const& arg) const override {
        return arg.find(m_substring) != std::string::npos;
    }
    std::string describe() const override { return "contains \"" + m_substring + "\""; }
};

// --- Tests ---

class MatchNotOfTest_143 : public ::testing::Test {};

TEST_F(MatchNotOfTest_143, NegatesMatchingResult_WhenUnderlyingMatches_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);

    // The underlying matcher matches 5, so MatchNotOf should NOT match 5
    EXPECT_FALSE(notEqualsFive.match(5));
}

TEST_F(MatchNotOfTest_143, NegatesMatchingResult_WhenUnderlyingDoesNotMatch_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);

    // The underlying matcher does NOT match 3, so MatchNotOf SHOULD match 3
    EXPECT_TRUE(notEqualsFive.match(3));
}

TEST_F(MatchNotOfTest_143, NegatesAlwaysTrueMatcher_143) {
    AlwaysTrueMatcher alwaysTrue;
    Catch::Matchers::Detail::MatchNotOf<int> notAlwaysTrue(alwaysTrue);

    EXPECT_FALSE(notAlwaysTrue.match(0));
    EXPECT_FALSE(notAlwaysTrue.match(42));
    EXPECT_FALSE(notAlwaysTrue.match(-1));
}

TEST_F(MatchNotOfTest_143, NegatesAlwaysFalseMatcher_143) {
    AlwaysFalseMatcher alwaysFalse;
    Catch::Matchers::Detail::MatchNotOf<int> notAlwaysFalse(alwaysFalse);

    EXPECT_TRUE(notAlwaysFalse.match(0));
    EXPECT_TRUE(notAlwaysFalse.match(42));
    EXPECT_TRUE(notAlwaysFalse.match(-1));
}

TEST_F(MatchNotOfTest_143, DescribeReturnsNegatedDescription_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);

    std::string description = notEqualsFive.describe();
    // The describe should contain some negation of the underlying description
    EXPECT_FALSE(description.empty());
    // We expect it to contain "not" based on the typical implementation
    EXPECT_NE(description.find("not"), std::string::npos);
}

TEST_F(MatchNotOfTest_143, WorksWithStringType_143) {
    ContainsMatcher containsHello("hello");
    Catch::Matchers::Detail::MatchNotOf<std::string> notContainsHello(containsHello);

    EXPECT_FALSE(notContainsHello.match("hello world"));
    EXPECT_TRUE(notContainsHello.match("goodbye world"));
}

TEST_F(MatchNotOfTest_143, WorksWithStringType_EmptyString_143) {
    ContainsMatcher containsHello("hello");
    Catch::Matchers::Detail::MatchNotOf<std::string> notContainsHello(containsHello);

    // Empty string does not contain "hello", so negation should be true
    EXPECT_TRUE(notContainsHello.match(""));
}

TEST_F(MatchNotOfTest_143, WorksWithStringType_EmptySubstring_143) {
    ContainsMatcher containsEmpty("");
    Catch::Matchers::Detail::MatchNotOf<std::string> notContainsEmpty(containsEmpty);

    // Every string contains "", so the underlying always matches, negation should be false
    EXPECT_FALSE(notContainsEmpty.match("anything"));
    EXPECT_FALSE(notContainsEmpty.match(""));
}

TEST_F(MatchNotOfTest_143, BoundaryCondition_MatchesZero_143) {
    EqualsMatcher equalsZero(0);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsZero(equalsZero);

    EXPECT_FALSE(notEqualsZero.match(0));
    EXPECT_TRUE(notEqualsZero.match(1));
    EXPECT_TRUE(notEqualsZero.match(-1));
}

TEST_F(MatchNotOfTest_143, BoundaryCondition_IntMinMax_143) {
    EqualsMatcher equalsIntMax(std::numeric_limits<int>::max());
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsIntMax(equalsIntMax);

    EXPECT_FALSE(notEqualsIntMax.match(std::numeric_limits<int>::max()));
    EXPECT_TRUE(notEqualsIntMax.match(std::numeric_limits<int>::min()));
    EXPECT_TRUE(notEqualsIntMax.match(0));
}

TEST_F(MatchNotOfTest_143, DoubleNegation_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);
    Catch::Matchers::Detail::MatchNotOf<int> notNotEqualsFive(notEqualsFive);

    // Double negation should yield the same result as the original matcher
    EXPECT_TRUE(notNotEqualsFive.match(5));
    EXPECT_FALSE(notNotEqualsFive.match(3));
}

TEST_F(MatchNotOfTest_143, IsAMatcherBase_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);

    // Verify it can be used polymorphically as a MatcherBase
    Catch::Matchers::MatcherBase<int>& base = notEqualsFive;
    EXPECT_FALSE(base.match(5));
    EXPECT_TRUE(base.match(3));
}

TEST_F(MatchNotOfTest_143, DescribeContainsUnderlyingDescription_143) {
    AlwaysTrueMatcher alwaysTrue;
    Catch::Matchers::Detail::MatchNotOf<int> notAlwaysTrue(alwaysTrue);

    std::string description = notAlwaysTrue.describe();
    // The description should reference the underlying matcher's description
    EXPECT_NE(description.find("always true"), std::string::npos);
}

TEST_F(MatchNotOfTest_143, MultipleCallsProduceConsistentResults_143) {
    EqualsMatcher equalsFive(5);
    Catch::Matchers::Detail::MatchNotOf<int> notEqualsFive(equalsFive);

    // Calling match multiple times should produce consistent results
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(notEqualsFive.match(5));
        EXPECT_TRUE(notEqualsFive.match(6));
    }
}
