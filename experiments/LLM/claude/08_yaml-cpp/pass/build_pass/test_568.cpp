#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

class NodeEndTest_568 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that end() on a default-constructed (valid, null) node returns a valid iterator
TEST_F(NodeEndTest_568, DefaultConstructedNodeEndReturnsIterator_568) {
    YAML::Node node;
    auto it = node.end();
    // For a null/undefined node, begin() should equal end()
    EXPECT_EQ(node.begin(), node.end());
}

// Test that end() on an empty sequence returns an iterator equal to begin()
TEST_F(NodeEndTest_568, EmptySequenceEndEqualsBegin_568) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.begin(), node.end());
}

// Test that end() on an empty map returns an iterator equal to begin()
TEST_F(NodeEndTest_568, EmptyMapEndEqualsBegin_568) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.begin(), node.end());
}

// Test that end() on a scalar node returns an iterator equal to begin()
TEST_F(NodeEndTest_568, ScalarNodeEndEqualsBegin_568) {
    YAML::Node node("hello");
    EXPECT_EQ(node.begin(), node.end());
}

// Test that end() on a sequence with elements does not equal begin()
TEST_F(NodeEndTest_568, NonEmptySequenceEndNotEqualsBegin_568) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    EXPECT_NE(node.begin(), node.end());
}

// Test that iterating from begin() to end() covers all elements in a sequence
TEST_F(NodeEndTest_568, SequenceIterationCoversAllElements_568) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test that iterating from begin() to end() covers all elements in a map
TEST_F(NodeEndTest_568, MapIterationCoversAllElements_568) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test that end() on a null-type node returns iterator equal to begin()
TEST_F(NodeEndTest_568, NullTypeNodeEndEqualsBegin_568) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_EQ(node.begin(), node.end());
}

// Test that end() on an undefined node returns iterator equal to begin()
TEST_F(NodeEndTest_568, UndefinedNodeEndEqualsBegin_568) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_EQ(node.begin(), node.end());
}

// Test end() with a parsed YAML sequence
TEST_F(NodeEndTest_568, ParsedSequenceEndIterator_568) {
    YAML::Node node = YAML::Load("[1, 2, 3, 4, 5]");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 5);
}

// Test end() with a parsed YAML map
TEST_F(NodeEndTest_568, ParsedMapEndIterator_568) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test that end() iterator is stable - calling it multiple times returns same result
TEST_F(NodeEndTest_568, EndIteratorIsStable_568) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    
    auto end1 = node.end();
    auto end2 = node.end();
    EXPECT_EQ(end1, end2);
}

// Test end() on a const node
TEST_F(NodeEndTest_568, ConstNodeEnd_568) {
    YAML::Node mutableNode;
    mutableNode.push_back("a");
    mutableNode.push_back("b");
    
    const YAML::Node& constNode = mutableNode;
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test that after removing an element, end() adjusts correctly
TEST_F(NodeEndTest_568, EndAfterRemoveFromMap_568) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    
    node.remove("b");
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test end() with single-element sequence
TEST_F(NodeEndTest_568, SingleElementSequenceEnd_568) {
    YAML::Node node;
    node.push_back(42);
    
    auto it = node.begin();
    EXPECT_NE(it, node.end());
    ++it;
    EXPECT_EQ(it, node.end());
}

// Test end() with a copied node
TEST_F(NodeEndTest_568, CopiedNodeEnd_568) {
    YAML::Node original;
    original.push_back(1);
    original.push_back(2);
    
    YAML::Node copy = original;
    
    int count = 0;
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test that accessing a non-existent key on a map and checking end still works
TEST_F(NodeEndTest_568, EndAfterAccessingNonExistentKey_568) {
    YAML::Node node = YAML::Load("{x: 1}");
    // Accessing a const node with non-existent key shouldn't modify the map
    const YAML::Node& constNode = node;
    YAML::Node val = constNode["nonexistent"];
    
    int count = 0;
    for (auto it = constNode.begin(); it != constNode.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 1);
}

// Test end() on nested sequences
TEST_F(NodeEndTest_568, NestedSequenceEnd_568) {
    YAML::Node node = YAML::Load("[[1,2],[3,4],[5,6]]");
    
    int outerCount = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        outerCount++;
        int innerCount = 0;
        for (auto inner = it->begin(); inner != it->end(); ++inner) {
            innerCount++;
        }
        EXPECT_EQ(innerCount, 2);
    }
    EXPECT_EQ(outerCount, 3);
}

// Test range-based for loop which depends on begin()/end()
TEST_F(NodeEndTest_568, RangeBasedForLoop_568) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    
    std::vector<int> values;
    for (const auto& elem : node) {
        values.push_back(elem.as<int>());
    }
    
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
}
