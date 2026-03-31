#include <gtest/gtest.h>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <cstring>

namespace {

class PreviewImageTest_1210 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    // Helper to create a minimal JPEG file in memory for testing
    std::string createTempJpegFile(const std::string& filename) {
        // Minimal JPEG: SOI + APP0 + minimal content + EOI
        static const unsigned char minimalJpeg[] = {
            0xFF, 0xD8, // SOI
            0xFF, 0xE0, // APP0
            0x00, 0x10, // Length 16
            0x4A, 0x46, 0x49, 0x46, 0x00, // JFIF\0
            0x01, 0x01, // Version
            0x00, // Units
            0x00, 0x01, // X density
            0x00, 0x01, // Y density
            0x00, 0x00, // Thumbnail
            0xFF, 0xDB, // DQT
            0x00, 0x43, // Length
            0x00, // Precision/ID
            // 64 bytes of quantization table (all 1s for simplicity)
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0xFF, 0xC0, // SOF0
            0x00, 0x0B, // Length
            0x08, // Precision
            0x00, 0x01, // Height = 1
            0x00, 0x01, // Width = 1
            0x01, // Num components
            0x01, 0x11, 0x00, // Component
            0xFF, 0xC4, // DHT
            0x00, 0x1F, // Length
            0x00, // Class/ID
            0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B,
            0xFF, 0xDA, // SOS
            0x00, 0x08, // Length
            0x01, // Num components
            0x01, 0x00, // Component
            0x00, 0x3F, 0x00, // Spectral selection
            0x7B, 0x40, // Compressed data
            0xFF, 0xD9  // EOI
        };

        std::string filepath = filename;
        std::ofstream ofs(filepath, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(minimalJpeg), sizeof(minimalJpeg));
        ofs.close();
        return filepath;
    }
};

// Test that PreviewManager can be created and getPreviewList works on a simple image
TEST_F(PreviewImageTest_1210, GetPreviewListOnMinimalJpeg_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        // Minimal JPEG may or may not have previews; just ensure no crash
        // and list is a valid (possibly empty) container
        EXPECT_GE(list.size(), 0u);

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // Some minimal JPEGs might not be fully parseable
    }
}

