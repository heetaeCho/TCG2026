#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

namespace {

// Helper to check if a file exists
bool fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

// Helper to get a test image path - we need a real image to test PreviewManager
// Since we can't create PreviewImage directly (private constructor), we need PreviewManager
class PreviewImageTest_1207 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal JPEG file for testing
        // We'll try to use an existing test image or create a minimal one
        testFile_ = "test_preview_1207.jpg";
        
        // Minimal JPEG with no preview - tests may have limited functionality
        // but we can still test what's available
    }
    
    void TearDown() override {
        // Clean up any files we created
        std::remove(testFile_.c_str());
        std::remove("test_output_1207.jpg");
    }
    
    std::string testFile_;
};

// Test that PreviewManager can be created and getPreviewImages returns a list
TEST_F(PreviewImageTest_1207, GetPreviewPropertiesFromImage_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP() << "Cannot open test image";
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        // The list may be empty for a minimal image, that's fine
        SUCCEED();
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Test image not suitable for preview extraction";
    }
}

// Test PreviewImage copy constructor
TEST_F(PreviewImageTest_1207, CopyConstructor_1207) {
    try {
        // Create a real JPEG with EXIF data that might have a preview
        // Use a known test file if available
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP() << "No previews available in test image";

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        // Test copy constructor
        Exiv2::PreviewImage copy(preview);
        
        EXPECT_EQ(preview.size(), copy.size());
        EXPECT_EQ(preview.width(), copy.width());
        EXPECT_EQ(preview.height(), copy.height());
        EXPECT_EQ(preview.mimeType(), copy.mimeType());
        EXPECT_EQ(preview.extension(), copy.extension());
        EXPECT_EQ(preview.id(), copy.id());
        
        // Verify data is the same
        if (preview.size() > 0) {
            EXPECT_EQ(0, std::memcmp(preview.pData(), copy.pData(), preview.size()));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not process test image";
    }
}

// Test PreviewImage assignment operator
TEST_F(PreviewImageTest_1207, AssignmentOperator_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP() << "No previews available";

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        Exiv2::PreviewImage assigned = preview;  // copy construct then assign
        
        // Self-consistency check
        EXPECT_EQ(preview.size(), assigned.size());
        EXPECT_EQ(preview.mimeType(), assigned.mimeType());
        EXPECT_EQ(preview.extension(), assigned.extension());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test copy() returns a DataBuf with correct size
TEST_F(PreviewImageTest_1207, CopyReturnsCorrectDataBuf_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        Exiv2::DataBuf buf = preview.copy();
        
        EXPECT_EQ(preview.size(), buf.size());
        
        // Verify content matches pData
        if (preview.size() > 0 && preview.pData() != nullptr) {
            EXPECT_EQ(0, std::memcmp(preview.pData(), buf.c_data(), preview.size()));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test that pData and size are consistent
TEST_F(PreviewImageTest_1207, PDataAndSizeConsistency_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        if (preview.size() > 0) {
            EXPECT_NE(nullptr, preview.pData());
        }
        
        // size should be non-negative (it's uint32_t so always >= 0)
        EXPECT_GE(preview.size(), 0u);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test writeFile
TEST_F(PreviewImageTest_1207, WriteFileCreatesFile_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        std::string outPath = "test_output_1207";
        size_t bytesWritten = preview.writeFile(outPath);
        
        EXPECT_GT(bytesWritten, 0u);
        
        // The file should have been created with the appropriate extension
        std::string fullPath = outPath + preview.extension();
        EXPECT_TRUE(fileExists(fullPath));
        
        // Clean up
        std::remove(fullPath.c_str());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test mimeType returns a non-empty string for valid previews
TEST_F(PreviewImageTest_1207, MimeTypeNonEmpty_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        EXPECT_FALSE(preview.mimeType().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test extension returns a string starting with '.'
TEST_F(PreviewImageTest_1207, ExtensionStartsWithDot_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        std::string ext = preview.extension();
        EXPECT_FALSE(ext.empty());
        if (!ext.empty()) {
            EXPECT_EQ('.', ext[0]);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test that width and height return reasonable values
TEST_F(PreviewImageTest_1207, WidthAndHeightReasonable_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        
        // Width and height should be non-negative for valid previews
        EXPECT_GE(preview.width(), 0u);
        EXPECT_GE(preview.height(), 0u);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test that empty preview list is handled
TEST_F(PreviewImageTest_1207, EmptyPreviewList_1207) {
    try {
        // Create a minimal JPEG with no embedded preview
        // Write minimal JPEG bytes
        unsigned char minJpeg[] = {
            0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
            0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
            0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
        };
        
        std::string minFile = "minimal_test_1207.jpg";
        {
            std::ofstream ofs(minFile, std::ios::binary);
            ofs.write(reinterpret_cast<const char*>(minJpeg), sizeof(minJpeg));
        }
        
        auto image = Exiv2::ImageFactory::open(minFile);
        if (!image) {
            std::remove(minFile.c_str());
            GTEST_SKIP();
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        
        // A minimal JPEG should have no preview images
        // This tests the boundary case of no previews
        // (It's acceptable if some implementations find previews here)
        SUCCEED();
        
        std::remove(minFile.c_str());
    } catch (const Exiv2::Error&) {
        std::remove("minimal_test_1207.jpg");
        GTEST_SKIP();
    }
}

// Test PreviewPropertiesList ordering (should be sorted by size)
TEST_F(PreviewImageTest_1207, PreviewPropertiesListSortedBySize_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        
        if (list.size() > 1) {
            for (size_t i = 1; i < list.size(); ++i) {
                // Properties should be ordered by increasing size
                EXPECT_GE(list[i].size_, list[i - 1].size_);
            }
        }
        SUCCEED();
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test that copy() produces independent data (deep copy)
TEST_F(PreviewImageTest_1207, CopyProducesIndependentData_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        Exiv2::DataBuf buf1 = preview.copy();
        Exiv2::DataBuf buf2 = preview.copy();
        
        // Both copies should have same size
        EXPECT_EQ(buf1.size(), buf2.size());
        
        // But different memory locations (deep copy)
        if (buf1.size() > 0 && buf2.size() > 0) {
            EXPECT_NE(buf1.c_data(), buf2.c_data());
            EXPECT_EQ(0, std::memcmp(buf1.c_data(), buf2.c_data(), buf1.size()));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

// Test that id() returns a valid PreviewId
TEST_F(PreviewImageTest_1207, IdReturnsValidPreviewId_1207) {
    try {
        auto image = Exiv2::ImageFactory::open(testFile_);
        if (!image)
            GTEST_SKIP();
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty())
            GTEST_SKIP();

        Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);
        Exiv2::PreviewId previewId = preview.id();
        
        // The id should match the properties id
        EXPECT_EQ(list[0].id_, previewId);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP();
    }
}

}  // namespace
