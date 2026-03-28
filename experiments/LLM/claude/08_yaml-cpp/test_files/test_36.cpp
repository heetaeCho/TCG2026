#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <string_view>
#include "yaml-cpp/yaml.h"

class EmitterTest_36 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Basic Construction and Initial State ===

TEST_F(EmitterTest_36, DefaultConstructor_GoodState_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, DefaultConstructor_EmptyOutput_36) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_36, DefaultConstructor_CStrNotNull_36) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_36, StreamConstructor_GoodState_36) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, DefaultConstructor_NoError_36) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// === Writing Strings ===

TEST_F(EmitterTest_36, WriteString_SimpleString_36) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteString_StdString_36) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_36, WriteStringView_36) {
    YAML::Emitter emitter;
    std::string_view sv = "test_view";
    emitter << sv;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("test_view"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteEmptyString_36) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// === Writing Booleans ===

TEST_F(EmitterTest_36, WriteBoolTrue_36) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_36, WriteBoolFalse_36) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// === Writing Integers ===

TEST_F(EmitterTest_36, WriteInt_36) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteNegativeInt_36) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-10"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteZero_36) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

// === Writing Floating Point ===

TEST_F(EmitterTest_36, WriteFloat_36) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteDouble_36) {
    YAML::Emitter emitter;
    emitter << 2.718281828;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

// === Writing Char ===

TEST_F(EmitterTest_36, WriteChar_36) {
    YAML::Emitter emitter;
    emitter << 'a';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("a"), std::string::npos);
}

// === Writing Null ===

TEST_F(EmitterTest_36, WriteNull_36) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// === Sequences ===

