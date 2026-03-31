#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP_Const.h"

class DeclareUsedNamespacesTest_2106 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }
    
    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that serializing an empty XMP object produces valid output without crashing
TEST_F(DeclareUsedNamespacesTest_2106, EmptyXMP_SerializesWithoutCrash_2106) {
    SXMPMeta meta;
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    EXPECT_FALSE(serialized.empty());
    // Should contain basic XML/RDF structure
    EXPECT_NE(serialized.find("rdf:RDF"), std::string::npos);
}

// Test that a simple property in dc namespace declares dc namespace
TEST_F(DeclareUsedNamespacesTest_2106, SimpleProperty_DeclaresNamespace_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    // The dc namespace should be declared
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("http://purl.org/dc/elements/1.1/"), std::string::npos);
}

// Test that a struct property declares namespaces for its fields
TEST_F(DeclareUsedNamespacesTest_2106, StructProperty_DeclaresFieldNamespaces_2106) {
    SXMPMeta meta;
    // Use IPTC extension namespace with a struct
    std::string ns = "http://iptc.org/std/Iptc4xmpExt/2008-02-29/";
    SXMPMeta::RegisterNamespace(ns.c_str(), "Iptc4xmpExt", nullptr);
    
    meta.SetStructField(ns.c_str(), "TestStruct", kXMP_NS_DC, "fieldName", "fieldValue");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    // Both the outer namespace and dc namespace should be declared
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
}

// Test multiple namespaces are declared when multiple properties from different namespaces exist
TEST_F(DeclareUsedNamespacesTest_2106, MultipleNamespaces_AllDeclared_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestTool");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("xmlns:xmp"), std::string::npos);
}

// Test array property serialization declares namespace properly
TEST_F(DeclareUsedNamespacesTest_2106, ArrayProperty_DeclaresNamespace_2106) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("keyword1"), std::string::npos);
    EXPECT_NE(serialized.find("keyword2"), std::string::npos);
}

// Test that qualifier namespaces are declared
TEST_F(DeclareUsedNamespacesTest_2106, QualifiedProperty_DeclaresQualifierNamespace_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "Test");
    meta.SetQualifier(kXMP_NS_DC, "description", kXMP_NS_XML, "lang", "en");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    // xml:lang should appear
    EXPECT_NE(serialized.find("xml:lang"), std::string::npos);
}

// Test alt-text (language alternatives) declares necessary namespaces
TEST_F(DeclareUsedNamespacesTest_2106, AltText_DeclaresNamespaces_2106) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "", "x-default", "Default Title");
    meta.SetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", "English Title");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("xml:lang"), std::string::npos);
    EXPECT_NE(serialized.find("Default Title"), std::string::npos);
    EXPECT_NE(serialized.find("English Title"), std::string::npos);
}

// Test serialization with compact formatting option
TEST_F(DeclareUsedNamespacesTest_2106, CompactSerialization_DeclaresNamespaces_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "Author");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("Author"), std::string::npos);
}

// Test nested struct properties declare all needed namespaces
TEST_F(DeclareUsedNamespacesTest_2106, NestedStruct_DeclaresAllNamespaces_2106) {
    SXMPMeta meta;
    
    std::string outerNS = "http://test.example.com/outer/";
    std::string innerNS = "http://test.example.com/inner/";
    SXMPMeta::RegisterNamespace(outerNS.c_str(), "outer", nullptr);
    SXMPMeta::RegisterNamespace(innerNS.c_str(), "inner", nullptr);
    
    // Create a struct with a nested struct field
    meta.SetStructField(outerNS.c_str(), "TestStruct", innerNS.c_str(), "InnerField", "InnerValue");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:outer"), std::string::npos);
    EXPECT_NE(serialized.find("xmlns:inner"), std::string::npos);
}

// Test that same namespace used multiple times is only declared once
TEST_F(DeclareUsedNamespacesTest_2106, DuplicateNamespace_DeclaredOnce_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Title");
    meta.SetProperty(kXMP_NS_DC, "description", "Description");
    meta.SetProperty(kXMP_NS_DC, "creator", "Creator");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    // Count occurrences of xmlns:dc - should be exactly once
    size_t pos = 0;
    int count = 0;
    while ((pos = serialized.find("xmlns:dc=", pos)) != std::string::npos) {
        ++count;
        pos += 9;
    }
    EXPECT_EQ(count, 1);
}

// Test serialization to buffer with read-only XMP (parsed from string)
TEST_F(DeclareUsedNamespacesTest_2106, ParsedXMP_SerializesWithNamespaces_2106) {
    const char* xmpPacket = 
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title>Test</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";
    
    SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("Test"), std::string::npos);
}

// Test schema node with value triggers namespace declaration
TEST_F(DeclareUsedNamespacesTest_2106, SchemaNodeValue_NamespaceDeclared_2106) {
    SXMPMeta meta;
    // Setting property in XMP namespace creates a schema node
    meta.SetProperty(kXMP_NS_XMP, "Rating", "5");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:xmp"), std::string::npos);
    EXPECT_NE(serialized.find("5"), std::string::npos);
}

// Test ordered array declares namespace
TEST_F(DeclareUsedNamespacesTest_2106, OrderedArray_DeclaresNamespace_2106) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1");
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("rdf:Seq"), std::string::npos);
}

// Test that serialization with no properties still produces well-formed output
TEST_F(DeclareUsedNamespacesTest_2106, NoProperties_WellFormedOutput_2106) {
    SXMPMeta meta;
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    // Should have proper XML structure
    EXPECT_NE(serialized.find("<?xpacket"), std::string::npos);
    EXPECT_NE(serialized.find("rdf:RDF"), std::string::npos);
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

// Test property with URI value type
TEST_F(DeclareUsedNamespacesTest_2106, URIProperty_DeclaresNamespace_2106) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "identifier", "http://example.com/id", kXMP_PropValueIsURI);
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized);
    
    EXPECT_NE(serialized.find("xmlns:dc"), std::string::npos);
    EXPECT_NE(serialized.find("http://example.com/id"), std::string::npos);
}
