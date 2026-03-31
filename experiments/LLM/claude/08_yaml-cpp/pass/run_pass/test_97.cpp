#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// ============================================================
// Tests for YAML::Dump function
// ============================================================

class DumpTest_97 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(DumpTest_97, DumpScalarNode_97) {
  YAML::Node node;
  node = "hello";
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "hello");
}

TEST_F(DumpTest_97, DumpIntegerNode_97) {
  YAML::Node node;
  node = 42;
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "42");
}

TEST_F(DumpTest_97, DumpBoolNodeTrue_97) {
  YAML::Node node;
  node = true;
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "true");
}

TEST_F(DumpTest_97, DumpBoolNodeFalse_97) {
  YAML::Node node;
  node = false;
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "false");
}

TEST_F(DumpTest_97, DumpNullNode_97) {
  YAML::Node node;
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "~");
}

TEST_F(DumpTest_97, DumpSequenceNode_97) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);
  std::string result = YAML::Dump(node);
  EXPECT_FALSE(result.empty());
  // Verify it contains expected elements
  EXPECT_NE(result.find("1"), std::string::npos);
  EXPECT_NE(result.find("2"), std::string::npos);
  EXPECT_NE(result.find("3"), std::string::npos);
}

TEST_F(DumpTest_97, DumpMapNode_97) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  std::string result = YAML::Dump(node);
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("key1"), std::string::npos);
  EXPECT_NE(result.find("value1"), std::string::npos);
  EXPECT_NE(result.find("key2"), std::string::npos);
  EXPECT_NE(result.find("value2"), std::string::npos);
}

TEST_F(DumpTest_97, DumpNestedMapNode_97) {
  YAML::Node node;
  node["outer"]["inner"] = "value";
  std::string result = YAML::Dump(node);
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("outer"), std::string::npos);
  EXPECT_NE(result.find("inner"), std::string::npos);
  EXPECT_NE(result.find("value"), std::string::npos);
}

TEST_F(DumpTest_97, DumpEmptySequence_97) {
  YAML::Node node(YAML::NodeType::Sequence);
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "[]");
}

TEST_F(DumpTest_97, DumpEmptyMap_97) {
  YAML::Node node(YAML::NodeType::Map);
  std::string result = YAML::Dump(node);
  EXPECT_EQ(result, "{}");
}

TEST_F(DumpTest_97, DumpDoubleNode_97) {
  YAML::Node node;
  node = 3.14;
  std::string result = YAML::Dump(node);
  EXPECT_FALSE(result.empty());
  // Should contain some representation of 3.14
  EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(DumpTest_97, DumpEmptyStringNode_97) {
  YAML::Node node;
  node = "";
  std::string result = YAML::Dump(node);
  // Empty string should be represented somehow (e.g., "" or '')
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for YAML::Emitter class
// ============================================================

class EmitterTest_97 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(EmitterTest_97, DefaultConstructorIsGood_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, DefaultConstructorEmptyOutput_97) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
  EXPECT_STREQ(emitter.c_str(), "");
}

TEST_F(EmitterTest_97, StreamConstructorIsGood_97) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, WriteString_97) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  EXPECT_NE(std::string(emitter.c_str()).find("hello"), std::string::npos);
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteBoolTrue_97) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "true");
}

TEST_F(EmitterTest_97, WriteBoolFalse_97) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "false");
}

TEST_F(EmitterTest_97, WriteInteger_97) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "42");
}

TEST_F(EmitterTest_97, WriteNegativeInteger_97) {
  YAML::Emitter emitter;
  emitter << -10;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "-10");
}

TEST_F(EmitterTest_97, WriteNull_97) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "~");
}

TEST_F(EmitterTest_97, WriteSequence_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "a";
  emitter << "b";
  emitter << "c";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
  EXPECT_NE(output.find("c"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteMap_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "John";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteFlowSequence_97) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteFlowMap_97) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteComment_97) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteAnchorAndAlias_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << YAML::Anchor("anchor1") << "value1";
  emitter << YAML::Key << "b" << YAML::Value << YAML::Alias("anchor1");
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
  EXPECT_NE(output.find("*anchor1"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteTag_97) {
  YAML::Emitter emitter;
  emitter << YAML::LocalTag("mytag") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteNodeToEmitter_97) {
  YAML::Node node;
  node["key"] = "value";
  YAML::Emitter emitter;
  emitter << node;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(EmitterTest_97, StreamConstructorOutputGoesToStream_97) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  // The stream should contain output
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

TEST_F(EmitterTest_97, SetOutputCharsetValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetStringFormatValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetBoolFormatValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetBoolFormatUpperCase_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "TRUE");
}

TEST_F(EmitterTest_97, SetBoolFormatCamelCase_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "True");
}

TEST_F(EmitterTest_97, SetBoolFormatLowerCase_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "true");
}

TEST_F(EmitterTest_97, SetNullFormatValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "null");
}

