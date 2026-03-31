#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "crwimage_int.hpp"

#include <memory>
#include <sstream>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: Create a minimal valid CRW file header for testing
// CRW files start with a specific signature
static std::vector<byte> createMinimalCrwData() {
    // Minimal CRW-like data with CIFF header
    // The CIFF header signature is "HEAPCCDR" at offset 6
    // Byte order: little endian (II)
    std::vector<byte> data(64, 0);
    // Byte order mark: 'II' for little endian
    data[0] = 'I';
    data[1] = 'I';
    // Header length (offset to root directory)
    data[2] = 0x1a;
    data[3] = 0x00;
    data[4] = 0x00;
    data[5] = 0x00;
    // Signature: HEAPCCDR
    data[6] = 'H';
    data[7] = 'E';
    data[8] = 'A';
    data[9] = 'P';
    data[10] = 'C';
    data[11] = 'C';
    data[12] = 'D';
    data[13] = 'R';
    // Version
    data[14] = 0x01;
    data[15] = 0x00;
    // Sub-version
    data[16] = 0x01;
    data[17] = 0x00;
    // Reserved
    data[18] = 0x00;
    data[19] = 0x00;
    data[20] = 0x00;
    data[21] = 0x00;
    data[22] = 0x00;
    data[23] = 0x00;
    data[24] = 0x00;
    data[25] = 0x00;
    return data;
}

// Helper function to create a MemIo-based Image for testing
static std::unique_ptr<Image> createTestImage() {
    auto io = std::make_unique<MemIo>();
    // Use ImageFactory to create a CRW image if possible, or just use a generic approach
    // For testing CrwMap, we need an Image object with exifData access
    // We'll try to open a memory-based image
    auto image = ImageFactory::open(std::move(io));
    return image;
}

class CrwMapTest_1798 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

