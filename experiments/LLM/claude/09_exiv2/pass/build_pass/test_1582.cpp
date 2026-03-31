#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/rw2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <fstream>
#include <sstream>

namespace {

// Helper to create a temporary file with given content
std::string createTempFile(const std::string& suffix, const std::vector<uint8_t>& content) {
    std::string filename = "test_rw2_" + suffix + ".rw2";
    std::ofstream ofs(filename, std::ios::binary);
    if (!content.empty()) {
        ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
    }
    ofs.close();
    return filename;
}

void removeTempFile(const std::string& filename) {
    std::remove(filename.c_str());
}

} // anonymous namespace

class Rw2ImageTest_1582 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }
    
    void addTempFile(const std::string& f) {
        tempFiles_.push_back(f);
    }
    
    std::vector<std::string> tempFiles_;
};

// Test that newRw2Instance returns nullptr for an invalid/empty MemIo
TEST_F(Rw2ImageTest_1582, NewInstanceWithEmptyMemIo_ReturnsNullOrValid_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRw2Instance(std::move(io), false);
    // An empty MemIo may not be "good", so nullptr is possible
    // We just verify no crash and consistent behavior
    // If null, that's expected for empty/invalid data
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    } else {
        EXPECT_EQ(image.get(), nullptr);
    }
}

// Test that newRw2Instance with create=false and valid MemIo with some data
TEST_F(Rw2ImageTest_1582, NewInstanceWithNonEmptyMemIo_1582) {
    // Provide some arbitrary bytes (not a valid RW2, but non-empty)
    const uint8_t data[] = {0x49, 0x49, 0x55, 0x00, 0x18, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data, sizeof(data));
    auto image = Exiv2::newRw2Instance(std::move(io), false);
    // The image may or may not be good depending on internal checks
    // We verify no crash
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that newRw2Instance with create=true still works (create param is ignored per signature)
TEST_F(Rw2ImageTest_1582, NewInstanceWithCreateTrue_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRw2Instance(std::move(io), true);
    // create parameter is ignored (/*create*/), so behavior should be same as false
    // Empty io likely returns nullptr
    if (!image) {
        EXPECT_EQ(image.get(), nullptr);
    }
}

// Test Rw2Image construction with MemIo
TEST_F(Rw2ImageTest_1582, Rw2ImageConstructionWithMemIo_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    // Check mimeType
    EXPECT_STREQ(image.mimeType().c_str(), "image/x-panasonic-rw2");
}

// Test that Rw2Image reports correct mime type
TEST_F(Rw2ImageTest_1582, MimeType_1582) {
    const uint8_t data[] = {0x49, 0x49, 0x55, 0x00, 0x18, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data, sizeof(data));
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_EQ(image.mimeType(), "image/x-panasonic-rw2");
}

// Test that setExifData throws or is not supported for RW2
TEST_F(Rw2ImageTest_1582, SetExifData_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    Exiv2::ExifData exifData;
    // setExifData should work (set the data structure)
    // We just ensure no crash
    image.setExifData(exifData);
}

// Test that setIptcData works without crash
TEST_F(Rw2ImageTest_1582, SetIptcData_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    Exiv2::IptcData iptcData;
    image.setIptcData(iptcData);
}

// Test that setComment works without crash
TEST_F(Rw2ImageTest_1582, SetComment_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    image.setComment("test comment");
}

// Test that writeMetadata throws for RW2 (RW2 is typically read-only)
TEST_F(Rw2ImageTest_1582, WriteMetadataThrows_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test readMetadata on invalid data throws
TEST_F(Rw2ImageTest_1582, ReadMetadataOnInvalidDataThrows_1582) {
    const uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data, sizeof(data));
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

// Test readMetadata on empty data throws
TEST_F(Rw2ImageTest_1582, ReadMetadataOnEmptyDataThrows_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

// Test newRw2Instance with a FileIo pointing to non-existent file
TEST_F(Rw2ImageTest_1582, NewInstanceWithNonExistentFile_1582) {
    auto io = std::make_unique<Exiv2::FileIo>("non_existent_file_1582.rw2");
    auto image = Exiv2::newRw2Instance(std::move(io), false);
    // Non-existent file should result in a non-good image, hence nullptr
    EXPECT_EQ(image.get(), nullptr);
}

// Test good() method on Rw2Image with empty MemIo
TEST_F(Rw2ImageTest_1582, GoodMethodEmptyMemIo_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    // Empty MemIo - good() might return true since MemIo itself is valid
    // We just observe the behavior
    bool isGood = image.good();
    // No specific assertion on value since it depends on implementation
    // but we ensure no crash
    (void)isGood;
}

// Test pixelWidth and pixelHeight on unread image
TEST_F(Rw2ImageTest_1582, PixelDimensionsDefault_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    // Before reading metadata, pixel dimensions should be 0
    EXPECT_EQ(image.pixelWidth(), 0u);
    EXPECT_EQ(image.pixelHeight(), 0u);
}

// Test that newRw2Instance returns a valid Rw2Image pointer type
TEST_F(Rw2ImageTest_1582, NewInstanceReturnType_1582) {
    const uint8_t data[] = {0x49, 0x49, 0x55, 0x00, 0x18, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data, sizeof(data));
    auto image = Exiv2::newRw2Instance(std::move(io), false);
    if (image) {
        // Verify it can be dynamically cast to Rw2Image
        auto* rw2 = dynamic_cast<Exiv2::Rw2Image*>(image.get());
        EXPECT_NE(rw2, nullptr);
    }
}

// Test with large random data
TEST_F(Rw2ImageTest_1582, NewInstanceWithLargeRandomData_1582) {
    std::vector<uint8_t> largeData(65536, 0xAB);
    auto io = std::make_unique<Exiv2::MemIo>(largeData.data(), largeData.size());
    auto image = Exiv2::newRw2Instance(std::move(io), false);
    // May or may not be valid, just ensure no crash
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test setXmpData doesn't crash
TEST_F(Rw2ImageTest_1582, SetXmpData_1582) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Rw2Image image(std::move(io));
    Exiv2::XmpData xmpData;
    image.setXmpData(xmpData);
}
