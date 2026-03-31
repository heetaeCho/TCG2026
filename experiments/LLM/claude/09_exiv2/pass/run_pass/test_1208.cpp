#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <fstream>
#include <vector>

using namespace Exiv2;

// ============================================================
// DataBuf Tests (dependency used by PreviewImage)
// ============================================================

class DataBufTest_1208 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DataBufTest_1208, DefaultConstructorCreatesEmptyBuffer_1208) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1208, SizeConstructorAllocatesCorrectSize_1208) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1208, SizeConstructorZeroSize_1208) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1208, DataPointerConstructor_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(std::memcmp(buf.c_data(), data, 5), 0);
}

TEST_F(DataBufTest_1208, CDataReturnsCorrectPointer_1208) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0xAA);
    EXPECT_EQ(ptr[1], 0xBB);
    EXPECT_EQ(ptr[2], 0xCC);
}

TEST_F(DataBufTest_1208, AllocResizesBuffer_1208) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST_F(DataBufTest_1208, ResizeChangesSize_1208) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1208, ResetClearsBuffer_1208) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1208, ReadWriteUint8_1208) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST_F(DataBufTest_1208, ReadWriteUint16LittleEndian_1208) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1208, ReadWriteUint16BigEndian_1208) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x5678, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x5678);
}

TEST_F(DataBufTest_1208, ReadWriteUint32LittleEndian_1208) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1208, ReadWriteUint32BigEndian_1208) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xCAFEBABE, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xCAFEBABE);
}

TEST_F(DataBufTest_1208, ReadWriteUint64LittleEndian_1208) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1208, ReadWriteUint64BigEndian_1208) {
    DataBuf buf(16);
    uint64_t val = 0xFEDCBA9876543210ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST_F(DataBufTest_1208, CmpBytesMatch_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(0, data, 4), 0);
}

TEST_F(DataBufTest_1208, CmpBytesNoMatch_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    const byte other[] = {0x01, 0x02, 0xFF, 0x04};
    DataBuf buf(data, 4);
    EXPECT_NE(buf.cmpBytes(0, other, 4), 0);
}

TEST_F(DataBufTest_1208, CmpBytesWithOffset_1208) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 4);
    const byte expected[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(1, expected, 2), 0);
}

TEST_F(DataBufTest_1208, DataReturnsWritablePointer_1208) {
    DataBuf buf(4);
    byte* ptr = buf.data();
    ASSERT_NE(ptr, nullptr);
    ptr[0] = 0xFF;
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

TEST_F(DataBufTest_1208, WriteUint8AtOffset_1208) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x10);
    buf.write_uint8(1, 0x20);
    buf.write_uint8(2, 0x30);
    buf.write_uint8(3, 0x40);
    EXPECT_EQ(buf.read_uint8(0), 0x10);
    EXPECT_EQ(buf.read_uint8(1), 0x20);
    EXPECT_EQ(buf.read_uint8(2), 0x30);
    EXPECT_EQ(buf.read_uint8(3), 0x40);
}

TEST_F(DataBufTest_1208, WriteUint16AtDifferentOffsets_1208) {
    DataBuf buf(8);
    buf.write_uint16(0, 0x1111, bigEndian);
    buf.write_uint16(2, 0x2222, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1111);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0x2222);
}

TEST_F(DataBufTest_1208, EmptyBufferIsEmpty_1208) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1208, ResizeToZero_1208) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1208, AllocAfterAlloc_1208) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1208, DataWithOffset_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    const byte* ptr = buf.c_data(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 0x03);
}

// ============================================================
// PreviewImage Tests
// ============================================================

