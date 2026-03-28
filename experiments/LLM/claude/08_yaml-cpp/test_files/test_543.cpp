#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/binary.h"
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

class EmitterTest_543 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Basic Construction and State ====================

TEST_F(EmitterTest_543, DefaultConstructor_GoodState_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, DefaultConstructor_EmptyOutput_543) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, DefaultConstructor_CStrNotNull_543) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_543, StreamConstructor_GoodState_543) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, DefaultConstructor_NoError_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

// ==================== Write String ====================

TEST_F(EmitterTest_543, WriteString_SimpleString_543) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteString_EmptyString_543) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, WriteString_ToStream_543) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "world";
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("world"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteStdString_543) {
    YAML::Emitter emitter;
    std::string val = "test_string";
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("test_string"), std::string::npos);
}

// ==================== Write Bool ====================

TEST_F(EmitterTest_543, WriteBool_True_543) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteBool_False_543) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteBool_TrueLongFormat_543) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::LongBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteBool_FalseLongFormat_543) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::LongBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("false"), std::string::npos);
}

// ==================== Write Integers ====================

TEST_F(EmitterTest_543, WriteInt_PositiveValue_543) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteInt_NegativeValue_543) {
    YAML::Emitter emitter;
    emitter << -7;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteInt_Zero_543) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteInt_HexBase_543) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteInt_OctBase_543) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Write Float/Double ====================

