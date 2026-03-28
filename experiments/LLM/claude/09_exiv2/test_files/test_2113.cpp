#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "XMP_Const.h"

class SerializeCompactRDFElemPropsTest_2113 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    std::string SerializeCompact(SXMPMeta& meta) {
        std::string output;
        meta.SerializeToBuffer(&output, kXMP_UseCompactFormat);
        return output;
    }
};

// Test simple property serialization in compact format
TEST_F(SerializeCompactRDFElemPropsTest_2113, SimplePropertySerialized_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    
    std::string output = SerializeCompact(meta);
    
    // The output should contain the dc:title element
    EXPECT_NE(output.find("dc:title"), std::string::npos);
    EXPECT_NE(output.find("Test Title"), std::string::npos);
}

// Test empty property value serialization (should produce self-closing tag)
TEST_F(SerializeCompactRDFElemPropsTest_2113, EmptyPropertyValue_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "");
    
    std::string output = SerializeCompact(meta);
    
    // Empty value should result in a self-closing tag or empty element
    // The compact serializer should handle this case
    EXPECT_NE(output.find("dc:description"), std::string::npos);
}

// Test URI property serialization (rdf:resource attribute)
TEST_F(SerializeCompactRDFElemPropsTest_2113, URIPropertySerialized_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "identifier", "http://example.com/resource", kXMP_PropValueIsURI);
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("rdf:resource"), std::string::npos);
    EXPECT_NE(output.find("http://example.com/resource"), std::string::npos);
}

// Test ordered array serialization
TEST_F(SerializeCompactRDFElemPropsTest_2113, OrderedArraySerialized_2113) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author One");
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author Two");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("rdf:Seq"), std::string::npos);
    EXPECT_NE(output.find("rdf:li"), std::string::npos);
    EXPECT_NE(output.find("Author One"), std::string::npos);
    EXPECT_NE(output.find("Author Two"), std::string::npos);
}

// Test unordered array serialization
TEST_F(SerializeCompactRDFElemPropsTest_2113, UnorderedArraySerialized_2113) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(output.find("rdf:li"), std::string::npos);
    EXPECT_NE(output.find("keyword1"), std::string::npos);
    EXPECT_NE(output.find("keyword2"), std::string::npos);
}

// Test alternative array (alt text) serialization
TEST_F(SerializeCompactRDFElemPropsTest_2113, AltTextArraySerialized_2113) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", "English Title");
    meta.SetLocalizedText(kXMP_NS_DC, "title", "fr", "fr-FR", "Titre Français");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("rdf:Alt"), std::string::npos);
    EXPECT_NE(output.find("rdf:li"), std::string::npos);
    EXPECT_NE(output.find("xml:lang"), std::string::npos);
    EXPECT_NE(output.find("English Title"), std::string::npos);
}

// Test struct property serialization
TEST_F(SerializeCompactRDFElemPropsTest_2113, StructPropertySerialized_2113) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_IPTC4xmpCore, "CreatorContactInfo",
                        kXMP_NS_IPTC4xmpCore, "CiEmailWork", "test@example.com");
    meta.SetStructField(kXMP_NS_IPTC4xmpCore, "CreatorContactInfo",
                        kXMP_NS_IPTC4xmpCore, "CiUrlWork", "http://example.com");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("CreatorContactInfo"), std::string::npos);
    EXPECT_NE(output.find("test@example.com"), std::string::npos);
}

// Test property with special XML characters that need escaping
TEST_F(SerializeCompactRDFElemPropsTest_2113, SpecialCharactersEscaped_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "Value with <special> & \"chars\"");
    
    std::string output = SerializeCompact(meta);
    
    // The special characters should be escaped in the output
    EXPECT_NE(output.find("dc:description"), std::string::npos);
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// Test empty struct serialization (rdf:parseType="Resource" with self-closing)
TEST_F(SerializeCompactRDFElemPropsTest_2113, EmptyStructSerialized_2113) {
    SXMPMeta meta;
    // Create a struct with no fields by setting and then removing
    meta.SetStructField(kXMP_NS_XMP, "TestStruct", kXMP_NS_XMP, "field", "value");
    meta.DeleteProperty(kXMP_NS_XMP, "TestStruct/xmp:field");
    
    std::string output = SerializeCompact(meta);
    
    // If the empty struct survives, it should serialize with parseType="Resource"
    // The struct may or may not be present depending on cleanup
    EXPECT_FALSE(output.empty());
}

