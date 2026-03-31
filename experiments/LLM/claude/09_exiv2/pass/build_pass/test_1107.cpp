#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <vector>
#include <cstring>

namespace {

// A minimal valid JPEG file (smallest possible)
const unsigned char kMinimalJpeg[] = {
    0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
    0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
};

// A minimal valid PNG file header
const unsigned char kMinimalPng[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
    0xDE, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41,
    0x54, 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC,
    0x33, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E,
    0x44, 0xAE, 0x42, 0x60, 0x82
};

} // anonymous namespace

class ImageFactoryOpenFromMemoryTest_1107 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that opening a valid JPEG from memory returns a non-null image
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenValidJpegReturnsNonNull_1107) {
    auto image = Exiv2::ImageFactory::open(kMinimalJpeg, sizeof(kMinimalJpeg));
    ASSERT_NE(image, nullptr);
}

// Test that opening random/garbage data throws an exception with kerMemoryContainsUnknownImageType
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenGarbageDataThrowsUnknownImageType_1107) {
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_THROW(
        Exiv2::ImageFactory::open(garbage, sizeof(garbage)),
        Exiv2::Error
    );
}

// Test that opening with zero-size data throws an exception
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenZeroSizeDataThrows_1107) {
    const unsigned char dummy[] = {0x00};
    EXPECT_THROW(
        Exiv2::ImageFactory::open(dummy, 0),
        Exiv2::Error
    );
}

// Test that opening with nullptr and zero size throws
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenNullptrThrows_1107) {
    EXPECT_THROW(
        Exiv2::ImageFactory::open(nullptr, 0),
        Exiv2::Error
    );
}

// Test that the error code is kerMemoryContainsUnknownImageType for garbage data
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenGarbageDataErrorCode_1107) {
    const unsigned char garbage[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00};
    try {
        Exiv2::ImageFactory::open(garbage, sizeof(garbage));
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerMemoryContainsUnknownImageType);
    }
}

// Test that opening a single byte throws (too small to be any image)
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenSingleByteThrows_1107) {
    const unsigned char singleByte[] = {0xFF};
    EXPECT_THROW(
        Exiv2::ImageFactory::open(singleByte, sizeof(singleByte)),
        Exiv2::Error
    );
}

// Test that opening only JPEG SOI marker (incomplete JPEG) throws
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenIncompleteJpegSOIThrows_1107) {
    const unsigned char incompleteJpeg[] = {0xFF, 0xD8};
    // This might either succeed or fail depending on the implementation's tolerance
    // But it should not crash. We test it doesn't crash and either returns or throws.
    try {
        auto image = Exiv2::ImageFactory::open(incompleteJpeg, sizeof(incompleteJpeg));
        // If it succeeds, image should be non-null
        EXPECT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        // Acceptable: implementation might reject incomplete JPEG
        SUCCEED();
    }
}

// Test that a valid PNG image can be opened from memory
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenValidPngReturnsNonNull_1107) {
    auto image = Exiv2::ImageFactory::open(kMinimalPng, sizeof(kMinimalPng));
    ASSERT_NE(image, nullptr);
}

// Test getType with valid JPEG data from memory
TEST_F(ImageFactoryOpenFromMemoryTest_1107, GetTypeValidJpeg_1107) {
    auto type = Exiv2::ImageFactory::getType(kMinimalJpeg, sizeof(kMinimalJpeg));
    EXPECT_NE(type, Exiv2::ImageType::none);
}

// Test getType with garbage data
TEST_F(ImageFactoryOpenFromMemoryTest_1107, GetTypeGarbageData_1107) {
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03};
    auto type = Exiv2::ImageFactory::getType(garbage, sizeof(garbage));
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test that a large buffer of zeros throws unknown image type
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenLargeZeroBufferThrows_1107) {
    std::vector<unsigned char> zeros(10000, 0);
    EXPECT_THROW(
        Exiv2::ImageFactory::open(zeros.data(), zeros.size()),
        Exiv2::Error
    );
}

// Test opening valid JPEG and verifying it can be used (e.g., readMetadata doesn't crash)
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenValidJpegAndReadMetadata_1107) {
    auto image = Exiv2::ImageFactory::open(kMinimalJpeg, sizeof(kMinimalJpeg));
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test that getType returns correct type for PNG
TEST_F(ImageFactoryOpenFromMemoryTest_1107, GetTypeValidPng_1107) {
    auto type = Exiv2::ImageFactory::getType(kMinimalPng, sizeof(kMinimalPng));
    EXPECT_NE(type, Exiv2::ImageType::none);
}

// Test opening with almost-valid data (JPEG header but corrupted body)
TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpenCorruptedJpegBody_1107) {
    // Start with valid JPEG SOI + APP0 marker but corrupt the rest
    unsigned char corrupted[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    // This might still be recognized as JPEG by header detection
    try {
        auto image = Exiv2::ImageFactory::open(corrupted, sizeof(corrupted));
        EXPECT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test create with ImageType (in-memory)
TEST_F(ImageFactoryOpenFromMemoryTest_1107, CreateJpegInMemory_1107) {
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
        EXPECT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        // Some implementations may not support all creation modes
        SUCCEED();
    }
}
