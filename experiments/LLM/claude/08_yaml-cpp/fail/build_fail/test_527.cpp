#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>
#include <cmath>
#include <limits>

class EmitterTest_527 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// ==================== Construction Tests ====================

TEST_F(EmitterTest_527, DefaultConstructor_IsGood_527) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, DefaultConstructor_EmptyOutput_527) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, DefaultConstructor_CStrNotNull_527) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_527, DefaultConstructor_NoError_527) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_527, StreamConstructor_IsGood_527) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// ==================== SetFloatPrecision Tests ====================

TEST_F(EmitterTest_527, SetFloatPrecision_ValidValue_527) {
    EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_527, SetFloatPrecision_Zero_527) {
    // Zero precision - implementation may accept or reject
    bool result = emitter.SetFloatPrecision(0);
    // Just verify no crash, result depends on implementation
    (void)result;
}

TEST_F(EmitterTest_527, SetFloatPrecision_LargeValue_527) {
    bool result = emitter.SetFloatPrecision(100);
    (void)result;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, SetFloatPrecision_One_527) {
    EXPECT_TRUE(emitter.SetFloatPrecision(1));
}

TEST_F(EmitterTest_527, SetFloatPrecision_StaysGood_527) {
    emitter.SetFloatPrecision(6);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, SetFloatPrecision_AffectsFloatOutput_527) {
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_527, SetFloatPrecision_HighPrecision_527) {
    emitter.SetFloatPrecision(10);
    emitter << 3.14159265f;
    EXPECT_TRUE(emitter.good());
}

// ==================== SetDoublePrecision Tests ====================

TEST_F(EmitterTest_527, SetDoublePrecision_ValidValue_527) {
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

TEST_F(EmitterTest_527, SetDoublePrecision_AffectsDoubleOutput_527) {
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterTest_527, SetIndent_ValidValue_527) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_527, SetIndent_MinValue_527) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_527, SetIndent_TooSmall_527) {
    // Indent of 1 might be rejected
    bool result = emitter.SetIndent(1);
    (void)result;
}

// ==================== SetPreCommentIndent Tests ====================

TEST_F(EmitterTest_527, SetPreCommentIndent_ValidValue_527) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

// ==================== SetPostCommentIndent Tests ====================

TEST_F(EmitterTest_527, SetPostCommentIndent_ValidValue_527) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterTest_527, SetOutputCharset_UTF8_527) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_527, SetOutputCharset_Default_527) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterTest_527, SetStringFormat_Auto_527) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Auto));
}

TEST_F(EmitterTest_527, SetStringFormat_SingleQuoted_527) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_527, SetStringFormat_DoubleQuoted_527) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_527, SetStringFormat_Literal_527) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterTest_527, SetBoolFormat_TrueFalseBool_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_527, SetBoolFormat_YesNoBool_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_527, SetBoolFormat_OnOffBool_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_527, SetBoolFormat_UpperCase_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_527, SetBoolFormat_LowerCase_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_527, SetBoolFormat_CamelCase_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_527, SetBoolFormat_LongBool_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_527, SetBoolFormat_ShortBool_527) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

// ==================== SetNullFormat Tests ====================

TEST_F(EmitterTest_527, SetNullFormat_LowerNull_527) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_527, SetNullFormat_UpperNull_527) {
    // Might not exist, but trying common ones
    bool result = emitter.SetNullFormat(YAML::CamelNull);
    (void)result;
}

TEST_F(EmitterTest_527, SetNullFormat_TildeNull_527) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

// ==================== SetIntBase Tests ====================

TEST_F(EmitterTest_527, SetIntBase_Dec_527) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_527, SetIntBase_Hex_527) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_527, SetIntBase_Oct_527) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// ==================== SetSeqFormat Tests ====================

TEST_F(EmitterTest_527, SetSeqFormat_Block_527) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_527, SetSeqFormat_Flow_527) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

// ==================== SetMapFormat Tests ====================

TEST_F(EmitterTest_527, SetMapFormat_Block_527) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_527, SetMapFormat_Flow_527) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// ==================== Write Tests (Scalar) ====================

TEST_F(EmitterTest_527, WriteString_Simple_527) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_527, WriteString_Empty_527) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, WriteInt_527) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_527, WriteBool_True_527) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteBool_False_527) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteChar_527) {
    emitter << 'a';
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, WriteFloat_527) {
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteDouble_527) {
    emitter << 3.14159;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteNull_527) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequence Tests ====================

TEST_F(EmitterTest_527, WriteSequence_Simple_527) {
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_527, WriteSequence_Empty_527) {
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, WriteSequence_Flow_527) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_527, WriteSequence_Block_527) {
    emitter << YAML::Block;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-"), std::string::npos);
}

// ==================== Map Tests ====================

TEST_F(EmitterTest_527, WriteMap_Simple_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "John";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_527, WriteMap_Empty_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, WriteMap_Flow_527) {
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_527, WriteNestedMapInSeq_527) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, WriteNestedSeqInMap_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Anchor and Alias Tests ====================

TEST_F(EmitterTest_527, WriteAnchor_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Anchor("anchor1") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_527, WriteAlias_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1";
    emitter << YAML::Value << YAML::Anchor("anch") << "value";
    emitter << YAML::Key << "key2";
    emitter << YAML::Value << YAML::Alias("anch");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anch"), std::string::npos);
}

// ==================== Tag Tests ====================