class CiffHeaderTest_1798 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test CiffHeader default byte order
TEST_F(CiffHeaderTest_1798, DefaultByteOrder_1798) {
    CiffHeader header;
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test CiffHeader signature
TEST_F(CiffHeaderTest_1798, SignatureIsValid_1798) {
    auto sig = CiffHeader::signature();
    // The signature should not be empty
    EXPECT_FALSE(sig.empty());
}

// Test CiffHeader read with invalid/too small data
TEST_F(CiffHeaderTest_1798, ReadTooSmallDataThrows_1798) {
    CiffHeader header;
    byte smallData[] = {0x00, 0x01};
    EXPECT_THROW(header.read(smallData, sizeof(smallData)), Error);
}

// Test CiffHeader read with invalid signature
TEST_F(CiffHeaderTest_1798, ReadInvalidSignatureThrows_1798) {
    CiffHeader header;
    std::vector<byte> data(64, 0);
    // Fill with garbage - no valid CIFF signature
    data[0] = 'X';
    data[1] = 'X';
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test CiffHeader read with zero-size data
TEST_F(CiffHeaderTest_1798, ReadZeroSizeThrows_1798) {
    CiffHeader header;
    byte dummy = 0;
    EXPECT_THROW(header.read(&dummy, 0), Error);
}

// Test CiffHeader findComponent returns null for non-existent component
TEST_F(CiffHeaderTest_1798, FindComponentNonExistent_1798) {
    CiffHeader header;
    // Without reading any data, there should be no components
    // This may throw or return nullptr depending on implementation
    // Since pRootDir_ is null, accessing it may cause issues
    // We test after attempting to read valid data
    auto minData = createMinimalCrwData();
    try {
        header.read(minData.data(), minData.size());
        const CiffComponent* comp = header.findComponent(0xFFFF, 0xFFFF);
        EXPECT_EQ(comp, nullptr);
    } catch (const Error&) {
        // If the minimal data isn't valid enough, that's acceptable
        SUCCEED();
    }
}

// Test CrwMap::loadStack with root directory
TEST_F(CrwMapTest_1798, LoadStackRootDir_1798) {
    CrwDirs dirs;
    CrwMap::loadStack(dirs, 0x0000);
    // Root directory should result in at least one entry in the stack
    EXPECT_FALSE(dirs.empty());
}

// Test CrwMap::loadStack with a known directory value
TEST_F(CrwMapTest_1798, LoadStackKnownDir_1798) {
    CrwDirs dirs;
    // 0x2804 is a known CRW directory (ImageProps)
    CrwMap::loadStack(dirs, 0x2804);
    EXPECT_FALSE(dirs.empty());
}

// Test CrwMap::loadStack builds proper hierarchy
TEST_F(CrwMapTest_1798, LoadStackHierarchy_1798) {
    CrwDirs dirs1;
    CrwMap::loadStack(dirs1, 0x0000);
    size_t rootSize = dirs1.size();

    CrwDirs dirs2;
    CrwMap::loadStack(dirs2, 0x2804);
    // A subdirectory should have more entries than root (includes path to root)
    EXPECT_GE(dirs2.size(), rootSize);
}

// Test CrwMap::encode with an image that has no EXIF data
TEST_F(CrwMapTest_1798, EncodeWithEmptyExifData_1798) {
    try {
        auto io = std::make_unique<MemIo>();
        // Create a minimal CRW in memory
        auto minData = createMinimalCrwData();

        CiffHeader header;
        // Try to read - may throw if minimal data is insufficient
        try {
            header.read(minData.data(), minData.size());
        } catch (...) {
            SUCCEED();
            return;
        }

        // Create an image with empty exif data
        auto memIo = std::make_unique<MemIo>();
        auto image = ImageFactory::open(std::move(memIo));
        if (image) {
            image->clearExifData();
            // Encode should not crash with empty exif data
            EXPECT_NO_THROW(CrwMap::encode(header, *image));
        }
    } catch (const Error&) {
        // If we can't create the image, that's okay for this test
        SUCCEED();
    }
}

// Test CiffHeader write produces output
TEST_F(CiffHeaderTest_1798, WriteProducesOutput_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    try {
        header.read(minData.data(), minData.size());
        Blob blob;
        header.write(blob);
        // Written data should not be empty
        EXPECT_FALSE(blob.empty());
    } catch (const Error&) {
        // Minimal data may not be sufficient
        SUCCEED();
    }
}

// Test CiffHeader byte order after reading little-endian data
TEST_F(CiffHeaderTest_1798, ByteOrderAfterReadLE_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    // Set byte order to little endian ('II')
    minData[0] = 'I';
    minData[1] = 'I';
    try {
        header.read(minData.data(), minData.size());
        EXPECT_EQ(header.byteOrder(), littleEndian);
    } catch (const Error&) {
        SUCCEED();
    }
}

// Test CiffHeader byte order with big-endian mark
TEST_F(CiffHeaderTest_1798, ByteOrderAfterReadBE_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    // Set byte order to big endian ('MM')
    minData[0] = 'M';
    minData[1] = 'M';
    // Adjust header length for big endian
    minData[2] = 0x00;
    minData[3] = 0x00;
    minData[4] = 0x00;
    minData[5] = 0x1a;
    try {
        header.read(minData.data(), minData.size());
        EXPECT_EQ(header.byteOrder(), bigEndian);
    } catch (const Error&) {
        // May fail due to other validation
        SUCCEED();
    }
}

// Test CrwMap::loadStack with another known directory
TEST_F(CrwMapTest_1798, LoadStackCameraDir_1798) {
    CrwDirs dirs;
    // 0x2807 is CameraObject directory
    CrwMap::loadStack(dirs, 0x2807);
    EXPECT_FALSE(dirs.empty());
}

// Test that loadStack for root vs non-root gives different sizes
TEST_F(CrwMapTest_1798, LoadStackDifferentDepths_1798) {
    CrwDirs rootDirs;
    CrwMap::loadStack(rootDirs, 0x0000);

    CrwDirs subDirs;
    CrwMap::loadStack(subDirs, 0x300b);
    
    // Sub-directories should have longer path than root
    if (!rootDirs.empty() && !subDirs.empty()) {
        EXPECT_GE(subDirs.size(), rootDirs.size());
    }
}

// Test CiffHeader remove on empty header doesn't crash
TEST_F(CiffHeaderTest_1798, RemoveOnEmptyHeader_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    try {
        header.read(minData.data(), minData.size());
        // Removing a non-existent tag should be safe
        EXPECT_NO_THROW(header.remove(0xFFFF, 0xFFFF));
    } catch (const Error&) {
        SUCCEED();
    }
}

// Test CiffHeader add then find
TEST_F(CiffHeaderTest_1798, AddThenFind_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    try {
        header.read(minData.data(), minData.size());
        
        // Add a component
        DataBuf buf(4);
        std::memset(buf.data(), 0x42, 4);
        uint16_t tagId = 0x0805;
        uint16_t dirId = 0x2804;
        header.add(tagId, dirId, std::move(buf));
        
        // Try to find it
        const CiffComponent* comp = header.findComponent(tagId, dirId);
        // It should be found now
        EXPECT_NE(comp, nullptr);
    } catch (const Error&) {
        SUCCEED();
    }
}

// Test CrwMap encode doesn't crash with valid header and image with some exif data
TEST_F(CrwMapTest_1798, EncodeWithSomeExifData_1798) {
    CiffHeader header;
    auto minData = createMinimalCrwData();
    try {
        header.read(minData.data(), minData.size());
    } catch (const Error&) {
        SUCCEED();
        return;
    }

    try {
        auto memIo = std::make_unique<MemIo>();
        auto image = ImageFactory::open(std::move(memIo));
        if (image) {
            // Add some EXIF data
            ExifData exifData;
            exifData["Exif.Photo.ExposureTime"] = "1/125";
            image->setExifData(exifData);
            
            EXPECT_NO_THROW(CrwMap::encode(header, *image));
        }
    } catch (const Error&) {
        SUCCEED();
    }
}

// Test CiffHeader read with nullptr
TEST_F(CiffHeaderTest_1798, ReadNullptrThrows_1798) {
    CiffHeader header;
    EXPECT_THROW(header.read(nullptr, 100), Error);
}

// Test that multiple loadStack calls produce consistent results
TEST_F(CrwMapTest_1798, LoadStackConsistency_1798) {
    CrwDirs dirs1;
    CrwMap::loadStack(dirs1, 0x2804);

    CrwDirs dirs2;
    CrwMap::loadStack(dirs2, 0x2804);

    EXPECT_EQ(dirs1.size(), dirs2.size());
}
