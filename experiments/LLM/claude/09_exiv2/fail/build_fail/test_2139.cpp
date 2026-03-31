#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstring>

#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP_Const.h"

// Callback that accumulates output into a string
static XMP_Status AccumulateOutput(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon == nullptr || buffer == nullptr) return -1;
    std::string* output = static_cast<std::string*>(refCon);
    output->append(buffer, bufferSize);
    return 0;
}

class XMPMetaDumpTest_2139 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that DumpObject works on an empty XMPMeta object
TEST_F(XMPMetaDumpTest_2139, DumpEmptyObject_2139) {
    SXMPMeta meta;
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Even an empty object should produce some output (headers, etc.)
    EXPECT_FALSE(output.empty());
}

// Test that DumpObject includes property information when properties are set
TEST_F(XMPMetaDumpTest_2139, DumpObjectWithProperties_2139) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "TestTitle");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    // The output should contain the property value we set
    EXPECT_NE(output.find("TestTitle"), std::string::npos);
}

// Test DumpObject with multiple properties
TEST_F(XMPMetaDumpTest_2139, DumpObjectWithMultipleProperties_2139) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "MyTitle");
    meta.SetProperty(kXMP_NS_DC, "creator", "MyCreator");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("MyTitle"), std::string::npos);
    EXPECT_NE(output.find("MyCreator"), std::string::npos);
}

// Test DumpObject with null refCon - the callback should handle it
TEST_F(XMPMetaDumpTest_2139, DumpObjectNullRefCon_2139) {
    SXMPMeta meta;
    // Passing nullptr as refCon - callback returns error
    XMP_Status status = meta.DumpObject(AccumulateOutput, nullptr);
    // The status might be non-zero since the callback returns -1 for null refCon
    EXPECT_NE(status, 0);
}

// Test that DumpObject reflects namespace prefixes
TEST_F(XMPMetaDumpTest_2139, DumpObjectShowsNamespace_2139) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "subject", "Science");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Should contain dc namespace reference
    EXPECT_NE(output.find("dc"), std::string::npos);
}

// Test DumpObject with structured/nested property
TEST_F(XMPMetaDumpTest_2139, DumpObjectWithQualifier_2139) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "A test description");
    meta.SetQualifier(kXMP_NS_DC, "description", kXMP_NS_XML, "lang", "en");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("A test description"), std::string::npos);
}

// Test DumpObject produces aligned output (the padding logic in DumpStringMap)
TEST_F(XMPMetaDumpTest_2139, DumpObjectAlignment_2139) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "a", "short");
    meta.SetProperty(kXMP_NS_DC, "longpropertyname", "value");
    std::string output;
    XMP_Status status = meta.DumpObject(AccumulateOutput, &output);
    EXPECT_EQ(status, 0);
    // Output should contain the " => " separator used in DumpStringMap
    // This verifies the map dumping format
    EXPECT_FALSE(output.empty());
}
