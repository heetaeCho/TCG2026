#include <gtest/gtest.h>
#include <map>
#include <string>
#include <sstream>
#include "yaml-cpp/yaml.h"

class StlEmitterTest_658 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test: Emitting an empty map produces valid YAML empty map
TEST_F(StlEmitterTest_658, EmptyMap_658) {
    std::map<std::string, std::string> m;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // An empty map should produce "{}" in flow or block notation
    EXPECT_FALSE(output.empty());
}

// Test: Emitting a single-element map
TEST_F(StlEmitterTest_658, SingleElementMap_658) {
    std::map<std::string, std::string> m;
    m["key1"] = "value1";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
}

// Test: Emitting a multi-element map contains all keys and values
TEST_F(StlEmitterTest_658, MultiElementMap_658) {
    std::map<std::string, std::string> m;
    m["alpha"] = "one";
    m["beta"] = "two";
    m["gamma"] = "three";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("alpha"), std::string::npos);
    EXPECT_NE(output.find("one"), std::string::npos);
    EXPECT_NE(output.find("beta"), std::string::npos);
    EXPECT_NE(output.find("two"), std::string::npos);
    EXPECT_NE(output.find("gamma"), std::string::npos);
    EXPECT_NE(output.find("three"), std::string::npos);
}

// Test: Emitting a map with integer keys and values
TEST_F(StlEmitterTest_658, IntIntMap_658) {
    std::map<int, int> m;
    m[1] = 10;
    m[2] = 20;
    m[3] = 30;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// Test: Emitting a map with string keys and integer values
TEST_F(StlEmitterTest_658, StringIntMap_658) {
    std::map<std::string, int> m;
    m["count"] = 42;
    m["total"] = 100;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("total"), std::string::npos);
    EXPECT_NE(output.find("100"), std::string::npos);
}

// Test: Emitting a map with integer keys and string values
TEST_F(StlEmitterTest_658, IntStringMap_658) {
    std::map<int, std::string> m;
    m[1] = "hello";
    m[2] = "world";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("hello"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("world"), std::string::npos);
}

// Test: Emitting a map to a stream
TEST_F(StlEmitterTest_658, EmitToStream_658) {
    std::stringstream ss;
    YAML::Emitter streamEmitter(ss);
    std::map<std::string, std::string> m;
    m["foo"] = "bar";
    streamEmitter << m;
    EXPECT_TRUE(streamEmitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("foo"), std::string::npos);
    EXPECT_NE(output.find("bar"), std::string::npos);
}

// Test: Emitting a map in flow format
TEST_F(StlEmitterTest_658, FlowFormatMap_658) {
    emitter << YAML::Flow;
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Flow maps typically use { and }
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: Emitting a map in block format
TEST_F(StlEmitterTest_658, BlockFormatMap_658) {
    emitter << YAML::Block;
    std::map<std::string, int> m;
    m["x"] = 10;
    m["y"] = 20;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("x"), std::string::npos);
    EXPECT_NE(output.find("10"), std::string::npos);
}

