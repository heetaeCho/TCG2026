#include <gtest/gtest.h>
#include <cstdint>
#include <memory>
#include <vector>

// Include necessary headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewIfdMnTest_1509 : public ::testing::Test {
protected:
    uint16_t tag_ = 0x927c;  // Common MakerNote tag
    IfdId group_ = IfdId::ifd0Id;
    IfdId mnGroup_ = IfdId::canonId;
    ByteOrder byteOrder_ = littleEndian;
};

// Test that nullptr is returned when size is 0
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIsZero_1509) {
    std::vector<byte> data(0);
    auto result = newIfdMn(tag_, group_, mnGroup_, nullptr, 0, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when size is 1
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIsOne_1509) {
    std::vector<byte> data(1, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 1, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when size is exactly 13 (boundary - 1)
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIs13_1509) {
    std::vector<byte> data(13, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 13, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when size is 7 (well below threshold)
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIs7_1509) {
    std::vector<byte> data(7, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 7, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test boundary: size exactly 14 should NOT return nullptr (should create object)
TEST_F(NewIfdMnTest_1509, ReturnsNonNullWhenSizeIs14_1509) {
    std::vector<byte> data(14, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 14, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that size 15 (above threshold) returns a valid object
TEST_F(NewIfdMnTest_1509, ReturnsNonNullWhenSizeIs15_1509) {
    std::vector<byte> data(15, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 15, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test with a larger buffer size
TEST_F(NewIfdMnTest_1509, ReturnsNonNullWhenSizeIsLarge_1509) {
    std::vector<byte> data(1024, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 1024, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test with big endian byte order
TEST_F(NewIfdMnTest_1509, WorksWithBigEndianByteOrder_1509) {
    std::vector<byte> data(14, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 14, bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test that size < 14 returns nullptr regardless of byte content
TEST_F(NewIfdMnTest_1509, ReturnsNullForSmallSizeRegardlessOfContent_1509) {
    std::vector<byte> data(13, 0xFF);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 13, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test with different tag value but valid size
TEST_F(NewIfdMnTest_1509, WorksWithDifferentTag_1509) {
    std::vector<byte> data(20, 0);
    auto result = newIfdMn(0x0001, group_, mnGroup_, data.data(), 20, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test size exactly at boundary with non-null data pointer
TEST_F(NewIfdMnTest_1509, BoundarySize14WithNonZeroData_1509) {
    std::vector<byte> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), data.size(), byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that size 2 returns nullptr
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIs2_1509) {
    std::vector<byte> data(2, 0);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 2, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test with size 12 (still below threshold)
TEST_F(NewIfdMnTest_1509, ReturnsNullWhenSizeIs12_1509) {
    std::vector<byte> data(12, 0xAB);
    auto result = newIfdMn(tag_, group_, mnGroup_, data.data(), 12, byteOrder_);
    EXPECT_EQ(result, nullptr);
}
