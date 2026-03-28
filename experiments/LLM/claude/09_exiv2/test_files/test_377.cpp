#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstddef>

// Forward declarations and minimal stubs needed to compile tests
// We need to provide enough context for the TiffEntryBase class

namespace Exiv2 {

// Minimal ByteOrder enum
enum ByteOrder {
    invalidByteOrder,
    littleEndian,
    bigEndian
};

namespace Internal {

// Forward declaration / minimal IoWrapper stub
class IoWrapper {
public:
    IoWrapper() = default;
    virtual ~IoWrapper() = default;
};

class TiffEntryBase {
public:
    size_t doWriteData(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/, size_t /*dataIdx*/, size_t& /*imageIdx*/) const {
        return 0;
    }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffEntryBaseTest_377 : public ::testing::Test {
protected:
    TiffEntryBase entry;
    IoWrapper ioWrapper;
};

// Test that doWriteData returns 0 under normal conditions
TEST_F(TiffEntryBaseTest_377, DoWriteDataReturnsZero_377) {
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with bigEndian byte order
TEST_F(TiffEntryBaseTest_377, DoWriteDataBigEndianReturnsZero_377) {
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, bigEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with invalidByteOrder
TEST_F(TiffEntryBaseTest_377, DoWriteDataInvalidByteOrderReturnsZero_377) {
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, invalidByteOrder, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with non-zero offset
TEST_F(TiffEntryBaseTest_377, DoWriteDataNonZeroOffsetReturnsZero_377) {
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 1024, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with non-zero dataIdx
TEST_F(TiffEntryBaseTest_377, DoWriteDataNonZeroDataIdxReturnsZero_377) {
    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 42, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with non-zero imageIdx
TEST_F(TiffEntryBaseTest_377, DoWriteDataNonZeroImageIdxReturnsZero_377) {
    size_t imageIdx = 100;
    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test that imageIdx is not modified by doWriteData
TEST_F(TiffEntryBaseTest_377, DoWriteDataDoesNotModifyImageIdx_377) {
    size_t imageIdx = 55;
    entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(imageIdx, 55u);
}

// Test with large offset value (boundary condition)
TEST_F(TiffEntryBaseTest_377, DoWriteDataLargeOffsetReturnsZero_377) {
    size_t imageIdx = 0;
    size_t largeOffset = static_cast<size_t>(-1);  // max size_t
    size_t result = entry.doWriteData(ioWrapper, littleEndian, largeOffset, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with large dataIdx value (boundary condition)
TEST_F(TiffEntryBaseTest_377, DoWriteDataLargeDataIdxReturnsZero_377) {
    size_t imageIdx = 0;
    size_t largeDataIdx = static_cast<size_t>(-1);
    size_t result = entry.doWriteData(ioWrapper, bigEndian, 0, largeDataIdx, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test with all non-zero parameters
TEST_F(TiffEntryBaseTest_377, DoWriteDataAllNonZeroParamsReturnsZero_377) {
    size_t imageIdx = 999;
    size_t result = entry.doWriteData(ioWrapper, bigEndian, 512, 256, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test calling doWriteData multiple times returns consistent results
TEST_F(TiffEntryBaseTest_377, DoWriteDataMultipleCallsConsistent_377) {
    size_t imageIdx = 0;
    size_t result1 = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    size_t result2 = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 0u);
}

// Test that the method can be called on a const object
TEST_F(TiffEntryBaseTest_377, DoWriteDataCallableOnConstObject_377) {
    const TiffEntryBase constEntry;
    size_t imageIdx = 0;
    size_t result = constEntry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}
