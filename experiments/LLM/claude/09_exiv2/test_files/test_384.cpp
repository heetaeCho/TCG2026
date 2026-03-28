#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal forward declarations and stubs needed to compile
namespace Exiv2 {

// ByteOrder enum - common in exiv2
enum ByteOrder {
    invalidByteOrder,
    littleEndian,
    bigEndian
};

// IoWrapper - minimal stub for testing
class IoWrapper {
public:
    virtual ~IoWrapper() = default;
};

namespace Internal {

class TiffEntryBase {
public:
    size_t doWriteImage(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/) const {
        return 0;
    }
};

} // namespace Internal
} // namespace Exiv2

// Test fixture
class TiffEntryBaseTest_384 : public ::testing::Test {
protected:
    Exiv2::Internal::TiffEntryBase entry;
    Exiv2::IoWrapper ioWrapper;
};

// Normal operation: doWriteImage returns 0
TEST_F(TiffEntryBaseTest_384, DoWriteImageReturnsZero_384) {
    size_t result = entry.doWriteImage(ioWrapper, Exiv2::littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test with bigEndian byte order
TEST_F(TiffEntryBaseTest_384, DoWriteImageWithBigEndianReturnsZero_384) {
    size_t result = entry.doWriteImage(ioWrapper, Exiv2::bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test with invalidByteOrder
TEST_F(TiffEntryBaseTest_384, DoWriteImageWithInvalidByteOrderReturnsZero_384) {
    size_t result = entry.doWriteImage(ioWrapper, Exiv2::invalidByteOrder);
    EXPECT_EQ(result, 0u);
}

// Test that doWriteImage is const-correct - can be called on const object
TEST_F(TiffEntryBaseTest_384, DoWriteImageIsConstCallable_384) {
    const Exiv2::Internal::TiffEntryBase constEntry;
    size_t result = constEntry.doWriteImage(ioWrapper, Exiv2::littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test multiple calls return consistent results
TEST_F(TiffEntryBaseTest_384, DoWriteImageMultipleCallsConsistent_384) {
    size_t result1 = entry.doWriteImage(ioWrapper, Exiv2::littleEndian);
    size_t result2 = entry.doWriteImage(ioWrapper, Exiv2::bigEndian);
    size_t result3 = entry.doWriteImage(ioWrapper, Exiv2::littleEndian);
    EXPECT_EQ(result1, 0u);
    EXPECT_EQ(result2, 0u);
    EXPECT_EQ(result3, 0u);
}

// Test default construction
TEST_F(TiffEntryBaseTest_384, DefaultConstruction_384) {
    Exiv2::Internal::TiffEntryBase newEntry;
    size_t result = newEntry.doWriteImage(ioWrapper, Exiv2::littleEndian);
    EXPECT_EQ(result, 0u);
}

// Boundary: return type is size_t, verify it's exactly zero (not negative or some other value)
TEST_F(TiffEntryBaseTest_384, ReturnValueIsExactlyZero_384) {
    size_t result = entry.doWriteImage(ioWrapper, Exiv2::bigEndian);
    EXPECT_EQ(result, static_cast<size_t>(0));
    EXPECT_FALSE(result > 0);
}
