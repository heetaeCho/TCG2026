#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "XMP_Const.h"

class SerializePrettyRDFPropertyTest_2110 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    std::string SerializeToRDF(SXMPMeta& meta) {
        std::string rdfStr;
        meta.SerializeToBuffer(&rdfStr, kXMP_OmitPacketWrapper);
        return rdfStr;
    }
};

// Test simple property serialization (propForm == 0, non-empty value)
TEST_F(SerializePrettyRDFPropertyTest_2110, SimplePropertyWithValue_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("dc:title"), std::string::npos);
    EXPECT_NE(rdf.find("Test Title"), std::string::npos);
}

// Test simple property with empty value (should produce self-closing tag)
TEST_F(SerializePrettyRDFPropertyTest_2110, SimplePropertyEmptyValue_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "");
    
    std::string rdf = SerializeToRDF(meta);
    // Empty value should produce self-closing tag like <dc:description/>
    EXPECT_NE(rdf.find("dc:description"), std::string::npos);
}

// Test property with URI value (kXMP_PropValueIsURI)
TEST_F(SerializePrettyRDFPropertyTest_2110, PropertyWithURIValue_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "identifier", "http://example.com", kXMP_PropValueIsURI);
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:resource"), std::string::npos);
    EXPECT_NE(rdf.find("http://example.com"), std::string::npos);
}

// Test ordered array serialization
TEST_F(SerializePrettyRDFPropertyTest_2110, OrderedArrayProperty_2110) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1");
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author2");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:Seq"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:li"), std::string::npos);
    EXPECT_NE(rdf.find("Author1"), std::string::npos);
    EXPECT_NE(rdf.find("Author2"), std::string::npos);
}

// Test unordered array serialization
TEST_F(SerializePrettyRDFPropertyTest_2110, UnorderedArrayProperty_2110) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:li"), std::string::npos);
    EXPECT_NE(rdf.find("keyword1"), std::string::npos);
    EXPECT_NE(rdf.find("keyword2"), std::string::npos);
}

// Test alternative array serialization
TEST_F(SerializePrettyRDFPropertyTest_2110, AlternativeArrayProperty_2110) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "description", kXMP_PropArrayIsAlternate, "desc1");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:Alt"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:li"), std::string::npos);
}

// Test AltText array (language alternatives)
TEST_F(SerializePrettyRDFPropertyTest_2110, AltTextArrayProperty_2110) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", "English Title");
    meta.SetLocalizedText(kXMP_NS_DC, "title", "fr", "fr-FR", "Titre Français");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:Alt"), std::string::npos);
    EXPECT_NE(rdf.find("xml:lang"), std::string::npos);
    EXPECT_NE(rdf.find("English Title"), std::string::npos);
}

// Test struct property serialization
TEST_F(SerializePrettyRDFPropertyTest_2110, StructProperty_2110) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field1", "value1", 0);
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field2", "value2", 0);
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:parseType=\"Resource\""), std::string::npos);
    EXPECT_NE(rdf.find("value1"), std::string::npos);
    EXPECT_NE(rdf.find("value2"), std::string::npos);
}

// Test empty struct property (should produce self-closing tag with parseType)
TEST_F(SerializePrettyRDFPropertyTest_2110, EmptyStructProperty_2110) {
    SXMPMeta meta;
    // Set a struct with a field, then remove the field to get empty struct
    meta.SetStructField(kXMP_NS_DC, "emptyStruct", kXMP_NS_DC, "tempField", "tempValue", 0);
    meta.DeleteProperty(kXMP_NS_DC, "emptyStruct/dc:tempField");
    
    std::string rdf = SerializeToRDF(meta);
    // An empty struct might be removed or serialized as self-closing
    // Just verify no crash and valid output
    EXPECT_FALSE(rdf.empty());
}

// Test property with qualifier (xml:lang is an RDF attr qualifier)
TEST_F(SerializePrettyRDFPropertyTest_2110, PropertyWithLangQualifier_2110) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "description", "", "x-default", "Default description");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("xml:lang"), std::string::npos);
    EXPECT_NE(rdf.find("x-default"), std::string::npos);
    EXPECT_NE(rdf.find("Default description"), std::string::npos);
}

// Test property with general qualifiers (non-RDF-attr qualifiers)
TEST_F(SerializePrettyRDFPropertyTest_2110, PropertyWithGeneralQualifier_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "source", "some source");
    meta.SetQualifier(kXMP_NS_DC, "source", kXMP_NS_DC, "customQual", "qualValue");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:parseType=\"Resource\""), std::string::npos);
    EXPECT_NE(rdf.find("rdf:value"), std::string::npos);
    EXPECT_NE(rdf.find("some source"), std::string::npos);
}

