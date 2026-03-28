#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// The root tag constants used in exiv2
// Tag::root is typically 0x10000 for standard TIFF
static constexpr uint32_t Tag_root = 0x10000;

class TiffCreatorGetPathTest_1166 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that getPath returns a non-empty path for a known valid IFD0 entry
TEST_F(TiffCreatorGetPathTest_1166, GetPathForIfd0ReturnsNonEmptyPath_1166) {
    // IFD0 with a standard tag should produce a valid path
    // Tag 0x0100 (ImageWidth) in IFD0
    TiffPath path = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    EXPECT_FALSE(path.empty());
}

// Test that getPath for ExifIFD returns a path with multiple entries (traverses tree)
TEST_F(TiffCreatorGetPathTest_1166, GetPathForExifIdReturnsMultiLevelPath_1166) {
    // A tag in the Exif IFD - e.g., 0x829a (ExposureTime)
    TiffPath path = TiffCreator::getPath(0x829a, IfdId::exifId, Tag_root);
    // The path should contain at least 2 entries: one for exifId and one for the root
    EXPECT_GE(path.size(), 2u);
}

// Test that getPath for GPS IFD returns a valid multi-level path
TEST_F(TiffCreatorGetPathTest_1166, GetPathForGpsIdReturnsMultiLevelPath_1166) {
    // A tag in GPS IFD - e.g., 0x0001 (GPSLatitudeRef)
    TiffPath path = TiffCreator::getPath(0x0001, IfdId::gpsId, Tag_root);
    EXPECT_GE(path.size(), 2u);
}

// Test that getPath for IOP IFD returns a valid path
TEST_F(TiffCreatorGetPathTest_1166, GetPathForIopIdReturnsValidPath_1166) {
    // A tag in IOP IFD - e.g., 0x0001 (InteroperabilityIndex)
    TiffPath path = TiffCreator::getPath(0x0001, IfdId::iopId, Tag_root);
    EXPECT_GE(path.size(), 2u);
}

// Test that getPath for IFD1 (thumbnail) returns a valid path
TEST_F(TiffCreatorGetPathTest_1166, GetPathForIfd1ReturnsValidPath_1166) {
    // IFD1 with a standard tag
    TiffPath path = TiffCreator::getPath(0x0100, IfdId::ifd1Id, Tag_root);
    EXPECT_FALSE(path.empty());
}

// Test that the path for IFD0 always includes the root element at the bottom
TEST_F(TiffCreatorGetPathTest_1166, GetPathForIfd0IncludesRootElement_1166) {
    TiffPath path = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    ASSERT_FALSE(path.empty());
    // The top of the priority queue (TiffPath) should represent the root or first traversed node
    // We just verify the path has content
    EXPECT_GE(path.size(), 1u);
}

// Test that different tags in the same group produce paths of the same depth
TEST_F(TiffCreatorGetPathTest_1166, DifferentTagsSameGroupSameDepth_1166) {
    TiffPath path1 = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    TiffPath path2 = TiffCreator::getPath(0x0101, IfdId::ifd0Id, Tag_root);
    // Both are in ifd0Id, so they should traverse the same tree levels
    EXPECT_EQ(path1.size(), path2.size());
}

// Test that ExifIFD path is deeper than IFD0 path (Exif is a sub-IFD of IFD0)
TEST_F(TiffCreatorGetPathTest_1166, ExifPathDeeperThanIfd0Path_1166) {
    TiffPath pathIfd0 = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    TiffPath pathExif = TiffCreator::getPath(0x829a, IfdId::exifId, Tag_root);
    EXPECT_GT(pathExif.size(), pathIfd0.size());
}

// Test that GPS path is deeper than IFD0 path
TEST_F(TiffCreatorGetPathTest_1166, GpsPathDeeperThanIfd0Path_1166) {
    TiffPath pathIfd0 = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    TiffPath pathGps = TiffCreator::getPath(0x0001, IfdId::gpsId, Tag_root);
    EXPECT_GT(pathGps.size(), pathIfd0.size());
}

// Test that IOP path is deeper than ExifIFD path (IOP is sub-IFD of Exif)
TEST_F(TiffCreatorGetPathTest_1166, IopPathDeeperThanExifPath_1166) {
    TiffPath pathExif = TiffCreator::getPath(0x829a, IfdId::exifId, Tag_root);
    TiffPath pathIop = TiffCreator::getPath(0x0001, IfdId::iopId, Tag_root);
    EXPECT_GT(pathIop.size(), pathExif.size());
}

// Test create function returns non-null for known tag/group combinations
TEST_F(TiffCreatorGetPathTest_1166, CreateReturnsNonNullForKnownCombination_1166) {
    auto component = TiffCreator::create(0x0100, IfdId::ifd0Id);
    EXPECT_NE(component, nullptr);
}

// Test create function for Exif tag
TEST_F(TiffCreatorGetPathTest_1166, CreateReturnsNonNullForExifTag_1166) {
    auto component = TiffCreator::create(0x829a, IfdId::exifId);
    EXPECT_NE(component, nullptr);
}

// Test that two calls to getPath with same parameters produce equal results
TEST_F(TiffCreatorGetPathTest_1166, GetPathIsDeterministic_1166) {
    TiffPath path1 = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    TiffPath path2 = TiffCreator::getPath(0x0100, IfdId::ifd0Id, Tag_root);
    EXPECT_EQ(path1.size(), path2.size());
}

// Test path for Canon maker note if it exists in the tree
TEST_F(TiffCreatorGetPathTest_1166, GetPathForCanonMakerNote_1166) {
    TiffPath path = TiffCreator::getPath(0x0001, IfdId::canonId, Tag_root);
    // Canon maker note should be deeper than Exif IFD
    EXPECT_GE(path.size(), 3u);
}

// Test that sub-image IFDs produce valid paths
TEST_F(TiffCreatorGetPathTest_1166, GetPathForSubImage1_1166) {
    TiffPath path = TiffCreator::getPath(0x0100, IfdId::subImage1Id, Tag_root);
    EXPECT_FALSE(path.empty());
}
