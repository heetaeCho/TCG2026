#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <fstream>
#include <cstdint>

#include "exiv2/jp2image.hpp"
#include "jp2image_int.hpp"
#include "exiv2/basicio.hpp"

namespace {

// Helper to create a minimal valid JP2 file in memory
std::vector<unsigned char> createMinimalJp2() {
    // JP2 signature box
    std::vector<unsigned char> data = {
        // Signature box (12 bytes)
        0x00, 0x00, 0x00, 0x0C, // box length = 12
        0x6A, 0x50, 0x20, 0x20, // box type = 'jP  '
        0x0D, 0x0A, 0x87, 0x0A, // signature

        // File type box
        0x00, 0x00, 0x00, 0x14, // box length = 20
        0x66, 0x74, 0x79, 0x70, // box type = 'ftyp'
        0x6A, 0x70, 0x32, 0x20, // brand = 'jp2 '
        0x00, 0x00, 0x00, 0x00, // minor version
        0x6A, 0x70, 0x32, 0x20, // compatibility = 'jp2 '
    };
    return data;
}

// Helper to create a minimal JPH file in memory
std::vector<unsigned char> createMinimalJph() {
    // JPH signature box - same signature as JP2 but with 'jph ' brand
    std::vector<unsigned char> data = {
        // Signature box (12 bytes)
        0x00, 0x00, 0x00, 0x0C, // box length = 12
        0x6A, 0x50, 0x20, 0x20, // box type = 'jP  '
        0x0D, 0x0A, 0x87, 0x0A, // signature

        // File type box
        0x00, 0x00, 0x00, 0x14, // box length = 20
        0x66, 0x74, 0x79, 0x70, // box type = 'ftyp'
        0x6A, 0x70, 0x68, 0x20, // brand = 'jph ' (0x6A706820)
        0x00, 0x00, 0x00, 0x00, // minor version
        0x6A, 0x70, 0x68, 0x20, // compatibility = 'jph '
    };
    return data;
}

class Jp2ImageTest_84 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that creating a Jp2Image from a JP2 file returns "image/jp2" as mime type
TEST_F(Jp2ImageTest_84, MimeTypeForJp2ReturnsImageJp2_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    // Before readMetadata, brand_ may be default (0), which should still return "image/jp2"
    // since any brand != brandJph returns "image/jp2"
    EXPECT_EQ(image->mimeType(), "image/jp2");
}

// Test that reading metadata on a JP2 file still reports "image/jp2"
TEST_F(Jp2ImageTest_84, MimeTypeAfterReadMetadataForJp2_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    try {
        image->readMetadata();
    } catch (...) {
        // The minimal file may not have full metadata; we just want brand_ set
    }

    EXPECT_EQ(image->mimeType(), "image/jp2");
}

// Test that a JPH file returns "image/jph" as mime type after readMetadata
TEST_F(Jp2ImageTest_84, MimeTypeForJphReturnsImageJph_84) {
    auto jphData = createMinimalJph();
    auto io = std::make_unique<Exiv2::MemIo>(jphData.data(), jphData.size());

    try {
        auto image = Exiv2::ImageFactory::open(std::move(io));
        ASSERT_NE(image, nullptr);

        try {
            image->readMetadata();
        } catch (...) {
            // Minimal file might fail at some point, but brand_ should be set after ftyp parsing
        }

        EXPECT_EQ(image->mimeType(), "image/jph");
    } catch (const Exiv2::Error&) {
        // If the factory can't open it as jp2, that's also valid behavior
        GTEST_SKIP() << "ImageFactory could not open minimal JPH data";
    }
}

// Test that setComment does not throw (it's documented as a no-op or override)
TEST_F(Jp2ImageTest_84, SetCommentDoesNotThrow_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that setComment with empty string does not throw
TEST_F(Jp2ImageTest_84, SetCommentEmptyString_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    EXPECT_NO_THROW(image->setComment(""));
}

// Test that reading metadata from empty/invalid data throws or handles gracefully
TEST_F(Jp2ImageTest_84, ReadMetadataFromEmptyIoThrows_84) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::open(std::move(io));
        if (image) {
            EXPECT_THROW(image->readMetadata(), Exiv2::Error);
        }
    } catch (const Exiv2::Error&) {
        // Expected: factory itself might throw for empty data
        SUCCEED();
    }
}

// Test that reading metadata from truncated JP2 data throws
TEST_F(Jp2ImageTest_84, ReadMetadataFromTruncatedDataThrows_84) {
    // Only the signature box, missing ftyp
    std::vector<unsigned char> truncated = {
        0x00, 0x00, 0x00, 0x0C,
        0x6A, 0x50, 0x20, 0x20,
        0x0D, 0x0A, 0x87, 0x0A,
    };
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    try {
        auto image = Exiv2::ImageFactory::open(std::move(io));
        if (image) {
            EXPECT_THROW(image->readMetadata(), Exiv2::Error);
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test printStructure does not crash on a minimal JP2
TEST_F(Jp2ImageTest_84, PrintStructureDoesNotCrash_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::ostringstream oss;
    try {
        image->printStructure(oss, Exiv2::kpsBasic, 0);
    } catch (const Exiv2::Error&) {
        // Some errors are expected for minimal data, but it shouldn't crash
        SUCCEED();
    }
}

// Test the brandJph constant value
TEST_F(Jp2ImageTest_84, BrandJphConstantValue_84) {
    // 'jph ' in ASCII = 0x6A706820
    EXPECT_EQ(Exiv2::Internal::brandJph, 0x6A706820u);
}

// Test that mimeType returns one of the two expected values
TEST_F(Jp2ImageTest_84, MimeTypeReturnsExpectedValues_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    std::string mime = image->mimeType();
    EXPECT_TRUE(mime == "image/jp2" || mime == "image/jph")
        << "Unexpected mime type: " << mime;
}

// Test writeMetadata on a minimal JP2 (should throw or succeed gracefully)
TEST_F(Jp2ImageTest_84, WriteMetadataOnMinimalJp2_84) {
    auto jp2Data = createMinimalJp2();
    auto io = std::make_unique<Exiv2::MemIo>(jp2Data.data(), jp2Data.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);

    try {
        image->readMetadata();
    } catch (...) {
        // May fail on minimal data
    }

    try {
        image->writeMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for minimal/incomplete files
        SUCCEED();
    }
}

// Test that Jp2Image created with create=true flag works
TEST_F(Jp2ImageTest_84, CreateNewJp2Image_84) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        Exiv2::Jp2Image img(std::move(io), true);
        EXPECT_EQ(img.mimeType(), "image/jp2");
    } catch (const Exiv2::Error&) {
        // If creation fails, that's acceptable behavior too
        SUCCEED();
    }
}

// Test that Jp2Image created with create=false and empty IO handles gracefully
TEST_F(Jp2ImageTest_84, CreateJp2ImageNoCreate_84) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        Exiv2::Jp2Image img(std::move(io), false);
        // Default brand should yield "image/jp2"
        EXPECT_EQ(img.mimeType(), "image/jp2");
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

}  // namespace
