#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emitfromevents.h"

class EmitTest_95 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test emitting a simple scalar node
TEST_F(EmitTest_95, EmitScalarNode_95) {
  YAML::Node node("hello");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "hello");
}

// Test emitting an integer scalar node
TEST_F(EmitTest_95, EmitIntegerScalarNode_95) {
  YAML::Node node(42);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "42");
}

// Test emitting a boolean scalar node
TEST_F(EmitTest_95, EmitBooleanScalarNode_95) {
  YAML::Node node(true);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "true");
}

// Test emitting a null node
TEST_F(EmitTest_95, EmitNullNode_95) {
  YAML::Node node;
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "~");
}

// Test emitting a sequence node
TEST_F(EmitTest_95, EmitSequenceNode_95) {
  YAML::Node node;
  node.push_back("one");
  node.push_back("two");
  node.push_back("three");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  // The result should contain all three values
  EXPECT_NE(result.find("one"), std::string::npos);
  EXPECT_NE(result.find("two"), std::string::npos);
  EXPECT_NE(result.find("three"), std::string::npos);
}

// Test emitting a map node
TEST_F(EmitTest_95, EmitMapNode_95) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("key1"), std::string::npos);
  EXPECT_NE(result.find("value1"), std::string::npos);
  EXPECT_NE(result.find("key2"), std::string::npos);
  EXPECT_NE(result.find("value2"), std::string::npos);
}

// Test emitting a nested map node
TEST_F(EmitTest_95, EmitNestedMapNode_95) {
  YAML::Node node;
  node["outer"]["inner"] = "value";
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("outer"), std::string::npos);
  EXPECT_NE(result.find("inner"), std::string::npos);
  EXPECT_NE(result.find("value"), std::string::npos);
}

// Test emitting a nested sequence
TEST_F(EmitTest_95, EmitNestedSequenceNode_95) {
  YAML::Node node;
  YAML::Node inner;
  inner.push_back(1);
  inner.push_back(2);
  node.push_back(inner);
  node.push_back("item");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("1"), std::string::npos);
  EXPECT_NE(result.find("2"), std::string::npos);
  EXPECT_NE(result.find("item"), std::string::npos);
}

// Test emitting to a stream
TEST_F(EmitTest_95, EmitToStream_95) {
  YAML::Node node("stream_test");
  std::stringstream ss;
  YAML::Emitter out(ss);
  out << node;
  EXPECT_TRUE(out.good());
  EXPECT_NE(ss.str().find("stream_test"), std::string::npos);
}

// Test emitting an empty sequence
TEST_F(EmitTest_95, EmitEmptySequenceNode_95) {
  YAML::Node node(YAML::NodeType::Sequence);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("[]"), std::string::npos);
}

// Test emitting an empty map
TEST_F(EmitTest_95, EmitEmptyMapNode_95) {
  YAML::Node node(YAML::NodeType::Map);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("{}"), std::string::npos);
}

// Test emitting a double value
TEST_F(EmitTest_95, EmitDoubleScalarNode_95) {
  YAML::Node node(3.14);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test emitting an empty string scalar
TEST_F(EmitTest_95, EmitEmptyStringScalar_95) {
  YAML::Node node(std::string(""));
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  // Empty string should still produce valid output
  EXPECT_GT(out.size(), 0u);
}

// Test emitting a string with special characters
TEST_F(EmitTest_95, EmitSpecialCharacterString_95) {
  YAML::Node node("hello: world");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  // Should be quoted or escaped since it contains a colon
  EXPECT_NE(result.find("hello: world"), std::string::npos);
}

// Test that the operator<< returns reference to same emitter
TEST_F(EmitTest_95, OperatorReturnsEmitterReference_95) {
  YAML::Node node("test");
  YAML::Emitter out;
  YAML::Emitter& ref = (out << node);
  EXPECT_EQ(&ref, &out);
}

// Test emitting a map with sequence value
TEST_F(EmitTest_95, EmitMapWithSequenceValue_95) {
  YAML::Node node;
  node["list"].push_back("a");
  node["list"].push_back("b");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("list"), std::string::npos);
  EXPECT_NE(result.find("a"), std::string::npos);
  EXPECT_NE(result.find("b"), std::string::npos);
}

// Test round-trip: emit then load
TEST_F(EmitTest_95, RoundTripScalar_95) {
  YAML::Node original("round_trip_value");
  YAML::Emitter out;
  out << original;
  EXPECT_TRUE(out.good());
  YAML::Node loaded = YAML::Load(out.c_str());
  EXPECT_EQ(loaded.as<std::string>(), "round_trip_value");
}

