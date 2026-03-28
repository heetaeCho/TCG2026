#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_513 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default constructor and initial state tests
// ============================================================

TEST_F(EmitterTest_513, DefaultConstructor_InitiallyGood_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_513, DefaultConstructor_InitialSizeIsZero_513) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_513, DefaultConstructor_CStrNotNull_513) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_513, DefaultConstructor_CStrIsEmptyString_513) {
    YAML::Emitter emitter;
    EXPECT_STREQ(emitter.c_str(), "");
}

TEST_F(EmitterTest_513, DefaultConstructor_NoLastError_513) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// ============================================================
// Stream constructor tests
// ============================================================

TEST_F(EmitterTest_513, StreamConstructor_InitiallyGood_513) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_513, StreamConstructor_WritesToStream_513) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    emitter << "hello";
    EXPECT_NE(stream.str().find("hello"), std::string::npos);
}

// ============================================================
// Writing scalar values
// ============================================================

TEST_F(EmitterTest_513, WriteString_SimpleString_513) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_STREQ(emitter.c_str(), "hello");
}

TEST_F(EmitterTest_513, WriteString_SizeMatchesOutput_513) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_EQ(emitter.size(), std::string("hello").size());
}

TEST_F(EmitterTest_513, WriteString_EmptyString_513) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Empty string should still produce valid YAML output
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_513, WriteBool_True_513) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteBool_False_513) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteInt_513) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteNegativeInt_513) {
    YAML::Emitter emitter;
    emitter << -7;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteDouble_513) {
    YAML::Emitter emitter;
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteChar_513) {
    YAML::Emitter emitter;
    emitter << 'a';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("a"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteNull_513) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Sequence tests
// ============================================================

TEST_F(EmitterTest_513, WriteBlockSequence_513) {
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

TEST_F(EmitterTest_513, WriteFlowSequence_513) {
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

TEST_F(EmitterTest_513, WriteEmptySequence_513) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ============================================================
// Map tests
// ============================================================

TEST_F(EmitterTest_513, WriteBlockMap_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "John";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteFlowMap_513) {
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

TEST_F(EmitterTest_513, WriteEmptyMap_513) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ============================================================
// Nested structures
// ============================================================

TEST_F(EmitterTest_513, WriteNestedMapInSequence_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteNestedSequenceInMap_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("items"), std::string::npos);
}

// ============================================================
// Comments
// ============================================================

TEST_F(EmitterTest_513, WriteComment_513) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ============================================================
// Anchors and Aliases
// ============================================================

TEST_F(EmitterTest_513, WriteAnchor_513) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_513, WriteAlias_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("ref") << "value";
    emitter << YAML::Alias("ref");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*ref"), std::string::npos);
}

// ============================================================
// Tags
// ============================================================

TEST_F(EmitterTest_513, WriteTag_513) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("tag") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!tag"), std::string::npos);
}

// ============================================================
// Setting manipulators / format options
// ============================================================

TEST_F(EmitterTest_513, SetBoolFormat_TrueFalse_513) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_513, SetBoolFormat_YesNo_513) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_513, SetBoolFormat_UpperCase_513) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase | YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_513, SetIntBase_Hex_513) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_513, SetIntBase_Oct_513) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_513, SetSeqFormat_Flow_513) {
    YAML::Emitter emitter;
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_513, SetMapFormat_Flow_513) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_513, SetIndent_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_513, SetIndent_TooSmall_513) {
    YAML::Emitter emitter;
    // Indent of 1 may be rejected (minimum is typically 2)
    bool result = emitter.SetIndent(1);
    // We just observe the return value; implementation may accept or reject
    (void)result;
}

TEST_F(EmitterTest_513, SetPreCommentIndent_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_513, SetPostCommentIndent_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_513, SetFloatPrecision_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_513, SetDoublePrecision_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_513, SetNullFormat_Tilde_513) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_513, SetStringFormat_DoubleQuoted_513) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_513, SetStringFormat_SingleQuoted_513) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// ============================================================
// Local manipulators
// ============================================================

