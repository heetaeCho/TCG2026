#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/iterator.h"
#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

// Test fixture for node_iterator tests
class NodeIteratorTest_184 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default-constructed iterators are equal
TEST_F(NodeIteratorTest_184, DefaultConstructedIteratorsAreEqual_184) {
    YAML::Node node;
    // Two default begin/end iterators on an undefined node should be equal
    YAML::const_iterator it1 = node.begin();
    YAML::const_iterator it2 = node.end();
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test sequence iteration
TEST_F(NodeIteratorTest_184, SequenceIterationBasic_184) {
    YAML::Node seq;
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(3);

    int count = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(3, count);
}

// Test sequence iterator dereference
TEST_F(NodeIteratorTest_184, SequenceIteratorDereference_184) {
    YAML::Node seq;
    seq.push_back("hello");
    seq.push_back("world");

    auto it = seq.begin();
    EXPECT_EQ("hello", it->as<std::string>());
    ++it;
    EXPECT_EQ("world", it->as<std::string>());
}

// Test map iteration
TEST_F(NodeIteratorTest_184, MapIterationBasic_184) {
    YAML::Node map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(2, count);
}

// Test map iterator dereference gives key-value pairs
TEST_F(NodeIteratorTest_184, MapIteratorDereferenceKeyValue_184) {
    YAML::Node map;
    map["alpha"] = 10;
    map["beta"] = 20;

    bool found_alpha = false;
    bool found_beta = false;
    for (auto it = map.begin(); it != map.end(); ++it) {
        std::string key = it->first.as<std::string>();
        int value = it->second.as<int>();
        if (key == "alpha" && value == 10) found_alpha = true;
        if (key == "beta" && value == 20) found_beta = true;
    }
    EXPECT_TRUE(found_alpha);
    EXPECT_TRUE(found_beta);
}

// Test post-increment operator on sequence
TEST_F(NodeIteratorTest_184, PostIncrementSequence_184) {
    YAML::Node seq;
    seq.push_back(42);
    seq.push_back(43);

    auto it = seq.begin();
    auto old_it = it++;
    EXPECT_EQ(42, old_it->as<int>());
    EXPECT_EQ(43, it->as<int>());
}

// Test pre-increment operator on sequence
TEST_F(NodeIteratorTest_184, PreIncrementSequence_184) {
    YAML::Node seq;
    seq.push_back(42);
    seq.push_back(43);

    auto it = seq.begin();
    auto& ref = ++it;
    EXPECT_EQ(43, ref->as<int>());
    EXPECT_EQ(43, it->as<int>());
}

// Test inequality operator
TEST_F(NodeIteratorTest_184, InequalityOperator_184) {
    YAML::Node seq;
    seq.push_back(1);
    seq.push_back(2);

    auto it = seq.begin();
    auto end = seq.end();
    EXPECT_TRUE(it != end);
    ++it;
    EXPECT_TRUE(it != end);
    ++it;
    EXPECT_FALSE(it != end);
}

// Test equality operator
TEST_F(NodeIteratorTest_184, EqualityOperator_184) {
    YAML::Node seq;
    seq.push_back(1);

    auto it1 = seq.begin();
    auto it2 = seq.begin();
    EXPECT_TRUE(it1 == it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
}

// Test empty sequence has begin == end
TEST_F(NodeIteratorTest_184, EmptySequenceBeginEqualsEnd_184) {
    YAML::Node seq(YAML::NodeType::Sequence);
    EXPECT_TRUE(seq.begin() == seq.end());
}

// Test empty map has begin == end
TEST_F(NodeIteratorTest_184, EmptyMapBeginEqualsEnd_184) {
    YAML::Node map(YAML::NodeType::Map);
    EXPECT_TRUE(map.begin() == map.end());
}

// Test scalar node has begin == end
TEST_F(NodeIteratorTest_184, ScalarNodeBeginEqualsEnd_184) {
    YAML::Node scalar("hello");
    EXPECT_TRUE(scalar.begin() == scalar.end());
}

// Test undefined node has begin == end
TEST_F(NodeIteratorTest_184, UndefinedNodeBeginEqualsEnd_184) {
    YAML::Node undef;
    EXPECT_TRUE(undef.begin() == undef.end());
}

// Test null node has begin == end
TEST_F(NodeIteratorTest_184, NullNodeBeginEqualsEnd_184) {
    YAML::Node null(YAML::NodeType::Null);
    EXPECT_TRUE(null.begin() == null.end());
}

// Test const_iterator from non-const iterator (conversion)
TEST_F(NodeIteratorTest_184, ConstIteratorConversion_184) {
    YAML::Node seq;
    seq.push_back(1);
    seq.push_back(2);

    YAML::iterator it = seq.begin();
    YAML::const_iterator cit = it;  // Should be convertible
    EXPECT_EQ(it->as<int>(), cit->as<int>());
}

// Test iteration over map with many entries
TEST_F(NodeIteratorTest_184, MapIterationManyEntries_184) {
    YAML::Node map;
    const int N = 100;
    for (int i = 0; i < N; i++) {
        map[std::to_string(i)] = i;
    }

    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        count++;
    }
    EXPECT_EQ(N, count);
}

// Test iteration over sequence with many entries
TEST_F(NodeIteratorTest_184, SequenceIterationManyEntries_184) {
    YAML::Node seq;
    const int N = 100;
    for (int i = 0; i < N; i++) {
        seq.push_back(i);
    }

    int count = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        count++;
    }
    EXPECT_EQ(N, count);
}

