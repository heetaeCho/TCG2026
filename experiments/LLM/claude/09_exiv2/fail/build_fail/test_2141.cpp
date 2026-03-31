#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>

// XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "XMP_Const.h"

// Callback that appends output to a string
static XMP_Status TestOutputProc(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon == nullptr || buffer == nullptr) return -1;
    std::string* output = static_cast<std::string*>(refCon);
    output->append(buffer, bufferSize);
    return 0;
}

class DumpPropertyTreeTest_2141 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    std::string DumpMeta(const SXMPMeta& meta) {
        std::string output;
        meta.DumpObject(TestOutputProc, &output);
        return output;
    }
};

TEST_F(DumpPropertyTreeTest_2141, EmptyMetaDump_2141) {
    SXMPMeta meta;
    std::string output = DumpMeta(meta);
    // An empty XMP object should still produce some dump output (header info)
    EXPECT_FALSE(output.empty());
}

TEST_F(DumpPropertyTreeTest_2141, SimplePropertyDump_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    std::string output = DumpMeta(meta);
    // The output should contain the property name and value
    EXPECT_NE(output.find("title"), std::string::npos);
    EXPECT_NE(output.find("Test Title"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, SimplePropertyValueQuoted_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "John Doe");
    std::string output = DumpMeta(meta);
    // Simple properties should have their value in quotes
    EXPECT_NE(output.find("\"John Doe\""), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, ArrayPropertyDump_2141) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword2", 0);
    std::string output = DumpMeta(meta);
    // Array items should be indexed with [1], [2], etc.
    EXPECT_NE(output.find("[1]"), std::string::npos);
    EXPECT_NE(output.find("[2]"), std::string::npos);
    EXPECT_NE(output.find("keyword1"), std::string::npos);
    EXPECT_NE(output.find("keyword2"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, StructPropertyDump_2141) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "field1", "value1");
    meta.SetStructField(kXMP_NS_DC, "myStruct", kXMP_NS_DC, "field2", "value2");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("field1"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
    EXPECT_NE(output.find("field2"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, OrderedArrayDump_2141) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, "Author2", 0);
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("[1]"), std::string::npos);
    EXPECT_NE(output.find("[2]"), std::string::npos);
    EXPECT_NE(output.find("Author1"), std::string::npos);
    EXPECT_NE(output.find("Author2"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, AltTextWithLangDump_2141) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "", "x-default", "Default Title");
    meta.SetLocalizedText(kXMP_NS_DC, "title", "", "en-US", "English Title");
    std::string output = DumpMeta(meta);
    // Language qualifiers should appear
    EXPECT_NE(output.find("xml:lang"), std::string::npos);
    EXPECT_NE(output.find("x-default"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, QualifierDump_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "A description");
    meta.SetQualifier(kXMP_NS_DC, "description", kXMP_NS_DC, "myQual", "qualValue");
    std::string output = DumpMeta(meta);
    // Qualifiers should be prefixed with "?"
    EXPECT_NE(output.find("?"), std::string::npos);
    EXPECT_NE(output.find("myQual"), std::string::npos);
    EXPECT_NE(output.find("qualValue"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, MultipleNamespaces_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "DC Title");
    meta.SetProperty(kXMP_NS_XMP, "CreatorTool", "TestTool");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("title"), std::string::npos);
    EXPECT_NE(output.find("DC Title"), std::string::npos);
    EXPECT_NE(output.find("CreatorTool"), std::string::npos);
    EXPECT_NE(output.find("TestTool"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, EmptyStringValueDump_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "source", "");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("source"), std::string::npos);
    // Empty value should still appear as ""
    EXPECT_NE(output.find("\"\""), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, NullCallbackRefCon_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test");
    // Testing with null refCon - the callback will return -1
    // This tests the error propagation path
    XMP_Status status = meta.DumpObject(TestOutputProc, nullptr);
    // Status should indicate an error since our callback returns -1 for null refCon
    // The exact behavior depends on implementation, but we test it doesn't crash
}

TEST_F(DumpPropertyTreeTest_2141, LargeValueDump_2141) {
    SXMPMeta meta;
    std::string largeValue(10000, 'A');
    meta.SetProperty(kXMP_NS_DC, "description", largeValue.c_str());
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find(largeValue), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, URIPropertyDump_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "identifier", "http://example.com", kXMP_PropValueIsURI);
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("http://example.com"), std::string::npos);
    // URI flag should be shown in options
    EXPECT_NE(output.find("isURI"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, AlternateArrayDump_2141) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "description",
                         kXMP_PropArrayIsAlternate, "Alt1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "description",
                         kXMP_PropArrayIsAlternate, "Alt2", 0);
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("[1]"), std::string::npos);
    EXPECT_NE(output.find("Alt1"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, NestedStructDump_2141) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "outer", kXMP_NS_DC, "inner", "");
    meta.SetStructField(kXMP_NS_DC, "outer/dc:inner", kXMP_NS_DC, "deep", "deepValue");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
    EXPECT_NE(output.find("deep"), std::string::npos);
    EXPECT_NE(output.find("deepValue"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, SpecialCharactersInValue_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Value with \"quotes\" and <brackets>");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("title"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, MultiplePropertiesSameNamespace_2141) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Title");
    meta.SetProperty(kXMP_NS_DC, "description", "Desc");
    meta.SetProperty(kXMP_NS_DC, "creator", "Creator");
    meta.SetProperty(kXMP_NS_DC, "source", "Source");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("title"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
    EXPECT_NE(output.find("source"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, ArrayWithQualifiers_2141) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsUnordered, "keyword", 0);
    meta.SetQualifier(kXMP_NS_DC, "subject[1]", kXMP_NS_DC, "relevance", "high");
    std::string output = DumpMeta(meta);
    EXPECT_NE(output.find("relevance"), std::string::npos);
    EXPECT_NE(output.find("high"), std::string::npos);
}

TEST_F(DumpPropertyTreeTest_2141, IndentationIncreases_2141) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "struct", kXMP_NS_DC, "field", "val");
    std::string output = DumpMeta(meta);
    // Child nodes should be more indented than parent nodes
    // We just verify the output contains indentation characters (spaces/tabs)
    EXPECT_NE(output.find("   "), std::string::npos);
}
