#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <set>
#include <string>
#include <sstream>

class StlEmitterSetTest_657 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test emitting an empty set
TEST_F(StlEmitterSetTest_657, EmitEmptySet_657) {
    std::set<int> emptySet;
    emitter << emptySet;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // An empty sequence should produce valid YAML
    EXPECT_FALSE(output.empty());
}

// Test emitting a set with a single integer element
TEST_F(StlEmitterSetTest_657, EmitSingleElementIntSet_657) {
    std::set<int> s;
    s.insert(42);
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test emitting a set with multiple integer elements
TEST_F(StlEmitterSetTest_657, EmitMultipleElementIntSet_657) {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test emitting a set of strings
TEST_F(StlEmitterSetTest_657, EmitStringSet_657) {
    std::set<std::string> s;
    s.insert("apple");
    s.insert("banana");
    s.insert("cherry");
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("apple"), std::string::npos);
    EXPECT_NE(output.find("banana"), std::string::npos);
    EXPECT_NE(output.find("cherry"), std::string::npos);
}

// Test that emitting a set produces a valid YAML sequence that can be parsed back
TEST_F(StlEmitterSetTest_657, EmitSetProducesValidYAML_657) {
    std::set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// Test that elements in the emitted set appear in sorted order (std::set is ordered)
TEST_F(StlEmitterSetTest_657, EmitSetElementsInOrder_657) {
    std::set<int> s;
    s.insert(30);
    s.insert(10);
    s.insert(20);
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

// Test emitting a set with negative integers
TEST_F(StlEmitterSetTest_657, EmitSetWithNegativeIntegers_657) {
    std::set<int> s;
    s.insert(-5);
    s.insert(0);
    s.insert(5);
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), -5);
    EXPECT_EQ(node[1].as<int>(), 0);
    EXPECT_EQ(node[2].as<int>(), 5);
}

// Test emitting a set with flow style
TEST_F(StlEmitterSetTest_657, EmitSetWithFlowStyle_657) {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    emitter << YAML::Flow << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Flow style should contain brackets
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test emitting a set to an ostream
TEST_F(StlEmitterSetTest_657, EmitSetToOstream_657) {
    std::ostringstream oss;
    YAML::Emitter streamEmitter(oss);
    std::set<int> s;
    s.insert(100);
    s.insert(200);
    streamEmitter << s;
    EXPECT_TRUE(streamEmitter.good());
    std::string output = oss.str();
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
}

// Test emitting a set with a single string element
TEST_F(StlEmitterSetTest_657, EmitSingleStringSet_657) {
    std::set<std::string> s;
    s.insert("hello");
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
}

// Test emitting a large set
TEST_F(StlEmitterSetTest_657, EmitLargeSet_657) {
    std::set<int> s;
    for (int i = 0; i < 100; ++i) {
        s.insert(i);
    }
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 100u);
}

// Test that the return value is the same emitter reference (chaining)
TEST_F(StlEmitterSetTest_657, ReturnValueIsEmitterReference_657) {
    std::set<int> s;
    s.insert(1);
    YAML::Emitter& ref = (emitter << s);
    EXPECT_EQ(&ref, &emitter);
}

// Test emitting a set of doubles
TEST_F(StlEmitterSetTest_657, EmitDoubleSet_657) {
    std::set<double> s;
    s.insert(1.5);
    s.insert(2.5);
    s.insert(3.5);
    emitter << s;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// Test emitting set as part of a map
TEST_F(StlEmitterSetTest_657, EmitSetAsMapValue_657) {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "numbers" << YAML::Value << s;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    ASSERT_TRUE(node.IsMap());
    ASSERT_TRUE(node["numbers"].IsSequence());
    EXPECT_EQ(node["numbers"].size(), 2u);
    EXPECT_EQ(node["numbers"][0].as<int>(), 1);
    EXPECT_EQ(node["numbers"][1].as<int>(), 2);
}

// Test size of output is non-zero for non-empty set
TEST_F(StlEmitterSetTest_657, EmitSetSizeNonZero_657) {
    std::set<int> s;
    s.insert(42);
    emitter << s;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test emitting set with block style (default)
TEST_F(StlEmitterSetTest_657, EmitSetBlockStyle_657) {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    emitter << YAML::Block << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Block style should contain dashes
    EXPECT_NE(output.find("- "), std::string::npos);
}
