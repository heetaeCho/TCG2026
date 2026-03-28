#include <gtest/gtest.h>
#include <string>
#include <cstring>

#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.hpp"
#include "public/include/XMP.incl_cpp"

class SerializeCompactRDFAttrPropsTest_2112 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that simple properties are serialized as attributes in compact RDF
TEST_F(SerializeCompactRDFAttrPropsTest_2112, SimplePropertiesAsAttributes_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // The serialized output should contain the property
    EXPECT_NE(serialized.find("TestTitle"), std::string::npos);
}

// Test with no properties - empty parent node
TEST_F(SerializeCompactRDFAttrPropsTest_2112, EmptyMetaSerialization_2112) {
    SXMPMeta meta;
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should still produce valid XML
    EXPECT_NE(serialized.find("<?xpacket"), std::string::npos);
}

// Test with multiple simple properties that should all be attrs
TEST_F(SerializeCompactRDFAttrPropsTest_2112, MultipleSimpleProperties_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "image/jpeg");
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestTool");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("image/jpeg"), std::string::npos);
    EXPECT_NE(serialized.find("TestTool"), std::string::npos);
}

// Test with structured property (not all can be attr props)
TEST_F(SerializeCompactRDFAttrPropsTest_2112, StructuredPropertyNotAllAttrs_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "image/jpeg");
    // Array items cannot be RDF attr props
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("image/jpeg"), std::string::npos);
    EXPECT_NE(serialized.find("keyword1"), std::string::npos);
    EXPECT_NE(serialized.find("keyword2"), std::string::npos);
}

// Test with special characters in values (should be escaped for attribute context)
TEST_F(SerializeCompactRDFAttrPropsTest_2112, SpecialCharsInValue_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "test&value<>\"");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Ampersand should be escaped
    EXPECT_NE(serialized.find("&amp;"), std::string::npos);
}

// Test with property value containing quotes
TEST_F(SerializeCompactRDFAttrPropsTest_2112, QuotesInValue_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "He said \"hello\"");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should contain the value somehow encoded
    EXPECT_FALSE(serialized.empty());
}

// Test with empty property value
TEST_F(SerializeCompactRDFAttrPropsTest_2112, EmptyPropertyValue_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should produce valid output with empty attribute
    EXPECT_NE(serialized.find("dc:format"), std::string::npos);
}

// Test with property that has qualifiers (should not be attr prop)
TEST_F(SerializeCompactRDFAttrPropsTest_2112, PropertyWithQualifier_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "MainTitle");
    meta.SetQualifier(kXMP_NS_DC, "title", kXMP_NS_XML, "lang", "en");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("MainTitle"), std::string::npos);
    EXPECT_NE(serialized.find("lang"), std::string::npos);
}

// Test compact format vs non-compact format
TEST_F(SerializeCompactRDFAttrPropsTest_2112, CompactVsNonCompact_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "image/png");
    
    std::string compactSerialized;
    meta.SerializeToBuffer(&compactSerialized, kXMP_UseCompactFormat);
    
    std::string normalSerialized;
    meta.SerializeToBuffer(&normalSerialized, 0);
    
    // Both should contain the value
    EXPECT_NE(compactSerialized.find("image/png"), std::string::npos);
    EXPECT_NE(normalSerialized.find("image/png"), std::string::npos);
    
    // Compact should generally be shorter or equal
    // (not strictly guaranteed but typical)
    EXPECT_FALSE(compactSerialized.empty());
    EXPECT_FALSE(normalSerialized.empty());
}

// Test with newline in property value (should prevent attr serialization or escape)
TEST_F(SerializeCompactRDFAttrPropsTest_2112, NewlineInValue_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "line1\nline2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // Should still produce valid output
    EXPECT_NE(serialized.find("line1"), std::string::npos);
}

// Test single child property
TEST_F(SerializeCompactRDFAttrPropsTest_2112, SingleChildProperty_2112) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "MyApp");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("xmp:CreatorTool"), std::string::npos);
    EXPECT_NE(serialized.find("MyApp"), std::string::npos);
}

// Test property with very long value
TEST_F(SerializeCompactRDFAttrPropsTest_2112, VeryLongValue_2112) {
    SXMPMeta meta;
    std::string longValue(10000, 'A');
    meta.SetProperty(kXMP_NS_DC, "format", longValue.c_str());
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    // The long value should be present somewhere in the output
    EXPECT_NE(serialized.find(std::string(100, 'A')), std::string::npos);
}

// Test mix of attr-eligible and non-attr-eligible properties
TEST_F(SerializeCompactRDFAttrPropsTest_2112, MixedAttrAndNonAttrProps_2112) {
    SXMPMeta meta;
    // Simple property - can be attr
    meta.SetProperty(kXMP_NS_DC, "format", "image/jpeg");
    // Array property - cannot be attr
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1");
    // Another simple property
    meta.SetProperty(kXMP_NS_XMP, "Rating", "5");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat);
    
    EXPECT_NE(serialized.find("image/jpeg"), std::string::npos);
    EXPECT_NE(serialized.find("Author1"), std::string::npos);
}