// Test sequence values are in order
TEST_F(NodeIteratorTest_184, SequenceValuesInOrder_184) {
    YAML::Node seq;
    seq.push_back(10);
    seq.push_back(20);
    seq.push_back(30);

    std::vector<int> values;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        values.push_back(it->as<int>());
    }
    ASSERT_EQ(3u, values.size());
    EXPECT_EQ(10, values[0]);
    EXPECT_EQ(20, values[1]);
    EXPECT_EQ(30, values[2]);
}

// Test range-based for loop on sequence
TEST_F(NodeIteratorTest_184, RangeBasedForSequence_184) {
    YAML::Node seq;
    seq.push_back("a");
    seq.push_back("b");

    std::vector<std::string> values;
    for (const auto& item : seq) {
        values.push_back(item.as<std::string>());
    }
    ASSERT_EQ(2u, values.size());
    EXPECT_EQ("a", values[0]);
    EXPECT_EQ("b", values[1]);
}

// Test range-based for loop on map
TEST_F(NodeIteratorTest_184, RangeBasedForMap_184) {
    YAML::Node map;
    map["x"] = 1;
    map["y"] = 2;

    std::map<std::string, int> result;
    for (const auto& item : map) {
        result[item.first.as<std::string>()] = item.second.as<int>();
    }
    EXPECT_EQ(1, result["x"]);
    EXPECT_EQ(2, result["y"]);
}

// Test single element sequence
TEST_F(NodeIteratorTest_184, SingleElementSequence_184) {
    YAML::Node seq;
    seq.push_back(999);

    auto it = seq.begin();
    EXPECT_NE(it, seq.end());
    EXPECT_EQ(999, it->as<int>());
    ++it;
    EXPECT_EQ(it, seq.end());
}

// Test single element map
TEST_F(NodeIteratorTest_184, SingleElementMap_184) {
    YAML::Node map;
    map["only"] = "one";

    auto it = map.begin();
    EXPECT_NE(it, map.end());
    EXPECT_EQ("only", it->first.as<std::string>());
    EXPECT_EQ("one", it->second.as<std::string>());
    ++it;
    EXPECT_EQ(it, map.end());
}

// Test post increment returns copy pointing to old position on map
TEST_F(NodeIteratorTest_184, PostIncrementMap_184) {
    YAML::Node map;
    map["a"] = 1;
    map["b"] = 2;

    auto it = map.begin();
    std::string first_key = it->first.as<std::string>();
    auto old_it = it++;
    EXPECT_EQ(first_key, old_it->first.as<std::string>());
    EXPECT_NE(it, old_it);
}

// Test parsed YAML sequence iteration
TEST_F(NodeIteratorTest_184, ParsedYAMLSequenceIteration_184) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->as<int>();
    }
    EXPECT_EQ(15, sum);
}

// Test parsed YAML map iteration
TEST_F(NodeIteratorTest_184, ParsedYAMLMapIteration_184) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        sum += it->second.as<int>();
    }
    EXPECT_EQ(6, sum);
}

// Test iterator arrow operator on sequence
TEST_F(NodeIteratorTest_184, ArrowOperatorSequence_184) {
    YAML::Node seq;
    seq.push_back("test_value");

    auto it = seq.begin();
    // Using -> to access Node methods
    EXPECT_TRUE(it->IsScalar());
    EXPECT_EQ("test_value", it->as<std::string>());
}

}  // namespace
