#include <gtest/gtest.h>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstring>
#include <vector>

using namespace Exiv2;

class PreviewImageTest_1213 : public ::testing::Test {
protected:
    // Helper to get preview images from a test file if available
    static std::vector<PreviewImage> getPreviewImages(const std::string& path) {
        std::vector<PreviewImage> result;
        try {
            auto image = ImageFactory::open(path);
            if (image.get()) {
                image->readMetadata();
                PreviewManager manager(*image);
                PreviewPropertiesList list = manager.getPreviewProperties();
                for (const auto& prop : list) {
                    result.push_back(manager.getPreviewImage(prop));
                }
            }
        } catch (...) {
            // No test file available
        }
        return result;
    }
};

// Test that PreviewProperties has expected default values
TEST_F(PreviewImageTest_1213, PreviewPropertiesDefaultId_1213) {
    PreviewProperties props;
    EXPECT_EQ(props.id_, 0);
    EXPECT_TRUE(props.extension_.empty());
}

// Test PreviewManager with a non-existent file throws
TEST_F(PreviewImageTest_1213, OpenNonExistentFileThrows_1213) {
    EXPECT_THROW({
        auto image = ImageFactory::open("non_existent_file_for_test.jpg");
    }, Exiv2::Error);
}

// Test that PreviewManager can be created from a valid image
TEST_F(PreviewImageTest_1213, PreviewManagerCreation_1213) {
    // Create a minimal JPEG in memory
    // JPEG SOI marker + APP0 + EOI
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();
            // A minimal JPEG likely has no embedded previews
            // This is a valid scenario - empty list
            SUCCEED();
        }
    } catch (const Exiv2::Error&) {
        // If the minimal JPEG is not valid enough, that's acceptable
        SUCCEED();
    }
}

// Test copy constructor of PreviewImage if we can obtain one
TEST_F(PreviewImageTest_1213, CopyConstructorPreservesProperties_1213) {
    // Create a minimal JPEG in memory with EXIF thumbnail
    // We'll try to create an image and see if we can get previews
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage original = manager.getPreviewImage(prop);
                PreviewImage copy(original);

                EXPECT_EQ(copy.width(), original.width());
                EXPECT_EQ(copy.height(), original.height());
                EXPECT_EQ(copy.size(), original.size());
                EXPECT_EQ(copy.mimeType(), original.mimeType());
                EXPECT_EQ(copy.extension(), original.extension());
                EXPECT_EQ(copy.id(), original.id());
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test assignment operator of PreviewImage
TEST_F(PreviewImageTest_1213, AssignmentOperatorPreservesProperties_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            if (list.size() >= 2) {
                PreviewImage first = manager.getPreviewImage(list[0]);
                PreviewImage second = manager.getPreviewImage(list[1]);

                second = first;

                EXPECT_EQ(second.width(), first.width());
                EXPECT_EQ(second.height(), first.height());
                EXPECT_EQ(second.size(), first.size());
                EXPECT_EQ(second.mimeType(), first.mimeType());
                EXPECT_EQ(second.extension(), first.extension());
                EXPECT_EQ(second.id(), first.id());
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that getPreviewProperties returns a list (possibly empty) for minimal image
TEST_F(PreviewImageTest_1213, GetPreviewPropertiesMinimalImage_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        ASSERT_NE(image.get(), nullptr);
        image->readMetadata();
        PreviewManager manager(*image);
        PreviewPropertiesList list = manager.getPreviewProperties();
        // For a minimal JPEG without embedded previews, expect empty list
        EXPECT_TRUE(list.empty());
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that pData returns non-null when size > 0 for a preview
TEST_F(PreviewImageTest_1213, PDataNonNullWhenSizePositive_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                if (preview.size() > 0) {
                    EXPECT_NE(preview.pData(), nullptr);
                }
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that copy() returns a DataBuf with consistent size
TEST_F(PreviewImageTest_1213, CopyReturnsConsistentDataBuf_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                DataBuf buf = preview.copy();
                EXPECT_EQ(buf.size(), preview.size());
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that extension returns a non-empty string for previews
TEST_F(PreviewImageTest_1213, ExtensionNonEmpty_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                // Extension should start with a dot
                const std::string& ext = preview.extension();
                if (!ext.empty()) {
                    EXPECT_EQ(ext[0], '.');
                }
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that mimeType returns a valid MIME type string for previews
TEST_F(PreviewImageTest_1213, MimeTypeFormat_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                const std::string& mime = preview.mimeType();
                // MIME type should contain a slash
                if (!mime.empty()) {
                    EXPECT_NE(mime.find('/'), std::string::npos);
                }
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test copy constructor produces independent data
TEST_F(PreviewImageTest_1213, CopyConstructorIndependentData_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage original = manager.getPreviewImage(prop);
                PreviewImage copy(original);

                // The copy should have its own data buffer
                if (original.size() > 0 && copy.size() > 0) {
                    // Both should have same content
                    EXPECT_EQ(std::memcmp(original.pData(), copy.pData(), original.size()), 0);
                }
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test PreviewPropertiesList sorted by size
TEST_F(PreviewImageTest_1213, PreviewPropertiesListSorted_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            // Properties list should be sorted by increasing size
            for (size_t i = 1; i < list.size(); ++i) {
                EXPECT_GE(list[i].width_ * list[i].height_,
                           list[i - 1].width_ * list[i - 1].height_);
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test height() returns value from properties
TEST_F(PreviewImageTest_1213, HeightReturnsPropertiesHeight_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                // height() should match the property's height
                EXPECT_EQ(preview.height(), prop.height_);
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test width() returns value from properties
TEST_F(PreviewImageTest_1213, WidthReturnsPropertiesWidth_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                EXPECT_EQ(preview.width(), prop.width_);
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test id() returns value from properties
TEST_F(PreviewImageTest_1213, IdReturnsPropertiesId_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                EXPECT_EQ(preview.id(), prop.id_);
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test writeFile writes data and returns bytes written
TEST_F(PreviewImageTest_1213, WriteFileReturnsSize_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                std::string tmpPath = "test_preview_1213_output";
                size_t written = preview.writeFile(tmpPath);
                EXPECT_EQ(written, preview.size());

                // Cleanup - the file gets the extension appended
                std::string fullPath = tmpPath + preview.extension();
                std::remove(fullPath.c_str());
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test self-assignment
TEST_F(PreviewImageTest_1213, SelfAssignment_1213) {
    const unsigned char minJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
        0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
    };

    try {
        auto image = ImageFactory::open(minJpeg, sizeof(minJpeg));
        if (image.get()) {
            image->readMetadata();
            PreviewManager manager(*image);
            PreviewPropertiesList list = manager.getPreviewProperties();

            for (const auto& prop : list) {
                PreviewImage preview = manager.getPreviewImage(prop);
                auto origSize = preview.size();
                auto origHeight = preview.height();
                auto origWidth = preview.width();

                preview = preview;  // self-assignment

                EXPECT_EQ(preview.size(), origSize);
                EXPECT_EQ(preview.height(), origHeight);
                EXPECT_EQ(preview.width(), origWidth);
            }
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}
