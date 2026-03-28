#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstring>

#include <exiv2/bmffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

using namespace Exiv2;

// Helper: create a minimal valid HEIF/BMFF file in memory
// A minimal BMFF file has at least an 'ftyp' box
static std::vector<uint8_t> createMinimalBmffData() {
    // ftyp box: size(4) + type(4) + major_brand(4) + minor_version(4) = 16 bytes minimum
    std::vector<uint8_t> data;
    // Box size = 20 (big-endian)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x14); // 20
    // Box type = 'ftyp'
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    // Major brand = 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    // Minor version = 0
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Compatible brand = 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    return data;
}

static std::unique_ptr<BasicIo> createMemIoFromData(const std::vector<uint8_t>& data) {
    return std::make_unique<MemIo>(data.data(), data.size());
}

class BmffImageTest_1201 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that BmffImage can be constructed with valid MemIo
TEST_F(BmffImageTest_1201, ConstructWithValidIo_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    ASSERT_NO_THROW(BmffImage img(std::move(io), false, 1000));
}

// Test mimeType returns a non-empty string
TEST_F(BmffImageTest_1201, MimeTypeReturnsString_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    // mimeType might vary but should return something
    std::string mime = img.mimeType();
    EXPECT_FALSE(mime.empty());
}

// Test pixelWidth returns 0 before metadata is read (or after for a minimal file)
TEST_F(BmffImageTest_1201, PixelWidthInitiallyZero_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    // For a minimal ftyp-only file, pixel dimensions should be 0
    try {
        img.readMetadata();
    } catch (...) {
        // Might throw for minimal file, that's okay
    }
    EXPECT_EQ(img.pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for minimal file
TEST_F(BmffImageTest_1201, PixelHeightInitiallyZero_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (...) {
    }
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test setComment does not throw (even though BMFF doesn't support comments in the usual sense)
TEST_F(BmffImageTest_1201, SetCommentNoThrow_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    ASSERT_NO_THROW(img.setComment("test comment"));
}

// Test setExifData does not throw
TEST_F(BmffImageTest_1201, SetExifDataNoThrow_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    ExifData exifData;
    ASSERT_NO_THROW(img.setExifData(exifData));
}

// Test setIptcData does not throw
TEST_F(BmffImageTest_1201, SetIptcDataNoThrow_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    IptcData iptcData;
    ASSERT_NO_THROW(img.setIptcData(iptcData));
}

// Test setXmpData does not throw
TEST_F(BmffImageTest_1201, SetXmpDataNoThrow_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    XmpData xmpData;
    ASSERT_NO_THROW(img.setXmpData(xmpData));
}

// Test printStructure with kpsIccProfile on a file with no ICC profile outputs nothing
TEST_F(BmffImageTest_1201, PrintStructureIccProfileEmpty_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (...) {
    }
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsIccProfile, 0);
    } catch (...) {
        // May throw if readMetadata failed
    }
    // For a minimal file with no ICC profile, output should be empty
    EXPECT_TRUE(oss.str().empty());
}

// Test printStructure with kpsBasic on minimal BMFF file
TEST_F(BmffImageTest_1201, PrintStructureBasic_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsBasic, 0);
    } catch (...) {
        // May throw for minimal file
    }
    // We just verify it doesn't crash; output may or may not be empty
}

// Test printStructure with kpsRecursive on minimal BMFF file
TEST_F(BmffImageTest_1201, PrintStructureRecursive_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsRecursive, 0);
    } catch (...) {
    }
}

// Test printStructure with kpsNone does nothing
TEST_F(BmffImageTest_1201, PrintStructureNoneDoesNothing_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (...) {
    }
    EXPECT_TRUE(oss.str().empty());
}

// Test that readMetadata can be called on minimal file
TEST_F(BmffImageTest_1201, ReadMetadataMinimalFile_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    // A minimal ftyp-only file may or may not successfully read metadata
    // We just test it doesn't crash with a segfault
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for a minimal file
    }
}

// Test with empty data - should fail gracefully
TEST_F(BmffImageTest_1201, EmptyDataReadMetadataThrows_1201) {
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<MemIo>();
    BmffImage img(std::move(io), false, 1000);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test good() on valid io
TEST_F(BmffImageTest_1201, GoodOnValidIo_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    EXPECT_TRUE(img.good());
}

// Test io() accessor
TEST_F(BmffImageTest_1201, IoAccessor_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    const BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.size(), data.size());
}

// Test writeMetadata throws for BMFF (typically unsupported)
TEST_F(BmffImageTest_1201, WriteMetadataThrows_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test exifData accessor returns reference
TEST_F(BmffImageTest_1201, ExifDataAccessor_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    ExifData& exif = img.exifData();
    EXPECT_TRUE(exif.empty());
}

// Test iptcData accessor returns reference
TEST_F(BmffImageTest_1201, IptcDataAccessor_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    IptcData& iptc = img.iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test xmpData accessor returns reference
TEST_F(BmffImageTest_1201, XmpDataAccessor_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    XmpData& xmp = img.xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test that max_box_depth of 0 limits recursion
TEST_F(BmffImageTest_1201, ZeroMaxBoxDepth_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 0);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsBasic, 0);
    } catch (...) {
        // May throw due to depth limitation
    }
}

// Test iccProfileDefined returns false for minimal file
TEST_F(BmffImageTest_1201, IccProfileNotDefined_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test clearMetadata doesn't throw
TEST_F(BmffImageTest_1201, ClearMetadataNoThrow_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    ASSERT_NO_THROW(img.clearMetadata());
}

// Test imageType returns bmff
TEST_F(BmffImageTest_1201, ImageTypeIsBmff_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    EXPECT_EQ(img.imageType(), ImageType::bmff);
}

// Test printStructure with depth > 0
TEST_F(BmffImageTest_1201, PrintStructureWithDepth_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsRecursive, 5);
    } catch (...) {
    }
}

// Test that constructing with create=true doesn't crash
TEST_F(BmffImageTest_1201, ConstructWithCreateTrue_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    ASSERT_NO_THROW(BmffImage img(std::move(io), true, 1000));
}

// Test repeated readMetadata calls
TEST_F(BmffImageTest_1201, RepeatedReadMetadata_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (...) {
    }
    // Second call should also be safe
    try {
        img.readMetadata();
    } catch (...) {
    }
}

#ifdef EXV_HAVE_XMP_TOOLKIT
// Test printStructure with kpsXMP on minimal file (no XMP data)
TEST_F(BmffImageTest_1201, PrintStructureXmpEmpty_1201) {
    auto data = createMinimalBmffData();
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (...) {
    }
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsXMP, 0);
    } catch (...) {
    }
    // With no XMP data, output should be empty or minimal
}
#endif

// Test truncated BMFF data
TEST_F(BmffImageTest_1201, TruncatedData_1201) {
    // Only 4 bytes - clearly not a valid BMFF
    std::vector<uint8_t> truncated = {0x00, 0x00, 0x00, 0x08};
    auto io = createMemIoFromData(truncated);
    BmffImage img(std::move(io), false, 1000);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test with corrupted box size (size > file size)
TEST_F(BmffImageTest_1201, CorruptedBoxSize_1201) {
    std::vector<uint8_t> data;
    // Box size = 0xFFFFFFFF (way larger than actual data)
    data.push_back(0xFF);
    data.push_back(0xFF);
    data.push_back(0xFF);
    data.push_back(0xFF);
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    auto io = createMemIoFromData(data);
    BmffImage img(std::move(io), false, 1000);
    // Should handle gracefully
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected
    }
}
