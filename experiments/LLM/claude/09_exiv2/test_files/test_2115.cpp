#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers for XMPMeta
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

class XMPMetaSerializeTest_2115 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test serialization of an empty XMP object with default options
TEST_F(XMPMetaSerializeTest_2115, SerializeEmptyXMP_DefaultOptions_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    ASSERT_GT(rdfSize, 0u);
    
    std::string result(rdfString, rdfSize);
    // Should contain packet header
    EXPECT_NE(result.find("<?xpacket begin="), std::string::npos);
    // Should contain packet trailer
    EXPECT_NE(result.find("<?xpacket end="), std::string::npos);
    // Should contain RDF start
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
    // Should contain RDF end
    EXPECT_NE(result.find("</rdf:RDF>"), std::string::npos);
    // Should contain xmpmeta element
    EXPECT_NE(result.find("<x:xmpmeta"), std::string::npos);
    EXPECT_NE(result.find("</x:xmpmeta>"), std::string::npos);
}

// Test serialization with kXMP_OmitPacketWrapper
TEST_F(XMPMetaSerializeTest_2115, SerializeOmitPacketWrapper_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should NOT contain packet header/trailer
    EXPECT_EQ(result.find("<?xpacket"), std::string::npos);
    // Should still contain RDF
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
}

// Test serialization with kXMP_OmitXMPMetaElement
TEST_F(XMPMetaSerializeTest_2115, SerializeOmitXMPMetaElement_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper | kXMP_OmitXMPMetaElement, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should NOT contain xmpmeta element
    EXPECT_EQ(result.find("<x:xmpmeta"), std::string::npos);
    EXPECT_EQ(result.find("</x:xmpmeta>"), std::string::npos);
    // Should still contain RDF
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
}

// Test serialization with kXMP_ReadOnlyPacket
TEST_F(XMPMetaSerializeTest_2115, SerializeReadOnlyPacket_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_ReadOnlyPacket, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // The trailer should have 'r' instead of 'w' for read-only
    EXPECT_NE(result.find("<?xpacket end=\"r\"?>"), std::string::npos);
}

// Test serialization without kXMP_ReadOnlyPacket (writable)
TEST_F(XMPMetaSerializeTest_2115, SerializeWritablePacket_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // The trailer should have 'w' for writable
    EXPECT_NE(result.find("<?xpacket end=\"w\"?>"), std::string::npos);
}

// Test serialization with compact format
TEST_F(XMPMetaSerializeTest_2115, SerializeCompactFormat_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_UseCompactFormat, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    ASSERT_GT(rdfSize, 0u);
    
    std::string result(rdfString, rdfSize);
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
}

// Test serialization with a property set
TEST_F(XMPMetaSerializeTest_2115, SerializeWithProperty_2115) {
    XMPMeta xmpObj;
    
    // Set a simple property
    xmpObj.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Test Title", 0);
    
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should contain the property value
    EXPECT_NE(result.find("Test Title"), std::string::npos);
    // Should contain schema description
    EXPECT_NE(result.find("rdf:Description"), std::string::npos);
}

// Test serialization with custom newline
TEST_F(XMPMetaSerializeTest_2115, SerializeWithCustomNewline_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\r\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should contain \r\n as line endings
    EXPECT_NE(result.find("\r\n"), std::string::npos);
}

// Test serialization with custom indent
TEST_F(XMPMetaSerializeTest_2115, SerializeWithCustomIndent_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "\t", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should contain tab indentation
    EXPECT_NE(result.find("\t"), std::string::npos);
}

// Test serialization with base indent > 0
TEST_F(XMPMetaSerializeTest_2115, SerializeWithBaseIndent_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString1 = nullptr;
    XMP_StringLen rdfSize1 = 0;
    XMP_StringPtr rdfString2 = nullptr;
    XMP_StringLen rdfSize2 = 0;

    xmpObj.SerializeToBuffer(&rdfString1, &rdfSize1, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);
    xmpObj.SerializeToBuffer(&rdfString2, &rdfSize2, kXMP_OmitPacketWrapper, 0, "\n", "  ", 2);

    ASSERT_NE(rdfString1, nullptr);
    ASSERT_NE(rdfString2, nullptr);
    
    std::string result1(rdfString1, rdfSize1);
    std::string result2(rdfString2, rdfSize2);
    
    // Result with base indent 2 should be longer due to extra indentation
    EXPECT_GT(result2.size(), result1.size());
}

// Test serialization with multiple properties in different schemas
TEST_F(XMPMetaSerializeTest_2115, SerializeMultipleSchemas_2115) {
    XMPMeta xmpObj;
    
    xmpObj.SetProperty("http://purl.org/dc/elements/1.1/", "title", "My Title", 0);
    xmpObj.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    EXPECT_NE(result.find("My Title"), std::string::npos);
    EXPECT_NE(result.find("TestTool"), std::string::npos);
}

