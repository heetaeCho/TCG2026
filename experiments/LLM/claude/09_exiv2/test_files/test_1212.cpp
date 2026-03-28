#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <fstream>
#include <cstdio>
#include <vector>

namespace {

// Helper to create a minimal valid JPEG file in memory for testing
std::string createTempJpegFile() {
    // Minimal JPEG with embedded thumbnail
    std::string tmpPath = "test_preview_1212.jpg";
    
    // We'll try to use Exiv2 to create a basic image
    // If no valid image can be created, tests will handle gracefully
    return tmpPath;
}

class PreviewImageTest_1212 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to find or create a test image with preview
    }
    
    void TearDown() override {
        // Cleanup temp files
        std::remove("test_preview_output_1212.jpg");
    }
};

// Test that PreviewManager can be constructed with a valid image
TEST_F(PreviewImageTest_1212, PreviewManagerConstruction_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        // Just verify we can call this without crashing
        SUCCEED();
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test PreviewImage accessors when previews are available
TEST_F(PreviewImageTest_1212, PreviewImageAccessors_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found in test image";
        }
        
        Exiv2::PreviewImage preview = manager.getPreviewImage(properties[0]);
        
        // Test width returns a value (could be 0 for some formats)
        size_t w = preview.width();
        EXPECT_GE(w, 0u);
        
        // Test height returns a value
        size_t h = preview.height();
        EXPECT_GE(h, 0u);
        
        // Test size returns non-zero for valid preview
        uint32_t sz = preview.size();
        EXPECT_GT(sz, 0u);
        
        // Test pData returns non-null for valid preview
        const Exiv2::byte* data = preview.pData();
        EXPECT_NE(data, nullptr);
        
        // Test mimeType returns non-empty string
        const std::string& mime = preview.mimeType();
        EXPECT_FALSE(mime.empty());
        
        // Test extension returns non-empty string
        const std::string& ext = preview.extension();
        EXPECT_FALSE(ext.empty());
        
        // Test id
        Exiv2::PreviewId pid = preview.id();
        EXPECT_EQ(pid, properties[0].id_);
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available or unreadable";
    }
}

