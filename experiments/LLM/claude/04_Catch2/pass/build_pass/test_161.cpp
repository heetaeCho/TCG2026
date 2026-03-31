#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to create some simple matchers to use with MatchAnyOfGeneric

namespace {

// A simple matcher that checks if an int equals a specific value
class EqualsMatcher : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit EqualsMatcher(int value) : m_value(value) {}
    
    bool match(int const& arg) const {
        return arg == m_value;
    }
    
    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

// A simple matcher that checks if an int is greater than a specific value
class GreaterThanMatcher : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit GreaterThanMatcher(int value) : m_value(value) {}
    
    bool match(int const& arg) const {
        return arg > m_value;
    }
    
    std::string describe() const override {
        return "is greater than " + std::to_string(m_value);
    }
};

// A simple matcher that checks if an int is less than a specific value
class LessThanMatcher : public Catch::Matchers::MatcherGenericBase {
    int m_value;
public:
    explicit LessThanMatcher(int value) : m_value(value) {}
    
    bool match(int const& arg) const {
        return arg < m_value;
    }
    
    std::string describe() const override {
        return "is less than " + std::to_string(m_value);
    }
};

// A matcher that always returns false
class NeverMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int const&) const {
        return false;
    }
    
    std::string describe() const override {
        return "never matches";
    }
};

// A matcher that always returns true
class AlwaysMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    bool match(int const&) const {
        return true;
    }
    
    std::string describe() const override {
        return "always matches";
    }
};

// A string matcher
class ContainsSubstringMatcher : public Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
public:
    explicit ContainsSubstringMatcher(std::string substr) : m_substr(std::move(substr)) {}
    
    bool match(std::string const& arg) const {
        return arg.find(m_substr) != std::string::npos;
    }
    
    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

} // anonymous namespace

class MatchAnyOfGenericTest_161 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Single matcher that matches should return true
TEST_F(MatchAnyOfGenericTest_161, SingleMatcherMatches_161) {
    EqualsMatcher eq5(5);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher> anyOf(eq5);
    EXPECT_TRUE(anyOf.match(5));
}

// Test: Single matcher that does not match should return false
TEST_F(MatchAnyOfGenericTest_161, SingleMatcherDoesNotMatch_161) {
    EqualsMatcher eq5(5);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher> anyOf(eq5);
    EXPECT_FALSE(anyOf.match(3));
}

// Test: Two matchers, first matches
TEST_F(MatchAnyOfGenericTest_161, TwoMatchersFirstMatches_161) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher> anyOf(eq5, eq10);
    EXPECT_TRUE(anyOf.match(5));
}

// Test: Two matchers, second matches
TEST_F(MatchAnyOfGenericTest_161, TwoMatchersSecondMatches_161) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher> anyOf(eq5, eq10);
    EXPECT_TRUE(anyOf.match(10));
}

// Test: Two matchers, neither matches
TEST_F(MatchAnyOfGenericTest_161, TwoMatchersNeitherMatches_161) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher> anyOf(eq5, eq10);
    EXPECT_FALSE(anyOf.match(7));
}

// Test: Two matchers, both match
TEST_F(MatchAnyOfGenericTest_161, TwoMatchersBothMatch_161) {
    GreaterThanMatcher gt3(3);
    LessThanMatcher lt10(10);
    Catch::Matchers::Detail::MatchAnyOfGeneric<GreaterThanMatcher, LessThanMatcher> anyOf(gt3, lt10);
    // Value 5 matches both (>3 and <10)
    EXPECT_TRUE(anyOf.match(5));
}

// Test: Multiple matchers, none match
TEST_F(MatchAnyOfGenericTest_161, MultipleMatchersNoneMatch_161) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher, EqualsMatcher> anyOf(eq1, eq2, eq3);
    EXPECT_FALSE(anyOf.match(4));
}

// Test: Multiple matchers, last one matches
TEST_F(MatchAnyOfGenericTest_161, MultipleMatchersLastMatches_161) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher, EqualsMatcher> anyOf(eq1, eq2, eq3);
    EXPECT_TRUE(anyOf.match(3));
}

// Test: Mixed matcher types
TEST_F(MatchAnyOfGenericTest_161, MixedMatcherTypes_161) {
    EqualsMatcher eq5(5);
    GreaterThanMatcher gt100(100);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, GreaterThanMatcher> anyOf(eq5, gt100);
    
    EXPECT_TRUE(anyOf.match(5));      // matches first
    EXPECT_TRUE(anyOf.match(200));    // matches second
    EXPECT_FALSE(anyOf.match(50));    // matches neither
}

