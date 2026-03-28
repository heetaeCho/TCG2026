#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FoFiIdentifier.h"

// We need to include the header that declares the public API
// The identify function is static in the .cc file, so we need to test through
// the public API. Let's check what public functions are available.
// Based on the FoFiIdentifier.h, there should be public functions like
// FoFiIdentifier::identifyMem, FoFiIdentifier::identifyFile, etc.

// Since the identify function is static (file-local), we need to test it
// through the public interface. Let's create a mock Reader and test through
// the available public API.

// First, let's define the Reader mock based on the known interface
class Reader {
public:
    Reader() = default;
    Reader(const Reader &) = delete;
    Reader &operator=(const Reader &other) = delete;
    virtual ~Reader() = default;

    virtual int getByte(int pos) = 0;
    virtual bool getU16BE(int pos, int *val) = 0;
    virtual bool getU32BE(int pos, unsigned int *val) = 0;
    virtual bool getU32LE(int pos, unsigned int *val) = 0;
    virtual bool getUVarBE(int pos, int size, unsigned int *val) = 0;
    virtual bool cmp(int pos, const char *s) = 0;
};

class MockReader : public Reader {
public:
    MOCK_METHOD(int, getByte, (int pos), (override));
    MOCK_METHOD(bool, getU16BE, (int pos, int *val), (override));
    MOCK_METHOD(bool, getU32BE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getU32LE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int *val), (override));
    MOCK_METHOD(bool, cmp, (int pos, const char *s), (override));
};

// Since identify() is a static function in the .cc file, we can't call it directly.
// We need to test through the public API. The public API likely includes
// FoFiIdentifier::identifyMem() which takes a buffer.
// Let's test using FoFiIdentifier::identifyMem if available.

// However, since we're asked to test the identify function and we have the Reader
// interface, let's assume we can access it or recreate the scenario.
// We'll test using the public memory-based identification function.

extern FoFiIdentifierType FoFiIdentifier_identifyMem(const char *file, int len);

// Alternative: if the public API is different, we test with buffer-based approach
// Let's create tests that exercise the identify logic through identifyMem

class FoFiIdentifierTest_50 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test Type1 PFA identification with "%!PS-AdobeFont-1"
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFA_AdobeFont_50) {
    const char data[] = "%!PS-AdobeFont-1.0 TestFont";
    FoFiIdentifierType result = FoFiIdentifier_identifyMem(data, sizeof(data) - 1);
    EXPECT_EQ(result, fofiIdType1PFA);
}

// Test Type1 PFA identification with "%!FontType1"
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFA_FontType1_50) {
    const char data[] = "%!FontType1-1.0 TestFont";
    FoFiIdentifierType result = FoFiIdentifier_identifyMem(data, sizeof(data) - 1);
    EXPECT_EQ(result, fofiIdType1PFA);
}

// Test Type1 PFB identification
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_50) {
    // PFB starts with 0x80 0x01, then 4-byte LE length, then PFA header
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    // Length = 20 (LE), which is >= 16
    data[2] = 20;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    // Then "%!PS-AdobeFont-1" at offset 6
    const char *header = "%!PS-AdobeFont-1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test Type1 PFB with FontType1 header
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_FontType1_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    // Length = 15 (LE), which is >= 11
    data[2] = 15;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char *header = "%!FontType1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test TrueType identification (0x00 0x01 0x00 0x00)
TEST_F(FoFiIdentifierTest_50, IdentifyTrueType_Standard_50) {
    unsigned char data[64] = {0};
    data[0] = 0x00;
    data[1] = 0x01;
    data[2] = 0x00;
    data[3] = 0x00;
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueType);
}

// Test TrueType identification with 'true' magic
TEST_F(FoFiIdentifierTest_50, IdentifyTrueType_TrueMagic_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x72; // 'r'
    data[2] = 0x75; // 'u'
    data[3] = 0x65; // 'e'
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueType);
}

// Test TrueType Collection identification ('ttcf')
TEST_F(FoFiIdentifierTest_50, IdentifyTrueTypeCollection_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x74; // 't'
    data[2] = 0x63; // 'c'
    data[3] = 0x66; // 'f'
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueTypeCollection);
}