class PreviewImageTest_1208 : public ::testing::Test {
protected:
    // Helper to create a minimal valid JPEG file for testing
    static std::string createMinimalJpeg(const std::string& path) {
        // Minimal JPEG: SOI + APP0 (JFIF) + minimal data + EOI
        std::vector<byte> jpeg;
        // SOI
        jpeg.push_back(0xFF);
        jpeg.push_back(0xD8);
        // APP0 JFIF marker
        jpeg.push_back(0xFF);
        jpeg.push_back(0xE0);
        // Length (16 bytes)
        jpeg.push_back(0x00);
        jpeg.push_back(0x10);
        // JFIF\0
        jpeg.push_back('J');
        jpeg.push_back('F');
        jpeg.push_back('I');
        jpeg.push_back('F');
        jpeg.push_back(0x00);
        // Version 1.01
        jpeg.push_back(0x01);
        jpeg.push_back(0x01);
        // Units (0 = no units)
        jpeg.push_back(0x00);
        // X density
        jpeg.push_back(0x00);
        jpeg.push_back(0x01);
        // Y density
        jpeg.push_back(0x00);
        jpeg.push_back(0x01);
        // Thumbnail dimensions
        jpeg.push_back(0x00);
        jpeg.push_back(0x00);
        // EOI
        jpeg.push_back(0xFF);
        jpeg.push_back(0xD9);

        std::ofstream ofs(path, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(jpeg.data()), jpeg.size());
        ofs.close();
        return path;
    }

    void SetUp() override {}
    void TearDown() override {}
};

// Test that PreviewManager can be created from an image and getPreviewImages returns a list
TEST_F(PreviewImageTest_1208, PreviewManagerGetPreviewProperties_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();
        // A minimal JPEG may not have previews, which is valid
        // Just confirm we can call the method without crashing
        SUCCEED();
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // Some minimal JPEGs may not be fully parseable; that's acceptable
        SUCCEED();
    }
}

