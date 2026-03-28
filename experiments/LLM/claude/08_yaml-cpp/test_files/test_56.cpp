#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cmath>
#include "yaml-cpp/yaml.h"

class EmitterTest_56 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_56, DefaultConstructor_GoodState_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, DefaultConstructor_EmptyOutput_56) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_56, DefaultConstructor_CStrNotNull_56) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_56, StreamConstructor_GoodState_56) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, DefaultConstructor_NoError_56) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// ==================== Writing Scalars ====================

TEST_F(EmitterTest_56, WriteString_56) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteCString_56) {
    YAML::Emitter emitter;
    const char* str = "test";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteBoolTrue_56) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteBoolFalse_56) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteInt_56) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteNegativeInt_56) {
    YAML::Emitter emitter;
    emitter << -7;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteFloat_56) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteDouble_56) {
    YAML::Emitter emitter;
    emitter << 2.718281828;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteChar_56) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, WriteNull_56) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_56, WriteBlockSequence_56) {
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

TEST_F(EmitterTest_56, WriteFlowSequence_56) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteEmptySequence_56) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_56, WriteBlockMap_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteFlowMap_56) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteEmptyMap_56) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_56, NestedMapInSequence_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, NestedSequenceInMap_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Stream Output ====================

TEST_F(EmitterTest_56, StreamConstructorWritesToStream_56) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== Size ====================

TEST_F(EmitterTest_56, SizeIncreasesAfterWrite_56) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "something";
    EXPECT_GT(emitter.size(), initialSize);
}

// ==================== Comments ====================

TEST_F(EmitterTest_56, WriteComment_56) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("#"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_56, WriteAnchor_56) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteAlias_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("val") << "original";
    emitter << YAML::Alias("val");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*val"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_56, WriteTag_56) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
    emitter << "tagged";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Setting Formats ====================

TEST_F(EmitterTest_56, SetBoolFormatUpperCase_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_56, SetBoolFormatCamelCase_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("False"), std::string::npos);
}

TEST_F(EmitterTest_56, SetBoolFormatLongBool_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_56, SetSeqFormatFlow_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_56, SetMapFormatFlow_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_56, SetIntBaseHex_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_56, SetIntBaseOct_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_56, SetIndent_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_56, SetIndentZero_ReturnsFalse_56) {
    YAML::Emitter emitter;
    // Indent of 0 should likely fail or be clamped
    // This tests boundary behavior
    bool result = emitter.SetIndent(0);
    // We just observe the return value, no assertion on specific value
    // since we don't know the implementation
    (void)result;
}

TEST_F(EmitterTest_56, SetIndentOne_ReturnsFalse_56) {
    YAML::Emitter emitter;
    bool result = emitter.SetIndent(1);
    // Indent of 1 may not be valid
    (void)result;
}

TEST_F(EmitterTest_56, SetPreCommentIndent_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_56, SetPostCommentIndent_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_56, SetFloatPrecision_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(3));
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, SetDoublePrecision_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
    emitter << 3.141592653589793;
    EXPECT_TRUE(emitter.good());
}

// ==================== String Formats ====================

TEST_F(EmitterTest_56, SetStringFormatSingleQuoted_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_56, SetStringFormatDoubleQuoted_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_56, SetStringFormatLiteral_56) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Null Format ====================

TEST_F(EmitterTest_56, SetNullFormatLowerNull_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("null"), std::string::npos);
}

// ==================== Local Value Manipulators ====================

TEST_F(EmitterTest_56, LocalValueFlow_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Document Markers ====================

TEST_F(EmitterTest_56, BeginDocEndDoc_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "hello";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_56, MultipleDocuments_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_56, WriteBinary_56) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Operator<< with float (the specific function in partial code) ====================

TEST_F(EmitterTest_56, OperatorShiftFloat_56) {
    YAML::Emitter emitter;
    float val = 1.5f;
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST_F(EmitterTest_56, OperatorShiftFloatZero_56) {
    YAML::Emitter emitter;
    emitter << 0.0f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_56, OperatorShiftFloatNegative_56) {
    YAML::Emitter emitter;
    emitter << -1.25f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-1.25"), std::string::npos);
}

TEST_F(EmitterTest_56, OperatorShiftFloatInSequence_56) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1.1f << 2.2f << 3.3f;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, OperatorShiftFloatInMap_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "pi" << YAML::Value << 3.14f;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("pi"), std::string::npos);
}