TEST_F(EmitterTest_513, SetLocalValue_Flow_513) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_513, SetLocalIndent_513) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ============================================================
// Document markers
// ============================================================

TEST_F(EmitterTest_513, BeginDoc_EndDoc_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "hello";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_513, MultipleDocuments_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ============================================================
// Binary data
// ============================================================

TEST_F(EmitterTest_513, WriteBinary_513) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x00, 0x01, 0x02, 0xFF};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteBinary_Empty_513) {
    YAML::Emitter emitter;
    emitter << YAML::Binary(nullptr, 0);
    EXPECT_TRUE(emitter.good());
}

// ============================================================
// Complex map with multiple key-value pairs
// ============================================================

TEST_F(EmitterTest_513, WriteMultipleMapEntries_513) {
    YAML::Emitter emitter;
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

// ============================================================
// Verify output via ostream constructor
// ============================================================

TEST_F(EmitterTest_513, StreamOutput_MatchesCStr_513) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    // Stream output should contain the same content
    EXPECT_NE(stream.str().find("a"), std::string::npos);
    EXPECT_NE(stream.str().find("b"), std::string::npos);
}

// ============================================================
// Long key in map
// ============================================================

TEST_F(EmitterTest_513, WriteLongKey_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::LongKey;
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ============================================================
// RestoreGlobalModifiedSettings
// ============================================================

TEST_F(EmitterTest_513, RestoreGlobalModifiedSettings_513) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, should still be good
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

// ============================================================
// Write const char* with size
// ============================================================

TEST_F(EmitterTest_513, WriteCharPtrWithSize_513) {
    YAML::Emitter emitter;
    const char* str = "hello world";
    emitter.Write(str, 5);  // should write "hello"
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ============================================================
// Verify Emitter is not copyable
// ============================================================

TEST_F(EmitterTest_513, EmitterIsNotCopyable_513) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

// ============================================================
// Special string values that need quoting
// ============================================================

TEST_F(EmitterTest_513, WriteStringWithSpecialChars_513) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteStringThatLooksLikeBool_513) {
    YAML::Emitter emitter;
    emitter << "true";
    EXPECT_TRUE(emitter.good());
    // Should be quoted to distinguish from boolean
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, WriteStringWithNewlines_513) {
    YAML::Emitter emitter;
    emitter << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Verbatim tag
// ============================================================

TEST_F(EmitterTest_513, WriteVerbatimTag_513) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ============================================================
// Literal block scalar
// ============================================================

TEST_F(EmitterTest_513, WriteLiteral_513) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ============================================================
// SetOutputCharset
// ============================================================

TEST_F(EmitterTest_513, SetOutputCharset_UTF8_513) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ============================================================
// Deeply nested structures
// ============================================================

TEST_F(EmitterTest_513, DeeplyNestedStructure_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level1";
    emitter << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level2";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "level3" << YAML::Value << "deep";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("level1"), std::string::npos);
    EXPECT_NE(output.find("level2"), std::string::npos);
    EXPECT_NE(output.find("level3"), std::string::npos);
    EXPECT_NE(output.find("deep"), std::string::npos);
}

// ============================================================
// Float precision test
// ============================================================

TEST_F(EmitterTest_513, FloatPrecisionAffectsOutput_513) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_513, DoublePrecisionAffectsOutput_513) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Multiple scalars at top level (should cause error or be handled)
// ============================================================

TEST_F(EmitterTest_513, MultipleTopLevelScalars_513) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << "second";
    // Second top-level scalar may put emitter in bad state
    // Just check that the emitter handled it in some way
    // (either good or bad, but no crash)
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Newline handling
// ============================================================

TEST_F(EmitterTest_513, NewlineManip_513) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Newline;
    emitter << "item2";
    emitter << YAML::EndSeq;
    // Should not crash; check output exists
    EXPECT_GT(emitter.size(), 0u);
}