// Test: AlwaysMatcher ensures true
TEST_F(MatchAnyOfGenericTest_161, AlwaysMatcherAlwaysReturnsTrue_161) {
    NeverMatcher never;
    AlwaysMatcher always;
    Catch::Matchers::Detail::MatchAnyOfGeneric<NeverMatcher, AlwaysMatcher> anyOf(never, always);
    EXPECT_TRUE(anyOf.match(42));
}

// Test: All NeverMatchers return false
TEST_F(MatchAnyOfGenericTest_161, AllNeverMatchersReturnFalse_161) {
    NeverMatcher n1;
    NeverMatcher n2;
    Catch::Matchers::Detail::MatchAnyOfGeneric<NeverMatcher, NeverMatcher> anyOf(n1, n2);
    EXPECT_FALSE(anyOf.match(42));
}

// Test: describe() returns a non-empty string
TEST_F(MatchAnyOfGenericTest_161, DescribeReturnsNonEmptyString_161) {
    EqualsMatcher eq5(5);
    GreaterThanMatcher gt10(10);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, GreaterThanMatcher> anyOf(eq5, gt10);
    std::string desc = anyOf.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: describe() with single matcher
TEST_F(MatchAnyOfGenericTest_161, DescribeSingleMatcher_161) {
    EqualsMatcher eq5(5);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher> anyOf(eq5);
    std::string desc = anyOf.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: Boundary - matching with zero value
TEST_F(MatchAnyOfGenericTest_161, BoundaryZeroValue_161) {
    EqualsMatcher eq0(0);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher> anyOf(eq0);
    EXPECT_TRUE(anyOf.match(0));
    EXPECT_FALSE(anyOf.match(1));
}

// Test: Boundary - negative values
TEST_F(MatchAnyOfGenericTest_161, BoundaryNegativeValues_161) {
    EqualsMatcher eqNeg(-1);
    LessThanMatcher ltNeg(-100);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, LessThanMatcher> anyOf(eqNeg, ltNeg);
    EXPECT_TRUE(anyOf.match(-1));
    EXPECT_TRUE(anyOf.match(-200));
    EXPECT_FALSE(anyOf.match(0));
}

// Test: String matchers with MatchAnyOfGeneric
TEST_F(MatchAnyOfGenericTest_161, StringMatchers_161) {
    ContainsSubstringMatcher hello("hello");
    ContainsSubstringMatcher world("world");
    Catch::Matchers::Detail::MatchAnyOfGeneric<ContainsSubstringMatcher, ContainsSubstringMatcher> anyOf(hello, world);
    
    EXPECT_TRUE(anyOf.match(std::string("hello there")));
    EXPECT_TRUE(anyOf.match(std::string("brave world")));
    EXPECT_TRUE(anyOf.match(std::string("hello world")));
    EXPECT_FALSE(anyOf.match(std::string("goodbye")));
}

// Test: Move construction compiles and works
TEST_F(MatchAnyOfGenericTest_161, MoveConstruction_161) {
    EqualsMatcher eq5(5);
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher> original(eq5);
    auto moved = std::move(original);
    EXPECT_TRUE(moved.match(5));
    EXPECT_FALSE(moved.match(3));
}

// Test: Using the || operator to combine matchers (if supported via MatcherGenericBase)
TEST_F(MatchAnyOfGenericTest_161, OperatorOrCombination_161) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);
    // The || operator typically creates a MatchAnyOfGeneric
    auto combined = eq5 || eq10;
    EXPECT_TRUE(combined.match(5));
    EXPECT_TRUE(combined.match(10));
    EXPECT_FALSE(combined.match(7));
}

// Test: Three-way OR combination
TEST_F(MatchAnyOfGenericTest_161, ThreeWayOrCombination_161) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);
    auto combined = eq1 || eq2 || eq3;
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test: Large value boundary
TEST_F(MatchAnyOfGenericTest_161, LargeValueBoundary_161) {
    EqualsMatcher eqMax(std::numeric_limits<int>::max());
    EqualsMatcher eqMin(std::numeric_limits<int>::min());
    Catch::Matchers::Detail::MatchAnyOfGeneric<EqualsMatcher, EqualsMatcher> anyOf(eqMax, eqMin);
    EXPECT_TRUE(anyOf.match(std::numeric_limits<int>::max()));
    EXPECT_TRUE(anyOf.match(std::numeric_limits<int>::min()));
    EXPECT_FALSE(anyOf.match(0));
}