// Test: Output size is non-zero for non-empty map
TEST_F(StlEmitterTest_658, SizeNonZeroForNonEmptyMap_658) {
    std::map<std::string, std::string> m;
    m["key"] = "val";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str returns non-null for emitted map
TEST_F(StlEmitterTest_658, CStrNonNull_658) {
    std::map<std::string, std::string> m;
    m["test"] = "data";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Emitting map preserves key ordering (std::map is sorted)
TEST_F(StlEmitterTest_658, KeyOrdering_658) {
    std::map<std::string, int> m;
    m["cherry"] = 3;
    m["apple"] = 1;
    m["banana"] = 2;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // std::map is sorted, so "apple" should appear before "banana" and "banana" before "cherry"
    auto posApple = output.find("apple");
    auto posBanana = output.find("banana");
    auto posCherry = output.find("cherry");
    EXPECT_NE(posApple, std::string::npos);
    EXPECT_NE(posBanana, std::string::npos);
    EXPECT_NE(posCherry, std::string::npos);
    EXPECT_LT(posApple, posBanana);
    EXPECT_LT(posBanana, posCherry);
}

// Test: Emitting a map with special characters in values
TEST_F(StlEmitterTest_658, SpecialCharactersInValues_658) {
    std::map<std::string, std::string> m;
    m["special"] = "value with: colon";
    m["another"] = "value with # hash";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("special"), std::string::npos);
    EXPECT_NE(output.find("another"), std::string::npos);
}

// Test: Emitting a map with empty string key and value
TEST_F(StlEmitterTest_658, EmptyStringKeyValue_658) {
    std::map<std::string, std::string> m;
    m[""] = "";
    emitter << m;
    EXPECT_TRUE(emitter.good());
    // Should still produce valid output
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Emitting a nested map (map of maps)
TEST_F(StlEmitterTest_658, NestedMap_658) {
    std::map<std::string, std::map<std::string, int>> m;
    m["outer"]["inner1"] = 1;
    m["outer"]["inner2"] = 2;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner1"), std::string::npos);
    EXPECT_NE(output.find("inner2"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

// Test: Emitting a large map
TEST_F(StlEmitterTest_658, LargeMap_658) {
    std::map<int, int> m;
    for (int i = 0; i < 100; ++i) {
        m[i] = i * i;
    }
    emitter << m;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Emitting map with double values
TEST_F(StlEmitterTest_658, MapWithDoubleValues_658) {
    std::map<std::string, double> m;
    m["pi"] = 3.14159;
    m["e"] = 2.71828;
    emitter << m;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("pi"), std::string::npos);
    EXPECT_NE(output.find("e"), std::string::npos);
}

// Test: Output is parseable YAML for a simple map
TEST_F(StlEmitterTest_658, OutputIsParseableYAML_658) {
    std::map<std::string, std::string> m;
    m["name"] = "test";
    m["value"] = "data";
    emitter << m;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["name"].as<std::string>(), "test");
    EXPECT_EQ(node["value"].as<std::string>(), "data");
}

// Test: Output is parseable YAML for an empty map
TEST_F(StlEmitterTest_658, EmptyMapParseableYAML_658) {
    std::map<std::string, std::string> m;
    emitter << m;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsMap() || node.IsNull());
}

// Test: Output is parseable YAML for integer map
TEST_F(StlEmitterTest_658, IntMapParseableYAML_658) {
    std::map<int, int> m;
    m[10] = 100;
    m[20] = 200;
    emitter << m;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node[10].as<int>(), 100);
    EXPECT_EQ(node[20].as<int>(), 200);
}

// Test: Emitting map after other content in sequence
TEST_F(StlEmitterTest_658, MapInSequence_658) {
    std::map<std::string, int> m;
    m["a"] = 1;
    emitter << YAML::BeginSeq;
    emitter << m;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_TRUE(node[0].IsMap());
    EXPECT_EQ(node[0]["a"].as<int>(), 1);
}

// Test: Multiple maps in sequence
TEST_F(StlEmitterTest_658, MultipleMapsInSequence_658) {
    std::map<std::string, int> m1;
    m1["x"] = 1;
    std::map<std::string, int> m2;
    m2["y"] = 2;

    emitter << YAML::BeginSeq;
    emitter << m1;
    emitter << m2;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["x"].as<int>(), 1);
    EXPECT_EQ(node[1]["y"].as<int>(), 2);
}

// Test: Map as value in another map
TEST_F(StlEmitterTest_658, MapAsValueInMap_658) {
    std::map<std::string, int> inner;
    inner["nested"] = 42;

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer" << YAML::Value << inner;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());

    YAML::Node node = YAML::Load(emitter.c_str());
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["outer"]["nested"].as<int>(), 42);
}
