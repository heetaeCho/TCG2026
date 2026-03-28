#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// Include the header under test
#include "catch2/matchers/catch_matchers.hpp"

// We need to work with Catch2's matcher infrastructure
// Let's create concrete matcher implementations for testing purposes

namespace {

using namespace Catch::Matchers;

// A simple concrete matcher for testing purposes
template <typename T>
class SimpleMatcher : public Catch::Matchers::MatcherBase<T> {
    T m_expected;
    std::string m_description;
    bool m_result;
public:
    SimpleMatcher(T expected, std::string desc, bool result = true)
        : m_expected(expected), m_description(std::move(desc)), m_result(result) {}

    bool match(T const& arg) const override {
        return m_result;
    }

    std::string describe() const override {
        return m_description;
    }
};

// Test fixture
class MatchAllOfTest_136 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that describe() with no matchers returns "( )"
TEST_F(MatchAllOfTest_136, DescribeWithNoMatchers_136) {
    Catch::Matchers::Detail::MatchAllOf<int> allOf;
    std::string desc = allOf.describe();
    EXPECT_EQ(desc, "( )");
}

// Test that describe() with one matcher returns "( <matcher_desc> )"
TEST_F(MatchAllOfTest_136, DescribeWithOneMatcher_136) {
    SimpleMatcher<int> m1(42, "equals 42");
    
    auto allOf = Catch::Matchers::Detail::MatchAllOf<int>();
    // We need to use the operator&& or similar to combine matchers
    // Based on Catch2 API, MatchAllOf is typically built via operator&&
    // But since we only have the class, let's test via the public interface
    
    // If MatchAllOf doesn't expose a way to add matchers directly through public API,
    // we may need to use Catch2's operator&& which returns MatchAllOf
    auto combined = m1 && SimpleMatcher<int>(0, "placeholder", true);
    // Actually, let's try the Catch2 way of combining
    // The operator&& on MatcherBase should produce a MatchAllOf
    
    std::string desc = combined.describe();
    // Should contain "and" between the two descriptions
    EXPECT_NE(desc.find("equals 42"), std::string::npos);
    EXPECT_NE(desc.find("placeholder"), std::string::npos);
    EXPECT_NE(desc.find(" and "), std::string::npos);
}

// Test that match() with all matching matchers returns true
TEST_F(MatchAllOfTest_136, MatchAllTrue_136) {
    SimpleMatcher<int> m1(42, "always true", true);
    SimpleMatcher<int> m2(42, "also true", true);
    
    auto combined = m1 && m2;
    EXPECT_TRUE(combined.match(42));
}

// Test that match() returns false when first matcher fails
TEST_F(MatchAllOfTest_136, MatchFirstFalse_136) {
    SimpleMatcher<int> m1(42, "always false", false);
    SimpleMatcher<int> m2(42, "always true", true);
    
    auto combined = m1 && m2;
    EXPECT_FALSE(combined.match(42));
}

// Test that match() returns false when second matcher fails
TEST_F(MatchAllOfTest_136, MatchSecondFalse_136) {
    SimpleMatcher<int> m1(42, "always true", true);
    SimpleMatcher<int> m2(42, "always false", false);
    
    auto combined = m1 && m2;
    EXPECT_FALSE(combined.match(42));
}

// Test that match() returns false when all matchers fail
TEST_F(MatchAllOfTest_136, MatchAllFalse_136) {
    SimpleMatcher<int> m1(42, "false1", false);
    SimpleMatcher<int> m2(42, "false2", false);
    
    auto combined = m1 && m2;
    EXPECT_FALSE(combined.match(42));
}

// Test describe with multiple matchers chained
TEST_F(MatchAllOfTest_136, DescribeWithThreeMatchers_136) {
    SimpleMatcher<int> m1(1, "cond1", true);
    SimpleMatcher<int> m2(2, "cond2", true);
    SimpleMatcher<int> m3(3, "cond3", true);
    
    auto combined = m1 && m2 && m3;
    std::string desc = combined.describe();
    
    // Should contain all three descriptions
    EXPECT_NE(desc.find("cond1"), std::string::npos);
    EXPECT_NE(desc.find("cond2"), std::string::npos);
    EXPECT_NE(desc.find("cond3"), std::string::npos);
    
    // Should start with "( " and end with " )"
    EXPECT_EQ(desc.substr(0, 2), "( ");
    EXPECT_EQ(desc.substr(desc.size() - 2), " )");
}

// Test that describe format uses " and " separator correctly between matchers
TEST_F(MatchAllOfTest_136, DescribeFormatAndSeparator_136) {
    SimpleMatcher<int> m1(1, "A", true);
    SimpleMatcher<int> m2(2, "B", true);
    
    auto combined = m1 && m2;
    std::string desc = combined.describe();
    
    // Expected format: "( A and B )"
    EXPECT_NE(desc.find("A and B"), std::string::npos);
}

// Test with string type
TEST_F(MatchAllOfTest_136, MatchWithStringType_136) {
    SimpleMatcher<std::string> m1("hello", "starts with h", true);
    SimpleMatcher<std::string> m2("hello", "ends with o", true);
    
    auto combined = m1 && m2;
    EXPECT_TRUE(combined.match("hello"));
    
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("starts with h"), std::string::npos);
    EXPECT_NE(desc.find("ends with o"), std::string::npos);
}

// Test that MatchAllOf is move constructible
TEST_F(MatchAllOfTest_136, MoveConstruction_136) {
    SimpleMatcher<int> m1(1, "cond1", true);
    SimpleMatcher<int> m2(2, "cond2", true);
    
    auto combined = m1 && m2;
    auto moved = std::move(combined);
    
    EXPECT_TRUE(moved.match(42));
    std::string desc = moved.describe();
    EXPECT_NE(desc.find("cond1"), std::string::npos);
    EXPECT_NE(desc.find("cond2"), std::string::npos);
}

// Test chaining many matchers
TEST_F(MatchAllOfTest_136, ChainManyMatchers_136) {
    SimpleMatcher<int> m1(1, "a", true);
    SimpleMatcher<int> m2(2, "b", true);
    SimpleMatcher<int> m3(3, "c", true);
    SimpleMatcher<int> m4(4, "d", true);
    SimpleMatcher<int> m5(5, "e", false);  // last one fails
    
    auto combined = m1 && m2 && m3 && m4 && m5;
    EXPECT_FALSE(combined.match(1));
}

// Test that when all of many matchers pass, result is true
TEST_F(MatchAllOfTest_136, ChainManyMatchersAllPass_136) {
    SimpleMatcher<int> m1(1, "a", true);
    SimpleMatcher<int> m2(2, "b", true);
    SimpleMatcher<int> m3(3, "c", true);
    SimpleMatcher<int> m4(4, "d", true);
    
    auto combined = m1 && m2 && m3 && m4;
    EXPECT_TRUE(combined.match(1));
}

// Test describe with empty description matchers
TEST_F(MatchAllOfTest_136, DescribeWithEmptyMatcherDescriptions_136) {
    SimpleMatcher<int> m1(1, "", true);
    SimpleMatcher<int> m2(2, "", true);
    
    auto combined = m1 && m2;
    std::string desc = combined.describe();
    
    // Should still have the structure "( " ... " and " ... " )"
    EXPECT_EQ(desc.substr(0, 2), "( ");
    EXPECT_EQ(desc.substr(desc.size() - 2), " )");
    EXPECT_NE(desc.find(" and "), std::string::npos);
}

} // anonymous namespace
