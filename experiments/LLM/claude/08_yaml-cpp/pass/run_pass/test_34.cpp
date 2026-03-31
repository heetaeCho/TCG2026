#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>
#include <cstdint>
#include <limits>

class EmitterTest_34 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_34, DefaultConstructor_GoodState_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_34, DefaultConstructor_EmptyOutput_34) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_34, DefaultConstructor_CStrNotNull_34) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_34, StreamConstructor_GoodState_34) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_34, DefaultConstructor_NoError_34) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// ==================== WriteIntegralType Tests ====================

TEST_F(EmitterTest_34, WriteIntegralType_Int_34) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(42);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_NegativeInt_34) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(-100);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-100"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_Zero_34) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(0);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_LargeInt_34) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(std::numeric_limits<int>::max());
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find(std::to_string(std::numeric_limits<int>::max())), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_MinInt_34) {
    YAML::Emitter emitter;
    emitter.WriteIntegralType(std::numeric_limits<int>::min());
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find(std::to_string(std::numeric_limits<int>::min())), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_Int64_34) {
    YAML::Emitter emitter;
    int64_t val = 9223372036854775807LL;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_UnsignedInt_34) {
    YAML::Emitter emitter;
    unsigned int val = 4294967295u;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("4294967295"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_Short_34) {
    YAML::Emitter emitter;
    short val = 32767;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("32767"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_UInt64_34) {
    YAML::Emitter emitter;
    uint64_t val = 18446744073709551615ULL;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("18446744073709551615"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_ToStream_34) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter.WriteIntegralType(123);
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("123"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_ReturnsSelf_34) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.WriteIntegralType(42);
    EXPECT_EQ(&ref, &emitter);
}

// ==================== WriteIntegralType with Hex Base ====================

TEST_F(EmitterTest_34, WriteIntegralType_HexBase_34) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter.WriteIntegralType(255);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Hex output should contain "0x" prefix
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_OctBase_34) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter.WriteIntegralType(8);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Oct output should contain "0" prefix
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Write String Tests ====================

TEST_F(EmitterTest_34, WriteString_Simple_34) {
    YAML::Emitter emitter;
    emitter.Write(std::string("hello"));
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteString_Empty_34) {
    YAML::Emitter emitter;
    emitter.Write(std::string(""));
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_34, WriteCStr_34) {
    YAML::Emitter emitter;
    const char* str = "world";
    emitter.Write(str, 5);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

// ==================== Write Bool Tests ====================

TEST_F(EmitterTest_34, WriteBool_True_34) {
    YAML::Emitter emitter;
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_34, WriteBool_False_34) {
    YAML::Emitter emitter;
    emitter.Write(false);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_34, WriteBool_TrueLongFormat_34) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteBool_FalseLongFormat_34) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter.Write(false);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteBool_YesNoBool_34) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter.Write(true);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("yes"), std::string::npos);
}

// ==================== Write Char Tests ====================

TEST_F(EmitterTest_34, WriteChar_34) {
    YAML::Emitter emitter;
    emitter.Write('A');
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Write Null Tests ====================

TEST_F(EmitterTest_34, WriteNull_Default_34) {
    YAML::Emitter emitter;
    emitter.Write(YAML::Null);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_34, WriteNull_Tilde_34) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::TildeNull);
    emitter.Write(YAML::Null);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Write Alias/Anchor/Tag/Comment ====================