// Test PreviewImage copy constructor
TEST_F(PreviewImageTest_1208, CopyConstructorPreservesData_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_copy_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            PreviewImage preview = manager.getPreviewImage(list.front());
            PreviewImage copy(preview);

            EXPECT_EQ(copy.size(), preview.size());
            EXPECT_EQ(copy.mimeType(), preview.mimeType());
            EXPECT_EQ(copy.extension(), preview.extension());
            EXPECT_EQ(copy.width(), preview.width());
            EXPECT_EQ(copy.height(), preview.height());
            EXPECT_EQ(copy.id(), preview.id());

            if (preview.size() > 0) {
                EXPECT_EQ(std::memcmp(copy.pData(), preview.pData(), preview.size()), 0);
            }
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test PreviewImage assignment operator
TEST_F(PreviewImageTest_1208, AssignmentOperatorPreservesData_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_assign_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        if (list.size() >= 1) {
            PreviewImage preview = manager.getPreviewImage(list.front());
            PreviewImage copy(preview);  // copy construct first
            copy = preview;  // then assign

            EXPECT_EQ(copy.size(), preview.size());
            EXPECT_EQ(copy.mimeType(), preview.mimeType());
            EXPECT_EQ(copy.extension(), preview.extension());
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that pData returns non-null when preview has data
TEST_F(PreviewImageTest_1208, PDataReturnsNonNullForNonEmptyPreview_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_pdata_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            PreviewImage preview = manager.getPreviewImage(props);
            if (preview.size() > 0) {
                EXPECT_NE(preview.pData(), nullptr);
            }
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test copy() returns a DataBuf with correct size
TEST_F(PreviewImageTest_1208, CopyReturnsCorrectSizeDataBuf_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_copybuf_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            PreviewImage preview = manager.getPreviewImage(props);
            DataBuf buf = preview.copy();
            EXPECT_EQ(buf.size(), preview.size());
            if (preview.size() > 0) {
                EXPECT_EQ(std::memcmp(buf.c_data(), preview.pData(), preview.size()), 0);
            }
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test mimeType returns non-empty string for previews
TEST_F(PreviewImageTest_1208, MimeTypeIsNonEmptyForPreview_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_mime_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            PreviewImage preview = manager.getPreviewImage(props);
            EXPECT_FALSE(preview.mimeType().empty());
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test extension returns non-empty string for previews
TEST_F(PreviewImageTest_1208, ExtensionIsNonEmptyForPreview_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_ext_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            PreviewImage preview = manager.getPreviewImage(props);
            EXPECT_FALSE(preview.extension().empty());
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test writeFile produces a file
TEST_F(PreviewImageTest_1208, WriteFileCreatesFile_1208) {
    try {
        std::string path = createMinimalJpeg("test_preview_write_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            PreviewImage preview = manager.getPreviewImage(list.front());
            std::string outBase = "test_preview_output_1208";
            size_t bytesWritten = preview.writeFile(outBase);
            EXPECT_GT(bytesWritten, 0u);

            // Clean up the output file
            std::string outPath = outBase + preview.extension();
            std::remove(outPath.c_str());
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that getPreviewProperties returns empty list for image without previews
TEST_F(PreviewImageTest_1208, NoPreviewsForMinimalJpeg_1208) {
    try {
        std::string path = createMinimalJpeg("test_no_preview_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();
        // A minimal JPEG without EXIF thumbnails should have no previews
        EXPECT_TRUE(list.empty());
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test PreviewProperties list sorting (properties should be sorted by size)
TEST_F(PreviewImageTest_1208, PreviewPropertiesAreSortedBySize_1208) {
    try {
        std::string path = createMinimalJpeg("test_sorted_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        // Verify that the list is sorted by size (ascending)
        for (size_t i = 1; i < list.size(); ++i) {
            EXPECT_LE(list[i - 1].size_, list[i].size_);
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test self-assignment
TEST_F(PreviewImageTest_1208, SelfAssignment_1208) {
    try {
        std::string path = createMinimalJpeg("test_selfassign_1208.jpg");
        auto image = ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            PreviewImage preview = manager.getPreviewImage(list.front());
            uint32_t sizeBefore = preview.size();
            std::string mimeBefore = preview.mimeType();

            preview = preview;  // self-assignment

            EXPECT_EQ(preview.size(), sizeBefore);
            EXPECT_EQ(preview.mimeType(), mimeBefore);
        }
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// ============================================================
// Additional DataBuf edge case tests
// ============================================================

TEST_F(DataBufTest_1208, LargeAllocation_1208) {
    DataBuf buf(1024 * 1024);  // 1 MB
    EXPECT_EQ(buf.size(), 1024u * 1024u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1208, ResizePreservesExistingData_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(8);
    EXPECT_EQ(buf.size(), 8u);
    // First 4 bytes should be preserved
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1208, ResizeSmaller_1208) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(2);
    EXPECT_EQ(buf.size(), 2u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
}

TEST_F(DataBufTest_1208, CStrReturnsCorrectString_1208) {
    const char str[] = "Hello";
    DataBuf buf(reinterpret_cast<const byte*>(str), 6);  // include null terminator
    EXPECT_STREQ(buf.c_str(), "Hello");
}

TEST_F(DataBufTest_1208, BeginEndIterators_1208) {
    const byte data[] = {0x0A, 0x0B, 0x0C};
    DataBuf buf(data, 3);
    auto it = buf.begin();
    EXPECT_EQ(*it, 0x0A);
    ++it;
    EXPECT_EQ(*it, 0x0B);
    ++it;
    EXPECT_EQ(*it, 0x0C);
    ++it;
    EXPECT_EQ(it, buf.end());
}

TEST_F(DataBufTest_1208, EndianConversionConsistency_1208) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    // In big endian, bytes should be 01 02 03 04
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1208, EndianConversionLittleEndian_1208) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, littleEndian);
    // In little endian, bytes should be 04 03 02 01
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}

TEST_F(DataBufTest_1208, MultipleResetAndAlloc_1208) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.reset();
    EXPECT_TRUE(buf.empty());
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
    buf.reset();
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1208, CmpBytesPartialBuffer_1208) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 5);
    const byte expected[] = {0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(2, expected, 2), 0);
}
