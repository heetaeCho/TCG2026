#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_520 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// ===================== Construction and Initial State =====================

TEST_F(EmitterTest_520, DefaultConstructor_IsGood_520) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_520, DefaultConstructor_EmptyOutput_520) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_520, DefaultConstructor_CStrNotNull_520) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_520, DefaultConstructor_NoError_520) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_520, StreamConstructor_IsGood_520) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// ===================== SetNullFormat =====================

TEST_F(EmitterTest_520, SetNullFormat_LowerNull_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_520, SetNullFormat_UpperNull_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_520, SetNullFormat_CamelNull_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_520, SetNullFormat_TildeNull_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_520, SetNullFormat_InvalidManip_ReturnsFalse_520) {
    // Passing a manip that doesn't apply to null format
    EXPECT_FALSE(emitter.SetNullFormat(YAML::Dec));
}

TEST_F(EmitterTest_520, SetNullFormat_LowerNull_OutputsLowerNull_520) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "null");
}

TEST_F(EmitterTest_520, SetNullFormat_UpperNull_OutputsUpperNull_520) {
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "NULL");
}

TEST_F(EmitterTest_520, SetNullFormat_CamelNull_OutputsCamelNull_520) {
    emitter.SetNullFormat(YAML::CamelNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "Null");
}

TEST_F(EmitterTest_520, SetNullFormat_TildeNull_OutputsTilde_520) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

// ===================== SetBoolFormat =====================

TEST_F(EmitterTest_520, SetBoolFormat_TrueFalseBool_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_520, SetBoolFormat_YesNoBool_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_520, SetBoolFormat_OnOffBool_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_520, SetBoolFormat_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetBoolFormat(YAML::Dec));
}

TEST_F(EmitterTest_520, SetBoolFormat_TrueFalse_OutputsTrue_520) {
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "true");
}

TEST_F(EmitterTest_520, SetBoolFormat_YesNo_OutputsYes_520) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "yes");
}

TEST_F(EmitterTest_520, SetBoolFormat_OnOff_OutputsOn_520) {
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "on");
}

// ===================== SetStringFormat =====================

TEST_F(EmitterTest_520, SetStringFormat_Auto_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Auto));
}

TEST_F(EmitterTest_520, SetStringFormat_SingleQuoted_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_520, SetStringFormat_DoubleQuoted_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_520, SetStringFormat_Literal_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_520, SetStringFormat_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetStringFormat(YAML::Dec));
}

// ===================== SetIntBase =====================

TEST_F(EmitterTest_520, SetIntBase_Dec_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_520, SetIntBase_Hex_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_520, SetIntBase_Oct_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_520, SetIntBase_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetIntBase(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_520, SetIntBase_Hex_OutputsHex_520) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0xff");
}

TEST_F(EmitterTest_520, SetIntBase_Oct_OutputsOct_520) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "010");
}

// ===================== SetSeqFormat =====================

TEST_F(EmitterTest_520, SetSeqFormat_Block_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_520, SetSeqFormat_Flow_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_520, SetSeqFormat_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Dec));
}

// ===================== SetMapFormat =====================

TEST_F(EmitterTest_520, SetMapFormat_Block_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_520, SetMapFormat_Flow_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_520, SetMapFormat_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetMapFormat(YAML::Dec));
}

// ===================== SetOutputCharset =====================

TEST_F(EmitterTest_520, SetOutputCharset_EmitNonAscii_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_520, SetOutputCharset_EscapeNonAscii_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_520, SetOutputCharset_InvalidManip_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetOutputCharset(YAML::Dec));
}

// ===================== SetIndent =====================

TEST_F(EmitterTest_520, SetIndent_ValidValue_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_520, SetIndent_MinimumValue_520) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_520, SetIndent_TooSmall_ReturnsFalse_520) {
    // Indent of 1 is typically too small
    EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_520, SetIndent_Zero_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetIndent(0));
}

// ===================== SetPreCommentIndent =====================

TEST_F(EmitterTest_520, SetPreCommentIndent_Valid_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_520, SetPreCommentIndent_Zero_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetPreCommentIndent(0));
}

// ===================== SetPostCommentIndent =====================

