#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/catch_tostring.hpp>
#include <gtest/gtest.h>
#include <string>
#include <array>
#include <utility>

// A simple matcher that implements the required interface for testing
template<typename T>
struct SimpleMatcher : Catch::Matchers::MatcherBase<T> {
    std::string m_description;

    SimpleMatcher(std::string desc) : m_description(std::move(desc)) {}

    bool match(T const&) const override { return false; }

    std::string describe() const override {
        return m_description;
    }
};

class DescribeMultiMatcherTest_155 : public ::testing::Test {
protected:
};

TEST_F(DescribeMultiMatcherTest_155, SingleMatcher_155) {
    SimpleMatcher<int> m1("equals 42");
    
    std::array<void const*, 1> matchers{{ &m1 }};
    
    std::string result = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>>(
        Catch::StringRef(" and "),
        matchers,
        std::index_sequence<0>{}
    );
    
    // With a single matcher, the result should contain the matcher's description
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("equals 42"), std::string::npos);
}

TEST_F(DescribeMultiMatcherTest_155, TwoMatchers_155) {
    SimpleMatcher<int> m1("equals 1");
    SimpleMatcher<int> m2("equals 2");
    
    std::array<void const*, 2> matchers{{ &m1, &m2 }};
    
    std::string result = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>, SimpleMatcher<int>>(
        Catch::StringRef(" and "),
        matchers,
        std::index_sequence<0, 1>{}
    );
    
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("equals 1"), std::string::npos);
    EXPECT_NE(result.find("equals 2"), std::string::npos);
    EXPECT_NE(result.find(" and "), std::string::npos);
}

TEST_F(DescribeMultiMatcherTest_155, ThreeMatchers_155) {
    SimpleMatcher<int> m1("is positive");
    SimpleMatcher<int> m2("is even");
    SimpleMatcher<int> m3("is less than 100");
    
    std::array<void const*, 3> matchers{{ &m1, &m2, &m3 }};
    
    std::string result = Catch::Matchers::Detail::describe_multi_matcher<
        SimpleMatcher<int>, SimpleMatcher<int>, SimpleMatcher<int>>(
        Catch::StringRef(" or "),
        matchers,
        std::index_sequence<0, 1, 2>{}
    );
    
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("is positive"), std::string::npos);
    EXPECT_NE(result.find("is even"), std::string::npos);
    EXPECT_NE(result.find("is less than 100"), std::string::npos);
    EXPECT_NE(result.find(" or "), std::string::npos);
}

TEST_F(DescribeMultiMatcherTest_155, CombineStringUsedBetweenMatchers_155) {
    SimpleMatcher<int> m1("A");
    SimpleMatcher<int> m2("B");
    
    std::array<void const*, 2> matchers{{ &m1, &m2 }};
    
    std::string result_and = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>, SimpleMatcher<int>>(
        Catch::StringRef(" and "),
        matchers,
        std::index_sequence<0, 1>{}
    );
    
    std::string result_or = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>, SimpleMatcher<int>>(
        Catch::StringRef(" or "),
        matchers,
        std::index_sequence<0, 1>{}
    );
    
    // Different combine strings should produce different results
    EXPECT_NE(result_and, result_or);
}

TEST_F(DescribeMultiMatcherTest_155, EmptyDescriptionMatchers_155) {
    SimpleMatcher<int> m1("");
    SimpleMatcher<int> m2("");
    
    std::array<void const*, 2> matchers{{ &m1, &m2 }};
    
    std::string result = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>, SimpleMatcher<int>>(
        Catch::StringRef(" and "),
        matchers,
        std::index_sequence<0, 1>{}
    );
    
    // Should not crash; result may contain just the combine string parts
    // We just verify it doesn't throw/crash
    EXPECT_TRUE(true);
}

TEST_F(DescribeMultiMatcherTest_155, MixedMatcherTypes_155) {
    SimpleMatcher<int> m1("int matcher");
    SimpleMatcher<double> m2("double matcher");
    
    std::array<void const*, 2> matchers{{ &m1, &m2 }};
    
    std::string result = Catch::Matchers::Detail::describe_multi_matcher<SimpleMatcher<int>, SimpleMatcher<double>>(
        Catch::StringRef(" and "),
        matchers,
        std::index_sequence<0, 1>{}
    );
    
    EXPECT_NE(result.find("int matcher"), std::string::npos);
    EXPECT_NE(result.find("double matcher"), std::string::npos);
}
