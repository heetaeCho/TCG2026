#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMnHeaderTest_1487 : public ::testing::Test {
protected:
    PentaxMnHeader header_;
};

// Test that reading with nullptr data returns false
TEST_F(PentaxMnHeaderTest_1487, ReadNullDataReturnsFalse_1487) {
    bool result = header_.read(nullptr, 10, littleEndian);
    EXPECT_FALSE(result);
}

// Test that reading with zero size returns false
TEST_F(PentaxMnHeaderTest_1487, ReadZeroSizeReturnsFalse_1487) {
    const byte data[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that reading with size less than signature size returns false
TEST_F(PentaxMnHeaderTest_1487, ReadSizeTooSmallReturnsFalse_1487) {
    const byte data[] = {0x41, 0x4F};
    bool result = header_.read(data, 2, littleEndian);
    EXPECT_FALSE(result);
}

// Test that reading with valid "AOC" signature succeeds
TEST_F(PentaxMnHeaderTest_1487, ReadValidAOCSignatureReturnsTrue_1487) {
    // "AOC" followed by padding bytes - the Pentax signature is "AOC\0"
    const byte data[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test that reading with invalid signature returns false
TEST_F(PentaxMnHeaderTest_1487, ReadInvalidSignatureReturnsFalse_1487) {
    const byte data[] = {0x58, 0x59, 0x5A, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that reading with partially matching signature returns false
TEST_F(PentaxMnHeaderTest_1487, ReadPartiallyMatchingSignatureReturnsFalse_1487) {
    // "AO" matches but third byte doesn't
    const byte data[] = {0x41, 0x4F, 0x44, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test with big endian byte order (should still work based on signature comparison)
TEST_F(PentaxMnHeaderTest_1487, ReadValidSignatureBigEndian_1487) {
    const byte data[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test with invalid signature and big endian
TEST_F(PentaxMnHeaderTest_1487, ReadInvalidSignatureBigEndian_1487) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_FALSE(result);
}

// Test that reading exactly at the minimum required size works with valid signature
TEST_F(PentaxMnHeaderTest_1487, ReadExactMinimumSizeValidSignature_1487) {
    // sizeOfSignature() is likely 4 based on "AOC\0"
    const byte data[] = {0x41, 0x4F, 0x43, 0x00};
    bool result = header_.read(data, 4, littleEndian);
    // This depends on sizeOfSignature() - if it's <= 4, this should succeed
    // We test it to observe the boundary behavior
    EXPECT_TRUE(result);
}

// Test size exactly 3 - which may be below sizeOfSignature
TEST_F(PentaxMnHeaderTest_1487, ReadSizeThreeReturnsFalse_1487) {
    const byte data[] = {0x41, 0x4F, 0x43};
    bool result = header_.read(data, 3, littleEndian);
    // sizeOfSignature() is likely > 3, so this should fail
    EXPECT_FALSE(result);
}

// Test reading with size 1
TEST_F(PentaxMnHeaderTest_1487, ReadSizeOneReturnsFalse_1487) {
    const byte data[] = {0x41};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that nullptr with size > 0 returns false
TEST_F(PentaxMnHeaderTest_1487, ReadNullDataNonZeroSizeReturnsFalse_1487) {
    bool result = header_.read(nullptr, 100, bigEndian);
    EXPECT_FALSE(result);
}

// Test reading with large valid buffer containing correct signature
TEST_F(PentaxMnHeaderTest_1487, ReadLargeBufferValidSignature_1487) {
    std::vector<byte> data(1024, 0x00);
    data[0] = 0x41; // 'A'
    data[1] = 0x4F; // 'O'
    data[2] = 0x43; // 'C'
    data[3] = 0x00;
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test calling read multiple times - second call with valid data
TEST_F(PentaxMnHeaderTest_1487, ReadMultipleTimesLastCallDeterminesState_1487) {
    const byte invalidData[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result1 = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result1);

    const byte validData[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result2 = header_.read(validData, sizeof(validData), littleEndian);
    EXPECT_TRUE(result2);
}

// Test calling read multiple times - second call with invalid data
TEST_F(PentaxMnHeaderTest_1487, ReadMultipleTimesSecondCallInvalid_1487) {
    const byte validData[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result1 = header_.read(validData, sizeof(validData), littleEndian);
    EXPECT_TRUE(result1);

    const byte invalidData[] = {0x58, 0x59, 0x5A, 0x00, 0x00, 0x00};
    bool result2 = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result2);
}
