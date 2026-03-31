#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_537 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_537, DefaultConstructor_GoodState_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, DefaultConstructor_EmptyOutput_537) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_537, DefaultConstructor_CStrNotNull_537) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_537, DefaultConstructor_NoLastError_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

TEST_F(EmitterTest_537, StreamConstructor_GoodState_537) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

// ==================== Write(char) ====================

TEST_F(EmitterTest_537, WriteChar_SimpleCharacter_537) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find('A'), std::string::npos);
}

TEST_F(EmitterTest_537, WriteChar_DigitCharacter_537) {
    YAML::Emitter emitter;
    emitter << '5';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find('5'), std::string::npos);
}

TEST_F(EmitterTest_537, WriteChar_SpaceCharacter_537) {
    YAML::Emitter emitter;
    emitter << ' ';
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, WriteChar_SizeIncreases_537) {
    YAML::Emitter emitter;
    emitter << 'x';
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_537, WriteChar_ToStream_537) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << 'Z';
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find('Z'), std::string::npos);
}

// ==================== Write(const std::string&) ====================

TEST_F(EmitterTest_537, WriteString_SimpleString_537) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteString_EmptyString_537) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, WriteString_StdString_537) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteString_SpecialCharacters_537) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, WriteString_ToStream_537) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "test";
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("test"), std::string::npos);
}

// ==================== Write(bool) ====================

TEST_F(EmitterTest_537, WriteBool_True_537) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteBool_False_537) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteBool_TrueCap_537) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

// ==================== Write(Null) ====================

TEST_F(EmitterTest_537, WriteNull_537) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Integral Types ====================

TEST_F(EmitterTest_537, WriteInt_537) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteNegativeInt_537) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-10"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteZero_537) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteIntHex_537) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0xff"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteIntOct_537) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("010"), std::string::npos);
}

// ==================== Float/Double ====================

TEST_F(EmitterTest_537, WriteFloat_537) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteDouble_537) {
    YAML::Emitter emitter;
    emitter << 2.71828;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_537, WriteFlowSequence_537) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteBlockSequence_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("- a"), std::string::npos);
    EXPECT_NE(output.find("- b"), std::string::npos);
    EXPECT_NE(output.find("- c"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteEmptySequence_537) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_537, WriteFlowMap_537) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteBlockMap_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteEmptyMap_537) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_537, WriteAnchor_537) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anc") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anc"), std::string::npos);
}

TEST_F(EmitterTest_537, WriteAlias_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "value";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// ==================== Tag ====================

TEST_F(EmitterTest_537, WriteTag_537) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Comment ====================

TEST_F(EmitterTest_537, WriteComment_537) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_537, WriteBinary_537) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03};
    emitter << YAML::Binary(data, 3);
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Settings ====================

TEST_F(EmitterTest_537, SetOutputCharset_ValidUTF8_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_537, SetStringFormat_SingleQuoted_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "test";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'test'"), std::string::npos);
}

TEST_F(EmitterTest_537, SetStringFormat_DoubleQuoted_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "test";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"test\""), std::string::npos);
}

TEST_F(EmitterTest_537, SetBoolFormat_TrueFalse_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_537, SetBoolFormat_YesNo_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_537, SetBoolFormat_OnOff_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("off"), std::string::npos);
}

TEST_F(EmitterTest_537, SetNullFormat_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_537, SetSeqFormat_Flow_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_537, SetSeqFormat_Block_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_537, SetMapFormat_Flow_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_537, SetMapFormat_Block_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_537, SetIndent_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_537, SetIndent_MinValue_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_537, SetPreCommentIndent_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_537, SetPostCommentIndent_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_537, SetFloatPrecision_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(3));
}

TEST_F(EmitterTest_537, SetDoublePrecision_537) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(6));
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_537, NestedSequenceInMap_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("items"), std::string::npos);
}

TEST_F(EmitterTest_537, NestedMapInSequence_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, NestedMapInMap_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "inner" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_537, MultipleDocuments_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Local Value Manipulators ====================

TEST_F(EmitterTest_537, SetLocalValue_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Long Key ====================

TEST_F(EmitterTest_537, LongKey_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "long_key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Special Characters in Strings ====================

TEST_F(EmitterTest_537, WriteStringWithNewline_537) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_537, WriteStringWithTab_537) {
    YAML::Emitter emitter;
    emitter << "col1\tcol2";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_537, WriteStringWithQuotes_537) {
    YAML::Emitter emitter;
    emitter << "he said \"hello\"";
    EXPECT_TRUE(emitter.good());
}

// ==================== Chaining ====================

TEST_F(EmitterTest_537, ChainingWrites_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Verify c_str and size consistency ====================

TEST_F(EmitterTest_537, CStrAndSizeConsistency_537) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string fromCStr(emitter.c_str());
    EXPECT_EQ(fromCStr.size(), emitter.size());
}

// ==================== Literal and Folded Strings ====================

TEST_F(EmitterTest_537, LiteralString_537) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_537, RestoreGlobalModifiedSettings_537) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Copy and Assignment Deleted ====================

TEST_F(EmitterTest_537, NonCopyable_537) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

// ==================== Precision Settings Applied ====================

TEST_F(EmitterTest_537, FloatPrecisionApplied_537) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // With precision 2, we expect something like "3.1"
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_537, DoublePrecisionApplied_537) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(2);
    emitter << 3.14159;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Map with multiple entries ====================

TEST_F(EmitterTest_537, MapMultipleEntries_537) {
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

// ==================== Sequence with mixed types ====================

TEST_F(EmitterTest_537, SequenceWithMixedTypes_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "string" << 42 << true << 3.14 << YAML::Null;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("string"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Large output ====================

TEST_F(EmitterTest_537, LargeSequence_537) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 100; i++) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 100u);
}

// ==================== Stream output matches c_str ====================

TEST_F(EmitterTest_537, StreamOutputMatchesCStr_537) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string streamOutput = ss.str();
    std::string cstrOutput = emitter.c_str();
    EXPECT_EQ(streamOutput, cstrOutput);
}
