#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_518 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_518, DefaultConstructor_IsGood_518) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_518, DefaultConstructor_EmptyOutput_518) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_518, DefaultConstructor_CStrNotNull_518) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_518, DefaultConstructor_NoError_518) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_518, StreamConstructor_IsGood_518) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// ==================== SetStringFormat ====================

TEST_F(EmitterTest_518, SetStringFormat_SingleQuoted_518) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_518, SetStringFormat_DoubleQuoted_518) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_518, SetStringFormat_Literal_518) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_518, SetStringFormat_InvalidValue_518) {
    // Passing an unrelated EMITTER_MANIP should return false
    EXPECT_FALSE(emitter.SetStringFormat(YAML::Dec));
}

TEST_F(EmitterTest_518, SetStringFormat_AffectsOutput_SingleQuoted_518) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_518, SetStringFormat_AffectsOutput_DoubleQuoted_518) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterTest_518, SetBoolFormat_TrueFalseBool_518) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_518, SetBoolFormat_YesNoBool_518) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_518, SetBoolFormat_OnOffBool_518) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_518, SetBoolFormat_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetBoolFormat(YAML::Dec));
}

TEST_F(EmitterTest_518, SetBoolFormat_TrueFalse_Output_518) {
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_518, SetBoolFormat_YesNo_Output_518) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    std::string output(emitter.c_str());
    // Should contain "yes" or "Yes" or "YES"
    EXPECT_TRUE(output.find("yes") != std::string::npos ||
                output.find("Yes") != std::string::npos ||
                output.find("YES") != std::string::npos);
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_518, SetNullFormat_LowerNull_518) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_518, SetNullFormat_TildeNull_518) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_518, SetNullFormat_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetNullFormat(YAML::Dec));
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_518, SetIntBase_Dec_518) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_518, SetIntBase_Hex_518) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_518, SetIntBase_Oct_518) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_518, SetIntBase_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetIntBase(YAML::SingleQuoted));
}

TEST_F(EmitterTest_518, SetIntBase_Hex_Output_518) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0xff"), std::string::npos);
}

TEST_F(EmitterTest_518, SetIntBase_Oct_Output_518) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("010"), std::string::npos);
}

// ==================== SetSeqFormat ====================

TEST_F(EmitterTest_518, SetSeqFormat_Block_518) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_518, SetSeqFormat_Flow_518) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_518, SetSeqFormat_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Dec));
}

// ==================== SetMapFormat ====================

TEST_F(EmitterTest_518, SetMapFormat_Block_518) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_518, SetMapFormat_Flow_518) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_518, SetMapFormat_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetMapFormat(YAML::Dec));
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_518, SetOutputCharset_UTF8_518) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_518, SetOutputCharset_EscapeNonAscii_518) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_518, SetOutputCharset_InvalidValue_518) {
    EXPECT_FALSE(emitter.SetOutputCharset(YAML::Dec));
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_518, SetIndent_ValidValue_518) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_518, SetIndent_MinValue_518) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_518, SetIndent_TooSmall_518) {
    // Indent of 1 is likely rejected (minimum is typically 2)
    EXPECT_FALSE(emitter.SetIndent(1));
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterTest_518, SetPreCommentIndent_ValidValue_518) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_518, SetPostCommentIndent_ValidValue_518) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterTest_518, SetFloatPrecision_Valid_518) {
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_518, SetDoublePrecision_Valid_518) {
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Write operations ====================

TEST_F(EmitterTest_518, WriteString_518) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteInt_518) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteBoolTrue_518) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteBoolFalse_518) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteNull_518) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteDouble_518) {
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_518, WriteBlockSequence_518) {
    emitter << YAML::BeginSeq;
    emitter << "item1" << "item2" << "item3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteFlowSequence_518) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_518, WriteBlockMap_518) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteFlowMap_518) {
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// ==================== Nested structures ====================

TEST_F(EmitterTest_518, NestedMapInSeq_518) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_518, NestedSeqInMap_518) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_518, WriteComment_518) {
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_518, WriteAnchor_518) {
    emitter << YAML::Anchor("anchor1") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_518, WriteAlias_518) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "hello";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_518, WriteTag_518) {
    emitter << YAML::LocalTag("mytag") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Stream output ====================

TEST_F(EmitterTest_518, StreamConstructor_WritesToStream_518) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ==================== Size tracking ====================

TEST_F(EmitterTest_518, Size_IncreasesAfterWrite_518) {
    std::size_t initialSize = emitter.size();
    emitter << "test";
    EXPECT_GT(emitter.size(), initialSize);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_518, SetLocalValue_Flow_518) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_518, RestoreGlobalModifiedSettings_518) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, emitting should still work
    emitter << "test";
    EXPECT_TRUE(emitter.good());
}

// ==================== Multiple documents ====================

TEST_F(EmitterTest_518, MultipleDocuments_518) {
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_518, WriteBinary_518) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
}

// ==================== Literal block scalar ====================

TEST_F(EmitterTest_518, SetStringFormat_Literal_Output_518) {
    emitter.SetStringFormat(YAML::Literal);
    emitter << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Complex map ====================

TEST_F(EmitterTest_518, ComplexMapWithMultipleKeys_518) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "Alice";
    emitter << YAML::Key << "age" << YAML::Value << 30;
    emitter << YAML::Key << "active" << YAML::Value << true;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("age"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// ==================== LongKey ====================

TEST_F(EmitterTest_518, LongKey_518) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "long_key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Char output ====================

TEST_F(EmitterTest_518, WriteChar_518) {
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Null format ====================

TEST_F(EmitterTest_518, NullFormat_LowerNull_Output_518) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_518, NullFormat_TildeNull_Output_518) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== SetIndent affects output ====================

TEST_F(EmitterTest_518, SetIndent_AffectsOutput_518) {
    emitter.SetIndent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value;
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Float precision ====================

TEST_F(EmitterTest_518, FloatPrecision_518) {
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_518, DoublePrecision_518) {
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
}

// ==================== Empty string ====================

TEST_F(EmitterTest_518, WriteEmptyString_518) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// ==================== VerbatimTag ====================

TEST_F(EmitterTest_518, WriteVerbatimTag_518) {
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!<tag:yaml.org,2002:str>"), std::string::npos);
}

// ==================== Negative integer ====================

TEST_F(EmitterTest_518, WriteNegativeInt_518) {
    emitter << -42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-42"), std::string::npos);
}

// ==================== Zero ====================

TEST_F(EmitterTest_518, WriteZero_518) {
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Emitter is not copyable ====================
// (This is a compile-time check; we just verify the type traits)
TEST_F(EmitterTest_518, NotCopyable_518) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}
