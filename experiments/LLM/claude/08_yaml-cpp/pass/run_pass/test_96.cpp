#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitOperatorTest_96 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Streaming a scalar node outputs the scalar value
TEST_F(EmitOperatorTest_96, ScalarNodeOutputsValue_96) {
  YAML::Node node;
  node = "hello";
  std::ostringstream oss;
  oss << node;
  EXPECT_EQ(oss.str(), "hello");
}

// Test: Streaming an integer scalar node
TEST_F(EmitOperatorTest_96, IntegerScalarNodeOutputsValue_96) {
  YAML::Node node;
  node = 42;
  std::ostringstream oss;
  oss << node;
  EXPECT_EQ(oss.str(), "42");
}

// Test: Streaming a boolean true node
TEST_F(EmitOperatorTest_96, BoolTrueNodeOutputsValue_96) {
  YAML::Node node;
  node = true;
  std::ostringstream oss;
  oss << node;
  EXPECT_EQ(oss.str(), "true");
}

// Test: Streaming a boolean false node
TEST_F(EmitOperatorTest_96, BoolFalseNodeOutputsValue_96) {
  YAML::Node node;
  node = false;
  std::ostringstream oss;
  oss << node;
  EXPECT_EQ(oss.str(), "false");
}

// Test: Streaming a null node
TEST_F(EmitOperatorTest_96, NullNodeOutputsTilde_96) {
  YAML::Node node;
  std::ostringstream oss;
  oss << node;
  EXPECT_EQ(oss.str(), "~");
}

// Test: Streaming a sequence node
TEST_F(EmitOperatorTest_96, SequenceNodeOutputsYAMLSequence_96) {
  YAML::Node node;
  node.push_back("item1");
  node.push_back("item2");
  node.push_back("item3");
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
  EXPECT_NE(output.find("item3"), std::string::npos);
}

// Test: Streaming a map node
TEST_F(EmitOperatorTest_96, MapNodeOutputsYAMLMap_96) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("value1"), std::string::npos);
  EXPECT_NE(output.find("key2"), std::string::npos);
  EXPECT_NE(output.find("value2"), std::string::npos);
}

