#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

class IteratorBaseTest_203 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default-constructed iterator equality
TEST_F(IteratorBaseTest_203, DefaultConstructedIteratorsAreEqual_203) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Sequence iteration - dereference returns scalar nodes
TEST_F(IteratorBaseTest_203, SequenceIteratorDereferencesScalarNodes_203) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 3);
}

// Test: Map iteration - dereference returns key-value pairs
TEST_F(IteratorBaseTest_203, MapIteratorDereferencesKeyValuePairs_203) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// Test: Prefix increment moves iterator forward in sequence
TEST_F(IteratorBaseTest_203, PrefixIncrementAdvancesSequenceIterator_203) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 10);
    ++it;
    EXPECT_EQ(it->as<int>(), 20);
    ++it;
    EXPECT_EQ(it->as<int>(), 30);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Postfix increment returns old value and advances
TEST_F(IteratorBaseTest_203, PostfixIncrementReturnsOldAndAdvances_203) {
    YAML::Node node = YAML::Load("[100, 200]");
    auto it = node.begin();
    auto old = it++;
    EXPECT_EQ(old->as<int>(), 100);
    EXPECT_EQ(it->as<int>(), 200);
}

// Test: Equality operator for same position
TEST_F(IteratorBaseTest_203, EqualityOperatorSamePosition_203) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test: Inequality operator for different positions
TEST_F(IteratorBaseTest_203, InequalityOperatorDifferentPositions_203) {
    YAML::Node node = YAML::Load("[1, 2]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it2;
    EXPECT_TRUE(it1 != it2);
    EXPECT_FALSE(it1 == it2);
}

// Test: Empty sequence has begin == end
TEST_F(IteratorBaseTest_203, EmptySequenceBeginEqualsEnd_203) {
    YAML::Node node = YAML::Load("[]");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Empty map has begin == end
TEST_F(IteratorBaseTest_203, EmptyMapBeginEqualsEnd_203) {
    YAML::Node node = YAML::Load("{}");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Scalar node has begin == end (no iteration)
TEST_F(IteratorBaseTest_203, ScalarNodeBeginEqualsEnd_203) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Null node has begin == end
TEST_F(IteratorBaseTest_203, NullNodeBeginEqualsEnd_203) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

// Test: Sequence with single element
TEST_F(IteratorBaseTest_203, SingleElementSequenceIteration_203) {
    YAML::Node node = YAML::Load("[42]");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<int>(), 42);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Map with single entry
TEST_F(IteratorBaseTest_203, SingleEntryMapIteration_203) {
    YAML::Node node = YAML::Load("{key: value}");
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Dereference operator returns correct value_type for sequence
TEST_F(IteratorBaseTest_203, DereferenceOperatorSequenceReturnsNode_203) {
    YAML::Node node = YAML::Load("[hello]");
    auto it = node.begin();
    auto val = *it;
    EXPECT_EQ(val.as<std::string>(), "hello");
}

// Test: Dereference operator returns correct value_type for map
TEST_F(IteratorBaseTest_203, DereferenceOperatorMapReturnsKeyValuePair_203) {
    YAML::Node node = YAML::Load("{foo: bar}");
    auto it = node.begin();
    EXPECT_EQ((*it).first.as<std::string>(), "foo");
    EXPECT_EQ((*it).second.as<std::string>(), "bar");
}

// Test: Nested sequence iteration
TEST_F(IteratorBaseTest_203, NestedSequenceIteration_203) {
    YAML::Node node = YAML::Load("[[1, 2], [3, 4]]");
    auto it = node.begin();
    YAML::Node first = *it;
    EXPECT_TRUE(first.IsSequence());
    EXPECT_EQ(first[0].as<int>(), 1);
    EXPECT_EQ(first[1].as<int>(), 2);
    ++it;
    YAML::Node second = *it;
    EXPECT_TRUE(second.IsSequence());
    EXPECT_EQ(second[0].as<int>(), 3);
    EXPECT_EQ(second[1].as<int>(), 4);
}

// Test: Nested map iteration
TEST_F(IteratorBaseTest_203, NestedMapIteration_203) {
    YAML::Node node = YAML::Load("{outer: {inner: val}}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "outer");
    EXPECT_TRUE(it->second.IsMap());
    EXPECT_EQ(it->second["inner"].as<std::string>(), "val");
}

// Test: Iteration count matches sequence size
TEST_F(IteratorBaseTest_203, IterationCountMatchesSequenceSize_203) {
    YAML::Node node = YAML::Load("[a, b, c, d, e]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 5);
}

// Test: Iteration count matches map size
TEST_F(IteratorBaseTest_203, IterationCountMatchesMapSize_203) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test: Arrow operator on sequence iterator
TEST_F(IteratorBaseTest_203, ArrowOperatorSequence_203) {
    YAML::Node node = YAML::Load("[test_string]");
    auto it = node.begin();
    // Arrow operator should allow accessing Node methods
    EXPECT_TRUE(it->IsScalar());
    EXPECT_EQ(it->as<std::string>(), "test_string");
}

// Test: Arrow operator on map iterator
TEST_F(IteratorBaseTest_203, ArrowOperatorMap_203) {
    YAML::Node node = YAML::Load("{x: y}");
    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "x");
    EXPECT_EQ(it->second.as<std::string>(), "y");
}

// Test: Copy construction of iterator (const from non-const via template)
TEST_F(IteratorBaseTest_203, ConstIteratorFromNonConst_203) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    YAML::iterator it = node.begin();
    YAML::const_iterator cit = it;
    EXPECT_EQ(cit->as<int>(), 1);
}

// Test: Multiple iterators on same node are independent
TEST_F(IteratorBaseTest_203, MultipleIteratorsIndependent_203) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it1;
    EXPECT_EQ(it1->as<int>(), 20);
    EXPECT_EQ(it2->as<int>(), 10);
}

// Test: Iteration over sequence with mixed types
TEST_F(IteratorBaseTest_203, MixedTypeSequenceIteration_203) {
    YAML::Node node = YAML::Load("[1, hello, 3.14, true]");
    auto it = node.begin();
    EXPECT_EQ(it->as<int>(), 1);
    ++it;
    EXPECT_EQ(it->as<std::string>(), "hello");
    ++it;
    EXPECT_NEAR(it->as<double>(), 3.14, 0.001);
    ++it;
    EXPECT_EQ(it->as<bool>(), true);
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test: Large sequence iteration
TEST_F(IteratorBaseTest_203, LargeSequenceIteration_203) {
    std::string yaml = "[";
    for (int i = 0; i < 1000; i++) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";
    YAML::Node node = YAML::Load(yaml);
    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 1000);
    EXPECT_EQ(sum, 999 * 1000 / 2);
}

// Test: Map with complex keys
TEST_F(IteratorBaseTest_203, MapWithStringKeysIteration_203) {
    YAML::Node node = YAML::Load("{long_key_name: value1, another_key: value2}");
    bool foundFirst = false, foundSecond = false;
    for (auto it = node.begin(); it != node.end(); ++it) {
        std::string key = it->first.as<std::string>();
        if (key == "long_key_name") {
            EXPECT_EQ(it->second.as<std::string>(), "value1");
            foundFirst = true;
        } else if (key == "another_key") {
            EXPECT_EQ(it->second.as<std::string>(), "value2");
            foundSecond = true;
        }
    }
    EXPECT_TRUE(foundFirst);
    EXPECT_TRUE(foundSecond);
}

// Test: Range-based for loop on sequence
TEST_F(IteratorBaseTest_203, RangeBasedForSequence_203) {
    YAML::Node node = YAML::Load("[5, 10, 15]");
    std::vector<int> values;
    for (const auto& elem : node) {
        values.push_back(elem.as<int>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 5);
    EXPECT_EQ(values[1], 10);
    EXPECT_EQ(values[2], 15);
}

// Test: Range-based for loop on map
TEST_F(IteratorBaseTest_203, RangeBasedForMap_203) {
    YAML::Node node = YAML::Load("{k1: v1, k2: v2}");
    std::map<std::string, std::string> result;
    for (const auto& kv : node) {
        result[kv.first.as<std::string>()] = kv.second.as<std::string>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["k1"], "v1");
    EXPECT_EQ(result["k2"], "v2");
}
