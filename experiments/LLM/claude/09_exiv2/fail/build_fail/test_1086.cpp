#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper to create an Image instance. Since Image is abstract (readMetadata/writeMetadata are pure virtual
// in some image types), we need a concrete subclass or use a known image type.
// We'll use a MemIo-based approach and create a minimal concrete Image subclass for testing.

class TestImage : public Exiv2::Image {
public:
    TestImage()
        : Image(ImageType::none, 0xFFFF, std::make_unique<MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}

    // Expose protected iccProfile_ for test setup
    void setIccProfileDirect(DataBuf&& buf) {
        iccProfile_ = std::move(buf);
    }

    DataBuf& getIccProfileRef() {
        return iccProfile_;
    }
};

class ImageCheckIccProfileTest_1086 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image;

    void SetUp() override {
        image = std::make_unique<TestImage>();
    }
};

// Test: Empty ICC profile should throw kerInvalidIccProfile
TEST_F(ImageCheckIccProfileTest_1086, EmptyProfileThrows_1086) {
    // iccProfile_ is empty by default (size 0, which is < sizeof(long))
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: ICC profile too small (less than sizeof(long)) should throw
TEST_F(ImageCheckIccProfileTest_1086, TooSmallProfileThrows_1086) {
    // Create a buffer smaller than sizeof(long) (typically 4 or 8 bytes)
    uint8_t smallBuf[2] = {0x00, 0x01};
    DataBuf buf(smallBuf, 2);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: ICC profile with size field not matching actual size should throw
TEST_F(ImageCheckIccProfileTest_1086, SizeMismatchThrows_1086) {
    // Create a buffer of 8 bytes but write a different size in the first 4 bytes (big endian)
    DataBuf buf(8);
    // Write size as 16 (doesn't match actual size of 8)
    buf.write_uint32(0, 16, bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: Valid ICC profile where size field matches buffer size should not throw
TEST_F(ImageCheckIccProfileTest_1086, ValidProfileDoesNotThrow_1086) {
    // Create a buffer of 8 bytes and write size=8 in the first 4 bytes (big endian)
    DataBuf buf(8);
    buf.write_uint32(0, 8, bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_NO_THROW(image->checkIccProfile());
}

// Test: Profile of exactly sizeof(long) with correct size
TEST_F(ImageCheckIccProfileTest_1086, MinimumValidProfileSize_1086) {
    size_t minSize = sizeof(long);
    DataBuf buf(minSize);
    buf.write_uint32(0, static_cast<uint32_t>(minSize), bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_NO_THROW(image->checkIccProfile());
}

// Test: Profile size field is zero but buffer is >= sizeof(long) — mismatch
TEST_F(ImageCheckIccProfileTest_1086, SizeFieldZeroThrows_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 0, bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: Large valid profile
TEST_F(ImageCheckIccProfileTest_1086, LargeValidProfile_1086) {
    size_t largeSize = 1024;
    DataBuf buf(largeSize);
    buf.write_uint32(0, static_cast<uint32_t>(largeSize), bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_NO_THROW(image->checkIccProfile());
}

// Test: Size field is 1 less than actual buffer size
TEST_F(ImageCheckIccProfileTest_1086, SizeFieldOneLessThanActual_1086) {
    DataBuf buf(100);
    buf.write_uint32(0, 99, bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: Size field is 1 more than actual buffer size
TEST_F(ImageCheckIccProfileTest_1086, SizeFieldOneMoreThanActual_1086) {
    DataBuf buf(100);
    buf.write_uint32(0, 101, bigEndian);
    image->setIccProfileDirect(std::move(buf));
    EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
}

// Test: Profile of size 3 bytes (less than sizeof(long) on most platforms where long >= 4)
TEST_F(ImageCheckIccProfileTest_1086, ThreeBytesProfileThrows_1086) {
    uint8_t data[3] = {0, 0, 3};
    DataBuf buf(data, 3);
    image->setIccProfileDirect(std::move(buf));
    if (sizeof(long) > 3) {
        EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
    }
}

// Test: setIccProfile with bTestValid=true on invalid profile should throw
TEST_F(ImageCheckIccProfileTest_1086, SetIccProfileWithValidationInvalid_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 16, bigEndian);  // mismatch
    EXPECT_THROW(image->setIccProfile(std::move(buf), true), Exiv2::Error);
}

// Test: setIccProfile with bTestValid=true on valid profile should succeed
TEST_F(ImageCheckIccProfileTest_1086, SetIccProfileWithValidationValid_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 8, bigEndian);
    EXPECT_NO_THROW(image->setIccProfile(std::move(buf), true));
    EXPECT_TRUE(image->iccProfileDefined());
}

// Test: setIccProfile with bTestValid=false on invalid profile should not throw
TEST_F(ImageCheckIccProfileTest_1086, SetIccProfileWithoutValidation_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 16, bigEndian);  // mismatch
    EXPECT_NO_THROW(image->setIccProfile(std::move(buf), false));
}

// Test: clearIccProfile clears the profile
TEST_F(ImageCheckIccProfileTest_1086, ClearIccProfile_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 8, bigEndian);
    image->setIccProfile(std::move(buf), true);
    EXPECT_TRUE(image->iccProfileDefined());
    image->clearIccProfile();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test: iccProfileDefined returns false for empty profile
TEST_F(ImageCheckIccProfileTest_1086, IccProfileDefinedFalseWhenEmpty_1086) {
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test: iccProfileDefined returns true after setting profile
TEST_F(ImageCheckIccProfileTest_1086, IccProfileDefinedTrueWhenSet_1086) {
    DataBuf buf(8);
    buf.write_uint32(0, 8, bigEndian);
    image->setIccProfile(std::move(buf), false);
    EXPECT_TRUE(image->iccProfileDefined());
}

// Test: Size exactly sizeof(long) - 1 should throw
TEST_F(ImageCheckIccProfileTest_1086, SizeSizeofLongMinusOneThrows_1086) {
    size_t sz = sizeof(long) - 1;
    if (sz > 0) {
        DataBuf buf(sz);
        image->setIccProfileDirect(std::move(buf));
        EXPECT_THROW(image->checkIccProfile(), Exiv2::Error);
    }
}
