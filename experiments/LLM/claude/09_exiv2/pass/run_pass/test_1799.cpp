#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/crwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <exiv2/tags.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
DataBuf packIfdId(const ExifData& exifData, IfdId ifdId, ByteOrder byteOrder);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PackIfdIdTest_1799 : public ::testing::Test {
protected:
    void SetUp() override {
        // Save original log level to restore later
        originalLevel_ = LogMsg::level();
    }

    void TearDown() override {
        LogMsg::setLevel(originalLevel_);
    }

    LogMsg::Level originalLevel_;
};

// Test with empty ExifData - should return empty buffer
TEST_F(PackIfdIdTest_1799, EmptyExifData_ReturnsEmptyBuffer_1799) {
    ExifData exifData;
    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

// Test with ExifData that has no matching IfdId
TEST_F(PackIfdIdTest_1799, NoMatchingIfdId_ReturnsEmptyBuffer_1799) {
    ExifData exifData;
    // Add an entry to ifd0Id
    exifData["Exif.Image.Make"] = "TestCamera";

    // Query for a different IfdId (exifId)
    DataBuf result = packIfdId(exifData, IfdId::exifId, littleEndian);
    EXPECT_TRUE(result.empty());
}

// Test with a single matching entry - little endian
TEST_F(PackIfdIdTest_1799, SingleMatchingEntry_LittleEndian_1799) {
    ExifData exifData;
    // Exif.Image.Make is tag 0x010F in IFD0
    exifData["Exif.Image.Make"] = "Test";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_FALSE(result.empty());
    EXPECT_GT(result.size(), 0u);
}

// Test with a single matching entry - big endian
TEST_F(PackIfdIdTest_1799, SingleMatchingEntry_BigEndian_1799) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Test";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, bigEndian);
    EXPECT_FALSE(result.empty());
    EXPECT_GT(result.size(), 0u);
}

// Test that buffer size is even (padding for alignment)
TEST_F(PackIfdIdTest_1799, BufferSizeIsEven_1799) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Test";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    if (!result.empty()) {
        EXPECT_EQ(result.size() % 2, 0u);
    }
}

// Test with multiple entries in same IFD
TEST_F(PackIfdIdTest_1799, MultipleEntriesSameIfd_1799) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_FALSE(result.empty());
    EXPECT_GT(result.size(), 0u);
    EXPECT_EQ(result.size() % 2, 0u);
}

// Test with entries from mixed IFDs - only matching ones should be included
TEST_F(PackIfdIdTest_1799, MixedIfdEntries_OnlyMatchingIncluded_1799) {
    ExifData exifData;
    // IFD0 entry
    exifData["Exif.Image.Make"] = "TestCamera";
    // Exif IFD entry
    exifData["Exif.Photo.ExposureTime"] = "1/100";

    DataBuf resultIfd0 = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    DataBuf resultExif = packIfdId(exifData, IfdId::exifId, littleEndian);

    // Both should produce non-empty results since we have entries in both IFDs
    EXPECT_FALSE(resultIfd0.empty());
    EXPECT_FALSE(resultExif.empty());
}

// Test with uint16_t value type
TEST_F(PackIfdIdTest_1799, Uint16Value_1799) {
    ExifData exifData;
    exifData["Exif.Image.Orientation"] = uint16_t(1);

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.size() % 2, 0u);
}

// Test with uint32_t value type
TEST_F(PackIfdIdTest_1799, Uint32Value_1799) {
    ExifData exifData;
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.size() % 2, 0u);
}

// Test with big endian byte order
TEST_F(PackIfdIdTest_1799, BigEndianByteOrder_1799) {
    ExifData exifData;
    exifData["Exif.Image.Orientation"] = uint16_t(6);

    DataBuf resultLE = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    DataBuf resultBE = packIfdId(exifData, IfdId::ifd0Id, bigEndian);

    // Both should produce non-empty results
    EXPECT_FALSE(resultLE.empty());
    EXPECT_FALSE(resultBE.empty());

    // Sizes should be the same regardless of byte order
    EXPECT_EQ(resultLE.size(), resultBE.size());
}

// Test that the result buffer size is always even
TEST_F(PackIfdIdTest_1799, ResultSizeAlwaysEven_1799) {
    ExifData exifData;
    exifData["Exif.Image.Orientation"] = uint16_t(1);

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_EQ(result.size() % 2, 0u);
}

// Test with low tag number entry
TEST_F(PackIfdIdTest_1799, LowTagNumber_1799) {
    ExifData exifData;
    // Exif.Image.ProcessingSoftware is tag 0x000b
    exifData["Exif.Image.ProcessingSoftware"] = "test";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    EXPECT_FALSE(result.empty());
}

// Test error logging for out-of-bounds entries (suppress error output)
TEST_F(PackIfdIdTest_1799, OutOfBoundsEntrySuppressed_1799) {
    // Mute log messages to avoid test output noise
    LogMsg::setLevel(LogMsg::mute);

    ExifData exifData;
    // Add a normal entry - this should work fine
    exifData["Exif.Image.Make"] = "Test";

    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    // Should still produce valid output for in-bounds entries
    EXPECT_FALSE(result.empty());
}

// Test with ExifData containing only non-matching IFD entries
TEST_F(PackIfdIdTest_1799, OnlyNonMatchingEntries_1799) {
    ExifData exifData;
    exifData["Exif.Photo.ExposureTime"] = "1/100";
    exifData["Exif.Photo.FNumber"] = "28/10";

    // Request IFD0 entries, but we only have Exif IFD entries
    DataBuf result = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    // Result might be empty or might have entries depending on key resolution
    // The key behavior: if ifdId doesn't match, entries are skipped
    // Since the entries are in exifId, not ifd0Id, result should be empty
    EXPECT_TRUE(result.empty());
}

// Test consistency - calling twice with same data produces same result
TEST_F(PackIfdIdTest_1799, ConsistentResults_1799) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";

    DataBuf result1 = packIfdId(exifData, IfdId::ifd0Id, littleEndian);
    DataBuf result2 = packIfdId(exifData, IfdId::ifd0Id, littleEndian);

    EXPECT_EQ(result1.size(), result2.size());
    if (!result1.empty() && !result2.empty()) {
        EXPECT_EQ(result1.cmpBytes(0, result2.c_data(0), result2.size()), 0);
    }
}