TEST_F(EmitterTest_520, SetPostCommentIndent_Valid_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

TEST_F(EmitterTest_520, SetPostCommentIndent_Zero_ReturnsFalse_520) {
    EXPECT_FALSE(emitter.SetPostCommentIndent(0));
}

// ===================== SetFloatPrecision / SetDoublePrecision =====================

TEST_F(EmitterTest_520, SetFloatPrecision_Valid_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_520, SetDoublePrecision_Valid_ReturnsTrue_520) {
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// ===================== Write scalar values =====================

TEST_F(EmitterTest_520, WriteString_ProducesOutput_520) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "hello");
}

TEST_F(EmitterTest_520, WriteInt_ProducesOutput_520) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_520, WriteDouble_ProducesOutput_520) {
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_520, WriteBoolTrue_ProducesOutput_520) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "true");
}

TEST_F(EmitterTest_520, WriteBoolFalse_ProducesOutput_520) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "false");
}

TEST_F(EmitterTest_520, WriteNull_ProducesOutput_520) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

TEST_F(EmitterTest_520, WriteChar_ProducesOutput_520) {
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ===================== Sequences =====================

TEST_F(EmitterTest_520, BlockSequence_ProducesValidYAML_520) {
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_520, FlowSequence_ProducesValidYAML_520) {
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// ===================== Maps =====================

TEST_F(EmitterTest_520, BlockMap_ProducesValidYAML_520) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_520, FlowMap_ProducesValidYAML_520) {
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// ===================== Nested structures =====================

TEST_F(EmitterTest_520, NestedMapInSequence_520) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_520, NestedSequenceInMap_520) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ===================== Comments =====================

TEST_F(EmitterTest_520, Comment_ProducesOutput_520) {
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ===================== Anchor and Alias =====================

TEST_F(EmitterTest_520, Anchor_ProducesOutput_520) {
    emitter << YAML::Anchor("anchor1") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_520, Alias_ProducesOutput_520) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("a") << "value";
    emitter << YAML::Alias("a");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*a"), std::string::npos);
}

// ===================== Tag =====================

TEST_F(EmitterTest_520, Tag_ProducesOutput_520) {
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!<tag:yaml.org,2002:str>"), std::string::npos);
}

// ===================== Stream constructor output =====================

TEST_F(EmitterTest_520, StreamConstructor_OutputGoesToStream_520) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ===================== RestoreGlobalModifiedSettings =====================

TEST_F(EmitterTest_520, RestoreGlobalModifiedSettings_520) {
    emitter.SetNullFormat(YAML::UpperNull);
    emitter.RestoreGlobalModifiedSettings();
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // After restore, should use default null format (~)
    EXPECT_EQ(output, "~");
}

// ===================== SetLocalValue =====================

TEST_F(EmitterTest_520, SetLocalValue_Flow_520) {
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

// ===================== Binary =====================

TEST_F(EmitterTest_520, WriteBinary_ProducesOutput_520) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ===================== Multiple documents =====================

TEST_F(EmitterTest_520, MultipleDocuments_520) {
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
    EXPECT_NE(output.find("..."), std::string::npos);
}

// ===================== Long key in map =====================

TEST_F(EmitterTest_520, LongKey_ProducesValidYAML_520) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey << YAML::Key << "longkey" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ===================== Empty string =====================

TEST_F(EmitterTest_520, WriteEmptyString_520) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ===================== Negative integer =====================

TEST_F(EmitterTest_520, WriteNegativeInt_520) {
    emitter << -42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "-42");
}

// ===================== Size matches c_str length =====================

TEST_F(EmitterTest_520, SizeMatchesCStrLength_520) {
    emitter << "test";
    EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

// ===================== Global format applies to multiple writes =====================

TEST_F(EmitterTest_520, SetNullFormat_Global_AppliesMultipleTimes_520) {
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::BeginSeq;
    emitter << YAML::Null;
    emitter << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Count occurrences of NULL
    std::size_t count = 0;
    std::size_t pos = 0;
    while ((pos = output.find("NULL", pos)) != std::string::npos) {
        count++;
        pos += 4;
    }
    EXPECT_EQ(count, 2u);
}

// ===================== Emitter good status after invalid format =====================

TEST_F(EmitterTest_520, InvalidFormat_StillGood_520) {
    bool result = emitter.SetNullFormat(YAML::Dec);
    EXPECT_FALSE(result);
    // Emitter should still be good even though format was invalid
    EXPECT_TRUE(emitter.good());
}

// ===================== Double quoted string format =====================

TEST_F(EmitterTest_520, DoubleQuotedStringFormat_520) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ===================== Single quoted string format =====================

TEST_F(EmitterTest_520, SingleQuotedStringFormat_520) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}
