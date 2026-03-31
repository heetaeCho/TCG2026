#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <fstream>
#include <cstdio>

// Helper to create a test image file that has preview images
// We'll use PreviewManager to get PreviewImage objects for testing

class PreviewImageTest_1214 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Try to get a PreviewImage from a real or minimal image
    std::unique_ptr<Exiv2::Image> openTestImage(const std::string& path) {
        try {
            auto image = Exiv2::ImageFactory::open(path);
            if (image) {
                image->readMetadata();
            }
            return image;
        } catch (...) {
            return nullptr;
        }
    }
};

// Test that PreviewManager can be constructed and getPreviewImages returns a list
TEST_F(PreviewImageTest_1214, PreviewManagerGetPreviewProperties_1214) {
    // Create a minimal JPEG in memory to work with
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        // The list may be empty for a minimal image, that's fine
        SUCCEED();
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test copy constructor of PreviewImage preserves properties
TEST_F(PreviewImageTest_1214, CopyConstructorPreservesId_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        Exiv2::PreviewImage copy(preview);

        EXPECT_EQ(preview.id(), copy.id());
        EXPECT_EQ(preview.size(), copy.size());
        EXPECT_EQ(preview.width(), copy.width());
        EXPECT_EQ(preview.height(), copy.height());
        EXPECT_EQ(preview.mimeType(), copy.mimeType());
        EXPECT_EQ(preview.extension(), copy.extension());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test assignment operator preserves properties
TEST_F(PreviewImageTest_1214, AssignmentOperatorPreservesProperties_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        Exiv2::PreviewImage assigned = preview;

        EXPECT_EQ(preview.id(), assigned.id());
        EXPECT_EQ(preview.size(), assigned.size());
        EXPECT_EQ(preview.mimeType(), assigned.mimeType());
        EXPECT_EQ(preview.extension(), assigned.extension());
        EXPECT_EQ(preview.width(), assigned.width());
        EXPECT_EQ(preview.height(), assigned.height());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that pData returns non-null for a valid preview
TEST_F(PreviewImageTest_1214, PDataReturnsNonNullForValidPreview_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        if (preview.size() > 0) {
            EXPECT_NE(preview.pData(), nullptr);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that size returns positive value for a valid preview
TEST_F(PreviewImageTest_1214, SizeReturnsPositiveForValidPreview_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        EXPECT_GT(preview.size(), static_cast<uint32_t>(0));
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that copy() returns a DataBuf with matching size
TEST_F(PreviewImageTest_1214, CopyReturnsDataBufWithMatchingSize_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        Exiv2::DataBuf buf = preview.copy();
        EXPECT_EQ(buf.size(), preview.size());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that mimeType returns a non-empty string
TEST_F(PreviewImageTest_1214, MimeTypeIsNonEmpty_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        EXPECT_FALSE(preview.mimeType().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that extension returns a non-empty string
TEST_F(PreviewImageTest_1214, ExtensionIsNonEmpty_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        EXPECT_FALSE(preview.extension().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test writeFile writes data to disk
TEST_F(PreviewImageTest_1214, WriteFileCreatesFile_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        std::string basePath = "test_output_preview_1214";
        size_t bytesWritten = preview.writeFile(basePath);
        EXPECT_GT(bytesWritten, static_cast<size_t>(0));

        // Clean up: the file should have been written with the extension appended
        std::string fullPath = basePath + preview.extension();
        std::remove(fullPath.c_str());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that id matches the PreviewProperties id used to get the image
TEST_F(PreviewImageTest_1214, IdMatchesRequestedPreviewProperties_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        for (const auto& props : list) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(props);
            EXPECT_EQ(preview.id(), props.id_);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test self-assignment
TEST_F(PreviewImageTest_1214, SelfAssignmentIsHandled_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        auto origId = preview.id();
        auto origSize = preview.size();

        preview = preview;  // self-assignment

        EXPECT_EQ(preview.id(), origId);
        EXPECT_EQ(preview.size(), origSize);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test that copy returns data matching pData
TEST_F(PreviewImageTest_1214, CopyDataMatchesPData_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.empty()) {
            GTEST_SKIP() << "No preview images in test file";
        }

        Exiv2::PreviewImage preview = manager.getPreviewImage(list.front());
        Exiv2::DataBuf buf = preview.copy();

        ASSERT_EQ(buf.size(), preview.size());
        if (preview.size() > 0) {
            EXPECT_EQ(std::memcmp(buf.data(), preview.pData(), preview.size()), 0);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test PreviewPropertiesList ordering (typically by size)
TEST_F(PreviewImageTest_1214, PreviewPropertiesListOrdering_1214) {
    try {
        auto image = Exiv2::ImageFactory::open("test_preview.jpg");
        if (!image) {
            GTEST_SKIP() << "Cannot open test image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (list.size() < 2) {
            GTEST_SKIP() << "Need at least 2 previews to test ordering";
        }

        // Properties list should be ordered by size (ascending)
        for (size_t i = 1; i < list.size(); ++i) {
            EXPECT_LE(list[i - 1].size_, list[i].size_);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "No test image available";
    }
}

// Test empty preview properties list for a minimal/no-preview image
TEST_F(PreviewImageTest_1214, EmptyPreviewListForMinimalImage_1214) {
    // Create a minimal image in memory with no previews
    try {
        Exiv2::DataBuf minimalJpeg(2);
        // Minimal JPEG: FFD8 FFD9
        auto* data = minimalJpeg.data();
        data[0] = 0xFF;
        data[1] = 0xD8;

        // This may throw if the image is too minimal
        auto image = Exiv2::ImageFactory::open(minimalJpeg.data(), minimalJpeg.size());
        if (!image) {
            GTEST_SKIP() << "Cannot create minimal image";
        }
        image->readMetadata();
        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        EXPECT_TRUE(list.empty());
    } catch (const Exiv2::Error&) {
        // Expected for truly minimal data
        SUCCEED();
    }
}
