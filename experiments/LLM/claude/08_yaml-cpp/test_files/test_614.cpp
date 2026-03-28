#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <list>
#include <string>
#include <vector>

// Test fixture for std::list decode tests
class ListDecodeTest_614 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Decoding a valid sequence of integers into std::list<int>
TEST_F(ListDecodeTest_614, DecodeIntListFromSequence_614) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);

    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

// Test: Decoding a valid sequence of strings into std::list<std::string>
TEST_F(ListDecodeTest_614, DecodeStringListFromSequence_614) {
    YAML::Node node;
    node.push_back("hello");
    node.push_back("world");

    std::list<std::string> result = node.as<std::list<std::string>>();

    ASSERT_EQ(result.size(), 2u);
    auto it = result.begin();
    EXPECT_EQ(*it, "hello"); ++it;
    EXPECT_EQ(*it, "world");
}

// Test: Decoding an empty sequence into std::list
TEST_F(ListDecodeTest_614, DecodeEmptySequence_614) {
    YAML::Node node(YAML::NodeType::Sequence);

    std::list<int> result = node.as<std::list<int>>();

    EXPECT_TRUE(result.empty());
}

// Test: Decoding a non-sequence node (scalar) should throw
TEST_F(ListDecodeTest_614, DecodeFromScalarThrows_614) {
    YAML::Node node("just a scalar");

    EXPECT_THROW(node.as<std::list<int>>(), YAML::TypedBadConversion<std::list<int>>);
}

// Test: Decoding a non-sequence node (map) should throw
TEST_F(ListDecodeTest_614, DecodeFromMapThrows_614) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";

    EXPECT_THROW(node.as<std::list<int>>(), YAML::TypedBadConversion<std::list<int>>);
}

// Test: Decoding a null node should throw
TEST_F(ListDecodeTest_614, DecodeFromNullNodeThrows_614) {
    YAML::Node node(YAML::NodeType::Null);

    EXPECT_THROW(node.as<std::list<int>>(), YAML::TypedBadConversion<std::list<int>>);
}

// Test: Decoding a single-element sequence
TEST_F(ListDecodeTest_614, DecodeSingleElementSequence_614) {
    YAML::Node node;
    node.push_back(42);

    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.front(), 42);
}

// Test: Decoding a sequence of doubles
TEST_F(ListDecodeTest_614, DecodeDoubleListFromSequence_614) {
    YAML::Node node;
    node.push_back(1.5);
    node.push_back(2.7);
    node.push_back(3.14);

    std::list<double> result = node.as<std::list<double>>();

    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_DOUBLE_EQ(*it, 1.5); ++it;
    EXPECT_DOUBLE_EQ(*it, 2.7); ++it;
    EXPECT_DOUBLE_EQ(*it, 3.14);
}

// Test: Decoding from YAML string
TEST_F(ListDecodeTest_614, DecodeListFromYAMLString_614) {
    YAML::Node node = YAML::Load("[10, 20, 30, 40]");

    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), 4u);
    auto it = result.begin();
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(*it, 20); ++it;
    EXPECT_EQ(*it, 30); ++it;
    EXPECT_EQ(*it, 40);
}

// Test: Decoding preserves order
TEST_F(ListDecodeTest_614, DecodePreservesOrder_614) {
    YAML::Node node = YAML::Load("[5, 3, 1, 4, 2]");

    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), 5u);
    std::vector<int> expected = {5, 3, 1, 4, 2};
    auto it = result.begin();
    for (size_t i = 0; i < expected.size(); ++i, ++it) {
        EXPECT_EQ(*it, expected[i]);
    }
}

// Test: Decoding with fallback when node is not a sequence
TEST_F(ListDecodeTest_614, DecodeWithFallbackOnScalar_614) {
    YAML::Node node("not a sequence");

    std::list<int> fallback = {99, 100};
    std::list<int> result = node.as<std::list<int>>(fallback);

    ASSERT_EQ(result.size(), 2u);
    auto it = result.begin();
    EXPECT_EQ(*it, 99); ++it;
    EXPECT_EQ(*it, 100);
}

// Test: Decoding with fallback when node is a valid sequence should return decoded value
TEST_F(ListDecodeTest_614, DecodeWithFallbackOnValidSequence_614) {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    std::list<int> fallback = {99};
    std::list<int> result = node.as<std::list<int>>(fallback);

    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

// Test: Decoding clears the existing list contents
TEST_F(ListDecodeTest_614, DecodeClearsExistingContents_614) {
    YAML::Node node = YAML::Load("[7, 8]");

    // We can verify indirectly by calling as<> which returns a fresh list
    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), 2u);
    auto it = result.begin();
    EXPECT_EQ(*it, 7); ++it;
    EXPECT_EQ(*it, 8);
}

// Test: Decoding a large sequence
TEST_F(ListDecodeTest_614, DecodeLargeSequence_614) {
    YAML::Node node(YAML::NodeType::Sequence);
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        node.push_back(i);
    }

    std::list<int> result = node.as<std::list<int>>();

    ASSERT_EQ(result.size(), static_cast<size_t>(count));
    int expected = 0;
    for (const auto& val : result) {
        EXPECT_EQ(val, expected);
        ++expected;
    }
}

// Test: Decoding a sequence of booleans
TEST_F(ListDecodeTest_614, DecodeBoolList_614) {
    YAML::Node node = YAML::Load("[true, false, true]");

    std::list<bool> result = node.as<std::list<bool>>();

    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_TRUE(*it); ++it;
    EXPECT_FALSE(*it); ++it;
    EXPECT_TRUE(*it);
}

// Test: Decoding undefined node should throw
TEST_F(ListDecodeTest_614, DecodeFromUndefinedNodeThrows_614) {
    YAML::Node node;
    YAML::Node undefined = node["nonexistent"];

    EXPECT_THROW(undefined.as<std::list<int>>(), YAML::TypedBadConversion<std::list<int>>);
}

// Test: Decoding nested lists (list of lists)
TEST_F(ListDecodeTest_614, DecodeNestedLists_614) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4], [5]]");

    std::list<std::list<int>> result = node.as<std::list<std::list<int>>>();

    ASSERT_EQ(result.size(), 3u);
    auto outer_it = result.begin();

    ASSERT_EQ(outer_it->size(), 2u);
    auto inner_it = outer_it->begin();
    EXPECT_EQ(*inner_it, 1); ++inner_it;
    EXPECT_EQ(*inner_it, 2);
    ++outer_it;

    ASSERT_EQ(outer_it->size(), 2u);
    inner_it = outer_it->begin();
    EXPECT_EQ(*inner_it, 3); ++inner_it;
    EXPECT_EQ(*inner_it, 4);
    ++outer_it;

    ASSERT_EQ(outer_it->size(), 1u);
    inner_it = outer_it->begin();
    EXPECT_EQ(*inner_it, 5);
}
