#include <gtest/gtest.h>
#include <string>

// Since we're testing the Catch2 matchers interface, we need to set up
// the necessary infrastructure based on the provided interface.

// Minimal recreation of the interface for testing purposes
namespace Catch {
namespace Matchers {

template <typename ArgT>
class MatcherBase {
public:
    virtual ~MatcherBase() = default;
    virtual bool match(ArgT const& arg) const = 0;
    virtual std::string describe() const = 0;
    
    std::string toString() const {
        return describe();
    }
};

namespace Detail {

template <typename ArgT>
class MatchNotOf : public MatcherBase<ArgT> {
private:
    const MatcherBase<ArgT>& m_underlyingMatcher;
public:
    explicit MatchNotOf(MatcherBase<ArgT> const& underlyingMatcher)
        : m_underlyingMatcher(underlyingMatcher) {}
    
    bool match(ArgT const& arg) const override {
        return !m_underlyingMatcher.match(arg);
    }
    
    std::string describe() const override {
        return "not " + m_underlyingMatcher.toString();
    }
};

} // namespace Detail
} // namespace Matchers
} // namespace Catch

// A concrete matcher for testing purposes
template <typename ArgT>
class AlwaysTrueMatcher : public Catch::Matchers::MatcherBase<ArgT> {
public:
    bool match(ArgT const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

template <typename ArgT>
class AlwaysFalseMatcher : public Catch::Matchers::MatcherBase<ArgT> {
public:
    bool match(ArgT const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

template <typename ArgT>
class EqualsMatcher : public Catch::Matchers::MatcherBase<ArgT> {
    ArgT m_expected;
public:
    explicit EqualsMatcher(ArgT expected) : m_expected(std::move(expected)) {}
    bool match(ArgT const& arg) const override { return arg == m_expected; }
    std::string describe() const override { return "equals " + std::to_string(m_expected); }
};

class StringEqualsMatcher : public Catch::Matchers::MatcherBase<std::string> {
    std::string m_expected;
public:
    explicit StringEqualsMatcher(std::string expected) : m_expected(std::move(expected)) {}
    bool match(std::string const& arg) const override { return arg == m_expected; }
    std::string describe() const override { return "equals \"" + m_expected + "\""; }
};

// Test fixture
class MatchNotOfTest_144 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: describe() returns "not " prefixed to underlying matcher's description
TEST_F(MatchNotOfTest_144, DescribePrefixesNotToUnderlyingDescription_144) {
    AlwaysTrueMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    std::string result = notMatcher.describe();
    EXPECT_EQ(result, "not always true");
}

// Test: match() negates the result of always-true matcher
TEST_F(MatchNotOfTest_144, MatchNegatesAlwaysTrueMatcher_144) {
    AlwaysTrueMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_FALSE(notMatcher.match(42));
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_FALSE(notMatcher.match(-1));
}

// Test: match() negates the result of always-false matcher
TEST_F(MatchNotOfTest_144, MatchNegatesAlwaysFalseMatcher_144) {
    AlwaysFalseMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_TRUE(notMatcher.match(42));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(-1));
}

// Test: match() correctly negates equality matcher when value matches
TEST_F(MatchNotOfTest_144, MatchNegatesEqualityMatcherOnMatch_144) {
    EqualsMatcher<int> underlying(42);
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    // 42 equals 42, so negation should be false
    EXPECT_FALSE(notMatcher.match(42));
}

// Test: match() correctly negates equality matcher when value does not match
TEST_F(MatchNotOfTest_144, MatchNegatesEqualityMatcherOnNoMatch_144) {
    EqualsMatcher<int> underlying(42);
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    // 43 does not equal 42, so negation should be true
    EXPECT_TRUE(notMatcher.match(43));
}

// Test: describe() with equality matcher
TEST_F(MatchNotOfTest_144, DescribeWithEqualsMatcher_144) {
    EqualsMatcher<int> underlying(42);
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    std::string result = notMatcher.describe();
    EXPECT_EQ(result, "not equals 42");
}

// Test: Works with string type
TEST_F(MatchNotOfTest_144, WorksWithStringType_144) {
    StringEqualsMatcher underlying("hello");
    Catch::Matchers::Detail::MatchNotOf<std::string> notMatcher(underlying);
    
    EXPECT_FALSE(notMatcher.match("hello"));
    EXPECT_TRUE(notMatcher.match("world"));
}

// Test: describe() works with string matcher
TEST_F(MatchNotOfTest_144, DescribeWithStringMatcher_144) {
    StringEqualsMatcher underlying("hello");
    Catch::Matchers::Detail::MatchNotOf<std::string> notMatcher(underlying);
    
    std::string result = notMatcher.describe();
    EXPECT_EQ(result, "not equals \"hello\"");
}

// Test: MatchNotOf is itself a MatcherBase, so it can be used as underlying matcher (double negation)
TEST_F(MatchNotOfTest_144, DoubleNegationReturnsOriginalResult_144) {
    AlwaysTrueMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    Catch::Matchers::Detail::MatchNotOf<int> notNotMatcher(notMatcher);
    
    // Double negation of true should be true
    EXPECT_TRUE(notNotMatcher.match(42));
}

// Test: Double negation describe
TEST_F(MatchNotOfTest_144, DoubleNegationDescribe_144) {
    AlwaysTrueMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    Catch::Matchers::Detail::MatchNotOf<int> notNotMatcher(notMatcher);
    
    std::string result = notNotMatcher.describe();
    EXPECT_EQ(result, "not not always true");
}

// Test: Boundary - empty description from underlying matcher
TEST_F(MatchNotOfTest_144, DescribeWithEmptyUnderlyingDescription_144) {
    class EmptyDescMatcher : public Catch::Matchers::MatcherBase<int> {
    public:
        bool match(int const&) const override { return true; }
        std::string describe() const override { return ""; }
    };
    
    EmptyDescMatcher underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_EQ(notMatcher.describe(), "not ");
}

// Test: Boundary - zero value
TEST_F(MatchNotOfTest_144, BoundaryZeroValue_144) {
    EqualsMatcher<int> underlying(0);
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_FALSE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
}

// Test: Boundary - negative value
TEST_F(MatchNotOfTest_144, BoundaryNegativeValue_144) {
    EqualsMatcher<int> underlying(-1);
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_FALSE(notMatcher.match(-1));
    EXPECT_TRUE(notMatcher.match(0));
    EXPECT_TRUE(notMatcher.match(1));
}

// Test: Works with double type
TEST_F(MatchNotOfTest_144, WorksWithDoubleType_144) {
    class PositiveMatcher : public Catch::Matchers::MatcherBase<double> {
    public:
        bool match(double const& arg) const override { return arg > 0.0; }
        std::string describe() const override { return "is positive"; }
    };
    
    PositiveMatcher underlying;
    Catch::Matchers::Detail::MatchNotOf<double> notMatcher(underlying);
    
    EXPECT_TRUE(notMatcher.match(-1.0));
    EXPECT_TRUE(notMatcher.match(0.0));
    EXPECT_FALSE(notMatcher.match(1.0));
    EXPECT_EQ(notMatcher.describe(), "not is positive");
}

// Test: toString() returns same as describe() through base class interface
TEST_F(MatchNotOfTest_144, ToStringReturnsSameAsDescribe_144) {
    AlwaysTrueMatcher<int> underlying;
    Catch::Matchers::Detail::MatchNotOf<int> notMatcher(underlying);
    
    EXPECT_EQ(notMatcher.toString(), notMatcher.describe());
}
