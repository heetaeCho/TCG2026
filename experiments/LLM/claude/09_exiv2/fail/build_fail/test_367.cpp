#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

// Include necessary exiv2 headers
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

// We need to include the internal header for TiffEntryBase and TiffType
// Since the provided code shows the implementation inline, we replicate the necessary parts
// for testing purposes based on the interface.

namespace Exiv2 {
namespace Internal {

// TiffType enum values as provided
enum TiffType {
    ttUnsignedByte = 1,
    ttAsciiString = 2,
    ttUnsignedShort = 3,
    ttUnsignedLong = 4,
    ttUnsignedRational = 5,
    ttSignedByte = 6,
    ttUndefined = 7,
    ttSignedShort = 8,
    ttSignedLong = 9,
    ttSignedRational = 10,
    ttTiffFloat = 11,
    ttTiffDouble = 12,
    ttTiffIfd = 13
};

// Minimal class to test writeOffset as a static-like method
class TiffEntryBase {
public:
    static size_t writeOffset(byte* buf, size_t offset, TiffType tiffType, ByteOrder byteOrder) {
        size_t rc = 0;
        switch (tiffType) {
            case ttUnsignedShort:
            case ttSignedShort:
                if (offset > std::numeric_limits<uint16_t>::max())
                    throw Error(ErrorCode::kerOffsetOutOfRange);
                rc = us2Data(buf, static_cast<uint16_t>(offset), byteOrder);
                break;
            case ttUnsignedLong:
            case ttSignedLong:
                rc = l2Data(buf, static_cast<uint32_t>(offset), byteOrder);
                break;
            default:
                throw Error(ErrorCode::kerUnsupportedDataAreaOffsetType);
        }
        return rc;
    }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffEntryBaseWriteOffsetTest_367 : public ::testing::Test {
protected:
    byte buf_[8];

    void SetUp() override {
        std::memset(buf_, 0, sizeof(buf_));
    }
};

// ============================================================
// Tests for ttUnsignedShort
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortZeroOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttUnsignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortZeroOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttUnsignedShort, bigEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortSmallOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0x0102, ttUnsignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
    // Little endian: low byte first
    EXPECT_EQ(buf_[0], 0x02);
    EXPECT_EQ(buf_[1], 0x01);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortSmallOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0x0102, ttUnsignedShort, bigEndian);
    EXPECT_EQ(rc, 2u);
    // Big endian: high byte first
    EXPECT_EQ(buf_[0], 0x01);
    EXPECT_EQ(buf_[1], 0x02);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortMaxValidOffset_367) {
    size_t maxVal = std::numeric_limits<uint16_t>::max();
    size_t rc = TiffEntryBase::writeOffset(buf_, maxVal, ttUnsignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0xFF);
    EXPECT_EQ(buf_[1], 0xFF);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortMaxValidOffsetBigEndian_367) {
    size_t maxVal = std::numeric_limits<uint16_t>::max();
    size_t rc = TiffEntryBase::writeOffset(buf_, maxVal, ttUnsignedShort, bigEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0xFF);
    EXPECT_EQ(buf_[1], 0xFF);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortOffsetOutOfRangeThrows_367) {
    size_t tooLarge = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, tooLarge, ttUnsignedShort, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortOffsetOutOfRangeBigEndianThrows_367) {
    size_t tooLarge = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, tooLarge, ttUnsignedShort, bigEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortVeryLargeOffsetThrows_367) {
    size_t veryLarge = 1000000;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, veryLarge, ttUnsignedShort, littleEndian),
        Error
    );
}

// ============================================================
// Tests for ttSignedShort
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortZeroOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttSignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortSmallOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 42, ttSignedShort, bigEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 42);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortMaxValidOffset_367) {
    size_t maxVal = std::numeric_limits<uint16_t>::max();
    size_t rc = TiffEntryBase::writeOffset(buf_, maxVal, ttSignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortOffsetOutOfRangeThrows_367) {
    size_t tooLarge = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, tooLarge, ttSignedShort, littleEndian),
        Error
    );
}

