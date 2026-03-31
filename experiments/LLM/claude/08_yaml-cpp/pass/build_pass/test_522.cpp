#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_522 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// --- Construction and Initial State Tests ---

TEST_F(EmitterTest_522, DefaultConstructor_IsGood_522) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_522, DefaultConstructor_EmptyOutput_522) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_522, DefaultConstructor_CStrNotNull_522) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_522, DefaultConstructor_NoLastError_522) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_522, StreamConstructor_IsGood_522) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// --- SetSeqFormat Tests ---

TEST_F(EmitterTest_522, SetSeqFormat_Flow_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_522, SetSeqFormat_Block_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_522, SetSeqFormat_InvalidValue_ReturnsFalse_522) {
    // Passing a manip that is not a flow type should return false
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Dec));
}

TEST_F(EmitterTest_522, SetSeqFormat_FlowProducesFlowSequence_522) {
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_522, SetSeqFormat_BlockProducesBlockSequence_522) {
    emitter.SetSeqFormat(YAML::Block);
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("- "), std::string::npos);
}

// --- SetMapFormat Tests ---

TEST_F(EmitterTest_522, SetMapFormat_Flow_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_522, SetMapFormat_Block_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_522, SetMapFormat_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetMapFormat(YAML::Hex));
}

TEST_F(EmitterTest_522, SetMapFormat_FlowProducesFlowMap_522) {
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap << YAML::Key << "a" << YAML::Value << 1 << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

// --- SetStringFormat Tests ---

TEST_F(EmitterTest_522, SetStringFormat_SingleQuoted_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_522, SetStringFormat_DoubleQuoted_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_522, SetStringFormat_Literal_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_522, SetStringFormat_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetStringFormat(YAML::Flow));
}

// --- SetBoolFormat Tests ---

TEST_F(EmitterTest_522, SetBoolFormat_TrueFalseBool_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_522, SetBoolFormat_YesNoBool_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_522, SetBoolFormat_OnOffBool_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_522, SetBoolFormat_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetBoolFormat(YAML::Flow));
}

// --- SetNullFormat Tests ---

TEST_F(EmitterTest_522, SetNullFormat_LowerNull_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_522, SetNullFormat_TildeNull_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_522, SetNullFormat_CamelNull_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_522, SetNullFormat_UpperNull_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_522, SetNullFormat_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetNullFormat(YAML::Flow));
}

// --- SetIntBase Tests ---

TEST_F(EmitterTest_522, SetIntBase_Dec_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_522, SetIntBase_Hex_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_522, SetIntBase_Oct_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_522, SetIntBase_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetIntBase(YAML::Flow));
}

// --- SetOutputCharset Tests ---

TEST_F(EmitterTest_522, SetOutputCharset_EmitNonAscii_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_522, SetOutputCharset_EscapeNonAscii_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_522, SetOutputCharset_InvalidValue_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetOutputCharset(YAML::Flow));
}

// --- SetIndent Tests ---

TEST_F(EmitterTest_522, SetIndent_ValidValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_522, SetIndent_MinValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_522, SetIndent_TooSmall_ReturnsFalse_522) {
    // Indent of 1 is typically invalid (minimum is 2)
    EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_522, SetIndent_Zero_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetIndent(0));
}

// --- SetPreCommentIndent Tests ---

TEST_F(EmitterTest_522, SetPreCommentIndent_ValidValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_522, SetPreCommentIndent_Zero_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetPreCommentIndent(0));
}

// --- SetPostCommentIndent Tests ---

