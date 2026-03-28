#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_38 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_38, DefaultConstructor_GoodState_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_38, DefaultConstructor_EmptyOutput_38) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_38, DefaultConstructor_CStrNotNull_38) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_38, StreamConstructor_GoodState_38) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_38, DefaultConstructor_NoError_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

// ==================== Bool Writing (the operator<< from the prompt) ====================

TEST_F(EmitterTest_38, WriteBoolTrue_38) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_38, WriteBoolFalse_38) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_38, WriteBoolTrueDefaultFormat_38) {
    YAML::Emitter emitter;
    emitter << true;
    std::string output(emitter.c_str());
    // Default bool format should produce "true"
    EXPECT_EQ(output, "true");
}

TEST_F(EmitterTest_38, WriteBoolFalseDefaultFormat_38) {
    YAML::Emitter emitter;
    emitter << false;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "false");
}

TEST_F(EmitterTest_38, WriteBoolTrueUpperCase_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << true;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "True");
}

TEST_F(EmitterTest_38, WriteBoolFalseUpperCase_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << false;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "False");
}

TEST_F(EmitterTest_38, WriteBoolTrueCamelCase_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::CamelCase);
    emitter << true;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "True");
}

TEST_F(EmitterTest_38, WriteBoolTrueLongBool_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::LongBool);
    emitter << true;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "true");
}

TEST_F(EmitterTest_38, WriteBoolFalseLongBool_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::LongBool);
    emitter << false;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "false");
}

TEST_F(EmitterTest_38, WriteBoolTrueShortBool_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::ShortBool);
    emitter << true;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "y");
}

TEST_F(EmitterTest_38, WriteBoolFalseShortBool_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::ShortBool);
    emitter << false;
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "n");
}

// ==================== String Writing ====================

TEST_F(EmitterTest_38, WriteString_38) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteStdString_38) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteEmptyString_38) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// ==================== Integer Writing ====================

TEST_F(EmitterTest_38, WriteInt_38) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_38, WriteNegativeInt_38) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "-10");
}

TEST_F(EmitterTest_38, WriteZero_38) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0");
}

TEST_F(EmitterTest_38, WriteIntHex_38) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteIntOct_38) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Float/Double Writing ====================

TEST_F(EmitterTest_38, WriteFloat_38) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteDouble_38) {
    YAML::Emitter emitter;
    emitter << 2.718281828;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

// ==================== Null Writing ====================

TEST_F(EmitterTest_38, WriteNull_38) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

// ==================== Sequence Writing ====================

TEST_F(EmitterTest_38, WriteBlockSequence_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("- 1"), std::string::npos);
    EXPECT_NE(output.find("- 2"), std::string::npos);
    EXPECT_NE(output.find("- 3"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteFlowSequence_38) {
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

TEST_F(EmitterTest_38, WriteEmptySequence_38) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Map Writing ====================

TEST_F(EmitterTest_38, WriteBlockMap_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteFlowMap_38) {
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

TEST_F(EmitterTest_38, WriteEmptyMap_38) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Comment Writing ====================

TEST_F(EmitterTest_38, WriteComment_38) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_38, WriteAnchor_38) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_38, WriteAlias_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "value";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// ==================== Tag Writing ====================

TEST_F(EmitterTest_38, WriteTag_38) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Char Writing ====================

TEST_F(EmitterTest_38, WriteChar_38) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Stream Output ====================

TEST_F(EmitterTest_38, StreamConstructor_WritesToStream_38) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== Size ====================

TEST_F(EmitterTest_38, SizeIncreasesAfterWrite_38) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "test";
    EXPECT_GT(emitter.size(), initialSize);
}

// ==================== SetBoolFormat Validation ====================

TEST_F(EmitterTest_38, SetBoolFormat_ValidValue_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_38, SetBoolFormat_InvalidValue_38) {
    YAML::Emitter emitter;
    // Passing a manip that isn't a bool format should return false
    EXPECT_FALSE(emitter.SetBoolFormat(YAML::Hex));
}

// ==================== SetStringFormat Validation ====================

TEST_F(EmitterTest_38, SetStringFormat_ValidValues_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

// ==================== SetSeqFormat Validation ====================

TEST_F(EmitterTest_38, SetSeqFormat_ValidValues_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_38, SetSeqFormat_InvalidValue_38) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Hex));
}