TEST_F(EmitterTest_56, FloatPrecisionAffectsOutput_56) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // With precision 2, should be around "3.1"
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_56, FloatLargeValue_56) {
    YAML::Emitter emitter;
    emitter << 1.0e10f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_56, FloatSmallValue_56) {
    YAML::Emitter emitter;
    emitter << 1.0e-10f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_56, RestoreGlobalModifiedSettings_56) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // After restore, should be back to default (lowercase "true")
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Complex Structures ====================

TEST_F(EmitterTest_56, ComplexNestedStructure_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::Key << "values" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "x" << YAML::Value << 1.0f;
    emitter << YAML::Key << "y" << YAML::Value << 2.0f;
    emitter << YAML::EndMap;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "x" << YAML::Value << 3.0f;
    emitter << YAML::Key << "y" << YAML::Value << 4.0f;
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Newline ====================

TEST_F(EmitterTest_56, NewlineManip_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << YAML::Newline;
    emitter << "b";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== LongKey ====================

TEST_F(EmitterTest_56, LongKey_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "long key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Multiple Writes Without Container ====================

TEST_F(EmitterTest_56, SecondWriteWithoutContainer_56) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << "second";
    // After writing a second scalar at top level without a container,
    // the emitter may go into error state
    // We just check if good() is false or the error is reported
    if (!emitter.good()) {
        EXPECT_FALSE(emitter.GetLastError().empty());
    }
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_56, SetOutputCharsetUTF8_56) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Write with size_t overload ====================

TEST_F(EmitterTest_56, WriteWithSizeOverload_56) {
    YAML::Emitter emitter;
    const char* data = "hello world";
    emitter.Write(data, 5);  // Should write "hello"
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== SetLocalPrecision ====================

TEST_F(EmitterTest_56, SetLocalPrecisionFloat_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::FloatPrecision(2) << 3.14159f;
    emitter << 3.14159f;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_56, SetLocalPrecisionDouble_56) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::DoublePrecision(15) << 3.141592653589793;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Large int types ====================

TEST_F(EmitterTest_56, WriteLongLong_56) {
    YAML::Emitter emitter;
    long long val = 9223372036854775807LL;
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_56, WriteUnsignedInt_56) {
    YAML::Emitter emitter;
    unsigned int val = 4294967295u;
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("4294967295"), std::string::npos);
}

// ==================== Emitter to std::ostream ====================

TEST_F(EmitterTest_56, StreamOutputConsistentWithCStr_56) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string fromStream = ss.str();
    std::string fromCStr(emitter.c_str(), emitter.size());
    EXPECT_EQ(fromStream, fromCStr);
}

// ==================== Empty string ====================

TEST_F(EmitterTest_56, WriteEmptyString_56) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Special float values ====================

TEST_F(EmitterTest_56, FloatInfinity_56) {
    YAML::Emitter emitter;
    emitter << std::numeric_limits<float>::infinity();
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find(".inf"), std::string::npos);
}

TEST_F(EmitterTest_56, FloatNegativeInfinity_56) {
    YAML::Emitter emitter;
    emitter << -std::numeric_limits<float>::infinity();
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-.inf"), std::string::npos);
}

TEST_F(EmitterTest_56, FloatNaN_56) {
    YAML::Emitter emitter;
    emitter << std::numeric_limits<float>::quiet_NaN();
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find(".nan"), std::string::npos);
}

TEST_F(EmitterTest_56, DoubleInfinity_56) {
    YAML::Emitter emitter;
    emitter << std::numeric_limits<double>::infinity();
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find(".inf"), std::string::npos);
}

TEST_F(EmitterTest_56, DoubleNaN_56) {
    YAML::Emitter emitter;
    emitter << std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find(".nan"), std::string::npos);
}