TEST_F(EmitterTest_97, SetNullFormatTilde_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "~");
}

TEST_F(EmitterTest_97, SetIntBaseHex_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_97, SetIntBaseOct_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_97, SetSeqFormatValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetMapFormatValid_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetIndent_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetPreCommentIndent_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(3));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetPostCommentIndent_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(2));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetFloatPrecision_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(3));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, SetDoublePrecision_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, GetLastErrorWhenGood_97) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_97, WriteNestedSequence_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2;
  emitter << YAML::EndSeq;
  emitter << YAML::BeginSeq;
  emitter << 3 << 4;
  emitter << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, WriteNestedMap_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "outer";
  emitter << YAML::Value;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "inner" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("outer"), std::string::npos);
  EXPECT_NE(output.find("inner"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteChar_97) {
  YAML::Emitter emitter;
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteDouble_97) {
  YAML::Emitter emitter;
  emitter << 3.14159;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteFloat_97) {
  YAML::Emitter emitter;
  emitter << 1.5f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteLongString_97) {
  YAML::Emitter emitter;
  std::string longStr(1000, 'x');
  emitter << longStr;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteMultipleScalars_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "first" << "second" << "third";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("first"), std::string::npos);
  EXPECT_NE(output.find("second"), std::string::npos);
  EXPECT_NE(output.find("third"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteBinary_97) {
  YAML::Emitter emitter;
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, SetLocalValueFlow_97) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_97, SetLocalIndent_97) {
  YAML::Emitter emitter;
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_97, WriteStringWithSpecialCharacters_97) {
  YAML::Emitter emitter;
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  // String containing colon should be quoted
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteEmptyString_97) {
  YAML::Emitter emitter;
  emitter << "";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteZeroInteger_97) {
  YAML::Emitter emitter;
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "0");
}

TEST_F(EmitterTest_97, WriteMapWithMultipleEntries_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::Key << "b" << YAML::Value << 2;
  emitter << YAML::Key << "c" << YAML::Value << 3;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
  EXPECT_NE(output.find("c"), std::string::npos);
}

TEST_F(EmitterTest_97, DumpAndParseRoundtrip_97) {
  YAML::Node original;
  original["name"] = "test";
  original["value"] = 42;
  std::string dumped = YAML::Dump(original);
  YAML::Node parsed = YAML::Load(dumped);
  EXPECT_EQ(parsed["name"].as<std::string>(), "test");
  EXPECT_EQ(parsed["value"].as<int>(), 42);
}

TEST_F(EmitterTest_97, DumpSequenceAndParseRoundtrip_97) {
  YAML::Node original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);
  std::string dumped = YAML::Dump(original);
  YAML::Node parsed = YAML::Load(dumped);
  ASSERT_TRUE(parsed.IsSequence());
  EXPECT_EQ(parsed.size(), 3u);
  EXPECT_EQ(parsed[0].as<int>(), 1);
  EXPECT_EQ(parsed[1].as<int>(), 2);
  EXPECT_EQ(parsed[2].as<int>(), 3);
}

TEST_F(EmitterTest_97, SetStringFormatDoubleQuoted_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_97, SetStringFormatSingleQuoted_97) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_97, RestoreGlobalModifiedSettings_97) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  // After restore, default bool format should be used
  EXPECT_STREQ(emitter.c_str(), "true");
}

TEST_F(EmitterTest_97, SizeMatchesCStr_97) {
  YAML::Emitter emitter;
  emitter << "test";
  EXPECT_EQ(emitter.size(), strlen(emitter.c_str()));
}

TEST_F(EmitterTest_97, WriteLiteralBlock_97) {
  YAML::Emitter emitter;
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("|"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteVerbatimTag_97) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!<tag:yaml.org,2002:str>"), std::string::npos);
}

TEST_F(EmitterTest_97, WriteMapSequenceValue_97) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list";
  emitter << YAML::Value << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("list"), std::string::npos);
}

TEST_F(EmitterTest_97, EmitterCopyDeleted_97) {
  EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
  EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

TEST_F(EmitterTest_97, WriteLongInteger_97) {
  YAML::Emitter emitter;
  emitter << 9223372036854775807LL;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_97, WriteNegativeLongInteger_97) {
  YAML::Emitter emitter;
  long long val = -9223372036854775807LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-"), std::string::npos);
}

TEST_F(EmitterTest_97, DumpComplexNode_97) {
  YAML::Node node;
  node["database"]["host"] = "localhost";
  node["database"]["port"] = 5432;
  node["database"]["options"].push_back("opt1");
  node["database"]["options"].push_back("opt2");
  std::string result = YAML::Dump(node);
  EXPECT_FALSE(result.empty());
  YAML::Node parsed = YAML::Load(result);
  EXPECT_EQ(parsed["database"]["host"].as<std::string>(), "localhost");
  EXPECT_EQ(parsed["database"]["port"].as<int>(), 5432);
  EXPECT_EQ(parsed["database"]["options"].size(), 2u);
}