// Test Unknown identification
TEST_F(FoFiIdentifierTest_50, IdentifyUnknown_50) {
    unsigned char data[64];
    memset(data, 0xFF, sizeof(data));
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test empty/minimal data
TEST_F(FoFiIdentifierTest_50, IdentifyEmptyData_50) {
    const char data[] = "";
    FoFiIdentifierType result = FoFiIdentifier_identifyMem(data, 0);
    // With zero length, should return unknown or error
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test PFB with length too small for AdobeFont header (n < 16) but valid for FontType1
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_SmallLength_FontType1_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    // Length = 11 (LE) - just enough for FontType1
    data[2] = 11;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char *header = "%!FontType1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test PFB with length too small for both headers
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_TooSmallLength_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    // Length = 5 (LE) - too small for either header
    data[2] = 5;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    // Should not match PFB, might fall through to other checks
    EXPECT_NE(result, fofiIdType1PFB);
}

// Test OTTO (OpenType) identification
TEST_F(FoFiIdentifierTest_50, IdentifyOpenType_OTTO_50) {
    // 'OTTO' magic followed by enough data for OpenType parsing
    unsigned char data[256] = {0};
    data[0] = 0x4f; // 'O'
    data[1] = 0x54; // 'T'
    data[2] = 0x54; // 'T'
    data[3] = 0x4f; // 'O'
    // The rest depends on identifyOpenType internals
    // We just verify it doesn't crash and returns a valid type
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 256);
    // Should return one of the OpenType types or error/unknown
    EXPECT_TRUE(result == fofiIdOpenTypeCFF8Bit || result == fofiIdOpenTypeCFFCID || 
                result == fofiIdUnknown || result == fofiIdError);
}

// Test CFF identification (starts with 0x01 0x00)
TEST_F(FoFiIdentifierTest_50, IdentifyCFF_Offset0_50) {
    unsigned char data[256] = {0};
    data[0] = 0x01;
    data[1] = 0x00;
    // Minimal CFF data - the rest depends on identifyCFF internals
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 256);
    // Should return one of the CFF types or unknown/error
    EXPECT_TRUE(result == fofiIdCFF8Bit || result == fofiIdCFFCID || 
                result == fofiIdUnknown || result == fofiIdError);
}

// Test CFF identification at offset 1 (byte[1]=0x01, byte[2]=0x00)
TEST_F(FoFiIdentifierTest_50, IdentifyCFF_Offset1_50) {
    unsigned char data[256] = {0};
    data[0] = 0x00; // Not matching other patterns
    data[1] = 0x01;
    data[2] = 0x00;
    // Make sure byte[3] is not 0x00 to avoid TrueType match
    data[3] = 0x01;
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 256);
    // Should return CFF type or unknown/error
    EXPECT_TRUE(result == fofiIdCFF8Bit || result == fofiIdCFFCID || 
                result == fofiIdUnknown || result == fofiIdError);
}

// Test that random data returns unknown
TEST_F(FoFiIdentifierTest_50, IdentifyRandomData_50) {
    unsigned char data[64] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42};
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test single byte data
TEST_F(FoFiIdentifierTest_50, IdentifySingleByte_50) {
    const char data[] = "X";
    FoFiIdentifierType result = FoFiIdentifier_identifyMem(data, 1);
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test that PFB with 0x80 first byte but wrong second byte doesn't match PFB
TEST_F(FoFiIdentifierTest_50, IdentifyNotPFB_WrongSecondByte_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x02; // Not 0x01
    data[2] = 0x42;
    data[3] = 0x42;
    
    FoFiIdentifierType result = FoFiIdentifier_identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdType1PFB);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include the public header
#include "FoFiIdentifier.h"

// The public API from FoFiIdentifier is likely:
// FoFiIdentifierType FoFiIdentifier::identifyMem(const char *file, int len);
// FoFiIdentifierType FoFiIdentifier::identifyFile(const char *fileName);
// FoFiIdentifierType FoFiIdentifier::identifyStream(int (*getChar)(void *data), void *data);

class FoFiIdentifierTest_50 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test Type1 PFA identification with "%!PS-AdobeFont-1"
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFA_AdobeFont_50) {
    const char data[] = "%!PS-AdobeFont-1.0 TestFont 001.001";
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(data, sizeof(data) - 1);
    EXPECT_EQ(result, fofiIdType1PFA);
}

// Test Type1 PFA identification with "%!FontType1"
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFA_FontType1_50) {
    const char data[] = "%!FontType1-1.0 TestFont";
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(data, sizeof(data) - 1);
    EXPECT_EQ(result, fofiIdType1PFA);
}

// Test Type1 PFB identification with AdobeFont header
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_AdobeFont_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    // Length = 20 in LE
    data[2] = 20; data[3] = 0; data[4] = 0; data[5] = 0;
    const char *header = "%!PS-AdobeFont-1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test Type1 PFB identification with FontType1 header
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_FontType1_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    data[2] = 15; data[3] = 0; data[4] = 0; data[5] = 0;
    const char *header = "%!FontType1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test PFB boundary: length exactly 16 for AdobeFont
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_ExactLength16_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    data[2] = 16; data[3] = 0; data[4] = 0; data[5] = 0;
    const char *header = "%!PS-AdobeFont-1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test PFB boundary: length exactly 11 for FontType1
TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_ExactLength11_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    data[2] = 11; data[3] = 0; data[4] = 0; data[5] = 0;
    const char *header = "%!FontType1";
    memcpy(data + 6, header, strlen(header));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test PFB with length too small
TEST_F(FoFiIdentifierTest_50, IdentifyPFB_LengthTooSmall_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    data[2] = 5; data[3] = 0; data[4] = 0; data[5] = 0;
    // Length 5 is too small for either header match
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdType1PFB);
}

