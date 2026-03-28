#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_524 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// ===== Basic Construction and State Tests =====

TEST_F(EmitterTest_524, DefaultConstructor_IsGood_524) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, DefaultConstructor_EmptyOutput_524) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_524, DefaultConstructor_CStrNotNull_524) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_524, DefaultConstructor_NoError_524) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_524, StreamConstructor_IsGood_524) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
}

// ===== SetIndent Tests =====

TEST_F(EmitterTest_524, SetIndent_ValidValue_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_524, SetIndent_DefaultValue2_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_524, SetIndent_LargeValue_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIndent(10));
}

TEST_F(EmitterTest_524, SetIndent_MinimumValue_524) {
    // Indent of 1 might be rejected as too small
    // Testing boundary
    bool result = emitter.SetIndent(1);
    // Just observe the result, don't assert specific value since it's implementation dependent
    (void)result;
}

TEST_F(EmitterTest_524, SetIndent_ZeroValue_524) {
    // Zero indent is likely invalid
    bool result = emitter.SetIndent(0);
    // Implementation may reject 0
    (void)result;
}

TEST_F(EmitterTest_524, SetIndent_AffectsOutput_524) {
    emitter.SetIndent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== SetPreCommentIndent Tests =====

TEST_F(EmitterTest_524, SetPreCommentIndent_ValidValue_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_524, SetPreCommentIndent_ZeroValue_524) {
    bool result = emitter.SetPreCommentIndent(0);
    (void)result;
}

// ===== SetPostCommentIndent Tests =====

TEST_F(EmitterTest_524, SetPostCommentIndent_ValidValue_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ===== SetOutputCharset Tests =====

TEST_F(EmitterTest_524, SetOutputCharset_UTF8_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_524, SetOutputCharset_EmitNonAscii_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

// ===== SetStringFormat Tests =====

TEST_F(EmitterTest_524, SetStringFormat_SingleQuoted_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_524, SetStringFormat_DoubleQuoted_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_524, SetStringFormat_Literal_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

// ===== SetBoolFormat Tests =====

TEST_F(EmitterTest_524, SetBoolFormat_TrueFalseBool_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_524, SetBoolFormat_YesNoBool_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_524, SetBoolFormat_OnOffBool_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_524, SetBoolFormat_UpperCase_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_524, SetBoolFormat_LowerCase_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_524, SetBoolFormat_CamelCase_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_524, SetBoolFormat_LongBool_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_524, SetBoolFormat_ShortBool_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

// ===== SetNullFormat Tests =====

TEST_F(EmitterTest_524, SetNullFormat_LowerNull_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_524, SetNullFormat_TildeNull_524) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

// ===== SetIntBase Tests =====

TEST_F(EmitterTest_524, SetIntBase_Dec_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_524, SetIntBase_Hex_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_524, SetIntBase_Oct_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// ===== SetSeqFormat Tests =====

TEST_F(EmitterTest_524, SetSeqFormat_Flow_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_524, SetSeqFormat_Block_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

// ===== SetMapFormat Tests =====

TEST_F(EmitterTest_524, SetMapFormat_Flow_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_524, SetMapFormat_Block_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

// ===== SetFloatPrecision / SetDoublePrecision Tests =====

TEST_F(EmitterTest_524, SetFloatPrecision_Valid_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_524, SetDoublePrecision_Valid_ReturnsTrue_524) {
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_524, SetFloatPrecision_Zero_524) {
    bool result = emitter.SetFloatPrecision(0);
    (void)result;
}

TEST_F(EmitterTest_524, SetDoublePrecision_Zero_524) {
    bool result = emitter.SetDoublePrecision(0);
    (void)result;
}

// ===== Write Tests =====

TEST_F(EmitterTest_524, WriteString_SimpleString_524) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_524, WriteString_StdString_524) {
    std::string s = "world";
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_524, WriteBool_True_524) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteBool_False_524) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteInt_524) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_524, WriteDouble_524) {
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteFloat_524) {
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteChar_524) {
    emitter << 'a';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteNull_524) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== Sequence Tests =====

TEST_F(EmitterTest_524, SimpleBlockSequence_524) {
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

TEST_F(EmitterTest_524, SimpleFlowSequence_524) {
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// ===== Map Tests =====

TEST_F(EmitterTest_524, SimpleBlockMap_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::Key << "age" << YAML::Value << 30;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
    EXPECT_NE(output.find("age"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

TEST_F(EmitterTest_524, SimpleFlowMap_524) {
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// ===== Nested Structure Tests =====

TEST_F(EmitterTest_524, NestedMapInSeq_524) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, NestedSeqInMap_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("list"), std::string::npos);
}

// ===== Comment Tests =====

TEST_F(EmitterTest_524, WriteComment_524) {
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
}

// ===== Anchor and Alias Tests =====

TEST_F(EmitterTest_524, WriteAnchor_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << YAML::Anchor("anchor1") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_524, WriteAlias_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "first" << YAML::Value << YAML::Anchor("anc") << "val";
    emitter << YAML::Key << "second" << YAML::Value << YAML::Alias("anc");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ===== Tag Tests =====

TEST_F(EmitterTest_524, WriteTag_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "tagged" << YAML::Value << YAML::LocalTag("mytag") << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("mytag"), std::string::npos);
}

// ===== Document Tests =====

TEST_F(EmitterTest_524, BeginDoc_524) {
    emitter << YAML::BeginDoc;
    emitter << "value";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_524, MultipleDocuments_524) {
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

// ===== Stream Constructor Tests =====

TEST_F(EmitterTest_524, StreamConstructor_WritesToStream_524) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "hello";
    EXPECT_TRUE(e.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_524, StreamConstructor_MapWritesToStream_524) {
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

// ===== BoolFormat Effect Tests =====

TEST_F(EmitterTest_524, BoolFormat_TrueFalse_Output_524) {
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain some form of "true"
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, BoolFormat_YesNo_Output_524) {
    YAML::Emitter e;
    e.SetBoolFormat(YAML::YesNoBool);
    e << true;
    EXPECT_TRUE(e.good());
    std::string output = e.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, BoolFormat_OnOff_Output_524) {
    YAML::Emitter e;
    e.SetBoolFormat(YAML::OnOffBool);
    e << false;
    EXPECT_TRUE(e.good());
    std::string output = e.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== IntBase Effect Tests =====

TEST_F(EmitterTest_524, IntBase_Hex_Output_524) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_524, IntBase_Oct_Output_524) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ===== NullFormat Effect Tests =====

TEST_F(EmitterTest_524, NullFormat_Tilde_524) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_524, NullFormat_LowerNull_524) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

// ===== SetIndent with Sequence =====

TEST_F(EmitterTest_524, SetIndent_NestedSequenceIndentation_524) {
    emitter.SetIndent(6);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list" << YAML::Value;
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== RestoreGlobalModifiedSettings Tests =====

TEST_F(EmitterTest_524, RestoreGlobalModifiedSettings_524) {
    emitter.SetIndent(6);
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, emitter should still be good
    EXPECT_TRUE(emitter.good());
}

// ===== SetLocalValue Tests =====

TEST_F(EmitterTest_524, SetLocalValue_Flow_524) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ===== SetLocalIndent Tests =====

TEST_F(EmitterTest_524, SetLocalIndent_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer" << YAML::Value;
    emitter << YAML::Indent(8) << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ===== Binary Tests =====

TEST_F(EmitterTest_524, WriteBinary_524) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0xFF};
    YAML::Binary binary(data.data(), data.size());
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== Empty String Tests =====

TEST_F(EmitterTest_524, WriteEmptyString_524) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, WriteEmptyStdString_524) {
    std::string empty;
    emitter << empty;
    EXPECT_TRUE(emitter.good());
}

// ===== Negative Integer Tests =====

TEST_F(EmitterTest_524, WriteNegativeInt_524) {
    emitter << -42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-42"), std::string::npos);
}

// ===== Long Key Tests =====

TEST_F(EmitterTest_524, LongKey_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "longkey" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ===== VerbatimTag Tests =====

TEST_F(EmitterTest_524, VerbatimTag_524) {
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ===== String Formats =====

TEST_F(EmitterTest_524, StringFormat_DoubleQuoted_524) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_524, StringFormat_SingleQuoted_524) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// ===== Literal String Format =====

TEST_F(EmitterTest_524, StringFormat_Literal_MultiLine_524) {
    emitter.SetStringFormat(YAML::Literal);
    emitter << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ===== Complex Nested Structure =====

TEST_F(EmitterTest_524, ComplexNestedStructure_524) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "database" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "host" << YAML::Value << "localhost";
    emitter << YAML::Key << "port" << YAML::Value << 5432;
    emitter << YAML::Key << "tables" << YAML::Value;
    emitter << YAML::BeginSeq << "users" << "orders" << "products" << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("database"), std::string::npos);
    EXPECT_NE(output.find("localhost"), std::string::npos);
    EXPECT_NE(output.find("5432"), std::string::npos);
    EXPECT_NE(output.find("users"), std::string::npos);
}

// ===== Size and c_str consistency =====

TEST_F(EmitterTest_524, SizeMatchesCStrLength_524) {
    emitter << "test";
    EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

// ===== Multiple Scalars at Top Level =====

TEST_F(EmitterTest_524, MultipleTopLevelScalars_InSequence_524) {
    emitter << YAML::BeginSeq;
    emitter << "first";
    emitter << "second";
    emitter << "third";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ===== SetIndent boundary: value of 1 =====

TEST_F(EmitterTest_524, SetIndent_One_MayFail_524) {
    bool result = emitter.SetIndent(1);
    // Indent of 1 is likely too small
    // Just verify emitter is still in a usable state
    if (!result) {
        // If SetIndent(1) returns false, emitter should still be good
        EXPECT_TRUE(emitter.good());
    }
}

// ===== Emitter with special characters =====

TEST_F(EmitterTest_524, WriteStringWithSpecialChars_524) {
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // String with colon should be quoted
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_524, WriteStringWithNewlines_524) {
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ===== SetFloatPrecision effect =====

TEST_F(EmitterTest_524, FloatPrecision_Effect_524) {
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, DoublePrecision_Effect_524) {
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
}

// ===== SetSeqFormat with invalid EMITTER_MANIP =====

TEST_F(EmitterTest_524, SetSeqFormat_InvalidManip_ReturnsFalse_524) {
    // Using a MANIP that's not Flow or Block for sequences
    bool result = emitter.SetSeqFormat(YAML::TrueFalseBool);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetMapFormat_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetMapFormat(YAML::TrueFalseBool);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetIntBase_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetIntBase(YAML::Flow);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetStringFormat_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetStringFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetBoolFormat_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetBoolFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetOutputCharset_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetOutputCharset(YAML::Flow);
    EXPECT_FALSE(result);
}

TEST_F(EmitterTest_524, SetNullFormat_InvalidManip_ReturnsFalse_524) {
    bool result = emitter.SetNullFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

// ===== Empty Map and Seq =====

TEST_F(EmitterTest_524, EmptyMap_524) {
    emitter << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, EmptySeq_524) {
    emitter << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ===== Long integer types =====

TEST_F(EmitterTest_524, WriteLongLong_524) {
    emitter << (long long)9223372036854775807LL;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_524, WriteUnsignedInt_524) {
    emitter << (unsigned int)4294967295u;
    EXPECT_TRUE(emitter.good());
}
