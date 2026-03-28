#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_525 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test: Default construction results in good state
TEST_F(EmitterTest_525, DefaultConstructionIsGood_525) {
    EXPECT_TRUE(emitter.good());
}

// Test: Default construction produces empty output
TEST_F(EmitterTest_525, DefaultConstructionEmptyOutput_525) {
    EXPECT_EQ(emitter.size(), 0u);
}

// Test: c_str returns non-null for default emitter
TEST_F(EmitterTest_525, DefaultConstructionCStr_525) {
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: GetLastError returns empty string when no error
TEST_F(EmitterTest_525, NoErrorReturnsEmptyLastError_525) {
    EXPECT_TRUE(emitter.GetLastError().empty());
}

// Test: SetPreCommentIndent with a typical value returns true
TEST_F(EmitterTest_525, SetPreCommentIndentTypicalValue_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

// Test: SetPreCommentIndent with zero returns true
TEST_F(EmitterTest_525, SetPreCommentIndentZero_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(0));
}

// Test: SetPreCommentIndent with large value returns true
TEST_F(EmitterTest_525, SetPreCommentIndentLargeValue_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(100));
}

// Test: SetPreCommentIndent with value 1 returns true
TEST_F(EmitterTest_525, SetPreCommentIndentOne_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(1));
}

// Test: SetPreCommentIndent called multiple times
TEST_F(EmitterTest_525, SetPreCommentIndentMultipleCalls_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
    EXPECT_TRUE(emitter.SetPreCommentIndent(4));
    EXPECT_TRUE(emitter.SetPreCommentIndent(1));
}

// Test: Emitter remains good after SetPreCommentIndent
TEST_F(EmitterTest_525, EmitterGoodAfterSetPreCommentIndent_525) {
    emitter.SetPreCommentIndent(3);
    EXPECT_TRUE(emitter.good());
}

// Test: SetPostCommentIndent with a typical value returns true
TEST_F(EmitterTest_525, SetPostCommentIndentTypicalValue_525) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

// Test: SetIndent with a typical value returns true
TEST_F(EmitterTest_525, SetIndentTypicalValue_525) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

// Test: SetIndent with minimum value (should be at least 2 for yaml-cpp)
TEST_F(EmitterTest_525, SetIndentMinimumValue_525) {
    bool result = emitter.SetIndent(2);
    EXPECT_TRUE(result);
}

// Test: Write a simple string scalar
TEST_F(EmitterTest_525, WriteSimpleString_525) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// Test: Write a boolean value
TEST_F(EmitterTest_525, WriteBoolTrue_525) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write a boolean false value
TEST_F(EmitterTest_525, WriteBoolFalse_525) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write null value
TEST_F(EmitterTest_525, WriteNull_525) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write integer value
TEST_F(EmitterTest_525, WriteInteger_525) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test: Write a sequence
TEST_F(EmitterTest_525, WriteSequence_525) {
    emitter << YAML::BeginSeq;
    emitter << "item1" << "item2" << "item3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write a map
TEST_F(EmitterTest_525, WriteMap_525) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write a comment and verify output
TEST_F(EmitterTest_525, WriteComment_525) {
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("#"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test: SetPreCommentIndent affects comment output in a map
TEST_F(EmitterTest_525, SetPreCommentIndentAffectsCommentInMap_525) {
    emitter.SetPreCommentIndent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::Comment("test comment");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("test comment"), std::string::npos);
}

// Test: Construction with ostream
TEST_F(EmitterTest_525, ConstructWithOstream_525) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.good());
    e << "hello";
    EXPECT_TRUE(e.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// Test: SetPreCommentIndent on ostream-based emitter
TEST_F(EmitterTest_525, SetPreCommentIndentWithOstream_525) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    EXPECT_TRUE(e.SetPreCommentIndent(3));
    EXPECT_TRUE(e.good());
}

// Test: SetOutputCharset returns true for valid value
TEST_F(EmitterTest_525, SetOutputCharset_525) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
    EXPECT_TRUE(emitter.good());
}

// Test: SetStringFormat returns true for valid value
TEST_F(EmitterTest_525, SetStringFormat_525) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    EXPECT_TRUE(emitter.good());
}

// Test: SetBoolFormat returns true for valid value
TEST_F(EmitterTest_525, SetBoolFormat_525) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
    EXPECT_TRUE(emitter.good());
}

// Test: SetNullFormat returns true for valid value
TEST_F(EmitterTest_525, SetNullFormat_525) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    EXPECT_TRUE(emitter.good());
}

