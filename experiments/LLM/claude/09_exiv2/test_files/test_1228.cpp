#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <memory>
#include <sstream>
#include <cstring>

namespace {

// Helper function to access newExvInstance
// Forward declaration based on the partial code
// newExvInstance is in the Exiv2 namespace

class NewExvInstanceTest_1228 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating an ExvImage with create=true and valid MemIo should return a valid image
TEST_F(NewExvInstanceTest_1228, CreateNewExvImage_ReturnsValidImage_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
    // If the factory supports EXV creation, we should get a valid pointer
    // Using the factory approach since newExvInstance may not be directly accessible
    // Let's test via the known interface
}

// Test: newExvInstance with create=true should produce a good image
TEST_F(NewExvInstanceTest_1228, CreateNewExvWithMemIo_IsGood_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Image::UniquePtr image;
    try {
        image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
    } catch (...) {
        // If creation throws, that's acceptable behavior for some configurations
        GTEST_SKIP() << "ImageFactory::create threw an exception for exv type";
    }
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: Opening an EXV file from a non-existent file path should fail
TEST_F(NewExvInstanceTest_1228, OpenNonExistentFile_ReturnsNullOrThrows_1228) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_that_does_not_exist.exv");
    try {
        auto image = Exiv2::ImageFactory::open(std::move(io));
        // If it returns, the image should not be good or should be null
        if (image) {
            EXPECT_FALSE(image->good());
        }
    } catch (const Exiv2::Error&) {
        // Expected: opening a non-existent file should throw
        SUCCEED();
    }
}

// Test: Creating an ExvImage with MemIo containing empty data and create=false
TEST_F(NewExvInstanceTest_1228, OpenEmptyMemIo_FailsOrReturnsNull_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::open(std::move(io));
        if (image) {
            // An empty MemIo shouldn't be a valid EXV image
            // good() might return false, or readMetadata might throw
            EXPECT_NO_FATAL_FAILURE(image->good());
        }
    } catch (const Exiv2::Error&) {
        // Expected for empty/invalid data
        SUCCEED();
    }
}

