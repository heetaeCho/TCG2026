#include <gtest/gtest.h>
#include <array>
#include <utility>
#include <type_traits>
#include <string>

// We need to include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

// Since we're testing a template function that expects matchers with a `match` method,
// we need to create concrete matcher types that follow the expected interface.

// A simple matcher that checks if an integer is greater than a threshold
struct GreaterThanMatcher {
    int threshold;
    explicit GreaterThanMatcher(int t) : threshold(t) {}
    bool match(int const& arg) const { return arg > threshold; }
};

// A simple matcher that checks if an integer is less than a threshold
struct LessThanMatcher {
    int threshold;
    explicit LessThanMatcher(int t) : threshold(t) {}
    bool match(int const& arg) const { return arg < threshold; }
};

// A matcher that always returns true
struct AlwaysTrueMatcher {
    bool match(int const& /*arg*/) const { return true; }
};

// A matcher that always returns false
struct AlwaysFalseMatcher {
    bool match(int const& /*arg*/) const { return false; }
};

// A matcher for strings - checks if string contains a substring
struct ContainsMatcher {
    std::string substring;
    explicit ContainsMatcher(std::string s) : substring(std::move(s)) {}
    bool match(std::string const& arg) const {
        return arg.find(substring) != std::string::npos;
    }
};

// A matcher for strings - checks if string starts with a prefix
struct StartsWithMatcher {
    std::string prefix;
    explicit StartsWithMatcher(std::string p) : prefix(std::move(p)) {}
    bool match(std::string const& arg) const {
        return arg.substr(0, prefix.size()) == prefix;
    }
};

// We need to handle the base case of match_all_of. The recursive template
// in the header handles the case with at least one index. We need to check
// if there's a base case defined. Looking at the code, we see the recursive
// call reduces the index sequence. There should be a base case for empty
// index_sequence. Let's assume it exists and returns true.

// Since the header only shows the recursive case, the base case must exist
// elsewhere in the same header or a related header. For testing purposes,
// we'll test scenarios that exercise the recursive template.

class MatchAllOfTest_152 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Single matcher that matches - should return true
TEST_F(MatchAllOfTest_152, SingleMatcherMatches_152) {
    GreaterThanMatcher m1(5);
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    // match_all_of with a single matcher that should match
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher>(
        10, matchers, std::index_sequence<0>{}
    );
    EXPECT_TRUE(result);
}

// Test: Single matcher that does not match - should return false
TEST_F(MatchAllOfTest_152, SingleMatcherDoesNotMatch_152) {
    GreaterThanMatcher m1(15);
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher>(
        10, matchers, std::index_sequence<0>{}
    );
    EXPECT_FALSE(result);
}

// Test: Two matchers both match - should return true
TEST_F(MatchAllOfTest_152, TwoMatchersBothMatch_152) {
    GreaterThanMatcher m1(5);
    LessThanMatcher m2(20);
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        10, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_TRUE(result);
}

// Test: Two matchers, first fails - should return false (short-circuit)
TEST_F(MatchAllOfTest_152, TwoMatchersFirstFails_152) {
    GreaterThanMatcher m1(15);  // 10 > 15 is false
    LessThanMatcher m2(20);     // 10 < 20 is true
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        10, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_FALSE(result);
}

// Test: Two matchers, second fails - should return false
TEST_F(MatchAllOfTest_152, TwoMatchersSecondFails_152) {
    GreaterThanMatcher m1(5);   // 10 > 5 is true
    LessThanMatcher m2(8);      // 10 < 8 is false
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        10, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_FALSE(result);
}

// Test: Two matchers, both fail - should return false
TEST_F(MatchAllOfTest_152, TwoMatchersBothFail_152) {
    GreaterThanMatcher m1(15);  // 10 > 15 is false
    LessThanMatcher m2(5);      // 10 < 5 is false
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        10, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_FALSE(result);
}

// Test: Three matchers all match
TEST_F(MatchAllOfTest_152, ThreeMatchersAllMatch_152) {
    GreaterThanMatcher m1(5);
    LessThanMatcher m2(20);
    AlwaysTrueMatcher m3;
    std::array<void const*, 3> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2),
        static_cast<void const*>(&m3)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher, AlwaysTrueMatcher>(
        10, matchers, std::index_sequence<0, 1, 2>{}
    );
    EXPECT_TRUE(result);
}

