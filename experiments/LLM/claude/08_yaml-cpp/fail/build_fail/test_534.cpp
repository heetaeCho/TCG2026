#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

class EmitterTest_534 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created Emitter is in good state
TEST_F(EmitterTest_534, DefaultConstructor_IsGood_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

// Test that a newly created Emitter has zero size
TEST_F(EmitterTest_534, DefaultConstructor_SizeIsZero_534) {
    YAML::Emitter emitter;
    EXPECT_EQ(0u, emitter.size());
}

// Test that c_str returns non-null for a new emitter
TEST_F(EmitterTest_534, DefaultConstructor_CStrNotNull_534) {
    YAML::Emitter emitter;
    EXPECT_NE(nullptr, emitter.c_str());
}

// Test that GetLastError returns empty string when good
TEST_F(EmitterTest_534, DefaultConstructor_NoError_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

// Test writing a simple string using Write(const char*, size_t)
TEST_F(EmitterTest_534, WriteCharPtr_SimpleString_534) {
    YAML::Emitter emitter;
    const char* str = "hello";
    emitter.Write(str, 5);
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test writing a simple string using Write(const std::string&)
TEST_F(EmitterTest_534, WriteString_SimpleString_534) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter.Write(str);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("world"), std::string::npos);
}

// Test writing an empty string
TEST_F(EmitterTest_534, WriteCharPtr_EmptyString_534) {
    YAML::Emitter emitter;
    const char* str = "";
    emitter.Write(str, 0);
    EXPECT_TRUE(emitter.good());
}

// Test writing a string with special characters that need quoting
TEST_F(EmitterTest_534, WriteCharPtr_SpecialCharsQuoted_534) {
    YAML::Emitter emitter;
    const char* str = "hello: world";
    emitter.Write(str, 12);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // The output should contain the string, possibly quoted
    EXPECT_NE(output.find("hello: world"), std::string::npos);
}

// Test writing a boolean true
TEST_F(EmitterTest_534, WriteBool_True_534) {
    YAML::Emitter emitter;
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test writing a boolean false
TEST_F(EmitterTest_534, WriteBool_False_534) {
    YAML::Emitter emitter;
    emitter.Write(false);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test writing null
TEST_F(EmitterTest_534, WriteNull_534) {
    YAML::Emitter emitter;
    emitter.Write(YAML::_Null());
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing a char
TEST_F(EmitterTest_534, WriteChar_534) {
    YAML::Emitter emitter;
    emitter.Write('A');
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// Test Write returns a reference to the emitter for chaining
TEST_F(EmitterTest_534, WriteChaining_534) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.Write("hello");
    EXPECT_EQ(&emitter, &ref);
}

// Test Write(const char*, size_t) returns a reference for chaining
TEST_F(EmitterTest_534, WriteCharPtrChaining_534) {
    YAML::Emitter emitter;
    const char* str = "test";
    YAML::Emitter& ref = emitter.Write(str, 4);
    EXPECT_EQ(&emitter, &ref);
}

// Test writing to an ostream
TEST_F(EmitterTest_534, ConstructWithOstream_534) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter.Write("hello");
    EXPECT_TRUE(emitter.good());
    // The output should be written to the stream
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test SetStringFormat
TEST_F(EmitterTest_534, SetStringFormat_DoubleQuoted_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter.Write("hello");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// Test SetStringFormat with SingleQuoted
TEST_F(EmitterTest_534, SetStringFormat_SingleQuoted_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter.Write("hello");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// Test SetBoolFormat with YesNoBool
TEST_F(EmitterTest_534, SetBoolFormat_YesNo_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Should contain "yes" in some form
    EXPECT_TRUE(output.find("yes") != std::string::npos ||
                output.find("Yes") != std::string::npos ||
                output.find("YES") != std::string::npos);
}

// Test SetIndent
TEST_F(EmitterTest_534, SetIndent_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
    EXPECT_TRUE(emitter.good());
}

// Test writing a sequence
TEST_F(EmitterTest_534, WriteSequence_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.Write("item1");
    emitter.Write("item2");
    emitter.SetLocalValue(YAML::EndSeq);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

// Test writing a map
TEST_F(EmitterTest_534, WriteMap_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("name");
    emitter.SetLocalValue(YAML::Value);
    emitter.Write("test");
    emitter.SetLocalValue(YAML::EndMap);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

// Test writing a flow sequence
TEST_F(EmitterTest_534, WriteFlowSequence_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.Write("a");
    emitter.Write("b");
    emitter.SetLocalValue(YAML::EndSeq);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test writing a flow map
TEST_F(EmitterTest_534, WriteFlowMap_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("k");
    emitter.SetLocalValue(YAML::Value);
    emitter.Write("v");
    emitter.SetLocalValue(YAML::EndMap);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test SetOutputCharset
TEST_F(EmitterTest_534, SetOutputCharset_EmitNonAscii_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
    EXPECT_TRUE(emitter.good());
}

// Test SetOutputCharset with EscapeNonAscii
TEST_F(EmitterTest_534, SetOutputCharset_EscapeNonAscii_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
    EXPECT_TRUE(emitter.good());
}

// Test SetNullFormat
TEST_F(EmitterTest_534, SetNullFormat_TildeNull_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
    emitter.Write(YAML::_Null());
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

// Test SetNullFormat with LowerNull
TEST_F(EmitterTest_534, SetNullFormat_LowerNull_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter.Write(YAML::_Null());
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("null"), std::string::npos);
}

// Test SetIntBase with Hex
TEST_F(EmitterTest_534, SetIntBase_Hex_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter.WriteIntegralType(255);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

// Test SetIntBase with Oct
TEST_F(EmitterTest_534, SetIntBase_Oct_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter.WriteIntegralType(8);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test SetFloatPrecision
TEST_F(EmitterTest_534, SetFloatPrecision_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(3));
    EXPECT_TRUE(emitter.good());
}

// Test SetDoublePrecision
TEST_F(EmitterTest_534, SetDoublePrecision_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
    EXPECT_TRUE(emitter.good());
}

// Test SetPreCommentIndent
TEST_F(EmitterTest_534, SetPreCommentIndent_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
    EXPECT_TRUE(emitter.good());
}

// Test SetPostCommentIndent
TEST_F(EmitterTest_534, SetPostCommentIndent_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
    EXPECT_TRUE(emitter.good());
}

// Test writing a comment
TEST_F(EmitterTest_534, WriteComment_534) {
    YAML::Emitter emitter;
    emitter.Write(YAML::_Comment("this is a comment"));
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("#"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test writing an anchor
TEST_F(EmitterTest_534, WriteAnchor_534) {
    YAML::Emitter emitter;
    emitter.Write(YAML::_Anchor("myanchor"));
    emitter.Write("value");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

// Test writing an alias
TEST_F(EmitterTest_534, WriteAlias_534) {
    YAML::Emitter emitter;
    emitter.Write(YAML::_Alias("myanchor"));
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*myanchor"), std::string::npos);
}

// Test writing a tag
TEST_F(EmitterTest_534, WriteTag_534) {
    YAML::Emitter emitter;
    emitter.Write(YAML::_Tag("!mytag"));
    emitter.Write("value");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// Test writing a string with newlines
TEST_F(EmitterTest_534, WriteStringWithNewlines_534) {
    YAML::Emitter emitter;
    const char* str = "line1\nline2\nline3";
    emitter.Write(str, 17);
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing a very long string (> 1024 characters triggers Literal/LongKey)
TEST_F(EmitterTest_534, WriteVeryLongString_534) {
    YAML::Emitter emitter;
    std::string longStr(2000, 'a');
    emitter.Write(longStr.c_str(), longStr.size());
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing a document with BeginDoc/EndDoc
TEST_F(EmitterTest_534, WriteDocument_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginDoc);
    emitter.Write("content");
    emitter.SetLocalValue(YAML::EndDoc);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

// Test nested sequences
TEST_F(EmitterTest_534, NestedSequences_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.Write("inner");
    emitter.SetLocalValue(YAML::EndSeq);
    emitter.SetLocalValue(YAML::EndSeq);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("inner"), std::string::npos);
}

// Test nested maps
TEST_F(EmitterTest_534, NestedMaps_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("outer");
    emitter.SetLocalValue(YAML::Value);
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("inner");
    emitter.SetLocalValue(YAML::Value);
    emitter.Write("val");
    emitter.SetLocalValue(YAML::EndMap);
    emitter.SetLocalValue(YAML::EndMap);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

// Test RestoreGlobalModifiedSettings
TEST_F(EmitterTest_534, RestoreGlobalModifiedSettings_534) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter.RestoreGlobalModifiedSettings();
    emitter.Write("test");
    EXPECT_TRUE(emitter.good());
}

// Test writing integral type (int)
TEST_F(EmitterTest_534, WriteIntegralType_Int_534) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(42);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test writing integral type (negative int)
TEST_F(EmitterTest_534, WriteIntegralType_NegativeInt_534) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(-10);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-10"), std::string::npos);
}

// Test writing streamable type (double)
TEST_F(EmitterTest_534, WriteStreamable_Double_534) {
    YAML::Emitter emitter;
    emitter.WriteStreamable(3.14);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test writing a string with special YAML characters
TEST_F(EmitterTest_534, WriteStringWithColonSpace_534) {
    YAML::Emitter emitter;
    std::string str = "key: value";
    emitter.Write(str);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key: value"), std::string::npos);
}

// Test writing string with hash character
TEST_F(EmitterTest_534, WriteStringWithHash_534) {
    YAML::Emitter emitter;
    std::string str = "has # symbol";
    emitter.Write(str);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("has # symbol"), std::string::npos);
}

// Test writing binary data
TEST_F(EmitterTest_534, WriteBinary_534) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, 4);
    emitter.Write(binary);
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test multiple writes
TEST_F(EmitterTest_534, MultipleScalarWrites_InSequence_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.Write("first");
    emitter.Write("second");
    emitter.Write("third");
    emitter.SetLocalValue(YAML::EndSeq);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("first"), std::string::npos);
    EXPECT_NE(output.find("second"), std::string::npos);
    EXPECT_NE(output.find("third"), std::string::npos);
}

// Test SetLocalValue
TEST_F(EmitterTest_534, SetLocalValue_Returns_EmitterRef_534) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.SetLocalValue(YAML::BeginSeq);
    EXPECT_EQ(&emitter, &ref);
}

// Test writing to string stream and verifying content
TEST_F(EmitterTest_534, OstreamEmitter_FullDocument_534) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("key1");
    emitter.SetLocalValue(YAML::Value);
    emitter.Write("val1");
    emitter.SetLocalValue(YAML::EndMap);
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
}

// Test Literal string format
TEST_F(EmitterTest_534, SetStringFormat_Literal_534) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::Literal);
    const char* str = "line1\nline2\nline3\n";
    emitter.Write(str, strlen(str));
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// Test that SetIndent with small value works
TEST_F(EmitterTest_534, SetIndent_MinValue_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

// Test that SetIndent with larger value works
TEST_F(EmitterTest_534, SetIndent_LargerValue_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(8));
}

// Test writing a map in a sequence
TEST_F(EmitterTest_534, MapInSequence_534) {
    YAML::Emitter emitter;
    emitter.SetLocalValue(YAML::BeginSeq);
    emitter.SetLocalValue(YAML::BeginMap);
    emitter.SetLocalValue(YAML::Key);
    emitter.Write("k");
    emitter.SetLocalValue(YAML::Value);
    emitter.Write("v");
    emitter.SetLocalValue(YAML::EndMap);
    emitter.SetLocalValue(YAML::EndSeq);
    EXPECT_TRUE(emitter.good());
}

// Test that Emitter is non-copyable (compile-time check - just ensure it compiles with single instance)
TEST_F(EmitterTest_534, EmitterIsNonCopyable_534) {
    YAML::Emitter emitter;
    // This test just ensures we can create and use an emitter
    emitter.Write("test");
    EXPECT_TRUE(emitter.good());
}

// Test SetBoolFormat with OnOff
TEST_F(EmitterTest_534, SetBoolFormat_OnOff_534) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_TRUE(output.find("on") != std::string::npos ||
                output.find("On") != std::string::npos ||
                output.find("ON") != std::string::npos);
}

// Test writing a string that looks like a number
TEST_F(EmitterTest_534, WriteStringLooksLikeNumber_534) {
    YAML::Emitter emitter;
    emitter.Write("123");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // Should be quoted or otherwise marked as string
    EXPECT_NE(output.find("123"), std::string::npos);
}