TEST_F(EmitterTest_36, WriteBlockSequence_36) {
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

TEST_F(EmitterTest_36, WriteFlowSequence_36) {
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

TEST_F(EmitterTest_36, WriteEmptySequence_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Maps ===

TEST_F(EmitterTest_36, WriteBlockMap_36) {
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

TEST_F(EmitterTest_36, WriteFlowMap_36) {
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

TEST_F(EmitterTest_36, WriteEmptyMap_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === Nested Structures ===

TEST_F(EmitterTest_36, WriteNestedMapInSeq_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, WriteNestedSeqInMap_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === Comments ===

TEST_F(EmitterTest_36, WriteComment_36) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// === Anchors and Aliases ===

TEST_F(EmitterTest_36, WriteAnchor_36) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_36, WriteAlias_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("ref") << "value";
    emitter << YAML::Alias("ref");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*ref"), std::string::npos);
}

// === Tags ===

TEST_F(EmitterTest_36, WriteTag_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Tag("!mytag") << "value";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// === Stream-based output ===

TEST_F(EmitterTest_36, StreamOutput_36) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    // The stream should contain the output
    std::string streamContent = ss.str();
    EXPECT_NE(streamContent.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_36, StreamOutputMap_36) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string streamContent = ss.str();
    EXPECT_NE(streamContent.find("key"), std::string::npos);
    EXPECT_NE(streamContent.find("val"), std::string::npos);
}

// === Settings ===

TEST_F(EmitterTest_36, SetBoolFormat_TrueFalse_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_36, SetBoolFormat_YesNo_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_36, SetBoolFormat_UpperCase_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_36, SetNullFormat_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_36, SetSeqFormat_Flow_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_36, SetSeqFormat_Block_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("-"), std::string::npos);
}

TEST_F(EmitterTest_36, SetMapFormat_Flow_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    emitter << YAML::BeginMap << YAML::Key << "k" << YAML::Value << "v" << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_36, SetMapFormat_Block_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
    emitter << YAML::BeginMap << YAML::Key << "k" << YAML::Value << "v" << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, SetIndent_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, SetIndent_TooSmall_36) {
    YAML::Emitter emitter;
    // Indent of 1 might be rejected (minimum is typically 2)
    bool result = emitter.SetIndent(1);
    // We just observe the return value
    (void)result;
}

TEST_F(EmitterTest_36, SetIntBase_Hex_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_36, SetIntBase_Oct_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_36, SetFloatPrecision_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(2));
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, SetDoublePrecision_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(4));
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, SetPreCommentIndent_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(3));
}

TEST_F(EmitterTest_36, SetPostCommentIndent_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

TEST_F(EmitterTest_36, SetStringFormat_SingleQuoted_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_36, SetStringFormat_DoubleQuoted_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// === Local Value Overrides ===

TEST_F(EmitterTest_36, SetLocalValue_Flow_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Binary ===

TEST_F(EmitterTest_36, WriteBinary_36) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, sizeof(data));
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_36, WriteBinaryEmpty_36) {
    YAML::Emitter emitter;
    YAML::Binary binary(nullptr, 0);
    emitter << binary;
    EXPECT_TRUE(emitter.good());
}

// === Document separators ===

TEST_F(EmitterTest_36, BeginDoc_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "hello";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_36, MultipleDocuments_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

// === Newline ===

TEST_F(EmitterTest_36, WriteNewline_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Newline;
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Complex structures ===

TEST_F(EmitterTest_36, ComplexNestedStructure_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "database";
    emitter << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "host" << YAML::Value << "localhost";
    emitter << YAML::Key << "port" << YAML::Value << 5432;
    emitter << YAML::Key << "tags";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << "production" << "primary";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("database"), std::string::npos);
    EXPECT_NE(output.find("localhost"), std::string::npos);
    EXPECT_NE(output.find("5432"), std::string::npos);
    EXPECT_NE(output.find("production"), std::string::npos);
}

// === Size tracking ===

TEST_F(EmitterTest_36, SizeIncreasesWithContent_36) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "some content";
    EXPECT_GT(emitter.size(), initialSize);
}

TEST_F(EmitterTest_36, SizeMatchesCStr_36) {
    YAML::Emitter emitter;
    emitter << "test";
    std::string output(emitter.c_str());
    EXPECT_EQ(emitter.size(), output.size());
}

// === RestoreGlobalModifiedSettings ===

TEST_F(EmitterTest_36, RestoreGlobalModifiedSettings_36) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

// === SetOutputCharset ===

TEST_F(EmitterTest_36, SetOutputCharset_UTF8_36) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === Long key in map ===

TEST_F(EmitterTest_36, LongKeyInMap_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "this is a long key";
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("this is a long key"), std::string::npos);
}

// === Multiple scalars at top level ===

TEST_F(EmitterTest_36, MultipleTopLevelScalars_AsDocuments_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "first" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "second" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

// === Literal and folded block scalars ===

TEST_F(EmitterTest_36, LiteralBlockScalar_36) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// === Verify operator<< with string_view returns reference ===

TEST_F(EmitterTest_36, StringViewOperatorReturnsEmitterRef_36) {
    YAML::Emitter emitter;
    std::string_view sv = "chained";
    YAML::Emitter& ref = (emitter << sv);
    EXPECT_EQ(&ref, &emitter);
}

// === Verify Write returns reference ===

TEST_F(EmitterTest_36, WriteReturnsEmitterRef_36) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.Write("test");
    EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_36, WriteBoolReturnsEmitterRef_36) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.Write(true);
    EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_36, WriteCharReturnsEmitterRef_36) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.Write('x');
    EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_36, WriteNullReturnsEmitterRef_36) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.Write(YAML::Null);
    EXPECT_EQ(&ref, &emitter);
}

// === Boundary: Large sequence ===

TEST_F(EmitterTest_36, LargeSequence_36) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 1000; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// === Boundary: Deeply nested structure ===

TEST_F(EmitterTest_36, DeeplyNestedSequence_36) {
    YAML::Emitter emitter;
    const int depth = 10;
    for (int i = 0; i < depth; ++i) {
        emitter << YAML::BeginSeq;
    }
    emitter << "deep_value";
    for (int i = 0; i < depth; ++i) {
        emitter << YAML::EndSeq;
    }
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("deep_value"), std::string::npos);
}

// === Special characters in strings ===

TEST_F(EmitterTest_36, StringWithSpecialChars_36) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    // String containing ':' should be properly quoted or escaped
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_36, StringWithNewlines_36) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
}

// === SetLocalIndent ===

TEST_F(EmitterTest_36, SetLocalIndent_36) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Int types ===

TEST_F(EmitterTest_36, WriteLongInt_36) {
    YAML::Emitter emitter;
    emitter << static_cast<long long>(9223372036854775807LL);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_36, WriteUnsignedInt_36) {
    YAML::Emitter emitter;
    emitter << static_cast<unsigned int>(4294967295u);
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("4294967295"), std::string::npos);
}
