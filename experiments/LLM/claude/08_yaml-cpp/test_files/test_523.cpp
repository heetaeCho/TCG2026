#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_523 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_523, DefaultConstructor_InitialStateIsGood_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_523, DefaultConstructor_InitialSizeIsZero_523) {
    YAML::Emitter emitter;
    EXPECT_EQ(0u, emitter.size());
}

TEST_F(EmitterTest_523, DefaultConstructor_CStrIsNotNull_523) {
    YAML::Emitter emitter;
    EXPECT_NE(nullptr, emitter.c_str());
}

TEST_F(EmitterTest_523, DefaultConstructor_NoLastError_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

TEST_F(EmitterTest_523, StreamConstructor_InitialStateIsGood_523) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

// ==================== SetMapFormat ====================

TEST_F(EmitterTest_523, SetMapFormat_Block_ReturnsTrue_523) {
    YAML::Emitter emitter;
    bool result = emitter.SetMapFormat(YAML::Block);
    EXPECT_TRUE(result);
}

TEST_F(EmitterTest_523, SetMapFormat_Flow_ReturnsTrue_523) {
    YAML::Emitter emitter;
    bool result = emitter.SetMapFormat(YAML::Flow);
    EXPECT_TRUE(result);
}

TEST_F(EmitterTest_523, SetMapFormat_LongKey_ReturnsTrue_523) {
    YAML::Emitter emitter;
    bool result = emitter.SetMapFormat(YAML::LongKey);
    EXPECT_TRUE(result);
}

TEST_F(EmitterTest_523, SetMapFormat_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    // Using a manip that is not valid for map format (e.g., Dec is for int base)
    bool result = emitter.SetMapFormat(YAML::Dec);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_523, SetMapFormat_EmitterRemainsGood_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Block);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_523, SetMapFormat_BlockThenFlow_BothSucceed_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// ==================== SetSeqFormat ====================

TEST_F(EmitterTest_523, SetSeqFormat_Block_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_523, SetSeqFormat_Flow_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_523, SetSeqFormat_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Hex));
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_523, SetOutputCharset_EmitNonAscii_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_523, SetOutputCharset_EscapeNonAscii_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_523, SetOutputCharset_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetOutputCharset(YAML::Flow));
}

// ==================== SetStringFormat ====================

TEST_F(EmitterTest_523, SetStringFormat_Auto_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Auto));
}

TEST_F(EmitterTest_523, SetStringFormat_SingleQuoted_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_523, SetStringFormat_DoubleQuoted_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_523, SetStringFormat_Literal_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_523, SetStringFormat_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetStringFormat(YAML::Dec));
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterTest_523, SetBoolFormat_TrueFalseBool_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_523, SetBoolFormat_YesNoBool_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_523, SetBoolFormat_OnOffBool_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_523, SetBoolFormat_UpperCase_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_523, SetBoolFormat_LowerCase_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_523, SetBoolFormat_CamelCase_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_523, SetBoolFormat_LongBool_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_523, SetBoolFormat_ShortBool_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

TEST_F(EmitterTest_523, SetBoolFormat_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetBoolFormat(YAML::Hex));
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_523, SetNullFormat_LowerNull_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_523, SetNullFormat_TildeNull_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_523, SetNullFormat_UpperNull_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_523, SetNullFormat_CamelNull_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_523, SetNullFormat_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetNullFormat(YAML::Block));
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_523, SetIntBase_Dec_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_523, SetIntBase_Hex_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_523, SetIntBase_Oct_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_523, SetIntBase_InvalidManip_ReturnsFalse_523) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetIntBase(YAML::Block));
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_523, SetIndent_ValidValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_523, SetIndent_MinValid_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_523, SetIndent_LargeValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(10));
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterTest_523, SetPreCommentIndent_ValidValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterTest_523, SetPostCommentIndent_ValidValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterTest_523, SetFloatPrecision_ValidValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterTest_523, SetDoublePrecision_ValidValue_ReturnsTrue_523) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// ==================== Write operations ====================

TEST_F(EmitterTest_523, WriteString_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_523, WriteBool_True_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_523, WriteBool_False_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_523, WriteInt_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_523, WriteNull_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequence emission ====================

TEST_F(EmitterTest_523, EmitBlockSequence_ProducesValidOutput_523) {
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

TEST_F(EmitterTest_523, EmitFlowSequence_ProducesValidOutput_523) {
    YAML::Emitter emitter;
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// ==================== Map emission ====================

TEST_F(EmitterTest_523, EmitBlockMap_ProducesValidOutput_523) {
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

TEST_F(EmitterTest_523, EmitFlowMap_ProducesValidOutput_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_523, SetMapFormat_Flow_AffectsEmission_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_523, SetMapFormat_Block_AffectsEmission_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Block);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Block maps should not have braces
    EXPECT_EQ(output.find("{"), std::string::npos);
}

// ==================== Stream constructor output ====================

TEST_F(EmitterTest_523, StreamConstructor_WritesToStream_523) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_523, SetLocalValue_Flow_AffectsNextEmission_523) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_523, WriteAnchor_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("myanchor"), std::string::npos);
}