// Test: Three matchers, last one fails
TEST_F(MatchAllOfTest_152, ThreeMatchersLastFails_152) {
    GreaterThanMatcher m1(5);
    LessThanMatcher m2(20);
    AlwaysFalseMatcher m3;
    std::array<void const*, 3> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2),
        static_cast<void const*>(&m3)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher, AlwaysFalseMatcher>(
        10, matchers, std::index_sequence<0, 1, 2>{}
    );
    EXPECT_FALSE(result);
}

// Test: AlwaysTrue matcher
TEST_F(MatchAllOfTest_152, AlwaysTrueSingleMatcher_152) {
    AlwaysTrueMatcher m1;
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    bool result = Catch::Matchers::Detail::match_all_of<AlwaysTrueMatcher>(
        42, matchers, std::index_sequence<0>{}
    );
    EXPECT_TRUE(result);
}

// Test: AlwaysFalse matcher
TEST_F(MatchAllOfTest_152, AlwaysFalseSingleMatcher_152) {
    AlwaysFalseMatcher m1;
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    bool result = Catch::Matchers::Detail::match_all_of<AlwaysFalseMatcher>(
        42, matchers, std::index_sequence<0>{}
    );
    EXPECT_FALSE(result);
}

// Test: Boundary value - matcher with exact boundary
TEST_F(MatchAllOfTest_152, BoundaryValueExact_152) {
    GreaterThanMatcher m1(10);  // 10 > 10 is false (strictly greater)
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher>(
        10, matchers, std::index_sequence<0>{}
    );
    EXPECT_FALSE(result);
}

// Test: Boundary value - just above threshold
TEST_F(MatchAllOfTest_152, BoundaryValueJustAbove_152) {
    GreaterThanMatcher m1(10);  // 11 > 10 is true
    std::array<void const*, 1> matchers = { static_cast<void const*>(&m1) };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher>(
        11, matchers, std::index_sequence<0>{}
    );
    EXPECT_TRUE(result);
}

// Test: String matchers - two string matchers both match
TEST_F(MatchAllOfTest_152, StringMatchersBothMatch_152) {
    ContainsMatcher m1("world");
    StartsWithMatcher m2("hello");
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    std::string testStr = "hello world";
    bool result = Catch::Matchers::Detail::match_all_of<ContainsMatcher, StartsWithMatcher>(
        testStr, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_TRUE(result);
}

// Test: String matchers - first matches, second doesn't
TEST_F(MatchAllOfTest_152, StringMatchersSecondFails_152) {
    ContainsMatcher m1("world");
    StartsWithMatcher m2("goodbye");
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    std::string testStr = "hello world";
    bool result = Catch::Matchers::Detail::match_all_of<ContainsMatcher, StartsWithMatcher>(
        testStr, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_FALSE(result);
}

// Test: Negative values
TEST_F(MatchAllOfTest_152, NegativeValues_152) {
    GreaterThanMatcher m1(-10);
    LessThanMatcher m2(0);
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        -5, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_TRUE(result);
}

// Test: Zero value with matchers
TEST_F(MatchAllOfTest_152, ZeroValue_152) {
    GreaterThanMatcher m1(-1);
    LessThanMatcher m2(1);
    std::array<void const*, 2> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<GreaterThanMatcher, LessThanMatcher>(
        0, matchers, std::index_sequence<0, 1>{}
    );
    EXPECT_TRUE(result);
}

// Test: Multiple AlwaysTrue matchers
TEST_F(MatchAllOfTest_152, MultipleAlwaysTrueMatchers_152) {
    AlwaysTrueMatcher m1, m2, m3;
    std::array<void const*, 3> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2),
        static_cast<void const*>(&m3)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<AlwaysTrueMatcher, AlwaysTrueMatcher, AlwaysTrueMatcher>(
        0, matchers, std::index_sequence<0, 1, 2>{}
    );
    EXPECT_TRUE(result);
}

// Test: Mixed AlwaysTrue and AlwaysFalse matchers
TEST_F(MatchAllOfTest_152, MixedAlwaysTrueAndFalse_152) {
    AlwaysTrueMatcher m1;
    AlwaysFalseMatcher m2;
    AlwaysTrueMatcher m3;
    std::array<void const*, 3> matchers = {
        static_cast<void const*>(&m1),
        static_cast<void const*>(&m2),
        static_cast<void const*>(&m3)
    };
    
    bool result = Catch::Matchers::Detail::match_all_of<AlwaysTrueMatcher, AlwaysFalseMatcher, AlwaysTrueMatcher>(
        0, matchers, std::index_sequence<0, 1, 2>{}
    );
    EXPECT_FALSE(result);
}
