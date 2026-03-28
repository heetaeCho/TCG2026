#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/cr2image.hpp>
#include <exiv2/basicio.hpp>

#include <fstream>
#include <sstream>
#include <memory>

class Cr2ImageTest_1739 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::Cr2Image> createCr2ImageFromMemory(const std::string& data = "") {
        auto memIo = std::make_unique<Exiv2::MemIo>(
            reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
        return std::make_unique<Exiv2::Cr2Image>(std::move(memIo), false);
    }

    std::unique_ptr<Exiv2::Cr2Image> createCr2ImageWithCreate() {
        auto memIo = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::Cr2Image>(std::move(memIo), true);
    }
};

// Test that mimeType returns the correct MIME type for CR2 images
TEST_F(Cr2ImageTest_1739, MimeTypeReturnsCr2MimeType_1739) {
    auto image = createCr2ImageFromMemory();
    EXPECT_EQ(image->mimeType(), "image/x-canon-cr2");
}

// Test that mimeType is consistent across multiple calls
TEST_F(Cr2ImageTest_1739, MimeTypeIsConsistent_1739) {
    auto image = createCr2ImageFromMemory();
    std::string first = image->mimeType();
    std::string second = image->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/x-canon-cr2");
}

// Test that the Cr2Image can be constructed with create=false
TEST_F(Cr2ImageTest_1739, ConstructWithCreateFalse_1739) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::Cr2Image(std::move(memIo), false));
}

// Test that the Cr2Image can be constructed with create=true
TEST_F(Cr2ImageTest_1739, ConstructWithCreateTrue_1739) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::Cr2Image(std::move(memIo), true));
}

// Test that setComment throws since CR2 doesn't support comments
TEST_F(Cr2ImageTest_1739, SetCommentThrows_1739) {
    auto image = createCr2ImageFromMemory();
    EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
}

// Test that readMetadata on empty data throws an error
TEST_F(Cr2ImageTest_1739, ReadMetadataOnEmptyDataThrows_1739) {
    auto image = createCr2ImageFromMemory("");
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that writeMetadata on empty/invalid data throws an error
TEST_F(Cr2ImageTest_1739, WriteMetadataOnEmptyDataThrows_1739) {
    auto image = createCr2ImageFromMemory("");
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test pixelWidth returns 0 for an image with no metadata loaded
TEST_F(Cr2ImageTest_1739, PixelWidthDefaultIsZero_1739) {
    auto image = createCr2ImageFromMemory();
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for an image with no metadata loaded
TEST_F(Cr2ImageTest_1739, PixelHeightDefaultIsZero_1739) {
    auto image = createCr2ImageFromMemory();
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test readMetadata with invalid/garbage data
TEST_F(Cr2ImageTest_1739, ReadMetadataWithGarbageDataThrows_1739) {
    std::string garbage(1024, '\x00');
    auto image = createCr2ImageFromMemory(garbage);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata with random non-CR2 data
TEST_F(Cr2ImageTest_1739, ReadMetadataWithRandomDataThrows_1739) {
    std::string randomData = "This is not a CR2 file at all, just random text data.";
    auto image = createCr2ImageFromMemory(randomData);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test printStructure does not crash on empty data with kpsNone
TEST_F(Cr2ImageTest_1739, PrintStructureKpsNoneOnEmptyData_1739) {
    auto image = createCr2ImageFromMemory("");
    std::ostringstream oss;
    // kpsNone should not attempt to read structure
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test that mimeType doesn't change after attempted (failed) readMetadata
TEST_F(Cr2ImageTest_1739, MimeTypeUnchangedAfterFailedRead_1739) {
    auto image = createCr2ImageFromMemory("not valid cr2");
    EXPECT_EQ(image->mimeType(), "image/x-canon-cr2");
    try {
        image->readMetadata();
    } catch (...) {
        // Expected to fail
    }
    EXPECT_EQ(image->mimeType(), "image/x-canon-cr2");
}

// Test that setComment with empty string still throws
TEST_F(Cr2ImageTest_1739, SetEmptyCommentThrows_1739) {
    auto image = createCr2ImageFromMemory();
    EXPECT_THROW(image->setComment(""), Exiv2::Error);
}

// Test constructing with very small data
TEST_F(Cr2ImageTest_1739, ConstructWithSingleByteData_1739) {
    std::string singleByte(1, '\xFF');
    auto image = createCr2ImageFromMemory(singleByte);
    EXPECT_EQ(image->mimeType(), "image/x-canon-cr2");
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}
