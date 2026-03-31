#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/rw2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <memory>

// Helper to create a Rw2Image with a MemIo (empty or with data)
static std::unique_ptr<Exiv2::Rw2Image> createRw2ImageWithEmptyIo() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
}

class Rw2ImageTest_1575 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::Rw2Image> image_;

    void SetUp() override {
        image_ = createRw2ImageWithEmptyIo();
    }
};

// Test that mimeType returns the correct MIME type for RW2
TEST_F(Rw2ImageTest_1575, MimeType_ReturnsCorrectType_1575) {
    std::string mime = image_->mimeType();
    EXPECT_EQ(mime, "image/x-panasonic-rw2");
}

// Test that mimeType is consistent across multiple calls
TEST_F(Rw2ImageTest_1575, MimeType_IsConsistent_1575) {
    std::string mime1 = image_->mimeType();
    std::string mime2 = image_->mimeType();
    EXPECT_EQ(mime1, mime2);
}

// Test that setExifData does not throw (RW2 is read-only for exif setting)
TEST_F(Rw2ImageTest_1575, SetExifData_DoesNotCrash_1575) {
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image_->setExifData(exifData));
}

// Test that setIptcData does not throw (RW2 is read-only for iptc setting)
TEST_F(Rw2ImageTest_1575, SetIptcData_DoesNotCrash_1575) {
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image_->setIptcData(iptcData));
}

// Test that setComment does not throw
TEST_F(Rw2ImageTest_1575, SetComment_DoesNotCrash_1575) {
    EXPECT_NO_THROW(image_->setComment("test comment"));
}

// Test that setComment with empty string does not throw
TEST_F(Rw2ImageTest_1575, SetComment_EmptyString_DoesNotCrash_1575) {
    EXPECT_NO_THROW(image_->setComment(""));
}

// Test that writeMetadata throws since RW2 is typically read-only
TEST_F(Rw2ImageTest_1575, WriteMetadata_ThrowsOnReadOnly_1575) {
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
}

// Test that readMetadata on empty IO throws or handles error
TEST_F(Rw2ImageTest_1575, ReadMetadata_OnEmptyIo_Throws_1575) {
    EXPECT_THROW(image_->readMetadata(), Exiv2::Error);
}

// Test that pixelWidth returns 0 for an image with no metadata loaded
TEST_F(Rw2ImageTest_1575, PixelWidth_DefaultIsZero_1575) {
    uint32_t width = image_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test that pixelHeight returns 0 for an image with no metadata loaded
TEST_F(Rw2ImageTest_1575, PixelHeight_DefaultIsZero_1575) {
    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test printStructure with kPrNone option on empty IO does not crash
TEST_F(Rw2ImageTest_1575, PrintStructure_NoneOption_DoesNotCrash_1575) {
    std::ostringstream oss;
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test creating Rw2Image with valid (but empty) MemIo
TEST(Rw2ImageCreationTest_1575, CreateWithMemIo_1575) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        Exiv2::Rw2Image img(std::move(io));
    });
}

// Test that after setExifData, exifData is still accessible (even if empty for RW2)
TEST_F(Rw2ImageTest_1575, ExifDataAccessible_AfterSet_1575) {
    Exiv2::ExifData exifData;
    image_->setExifData(exifData);
    // ExifData should be accessible (may be empty since RW2 ignores setExifData)
    const Exiv2::ExifData& retrieved = image_->exifData();
    EXPECT_TRUE(retrieved.empty());
}

// Test that after setIptcData, iptcData is still accessible
TEST_F(Rw2ImageTest_1575, IptcDataAccessible_AfterSet_1575) {
    Exiv2::IptcData iptcData;
    image_->setIptcData(iptcData);
    const Exiv2::IptcData& retrieved = image_->iptcData();
    EXPECT_TRUE(retrieved.empty());
}

// Test that comment is empty by default
TEST_F(Rw2ImageTest_1575, Comment_DefaultEmpty_1575) {
    std::string comment = image_->comment();
    EXPECT_TRUE(comment.empty());
}

// Test mimeType is not empty
TEST_F(Rw2ImageTest_1575, MimeType_NotEmpty_1575) {
    EXPECT_FALSE(image_->mimeType().empty());
}

// Test mimeType starts with "image/"
TEST_F(Rw2ImageTest_1575, MimeType_StartsWithImage_1575) {
    std::string mime = image_->mimeType();
    EXPECT_EQ(mime.substr(0, 6), "image/");
}