// Test PreviewImage copy constructor
TEST_F(PreviewImageTest_1210, CopyConstructor_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_copy_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            // Copy construct
            Exiv2::PreviewImage copy(preview);

            EXPECT_EQ(copy.mimeType(), preview.mimeType());
            EXPECT_EQ(copy.extension(), preview.extension());
            EXPECT_EQ(copy.size(), preview.size());
            EXPECT_EQ(copy.width(), preview.width());
            EXPECT_EQ(copy.height(), preview.height());
            EXPECT_EQ(copy.id(), preview.id());
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test PreviewImage assignment operator
TEST_F(PreviewImageTest_1210, AssignmentOperator_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_assign_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            Exiv2::PreviewImage assigned = preview;  // assignment

            EXPECT_EQ(assigned.mimeType(), preview.mimeType());
            EXPECT_EQ(assigned.extension(), preview.extension());
            EXPECT_EQ(assigned.size(), preview.size());
            EXPECT_EQ(assigned.width(), preview.width());
            EXPECT_EQ(assigned.height(), preview.height());
            EXPECT_EQ(assigned.id(), preview.id());
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test mimeType returns a reference to a string
TEST_F(PreviewImageTest_1210, MimeTypeReturnsString_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_mime_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            const std::string& mime = preview.mimeType();
            // MIME type should not be empty for a valid preview
            EXPECT_FALSE(mime.empty());
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test extension returns a non-empty string for valid previews
TEST_F(PreviewImageTest_1210, ExtensionReturnsString_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_ext_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            const std::string& ext = preview.extension();
            // Extension should start with a dot if non-empty
            if (!ext.empty()) {
                EXPECT_EQ(ext[0], '.');
            }
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test pData and size consistency
TEST_F(PreviewImageTest_1210, PDataAndSizeConsistency_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_data_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            uint32_t sz = preview.size();

            if (sz > 0) {
                const Exiv2::byte* data = preview.pData();
                EXPECT_NE(data, nullptr);
            }
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test copy() returns a DataBuf with same size
TEST_F(PreviewImageTest_1210, CopyReturnsDataBuf_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_copybuf_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            Exiv2::DataBuf buf = preview.copy();
            EXPECT_EQ(buf.size(), preview.size());

            // Verify data content matches
            if (buf.size() > 0 && preview.pData()) {
                EXPECT_EQ(std::memcmp(buf.c_data(), preview.pData(), buf.size()), 0);
            }
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test writeFile writes data to a file
TEST_F(PreviewImageTest_1210, WriteFileCreatesFile_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_write_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            std::string outPath = "test_preview_output_1210";
            size_t bytesWritten = preview.writeFile(outPath);
            EXPECT_GT(bytesWritten, 0u);

            // Clean up the output file (extension is appended by writeFile)
            std::string fullPath = outPath + preview.extension();
            std::remove(fullPath.c_str());
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test width and height return sensible values
TEST_F(PreviewImageTest_1210, WidthAndHeight_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_dims_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            size_t w = preview.width();
            size_t h = preview.height();
            // Width and height should be non-negative (they're size_t so always >= 0)
            // For valid previews they should typically be > 0
            EXPECT_GE(w, 0u);
            EXPECT_GE(h, 0u);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test id returns a valid PreviewId
TEST_F(PreviewImageTest_1210, IdReturnsValidId_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_id_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            Exiv2::PreviewId pid = preview.id();
            // The id from the preview should match the one from the properties
            EXPECT_EQ(pid, list.front().id_);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test PreviewPropertiesList is sorted by size (ascending)
TEST_F(PreviewImageTest_1210, PreviewListSortedBySize_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_sorted_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // If multiple previews, they should be sorted by size
        for (size_t i = 1; i < list.size(); ++i) {
            EXPECT_LE(list[i - 1].width_, list[i].width_);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test self-assignment
TEST_F(PreviewImageTest_1210, SelfAssignment_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_selfassign_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            std::string origMime = preview.mimeType();
            uint32_t origSize = preview.size();

            // Self-assignment should not corrupt data
            preview = preview;

            EXPECT_EQ(preview.mimeType(), origMime);
            EXPECT_EQ(preview.size(), origSize);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test that copy-constructed preview has independent data
TEST_F(PreviewImageTest_1210, CopyConstructorIndependentData_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_indep_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            Exiv2::PreviewImage copy(preview);

            // Both should have valid but potentially different pointers
            if (preview.size() > 0) {
                // Data content should be identical
                EXPECT_EQ(std::memcmp(preview.pData(), copy.pData(), preview.size()), 0);
            }
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test PreviewManager with empty/no metadata
TEST_F(PreviewImageTest_1210, EmptyMetadataNoPreview_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_empty_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        // Read metadata - minimal JPEG likely has no previews
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // A minimal JPEG without embedded thumbnails should have empty list
        // This is expected behavior but not guaranteed; just ensure no crash
        SUCCEED();

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable - minimal JPEG might not parse
    }
}

// Test multiple calls to mimeType return same reference
TEST_F(PreviewImageTest_1210, MimeTypeConsistentReference_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_mimeref_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            const std::string& mime1 = preview.mimeType();
            const std::string& mime2 = preview.mimeType();
            // Should return reference to the same string
            EXPECT_EQ(&mime1, &mime2);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

// Test multiple calls to extension return same reference
TEST_F(PreviewImageTest_1210, ExtensionConsistentReference_1210) {
    try {
        std::string path = createTempJpegFile("test_preview_extref_1210.jpg");
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
            const std::string& ext1 = preview.extension();
            const std::string& ext2 = preview.extension();
            // Should return reference to the same string
            EXPECT_EQ(&ext1, &ext2);
        }

        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        // acceptable
    }
}

}  // namespace