TEST_F(EmitterTest_527, WriteTag_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::Tag("!mytag") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Comment Tests ====================

TEST_F(EmitterTest_527, WriteComment_527) {
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Binary Tests ====================

TEST_F(EmitterTest_527, WriteBinary_527) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteBinary_Empty_527) {
    emitter << YAML::Binary(nullptr, 0);
    EXPECT_TRUE(emitter.good());
}

// ==================== Stream Constructor Output Tests ====================

TEST_F(EmitterTest_527, StreamConstructor_OutputToStream_527) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

TEST_F(EmitterTest_527, StreamConstructor_ComplexOutput_527) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << YAML::BeginMap;
    e << YAML::Key << "key" << YAML::Value << "value";
    e << YAML::EndMap;
    EXPECT_TRUE(e.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// ==================== Size Tests ====================

TEST_F(EmitterTest_527, Size_IncreasesAfterWrite_527) {
    std::size_t initialSize = emitter.size();
    emitter << "hello";
    EXPECT_GT(emitter.size(), initialSize);
}

TEST_F(EmitterTest_527, Size_MatchesCStr_527) {
    emitter << "test";
    EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterTest_527, RestoreGlobalModifiedSettings_AfterChange_527) {
    emitter.SetIndent(4);
    emitter.SetFloatPrecision(3);
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue Tests ====================

TEST_F(EmitterTest_527, SetLocalValue_Flow_527) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalIndent Tests ====================

TEST_F(EmitterTest_527, SetLocalIndent_527) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Indent(6);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Int Base Format Tests ====================

TEST_F(EmitterTest_527, IntBase_Hex_527) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_527, IntBase_Oct_527) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_527, IntBase_Dec_527) {
    emitter.SetIntBase(YAML::Dec);
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== Bool Format Tests ====================

TEST_F(EmitterTest_527, BoolFormat_TrueFalse_527) {
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain some form of "true"
    EXPECT_GT(output.size(), 0u);
}

TEST_F(EmitterTest_527, BoolFormat_YesNo_527) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_527, BoolFormat_OnOff_527) {
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
}

// ==================== Null Format Tests ====================

TEST_F(EmitterTest_527, NullFormat_Tilde_527) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_527, NullFormat_LowerNull_527) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

// ==================== String Format Tests ====================

TEST_F(EmitterTest_527, StringFormat_DoubleQuoted_527) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_527, StringFormat_SingleQuoted_527) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_527, MultipleDocuments_527) {
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

// ==================== Complex/Integration Tests ====================

TEST_F(EmitterTest_527, ComplexDocument_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::Key << "numbers" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::Key << "nested" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << true;
    emitter << YAML::Key << "b" << YAML::Value << YAML::Null;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, LongKey_527) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "a very long key";
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Float Precision Effect Tests ====================

TEST_F(EmitterTest_527, SetFloatPrecision_LowPrecision_OutputShorter_527) {
    YAML::Emitter e1;
    e1.SetFloatPrecision(2);
    e1 << 3.14159f;

    YAML::Emitter e2;
    e2.SetFloatPrecision(6);
    e2 << 3.14159f;

    EXPECT_TRUE(e1.good());
    EXPECT_TRUE(e2.good());
    // Lower precision should produce shorter or equal output
    EXPECT_LE(e1.size(), e2.size());
}

TEST_F(EmitterTest_527, SetDoublePrecision_LowPrecision_OutputShorter_527) {
    YAML::Emitter e1;
    e1.SetDoublePrecision(2);
    e1 << 3.141592653589793;

    YAML::Emitter e2;
    e2.SetDoublePrecision(10);
    e2 << 3.141592653589793;

    EXPECT_TRUE(e1.good());
    EXPECT_TRUE(e2.good());
    EXPECT_LE(e1.size(), e2.size());
}

// ==================== Newline Tests ====================

TEST_F(EmitterTest_527, Newline_InSequence_527) {
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << YAML::Newline;
    emitter << "b";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Negative Integer Tests ====================

TEST_F(EmitterTest_527, WriteNegativeInt_527) {
    emitter << -42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-42"), std::string::npos);
}

// ==================== Large Integer Tests ====================

TEST_F(EmitterTest_527, WriteLargeInt_527) {
    emitter << 2147483647;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2147483647"), std::string::npos);
}

// ==================== Special Float Values ====================

TEST_F(EmitterTest_527, WriteFloat_Inf_527) {
    emitter << std::numeric_limits<float>::infinity();
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteFloat_NaN_527) {
    emitter << std::numeric_limits<float>::quiet_NaN();
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteDouble_Inf_527) {
    emitter << std::numeric_limits<double>::infinity();
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteDouble_NaN_527) {
    emitter << std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Special String Values ====================

TEST_F(EmitterTest_527, WriteString_WithSpecialChars_527) {
    emitter << "hello\nworld";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteString_WithColon_527) {
    emitter << "key: value";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_527, WriteString_WithHash_527) {
    emitter << "# not a comment";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Literal Block Scalar ====================

TEST_F(EmitterTest_527, WriteLiteralBlockScalar_527) {
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Multiple settings combination ====================

TEST_F(EmitterTest_527, CombinedSettings_527) {
    emitter.SetIndent(4);
    emitter.SetFloatPrecision(3);
    emitter.SetDoublePrecision(6);
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter.SetStringFormat(YAML::DoubleQuoted);

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "flag" << YAML::Value << true;
    emitter << YAML::Key << "pi" << YAML::Value << 3.14159;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::EndMap;

    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Non-copyable Tests ====================

// Emitter is non-copyable, non-assignable - verified at compile time
// These would fail to compile if uncommented:
// TEST_F(EmitterTest_527, NonCopyable_527) {
//     YAML::Emitter e2 = emitter; // Should not compile
// }
