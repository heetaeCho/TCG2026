#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffReaderCircularReferenceTest_1700 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set log level to mute to suppress error output during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        // Restore default log level
        LogMsg::setLevel(LogMsg::warn);
    }

    // Minimal valid TIFF data buffer
    static constexpr size_t kDataSize = 256;
    byte data_[kDataSize] = {0};
};

// Test that the first call with a new pointer returns false (no circular reference)
TEST_F(TiffReaderCircularReferenceTest_1700, FirstCallReturnsFalse_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_ + 10;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
}

// Test that calling with the same pointer twice returns true on second call
TEST_F(TiffReaderCircularReferenceTest_1700, SecondCallWithSamePointerReturnsTrue_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_ + 20;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd0Id));
}

// Test that different pointers don't cause circular reference
TEST_F(TiffReaderCircularReferenceTest_1700, DifferentPointersReturnFalse_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start1 = data_ + 10;
    const byte* start2 = data_ + 20;
    const byte* start3 = data_ + 30;

    EXPECT_FALSE(reader.circularReference(start1, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(start2, IfdId::ifd1Id));
    EXPECT_FALSE(reader.circularReference(start3, IfdId::exifId));
}

// Test that same pointer with different group still triggers circular reference
TEST_F(TiffReaderCircularReferenceTest_1700, SamePointerDifferentGroupReturnsTrue_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_ + 40;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
    // Same pointer but different group should still be detected as circular
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd1Id));
}

// Test multiple pointers, then re-check each for circular reference
TEST_F(TiffReaderCircularReferenceTest_1700, MultiplePointersAllDetectedOnSecondCall_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* ptrs[5];
    for (int i = 0; i < 5; ++i) {
        ptrs[i] = data_ + (i * 10);
        EXPECT_FALSE(reader.circularReference(ptrs[i], IfdId::ifd0Id));
    }

    // All should now return true
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(reader.circularReference(ptrs[i], IfdId::ifd0Id));
    }
}

// Test with pointer at the beginning of data
TEST_F(TiffReaderCircularReferenceTest_1700, PointerAtDataBeginning_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd0Id));
}

// Test with pointer at the end of data
TEST_F(TiffReaderCircularReferenceTest_1700, PointerAtDataEnd_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_ + kDataSize - 1;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd0Id));
}

// Test third call with same pointer also returns true
TEST_F(TiffReaderCircularReferenceTest_1700, ThirdCallWithSamePointerReturnsTrue_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start = data_ + 50;
    EXPECT_FALSE(reader.circularReference(start, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start, IfdId::ifd0Id));
}

// Test adjacent pointers are treated as distinct
TEST_F(TiffReaderCircularReferenceTest_1700, AdjacentPointersAreDistinct_1700) {
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data_, kDataSize, &root, state);

    const byte* start1 = data_ + 50;
    const byte* start2 = data_ + 51;

    EXPECT_FALSE(reader.circularReference(start1, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(start2, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start1, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(start2, IfdId::ifd0Id));
}