// Test serialization with compact format and properties
TEST_F(XMPMetaSerializeTest_2115, SerializeCompactFormatWithProperties_2115) {
    XMPMeta xmpObj;
    
    xmpObj.SetProperty("http://purl.org/dc/elements/1.1/", "creator", "Author Name", 0);
    
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_UseCompactFormat | kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    EXPECT_NE(result.find("Author Name"), std::string::npos);
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
}

// Test serialization produces valid XML structure
TEST_F(XMPMetaSerializeTest_2115, SerializeProducesValidStructure_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Verify proper nesting - xmpmeta start before RDF start
    size_t xmpmetaStart = result.find("<x:xmpmeta");
    size_t rdfStart = result.find("<rdf:RDF");
    size_t rdfEnd = result.find("</rdf:RDF>");
    size_t xmpmetaEnd = result.find("</x:xmpmeta>");
    
    EXPECT_LT(xmpmetaStart, rdfStart);
    EXPECT_LT(rdfStart, rdfEnd);
    EXPECT_LT(rdfEnd, xmpmetaEnd);
}

// Test serialization of empty XMP object contains rdf:Description with about
TEST_F(XMPMetaSerializeTest_2115, SerializeEmptyContainsDescription_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Empty XMP should have an empty rdf:Description
    EXPECT_NE(result.find("rdf:Description rdf:about="), std::string::npos);
}

// Test serialization with both omit options
TEST_F(XMPMetaSerializeTest_2115, SerializeOmitBothWrappers_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 
        kXMP_OmitPacketWrapper | kXMP_OmitXMPMetaElement, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    EXPECT_EQ(result.find("<?xpacket"), std::string::npos);
    EXPECT_EQ(result.find("<x:xmpmeta"), std::string::npos);
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
    EXPECT_NE(result.find("</rdf:RDF>"), std::string::npos);
}

// Test that setting object name affects serialization
TEST_F(XMPMetaSerializeTest_2115, SerializeWithObjectName_2115) {
    XMPMeta xmpObj;
    xmpObj.SetObjectName("test-about-value");
    
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // The object name should appear in the rdf:about attribute
    EXPECT_NE(result.find("test-about-value"), std::string::npos);
}

// Test serialization with XMP_OmitAllFormatting
TEST_F(XMPMetaSerializeTest_2115, SerializeOmitAllFormatting_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 
        kXMP_OmitPacketWrapper | kXMP_OmitAllFormatting, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should still contain RDF content
    EXPECT_NE(result.find("<rdf:RDF"), std::string::npos);
}

// Test that packet header contains expected content
TEST_F(XMPMetaSerializeTest_2115, PacketHeaderContent_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, 0, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Packet header should contain the BOM and ID
    EXPECT_NE(result.find("W5M0MpCehiHzreSzNTczkc9d"), std::string::npos);
}

// Test serialization consistency - same input produces same output
TEST_F(XMPMetaSerializeTest_2115, SerializeConsistency_2115) {
    XMPMeta xmpObj;
    xmpObj.SetProperty("http://purl.org/dc/elements/1.1/", "title", "Consistent", 0);
    
    XMP_StringPtr rdfString1 = nullptr;
    XMP_StringLen rdfSize1 = 0;
    XMP_StringPtr rdfString2 = nullptr;
    XMP_StringLen rdfSize2 = 0;

    xmpObj.SerializeToBuffer(&rdfString1, &rdfSize1, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);
    xmpObj.SerializeToBuffer(&rdfString2, &rdfSize2, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString1, nullptr);
    ASSERT_NE(rdfString2, nullptr);
    
    std::string result1(rdfString1, rdfSize1);
    std::string result2(rdfString2, rdfSize2);
    
    EXPECT_EQ(result1, result2);
}

// Test that xmpmeta element contains version info
TEST_F(XMPMetaSerializeTest_2115, XMPMetaContainsVersionInfo_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // xmpmeta should contain x:xmptk attribute with version
    EXPECT_NE(result.find("x:xmptk="), std::string::npos);
}

// Test serialization after erasing all content
TEST_F(XMPMetaSerializeTest_2115, SerializeAfterErase_2115) {
    XMPMeta xmpObj;
    xmpObj.SetProperty("http://purl.org/dc/elements/1.1/", "title", "To Be Erased", 0);
    xmpObj.Erase();
    
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    // Should not contain the erased property
    EXPECT_EQ(result.find("To Be Erased"), std::string::npos);
}

// Test that RDF namespace declaration is present
TEST_F(XMPMetaSerializeTest_2115, RDFNamespacePresent_2115) {
    XMPMeta xmpObj;
    XMP_StringPtr rdfString = nullptr;
    XMP_StringLen rdfSize = 0;

    xmpObj.SerializeToBuffer(&rdfString, &rdfSize, kXMP_OmitPacketWrapper, 0, "\n", "  ", 0);

    ASSERT_NE(rdfString, nullptr);
    std::string result(rdfString, rdfSize);
    
    EXPECT_NE(result.find("xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""), std::string::npos);
}