// Test value with special XML characters requiring escaping
TEST_F(SerializePrettyRDFPropertyTest_2110, PropertyWithSpecialCharacters_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Value with <special> & \"chars\"");
    
    std::string rdf = SerializeToRDF(meta);
    // XML special chars should be escaped
    EXPECT_NE(rdf.find("&lt;"), std::string::npos);
    EXPECT_NE(rdf.find("&amp;"), std::string::npos);
}

// Test nested array in struct
TEST_F(SerializePrettyRDFPropertyTest_2110, NestedArrayInStruct_2110) {
    SXMPMeta meta;
    std::string path;
    
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "name", "TestName", 0);
    SXMPUtils::ComposeStructFieldPath(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "tags", &path);
    meta.AppendArrayItem(kXMP_NS_DC, path.c_str(), kXMP_PropArrayIsUnordered, "tag1");
    meta.AppendArrayItem(kXMP_NS_DC, path.c_str(), kXMP_PropArrayIsUnordered, "tag2");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("TestName"), std::string::npos);
    EXPECT_NE(rdf.find("tag1"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:Bag"), std::string::npos);
}

// Test multiple namespaces
TEST_F(SerializePrettyRDFPropertyTest_2110, MultipleNamespaces_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "DC Title");
    meta.SetProperty(kXMP_NS_XMP, "CreateDate", "2023-01-01");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("dc:title"), std::string::npos);
    EXPECT_NE(rdf.find("DC Title"), std::string::npos);
    EXPECT_NE(rdf.find("2023-01-01"), std::string::npos);
}

// Test serialization produces valid XML structure
TEST_F(SerializePrettyRDFPropertyTest_2110, ValidXMLStructure_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    
    std::string rdf = SerializeToRDF(meta);
    // Should contain RDF root element
    EXPECT_NE(rdf.find("<rdf:RDF"), std::string::npos);
    EXPECT_NE(rdf.find("</rdf:RDF>"), std::string::npos);
    EXPECT_NE(rdf.find("<rdf:Description"), std::string::npos);
}

// Test empty metadata serialization
TEST_F(SerializePrettyRDFPropertyTest_2110, EmptyMetadata_2110) {
    SXMPMeta meta;
    
    std::string rdf = SerializeToRDF(meta);
    // Even empty metadata should produce valid RDF wrapper
    EXPECT_NE(rdf.find("<rdf:RDF"), std::string::npos);
    EXPECT_NE(rdf.find("</rdf:RDF>"), std::string::npos);
}

// Test array with single item
TEST_F(SerializePrettyRDFPropertyTest_2110, ArrayWithSingleItem_2110) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "singleKeyword");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:li"), std::string::npos);
    EXPECT_NE(rdf.find("singleKeyword"), std::string::npos);
}

// Test property value with URI in attribute context
TEST_F(SerializePrettyRDFPropertyTest_2110, URIPropertySerialization_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "relation", "http://example.org/resource", kXMP_PropValueIsURI);
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("rdf:resource=\"http://example.org/resource\""), std::string::npos);
}

// Test deeply nested structures
TEST_F(SerializePrettyRDFPropertyTest_2110, DeeplyNestedStruct_2110) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "outer", kXMP_NS_DC, "inner", "", kXMP_PropValueIsStruct);
    meta.SetStructField(kXMP_NS_DC, "outer/dc:inner", kXMP_NS_DC, "deep", "deepValue", 0);
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("deepValue"), std::string::npos);
}

// Test AltText with x-default normalization
TEST_F(SerializePrettyRDFPropertyTest_2110, AltTextXDefaultFirst_2110) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "fr", "fr", "Titre");
    meta.SetLocalizedText(kXMP_NS_DC, "title", "", "x-default", "Default Title");
    
    std::string rdf = SerializeToRDF(meta);
    // x-default should be normalized to be first in Alt array
    size_t defaultPos = rdf.find("x-default");
    size_t frPos = rdf.find("xml:lang=\"fr\"");
    EXPECT_NE(defaultPos, std::string::npos);
    EXPECT_NE(frPos, std::string::npos);
    // x-default should appear before fr
    EXPECT_LT(defaultPos, frPos);
}

// Test property with ampersand in value (XML escaping)
TEST_F(SerializePrettyRDFPropertyTest_2110, PropertyValueAmpersandEscaping_2110) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "rights", "Copyright & Trademark");
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("&amp;"), std::string::npos);
    // Raw & should not appear in element context (except as part of escape)
}

// Test large number of array items
TEST_F(SerializePrettyRDFPropertyTest_2110, LargeArray_2110) {
    SXMPMeta meta;
    for (int i = 0; i < 100; ++i) {
        std::string val = "item" + std::to_string(i);
        meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, val.c_str());
    }
    
    std::string rdf = SerializeToRDF(meta);
    EXPECT_NE(rdf.find("item0"), std::string::npos);
    EXPECT_NE(rdf.find("item99"), std::string::npos);
    EXPECT_NE(rdf.find("rdf:Bag"), std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
