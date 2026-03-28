#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_516 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(EmitterTest_516, DefaultConstruction_IsGood_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_516, DefaultConstruction_EmptyOutput_516) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, DefaultConstruction_CStrNotNull_516) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_516, DefaultConstruction_NoError_516) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_516, StreamConstruction_IsGood_516) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

// ==================== Write String Tests ====================

TEST_F(EmitterTest_516, WriteString_SimpleString_516) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteString_EmptyString_516) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_516, WriteString_ToStream_516) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "test";
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("test"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteStdString_516) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

// ==================== Write Bool Tests ====================

TEST_F(EmitterTest_516, WriteBool_True_516) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, WriteBool_False_516) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Integer Tests ====================

TEST_F(EmitterTest_516, WriteInt_516) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteNegativeInt_516) {
    YAML::Emitter emitter;
    emitter << -7;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteZero_516) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Write Float/Double Tests ====================

TEST_F(EmitterTest_516, WriteFloat_516) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, WriteDouble_516) {
    YAML::Emitter emitter;
    emitter << 2.71828;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Char Tests ====================

TEST_F(EmitterTest_516, WriteChar_516) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Null Tests ====================

TEST_F(EmitterTest_516, WriteNull_516) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequence Tests ====================

TEST_F(EmitterTest_516, WriteBlockSequence_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << "item3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteFlowSequence_516) {
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

TEST_F(EmitterTest_516, WriteEmptySequence_516) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Map Tests ====================

TEST_F(EmitterTest_516, WriteBlockMap_516) {
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

TEST_F(EmitterTest_516, WriteFlowMap_516) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a";
    emitter << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteEmptyMap_516) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Nested Structure Tests ====================

TEST_F(EmitterTest_516, WriteNestedMapInSequence_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_516, WriteNestedSequenceInMap_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Anchor and Alias Tests ====================

TEST_F(EmitterTest_516, WriteAnchor_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Anchor("anchor1") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteAlias_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1";
    emitter << YAML::Value << YAML::Anchor("anc") << "value";
    emitter << YAML::Key << "key2";
    emitter << YAML::Value << YAML::Alias("anc");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Tag Tests ====================

TEST_F(EmitterTest_516, WriteTag_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Tag("!mytag") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Comment Tests ====================

TEST_F(EmitterTest_516, WriteComment_516) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Binary Tests ====================

TEST_F(EmitterTest_516, WriteBinary_516) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data.data(), data.size());
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, WriteBinaryEmpty_516) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data;
    emitter << YAML::Binary(data.data(), 0);
    EXPECT_TRUE(emitter.good());
}

// ==================== Setting Tests ====================

TEST_F(EmitterTest_516, SetBoolFormat_TrueFalseBool_516) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_516, SetBoolFormat_YesNoBool_516) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_516, SetBoolFormat_OnOffBool_516) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("on"), std::string::npos);
}

TEST_F(EmitterTest_516, SetBoolFormat_UpperCase_516) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_516, SetNullFormat_LowerNull_516) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_516, SetNullFormat_TildeNull_516) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_516, SetIntBase_Hex_516) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_516, SetIntBase_Oct_516) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_516, SetSeqFormat_Flow_516) {
    YAML::Emitter emitter;
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_516, SetMapFormat_Flow_516) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_516, SetIndent_ReturnsTrue_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_516, SetIndent_TooSmall_ReturnsFalse_516) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_516, SetPreCommentIndent_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_516, SetPostCommentIndent_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_516, SetFloatPrecision_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_516, SetDoublePrecision_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_516, SetStringFormat_SingleQuoted_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_516, SetStringFormat_DoubleQuoted_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_516, SetOutputCharset_UTF8_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterTest_516, SetLocalValue_Flow_516) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_516, SetLocalValue_Block_516) {
    YAML::Emitter emitter;
    emitter << YAML::Block << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-"), std::string::npos);
}

// ==================== SetLocalIndent Tests ====================

TEST_F(EmitterTest_516, SetLocalIndent_516) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Literal/Verbatim String Tests ====================

TEST_F(EmitterTest_516, WriteLiteral_516) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Long Key Tests ====================

TEST_F(EmitterTest_516, WriteLongKey_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "longkey";
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Document Tests ====================

TEST_F(EmitterTest_516, WriteBeginDoc_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "hello";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_516, WriteMultipleDocuments_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Size Tests ====================

TEST_F(EmitterTest_516, SizeIncreasesAfterWrite_516) {
    YAML::Emitter emitter;
    std::size_t sizeBefore = emitter.size();
    emitter << "something";
    EXPECT_GT(emitter.size(), sizeBefore);
}

TEST_F(EmitterTest_516, SizeMatchesCStr_516) {
    YAML::Emitter emitter;
    emitter << "hello world";
    EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterTest_516, RestoreGlobalModifiedSettings_516) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

// ==================== Complex Structure Tests ====================

TEST_F(EmitterTest_516, ComplexNestedStructure_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "project";
    emitter << YAML::Key << "versions" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "version" << YAML::Value << 1;
    emitter << YAML::Key << "stable" << YAML::Value << true;
    emitter << YAML::EndMap;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "version" << YAML::Value << 2;
    emitter << YAML::Key << "stable" << YAML::Value << false;
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, MultipleScalarsAtTopLevel_NotGood_516) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << "second";
    // Writing two scalars at top level without document separators may cause an error
    // The behavior depends on the implementation; we just check it doesn't crash
    // and the state is consistent
    // If it's not good, there should be an error message
    if (!emitter.good()) {
        EXPECT_NE(emitter.GetLastError(), "");
    }
}

// ==================== Precision Tests ====================

TEST_F(EmitterTest_516, FloatPrecision_516) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    // Output should have limited precision
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, DoublePrecision_516) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== String With Special Characters ====================

TEST_F(EmitterTest_516, StringWithNewlines_516) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, StringWithSpecialYAMLChars_516) {
    YAML::Emitter emitter;
    emitter << "key: value";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_516, StringWithQuotes_516) {
    YAML::Emitter emitter;
    emitter << "he said \"hello\"";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== SingleQuoted / DoubleQuoted Format ====================

TEST_F(EmitterTest_516, SingleQuotedString_516) {
    YAML::Emitter emitter;
    emitter << YAML::SingleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_516, DoubleQuotedString_516) {
    YAML::Emitter emitter;
    emitter << YAML::DoubleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== Stream Output Consistency ====================

TEST_F(EmitterTest_516, StreamOutputMatchesCStr_516) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    // Stream and c_str should produce same content
    std::string fromCStr = emitter.c_str();
    std::string fromStream = ss.str();
    EXPECT_EQ(fromCStr, fromStream);
}

// ==================== Large Data Tests ====================

TEST_F(EmitterTest_516, LargeSequence_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 1000; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetSeqFormat/SetMapFormat Return Values ====================

TEST_F(EmitterTest_516, SetSeqFormat_ValidValue_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_516, SetMapFormat_ValidValue_516) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

// ==================== Chaining Tests ====================

TEST_F(EmitterTest_516, ChainingWrites_516) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
    EXPECT_NE(output.find("c"), std::string::npos);
}