// Test multiple properties in the same namespace
TEST_F(SerializeCompactRDFElemPropsTest_2113, MultiplePropertiesSameNamespace_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "My Title");
    meta.SetProperty(kXMP_NS_DC, "creator", "John Doe");
    meta.SetProperty(kXMP_NS_DC, "description", "A description");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("dc:title"), std::string::npos);
    EXPECT_NE(output.find("My Title"), std::string::npos);
}

// Test compact format produces valid XML structure
TEST_F(SerializeCompactRDFElemPropsTest_2113, CompactFormatProducesValidXML_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string output = SerializeCompact(meta);
    
    // Should have XML declaration
    EXPECT_NE(output.find("<?xpacket"), std::string::npos);
    // Should have RDF root
    EXPECT_NE(output.find("rdf:RDF"), std::string::npos);
    // Should have rdf:Description
    EXPECT_NE(output.find("rdf:Description"), std::string::npos);
}

// Test qualifier with xml:lang on a simple property
TEST_F(SerializeCompactRDFElemPropsTest_2113, QualifierWithLang_2113) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "description", "", "x-default", "Default description");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("xml:lang"), std::string::npos);
    EXPECT_NE(output.find("x-default"), std::string::npos);
    EXPECT_NE(output.find("Default description"), std::string::npos);
}

// Test nested array inside struct
TEST_F(SerializeCompactRDFElemPropsTest_2113, NestedArrayInStruct_2113) {
    SXMPMeta meta;
    const char* ns = "http://ns.test.com/test/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    
    meta.SetStructField(ns, "myStruct", ns, "name", "TestName");
    meta.AppendArrayItem(ns, "myStruct/test:tags", kXMP_PropArrayIsUnordered, "tag1");
    meta.AppendArrayItem(ns, "myStruct/test:tags", kXMP_PropArrayIsUnordered, "tag2");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("test:myStruct"), std::string::npos);
    EXPECT_NE(output.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(output.find("tag1"), std::string::npos);
    EXPECT_NE(output.find("tag2"), std::string::npos);
}

// Test alternate array serialization
TEST_F(SerializeCompactRDFElemPropsTest_2113, AlternateArraySerialized_2113) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "title",
                         kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered,
                         "First Alternative");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("rdf:Alt"), std::string::npos);
    EXPECT_NE(output.find("First Alternative"), std::string::npos);
}

// Test property value with newline characters
TEST_F(SerializeCompactRDFElemPropsTest_2113, PropertyWithNewlines_2113) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "Line1\nLine2\nLine3");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("dc:description"), std::string::npos);
    // The newlines should be preserved or escaped in the output
    EXPECT_FALSE(output.empty());
}

// Test serialization with no properties produces minimal output
TEST_F(SerializeCompactRDFElemPropsTest_2113, NoPropertiesMinimalOutput_2113) {
    SXMPMeta meta;
    
    std::string output = SerializeCompact(meta);
    
    // Even with no properties, should produce valid XMP packet
    EXPECT_NE(output.find("<?xpacket"), std::string::npos);
    EXPECT_NE(output.find("rdf:RDF"), std::string::npos);
}

// Test struct with all attr-friendly fields (compact attribute form)
TEST_F(SerializeCompactRDFElemPropsTest_2113, StructWithAttrFriendlyFields_2113) {
    SXMPMeta meta;
    const char* ns = "http://ns.test.com/attr/";
    SXMPMeta::RegisterNamespace(ns, "attr", nullptr);
    
    meta.SetStructField(ns, "simpleStruct", ns, "field1", "value1");
    meta.SetStructField(ns, "simpleStruct", ns, "field2", "value2");
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("attr:simpleStruct"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
}

// Test long property value
TEST_F(SerializeCompactRDFElemPropsTest_2113, LongPropertyValue_2113) {
    SXMPMeta meta;
    std::string longValue(10000, 'A');
    meta.SetProperty(kXMP_NS_DC, "description", longValue.c_str());
    
    std::string output = SerializeCompact(meta);
    
    EXPECT_NE(output.find("dc:description"), std::string::npos);
    // The long value should be present in the output
    EXPECT_NE(output.find(longValue), std::string::npos);
}
