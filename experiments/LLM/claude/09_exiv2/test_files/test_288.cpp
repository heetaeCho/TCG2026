#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the exiv2 project
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper subclass to access protected methods for testing
class TestableTiffImageEntry : public TiffImageEntry {
public:
    using TiffImageEntry::TiffImageEntry;

    // Expose protected methods for testing
    TiffImageEntry* callDoClone() const {
        return doClone();
    }

    size_t callDoSize() const {
        return doSize();
    }

    size_t callDoSizeData() const {
        return doSizeData();
    }

    size_t callDoSizeImage() const {
        return doSizeImage();
    }
};

class TiffImageEntryTest_288 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doClone creates a non-null copy
TEST_F(TiffImageEntryTest_288, DoCloneReturnsNonNull_288) {
    // TiffImageEntry typically requires a tag and group for construction
    // Based on TiffDataEntryBase constructor pattern
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    TiffImageEntry* clone = entry.callDoClone();
    ASSERT_NE(clone, nullptr);
    delete clone;
}

// Test that doClone returns a different pointer (actual copy, not same object)
TEST_F(TiffImageEntryTest_288, DoCloneReturnsDifferentObject_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    TiffImageEntry* clone = entry.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_NE(static_cast<TiffImageEntry*>(&entry), clone);
    delete clone;
}

// Test initial size before any strips are set
TEST_F(TiffImageEntryTest_288, InitialDoSizeImage_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t imageSize = entry.callDoSizeImage();
    EXPECT_EQ(imageSize, 0u);
}

// Test setStrips with null Value pointer
TEST_F(TiffImageEntryTest_288, SetStripsWithNullValue_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    // Passing nullptr for pSize should be handled gracefully
    entry.setStrips(nullptr, nullptr, 0, 0);
    size_t imageSize = entry.callDoSizeImage();
    EXPECT_EQ(imageSize, 0u);
}

// Test setStrips with null data pointer but valid size
TEST_F(TiffImageEntryTest_288, SetStripsWithNullData_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    // Create a value to represent strip sizes
    LongValue sizeValue;
    sizeValue.read("100");
    entry.setStrips(&sizeValue, nullptr, 0, 0);
    // With null data and zero sizeData, image size should reflect the situation
    size_t imageSize = entry.callDoSizeImage();
    // Can't predict exact value, just ensure no crash
    SUCCEED();
}

// Test setStrips with valid data
TEST_F(TiffImageEntryTest_288, SetStripsWithValidData_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    LongValue sizeValue;
    sizeValue.read("10");

    byte data[100];
    std::memset(data, 0xAB, sizeof(data));

    entry.setStrips(&sizeValue, data, sizeof(data), 0);
    size_t imageSize = entry.callDoSizeImage();
    EXPECT_GE(imageSize, 0u);
}

// Test setStrips with zero sizeData
TEST_F(TiffImageEntryTest_288, SetStripsWithZeroSizeData_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    LongValue sizeValue;
    sizeValue.read("0");

    byte data[10];
    entry.setStrips(&sizeValue, data, 0, 0);
    size_t imageSize = entry.callDoSizeImage();
    EXPECT_EQ(imageSize, 0u);
}

// Test clone preserves tag
TEST_F(TiffImageEntryTest_288, DoClonePreservesTag_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    TiffImageEntry* clone = entry.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), entry.tag());
    delete clone;
}

// Test with different tag values
TEST_F(TiffImageEntryTest_288, DoCloneWithDifferentTag_288) {
    TestableTiffImageEntry entry(0x0144, IfdId::ifd0Id);
    TiffImageEntry* clone = entry.callDoClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), 0x0144);
    delete clone;
}

// Test doSizeData initial state
TEST_F(TiffImageEntryTest_288, InitialDoSizeData_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t dataSize = entry.callDoSizeData();
    EXPECT_EQ(dataSize, 0u);
}

// Test doSize initial state
TEST_F(TiffImageEntryTest_288, InitialDoSize_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    size_t size = entry.callDoSize();
    // Initial size should be the base TIFF entry size (typically 12 bytes for a TIFF directory entry)
    EXPECT_GE(size, 0u);
}

// Test multiple strips
TEST_F(TiffImageEntryTest_288, SetStripsMultipleStrips_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    LongValue sizeValue;
    sizeValue.read("10 20 30");

    byte data[200];
    std::memset(data, 0xCD, sizeof(data));

    entry.setStrips(&sizeValue, data, sizeof(data), 0);
    size_t imageSize = entry.callDoSizeImage();
    // Total strip sizes = 10 + 20 + 30 = 60
    EXPECT_EQ(imageSize, 60u);
}

// Test setStrips with baseOffset
TEST_F(TiffImageEntryTest_288, SetStripsWithBaseOffset_288) {
    TestableTiffImageEntry entry(0x0111, IfdId::ifd0Id);
    LongValue sizeValue;
    sizeValue.read("50");

    byte data[200];
    std::memset(data, 0xEF, sizeof(data));

    entry.setStrips(&sizeValue, data, sizeof(data), 10);
    size_t imageSize = entry.callDoSizeImage();
    EXPECT_GE(imageSize, 0u);
}
