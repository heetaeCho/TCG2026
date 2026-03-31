#include <gtest/gtest.h>
#include <string>
#include <vector>

#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"

class SerializePrettyRDFSchemaTest_2111 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "Failed to initialize XMP toolkit";
        }
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

TEST_F(SerializePrettyRDFSchemaTest_2111, BasicSerialization_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("rdf:about"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, SchemaStartAndEndPresent_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "Author Name");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("<rdf:Description rdf:about="), std::string::npos);
    EXPECT_NE(serialized.find("</rdf:Description>"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, MultiplePropertiesInSchema_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "My Title");
    meta.SetProperty(kXMP_NS_DC, "description", "My Description");
    meta.SetProperty(kXMP_NS_DC, "creator", "My Creator");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("dc:title"), std::string::npos);
    EXPECT_NE(serialized.find("dc:description"), std::string::npos);
    EXPECT_NE(serialized.find("dc:creator"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, CompactFormatSerialization_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Compact Title");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_UseCompactFormat, 0);
    
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, PrettyFormatContainsNewlines_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Pretty Title");
    
    std::string serialized;
    // Default (pretty) format without compact flag
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("\n"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, OmitAllFormattingSerialization_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "No Format Title");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_OmitAllFormatting, 0);
    
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, MultipleSchemasInOutput_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "DC Title");
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestTool");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("dc:title"), std::string::npos);
    EXPECT_NE(serialized.find("xmp:CreatorTool"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, NamespaceDeclarationsPresent_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "NS Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // The dc namespace URI should be declared
    EXPECT_NE(serialized.find("http://purl.org/dc/elements/1.1/"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, EmptyMetaSerialization_2111) {
    SXMPMeta meta;
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // Even empty meta should produce valid XML structure
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:RDF"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, IndentationPresent_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Indent Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // Pretty printing should include spaces for indentation
    EXPECT_NE(serialized.find("   "), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, WriteAliasCommentsOption_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Alias Test");
    
    std::string serialized;
    // kXMP_WriteAliasComments = 1024
    meta.SerializeToBuffer(&serialized, kXMP_WriteAliasComments, 0);
    
    // Should still produce valid output
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, RDFAboutContainsTreeName_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "About Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // rdf:about="" for default (empty) tree name
    EXPECT_NE(serialized.find("rdf:about=\"\""), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, OmitPacketWrapperOption_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "No Wrapper");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_OmitPacketWrapper, 0);
    
    // Should not contain packet processing instruction
    EXPECT_EQ(serialized.find("<?xpacket"), std::string::npos);
    // But should still have rdf:Description
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, StructuredPropertySerialization_2111) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field1", "value1");
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field2", "value2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
    EXPECT_NE(serialized.find("value1"), std::string::npos);
    EXPECT_NE(serialized.find("value2"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, ArrayPropertySerialization_2111) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1");
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    EXPECT_NE(serialized.find("rdf:Bag"), std::string::npos);
    EXPECT_NE(serialized.find("keyword1"), std::string::npos);
    EXPECT_NE(serialized.find("keyword2"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, SchemaEndClosingTag_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "End Tag Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // Verify the closing tag appears after the opening
    size_t startPos = serialized.find("<rdf:Description rdf:about=");
    size_t endPos = serialized.find("</rdf:Description>");
    
    ASSERT_NE(startPos, std::string::npos);
    ASSERT_NE(endPos, std::string::npos);
    EXPECT_LT(startPos, endPos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, SpecialCharactersInValue_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Value with <special> & \"chars\"");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 0);
    
    // Special characters should be escaped in XML output
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("rdf:Description"), std::string::npos);
}

TEST_F(SerializePrettyRDFSchemaTest_2111, CustomPaddingSize_2111) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Padding Test");
    
    std::string serialized;
    meta.SerializeToBuffer(&serialized, kXMP_EncodeUTF8, 2048);
    
    // With padding, output should be at least the requested size
    EXPECT_GE(serialized.size(), static_cast<size_t>(2048));
}
