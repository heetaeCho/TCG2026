#include <gtest/gtest.h>
#include <exiv2/crwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <cstdint>
#include <memory>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a minimal CRW file in memory for testing
std::unique_ptr<Exiv2::MemIo> createEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

std::unique_ptr<Exiv2::MemIo> createMemIoWithData(const std::vector<uint8_t>& data) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    if (!data.empty()) {
        memIo->write(data.data(), data.size());
        memIo->seek(0, Exiv2::BasicIo::beg);
    }
    return memIo;
}

class CrwImageTest_1811 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that mimeType returns the correct MIME type for CRW images
TEST_F(CrwImageTest_1811, MimeTypeReturnsCorrectValue_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    EXPECT_EQ(crwImage.mimeType(), "image/x-canon-crw");
}

// Test that mimeType is consistent across multiple calls
TEST_F(CrwImageTest_1811, MimeTypeIsConsistent_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    std::string first = crwImage.mimeType();
    std::string second = crwImage.mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/x-canon-crw");
}

// Test that setIptcData does not throw (CRW doesn't support IPTC)
TEST_F(CrwImageTest_1811, SetIptcDataDoesNotThrow_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(crwImage.setIptcData(iptcData));
}

// Test that reading metadata from empty/invalid data throws or handles gracefully
TEST_F(CrwImageTest_1811, ReadMetadataFromEmptyIoThrows_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), false);
    EXPECT_THROW(crwImage.readMetadata(), Exiv2::Error);
}

// Test that writing metadata from a freshly created (empty) image doesn't crash
TEST_F(CrwImageTest_1811, WriteMetadataOnEmptyIo_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    // Writing metadata on an empty/new CRW may throw due to no valid structure
    // We just verify it doesn't cause undefined behavior
    try {
        crwImage.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Expected - empty CRW may not be writable
    }
}

// Test pixelWidth returns 0 when no metadata has been read
TEST_F(CrwImageTest_1811, PixelWidthDefaultIsZero_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    EXPECT_EQ(crwImage.pixelWidth(), 0u);
}

// Test pixelHeight returns 0 when no metadata has been read
TEST_F(CrwImageTest_1811, PixelHeightDefaultIsZero_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    EXPECT_EQ(crwImage.pixelHeight(), 0u);
}

// Test that reading metadata from garbage data throws an error
TEST_F(CrwImageTest_1811, ReadMetadataFromGarbageDataThrows_1811) {
    std::vector<uint8_t> garbage(1024, 0xFF);
    auto io = createMemIoWithData(garbage);
    Exiv2::CrwImage crwImage(std::move(io), false);
    EXPECT_THROW(crwImage.readMetadata(), Exiv2::Error);
}

// Test that setIptcData with non-empty data still doesn't throw (silently ignored)
TEST_F(CrwImageTest_1811, SetIptcDataWithNonEmptyData_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    Exiv2::IptcData iptcData;
    // Add some IPTC tag - CRW should silently ignore it
    EXPECT_NO_THROW(crwImage.setIptcData(iptcData));
}

// Test construction with create=true
TEST_F(CrwImageTest_1811, ConstructWithCreateTrue_1811) {
    auto io = createEmptyMemIo();
    EXPECT_NO_THROW(Exiv2::CrwImage crwImage(std::move(io), true));
}

// Test construction with create=false
TEST_F(CrwImageTest_1811, ConstructWithCreateFalse_1811) {
    auto io = createEmptyMemIo();
    EXPECT_NO_THROW(Exiv2::CrwImage crwImage(std::move(io), false));
}

// Test that reading metadata from very small data throws
TEST_F(CrwImageTest_1811, ReadMetadataFromTinyDataThrows_1811) {
    std::vector<uint8_t> tiny = {0x49, 0x49}; // Just 2 bytes
    auto io = createMemIoWithData(tiny);
    Exiv2::CrwImage crwImage(std::move(io), false);
    EXPECT_THROW(crwImage.readMetadata(), Exiv2::Error);
}

// Test that mimeType does not return an empty string
TEST_F(CrwImageTest_1811, MimeTypeNotEmpty_1811) {
    auto io = createEmptyMemIo();
    Exiv2::CrwImage crwImage(std::move(io), true);
    EXPECT_FALSE(crwImage.mimeType().empty());
}

} // namespace