// Test: Streaming a nested map node
TEST_F(EmitOperatorTest_96, NestedMapNodeOutputsYAML_96) {
  YAML::Node node;
  node["outer"]["inner"] = "value";
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_NE(output.find("outer"), std::string::npos);
  EXPECT_NE(output.find("inner"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

// Test: Streaming produces valid YAML that can be parsed back
TEST_F(EmitOperatorTest_96, OutputIsParseable_96) {
  YAML::Node node;
  node["name"] = "test";
  node["count"] = 5;
  std::ostringstream oss;
  oss << node;
  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_EQ(parsed["name"].as<std::string>(), "test");
  EXPECT_EQ(parsed["count"].as<int>(), 5);
}

// Test: Streaming an empty sequence
TEST_F(EmitOperatorTest_96, EmptySequenceNode_96) {
  YAML::Node node(YAML::NodeType::Sequence);
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// Test: Streaming an empty map
TEST_F(EmitOperatorTest_96, EmptyMapNode_96) {
  YAML::Node node(YAML::NodeType::Map);
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// Test: Streaming returns the same ostream reference
TEST_F(EmitOperatorTest_96, ReturnsOstreamReference_96) {
  YAML::Node node;
  node = "test";
  std::ostringstream oss;
  std::ostream& result = (oss << node);
  EXPECT_EQ(&result, &oss);
}

// Test: Streaming a double value
TEST_F(EmitOperatorTest_96, DoubleScalarNodeOutputsValue_96) {
  YAML::Node node;
  node = 3.14;
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test: Streaming a string with special characters
TEST_F(EmitOperatorTest_96, StringWithSpecialChars_96) {
  YAML::Node node;
  node = "hello: world";
  std::ostringstream oss;
  oss << node;
  std::string output = oss.str();
  // The output should contain the string, possibly quoted
  YAML::Node parsed = YAML::Load(output);
  EXPECT_EQ(parsed.as<std::string>(), "hello: world");
}

// Test: Streaming a sequence of sequences (nested)
TEST_F(EmitOperatorTest_96, NestedSequenceNode_96) {
  YAML::Node node;
  YAML::Node inner;
  inner.push_back(1);
  inner.push_back(2);
  node.push_back(inner);
  node.push_back("text");
  std::ostringstream oss;
  oss << node;
  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_TRUE(parsed.IsSequence());
  EXPECT_EQ(parsed.size(), 2u);
  EXPECT_TRUE(parsed[0].IsSequence());
  EXPECT_EQ(parsed[0][0].as<int>(), 1);
  EXPECT_EQ(parsed[0][1].as<int>(), 2);
  EXPECT_EQ(parsed[1].as<std::string>(), "text");
}

// Test: Streaming a large map
TEST_F(EmitOperatorTest_96, LargeMapNode_96) {
  YAML::Node node;
  for (int i = 0; i < 100; ++i) {
    node["key" + std::to_string(i)] = "value" + std::to_string(i);
  }
  std::ostringstream oss;
  oss << node;
  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_EQ(parsed.size(), 100u);
  EXPECT_EQ(parsed["key0"].as<std::string>(), "value0");
  EXPECT_EQ(parsed["key99"].as<std::string>(), "value99");
}

// Test: Streaming an empty string scalar
TEST_F(EmitOperatorTest_96, EmptyStringScalar_96) {
  YAML::Node node;
  node = "";
  std::ostringstream oss;
  oss << node;
  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_EQ(parsed.as<std::string>(), "");
}

// Test: Streaming preserves negative integers
TEST_F(EmitOperatorTest_96, NegativeIntegerScalar_96) {
  YAML::Node node;
  node = -42;
  std::ostringstream oss;
  oss << node;
  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_EQ(parsed.as<int>(), -42);
}

// Test: Streaming chained with other output
TEST_F(EmitOperatorTest_96, ChainedStreamOutput_96) {
  YAML::Node node;
  node = "yaml_value";
  std::ostringstream oss;
  oss << "before:" << node << ":after";
  std::string output = oss.str();
  EXPECT_NE(output.find("before:"), std::string::npos);
  EXPECT_NE(output.find("yaml_value"), std::string::npos);
  EXPECT_NE(output.find(":after"), std::string::npos);
}

// Test: Emitter basic construction and good state
TEST_F(EmitOperatorTest_96, EmitterDefaultConstruction_96) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

// Test: Emitter with ostream construction
TEST_F(EmitOperatorTest_96, EmitterOstreamConstruction_96) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);
  EXPECT_TRUE(emitter.good());
}

// Test: Emitter write string and check c_str and size
TEST_F(EmitOperatorTest_96, EmitterWriteStringCheckOutput_96) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  EXPECT_NE(emitter.c_str(), nullptr);
  EXPECT_GT(emitter.size(), 0u);
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "hello");
}

// Test: Emitter writes to provided ostream
TEST_F(EmitOperatorTest_96, EmitterWritesToOstream_96) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);
  emitter << "test_value";
  EXPECT_TRUE(emitter.good());
  // The content should be in the stream
  EXPECT_NE(oss.str().find("test_value"), std::string::npos);
}

// Test: Emitter emits a sequence
TEST_F(EmitOperatorTest_96, EmitterSequence_96) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

// Test: Emitter emits a map
TEST_F(EmitOperatorTest_96, EmitterMap_96) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1" << YAML::Value << "val1";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("val1"), std::string::npos);
}

// Test: Emitter emits node
TEST_F(EmitOperatorTest_96, EmitterEmitsNode_96) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  YAML::Emitter emitter;
  emitter << node;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
}

// Test: Emitter SetIndent
TEST_F(EmitOperatorTest_96, EmitterSetIndent_96) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value;
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// Test: Emitter flow sequence format
TEST_F(EmitOperatorTest_96, EmitterFlowSequence_96) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

// Test: Emitter flow map format
TEST_F(EmitOperatorTest_96, EmitterFlowMap_96) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: Emitter null value
TEST_F(EmitOperatorTest_96, EmitterNull_96) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "~");
}

