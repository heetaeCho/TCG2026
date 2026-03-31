#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to create simple matchers that conform to the Catch2 matcher protocol
// to test MatchAllOfGeneric

namespace {

// A simple matcher that checks if an int is positive
struct IsPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const {
        return val > 0;
    }
    std::string describe() const override {
        return "is positive";
    }
};

// A simple matcher that checks if an int is less than 100
struct IsLessThan100Matcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const {
        return val < 100;
    }
    std::string describe() const override {
        return "is less than 100";
    }
};

// A simple matcher that checks if an int is even
struct IsEvenMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const {
        return (val % 2) == 0;
    }
    std::string describe() const override {
        return "is even";
    }
};

// A matcher that always returns true
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return true;
    }
    std::string describe() const override {
        return "always true";
    }
};

// A matcher that always returns false
struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return false;
    }
    std::string describe() const override {
        return "always false";
    }
};

// A string matcher that checks if string contains a substring
struct ContainsSubstringMatcher : Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
    ContainsSubstringMatcher(std::string substr) : m_substr(std::move(substr)) {}
    
    bool match(std::string const& val) const {
        return val.find(m_substr) != std::string::npos;
    }
    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

// A string matcher that checks if string length is greater than N
struct LengthGreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    size_t m_length;
    LengthGreaterThanMatcher(size_t len) : m_length(len) {}
    
    bool match(std::string const& val) const {
        return val.size() > m_length;
    }
    std::string describe() const override {
        return "has length greater than " + std::to_string(m_length);
    }
};

} // anonymous namespace

class MatchAllOfGenericTest_156 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: All matchers match - should return true
TEST_F(MatchAllOfGenericTest_156, AllMatchersMatch_ReturnsTrue_156) {
    IsPositiveMatcher pos;
    IsLessThan100Matcher lt100;
    IsEvenMatcher even;
    
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{} && IsEvenMatcher{};
    
    // 42 is positive, less than 100, and even
    EXPECT_TRUE(combined.match(42));
}

// Test: One matcher fails - should return false
TEST_F(MatchAllOfGenericTest_156, OneMatcherFails_ReturnsFalse_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{} && IsEvenMatcher{};
    
    // 43 is positive and less than 100, but NOT even
    EXPECT_FALSE(combined.match(43));
}

// Test: First matcher fails - should return false
TEST_F(MatchAllOfGenericTest_156, FirstMatcherFails_ReturnsFalse_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{} && IsEvenMatcher{};
    
    // -2 is NOT positive, but is less than 100 and is even
    EXPECT_FALSE(combined.match(-2));
}

// Test: Last matcher fails - should return false
TEST_F(MatchAllOfGenericTest_156, LastMatcherFails_ReturnsFalse_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{};
    
    // 200 is positive but NOT less than 100
    EXPECT_FALSE(combined.match(200));
}

// Test: All matchers fail - should return false
TEST_F(MatchAllOfGenericTest_156, AllMatchersFail_ReturnsFalse_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{} && IsEvenMatcher{};
    
    // -101 is not positive, not less than... wait, -101 IS less than 100
    // Let's use a value that fails all: impossible with these matchers together
    // -101 is not positive, IS less than 100, and is odd -> fails two of three
    // Just test that it fails
    EXPECT_FALSE(combined.match(-101));
}

// Test: Two matchers combined, both true
TEST_F(MatchAllOfGenericTest_156, TwoMatchers_BothTrue_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    EXPECT_TRUE(combined.match(4));
}

// Test: Two matchers combined, one false
TEST_F(MatchAllOfGenericTest_156, TwoMatchers_OneFalse_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    EXPECT_FALSE(combined.match(3)); // positive but odd
}

// Test: AlwaysTrue combined with AlwaysFalse should be false
TEST_F(MatchAllOfGenericTest_156, AlwaysTrueAndAlwaysFalse_ReturnsFalse_156) {
    auto combined = AlwaysTrueMatcher{} && AlwaysFalseMatcher{};
    
    EXPECT_FALSE(combined.match(0));
}