TEST_F(EmitterTest_522, SetPostCommentIndent_ValidValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

TEST_F(EmitterTest_522, SetPostCommentIndent_Zero_ReturnsFalse_522) {
    EXPECT_FALSE(emitter.SetPostCommentIndent(0));
}

// --- SetFloatPrecision Tests ---

TEST_F(EmitterTest_522, SetFloatPrecision_ValidValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

// --- SetDoublePrecision Tests ---

TEST_F(EmitterTest_522, SetDoublePrecision_ValidValue_ReturnsTrue_522) {
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// --- Write Tests (Scalars) ---

TEST_F(EmitterTest_522, WriteString_ProducesOutput_522) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteInt_ProducesOutput_522) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteBool_True_ProducesOutput_522) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteBool_False_ProducesOutput_522) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteNull_ProducesOutput_522) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteChar_ProducesOutput_522) {
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

// --- Write Tests (Sequences) ---

TEST_F(EmitterTest_522, WriteBlockSequence_ProducesValidOutput_522) {
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteFlowSequence_ProducesValidOutput_522) {
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// --- Write Tests (Maps) ---

TEST_F(EmitterTest_522, WriteBlockMap_ProducesValidOutput_522) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::Key << "key2" << YAML::Value << "val2";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteFlowMap_ProducesValidOutput_522) {
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// --- Anchor and Alias Tests ---

TEST_F(EmitterTest_522, WriteAnchor_ProducesValidOutput_522) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anc"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteAlias_ProducesValidOutput_522) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::Alias("anc");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// --- Tag Tests ---

TEST_F(EmitterTest_522, WriteTag_ProducesValidOutput_522) {
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// --- Comment Tests ---

TEST_F(EmitterTest_522, WriteComment_ProducesValidOutput_522) {
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// --- Stream Constructor Tests ---

TEST_F(EmitterTest_522, StreamConstructor_WritesToStream_522) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// --- Nested Structure Tests ---

TEST_F(EmitterTest_522, NestedMapInSeq_ProducesValidOutput_522) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_522, NestedSeqInMap_ProducesValidOutput_522) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// --- Binary Tests ---

TEST_F(EmitterTest_522, WriteBinary_ProducesValidOutput_522) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// --- RestoreGlobalModifiedSettings Tests ---

TEST_F(EmitterTest_522, RestoreGlobalModifiedSettings_ResetsFormat_522) {
    emitter.SetSeqFormat(YAML::Flow);
    emitter.RestoreGlobalModifiedSettings();
    // After restore, default block format should apply
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("- "), std::string::npos);
}

// --- SetLocalValue Tests ---

TEST_F(EmitterTest_522, SetLocalValue_Flow_AffectsNextGroup_522) {
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

// --- Bool Format Variations ---

TEST_F(EmitterTest_522, BoolFormat_YesNo_True_522) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain yes in some case form
    EXPECT_TRUE(output.find("yes") != std::string::npos ||
                output.find("Yes") != std::string::npos ||
                output.find("YES") != std::string::npos);
}

TEST_F(EmitterTest_522, BoolFormat_OnOff_False_522) {
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_TRUE(output.find("off") != std::string::npos ||
                output.find("Off") != std::string::npos ||
                output.find("OFF") != std::string::npos);
}

// --- Null Format Variations ---

TEST_F(EmitterTest_522, NullFormat_LowerNull_522) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_522, NullFormat_TildeNull_522) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_522, NullFormat_UpperNull_522) {
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("NULL"), std::string::npos);
}

TEST_F(EmitterTest_522, NullFormat_CamelNull_522) {
    emitter.SetNullFormat(YAML::CamelNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("Null"), std::string::npos);
}

// --- Int Base Variations ---

TEST_F(EmitterTest_522, IntBase_Hex_522) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_522, IntBase_Oct_522) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// --- Float/Double Tests ---

TEST_F(EmitterTest_522, WriteFloat_ProducesOutput_522) {
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_522, WriteDouble_ProducesOutput_522) {
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// --- Size and c_str consistency ---

TEST_F(EmitterTest_522, SizeMatchesCStr_522) {
    emitter << "test string";
    std::string output = emitter.c_str();
    EXPECT_EQ(emitter.size(), output.size());
}

// --- Empty Sequence and Map ---

TEST_F(EmitterTest_522, EmptyFlowSequence_522) {
    emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("[]"), std::string::npos);
}

TEST_F(EmitterTest_522, EmptyFlowMap_522) {
    emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// --- Multiple documents ---

TEST_F(EmitterTest_522, MultipleDocuments_522) {
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// --- SetLocalIndent ---

TEST_F(EmitterTest_522, SetLocalIndent_522) {
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// --- Long Key ---

TEST_F(EmitterTest_522, LongKey_ProducesValidOutput_522) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey << YAML::Key << "longkeytest" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// --- Double quoted string format ---

TEST_F(EmitterTest_522, StringFormat_DoubleQuoted_522) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// --- Single quoted string format ---

TEST_F(EmitterTest_522, StringFormat_SingleQuoted_522) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// --- Write with const char* and size ---

TEST_F(EmitterTest_522, WriteCStrWithSize_522) {
    const char* data = "hello world";
    emitter.Write(data, 5);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}
