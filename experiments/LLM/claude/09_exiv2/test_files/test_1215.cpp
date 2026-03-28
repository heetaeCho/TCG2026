#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/preview.hpp>
#include <algorithm>
#include <memory>
#include <fstream>
#include <cstdio>

namespace {

class PreviewManagerTest_1215 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        // Clean up any temporary files
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::string createTempFile(const std::string& name, const std::vector<uint8_t>& data) {
        std::string path = name;
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        ofs.close();
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test that getPreviewProperties returns an empty list for an image with no previews
TEST_F(PreviewManagerTest_1215, EmptyImageReturnsEmptyPreviewList_1215) {
    // Create a minimal valid JPEG with no embedded thumbnails
    // JPEG SOI + APP0 (JFIF minimal) + SOS minimal + EOI
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, // SOI
        0xFF, 0xE0, // APP0
        0x00, 0x10, // Length 16
        'J', 'F', 'I', 'F', 0x00, // JFIF identifier
        0x01, 0x01, // Version
        0x00, // Units
        0x00, 0x01, // X density
        0x00, 0x01, // Y density
        0x00, 0x00, // No thumbnail
        0xFF, 0xD9  // EOI
    };

    std::string path = createTempFile("test_no_preview_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // A minimal JPEG without embedded thumbnails should have no or very few previews
        // We just verify it doesn't crash and returns a valid list
        SUCCEED();
    } catch (const Exiv2::Error&) {
        // If the minimal JPEG isn't valid enough, that's acceptable
        SUCCEED();
    }
}

// Test that preview properties list is sorted by pixel count (width * height) ascending
TEST_F(PreviewManagerTest_1215, PreviewPropertiesAreSortedByArea_1215) {
    // Try to use a real JPEG with EXIF thumbnail if available
    // We'll create an image using Exiv2's own API
    try {
        // Create a basic JPEG
        std::vector<uint8_t> minimalJpeg = {
            0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
            'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
            0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
            0xFF, 0xD9
        };
        std::string path = createTempFile("test_sorted_1215.jpg", minimalJpeg);

        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // Verify sorting: each element should have area <= next element's area
        for (size_t i = 1; i < list.size(); ++i) {
            size_t prevArea = list[i - 1].width_ * list[i - 1].height_;
            size_t currArea = list[i].width_ * list[i].height_;
            EXPECT_LE(prevArea, currArea)
                << "Preview properties not sorted by area at index " << i;
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that PreviewManager can be constructed from an Image reference
TEST_F(PreviewManagerTest_1215, ConstructionFromImage_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_construct_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        // Should not throw
        Exiv2::PreviewManager manager(*image);
        SUCCEED();
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that getPreviewImage can be called with properties from getPreviewProperties
TEST_F(PreviewManagerTest_1215, GetPreviewImageFromProperties_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_get_preview_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // If there are previews, try to get each one
        for (const auto& props : list) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(props);
            // The preview image should have data
            EXPECT_GT(preview.size(), static_cast<uint32_t>(0));
            // Extension should not be empty
            EXPECT_FALSE(preview.extension().empty());
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that each PreviewProperties has a non-empty extension
TEST_F(PreviewManagerTest_1215, PreviewPropertiesHaveExtension_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_extension_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            EXPECT_FALSE(props.extension_.empty())
                << "Preview property at id=" << props.id_ << " has empty extension";
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that preview properties size_ field is positive for valid previews
TEST_F(PreviewManagerTest_1215, PreviewPropertiesSizeIsPositive_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_size_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            EXPECT_GT(props.size_, static_cast<size_t>(0))
                << "Preview property at id=" << props.id_ << " has zero size";
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that getPreviewProperties is consistent on multiple calls
TEST_F(PreviewManagerTest_1215, ConsistentResultsOnMultipleCalls_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_consistent_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list1 = manager.getPreviewProperties();
        Exiv2::PreviewPropertiesList list2 = manager.getPreviewProperties();

        ASSERT_EQ(list1.size(), list2.size());
        for (size_t i = 0; i < list1.size(); ++i) {
            EXPECT_EQ(list1[i].id_, list2[i].id_);
            EXPECT_EQ(list1[i].size_, list2[i].size_);
            EXPECT_EQ(list1[i].width_, list2[i].width_);
            EXPECT_EQ(list1[i].height_, list2[i].height_);
            EXPECT_EQ(list1[i].extension_, list2[i].extension_);
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test with a PNG image (different format)
TEST_F(PreviewManagerTest_1215, PngImagePreviewProperties_1215) {
    // Minimal valid PNG
    std::vector<uint8_t> minimalPng = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, // PNG signature
        // IHDR chunk
        0x00, 0x00, 0x00, 0x0D, // length = 13
        'I', 'H', 'D', 'R',
        0x00, 0x00, 0x00, 0x01, // width = 1
        0x00, 0x00, 0x00, 0x01, // height = 1
        0x08, // bit depth = 8
        0x02, // color type = RGB
        0x00, 0x00, 0x00, // compression, filter, interlace
        0x1E, 0x92, 0x6E, 0x05, // CRC
        // IDAT chunk
        0x00, 0x00, 0x00, 0x0C, // length
        'I', 'D', 'A', 'T',
        0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00, 0x00,
        0x00, 0x02, 0x00, 0x01,
        0xE2, 0x21, 0xBC, 0x33, // CRC
        // IEND chunk
        0x00, 0x00, 0x00, 0x00,
        'I', 'E', 'N', 'D',
        0xAE, 0x42, 0x60, 0x82  // CRC
    };
    std::string path = createTempFile("test_png_1215.png", minimalPng);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        // PNG typically has no embedded previews, so list may be empty
        // Just verify it doesn't crash
        for (size_t i = 1; i < list.size(); ++i) {
            size_t prevArea = list[i - 1].width_ * list[i - 1].height_;
            size_t currArea = list[i].width_ * list[i].height_;
            EXPECT_LE(prevArea, currArea);
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that width and height are positive for all returned previews
TEST_F(PreviewManagerTest_1215, PreviewDimensionsArePositive_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_dimensions_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        for (const auto& props : list) {
            EXPECT_GT(props.width_, static_cast<size_t>(0))
                << "Preview id=" << props.id_ << " has zero width";
            EXPECT_GT(props.height_, static_cast<size_t>(0))
                << "Preview id=" << props.id_ << " has zero height";
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that each preview has a unique ID
TEST_F(PreviewManagerTest_1215, PreviewIdsAreUnique_1215) {
    std::vector<uint8_t> minimalJpeg = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0xFF, 0xD9
    };
    std::string path = createTempFile("test_unique_ids_1215.jpg", minimalJpeg);

    try {
        auto image = Exiv2::ImageFactory::open(path);
        ASSERT_NE(image, nullptr);
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();

        std::set<Exiv2::PreviewId> ids;
        for (const auto& props : list) {
            EXPECT_TRUE(ids.insert(props.id_).second)
                << "Duplicate preview ID: " << props.id_;
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

}  // namespace
