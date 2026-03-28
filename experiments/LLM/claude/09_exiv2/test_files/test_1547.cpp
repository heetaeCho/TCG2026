#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <sstream>

// Include necessary headers from exiv2
#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

namespace {

class OrfImageTest_1547 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::OrfImage> createOrfImageFromFile(const std::string& path, bool create = false) {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        return std::make_unique<Exiv2::OrfImage>(std::move(io), create);
    }

    std::unique_ptr<Exiv2::OrfImage> createOrfImageFromMemory(const std::string& data = "", bool create = false) {
        auto io = std::make_unique<Exiv2::MemIo>(
            reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
        return std::make_unique<Exiv2::OrfImage>(std::move(io), create);
    }
};

// Test that mimeType returns the correct MIME type for ORF images
TEST_F(OrfImageTest_1547, MimeTypeReturnsCorrectValue_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/x-olympus-orf");
}

// Test that mimeType is consistent across multiple calls
TEST_F(OrfImageTest_1547, MimeTypeConsistentAcrossCalls_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    std::string first = image->mimeType();
    std::string second = image->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/x-olympus-orf");
}

// Test creating OrfImage with create=true and empty data
TEST_F(OrfImageTest_1547, CreateWithEmptyMemoryIo_1547) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        auto image = std::make_unique<Exiv2::OrfImage>(std::move(io), true);
        ASSERT_NE(image, nullptr);
    });
}

// Test creating OrfImage with create=false and empty data
TEST_F(OrfImageTest_1547, CreateWithoutCreateFlag_1547) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        auto image = std::make_unique<Exiv2::OrfImage>(std::move(io), false);
        ASSERT_NE(image, nullptr);
    });
}

// Test setComment throws or handles since ORF may not support comments
TEST_F(OrfImageTest_1547, SetCommentBehavior_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    // ORF images typically don't support comments; expect an exception
    EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
}

// Test readMetadata on empty/invalid data throws
TEST_F(OrfImageTest_1547, ReadMetadataOnEmptyDataThrows_1547) {
    auto image = createOrfImageFromMemory("");
    ASSERT_NE(image, nullptr);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test writeMetadata on empty/invalid data throws
TEST_F(OrfImageTest_1547, WriteMetadataOnEmptyDataThrows_1547) {
    auto image = createOrfImageFromMemory("");
    ASSERT_NE(image, nullptr);
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test readMetadata with garbage data throws
TEST_F(OrfImageTest_1547, ReadMetadataWithGarbageDataThrows_1547) {
    std::string garbageData(1024, '\x00');
    auto image = createOrfImageFromMemory(garbageData);
    ASSERT_NE(image, nullptr);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test pixelWidth on an image without valid data
TEST_F(OrfImageTest_1547, PixelWidthDefaultValue_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    // Without reading metadata, pixel dimensions should be 0 or default
    uint32_t width = image->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test pixelHeight on an image without valid data
TEST_F(OrfImageTest_1547, PixelHeightDefaultValue_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    uint32_t height = image->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test printStructure with kpsNone on empty image
TEST_F(OrfImageTest_1547, PrintStructureNoneOnEmptyImage_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    std::ostringstream oss;
    // kpsNone should not throw
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test that multiple OrfImage instances have independent mimeTypes
TEST_F(OrfImageTest_1547, MultipleInstancesMimeType_1547) {
    auto image1 = createOrfImageFromMemory("", true);
    auto image2 = createOrfImageFromMemory("", true);
    ASSERT_NE(image1, nullptr);
    ASSERT_NE(image2, nullptr);
    EXPECT_EQ(image1->mimeType(), image2->mimeType());
    EXPECT_EQ(image1->mimeType(), "image/x-olympus-orf");
}

// Test readMetadata with random non-TIFF data
TEST_F(OrfImageTest_1547, ReadMetadataWithRandomDataThrows_1547) {
    std::string randomData = "This is definitely not an ORF file!";
    auto image = createOrfImageFromMemory(randomData);
    ASSERT_NE(image, nullptr);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test setComment with empty string
TEST_F(OrfImageTest_1547, SetCommentEmptyString_1547) {
    auto image = createOrfImageFromMemory("", true);
    ASSERT_NE(image, nullptr);
    EXPECT_THROW(image->setComment(""), Exiv2::Error);
}

} // namespace
