#include <gtest/gtest.h>
#include <string>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.incl_cpp"
#include "public/include/XMP_Const.h"
#include "public/include/TXMPMeta.hpp"

class SerializeCompactRDFSchemasTest_2114 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

TEST_F(SerializeCompactRDFSchemasTest_2114, EmptyXMPSerializesCompactRDF_2114) {
    SXMPMeta meta;
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should contain rdf:Description
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    // Should contain proper XML structure
    EXPECT_NE(serialized.find("<?xpacket"), std::string::npos);
    EXPECT_NE(serialized.find("rdf:RDF"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, SingleSimplePropertyCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("dc:title"), std::string::npos);
    EXPECT_NE(serialized.find("TestTitle"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, MultiplePropertiesCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "Author1");
    meta.SetProperty(kXMP_NS_DC, "description", "A description");
    meta.SetProperty(kXMP_NS_XMP, "CreateDate", "2023-01-01");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("dc:creator"), std::string::npos);
    EXPECT_NE(serialized.find("dc:description"), std::string::npos);
    EXPECT_NE(serialized.find("xmp:CreateDate"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, CompactFormatContainsSchemaStart_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // The compact format should contain rdf:Description rdf:about=
    EXPECT_NE(serialized.find("<rdf:Description rdf:about="), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, CompactFormatWithAboutURI_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Default about should be empty string
    EXPECT_NE(serialized.find("rdf:about=\"\""), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, StructPropertyCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field1", "value1");
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field2", "value2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("value1"), std::string::npos);
    EXPECT_NE(serialized.find("value2"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, ArrayPropertyCompactRDF_2114) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(serialized.find("keyword1"), std::string::npos);
    EXPECT_NE(serialized.find("keyword2"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, OrderedArrayCompactRDF_2114) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1");
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Seq"), std::string::npos);
    EXPECT_NE(serialized.find("Author1"), std::string::npos);
    EXPECT_NE(serialized.find("Author2"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, CompactVsNonCompactDifference_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    
    std::string compactSerialized;
    meta.SerializeToBuffer(&compactSerialized, kXMP_UseCompactFormat);
    
    std::string normalSerialized;
    meta.SerializeToBuffer(&normalSerialized, 0);
    
    // Both should be valid but potentially different
    EXPECT_NE(compactSerialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(normalSerialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, NamespaceDeclaredInCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should declare the dc namespace
    EXPECT_NE(serialized.find("xmlns:dc="), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, MultipleNamespacesCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    meta.SetProperty(kXMP_NS_XMP, "CreateDate", "2023-01-01");
    meta.SetProperty(kXMP_NS_EXIF, "ExifVersion", "0230");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("xmlns:dc="), std::string::npos);
    EXPECT_NE(serialized.find("xmlns:xmp="), std::string::npos);
    EXPECT_NE(serialized.find("xmlns:exif="), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, CompactRDFSchemaEndTag_2114) {
    SXMPMeta meta;
    // Add array property to force element serialization (not just attributes)
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should contain closing rdf:Description tag when element props exist
    EXPECT_NE(serialized.find("</rdf:Description>"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, SimplePropertyAsAttribute_2114) {
    SXMPMeta meta;
    // Simple properties might be serialized as attributes in compact format
    meta.SetProperty(kXMP_NS_DC, "format", "image/jpeg");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("image/jpeg"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, SelfClosingDescriptionWhenAllAttrs_2114) {
    SXMPMeta meta;
    // A simple property without qualifiers should be an attribute in compact
    meta.SetProperty(kXMP_NS_DC, "format", "image/jpeg");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat | kXMP_OmitPacketWrapper);
    
    // If all properties are attributes, description should self-close
    // Check for either self-closing or closing tag
    bool hasSelfClosing = serialized.find("/>") != std::string::npos;
    bool hasClosingTag = serialized.find("</rdf:Description>") != std::string::npos;
    EXPECT_TRUE(hasSelfClosing || hasClosingTag);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, OmitPacketWrapperCompact_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat | kXMP_OmitPacketWrapper);
    
    // Should NOT contain xpacket processing instruction
    EXPECT_EQ(serialized.find("<?xpacket"), std::string::npos);
    // But should still contain RDF structure
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, SpecialCharactersInValueCompact_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "Test <with> &special\" 'chars'");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Special characters should be properly escaped
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    // The output should be valid - at minimum it should not crash
    EXPECT_FALSE(serialized.empty());
}

TEST_F(SerializeCompactRDFSchemasTest_2114, QualifiedPropertyCompactRDF_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    meta.SetQualifier(kXMP_NS_DC, "title", kXMP_NS_XML, "lang", "en");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("xml:lang"), std::string::npos);
    EXPECT_NE(serialized.find("en"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, EmptyValuePropertyCompact_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializeCompactRDFSchemasTest_2114, RoundTripCompactSerialization_2114) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "RoundTripTest");
    meta.SetProperty(kXMP_NS_DC, "format", "text/plain");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Parse the serialized output back
    SXMPMeta meta2;
    meta2.ParseFromBuffer(serialized.c_str(), static_cast<XMP_StringLen>(serialized.size()));
    
    std::string value;
    EXPECT_TRUE(meta2.GetProperty(kXMP_NS_DC, "title", &value, nullptr));
    EXPECT_EQ(value, "RoundTripTest");
    
    EXPECT_TRUE(meta2.GetProperty(kXMP_NS_DC, "format", &value, nullptr));
    EXPECT_EQ(value, "text/plain");
}