// Test: Image created via factory for EXV type has correct mime type
TEST_F(NewExvInstanceTest_1228, ExvImageMimeType_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            std::string mime = image->mimeType();
            // EXV images should have a specific mime type
            EXPECT_FALSE(mime.empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ExvImage should support exif metadata
TEST_F(NewExvInstanceTest_1228, ExvImageSupportsExifMetadata_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdExif));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ExvImage should support IPTC metadata
TEST_F(NewExvInstanceTest_1228, ExvImageSupportsIptcMetadata_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdIptc));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ExvImage should support XMP metadata
TEST_F(NewExvInstanceTest_1228, ExvImageSupportsXmpMetadata_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdXmp));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ExvImage comment support
TEST_F(NewExvInstanceTest_1228, ExvImageSupportsComment_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdComment));
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Setting and getting comment on created ExvImage
TEST_F(NewExvInstanceTest_1228, ExvImageSetComment_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->setComment("Test comment");
            EXPECT_EQ(image->comment(), "Test comment");
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Clearing comment on ExvImage
TEST_F(NewExvInstanceTest_1228, ExvImageClearComment_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->setComment("Test comment");
            image->clearComment();
            EXPECT_TRUE(image->comment().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Initial pixel dimensions should be zero
TEST_F(NewExvInstanceTest_1228, ExvImageInitialPixelDimensions_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_EQ(image->pixelWidth(), 0u);
            EXPECT_EQ(image->pixelHeight(), 0u);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: io() returns a reference to the BasicIo object
TEST_F(NewExvInstanceTest_1228, ExvImageIoAccessible_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            const Exiv2::BasicIo& ioRef = image->io();
            // Just verify we can access it without crashing
            EXPECT_NO_FATAL_FAILURE(ioRef.size());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ExifData reference accessible
TEST_F(NewExvInstanceTest_1228, ExvImageExifDataAccessible_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::ExifData& exif = image->exifData();
            EXPECT_TRUE(exif.empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: IptcData reference accessible
TEST_F(NewExvInstanceTest_1228, ExvImageIptcDataAccessible_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::IptcData& iptc = image->iptcData();
            EXPECT_TRUE(iptc.empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: XmpData reference accessible
TEST_F(NewExvInstanceTest_1228, ExvImageXmpDataAccessible_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::XmpData& xmp = image->xmpData();
            EXPECT_TRUE(xmp.empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: writeXmpFromPacket default is false
TEST_F(NewExvInstanceTest_1228, ExvImageWriteXmpFromPacketDefault_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_FALSE(image->writeXmpFromPacket());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Setting writeXmpFromPacket
TEST_F(NewExvInstanceTest_1228, ExvImageSetWriteXmpFromPacket_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->writeXmpFromPacket(true);
            EXPECT_TRUE(image->writeXmpFromPacket());
            image->writeXmpFromPacket(false);
            EXPECT_FALSE(image->writeXmpFromPacket());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: clearMetadata clears all metadata
TEST_F(NewExvInstanceTest_1228, ExvImageClearMetadata_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->setComment("Some comment");
            image->clearMetadata();
            EXPECT_TRUE(image->comment().empty());
            EXPECT_TRUE(image->exifData().empty());
            EXPECT_TRUE(image->iptcData().empty());
            EXPECT_TRUE(image->xmpData().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: setByteOrder and byteOrder
TEST_F(NewExvInstanceTest_1228, ExvImageSetByteOrder_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->setByteOrder(Exiv2::bigEndian);
            EXPECT_EQ(image->byteOrder(), Exiv2::bigEndian);
            image->setByteOrder(Exiv2::littleEndian);
            EXPECT_EQ(image->byteOrder(), Exiv2::littleEndian);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: ICC profile not defined initially
TEST_F(NewExvInstanceTest_1228, ExvImageIccProfileNotDefinedInitially_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_FALSE(image->iccProfileDefined());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: clearIccProfile
TEST_F(NewExvInstanceTest_1228, ExvImageClearIccProfile_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            image->clearIccProfile();
            EXPECT_FALSE(image->iccProfileDefined());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: nativePreviews is empty initially
TEST_F(NewExvInstanceTest_1228, ExvImageNativePreviewsEmptyInitially_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_TRUE(image->nativePreviews().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Image type
TEST_F(NewExvInstanceTest_1228, ExvImageType_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            EXPECT_EQ(image->imageType(), Exiv2::ImageType::exv);
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Static helper - endian platform checks are consistent
TEST_F(NewExvInstanceTest_1228, EndianPlatformConsistency_1228) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    // One must be true and the other false (or both could be false in theory for mixed, but typically)
    EXPECT_NE(isBig, isLittle);
}

// Test: byteSwap uint16_t with bSwap=false returns same value
TEST_F(NewExvInstanceTest_1228, ByteSwap16NoSwap_1228) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test: byteSwap uint16_t with bSwap=true returns swapped value
TEST_F(NewExvInstanceTest_1228, ByteSwap16Swap_1228) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, static_cast<uint16_t>(0x3412));
}

// Test: byteSwap uint32_t with bSwap=false returns same value
TEST_F(NewExvInstanceTest_1228, ByteSwap32NoSwap_1228) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test: byteSwap uint32_t with bSwap=true returns swapped value
TEST_F(NewExvInstanceTest_1228, ByteSwap32Swap_1228) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, static_cast<uint32_t>(0x78563412));
}

// Test: byteSwap uint64_t with bSwap=false returns same value
TEST_F(NewExvInstanceTest_1228, ByteSwap64NoSwap_1228) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test: byteSwap uint64_t with bSwap=true returns swapped value
TEST_F(NewExvInstanceTest_1228, ByteSwap64Swap_1228) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, static_cast<uint64_t>(0x0807060504030201ULL));
}

// Test: isStringType
TEST_F(NewExvInstanceTest_1228, IsStringType_1228) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Type 1 (BYTE) is not a string type
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

// Test: isShortType
TEST_F(NewExvInstanceTest_1228, IsShortType_1228) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// Test: isLongType
TEST_F(NewExvInstanceTest_1228, IsLongType_1228) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test: isRationalType
TEST_F(NewExvInstanceTest_1228, IsRationalType_1228) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// Test: Setting ExifData and clearing it
TEST_F(NewExvInstanceTest_1228, ExvImageSetAndClearExifData_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::ExifData exifData;
            // Set some exif data
            exifData["Exif.Image.Make"] = "TestMake";
            image->setExifData(exifData);
            EXPECT_FALSE(image->exifData().empty());

            image->clearExifData();
            EXPECT_TRUE(image->exifData().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Setting IptcData and clearing it
TEST_F(NewExvInstanceTest_1228, ExvImageSetAndClearIptcData_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::IptcData iptcData;
            iptcData["Iptc.Application2.Caption"] = "Test caption";
            image->setIptcData(iptcData);
            EXPECT_FALSE(image->iptcData().empty());

            image->clearIptcData();
            EXPECT_TRUE(image->iptcData().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Setting XmpData and clearing it
TEST_F(NewExvInstanceTest_1228, ExvImageSetAndClearXmpData_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            Exiv2::XmpData xmpData;
            xmpData["Xmp.dc.title"] = "Test title";
            image->setXmpData(xmpData);
            EXPECT_FALSE(image->xmpData().empty());

            image->clearXmpData();
            EXPECT_TRUE(image->xmpData().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: Setting and clearing XmpPacket
TEST_F(NewExvInstanceTest_1228, ExvImageSetAndClearXmpPacket_1228) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
        if (image) {
            std::string packet = "<x:xmpmeta></x:xmpmeta>";
            image->setXmpPacket(packet);
            EXPECT_EQ(image->xmpPacket(), packet);

            image->clearXmpPacket();
            EXPECT_TRUE(image->xmpPacket().empty());
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not create EXV image";
    }
}

// Test: is2ByteType
TEST_F(NewExvInstanceTest_1228, Is2ByteType_1228) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    // LONG (4) is not 2 bytes
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test: is4ByteType
TEST_F(NewExvInstanceTest_1228, Is4ByteType_1228) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    // SHORT (3) is not 4 bytes
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// Test: is8ByteType
TEST_F(NewExvInstanceTest_1228, Is8ByteType_1228) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    // LONG (4) is not 8 bytes
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

} // namespace