// Test round-trip for a map
TEST_F(EmitTest_95, RoundTripMap_95) {
  YAML::Node original;
  original["name"] = "test";
  original["value"] = 123;
  YAML::Emitter out;
  out << original;
  EXPECT_TRUE(out.good());
  YAML::Node loaded = YAML::Load(out.c_str());
  EXPECT_EQ(loaded["name"].as<std::string>(), "test");
  EXPECT_EQ(loaded["value"].as<int>(), 123);
}

// Test round-trip for a sequence
TEST_F(EmitTest_95, RoundTripSequence_95) {
  YAML::Node original;
  original.push_back(10);
  original.push_back(20);
  original.push_back(30);
  YAML::Emitter out;
  out << original;
  EXPECT_TRUE(out.good());
  YAML::Node loaded = YAML::Load(out.c_str());
  EXPECT_TRUE(loaded.IsSequence());
  EXPECT_EQ(loaded.size(), 3u);
  EXPECT_EQ(loaded[0].as<int>(), 10);
  EXPECT_EQ(loaded[1].as<int>(), 20);
  EXPECT_EQ(loaded[2].as<int>(), 30);
}

// Test emitting with a tagged node
TEST_F(EmitTest_95, EmitTaggedNode_95) {
  YAML::Node node("tagged_value");
  node.SetTag("!mytag");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("!mytag"), std::string::npos);
  EXPECT_NE(result.find("tagged_value"), std::string::npos);
}

// Test emitting a complex nested structure
TEST_F(EmitTest_95, EmitComplexNestedStructure_95) {
  YAML::Node node;
  node["database"]["host"] = "localhost";
  node["database"]["port"] = 5432;
  node["database"]["users"].push_back("admin");
  node["database"]["users"].push_back("guest");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("database"), std::string::npos);
  EXPECT_NE(result.find("host"), std::string::npos);
  EXPECT_NE(result.find("localhost"), std::string::npos);
  EXPECT_NE(result.find("port"), std::string::npos);
  EXPECT_NE(result.find("5432"), std::string::npos);
  EXPECT_NE(result.find("admin"), std::string::npos);
  EXPECT_NE(result.find("guest"), std::string::npos);
}

// Test emitting a node loaded from YAML string
TEST_F(EmitTest_95, EmitLoadedNode_95) {
  std::string yaml = "name: John\nage: 30\nitems:\n  - apple\n  - banana";
  YAML::Node node = YAML::Load(yaml);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  // Reload and verify
  YAML::Node reloaded = YAML::Load(out.c_str());
  EXPECT_EQ(reloaded["name"].as<std::string>(), "John");
  EXPECT_EQ(reloaded["age"].as<int>(), 30);
  EXPECT_EQ(reloaded["items"][0].as<std::string>(), "apple");
  EXPECT_EQ(reloaded["items"][1].as<std::string>(), "banana");
}

// Test emitting with flow style sequence
TEST_F(EmitTest_95, EmitFlowStyleSequence_95) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);
  node.SetStyle(YAML::EmitterStyle::Flow);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("["), std::string::npos);
  EXPECT_NE(result.find("]"), std::string::npos);
}

// Test emitting with flow style map
TEST_F(EmitTest_95, EmitFlowStyleMap_95) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  node.SetStyle(YAML::EmitterStyle::Flow);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_NE(result.find("{"), std::string::npos);
  EXPECT_NE(result.find("}"), std::string::npos);
}

// Test emitting size is non-zero for non-empty nodes
TEST_F(EmitTest_95, EmitSizeNonZero_95) {
  YAML::Node node("content");
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  EXPECT_GT(out.size(), 0u);
}

// Test emitting a negative integer
TEST_F(EmitTest_95, EmitNegativeInteger_95) {
  YAML::Node node(-42);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "-42");
}

// Test emitting a node with boolean false
TEST_F(EmitTest_95, EmitBooleanFalse_95) {
  YAML::Node node(false);
  YAML::Emitter out;
  out << node;
  EXPECT_TRUE(out.good());
  std::string result = out.c_str();
  EXPECT_EQ(result, "false");
}

// Test multiple nodes emitted sequentially
TEST_F(EmitTest_95, EmitMultipleNodesInSequence_95) {
  YAML::Node seq;
  seq.push_back("first");
  seq.push_back("second");
  
  YAML::Emitter out;
  out << seq;
  EXPECT_TRUE(out.good());
  
  YAML::Node reloaded = YAML::Load(out.c_str());
  EXPECT_TRUE(reloaded.IsSequence());
  EXPECT_EQ(reloaded.size(), 2u);
}