TEST_F(EmitterTest_523, WriteAlias_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::Alias("anc");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Tag ====================

TEST_F(EmitterTest_523, WriteTag_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("mytag") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("mytag"), std::string::npos);
}

// ==================== Comment ====================

TEST_F(EmitterTest_523, WriteComment_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
    EXPECT_NE(output.find("#"), std::string::npos);
}

// ==================== Nested structures ====================

TEST_F(EmitterTest_523, NestedMapInSeq_ProducesValidOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key1"), std::string::npos);
}

TEST_F(EmitterTest_523, NestedSeqInMap_ProducesValidOutput_523) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("items"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_523, RestoreGlobalModifiedSettings_RestoresDefaults_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter.RestoreGlobalModifiedSettings();
    // After restoration, the emitter should still be good
    EXPECT_TRUE(emitter.good());
}

// ==================== Binary ====================

TEST_F(EmitterTest_523, WriteBinary_ProducesOutput_523) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, sizeof(data));
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Multiple documents ====================

TEST_F(EmitterTest_523, MultipleDocuments_ProducesValidOutput_523) {
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

// ==================== SetMapFormat with LongKey ====================

TEST_F(EmitterTest_523, SetMapFormat_LongKey_AffectsEmission_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::LongKey);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "longkey" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Integer formatting ====================

TEST_F(EmitterTest_523, WriteIntHex_ProducesHexOutput_523) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_523, WriteIntOct_ProducesOctalOutput_523) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Char emission ====================

TEST_F(EmitterTest_523, WriteChar_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Double values ====================

TEST_F(EmitterTest_523, WriteDouble_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << 3.14159;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// ==================== Float values ====================

TEST_F(EmitterTest_523, WriteFloat_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("2.5"), std::string::npos);
}

// ==================== Empty string ====================

TEST_F(EmitterTest_523, WriteEmptyString_ProducesOutput_523) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetIndent boundary ====================

TEST_F(EmitterTest_523, SetIndent_One_ReturnsFalse_523) {
    YAML::Emitter emitter;
    // Indent of 1 is typically too small
    bool result = emitter.SetIndent(1);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_523, SetIndent_Zero_ReturnsFalse_523) {
    YAML::Emitter emitter;
    bool result = emitter.SetIndent(0);
    EXPECT_FALSE(result);
}

// ==================== Multiple SetMapFormat calls ====================

TEST_F(EmitterTest_523, SetMapFormat_MultipleCalls_LastOneWins_523) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter.SetMapFormat(YAML::Block);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Block format shouldn't have braces
    EXPECT_EQ(output.find("{"), std::string::npos);
}

// ==================== Newline in string ====================

TEST_F(EmitterTest_523, WriteStringWithNewline_IsHandled_523) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== c_str matches size ====================

TEST_F(EmitterTest_523, CStr_MatchesSize_523) {
    YAML::Emitter emitter;
    emitter << "test";
    std::string output(emitter.c_str());
    EXPECT_EQ(output.size(), emitter.size());
}

// ==================== Bool format affects output ====================

TEST_F(EmitterTest_523, SetBoolFormat_YesNo_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Should contain "yes" in some case
    std::string lower_output = output;
    std::transform(lower_output.begin(), lower_output.end(), lower_output.begin(), ::tolower);
    EXPECT_NE(lower_output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_523, SetBoolFormat_OnOff_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    std::string lower_output = output;
    std::transform(lower_output.begin(), lower_output.end(), lower_output.begin(), ::tolower);
    EXPECT_NE(lower_output.find("on"), std::string::npos);
}

// ==================== Null format affects output ====================

TEST_F(EmitterTest_523, SetNullFormat_Tilde_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_523, SetNullFormat_LowerNull_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_523, SetNullFormat_UpperNull_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("NULL"), std::string::npos);
}

TEST_F(EmitterTest_523, SetNullFormat_CamelNull_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::CamelNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("Null"), std::string::npos);
}

// ==================== String format affects output ====================

TEST_F(EmitterTest_523, SetStringFormat_DoubleQuoted_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_523, SetStringFormat_SingleQuoted_AffectsOutput_523) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}
