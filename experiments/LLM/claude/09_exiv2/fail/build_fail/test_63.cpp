#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

// Include necessary Exiv2 headers
#include "image_int.hpp"
#include "slice.hpp"

namespace {

using Exiv2::Internal::binaryToString;
using Exiv2::Slice;

// Helper to create a slice from a vector
template <typename T>
Slice<T*> makeSlice(std::vector<typename std::remove_const<T>::type>& v, size_t begin, size_t end) {
    return Slice<T*>(v.data(), begin, end);
}

// Test normal ASCII printable characters
TEST(BinaryToStringTest_63, PrintableAsciiCharacters_63) {
    std::vector<uint8_t> data = {'H', 'e', 'l', 'l', 'o'};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    // Printable ASCII should appear as-is in the result
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
    EXPECT_NE(resultStr.find('H'), std::string::npos);
    EXPECT_NE(resultStr.find('e'), std::string::npos);
}

// Test empty slice
TEST(BinaryToStringTest_63, EmptySlice_63) {
    std::vector<uint8_t> data;
    auto slice = Slice<uint8_t*>(data.data(), 0, 0);
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_TRUE(resultStr.empty());
}

// Test single byte - printable
TEST(BinaryToStringTest_63, SinglePrintableByte_63) {
    std::vector<uint8_t> data = {'A'};
    auto slice = Slice<uint8_t*>(data.data(), 0, 1);
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
    EXPECT_NE(resultStr.find('A'), std::string::npos);
}

// Test single byte - non-printable
TEST(BinaryToStringTest_63, SingleNonPrintableByte_63) {
    std::vector<uint8_t> data = {0x01};
    auto slice = Slice<uint8_t*>(data.data(), 0, 1);
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    // Non-printable characters should be escaped/replaced, so 'A'-'Z' shouldn't appear raw
    // At minimum the result should not be empty (it should have some representation)
    EXPECT_FALSE(resultStr.empty());
}

// Test null bytes
TEST(BinaryToStringTest_63, NullBytes_63) {
    std::vector<uint8_t> data = {0x00, 0x00, 0x00};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    // Result may or may not be empty depending on how nulls are handled
    // But the function should not crash
}

// Test mixed printable and non-printable
TEST(BinaryToStringTest_63, MixedPrintableAndNonPrintable_63) {
    std::vector<uint8_t> data = {'A', 0x01, 'B', 0xFF, 'C'};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test all printable ASCII range
TEST(BinaryToStringTest_63, AllPrintableAscii_63) {
    std::vector<uint8_t> data;
    for (uint8_t i = 0x20; i < 0x7F; ++i) {
        data.push_back(i);
    }
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test high bytes (0x80-0xFF)
TEST(BinaryToStringTest_63, HighBytes_63) {
    std::vector<uint8_t> data = {0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xFF};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    // Should handle high bytes without crashing
    EXPECT_FALSE(resultStr.empty());
}

// Test with partial slice (not starting at 0)
TEST(BinaryToStringTest_63, PartialSliceFromMiddle_63) {
    std::vector<uint8_t> data = {'A', 'B', 'C', 'D', 'E'};
    auto slice = Slice<uint8_t*>(data.data(), 1, 4);
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
    // Should contain B, C, D but not necessarily A or E
    EXPECT_NE(resultStr.find('B'), std::string::npos);
    EXPECT_NE(resultStr.find('C'), std::string::npos);
    EXPECT_NE(resultStr.find('D'), std::string::npos);
}

// Test with const data
TEST(BinaryToStringTest_63, ConstData_63) {
    const std::vector<uint8_t> data = {'X', 'Y', 'Z'};
    auto slice = Slice<const uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test binary data representing common image header bytes
TEST(BinaryToStringTest_63, ImageHeaderBytes_63) {
    // JPEG SOI marker
    std::vector<uint8_t> data = {0xFF, 0xD8, 0xFF, 0xE0};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    // Should not crash on typical binary image data
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test large data
TEST(BinaryToStringTest_63, LargeData_63) {
    std::vector<uint8_t> data(1000, 'A');
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test space character (boundary of printable)
TEST(BinaryToStringTest_63, SpaceCharacter_63) {
    std::vector<uint8_t> data = {0x20}; // space
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_FALSE(resultStr.empty());
}

// Test tilde character (upper boundary of printable ASCII)
TEST(BinaryToStringTest_63, TildeCharacter_63) {
    std::vector<uint8_t> data = {0x7E}; // ~
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    std::string resultStr(result);
    EXPECT_NE(resultStr.find('~'), std::string::npos);
}

// Test DEL character (0x7F - non-printable)
TEST(BinaryToStringTest_63, DelCharacter_63) {
    std::vector<uint8_t> data = {0x7F};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    // Should handle DEL without crashing
}

// Test control characters
TEST(BinaryToStringTest_63, ControlCharacters_63) {
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    auto slice = Slice<uint8_t*>(data.data(), 0, data.size());
    auto result = binaryToString(std::move(slice));
    // Should represent control characters in some way without crashing
}

}  // namespace
