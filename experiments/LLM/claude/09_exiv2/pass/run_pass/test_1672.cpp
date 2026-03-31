#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffHeaderBase for encoder construction
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader(ByteOrder byteOrder = littleEndian)
        : TiffHeaderBase(42, 8, byteOrder, 0) {}
    ~TestTiffHeader() override = default;
};

class TiffEncoderVisitDirectoryNextTest_1672 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that visitDirectoryNext does not crash with a directory that has no components
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, EmptyDirectoryDoesNotCrash_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    // Allocate a buffer for the directory start - needs at least 2 bytes for count
    byte buffer[256] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    // Should not crash with empty directory
    EXPECT_NO_THROW(encoder.visitDirectoryNext(&rootDir));
}

// Test that visitDirectoryNext does not crash with big-endian byte order
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, BigEndianEmptyDirectory_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, false);
    byte buffer[256] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(bigEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_NO_THROW(encoder.visitDirectoryNext(&rootDir));
}

// Test byteOrder accessor returns header's byte order
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, ByteOrderMatchesHeader_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    {
        TestTiffHeader header(littleEndian);
        PrimaryGroups primaryGroups;

        TiffEncoder encoder(exifData, iptcData, xmpData,
                            &rootDir, false, std::move(primaryGroups),
                            &header, nullptr);

        EXPECT_EQ(encoder.byteOrder(), littleEndian);
    }

    {
        TestTiffHeader header(bigEndian);
        PrimaryGroups primaryGroups;

        TiffEncoder encoder(exifData, iptcData, xmpData,
                            &rootDir, false, std::move(primaryGroups),
                            &header, nullptr);

        EXPECT_EQ(encoder.byteOrder(), bigEndian);
    }
}

// Test dirty flag default and setter
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, DirtyFlagDefaultFalse_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_FALSE(encoder.dirty());
}

// Test setting dirty flag to true
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, SetDirtyTrue_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
}

// Test setting dirty flag back to false
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, SetDirtyFalseAfterTrue_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());

    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
}

// Test writeMethod default is non-intrusive
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, DefaultWriteMethodNonIntrusive_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test TiffDirectory construction and hasNext
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, TiffDirectoryHasNext_1672) {
    TiffDirectory dirWithNext(0, IfdId::ifd0Id, true);
    EXPECT_TRUE(dirWithNext.hasNext());

    TiffDirectory dirWithoutNext(0, IfdId::ifd0Id, false);
    EXPECT_FALSE(dirWithoutNext.hasNext());
}

// Test TiffComponent basic properties
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, TiffDirectoryTagAndGroup_1672) {
    TiffDirectory dir(0x0100, IfdId::ifd0Id, true);
    EXPECT_EQ(dir.tag(), 0x0100);
    EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test visitDirectory (which is documented as a no-op/empty) doesn't crash
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, VisitDirectoryNoOp_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[64] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_NO_THROW(encoder.visitDirectory(&rootDir));
}

// Test that start() returns what was set
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, TiffComponentStartPointer_1672) {
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    byte buffer[64] = {};
    dir.setStart(buffer);
    EXPECT_EQ(dir.start(), buffer);
}

// Test visitDirectoryNext with directory having hasNext=false
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, VisitDirectoryNextNoNext_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, false);
    byte buffer[256] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_NO_THROW(encoder.visitDirectoryNext(&rootDir));
}

// Test creating encoder with isNewImage=true
TEST_F(TiffEncoderVisitDirectoryNextTest_1672, NewImageEncoder_1672) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TiffDirectory rootDir(0, IfdId::ifd0Id, true);
    byte buffer[256] = {};
    rootDir.setStart(buffer);

    TestTiffHeader header(bigEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        &rootDir, true, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_FALSE(encoder.dirty());
    EXPECT_EQ(encoder.byteOrder(), bigEndian);
    EXPECT_NO_THROW(encoder.visitDirectoryNext(&rootDir));
}