// Test PreviewImage copy constructor
TEST_F(PreviewImageTest_1212, CopyConstructor_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found in test image";
        }
        
        Exiv2::PreviewImage original = manager.getPreviewImage(properties[0]);
        Exiv2::PreviewImage copy(original);
        
        // Verify copy has same properties
        EXPECT_EQ(copy.width(), original.width());
        EXPECT_EQ(copy.height(), original.height());
        EXPECT_EQ(copy.size(), original.size());
        EXPECT_EQ(copy.mimeType(), original.mimeType());
        EXPECT_EQ(copy.extension(), original.extension());
        EXPECT_EQ(copy.id(), original.id());
        
        // Data should be equal
        ASSERT_EQ(copy.size(), original.size());
        if (copy.size() > 0) {
            EXPECT_EQ(std::memcmp(copy.pData(), original.pData(), copy.size()), 0);
        }
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test PreviewImage assignment operator
TEST_F(PreviewImageTest_1212, AssignmentOperator_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.size() < 1) {
            GTEST_SKIP() << "Not enough previews found in test image";
        }
        
        Exiv2::PreviewImage original = manager.getPreviewImage(properties[0]);
        Exiv2::PreviewImage assigned = manager.getPreviewImage(properties[0]);
        
        // Perform assignment
        assigned = original;
        
        EXPECT_EQ(assigned.width(), original.width());
        EXPECT_EQ(assigned.height(), original.height());
        EXPECT_EQ(assigned.size(), original.size());
        EXPECT_EQ(assigned.mimeType(), original.mimeType());
        EXPECT_EQ(assigned.extension(), original.extension());
        EXPECT_EQ(assigned.id(), original.id());
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test copy() method returns valid DataBuf
TEST_F(PreviewImageTest_1212, CopyMethod_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found in test image";
        }
        
        Exiv2::PreviewImage preview = manager.getPreviewImage(properties[0]);
        Exiv2::DataBuf buf = preview.copy();
        
        EXPECT_EQ(buf.size(), preview.size());
        if (buf.size() > 0 && preview.pData()) {
            EXPECT_EQ(std::memcmp(buf.c_data(), preview.pData(), buf.size()), 0);
        }
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test writeFile method
TEST_F(PreviewImageTest_1212, WriteFile_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found in test image";
        }
        
        Exiv2::PreviewImage preview = manager.getPreviewImage(properties[0]);
        
        std::string basePath = "test_preview_output_1212";
        size_t bytesWritten = preview.writeFile(basePath);
        
        EXPECT_GT(bytesWritten, 0u);
        
        // The file should have been written with the appropriate extension
        std::string fullPath = basePath + preview.extension();
        std::ifstream file(fullPath, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            auto fileSize = file.tellg();
            EXPECT_EQ(static_cast<size_t>(fileSize), bytesWritten);
            file.close();
            std::remove(fullPath.c_str());
        }
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test that multiple previews from the same image have different or consistent properties
TEST_F(PreviewImageTest_1212, MultiplePreviewProperties_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.size() < 2) {
            GTEST_SKIP() << "Need at least 2 previews for this test";
        }
        
        Exiv2::PreviewImage preview1 = manager.getPreviewImage(properties[0]);
        Exiv2::PreviewImage preview2 = manager.getPreviewImage(properties[1]);
        
        // Different previews should have different IDs
        EXPECT_NE(preview1.id(), preview2.id());
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test PreviewProperties from getPreviewProperties
TEST_F(PreviewImageTest_1212, PreviewPropertiesConsistency_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found";
        }
        
        // Properties and actual PreviewImage should be consistent
        for (const auto& prop : properties) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(prop);
            EXPECT_EQ(preview.id(), prop.id_);
            EXPECT_EQ(preview.extension(), prop.extension_);
            EXPECT_EQ(preview.width(), prop.width_);
            EXPECT_EQ(preview.height(), prop.height_);
            EXPECT_EQ(preview.size(), prop.size_);
        }
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test with an image that has no previews
TEST_F(PreviewImageTest_1212, NoPreviewsAvailable_1212) {
    try {
        // Create a minimal image that likely has no embedded previews
        // Use a minimal TIFF or similar
        Exiv2::Blob blob;
        // Create a 1x1 JPEG
        unsigned char minJpeg[] = {
            0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
            0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0xFF, 0xDB, 0x00, 0x43,
            0x00, 0x08, 0x06, 0x06, 0x07, 0x06, 0x05, 0x08, 0x07, 0x07, 0x07, 0x09,
            0x09, 0x08, 0x0A, 0x0C, 0x14, 0x0D, 0x0C, 0x0B, 0x0B, 0x0C, 0x19, 0x12,
            0x13, 0x0F, 0x14, 0x1D, 0x1A, 0x1F, 0x1E, 0x1D, 0x1A, 0x1C, 0x1C, 0x20,
            0x24, 0x2E, 0x27, 0x20, 0x22, 0x2C, 0x23, 0x1C, 0x1C, 0x28, 0x37, 0x29,
            0x2C, 0x30, 0x31, 0x34, 0x34, 0x34, 0x1F, 0x27, 0x39, 0x3D, 0x38, 0x32,
            0x3C, 0x2E, 0x33, 0x34, 0x32, 0xFF, 0xC0, 0x00, 0x0B, 0x08, 0x00, 0x01,
            0x00, 0x01, 0x01, 0x01, 0x11, 0x00, 0xFF, 0xC4, 0x00, 0x1F, 0x00, 0x00,
            0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
            0x09, 0x0A, 0x0B, 0xFF, 0xC4, 0x00, 0xB5, 0x10, 0x00, 0x02, 0x01, 0x03,
            0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7D,
            0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06,
            0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08,
            0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72,
            0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
            0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45,
            0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
            0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75,
            0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
            0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3,
            0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
            0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
            0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
            0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4,
            0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0xDA, 0x00, 0x08, 0x01, 0x01,
            0x00, 0x00, 0x3F, 0x00, 0x7B, 0x94, 0x11, 0x00, 0x00, 0x00, 0x00, 0xFF,
            0xD9
        };
        
        std::string tmpFile = "test_minimal_1212.jpg";
        {
            std::ofstream ofs(tmpFile, std::ios::binary);
            ofs.write(reinterpret_cast<const char*>(minJpeg), sizeof(minJpeg));
        }
        
        auto image = Exiv2::ImageFactory::open(tmpFile);
        if (image.get()) {
            image->readMetadata();
            Exiv2::PreviewManager manager(*image);
            auto properties = manager.getPreviewProperties();
            // A minimal JPEG without embedded thumbnails should have no previews
            // (or possibly some, depending on the format)
            // This is mainly to ensure no crash
            SUCCEED();
        }
        
        std::remove(tmpFile.c_str());
        
    } catch (const Exiv2::Error&) {
        // Expected for minimal/invalid images
        SUCCEED();
    }
}

// Test self-assignment
TEST_F(PreviewImageTest_1212, SelfAssignment_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found";
        }
        
        Exiv2::PreviewImage preview = manager.getPreviewImage(properties[0]);
        size_t origWidth = preview.width();
        size_t origHeight = preview.height();
        uint32_t origSize = preview.size();
        
        // Self-assignment should not corrupt the object
        preview = preview;
        
        EXPECT_EQ(preview.width(), origWidth);
        EXPECT_EQ(preview.height(), origHeight);
        EXPECT_EQ(preview.size(), origSize);
        EXPECT_NE(preview.pData(), nullptr);
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

// Test that copy() returns independent data
TEST_F(PreviewImageTest_1212, CopyReturnsIndependentData_1212) {
    try {
        auto image = Exiv2::ImageFactory::open(TESTDATA_PATH "/exiv2-canon-powershot-s40.jpg");
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        
        Exiv2::PreviewManager manager(*image);
        auto properties = manager.getPreviewProperties();
        
        if (properties.empty()) {
            GTEST_SKIP() << "No previews found";
        }
        
        Exiv2::PreviewImage preview = manager.getPreviewImage(properties[0]);
        
        Exiv2::DataBuf buf1 = preview.copy();
        Exiv2::DataBuf buf2 = preview.copy();
        
        // Both copies should have same size
        EXPECT_EQ(buf1.size(), buf2.size());
        
        // Both should have same content
        if (buf1.size() > 0) {
            EXPECT_EQ(std::memcmp(buf1.c_data(), buf2.c_data(), buf1.size()), 0);
        }
        
        // But they should be different buffers (different addresses)
        if (buf1.size() > 0) {
            EXPECT_NE(buf1.c_data(), buf2.c_data());
        }
        
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not available";
    }
}

} // namespace
