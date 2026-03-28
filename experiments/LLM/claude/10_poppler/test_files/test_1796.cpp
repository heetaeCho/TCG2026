#include <gtest/gtest.h>
#include <cstring>

// Include necessary NSS headers for SECItem
#include <seccomon.h>
#include <secitem.h>

// Include GooString header
#include "goo/GooString.h"

// We need to access the static function. Since it's static in the .cc file,
// we'll need to either include the .cc file or re-declare the function for testing.
// Since the constraint says we treat implementation as black box and only test the interface,
// we include the source file to access the static function.
// In practice, this is a common technique for testing static (file-scope) functions.

// Forward declare or include to get access to the static function
// We replicate the signature since we need to call it
static GooString SECItemToGooString(const SECItem &secItem);

// Include the implementation file to get the static function
#include "poppler/NSSCryptoSignBackend.cc"

class SECItemToGooStringTest_1796 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Normal operation with typical data
TEST_F(SECItemToGooStringTest_1796, NormalDataConversion_1796)
{
    const char *testData = "Hello, World!";
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = (unsigned char *)testData;
    secItem.len = strlen(testData);

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), (int)strlen(testData));
    EXPECT_EQ(strcmp(result.c_str(), testData), 0);
}

// Test: Empty SECItem (zero length)
TEST_F(SECItemToGooStringTest_1796, EmptyData_1796)
{
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = nullptr;
    secItem.len = 0;

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), 0);
}

// Test: Single byte data
TEST_F(SECItemToGooStringTest_1796, SingleByteData_1796)
{
    unsigned char singleByte = 'A';
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = &singleByte;
    secItem.len = 1;

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), 1);
    EXPECT_EQ(result.c_str()[0], 'A');
}

// Test: Binary data with embedded null bytes
TEST_F(SECItemToGooStringTest_1796, BinaryDataWithNullBytes_1796)
{
    unsigned char binaryData[] = { 0x00, 0x01, 0x02, 0x00, 0x03 };
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = binaryData;
    secItem.len = sizeof(binaryData);

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), 5);
    EXPECT_EQ((unsigned char)result.c_str()[0], 0x00);
    EXPECT_EQ((unsigned char)result.c_str()[1], 0x01);
    EXPECT_EQ((unsigned char)result.c_str()[2], 0x02);
    EXPECT_EQ((unsigned char)result.c_str()[3], 0x00);
    EXPECT_EQ((unsigned char)result.c_str()[4], 0x03);
}

// Test: Large data
TEST_F(SECItemToGooStringTest_1796, LargeData_1796)
{
    const size_t dataSize = 10000;
    std::vector<unsigned char> largeData(dataSize, 0x42);

    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = largeData.data();
    secItem.len = dataSize;

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), (int)dataSize);
    for (int i = 0; i < result.getLength(); i++) {
        EXPECT_EQ((unsigned char)result.c_str()[i], 0x42);
    }
}

// Test: Data with all byte values (0x00 to 0xFF)
TEST_F(SECItemToGooStringTest_1796, AllByteValues_1796)
{
    unsigned char allBytes[256];
    for (int i = 0; i < 256; i++) {
        allBytes[i] = (unsigned char)i;
    }

    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = allBytes;
    secItem.len = 256;

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), 256);
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ((unsigned char)result.c_str()[i], (unsigned char)i);
    }
}

// Test: Data content is correctly preserved (not just length)
TEST_F(SECItemToGooStringTest_1796, DataContentPreserved_1796)
{
    const char *testStr = "Test string with special chars: !@#$%^&*()";
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = (unsigned char *)testStr;
    secItem.len = strlen(testStr);

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), (int)strlen(testStr));
    EXPECT_EQ(memcmp(result.c_str(), testStr, strlen(testStr)), 0);
}

// Test: Partial data from a larger buffer
TEST_F(SECItemToGooStringTest_1796, PartialBufferConversion_1796)
{
    const char *fullData = "Hello, World!";
    SECItem secItem;
    secItem.type = siBuffer;
    secItem.data = (unsigned char *)fullData;
    secItem.len = 5; // Only "Hello"

    GooString result = SECItemToGooString(secItem);

    EXPECT_EQ(result.getLength(), 5);
    EXPECT_EQ(memcmp(result.c_str(), "Hello", 5), 0);
}