// Test: AlwaysTrue combined with AlwaysTrue should be true
TEST_F(MatchAllOfGenericTest_156, AlwaysTrueAndAlwaysTrue_ReturnsTrue_156) {
    auto combined = AlwaysTrueMatcher{} && AlwaysTrueMatcher{};
    
    EXPECT_TRUE(combined.match(0));
}

// Test: AlwaysFalse combined with AlwaysFalse should be false
TEST_F(MatchAllOfGenericTest_156, AlwaysFalseAndAlwaysFalse_ReturnsFalse_156) {
    auto combined = AlwaysFalseMatcher{} && AlwaysFalseMatcher{};
    
    EXPECT_FALSE(combined.match(0));
}

// Test: Boundary value - zero
TEST_F(MatchAllOfGenericTest_156, BoundaryValueZero_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    // 0 is not positive (0 > 0 is false), but is even
    EXPECT_FALSE(combined.match(0));
}

// Test: Boundary value - exactly 100
TEST_F(MatchAllOfGenericTest_156, BoundaryValueExactly100_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{};
    
    // 100 is positive but NOT less than 100
    EXPECT_FALSE(combined.match(100));
}

// Test: Boundary value - 99
TEST_F(MatchAllOfGenericTest_156, BoundaryValue99_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{};
    
    // 99 is positive and less than 100
    EXPECT_TRUE(combined.match(99));
}

// Test: String matchers combined
TEST_F(MatchAllOfGenericTest_156, StringMatchers_BothMatch_156) {
    auto combined = ContainsSubstringMatcher{"hello"} && LengthGreaterThanMatcher{3};
    
    EXPECT_TRUE(combined.match(std::string("say hello world")));
}

// Test: String matchers combined, one fails
TEST_F(MatchAllOfGenericTest_156, StringMatchers_OneFails_156) {
    auto combined = ContainsSubstringMatcher{"hello"} && LengthGreaterThanMatcher{3};
    
    // "hi" does not contain "hello" and length is not > 3
    EXPECT_FALSE(combined.match(std::string("hi")));
}

// Test: String matchers combined, substring not found
TEST_F(MatchAllOfGenericTest_156, StringMatchers_SubstringNotFound_156) {
    auto combined = ContainsSubstringMatcher{"hello"} && LengthGreaterThanMatcher{3};
    
    // "world abcdef" has length > 3 but doesn't contain "hello"
    EXPECT_FALSE(combined.match(std::string("world abcdef")));
}

// Test: describe() returns a non-empty string
TEST_F(MatchAllOfGenericTest_156, DescribeReturnsNonEmpty_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: describe() with multiple matchers contains meaningful info
TEST_F(MatchAllOfGenericTest_156, DescribeContainsMatcherDescriptions_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    std::string desc = combined.describe();
    // The description should mention both sub-matcher descriptions
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
}

// Test: Three matchers describe
TEST_F(MatchAllOfGenericTest_156, ThreeMatchersDescribe_156) {
    auto combined = IsPositiveMatcher{} && IsLessThan100Matcher{} && IsEvenMatcher{};
    
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is less than 100"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
}

// Test: Large positive value matching
TEST_F(MatchAllOfGenericTest_156, LargePositiveValue_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    EXPECT_TRUE(combined.match(1000000));
}

// Test: Negative even value
TEST_F(MatchAllOfGenericTest_156, NegativeEvenValue_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    // -4 is even but not positive
    EXPECT_FALSE(combined.match(-4));
}

// Test: Value of 1 (positive, odd)
TEST_F(MatchAllOfGenericTest_156, ValueOne_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    // 1 is positive but not even
    EXPECT_FALSE(combined.match(1));
}

// Test: Value of 2 (positive, even)
TEST_F(MatchAllOfGenericTest_156, ValueTwo_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    
    EXPECT_TRUE(combined.match(2));
}

// Test: Move semantics - combined matcher should be movable
TEST_F(MatchAllOfGenericTest_156, MoveConstruction_156) {
    auto combined = IsPositiveMatcher{} && IsEvenMatcher{};
    auto moved = std::move(combined);
    
    EXPECT_TRUE(moved.match(42));
    EXPECT_FALSE(moved.match(-1));
}
