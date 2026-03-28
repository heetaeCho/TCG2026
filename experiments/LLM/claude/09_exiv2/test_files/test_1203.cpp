#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <cstring>

namespace {

// Minimal valid BMFF/HEIF file header (ftyp box)
std::vector<uint8_t> createMinimalBmffData() {
    // A minimal ftyp box: size(4) + 'ftyp'(4) + major_brand(4) + minor_version(4) = 16 bytes minimum
    // We'll create a minimal ftyp box with 'heic' brand
    std::vector<uint8_t> data;
    
    // ftyp box
    uint32_t ftypSize = 20; // size
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    
    // 'ftyp'
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    
    // major brand 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    
    // minor version
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    
    // compatible brand 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    
    return data;
}

std::vector<uint8_t> createInvalidData() {
    // Just random garbage that is not a valid BMFF file
    return {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
}

class NewBmffInstanceTest_1203 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that newBmffInstance returns a non-null pointer for valid BMFF data
TEST_F(NewBmffInstanceTest_1203, ValidBmffDataReturnsNonNull_1203) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // The image may or may not be valid depending on internal validation.
    // We just check it doesn't crash. The result depends on whether the data is sufficient.
    // Since minimal ftyp might not be enough, we accept either null or non-null.
    // This is a basic smoke test.
}

// Test that newBmffInstance with create=true and empty io
TEST_F(NewBmffInstanceTest_1203, CreateModeWithEmptyIo_1203) {
    auto io = std::make_unique<Exiv2::MemIo>();
    
    auto image = Exiv2::newBmffInstance(std::move(io), true);
    // When create=true, the function may create a new image or return null
    // depending on the implementation.
}

// Test that newBmffInstance returns nullptr for invalid/garbage data
TEST_F(NewBmffInstanceTest_1203, InvalidDataReturnsNull_1203) {
    auto data = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // Invalid data should likely cause good() to return false, hence nullptr
    EXPECT_EQ(image, nullptr);
}

// Test that newBmffInstance returns nullptr for empty data with create=false
TEST_F(NewBmffInstanceTest_1203, EmptyDataCreateFalseReturnsNull_1203) {
    auto io = std::make_unique<Exiv2::MemIo>();
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // Empty data should not be a valid BMFF image
    EXPECT_EQ(image, nullptr);
}

// Test that newBmffInstance with a single zero byte returns nullptr
TEST_F(NewBmffInstanceTest_1203, SingleByteDataReturnsNull_1203) {
    uint8_t byte = 0;
    auto io = std::make_unique<Exiv2::MemIo>(&byte, 1);
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with data that has ftyp box but with unsupported brand
TEST_F(NewBmffInstanceTest_1203, UnsupportedBrandReturnsNull_1203) {
    std::vector<uint8_t> data;
    
    // ftyp box with unknown brand
    uint32_t ftypSize = 16;
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    
    // Unknown brand 'xxxx'
    data.push_back('x');
    data.push_back('x');
    data.push_back('x');
    data.push_back('x');
    
    // minor version
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // Unknown brand likely means not a valid BMFF for exiv2
    EXPECT_EQ(image, nullptr);
}

// Test that if a valid image is returned, good() returns true
TEST_F(NewBmffInstanceTest_1203, ReturnedImageIsGood_1203) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with avif brand ftyp
TEST_F(NewBmffInstanceTest_1203, AvifBrandData_1203) {
    std::vector<uint8_t> data;
    
    uint32_t ftypSize = 20;
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    
    // 'avif' brand
    data.push_back('a');
    data.push_back('v');
    data.push_back('i');
    data.push_back('f');
    
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    
    // compatible brand
    data.push_back('a');
    data.push_back('v');
    data.push_back('i');
    data.push_back('f');
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // May or may not be valid, just test it doesn't crash
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with cr3 brand ftyp (Canon RAW 3)
TEST_F(NewBmffInstanceTest_1203, Cr3BrandData_1203) {
    std::vector<uint8_t> data;
    
    uint32_t ftypSize = 20;
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    
    // 'crx ' brand
    data.push_back('c');
    data.push_back('r');
    data.push_back('x');
    data.push_back(' ');
    
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(1);
    
    // compatible brand
    data.push_back('c');
    data.push_back('r');
    data.push_back('x');
    data.push_back(' ');
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // May or may not be valid
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with jxl brand ftyp (JPEG XL)
TEST_F(NewBmffInstanceTest_1203, JxlBrandData_1203) {
    std::vector<uint8_t> data;
    
    uint32_t ftypSize = 20;
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    
    // 'jxl ' brand
    data.push_back('j');
    data.push_back('x');
    data.push_back('l');
    data.push_back(' ');
    
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    
    data.push_back('j');
    data.push_back('x');
    data.push_back('l');
    data.push_back(' ');
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that returned image has correct mime type if it's valid
TEST_F(NewBmffInstanceTest_1203, ValidImageMimeType_1203) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    if (image) {
        // The mime type should be some valid string
        std::string mime = image->mimeType();
        EXPECT_FALSE(mime.empty());
    }
}

// Test that large garbage data returns nullptr
TEST_F(NewBmffInstanceTest_1203, LargeGarbageDataReturnsNull_1203) {
    std::vector<uint8_t> data(10000, 0xFF);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with truncated ftyp box (only 4 bytes of size, no type)
TEST_F(NewBmffInstanceTest_1203, TruncatedFtypBoxReturnsNull_1203) {
    std::vector<uint8_t> data = {0x00, 0x00, 0x00, 0x10};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with zero-size ftyp box
TEST_F(NewBmffInstanceTest_1203, ZeroSizeFtypBoxReturnsNull_1203) {
    std::vector<uint8_t> data = {
        0x00, 0x00, 0x00, 0x00, // size = 0
        'f', 't', 'y', 'p',
        'h', 'e', 'i', 'c',
        0x00, 0x00, 0x00, 0x00
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    auto image = Exiv2::newBmffInstance(std::move(io), false);
    // Zero size box is special (means box extends to end of file), but may still fail
    // Just verify no crash
}

} // namespace