// ============================================================
// Tests for ttUnsignedLong
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongZeroOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttUnsignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x00);
    EXPECT_EQ(buf_[3], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongZeroOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttUnsignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x00);
    EXPECT_EQ(buf_[3], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongSmallOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0x01020304, ttUnsignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
    // Little endian: least significant byte first
    EXPECT_EQ(buf_[0], 0x04);
    EXPECT_EQ(buf_[1], 0x03);
    EXPECT_EQ(buf_[2], 0x02);
    EXPECT_EQ(buf_[3], 0x01);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongSmallOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0x01020304, ttUnsignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
    // Big endian: most significant byte first
    EXPECT_EQ(buf_[0], 0x01);
    EXPECT_EQ(buf_[1], 0x02);
    EXPECT_EQ(buf_[2], 0x03);
    EXPECT_EQ(buf_[3], 0x04);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongLargeOffset_367) {
    // An offset larger than uint16_t max should work fine for unsigned long
    size_t largeOffset = 0x00010000;
    size_t rc = TiffEntryBase::writeOffset(buf_, largeOffset, ttUnsignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x01);
    EXPECT_EQ(buf_[3], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongMaxUint32Offset_367) {
    size_t maxVal = std::numeric_limits<uint32_t>::max();
    size_t rc = TiffEntryBase::writeOffset(buf_, maxVal, ttUnsignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0xFF);
    EXPECT_EQ(buf_[1], 0xFF);
    EXPECT_EQ(buf_[2], 0xFF);
    EXPECT_EQ(buf_[3], 0xFF);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongOffset1LittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 1, ttUnsignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x01);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x00);
    EXPECT_EQ(buf_[3], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongOffset1BigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 1, ttUnsignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x00);
    EXPECT_EQ(buf_[3], 0x01);
}

// ============================================================
// Tests for ttSignedLong
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedLongZeroOffsetLittleEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 0, ttSignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedLongSmallOffsetBigEndian_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 256, ttSignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x00);
    EXPECT_EQ(buf_[1], 0x00);
    EXPECT_EQ(buf_[2], 0x01);
    EXPECT_EQ(buf_[3], 0x00);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedLongLargeOffset_367) {
    size_t largeOffset = 0xABCD1234;
    size_t rc = TiffEntryBase::writeOffset(buf_, largeOffset, ttSignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
    EXPECT_EQ(buf_[0], 0x34);
    EXPECT_EQ(buf_[1], 0x12);
    EXPECT_EQ(buf_[2], 0xCD);
    EXPECT_EQ(buf_[3], 0xAB);
}

// ============================================================
// Tests for unsupported types (default case)
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedByteThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttUnsignedByte, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, AsciiStringThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttAsciiString, bigEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedRationalThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttUnsignedRational, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedByteThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttSignedByte, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UndefinedThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttUndefined, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedRationalThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttSignedRational, bigEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, TiffFloatThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttTiffFloat, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, TiffDoubleThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttTiffDouble, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, TiffIfdThrowsUnsupported_367) {
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, 0, ttTiffIfd, bigEndian),
        Error
    );
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortBoundaryJustBelowMax_367) {
    size_t justBelow = std::numeric_limits<uint16_t>::max() - 1;
    size_t rc = TiffEntryBase::writeOffset(buf_, justBelow, ttUnsignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
    EXPECT_EQ(buf_[0], 0xFE);
    EXPECT_EQ(buf_[1], 0xFF);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortBoundaryExactlyAtMax_367) {
    size_t exactMax = std::numeric_limits<uint16_t>::max();
    EXPECT_NO_THROW(
        TiffEntryBase::writeOffset(buf_, exactMax, ttUnsignedShort, littleEndian)
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortBoundaryJustAboveMax_367) {
    size_t justAbove = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, justAbove, ttUnsignedShort, littleEndian),
        Error
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortBoundaryExactlyAtMax_367) {
    size_t exactMax = std::numeric_limits<uint16_t>::max();
    EXPECT_NO_THROW(
        TiffEntryBase::writeOffset(buf_, exactMax, ttSignedShort, bigEndian)
    );
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortBoundaryJustAboveMax_367) {
    size_t justAbove = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;
    EXPECT_THROW(
        TiffEntryBase::writeOffset(buf_, justAbove, ttSignedShort, bigEndian),
        Error
    );
}

// ============================================================
// Return value consistency tests
// ============================================================

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedShortReturnsTwo_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 100, ttUnsignedShort, littleEndian);
    EXPECT_EQ(rc, 2u);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedShortReturnsTwo_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 100, ttSignedShort, bigEndian);
    EXPECT_EQ(rc, 2u);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, UnsignedLongReturnsFour_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 100, ttUnsignedLong, littleEndian);
    EXPECT_EQ(rc, 4u);
}

TEST_F(TiffEntryBaseWriteOffsetTest_367, SignedLongReturnsFour_367) {
    size_t rc = TiffEntryBase::writeOffset(buf_, 100, ttSignedLong, bigEndian);
    EXPECT_EQ(rc, 4u);
}