TEST_F(EmitterTest_34, WriteAnchor_34) {
    YAML::Emitter emitter;
    emitter.Write(YAML::Anchor("myanchor"));
    emitter.Write(std::string("value"));
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("myanchor"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteAlias_34) {
    YAML::Emitter emitter;
    emitter.Write(YAML::Anchor("myanchor"));
    emitter.Write(std::string("value"));
    // Now in a different context we'd use alias
    // Just test that alias write doesn't crash and emitter might still be good
    // depending on context
}

TEST_F(EmitterTest_34, WriteTag_34) {
    YAML::Emitter emitter;
    emitter.Write(YAML::LocalTag("mytag"));
    emitter.Write(std::string("value"));
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("mytag"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteComment_34) {
    YAML::Emitter emitter;
    emitter.Write(YAML::Comment("this is a comment"));
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// ==================== Sequence and Map Tests ====================

TEST_F(EmitterTest_34, BeginEndSeq_34) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 1;
    emitter << 2;
    emitter << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(EmitterTest_34, BeginEndMap_34) {
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

TEST_F(EmitterTest_34, FlowSeq_34) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_34, FlowMap_34) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// ==================== SetIntBase Tests ====================

TEST_F(EmitterTest_34, SetIntBase_Dec_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_34, SetIntBase_Hex_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_34, SetIntBase_Oct_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// ==================== SetStringFormat Tests ====================

TEST_F(EmitterTest_34, SetStringFormat_SingleQuoted_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_34, SetStringFormat_DoubleQuoted_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_34, SetStringFormat_Literal_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

// ==================== SetBoolFormat Tests ====================

TEST_F(EmitterTest_34, SetBoolFormat_TrueFalse_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_34, SetBoolFormat_YesNo_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_34, SetBoolFormat_UpperCase_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

// ==================== SetIndent Tests ====================

TEST_F(EmitterTest_34, SetIndent_Valid_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_34, SetIndent_MinValid_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

// ==================== SetSeqFormat Tests ====================

TEST_F(EmitterTest_34, SetSeqFormat_Block_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_34, SetSeqFormat_Flow_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

// ==================== SetMapFormat Tests ====================

TEST_F(EmitterTest_34, SetMapFormat_Block_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_34, SetMapFormat_Flow_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// ==================== Precision Tests ====================

TEST_F(EmitterTest_34, SetFloatPrecision_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_34, SetDoublePrecision_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Complex Scenarios ====================

TEST_F(EmitterTest_34, NestedSequences_34) {
    YAML::Emitter emitter;
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

TEST_F(EmitterTest_34, NestedMaps_34) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer";
    emitter << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "inner" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(EmitterTest_34, MapWithSequenceValue_34) {
    YAML::Emitter emitter;
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

// ==================== Stream Constructor Output ====================

TEST_F(EmitterTest_34, StreamConstructor_OutputToStream_34) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

// ==================== Binary Tests ====================

TEST_F(EmitterTest_34, WriteBinary_34) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data = {0x00, 0x01, 0x02, 0xFF};
    emitter.Write(YAML::Binary(data.data(), data.size()));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== WriteIntegralType with different types ====================

TEST_F(EmitterTest_34, WriteIntegralType_Long_34) {
    YAML::Emitter emitter;
    long val = 123456789L;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("123456789"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_UnsignedShort_34) {
    YAML::Emitter emitter;
    unsigned short val = 65535;
    emitter.WriteIntegralType(val);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("65535"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_34, RestoreGlobalModifiedSettings_34) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, emitter should still be good
    EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_34, SetLocalValue_Flow_34) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter.SetLocalValue(YAML::Flow);
    emitter << YAML::BeginSeq;
    emitter << 1 << 2;
    emitter << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Multiple Scalars at Top Level ====================

TEST_F(EmitterTest_34, WriteMultipleDocuments_34) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "first";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "second";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("first"), std::string::npos);
    EXPECT_NE(output.find("second"), std::string::npos);
}

// ==================== Size reflects output ====================

TEST_F(EmitterTest_34, SizeIncreasesAfterWrite_34) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "hello";
    EXPECT_GT(emitter.size(), initialSize);
}

// ==================== Hex output format verification ====================

TEST_F(EmitterTest_34, WriteIntegralType_HexFormat_Verification_34) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter.WriteIntegralType(16);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x10"), std::string::npos);
}

TEST_F(EmitterTest_34, WriteIntegralType_OctFormat_Verification_34) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter.WriteIntegralType(8);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("010"), std::string::npos);
}

// ==================== Comment indent ====================

TEST_F(EmitterTest_34, SetPreCommentIndent_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_34, SetPostCommentIndent_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== Operator<< with integral types ====================

TEST_F(EmitterTest_34, OperatorShift_Int_34) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_34, OperatorShift_Double_34) {
    YAML::Emitter emitter;
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_34, OperatorShift_Float_34) {
    YAML::Emitter emitter;
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2.5"), std::string::npos);
}

// ==================== String format tests ====================

TEST_F(EmitterTest_34, SingleQuotedString_34) {
    YAML::Emitter emitter;
    emitter << YAML::SingleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_34, DoubleQuotedString_34) {
    YAML::Emitter emitter;
    emitter << YAML::DoubleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== Literal block scalar ====================

TEST_F(EmitterTest_34, LiteralString_34) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_34, AnchorAndAlias_34) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("val") << "hello";
    emitter << YAML::Alias("val");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&val"), std::string::npos);
    EXPECT_NE(output.find("*val"), std::string::npos);
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_34, SetNullFormat_LowerNull_34) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter.Write(YAML::Null);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

// ==================== Empty sequence and map ====================

TEST_F(EmitterTest_34, EmptyFlowSeq_34) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("[]"), std::string::npos);
}

TEST_F(EmitterTest_34, EmptyFlowMap_34) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{}"), std::string::npos);
}