// Test TrueType identification (standard magic)
TEST_F(FoFiIdentifierTest_50, IdentifyTrueType_Standard_50) {
    unsigned char data[64] = {0};
    data[0] = 0x00;
    data[1] = 0x01;
    data[2] = 0x00;
    data[3] = 0x00;
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueType);
}

// Test TrueType identification ('true' magic)
TEST_F(FoFiIdentifierTest_50, IdentifyTrueType_TrueMagic_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x72; // 'r'
    data[2] = 0x75; // 'u'
    data[3] = 0x65; // 'e'
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueType);
}

// Test TrueType Collection identification ('ttcf')
TEST_F(FoFiIdentifierTest_50, IdentifyTrueTypeCollection_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x74; // 't'
    data[2] = 0x63; // 'c'
    data[3] = 0x66; // 'f'
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdTrueTypeCollection);
}

// Test OpenType ('OTTO') identification
TEST_F(FoFiIdentifierTest_50, IdentifyOpenType_OTTO_50) {
    unsigned char data[256] = {0};
    data[0] = 0x4f; // 'O'
    data[1] = 0x54; // 'T'
    data[2] = 0x54; // 'T'
    data[3] = 0x4f; // 'O'
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 256);
    // Should be one of the OpenType results or unknown/error
    EXPECT_TRUE(result == fofiIdOpenTypeCFF8Bit || result == fofiIdOpenTypeCFFCID || 
                result == fofiIdUnknown || result == fofiIdError);
}

// Test CFF identification at offset 0
TEST_F(FoFiIdentifierTest_50, IdentifyCFF_Offset0_50) {
    unsigned char data[256] = {0};
    data[0] = 0x01;
    data[1] = 0x00;
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 256);
    EXPECT_TRUE(result == fofiIdCFF8Bit || result == fofiIdCFFCID || 
                result == fofiIdUnknown || result == fofiIdError);
}

// Test Unknown identification with random data
TEST_F(FoFiIdentifierTest_50, IdentifyUnknown_RandomData_50) {
    unsigned char data[64];
    memset(data, 0x42, sizeof(data));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test with all 0xFF bytes
TEST_F(FoFiIdentifierTest_50, IdentifyUnknown_AllFF_50) {
    unsigned char data[64];
    memset(data, 0xFF, sizeof(data));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test empty data
TEST_F(FoFiIdentifierTest_50, IdentifyEmptyData_50) {
    FoFiIdentifierType result = FoFiIdentifier::identifyMem("", 0);
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test single byte
TEST_F(FoFiIdentifierTest_50, IdentifySingleByte_50) {
    const char data[] = "X";
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(data, 1);
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test PFB with wrong second byte (not 0x01)
TEST_F(FoFiIdentifierTest_50, IdentifyNotPFB_WrongSecondByte_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x02;
    data[2] = 0x42;
    data[3] = 0x42;
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdType1PFB);
}

// Test PFB length boundary: n = 15 (< 16 for AdobeFont, >= 11 for FontType1 but wrong content)
TEST_F(FoFiIdentifierTest_50, IdentifyPFB_Length15_NoFontType1Match_50) {
    unsigned char data[64] = {0};
    data[0] = 0x80;
    data[1] = 0x01;
    data[2] = 15; data[3] = 0; data[4] = 0; data[5] = 0;
    // Fill with garbage - won't match either header
    memset(data + 6, 'A', 20);
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdType1PFB);
}

// Test that 'tru' + wrong 4th byte doesn't match TrueType 'true'
TEST_F(FoFiIdentifierTest_50, IdentifyNotTrueType_WrongFourthByte_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x72; // 'r'
    data[2] = 0x75; // 'u'
    data[3] = 0x66; // 'f' (not 'e')
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdTrueType);
}

// Test partial TrueType Collection magic ('ttc' + wrong 4th byte)
TEST_F(FoFiIdentifierTest_50, IdentifyNotTTC_WrongFourthByte_50) {
    unsigned char data[64] = {0};
    data[0] = 0x74; // 't'
    data[1] = 0x74; // 't'
    data[2] = 0x63; // 'c'
    data[3] = 0x67; // 'g' (not 'f')
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdTrueTypeCollection);
}

// Test partial OTTO magic
TEST_F(FoFiIdentifierTest_50, IdentifyNotOTTO_WrongFourthByte_50) {
    unsigned char data[64] = {0};
    data[0] = 0x4f; // 'O'
    data[1] = 0x54; // 'T'
    data[2] = 0x54; // 'T'
    data[3] = 0x50; // 'P' (not 'O')
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_NE(result, fofiIdOpenTypeCFF8Bit);
    EXPECT_NE(result, fofiIdOpenTypeCFFCID);
}

// Verify return type is valid enum value
TEST_F(FoFiIdentifierTest_50, IdentifyReturnsValidEnum_50) {
    unsigned char data[64];
    memset(data, 0xAB, sizeof(data));
    
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((const char *)data, 64);
    EXPECT_GE(result, fofiIdType1PFA);
    EXPECT_LE(result, fofiIdError);
}
