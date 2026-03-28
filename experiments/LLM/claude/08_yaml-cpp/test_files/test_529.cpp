#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_529 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// === Construction and Initial State Tests ===

TEST_F(EmitterTest_529, DefaultConstructor_IsGood_529) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, DefaultConstructor_EmptyOutput_529) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_529, DefaultConstructor_CStrNotNull_529) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_529, DefaultConstructor_NoError_529) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_529, StreamConstructor_IsGood_529) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// === Write String Tests ===

TEST_F(EmitterTest_529, WriteString_BasicString_529) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteString_EmptyString_529) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, WriteString_StdString_529) {
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

// === Write Bool Tests ===

TEST_F(EmitterTest_529, WriteBool_True_529) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteBool_False_529) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// === Write Integer Tests ===

TEST_F(EmitterTest_529, WriteInt_PositiveNumber_529) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteInt_NegativeNumber_529) {
    emitter << -7;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteInt_Zero_529) {
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// === Write Float/Double Tests ===

TEST_F(EmitterTest_529, WriteDouble_529) {
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteFloat_529) {
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
}

// === Write Null Tests ===

TEST_F(EmitterTest_529, WriteNull_529) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

// === Sequence Tests ===

TEST_F(EmitterTest_529, WriteSequence_Block_529) {
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteSequence_Flow_529) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteEmptySequence_529) {
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Map Tests ===

TEST_F(EmitterTest_529, WriteMap_Block_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteMap_Flow_529) {
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteEmptyMap_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === Nested Structures Tests ===

TEST_F(EmitterTest_529, NestedMapInSequence_529) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k1" << YAML::Value << "v1";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, NestedSequenceInMap_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("list"), std::string::npos);
}

// === Anchor and Alias Tests ===

TEST_F(EmitterTest_529, WriteAnchor_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "item";
    emitter << YAML::Value << YAML::Anchor("anc") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anc"), std::string::npos);
}

TEST_F(EmitterTest_529, WriteAlias_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "first";
    emitter << YAML::Value << YAML::Anchor("anc") << "value";
    emitter << YAML::Key << "second";
    emitter << YAML::Value << YAML::Alias("anc");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// === Tag Tests ===

TEST_F(EmitterTest_529, WriteTag_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "tagged";
    emitter << YAML::Value << YAML::LocalTag("mytype") << "data";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!mytype"), std::string::npos);
}

// === Comment Tests ===

TEST_F(EmitterTest_529, WriteComment_529) {
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// === SetOutputCharset Tests ===

TEST_F(EmitterTest_529, SetOutputCharset_UTF8_529) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === SetStringFormat Tests ===

TEST_F(EmitterTest_529, SetStringFormat_SingleQuoted_529) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_529, SetStringFormat_DoubleQuoted_529) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_529, SetStringFormat_Literal_529) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

// === SetBoolFormat Tests ===

TEST_F(EmitterTest_529, SetBoolFormat_TrueFalse_529) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_529, SetBoolFormat_YesNo_529) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_529, SetBoolFormat_OnOff_529) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

// === SetNullFormat Tests ===

TEST_F(EmitterTest_529, SetNullFormat_LowerNull_529) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_529, SetNullFormat_Tilde_529) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

// === SetIntBase Tests ===

TEST_F(EmitterTest_529, SetIntBase_Dec_529) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_529, SetIntBase_Hex_529) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_529, SetIntBase_Oct_529) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// === SetSeqFormat Tests ===

TEST_F(EmitterTest_529, SetSeqFormat_Block_529) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_529, SetSeqFormat_Flow_529) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

// === SetMapFormat Tests ===

TEST_F(EmitterTest_529, SetMapFormat_Block_529) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_529, SetMapFormat_Flow_529) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// === SetIndent Tests ===

TEST_F(EmitterTest_529, SetIndent_Valid_529) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_529, SetIndent_MinBoundary_529) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

// === SetPreCommentIndent Tests ===

TEST_F(EmitterTest_529, SetPreCommentIndent_529) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

// === SetPostCommentIndent Tests ===

TEST_F(EmitterTest_529, SetPostCommentIndent_529) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// === SetFloatPrecision Tests ===

TEST_F(EmitterTest_529, SetFloatPrecision_529) {
    EXPECT_TRUE(emitter.SetFloatPrecision(4));
}

// === SetDoublePrecision Tests ===

TEST_F(EmitterTest_529, SetDoublePrecision_529) {
    EXPECT_TRUE(emitter.SetDoublePrecision(8));
}

// === RestoreGlobalModifiedSettings Tests ===

TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_NoModifications_529) {
    // Should not crash or cause errors when no modifications have been made
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_AfterSetBoolFormat_529) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
    // After restoring, writing a bool should use default format
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_AfterMultipleChanges_529) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter.SetIntBase(YAML::Hex);
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
}

// === Output to stream Tests ===

TEST_F(EmitterTest_529, OutputToStream_529) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

