#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_ParseFromBuffer_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr buffer,
    XMP_StringLen bufferSize,
    XMP_OptionBits options,
    WXMP_Result * wResult
);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaParseFromBufferTest_2045 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
};

// Valid minimal XMP packet
static const char* kValidXMP =
    "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
    "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
    "<rdf:Description rdf:about=\"\""
    " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
    "<dc:title>"
    "<rdf:Alt><rdf:li xml:lang=\"x-default\">Test Title</rdf:li></rdf:Alt>"
    "</dc:title>"
    "</rdf:Description>"
    "</rdf:RDF>"
    "</x:xmpmeta>"
    "<?xpacket end=\"w\"?>";

// Test: Parse a valid XMP buffer successfully
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseValidXMP_2045) {
    WXMP_Result wResult;
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, bufferSize, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error for valid XMP";

    // Verify the property was actually parsed
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty("http://purl.org/dc/elements/1.1/", "title", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found);
}

// Test: Parse empty buffer with zero size
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseEmptyBuffer_2045) {
    WXMP_Result wResult;

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), "", 0, 0, &wResult);

    // An empty buffer parse should not crash; it might or might not set an error
    // depending on whether kXMP_RequireXMPMeta is set
    // Just verify it doesn't crash - the result state is implementation-dependent
}

// Test: Parse null buffer with zero size
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseNullBufferZeroSize_2045) {
    WXMP_Result wResult;

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), nullptr, 0, 0, &wResult);

    // Should handle null buffer with zero size gracefully
}

// Test: Parse invalid/malformed XML
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseInvalidXML_2045) {
    WXMP_Result wResult;
    const char* invalidXML = "<this is not valid xml at all &&&";
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(invalidXML));

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), invalidXML, bufferSize, 0, &wResult);

    // With malformed XML, we expect an error message to be set
    // (depending on the options; without kXMP_RequireXMPMeta it might be lenient)
}

// Test: Parse valid XMP and verify a specific property value can be retrieved
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseAndRetrieveProperty_2045) {
    WXMP_Result wResult;
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, bufferSize, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // The dc:title is an alt-text array, check via GetLocalizedText
    XMP_StringPtr actualLang = nullptr;
    XMP_StringLen langSize = 0;
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetLocalizedText(
        "http://purl.org/dc/elements/1.1/", "title",
        "x-default", "x-default",
        &actualLang, &langSize, &itemValue, &valueSize, &opts
    );
    EXPECT_TRUE(found);
    if (found && itemValue) {
        EXPECT_STREQ(itemValue, "Test Title");
    }
}

// Test: Parse with kXMP_RequireXMPMeta option on non-XMP content
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseWithRequireXMPMetaOption_2045) {
    WXMP_Result wResult;
    const char* plainXML = "<root><child>value</child></root>";
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(plainXML));

    // kXMP_RequireXMPMeta = 0x0001UL typically
    XMP_OptionBits options = 0x0001UL;

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), plainXML, bufferSize, options, &wResult);

    // With RequireXMPMeta, plain XML without xmpmeta wrapper should result in
    // no properties being found (or possibly an error)
}

// Test: Parse partial buffer size (less than actual content)
TEST_F(WXMPMetaParseFromBufferTest_2045, ParsePartialBufferSize_2045) {
    WXMP_Result wResult;
    // Only pass part of the valid XMP
    XMP_StringLen partialSize = 50;

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, partialSize, 0, &wResult);

    // Parsing an incomplete XMP packet - behavior depends on implementation
    // Just verifying it doesn't crash
}

// Test: Parse with null xmpRef should produce an error
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseWithNullXmpRef_2045) {
    WXMP_Result wResult;
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));

    WXMPMeta_ParseFromBuffer_1(nullptr, kValidXMP, bufferSize, 0, &wResult);

    // A null xmpRef should result in an error
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Parse replaces previous content
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseReplacesExistingContent_2045) {
    WXMP_Result wResult;

    // First, set a property directly
    meta->SetProperty("http://purl.org/dc/elements/1.1/", "creator", "OriginalCreator", 0);

    // Now parse new XMP that has dc:title but not dc:creator
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));
    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, bufferSize, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    // After parsing, the old dc:creator might be gone (replaced by parsed content)
    // and dc:title should exist
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty("http://purl.org/dc/elements/1.1/", "title", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found);
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaParseFromBufferTest_2045, ResultInitialization_2045) {
    WXMP_Result wResult;

    // Verify the WXMP_Result constructor initializes errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));
    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, bufferSize, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Parse XMP with multiple properties
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseMultipleProperties_2045) {
    const char* multiPropXMP =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:dc=\"http://purl.org/dc/elements/1.1/\""
        " xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<dc:format>image/jpeg</dc:format>"
        "<xmp:CreatorTool>TestTool</xmp:CreatorTool>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    WXMP_Result wResult;
    XMP_StringLen bufferSize = static_cast<XMP_StringLen>(std::strlen(multiPropXMP));

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), multiPropXMP, bufferSize, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;

    bool found1 = meta->GetProperty("http://purl.org/dc/elements/1.1/", "format", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found1);
    if (found1 && propValue) {
        EXPECT_STREQ(propValue, "image/jpeg");
    }

    bool found2 = meta->GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &propValue, &valueSize, &opts);
    EXPECT_TRUE(found2);
    if (found2 && propValue) {
        EXPECT_STREQ(propValue, "TestTool");
    }
}

// Test: Parse large buffer size value but valid content
TEST_F(WXMPMetaParseFromBufferTest_2045, ParseExactBufferSize_2045) {
    WXMP_Result wResult;
    XMP_StringLen exactSize = static_cast<XMP_StringLen>(std::strlen(kValidXMP));

    WXMPMeta_ParseFromBuffer_1(MetaToRef(meta), kValidXMP, exactSize, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}
