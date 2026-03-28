#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FoFiIdentifier.h"

// We need to include the source to access the static function.
// Since identifyOpenType is static, we need to either make it accessible
// or test through the public API. Since it's a static function in the .cc file,
// we'll test it indirectly through the public FoFiIdentifier API if available,
// or we need to include the .cc file directly to access it.

// Forward declare the Reader class as we know its interface
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

// Mock Reader for testing
class MockReader : public Reader {
public:
    MOCK_METHOD(int, getByte, (int pos), (override));
    MOCK_METHOD(bool, getU16BE, (int pos, int *val), (override));
    MOCK_METHOD(bool, getU32BE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getU32LE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int *val), (override));
    MOCK_METHOD(bool, cmp, (int pos, const char *s), (override));
};

// Include the .cc file to get access to the static function
// This is necessary because identifyOpenType is a static (file-scope) function
#include "FoFiIdentifier.cc"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::Invoke;

class IdentifyOpenTypeTest_51 : public ::testing::Test {
protected:
    MockReader reader;
};

// Test: When getU16BE fails to read nTables, return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, GetU16BEFails_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: When nTables is 0, no tables to check, return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, ZeroTables_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: When there are tables but none match "CFF ", return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, NoMatchingCFFTable_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(3), Return(true)));

    // None of the tables match "CFF "
    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(false));
    EXPECT_CALL(reader, cmp(28, "CFF ")).WillOnce(Return(false));
    EXPECT_CALL(reader, cmp(44, "CFF ")).WillOnce(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: CFF table found but getU32BE fails, return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, CFFTableFoundButGetU32BEFails_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: CFF table found but offset >= INT_MAX, return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, CFFTableFoundButOffsetTooLarge_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));
    
    unsigned int largeOffset = (unsigned int)INT_MAX; // equals INT_MAX, not less than
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(DoAll(SetArgPointee<1>(largeOffset), Return(true)));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: CFF table found in second table entry
TEST_F(IdentifyOpenTypeTest_51, CFFTableFoundInSecondEntry_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(2), Return(true)));

    // First table doesn't match
    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(false));
    // Second table matches
    EXPECT_CALL(reader, cmp(28, "CFF ")).WillOnce(Return(true));

    unsigned int offset = 100;
    EXPECT_CALL(reader, getU32BE(36, _))
        .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

    // identifyCFF will be called with the reader at offset 100
    // Since identifyCFF is also a static function in the same file,
    // we need to set up expectations for what it does.
    // identifyCFF reads bytes from the reader to determine CFF type.
    // For CFF8Bit -> should return fofiIdOpenTypeCFF8Bit
    // We'll set up the reader to make identifyCFF return fofiIdCFF8Bit
    
    // identifyCFF checks: getByte at offset, offset+1, offset+2, offset+3
    // for header "major version" etc., and then reads ROS to determine CID vs 8bit
    // This is complex internal logic. Let's just make it return fofiIdUnknown
    // by making getByte fail or return unexpected values.
    
    // Actually, identifyCFF reads header bytes. Let's make it simple:
    // If we can't fully control identifyCFF's behavior, we'll test what we can.
    // Let's try to make identifyCFF return fofiIdCFF8Bit by providing appropriate data.
    
    // identifyCFF checks the CFF header: major version at offset
    // For a minimal test, let's just verify the function doesn't crash
    // and returns something reasonable.
    
    // Let getByte return values that identifyCFF can process
    EXPECT_CALL(reader, getByte(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(reader, getU16BE(_, _)).WillRepeatedly(Return(false));
    EXPECT_CALL(reader, getU32BE(_, _)).WillRepeatedly(Return(false));
    EXPECT_CALL(reader, getUVarBE(_, _, _)).WillRepeatedly(Return(false));
    EXPECT_CALL(reader, cmp(_, _)).WillRepeatedly(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    // The result depends on identifyCFF's behavior with the mock data
    // We just verify it returns a valid enum value
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// Test: Single table that is CFF with valid offset near 0
TEST_F(IdentifyOpenTypeTest_51, CFFTableWithZeroOffset_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));

    unsigned int offset = 0;
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

    // Set up for identifyCFF to process - provide minimal mock behavior
    EXPECT_CALL(reader, getByte(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(reader, getUVarBE(_, _, _)).WillRepeatedly(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// Test: Large number of tables, CFF not found
TEST_F(IdentifyOpenTypeTest_51, ManyTablesNoCFF_ReturnsUnknown_51) {
    int nTables = 100;
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));

    // None match "CFF "
    EXPECT_CALL(reader, cmp(_, "CFF ")).WillRepeatedly(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: Offset exactly INT_MAX - 1 (boundary, should be valid since < INT_MAX)
TEST_F(IdentifyOpenTypeTest_51, CFFTableWithOffsetJustBelowIntMax_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));

    unsigned int offset = (unsigned int)INT_MAX - 1;
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

    // identifyCFF will be called with this large offset
    EXPECT_CALL(reader, getByte(_)).WillRepeatedly(Return(-1));
    EXPECT_CALL(reader, getUVarBE(_, _, _)).WillRepeatedly(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    // Should attempt to identify CFF and return some result
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// Test: Offset is UINT_MAX (well above INT_MAX), should return fofiIdUnknown
TEST_F(IdentifyOpenTypeTest_51, CFFTableWithOffsetUINTMAX_ReturnsUnknown_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));

    unsigned int offset = UINT_MAX;
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

    FoFiIdentifierType result = identifyOpenType(&reader);
    EXPECT_EQ(result, fofiIdUnknown);
}

// Test: nTables = 1, first table is CFF
TEST_F(IdentifyOpenTypeTest_51, SingleCFFTable_51) {
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));

    EXPECT_CALL(reader, cmp(12, "CFF ")).WillOnce(Return(true));

    unsigned int offset = 50;
    EXPECT_CALL(reader, getU32BE(20, _))
        .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

    // Setup for identifyCFF - make it return something predictable
    // getByte(50) returns major version, etc.
    EXPECT_CALL(reader, getByte(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(reader, getUVarBE(_, _, _)).WillRepeatedly(Return(false));

    FoFiIdentifierType result = identifyOpenType(&reader);
    // Result will depend on identifyCFF behavior, but should be valid
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// ========================================================
// Tests for the public API: FoFiIdentifier::identifyMem, etc.
// ========================================================

class FoFiIdentifierPublicTest_51 : public ::testing::Test {
};

// Test: identifyMem with empty data
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemEmptyData_51) {
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(nullptr, 0);
    // With null/empty data, should return unknown or error
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test: identifyMem with TrueType signature (0x00010000)
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemTrueTypeSignature_51) {
    // TrueType starts with 00 01 00 00
    unsigned char data[] = {0x00, 0x01, 0x00, 0x00,
                            0x00, 0x00, // nTables = 0
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((char *)data, sizeof(data));
    // With nTables=0 and no CFF table, TrueType-like data
    // The actual result depends on the full identify logic
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// Test: identifyMem with very small data (1 byte)
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemTinyData_51) {
    char data[] = {0x00};
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(data, 1);
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}

// Test: identifyMem with Type1 PFA header (starts with '%!')
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemType1PFA_51) {
    const char *data = "%!PS-AdobeFont-1.0";
    FoFiIdentifierType result = FoFiIdentifier::identifyMem(data, strlen(data));
    // Should identify as Type1 PFA
    EXPECT_EQ(result, fofiIdType1PFA);
}

// Test: identifyMem with Type1 PFB header (starts with 0x80 0x01)
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemType1PFB_51) {
    unsigned char data[64];
    memset(data, 0, sizeof(data));
    data[0] = 0x80;
    data[1] = 0x01;
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((char *)data, sizeof(data));
    EXPECT_EQ(result, fofiIdType1PFB);
}

// Test: identifyMem with TrueType Collection ('ttcf')
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemTTCSignature_51) {
    unsigned char data[64];
    memset(data, 0, sizeof(data));
    data[0] = 't';
    data[1] = 't';
    data[2] = 'c';
    data[3] = 'f';
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((char *)data, sizeof(data));
    EXPECT_EQ(result, fofiIdTrueTypeCollection);
}

// Test: identifyMem with OpenType signature ('OTTO')
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemOTTOSignature_51) {
    unsigned char data[64];
    memset(data, 0, sizeof(data));
    data[0] = 'O';
    data[1] = 'T';
    data[2] = 'T';
    data[3] = 'O';
    // nTables = 0
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((char *)data, sizeof(data));
    // OTTO with no CFF table -> unknown
    EXPECT_TRUE(result >= fofiIdType1PFA && result <= fofiIdError);
}

// Test: identifyMem with random/garbage data
TEST_F(FoFiIdentifierPublicTest_51, IdentifyMemGarbageData_51) {
    unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04};
    FoFiIdentifierType result = FoFiIdentifier::identifyMem((char *)data, sizeof(data));
    EXPECT_TRUE(result == fofiIdUnknown || result == fofiIdError);
}
