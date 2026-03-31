#include <gtest/gtest.h>
#include <exiv2/mrwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <fstream>

using namespace Exiv2;

class MrwImageTest_978 : public ::testing::Test {
protected:
    std::unique_ptr<MrwImage> createMrwImageFromMemory(const std::vector<uint8_t>& data, bool create = false) {
        auto memIo = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<MrwImage>(std::move(memIo), create);
    }

    std::unique_ptr<MrwImage> createEmptyMrwImage(bool create = false) {
        auto memIo = std::make_unique<MemIo>();
        return std::make_unique<MrwImage>(std::move(memIo), create);
    }
};

TEST_F(MrwImageTest_978, MimeType_ReturnsCorrectMimeType_978) {
    auto image = createEmptyMrwImage();
    EXPECT_EQ("image/x-minolta-mrw", image->mimeType());
}

TEST_F(MrwImageTest_978, Constructor_WithEmptyIo_978) {
    auto memIo = std::make_unique<MemIo>();
    EXPECT_NO_THROW(MrwImage(std::move(memIo), false));
}

TEST_F(MrwImageTest_978, Constructor_WithCreateFlag_978) {
    auto memIo = std::make_unique<MemIo>();
    EXPECT_NO_THROW(MrwImage(std::move(memIo), true));
}

TEST_F(MrwImageTest_978, SetExifData_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

TEST_F(MrwImageTest_978, SetIptcData_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

TEST_F(MrwImageTest_978, SetComment_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    EXPECT_NO_THROW(image->setComment("test comment"));
}

TEST_F(MrwImageTest_978, SetComment_EmptyString_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    EXPECT_NO_THROW(image->setComment(""));
}

TEST_F(MrwImageTest_978, ReadMetadata_EmptyIo_ThrowsError_978) {
    auto image = createEmptyMrwImage();
    EXPECT_THROW(image->readMetadata(), Error);
}

TEST_F(MrwImageTest_978, ReadMetadata_InvalidData_ThrowsError_978) {
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto image = createMrwImageFromMemory(invalidData);
    EXPECT_THROW(image->readMetadata(), Error);
}

TEST_F(MrwImageTest_978, WriteMetadata_ThrowsError_978) {
    auto image = createEmptyMrwImage();
    EXPECT_THROW(image->writeMetadata(), Error);
}

TEST_F(MrwImageTest_978, PixelWidth_DefaultIsZero_978) {
    auto image = createEmptyMrwImage();
    EXPECT_EQ(0u, image->pixelWidth());
}

TEST_F(MrwImageTest_978, PixelHeight_DefaultIsZero_978) {
    auto image = createEmptyMrwImage();
    EXPECT_EQ(0u, image->pixelHeight());
}

TEST_F(MrwImageTest_978, MimeType_ConsistentAcrossMultipleCalls_978) {
    auto image = createEmptyMrwImage();
    std::string mime1 = image->mimeType();
    std::string mime2 = image->mimeType();
    EXPECT_EQ(mime1, mime2);
    EXPECT_EQ("image/x-minolta-mrw", mime1);
}

TEST_F(MrwImageTest_978, ReadMetadata_RandomGarbage_ThrowsError_978) {
    std::vector<uint8_t> garbage(1024, 0xFF);
    auto image = createMrwImageFromMemory(garbage);
    EXPECT_THROW(image->readMetadata(), Error);
}

TEST_F(MrwImageTest_978, ReadMetadata_MrwMagicButTruncated_ThrowsError_978) {
    // MRW magic bytes are 0x00 0x4D 0x52 0x4D ("\0MRM")
    std::vector<uint8_t> truncated = {0x00, 0x4D, 0x52, 0x4D, 0x00, 0x00};
    auto image = createMrwImageFromMemory(truncated);
    EXPECT_THROW(image->readMetadata(), Error);
}

TEST_F(MrwImageTest_978, SetExifData_WithPopulatedData_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Minolta";
    EXPECT_NO_THROW(image->setExifData(exifData));
}

TEST_F(MrwImageTest_978, SetIptcData_WithPopulatedData_DoesNotThrow_978) {
    auto image = createEmptyMrwImage();
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}
