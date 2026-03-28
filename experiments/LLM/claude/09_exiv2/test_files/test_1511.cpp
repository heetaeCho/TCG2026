#include <gtest/gtest.h>
#include <cstring>
#include <memory>

#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewOlympusMnTest_1511 : public ::testing::Test {
protected:
    static constexpr uint16_t testTag = 0x927c;
    static constexpr IfdId testGroup = IfdId::exifId;
    static constexpr IfdId testMnGroup = IfdId::olympusId;
};

// Test: nullptr data with size 0 should return nullptr (too small for any signature)
TEST_F(NewOlympusMnTest_1511, NullDataZeroSize_1511) {
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, nullptr, 0, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: Data too small (less than 10 bytes) and also too small for OlympusMnHeader
TEST_F(NewOlympusMnTest_1511, TooSmallForAnySignature_1511) {
    byte data[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 5, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: OM SYSTEM signature with exactly 14 bytes but total size too small
TEST_F(NewOlympusMnTest_1511, OMSystemSignatureTooSmall_1511) {
    // "OM SYSTEM\0\0\0II" is 14 bytes
    const char sig[] = "OM SYSTEM\0\0\0II";
    // Size is 14, which is >= 14 for signature match, but likely < sizeOfSignature() + 18
    byte data[14];
    std::memcpy(data, sig, 14);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 14, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: OM SYSTEM signature with sufficient size should return non-null
TEST_F(NewOlympusMnTest_1511, OMSystemSignatureSufficientSize_1511) {
    // "OM SYSTEM\0\0\0II" is 14 bytes
    const char sig[] = "OM SYSTEM\0\0\0II";
    // Make buffer large enough: signature + plenty of extra bytes
    byte data[256];
    std::memset(data, 0, sizeof(data));
    std::memcpy(data, sig, 14);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: OLYMPUS\0II signature (10 bytes) with sufficient size should return non-null
TEST_F(NewOlympusMnTest_1511, Olympus2SignatureSufficientSize_1511) {
    // "OLYMPUS\0II" is 10 bytes
    const char sig[] = "OLYMPUS\0II";
    byte data[256];
    std::memset(data, 0, sizeof(data));
    std::memcpy(data, sig, 10);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: OLYMPUS\0II signature but data too small for Olympus2MnHeader
TEST_F(NewOlympusMnTest_1511, Olympus2SignatureTooSmall_1511) {
    const char sig[] = "OLYMPUS\0II";
    byte data[10];
    std::memcpy(data, sig, 10);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 10, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: Non-matching signature with >= 10 bytes should fall through to OlympusMnHeader path
TEST_F(NewOlympusMnTest_1511, NonMatchingSignatureSufficientSize_1511) {
    byte data[256];
    std::memset(data, 0, sizeof(data));
    // Not matching "OLYMPUS\0II" or "OM SYSTEM..."
    std::memcpy(data, "SOMETHING_", 10);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Non-matching signature with size < OlympusMnHeader::sizeOfSignature() + 18
// Data is >= 10 but doesn't match OLYMPUS\0II, and is small
TEST_F(NewOlympusMnTest_1511, NonMatchingSignatureSmallSize_1511) {
    byte data[10];
    std::memset(data, 'A', sizeof(data));
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 10, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: Data less than 10 bytes but enough for OlympusMnHeader path with sufficient total size
TEST_F(NewOlympusMnTest_1511, SmallNonMatchingWithSufficientTotal_1511) {
    byte data[256];
    std::memset(data, 0xFF, sizeof(data));
    // Size >= 10 check but string doesn't match "OLYMPUS\0II"
    // This goes into the non-OLYMPUS branch (old Olympus)
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: OM SYSTEM partial match (only 13 bytes matching) with sufficient size
TEST_F(NewOlympusMnTest_1511, OMSystemPartialMatch_1511) {
    byte data[256];
    std::memset(data, 0, sizeof(data));
    // Write almost OM SYSTEM but corrupt last byte
    const char sig[] = "OM SYSTEM\0\0\0IX";
    std::memcpy(data, sig, 14);
    // This won't match OM SYSTEM signature (last two bytes should be "II")
    // Also check if it matches OLYMPUS\0II - it doesn't
    // So it falls through to non-matching path
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Exactly at boundary where size == 14 for OM SYSTEM check but doesn't match
TEST_F(NewOlympusMnTest_1511, BoundarySize14NonOMSystem_1511) {
    byte data[14];
    std::memset(data, 'X', sizeof(data));
    // Doesn't match OM SYSTEM, doesn't match OLYMPUS\0II
    // Falls to old Olympus path, but size=14 might be too small
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 14, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: ByteOrder parameter - big endian
TEST_F(NewOlympusMnTest_1511, BigEndianOMSystem_1511) {
    const char sig[] = "OM SYSTEM\0\0\0II";
    byte data[256];
    std::memset(data, 0, sizeof(data));
    std::memcpy(data, sig, 14);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test: BigEndian with OLYMPUS\0II signature
TEST_F(NewOlympusMnTest_1511, BigEndianOlympus2_1511) {
    const char sig[] = "OLYMPUS\0II";
    byte data[256];
    std::memset(data, 0, sizeof(data));
    std::memcpy(data, sig, 10);
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, sizeof(data), bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Size exactly at edge for non-matching signature path
TEST_F(NewOlympusMnTest_1511, EdgeSizeNonMatching_1511) {
    // We test sizes around the boundary. The exact threshold depends on
    // OlympusMnHeader::sizeOfSignature() + 18 which we don't know exactly.
    // But we know that size=10 returns nullptr, so try incrementally larger.
    byte data[256];
    std::memset(data, 'Z', sizeof(data));
    
    // With a large enough buffer, non-matching should succeed
    auto result = newOlympusMn(testTag, testGroup, testMnGroup, data, 256, littleEndian);
    EXPECT_NE(result, nullptr);
}