TEST_F(EmitterTest_529, OutputToStream_Map_529) {
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

// === Size Tests ===

TEST_F(EmitterTest_529, Size_AfterWrite_529) {
    emitter << "test";
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_529, Size_InitiallyZero_529) {
    EXPECT_EQ(emitter.size(), 0u);
}

// === Char Write Tests ===

TEST_F(EmitterTest_529, WriteChar_529) {
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("A"), std::string::npos);
}

// === Binary Tests ===

TEST_F(EmitterTest_529, WriteBinary_529) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, sizeof(data));
    emitter << binary;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, WriteBinary_Empty_529) {
    YAML::Binary binary(nullptr, 0);
    emitter << binary;
    EXPECT_TRUE(emitter.good());
}

// === Hex Int Base Output Test ===

TEST_F(EmitterTest_529, HexIntOutput_529) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0xff"), std::string::npos);
}

TEST_F(EmitterTest_529, OctIntOutput_529) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("010"), std::string::npos);
}

// === Bool Format Output Tests ===

TEST_F(EmitterTest_529, BoolFormat_YesNo_Output_529) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain some form of "yes"
    EXPECT_TRUE(output.find("yes") != std::string::npos ||
                output.find("Yes") != std::string::npos ||
                output.find("YES") != std::string::npos);
}

TEST_F(EmitterTest_529, BoolFormat_OnOff_Output_529) {
    emitter.SetBoolFormat(YAML::OnOffBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_TRUE(output.find("off") != std::string::npos ||
                output.find("Off") != std::string::npos ||
                output.find("OFF") != std::string::npos);
}

// === Null Format Output Tests ===

TEST_F(EmitterTest_529, NullFormat_LowerNull_Output_529) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_529, NullFormat_Tilde_Output_529) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

// === String Format Output Tests ===

TEST_F(EmitterTest_529, StringFormat_DoubleQuoted_Output_529) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_529, StringFormat_SingleQuoted_Output_529) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// === Document Separator Tests ===

TEST_F(EmitterTest_529, BeginDoc_EndDoc_529) {
    emitter << YAML::BeginDoc;
    emitter << "content";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, MultipleDocuments_529) {
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

// === Newline Tests ===

TEST_F(EmitterTest_529, Newline_529) {
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << YAML::Newline;
    emitter << "b";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === LongKey Tests ===

TEST_F(EmitterTest_529, LongKey_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "longkey" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// === SetLocalValue Tests ===

TEST_F(EmitterTest_529, SetLocalValue_Flow_529) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

// === SetLocalIndent Tests ===

TEST_F(EmitterTest_529, SetLocalIndent_529) {
    emitter << YAML::Indent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === Complex Nested Structure Test ===

TEST_F(EmitterTest_529, ComplexNestedStructure_529) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "id" << YAML::Value << 1;
    emitter << YAML::Key << "tags" << YAML::Value;
    emitter << YAML::Flow << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("items"), std::string::npos);
}

// === Verbatim Tag Test ===

TEST_F(EmitterTest_529, VerbatimTag_529) {
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!<tag:yaml.org,2002:str>"), std::string::npos);
}

// === Invalid Format Setting Tests ===

TEST_F(EmitterTest_529, SetStringFormat_InvalidManip_529) {
    // Passing an invalid EMITTER_MANIP for string format
    bool result = emitter.SetStringFormat(YAML::Block);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_529, SetBoolFormat_InvalidManip_529) {
    bool result = emitter.SetBoolFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_529, SetSeqFormat_InvalidManip_529) {
    bool result = emitter.SetSeqFormat(YAML::Dec);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_529, SetMapFormat_InvalidManip_529) {
    bool result = emitter.SetMapFormat(YAML::Hex);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_529, SetIntBase_InvalidManip_529) {
    bool result = emitter.SetIntBase(YAML::Flow);
    EXPECT_FALSE(result);
}

// === Large data tests ===

TEST_F(EmitterTest_529, LargeSequence_529) {
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 100; i++) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_529, LargeMap_529) {
    emitter << YAML::BeginMap;
    for (int i = 0; i < 50; i++) {
        emitter << YAML::Key << ("key" + std::to_string(i));
        emitter << YAML::Value << i;
    }
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === RestoreGlobalModifiedSettings comprehensive test ===

TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_BoolFormatRestoredToDefault_529) {
    // Set bool format to YesNo globally
    emitter.SetBoolFormat(YAML::YesNoBool);
    // Now restore
    emitter.RestoreGlobalModifiedSettings();
    // Write a bool - should use default TrueFalse format
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_529, RestoreGlobalModifiedSettings_CalledMultipleTimes_529) {
    emitter.RestoreGlobalModifiedSettings();
    emitter.RestoreGlobalModifiedSettings();
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
}

// === Special characters in strings ===

TEST_F(EmitterTest_529, WriteString_WithSpecialChars_529) {
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, WriteString_WithNewline_529) {
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_529, WriteString_WithTab_529) {
    emitter << "col1\tcol2";
    EXPECT_TRUE(emitter.good());
}
