#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_535 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(EmitterTest_535, DefaultConstructor_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, StreamConstructor_535) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

// ==================== Basic Write Tests ====================

TEST_F(EmitterTest_535, WriteString_535) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteStdString_535) {
    YAML::Emitter emitter;
    std::string value = "test_string";
    emitter << value;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("test_string"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteEmptyString_535) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, WriteBoolTrue_535) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteBoolFalse_535) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteChar_535) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteInteger_535) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteNegativeInteger_535) {
    YAML::Emitter emitter;
    emitter << -100;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-100"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteDouble_535) {
    YAML::Emitter emitter;
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteFloat_535) {
    YAML::Emitter emitter;
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteNull_535) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequence Tests ====================

TEST_F(EmitterTest_535, WriteBlockSequence_535) {
    YAML::Emitter emitter;
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

TEST_F(EmitterTest_535, WriteFlowSequence_535) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteEmptySequence_535) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Map Tests ====================

TEST_F(EmitterTest_535, WriteBlockMap_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteFlowMap_535) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteEmptyMap_535) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_535, WriteNestedMapInSequence_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, WriteNestedSequenceInMap_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "list";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== c_str and size Tests ====================

TEST_F(EmitterTest_535, CStrReturnsNonNull_535) {
    YAML::Emitter emitter;
    emitter << "data";
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_535, SizeMatchesCStr_535) {
    YAML::Emitter emitter;
    emitter << "hello";
    std::string output = emitter.c_str();
    EXPECT_EQ(emitter.size(), output.size());
}

TEST_F(EmitterTest_535, SizeIsZeroInitially_535) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

// ==================== Stream Output Tests ====================

TEST_F(EmitterTest_535, OutputToStream_535) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    // The stream should contain the output
    std::string result = ss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// ==================== Good / Error State Tests ====================

TEST_F(EmitterTest_535, GoodInitially_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, GetLastErrorEmptyWhenGood_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    // When good, last error should be empty or indicate no error
    std::string err = emitter.GetLastError();
    // We just check it doesn't crash; exact value depends on implementation
}

// ==================== Setting Format Tests ====================

TEST_F(EmitterTest_535, SetStringFormatSingleQuoted_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_535, SetStringFormatDoubleQuoted_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_535, SetBoolFormatTrueFalseCase_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_535, SetBoolFormatYesNo_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain "yes" or "Yes" or "YES"
}

TEST_F(EmitterTest_535, SetBoolFormatUpperCase_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
    emitter << true;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, SetNullFormat_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_535, SetIntBaseHex_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_535, SetIntBaseOct_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_535, SetSeqFormatBlock_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_535, SetSeqFormatFlow_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_535, SetMapFormatBlock_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_535, SetMapFormatFlow_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// ==================== Indent Tests ====================

TEST_F(EmitterTest_535, SetIndent_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_535, SetIndentMinimum_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_535, SetPreCommentIndent_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_535, SetPostCommentIndent_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== Precision Tests ====================

TEST_F(EmitterTest_535, SetFloatPrecision_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_535, SetDoublePrecision_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Anchor and Alias Tests ====================

TEST_F(EmitterTest_535, WriteAnchor_535) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteAlias_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::Alias("anc");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Tag Tests ====================

TEST_F(EmitterTest_535, WriteTag_535) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Comment Tests ====================

TEST_F(EmitterTest_535, WriteComment_535) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Binary Tests ====================

TEST_F(EmitterTest_535, WriteBinary_535) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data.data(), data.size());
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteBinaryEmpty_535) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data;
    emitter << YAML::Binary(data.data(), 0);
    EXPECT_TRUE(emitter.good());
}

// ==================== Local Value / Manipulator Tests ====================

TEST_F(EmitterTest_535, SetLocalValueFlow_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, SetLocalIndent_535) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, SetLocalPrecisionFloat_535) {
    YAML::Emitter emitter;
    emitter << YAML::FloatPrecision(3);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_535, SetLocalPrecisionDouble_535) {
    YAML::Emitter emitter;
    emitter << YAML::DoublePrecision(5);
    emitter << 3.141592653589793;
    EXPECT_TRUE(emitter.good());
}

// ==================== Document Tests ====================

TEST_F(EmitterTest_535, BeginAndEndDoc_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "content";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_535, MultipleDocuments_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

// ==================== Newline Tests ====================

TEST_F(EmitterTest_535, WriteNewline_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Newline;
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Chaining Tests ====================

TEST_F(EmitterTest_535, ChainingWrites_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap
            << YAML::Key << "key1" << YAML::Value << "val1"
            << YAML::Key << "key2" << YAML::Value << 42
            << YAML::Key << "key3" << YAML::Value << true
            << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
    EXPECT_NE(output.find("key2"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings Tests ====================

TEST_F(EmitterTest_535, RestoreGlobalModifiedSettings_535) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, the emitter should still be in a good state
    emitter << "test";
    EXPECT_TRUE(emitter.good());
}

// ==================== Complex Structure Tests ====================

TEST_F(EmitterTest_535, ComplexNestedStructure_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "database";
    emitter << YAML::Value;
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
}

// ==================== Long Key Map Tests ====================

TEST_F(EmitterTest_535, LongKeyMap_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "a_very_long_key";
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Large Data Tests ====================

TEST_F(EmitterTest_535, WriteLargeSequence_535) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 100; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteLongString_535) {
    YAML::Emitter emitter;
    std::string longStr(10000, 'x');
    emitter << longStr;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Literal and Folded Strings ====================

TEST_F(EmitterTest_535, WriteLiteralString_535) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Special Characters in Strings ====================

TEST_F(EmitterTest_535, WriteStringWithSpecialChars_535) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    // String with colon should be quoted or escaped
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_535, WriteStringWithNewline_535) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetOutputCharset Tests ====================

TEST_F(EmitterTest_535, SetOutputCharsetUTF8_535) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Multiple Scalars at Top Level ====================

TEST_F(EmitterTest_535, WriteZeroInteger_535) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteLargeInteger_535) {
    YAML::Emitter emitter;
    emitter << 2147483647;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2147483647"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteUnsignedInteger_535) {
    YAML::Emitter emitter;
    emitter << static_cast<unsigned int>(42);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_535, WriteLongLong_535) {
    YAML::Emitter emitter;
    emitter << static_cast<long long>(9876543210LL);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("9876543210"), std::string::npos);
}
