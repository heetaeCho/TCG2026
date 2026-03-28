#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>

// Include the XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "public/include/XMP.hpp"
#include "public/include/XMP.incl_cpp"

// Helper: callback that accumulates output into a string
static XMP_Status AccumulateOutput(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    if (refCon == nullptr || buffer == nullptr) return -1;
    std::string* output = static_cast<std::string*>(refCon);
    output->append(buffer, bufferSize);
    return 0;
}

// Helper: callback that fails after a certain number of bytes
struct FailAfterN {
    std::string output;
    size_t maxBytes;
    size_t written;
};

static XMP_Status FailAfterNCallback(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    FailAfterN* ctx = static_cast<FailAfterN*>(refCon);
    if (ctx->written + bufferSize > ctx->maxBytes) {
        return -1;  // Simulate failure
    }
    ctx->output.append(buffer, bufferSize);
    ctx->written += bufferSize;
    return 0;
}

class XMPMetaDumpTest_2138 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "Failed to initialize XMP SDK";
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        meta_ = SXMPMeta();
    }

    SXMPMeta meta_;
};

// Test that DumpObject works with normal ASCII property values
TEST_F(XMPMetaDumpTest_2138, DumpWithNormalAsciiValue_2138) {
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Creator", "TestCreator");
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("TestCreator"), std::string::npos);
}

// Test DumpObject with empty metadata produces some output (header at minimum)
TEST_F(XMPMetaDumpTest_2138, DumpWithEmptyMeta_2138) {
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    // Even empty metadata should produce some dump output
}

// Test that DumpObject handles property values containing control characters
// Control characters (< 0x20, not tab/LF) should be hex-encoded in the dump
TEST_F(XMPMetaDumpTest_2138, DumpWithControlCharactersInValue_2138) {
    // String with a control character (0x01)
    std::string valueWithControl = "Hello";
    valueWithControl += '\x01';
    valueWithControl += "World";
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", valueWithControl.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    // The control char should appear as hex in angle brackets
    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("World"), std::string::npos);
}

// Test that DumpObject handles high-byte characters (> 0x7F) with hex encoding
TEST_F(XMPMetaDumpTest_2138, DumpWithHighByteCharactersInValue_2138) {
    std::string valueWithHighByte = "Test";
    valueWithHighByte += '\x80';
    valueWithHighByte += '\xFF';
    valueWithHighByte += "End";
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", valueWithHighByte.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Test"), std::string::npos);
    EXPECT_NE(output.find("End"), std::string::npos);
}

// Test that tab characters in values are treated as normal (not hex-encoded)
TEST_F(XMPMetaDumpTest_2138, DumpWithTabCharacterInValue_2138) {
    std::string valueWithTab = "Hello\tWorld";
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", valueWithTab.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    // Tab is treated as normal, so "Hello\tWorld" should appear as-is
    EXPECT_NE(output.find("Hello\tWorld"), std::string::npos);
}

// Test that linefeed characters in values are treated as normal (not hex-encoded)
TEST_F(XMPMetaDumpTest_2138, DumpWithLinefeedCharacterInValue_2138) {
    std::string valueWithLF = "Hello\nWorld";
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", valueWithLF.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello\nWorld"), std::string::npos);
}

// Test DumpObject with a failing output proc returns non-zero status
TEST_F(XMPMetaDumpTest_2138, DumpWithFailingOutputProc_2138) {
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Creator", "TestValue");
    
    FailAfterN ctx;
    ctx.maxBytes = 5;  // Allow only 5 bytes before failing
    ctx.written = 0;
    
    XMP_Status status = meta_.DumpObject(FailAfterNCallback, &ctx);
    
    // The proc should eventually fail, returning non-zero
    EXPECT_NE(status, 0);
}

// Test that DumpObject handles a value that is entirely control characters
TEST_F(XMPMetaDumpTest_2138, DumpWithAllControlChars_2138) {
    std::string allControl;
    allControl += '\x01';
    allControl += '\x02';
    allControl += '\x03';
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", allControl.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
    // Control chars should be in angle brackets with hex representation
    EXPECT_NE(output.find("<"), std::string::npos);
    EXPECT_NE(output.find(">"), std::string::npos);
}

// Test DumpObject with an empty string property value
TEST_F(XMPMetaDumpTest_2138, DumpWithEmptyPropertyValue_2138) {
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", "");
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
}

// Test DumpObject with mixed normal, control, and high-byte characters
TEST_F(XMPMetaDumpTest_2138, DumpWithMixedCharacters_2138) {
    std::string mixed = "A";
    mixed += '\x01';  // control
    mixed += "B";
    mixed += '\x80';  // high byte
    mixed += "C";
    mixed += '\t';    // tab (normal)
    mixed += "D";
    mixed += '\n';    // LF (normal)
    mixed += "E";
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", mixed.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
}

// Test DumpObject with multiple properties
TEST_F(XMPMetaDumpTest_2138, DumpWithMultipleProperties_2138) {
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Creator", "Alice");
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", "A test description");
    meta_.SetProperty("http://purl.org/dc/elements/1.1/", "title", "MyTitle");
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("A test description"), std::string::npos);
    EXPECT_NE(output.find("MyTitle"), std::string::npos);
}

// Test DumpObject with a long string value
TEST_F(XMPMetaDumpTest_2138, DumpWithLongStringValue_2138) {
    std::string longValue(1000, 'X');
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", longValue.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
    EXPECT_FALSE(output.empty());
}

// Test that null byte in value is handled as a control character
TEST_F(XMPMetaDumpTest_2138, DumpWithNullByteInValue_2138) {
    // Create a value with embedded null - note SetProperty with length
    std::string valueWithNull = "AB";
    valueWithNull += '\x00';
    valueWithNull += "CD";
    
    // Use SetProperty with explicit length to include the null byte
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", valueWithNull.c_str(), 
                       static_cast<XMP_OptionBits>(0));
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
}

// Test DumpObject with only printable ASCII characters (boundary: space 0x20 and tilde 0x7E)
TEST_F(XMPMetaDumpTest_2138, DumpWithBoundaryPrintableChars_2138) {
    std::string boundary;
    boundary += ' ';    // 0x20 - should be normal
    boundary += '~';    // 0x7E - should be normal
    boundary += '\x7F'; // 0x7F - should be normal (<=0x7F and >=0x20)
    
    meta_.SetProperty("http://ns.adobe.com/xap/1.0/", "Description", boundary.c_str());
    
    std::string output;
    XMP_Status status = meta_.DumpObject(AccumulateOutput, &output);
    
    EXPECT_EQ(status, 0);
}
