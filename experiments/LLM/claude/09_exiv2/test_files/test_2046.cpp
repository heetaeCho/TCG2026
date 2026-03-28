#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "WXMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SerializeToBuffer_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr * rdfString,
    XMP_StringLen * rdfSize,
    XMP_OptionBits options,
    XMP_StringLen padding,
    XMP_StringPtr newline,
    XMP_StringPtr indent,
    XMP_Index baseIndent,
    WXMP_Result * wResult);

class WXMPMetaSerializeTest_2046 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Basic serialization of empty metadata produces valid output
TEST_F(WXMPMetaSerializeTest_2046, BasicSerializeEmptyMeta_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error";
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Null rdfString pointer is handled gracefully (uses voidStringPtr internally)
TEST_F(WXMPMetaSerializeTest_2046, NullRdfStringPointer_2046) {
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), nullptr, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error with null rdfString";
    // rdfSize should still be populated
    EXPECT_GT(rdfSize, 0u);
}

// Test: Null rdfSize pointer is handled gracefully (uses voidStringLen internally)
TEST_F(WXMPMetaSerializeTest_2046, NullRdfSizePointer_2046) {
    XMP_StringPtr rdfString = nullptr;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, nullptr, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error with null rdfSize";
    EXPECT_NE(rdfString, nullptr);
}

// Test: Both rdfString and rdfSize null
TEST_F(WXMPMetaSerializeTest_2046, BothOutputPointersNull_2046) {
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), nullptr, nullptr, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error with both null outputs";
}

// Test: Null newline defaults to empty string
TEST_F(WXMPMetaSerializeTest_2046, NullNewlineDefaultsToEmpty_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, nullptr, " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Null indent defaults to empty string
TEST_F(WXMPMetaSerializeTest_2046, NullIndentDefaultsToEmpty_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", nullptr, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Both newline and indent null
TEST_F(WXMPMetaSerializeTest_2046, BothNewlineAndIndentNull_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, nullptr, nullptr, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Serialization with padding
TEST_F(WXMPMetaSerializeTest_2046, SerializeWithPadding_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 2048, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GE(rdfSize, 2048u);
}

// Test: Serialization with custom newline and indent
TEST_F(WXMPMetaSerializeTest_2046, SerializeWithCustomNewlineAndIndent_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\r\n", "\t", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Serialization with non-zero baseIndent
TEST_F(WXMPMetaSerializeTest_2046, SerializeWithBaseIndent_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 3, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);
}

// Test: Serialization of metadata with a property set
TEST_F(WXMPMetaSerializeTest_2046, SerializeWithProperty_2046) {
    meta->SetProperty("http://purl.org/dc/elements/1.1/", "title", "Test Title", 0);

    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    EXPECT_GT(rdfSize, 0u);

    // The serialized output should contain the property value
    std::string output(rdfString, rdfSize);
    EXPECT_NE(output.find("Test Title"), std::string::npos);
}

// Test: rdfSize matches the string length
TEST_F(WXMPMetaSerializeTest_2046, RdfSizeMatchesStringLength_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(rdfString, nullptr);
    // The rdfSize should correspond to the actual content length
    EXPECT_EQ(rdfSize, std::strlen(rdfString));
}

// Test: WXMP_Result is initialized properly on success
TEST_F(WXMPMetaSerializeTest_2046, ResultInitializedOnSuccess_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: All null optional parameters simultaneously
TEST_F(WXMPMetaSerializeTest_2046, AllOptionalParamsNull_2046) {
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), nullptr, nullptr, 0, 0, nullptr, nullptr, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Serialization produces valid XML-like content
TEST_F(WXMPMetaSerializeTest_2046, OutputContainsXMPPacket_2046) {
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;
    WXMP_Result wResult;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString, &rdfSize, 0, 0, "\n", " ", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rdfString, nullptr);

    std::string output(rdfString, rdfSize);
    // XMP serialization should contain the xpacket processing instruction
    EXPECT_NE(output.find("xpacket"), std::string::npos);
}

// Test: Zero padding produces minimal output
TEST_F(WXMPMetaSerializeTest_2046, ZeroPaddingMinimalOutput_2046) {
    XMP_StringPtr rdfString1 = nullptr;
    XMP_StringLen rdfSize1 = 0;
    XMP_StringPtr rdfString2 = nullptr;
    XMP_StringLen rdfSize2 = 0;
    WXMP_Result wResult1, wResult2;

    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString1, &rdfSize1, 0, 0, "\n", " ", 0, &wResult1);
    WXMPMeta_SerializeToBuffer_1(
        GetRef(), &rdfString2, &rdfSize2, 0, 4096, "\n", " ", 0, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    // With more padding, output should be at least as large
    EXPECT_LE(rdfSize1, rdfSize2);
}
