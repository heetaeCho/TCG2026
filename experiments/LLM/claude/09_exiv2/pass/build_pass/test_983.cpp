#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/mrwimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <cstring>
#include <memory>
#include <sstream>

namespace {

// MRW file magic bytes: 0x00 0x4D 0x52 0x4D ("\0MRM")
const unsigned char kMrwHeader[] = {
    0x00, 0x4D, 0x52, 0x4D,  // MRM magic
    0x00, 0x00, 0x00, 0x00,  // offset to MRW data (placeholder)
};

class MrwImageTest_983 : public ::testing::Test {
protected:
    // Create a BasicIo from a memory buffer
    static Exiv2::BasicIo::UniquePtr createMemIo(const unsigned char* data, size_t size) {
        return std::make_unique<Exiv2::MemIo>(data, size);
    }

    static Exiv2::BasicIo::UniquePtr createEmptyMemIo() {
        return std::make_unique<Exiv2::MemIo>();
    }
};

// Test: newMrwInstance with empty MemIo and create=false should return nullptr (not a valid MRW)
TEST_F(MrwImageTest_983, NewInstanceEmptyIoNoCreate_983) {
    auto io = createEmptyMemIo();
    auto image = Exiv2::newMrwInstance(std::move(io), false);
    // An empty IO with create=false likely fails good() check
    // The result depends on whether MrwImage constructor considers it good
    // We just verify it doesn't crash and returns something (possibly nullptr)
    // Based on the code: if (!image->good()) return nullptr;
    EXPECT_EQ(image, nullptr);
}

// Test: newMrwInstance with create=true on empty MemIo
TEST_F(MrwImageTest_983, NewInstanceEmptyIoWithCreate_983) {
    auto io = createEmptyMemIo();
    auto image = Exiv2::newMrwInstance(std::move(io), true);
    // When create=true, the image may or may not be valid depending on implementation
    // We just verify no crash; result could be nullptr or valid
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: newMrwInstance with valid MRW header data
TEST_F(MrwImageTest_983, NewInstanceWithMrwHeader_983) {
    auto io = createMemIo(kMrwHeader, sizeof(kMrwHeader));
    auto image = Exiv2::newMrwInstance(std::move(io), false);
    // A minimal MRW header may or may not pass the good() check
    // Just verify no crash
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: newMrwInstance with garbage data returns nullptr
TEST_F(MrwImageTest_983, NewInstanceWithGarbageData_983) {
    const unsigned char garbage[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8};
    auto io = createMemIo(garbage, sizeof(garbage));
    auto image = Exiv2::newMrwInstance(std::move(io), false);
    // Garbage data should not be recognized as valid MRW
    EXPECT_EQ(image, nullptr);
}

// Test: MrwImage constructed directly with empty IO and create=false
TEST_F(MrwImageTest_983, DirectConstructEmptyNoCreate_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), false);
    EXPECT_NE(image, nullptr);
    // good() may be false for empty IO with no create
    // Just verify it doesn't crash
    bool g = image->good();
    (void)g;
}

// Test: MrwImage mimeType returns expected value
TEST_F(MrwImageTest_983, MimeType_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        std::string mime = image->mimeType();
        EXPECT_EQ(mime, "image/x-minolta-mrw");
    }
}

// Test: MrwImage readMetadata on empty IO throws
TEST_F(MrwImageTest_983, ReadMetadataEmptyIoThrows_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), false);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test: MrwImage readMetadata on garbage data throws
TEST_F(MrwImageTest_983, ReadMetadataGarbageThrows_983) {
    const unsigned char garbage[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto io = createMemIo(garbage, sizeof(garbage));
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), false);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test: MrwImage writeMetadata throws (MRW is read-only typically)
TEST_F(MrwImageTest_983, WriteMetadataThrows_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
    }
}

// Test: MrwImage setComment throws (unsupported operation for MRW)
TEST_F(MrwImageTest_983, SetCommentThrows_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
    }
}

// Test: MrwImage exifData returns reference
TEST_F(MrwImageTest_983, ExifDataAccess_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::ExifData& exif = image->exifData();
        EXPECT_TRUE(exif.empty());
    }
}

// Test: MrwImage iptcData returns reference
TEST_F(MrwImageTest_983, IptcDataAccess_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::IptcData& iptc = image->iptcData();
        EXPECT_TRUE(iptc.empty());
    }
}

// Test: MrwImage xmpData returns reference
TEST_F(MrwImageTest_983, XmpDataAccess_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::XmpData& xmp = image->xmpData();
        EXPECT_TRUE(xmp.empty());
    }
}

// Test: MrwImage pixelWidth and pixelHeight default to 0
TEST_F(MrwImageTest_983, DefaultPixelDimensions_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_EQ(image->pixelWidth(), 0u);
        EXPECT_EQ(image->pixelHeight(), 0u);
    }
}

// Test: newMrwInstance with nullptr-like IO (single byte)
TEST_F(MrwImageTest_983, NewInstanceSingleByte_983) {
    const unsigned char single = 0x00;
    auto io = createMemIo(&single, 1);
    auto image = Exiv2::newMrwInstance(std::move(io), false);
    // Likely not valid MRW
    EXPECT_EQ(image, nullptr);
}

// Test: MrwImage comment returns empty string by default
TEST_F(MrwImageTest_983, DefaultComment_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_TRUE(image->comment().empty());
    }
}

// Test: MrwImage clearMetadata does not throw
TEST_F(MrwImageTest_983, ClearMetadata_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_NO_THROW(image->clearMetadata());
    }
}

// Test: MrwImage clearExifData does not throw
TEST_F(MrwImageTest_983, ClearExifData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_NO_THROW(image->clearExifData());
    }
}

// Test: MrwImage clearIptcData does not throw
TEST_F(MrwImageTest_983, ClearIptcData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_NO_THROW(image->clearIptcData());
    }
}

// Test: MrwImage clearXmpData does not throw
TEST_F(MrwImageTest_983, ClearXmpData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        EXPECT_NO_THROW(image->clearXmpData());
    }
}

// Test: newMrwInstance with partial MRW magic (only 2 bytes)
TEST_F(MrwImageTest_983, NewInstancePartialMagic_983) {
    const unsigned char partial[] = {0x00, 0x4D};
    auto io = createMemIo(partial, sizeof(partial));
    auto image = Exiv2::newMrwInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: MrwImage io() returns a reference
TEST_F(MrwImageTest_983, IoAccess_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::BasicIo& ioRef = image->io();
        // Just verify we can access it without crash
        EXPECT_GE(ioRef.size(), 0u);
    }
}

// Test: MrwImage setExifData and verify
TEST_F(MrwImageTest_983, SetExifData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::ExifData exifData;
        EXPECT_NO_THROW(image->setExifData(exifData));
    }
}

// Test: MrwImage setIptcData and verify
TEST_F(MrwImageTest_983, SetIptcData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::IptcData iptcData;
        EXPECT_NO_THROW(image->setIptcData(iptcData));
    }
}

// Test: MrwImage setXmpData and verify
TEST_F(MrwImageTest_983, SetXmpData_983) {
    auto io = createEmptyMemIo();
    auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), true);
    if (image) {
        Exiv2::XmpData xmpData;
        EXPECT_NO_THROW(image->setXmpData(xmpData));
    }
}

}  // namespace