// Test: SetIntBase returns true for valid value
TEST_F(EmitterTest_525, SetIntBase_525) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    EXPECT_TRUE(emitter.good());
}

// Test: SetSeqFormat returns true for valid value
TEST_F(EmitterTest_525, SetSeqFormat_525) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    EXPECT_TRUE(emitter.good());
}

// Test: SetMapFormat returns true for valid value
TEST_F(EmitterTest_525, SetMapFormat_525) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    EXPECT_TRUE(emitter.good());
}

// Test: SetFloatPrecision returns true
TEST_F(EmitterTest_525, SetFloatPrecision_525) {
    EXPECT_TRUE(emitter.SetFloatPrecision(5));
    EXPECT_TRUE(emitter.good());
}

// Test: SetDoublePrecision returns true
TEST_F(EmitterTest_525, SetDoublePrecision_525) {
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
    EXPECT_TRUE(emitter.good());
}

// Test: Write float value
TEST_F(EmitterTest_525, WriteFloat_525) {
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write double value
TEST_F(EmitterTest_525, WriteDouble_525) {
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Write anchor and alias
TEST_F(EmitterTest_525, WriteAnchorAndAlias_525) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anchor1") << "value";
    emitter << YAML::Alias("anchor1");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

// Test: Write tag
TEST_F(EmitterTest_525, WriteTag_525) {
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test: Write char
TEST_F(EmitterTest_525, WriteChar_525) {
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// Test: Nested sequences
TEST_F(EmitterTest_525, NestedSequences_525) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2;
    emitter << YAML::EndSeq;
    emitter << YAML::BeginSeq;
    emitter << 3 << 4;
    emitter << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test: Nested maps
TEST_F(EmitterTest_525, NestedMaps_525) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "inner" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test: Flow sequence format
TEST_F(EmitterTest_525, FlowSequence_525) {
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test: Flow map format
TEST_F(EmitterTest_525, FlowMap_525) {
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: RestoreGlobalModifiedSettings
TEST_F(EmitterTest_525, RestoreGlobalModifiedSettings_525) {
    emitter.SetPreCommentIndent(5);
    emitter.SetPostCommentIndent(3);
    emitter.SetIndent(6);
    emitter.RestoreGlobalModifiedSettings();
    EXPECT_TRUE(emitter.good());
}

// Test: SetPreCommentIndent with max size_t value
TEST_F(EmitterTest_525, SetPreCommentIndentMaxValue_525) {
    // Testing boundary - very large value
    bool result = emitter.SetPreCommentIndent(static_cast<std::size_t>(-1));
    // We don't assert the return value as we don't know the internal limits
    // but the emitter should still be in some defined state
    (void)result;
}

// Test: Write binary data
TEST_F(EmitterTest_525, WriteBinary_525) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0xFF};
    YAML::Binary binary(data.data(), data.size());
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: Multiple documents are not typical but write multiple scalars causes error
TEST_F(EmitterTest_525, WriteTwoScalarsIsInvalid_525) {
    emitter << "first";
    emitter << "second";
    // Writing two top-level scalars without proper doc handling might cause error
    // We observe the behavior through good()
    // Not asserting specific behavior since it's black box
}

// Test: SetLocalIndent
TEST_F(EmitterTest_525, SetLocalIndent_525) {
    emitter << YAML::BeginSeq;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq;
    emitter << 1 << 2;
    emitter << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test: Comment with SetPreCommentIndent = 0
TEST_F(EmitterTest_525, CommentWithZeroPreCommentIndent_525) {
    emitter.SetPreCommentIndent(0);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::Comment("comment");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("comment"), std::string::npos);
}

// Test: Emitter output through ostream matches c_str
TEST_F(EmitterTest_525, OstreamMatchesCStr_525) {
    std::stringstream ss;
    YAML::Emitter e(ss);
    e << "test_value";
    EXPECT_TRUE(e.good());
    // The ostream should have the same content
    EXPECT_EQ(ss.str(), std::string(e.c_str()));
}

// Test: Write with const char* and size
TEST_F(EmitterTest_525, WriteWithSizeParameter_525) {
    const char* text = "hello world";
    emitter.Write(text, 5);  // Should write "hello"
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test: size() after writing
TEST_F(EmitterTest_525, SizeAfterWriting_525) {
    EXPECT_EQ(emitter.size(), 0u);
    emitter << "hello";
    EXPECT_GT(emitter.size(), 0u);
}