// ==================== SetMapFormat Validation ====================

TEST_F(EmitterTest_38, SetMapFormat_ValidValues_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_38, SetMapFormat_InvalidValue_38) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetMapFormat(YAML::Hex));
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_38, SetIndent_Valid_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_38, SetIndent_TooSmall_38) {
    YAML::Emitter emitter;
    // Indent of 1 is too small (min is 2)
    EXPECT_FALSE(emitter.SetIndent(1));
}

// ==================== SetFloatPrecision ====================

TEST_F(EmitterTest_38, SetFloatPrecision_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

// ==================== SetDoublePrecision ====================

TEST_F(EmitterTest_38, SetDoublePrecision_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_38, SetIntBase_Dec_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_38, SetIntBase_Hex_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_38, SetIntBase_Oct_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_38, SetIntBase_InvalidValue_38) {
    YAML::Emitter emitter;
    EXPECT_FALSE(emitter.SetIntBase(YAML::Flow));
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_38, SetNullFormat_Valid_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

// ==================== Complex Structures ====================

TEST_F(EmitterTest_38, NestedMapInSequence_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_38, NestedSequenceInMap_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("list"), std::string::npos);
}

TEST_F(EmitterTest_38, MultipleDocuments_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "first";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "second";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

// ==================== Binary Writing ====================

TEST_F(EmitterTest_38, WriteBinary_38) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ==================== Local Value Setting ====================

TEST_F(EmitterTest_38, SetLocalValue_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Multiple Bools in Sequence ====================

TEST_F(EmitterTest_38, MultipleBoolsInSequence_38) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << true << false << true;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
    EXPECT_NE(output.find("false"), std::string::npos);
}

// ==================== Bool as Map Value ====================

TEST_F(EmitterTest_38, BoolAsMapValue_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "enabled" << YAML::Value << true;
    emitter << YAML::Key << "disabled" << YAML::Value << false;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("enabled: true"), std::string::npos);
    EXPECT_NE(output.find("disabled: false"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_38, RestoreGlobalModifiedSettings_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::ShortBool);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // After restore, should be back to default (TrueFalseBool/LongBool)
    EXPECT_EQ(output, "true");
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterTest_38, SetPreCommentIndent_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_38, SetPostCommentIndent_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== Operator<< chaining with bool ====================

TEST_F(EmitterTest_38, OperatorChaining_38) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << true;
    emitter << false;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[true, false]"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_38, WriteNewline_38) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << YAML::Newline;
    emitter << "second";
    EXPECT_TRUE(emitter.good());
}

// ==================== Long Bool Formats ====================

TEST_F(EmitterTest_38, WriteBoolYesNoBoolTrue_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "yes");
}

TEST_F(EmitterTest_38, WriteBoolYesNoBoolFalse_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "no");
}

TEST_F(EmitterTest_38, WriteBoolOnOffBoolTrue_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "on");
}

TEST_F(EmitterTest_38, WriteBoolOnOffBoolFalse_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "off");
}

// ==================== UpperCase combined with different bool types ====================

TEST_F(EmitterTest_38, WriteBoolUpperCaseYesNo_38) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

// ==================== Precision Tests ====================

TEST_F(EmitterTest_38, FloatPrecisionAffectsOutput_38) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.1"), std::string::npos);
}

TEST_F(EmitterTest_38, DoublePrecisionAffectsOutput_38) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(15);
    emitter << 3.141592653589793;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14159265358979"), std::string::npos);
}

// ==================== Deeply nested structure ====================

TEST_F(EmitterTest_38, DeeplyNestedStructure_38) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level1" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level2" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << true << false;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_38, SetOutputCharset_UTF8_38) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}