TEST_F(EmitterTest_543, WriteFloat_543) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteDouble_543) {
    YAML::Emitter emitter;
    emitter << 2.71828;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Char ====================

TEST_F(EmitterTest_543, WriteChar_543) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Write Null ====================

TEST_F(EmitterTest_543, WriteNull_543) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_543, WriteBlockSequence_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << "item3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteFlowSequence_543) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteEmptySequence_543) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_543, WriteBlockMap_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "John";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteFlowMap_543) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteEmptyMap_543) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_543, WriteNestedMapInSeq_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, WriteNestedSeqInMap_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_543, WriteAnchor_543) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteAlias_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::Alias("anc");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_543, WriteTag_543) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("myTag");
    emitter << "tagged_value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("myTag"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteVerbatimTag_543) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Comments ====================

TEST_F(EmitterTest_543, WriteComment_543) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
    EXPECT_NE(output.find("#"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_543, WriteBinary_SimpleData_543) {
    const unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    YAML::Binary binary(data, sizeof(data));
    YAML::Emitter emitter;
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteBinary_EmptyData_543) {
    YAML::Binary binary(nullptr, 0);
    YAML::Emitter emitter;
    emitter << binary;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, WriteBinary_ContainsBinaryTag_543) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(data, sizeof(data));
    YAML::Emitter emitter;
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("binary"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteBinary_LargeData_543) {
    std::vector<unsigned char> data(1024, 0xAB);
    YAML::Binary binary(data.data(), data.size());
    YAML::Emitter emitter;
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Settings ====================

TEST_F(EmitterTest_543, SetIndent_ValidValue_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_543, SetIndent_MinimumValue_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_543, SetStringFormat_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_543, SetBoolFormat_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_543, SetNullFormat_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_543, SetSeqFormat_Flow_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_543, SetSeqFormat_Block_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_543, SetMapFormat_Flow_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_543, SetMapFormat_Block_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_543, SetFloatPrecision_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_543, SetDoublePrecision_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_543, SetPreCommentIndent_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_543, SetPostCommentIndent_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== Local Manipulators ====================

TEST_F(EmitterTest_543, SetLocalValue_Flow_543) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_543, SetLocalIndent_543) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Document Markers ====================

TEST_F(EmitterTest_543, WriteBeginDoc_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "value";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteMultipleDocuments_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

// ==================== c_str and size ====================

TEST_F(EmitterTest_543, SizeMatchesCStr_543) {
    YAML::Emitter emitter;
    emitter << "hello world";
    EXPECT_EQ(emitter.size(), std::strlen(emitter.c_str()));
}

TEST_F(EmitterTest_543, SizeIncreasesWithContent_543) {
    YAML::Emitter emitter;
    std::size_t initial_size = emitter.size();
    emitter << "data";
    EXPECT_GT(emitter.size(), initial_size);
}

// ==================== Stream output ====================

TEST_F(EmitterTest_543, StreamOutput_MatchesInternal_543) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "streamed";
    EXPECT_TRUE(emitter.good());
    // The stream should contain the output
    EXPECT_NE(ss.str().find("streamed"), std::string::npos);
}

// ==================== Complex scenarios ====================

TEST_F(EmitterTest_543, ComplexMapWithSequenceValues_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "fruits";
    emitter << YAML::Value << YAML::BeginSeq;
    emitter << "apple" << "banana" << "cherry";
    emitter << YAML::EndSeq;
    emitter << YAML::Key << "count";
    emitter << YAML::Value << 3;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("fruits"), std::string::npos);
    EXPECT_NE(output.find("apple"), std::string::npos);
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(EmitterTest_543, MultipleScalarsInSequence_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2.5 << "three" << true << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_543, WriteStringWithSpecialChars_543) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteStringWithNewlines_543) {
    YAML::Emitter emitter;
    emitter << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_543, WriteLongInteger_543) {
    YAML::Emitter emitter;
    emitter << static_cast<long long>(9223372036854775807LL);
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_543, RestoreGlobalModifiedSettings_543) {
    YAML::Emitter emitter;
    emitter.SetIndent(6);
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    // After restore, emitter should still be good
    EXPECT_TRUE(emitter.good());
}

// ==================== Chaining ====================

TEST_F(EmitterTest_543, ChainingWrites_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << "b";
    emitter << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Binary in Map ====================

TEST_F(EmitterTest_543, WriteBinaryInMap_543) {
    const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    YAML::Binary binary(data, sizeof(data));
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "data";
    emitter << YAML::Value << binary;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("data"), std::string::npos);
    EXPECT_NE(output.find("binary"), std::string::npos);
}

// ==================== Quoted strings ====================

TEST_F(EmitterTest_543, WriteSingleQuotedString_543) {
    YAML::Emitter emitter;
    emitter << YAML::SingleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_543, WriteDoubleQuotedString_543) {
    YAML::Emitter emitter;
    emitter << YAML::DoubleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== Literal and Folded ====================

TEST_F(EmitterTest_543, WriteLiteralString_543) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Newline handling ====================

TEST_F(EmitterTest_543, NewlineManip_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "first";
    emitter << YAML::Newline;
    emitter << "second";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Output charset ====================

TEST_F(EmitterTest_543, SetOutputCharsetUTF8_543) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Deeply nested ====================

TEST_F(EmitterTest_543, DeeplyNestedStructure_543) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level1";
    emitter << YAML::Value << YAML::BeginMap;
    emitter << YAML::Key << "level2";
    emitter << YAML::Value << YAML::BeginMap;
    emitter << YAML::Key << "level3";
    emitter << YAML::Value << "deep_value";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("deep_value"), std::string::npos);
}

// ==================== Binary with all byte values ====================

TEST_F(EmitterTest_543, WriteBinary_AllByteValues_543) {
    std::vector<unsigned char> data(256);
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<unsigned char>(i);
    }
    YAML::Binary binary(data.data(), data.size());
    YAML::Emitter emitter;
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Multiple scalars at top level (should cause error?) ====================

TEST_F(EmitterTest_543, WriteSecondTopLevelScalar_543) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << "second";
    // After writing two top-level scalars without document markers,
    // the emitter may or may not be in a good state depending on implementation
    // We just check it doesn't crash
    emitter.c_str();
}

// ==================== Sequence with Binary ====================

TEST_F(EmitterTest_543, WriteBinaryInSequence_543) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x03, 0x04};
    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << bin1;
    emitter << bin2;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}
