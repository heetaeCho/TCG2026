#include <gtest/gtest.h>
#include <string>
#include <cstring>

#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.hpp"
#include "public/include/XMP.incl_cpp"

// Callback to accumulate output text
static XMP_Status AccumulateOutput(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    std::string* output = static_cast<std::string*>(refCon);
    output->append(buffer, bufferSize);
    return 0;
}

class XMPMetaDumpTest_2140 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

TEST_F(XMPMetaDumpTest_2140, DumpEmptyMeta_2140) {
    SXMPMeta meta;
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // An empty meta should produce some output (at minimum a header)
    EXPECT_FALSE(output.empty());
}

TEST_F(XMPMetaDumpTest_2140, DumpWithSimpleProperty_2140) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Output should contain something related to the property
    EXPECT_NE(output.find("dc:"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpWithArrayProperty_2140) {
    SXMPMeta meta;
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsOrdered, "keyword1", 0);
    meta.AppendArrayItem(kXMP_NS_DC, "subject", kXMP_PropArrayIsOrdered, "keyword2", 0);
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Should contain array-related option flags like isOrdered or isArray
    EXPECT_NE(output.find("isOrdered"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpWithStructProperty_2140) {
    SXMPMeta meta;
    meta.SetStructField(kXMP_NS_DC, "testStruct", kXMP_NS_DC, "field1", "value1");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("isStruct"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpWithQualifier_2140) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "A description");
    meta.SetQualifier(kXMP_NS_DC, "description", kXMP_NS_XML, "lang", "en");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("hasQual"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpWithLangAlt_2140) {
    SXMPMeta meta;
    meta.SetLocalizedText(kXMP_NS_DC, "title", "", "x-default", "Default Title");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("isLangAlt"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpOptionBitsShowHex_2140) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "creator", "Author", 0);
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Options should appear in hex format with "0x" prefix
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpNullCallbackReturnsError_2140) {
    SXMPMeta meta;
    // Passing null outProc should cause an error
    EXPECT_ANY_THROW(meta.DumpObject(nullptr, nullptr));
}

TEST_F(XMPMetaDumpTest_2140, DumpSchemaOption_2140) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "format", "application/pdf");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // The schema node should have the "schema" option label
    EXPECT_NE(output.find("schema"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpZeroOptionsShowsZero_2140) {
    // A simple property with no special flags should show (0x0) for zero options
    // or a small hex value. We verify the dump contains "0x" formatting.
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "identifier", "12345");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // At minimum "0x" should appear in output for option formatting
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(XMPMetaDumpTest_2140, DumpMultipleProperties_2140) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Title");
    meta.SetProperty(kXMP_NS_DC, "creator", "Creator");
    meta.SetProperty(kXMP_NS_DC, "description", "Desc");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("title"), std::string::npos);
    EXPECT_NE(output.find("creator"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
}
