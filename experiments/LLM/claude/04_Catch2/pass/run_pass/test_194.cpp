#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the necessary headers
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

using Catch::Matchers::Detail::describe_multi_matcher;
using Catch::StringRef;

class DescribeMultiMatcherTest_194 : public ::testing::Test {
protected:
};

// Test with two descriptions and a simple combiner
TEST_F(DescribeMultiMatcherTest_194, TwoDescriptionsWithAnd_194) {
    std::string descriptions[] = {"is greater than 5", "is less than 10"};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_EQ(result, "( is greater than 5 and is less than 10 )");
}

// Test with two descriptions and "or" combiner
TEST_F(DescribeMultiMatcherTest_194, TwoDescriptionsWithOr_194) {
    std::string descriptions[] = {"is equal to 1", "is equal to 2"};
    StringRef combine(" or ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_EQ(result, "( is equal to 1 or is equal to 2 )");
}

// Test with a single description - no combiner should appear
TEST_F(DescribeMultiMatcherTest_194, SingleDescription_194) {
    std::string descriptions[] = {"matches something"};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 1);
    EXPECT_EQ(result, "( matches something )");
}

// Test with three descriptions
TEST_F(DescribeMultiMatcherTest_194, ThreeDescriptions_194) {
    std::string descriptions[] = {"A", "B", "C"};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 3);
    EXPECT_EQ(result, "( A and B and C )");
}

// Test with empty string descriptions
TEST_F(DescribeMultiMatcherTest_194, EmptyStringDescriptions_194) {
    std::string descriptions[] = {"", ""};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_EQ(result, "(  and  )");
}

// Test with a single empty description
TEST_F(DescribeMultiMatcherTest_194, SingleEmptyDescription_194) {
    std::string descriptions[] = {""};
    StringRef combine(" or ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 1);
    EXPECT_EQ(result, "(  )");
}

// Test with many descriptions
TEST_F(DescribeMultiMatcherTest_194, ManyDescriptions_194) {
    std::string descriptions[] = {"a", "b", "c", "d", "e"};
    StringRef combine(", ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 5);
    EXPECT_EQ(result, "( a, b, c, d, e )");
}

// Test result always starts with "( " and ends with " )"
TEST_F(DescribeMultiMatcherTest_194, ResultWrappedInParentheses_194) {
    std::string descriptions[] = {"foo", "bar"};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_TRUE(result.size() >= 4);
    EXPECT_EQ(result.substr(0, 2), "( ");
    EXPECT_EQ(result.substr(result.size() - 2), " )");
}

// Test with long descriptions
TEST_F(DescribeMultiMatcherTest_194, LongDescriptions_194) {
    std::string long_desc(200, 'x');
    std::string descriptions[] = {long_desc, long_desc};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    std::string expected = "( " + long_desc + " and " + long_desc + " )";
    EXPECT_EQ(result, expected);
}

// Test with single character combiner
TEST_F(DescribeMultiMatcherTest_194, SingleCharCombiner_194) {
    std::string descriptions[] = {"X", "Y", "Z"};
    StringRef combine(",");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 3);
    EXPECT_EQ(result, "( X,Y,Z )");
}

// Test with empty combiner
TEST_F(DescribeMultiMatcherTest_194, EmptyCombiner_194) {
    std::string descriptions[] = {"hello", "world"};
    StringRef combine("");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_EQ(result, "( helloworld )");
}

// Test with descriptions containing special characters
TEST_F(DescribeMultiMatcherTest_194, SpecialCharacterDescriptions_194) {
    std::string descriptions[] = {"contains \"quoted\"", "has (parens)"};
    StringRef combine(" and ");
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 2);
    EXPECT_EQ(result, "( contains \"quoted\" and has (parens) )");
}

// Test with descriptions from a vector
TEST_F(DescribeMultiMatcherTest_194, DescriptionsFromVector_194) {
    std::vector<std::string> descriptions = {"alpha", "beta", "gamma"};
    StringRef combine(" or ");
    std::string result = describe_multi_matcher(combine, descriptions.data(), descriptions.data() + descriptions.size());
    EXPECT_EQ(result, "( alpha or beta or gamma )");
}

// Test that two descriptions produce exactly one combiner instance
TEST_F(DescribeMultiMatcherTest_194, CombinerAppearsCorrectNumberOfTimes_194) {
    std::string descriptions[] = {"a", "b", "c", "d"};
    std::string combiner_str = " AND ";
    StringRef combine(combiner_str);
    std::string result = describe_multi_matcher(combine, descriptions, descriptions + 4);
    
    // Count occurrences of " AND " - should be 3 for 4 descriptions
    size_t count = 0;
    size_t pos = 0;
    while ((pos = result.find(combiner_str, pos)) != std::string::npos) {
        ++count;
        pos += combiner_str.size();
    }
    EXPECT_EQ(count, 3u);
}

} // namespace