// Test: Emitter comment
TEST_F(EmitOperatorTest_96, EmitterComment_96) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("This is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// Test: Emitter anchor and alias
TEST_F(EmitOperatorTest_96, EmitterAnchorAlias_96) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "first" << YAML::Value << YAML::Anchor("anchor1") << "value1";
  emitter << YAML::Key << "second" << YAML::Value << YAML::Alias("anchor1");
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
  EXPECT_NE(output.find("*anchor1"), std::string::npos);
}

// Test: Emitter SetBoolFormat
TEST_F(EmitOperatorTest_96, EmitterSetBoolFormatUpperCase_96) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "TRUE");
}

// Test: Emitter SetSeqFormat
TEST_F(EmitOperatorTest_96, EmitterSetSeqFormatFlow_96) {
  YAML::Emitter emitter;
  emitter.SetSeqFormat(YAML::Flow);
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

// Test: Emitter SetMapFormat
TEST_F(EmitOperatorTest_96, EmitterSetMapFormatFlow_96) {
  YAML::Emitter emitter;
  emitter.SetMapFormat(YAML::Flow);
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
}

// Test: Emitter tag
TEST_F(EmitOperatorTest_96, EmitterTag_96) {
  YAML::Emitter emitter;
  emitter << YAML::LocalTag("mytag") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// Test: operator<< roundtrip - complex structure
TEST_F(EmitOperatorTest_96, RoundtripComplexStructure_96) {
  YAML::Node original;
  original["string"] = "hello";
  original["number"] = 123;
  original["bool"] = true;
  original["list"].push_back("a");
  original["list"].push_back("b");
  original["nested"]["x"] = 10;

  std::ostringstream oss;
  oss << original;

  YAML::Node parsed = YAML::Load(oss.str());
  EXPECT_EQ(parsed["string"].as<std::string>(), "hello");
  EXPECT_EQ(parsed["number"].as<int>(), 123);
  EXPECT_EQ(parsed["bool"].as<bool>(), true);
  EXPECT_EQ(parsed["list"].size(), 2u);
  EXPECT_EQ(parsed["list"][0].as<std::string>(), "a");
  EXPECT_EQ(parsed["list"][1].as<std::string>(), "b");
  EXPECT_EQ(parsed["nested"]["x"].as<int>(), 10);
}

// Test: Emitter size for empty emitter
TEST_F(EmitOperatorTest_96, EmitterEmptySize_96) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

// Test: Emitter GetLastError when good
TEST_F(EmitOperatorTest_96, EmitterNoErrorWhenGood_96) {
  YAML::Emitter emitter;
  emitter << "test";
  EXPECT_TRUE(emitter.good());
  EXPECT_TRUE(emitter.GetLastError().empty());
}

// Test: Emitter with float precision
TEST_F(EmitOperatorTest_96, EmitterFloatPrecision_96) {
  YAML::Emitter emitter;
  emitter.SetFloatPrecision(2);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
}

// Test: Emitter with double precision
TEST_F(EmitOperatorTest_96, EmitterDoublePrecision_96) {
  YAML::Emitter emitter;
  emitter.SetDoublePrecision(3);
  emitter << 3.14159265;
  EXPECT_TRUE(emitter.good());
}

// Test: Emitter SetIntBase hex
TEST_F(EmitOperatorTest_96, EmitterSetIntBaseHex_96) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0xff"), std::string::npos);
}

// Test: Emitter SetIntBase oct
TEST_F(EmitOperatorTest_96, EmitterSetIntBaseOct_96) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("010"), std::string::npos);
}

// Test: Streaming a node constructed from parsed YAML
TEST_F(EmitOperatorTest_96, StreamParsedNode_96) {
  std::string yaml = "foo: bar\nbaz: 42";
  YAML::Node node = YAML::Load(yaml);
  std::ostringstream oss;
  oss << node;
  YAML::Node reparsed = YAML::Load(oss.str());
  EXPECT_EQ(reparsed["foo"].as<std::string>(), "bar");
  EXPECT_EQ(reparsed["baz"].as<int>(), 42);
}
