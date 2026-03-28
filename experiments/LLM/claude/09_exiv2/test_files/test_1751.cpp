#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

// Include necessary headers
#include "jp2image_int.hpp"

// Helper to create big-endian uint32_t bytes
static void putULongBE(uint8_t* buf, uint32_t val) {
    buf[0] = static_cast<uint8_t>((val >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((val >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((val >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(val & 0xFF);
}

static std::vector<uint8_t> buildBoxData(uint32_t brand, uint32_t minorVersion, const std::vector<uint32_t>& compatibilityList) {
    std::vector<uint8_t> data(8 + compatibilityList.size() * 4);
    putULongBE(data.data(), brand);
    putULongBE(data.data() + 4, minorVersion);
    for (size_t i = 0; i < compatibilityList.size(); i++) {
        putULongBE(data.data() + 8 + i * 4, compatibilityList[i]);
    }
    return data;
}

const uint32_t brandJp2 = 1785737760;
const uint32_t brandJph = 1785751584;

class IsValidBoxFileTypeTest_1751 : public ::testing::Test {};

// Test empty data returns false
TEST_F(IsValidBoxFileTypeTest_1751, EmptyData_1751) {
    std::vector<uint8_t> data;
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Test data smaller than 8 bytes returns false
TEST_F(IsValidBoxFileTypeTest_1751, TooSmallData_1751) {
    std::vector<uint8_t> data(7, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Test data of exactly 8 bytes with no compatibility list but brand=jp2, minorVersion=0
// Should return false because there's no compatibility list entry matching the brand
TEST_F(IsValidBoxFileTypeTest_1751, ExactlyEightBytesNoCompatibilityList_1751) {
    auto data = buildBoxData(brandJp2, 0, {});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Test data size not aligned to 4 bytes after the first 8 bytes returns false
TEST_F(IsValidBoxFileTypeTest_1751, MisalignedDataSize_1751) {
    std::vector<uint8_t> data(9, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

TEST_F(IsValidBoxFileTypeTest_1751, MisalignedDataSize10_1751) {
    std::vector<uint8_t> data(10, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

TEST_F(IsValidBoxFileTypeTest_1751, MisalignedDataSize11_1751) {
    std::vector<uint8_t> data(11, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Valid JP2 box: brand=jp2, minorVersion=0, compatibility list contains jp2
TEST_F(IsValidBoxFileTypeTest_1751, ValidJp2Brand_1751) {
    auto data = buildBoxData(brandJp2, 0, {brandJp2});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// Valid JPH box: brand=jph, minorVersion=0, compatibility list contains jph
TEST_F(IsValidBoxFileTypeTest_1751, ValidJphBrand_1751) {
    auto data = buildBoxData(brandJph, 0, {brandJph});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand but non-zero minor version returns false
TEST_F(IsValidBoxFileTypeTest_1751, Jp2NonZeroMinorVersion_1751) {
    auto data = buildBoxData(brandJp2, 1, {brandJp2});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JPH brand but non-zero minor version returns false
TEST_F(IsValidBoxFileTypeTest_1751, JphNonZeroMinorVersion_1751) {
    auto data = buildBoxData(brandJph, 1, {brandJph});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand but compatibility list does not contain jp2
TEST_F(IsValidBoxFileTypeTest_1751, Jp2BrandNotInCompatibilityList_1751) {
    auto data = buildBoxData(brandJp2, 0, {brandJph});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JPH brand but compatibility list does not contain jph
TEST_F(IsValidBoxFileTypeTest_1751, JphBrandNotInCompatibilityList_1751) {
    auto data = buildBoxData(brandJph, 0, {brandJp2});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Unknown brand with minorVersion=0 and some compatibility list
TEST_F(IsValidBoxFileTypeTest_1751, UnknownBrand_1751) {
    auto data = buildBoxData(0x12345678, 0, {0x12345678});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand with multiple entries in compatibility list, jp2 is present
TEST_F(IsValidBoxFileTypeTest_1751, Jp2BrandInMultipleEntries_1751) {
    auto data = buildBoxData(brandJp2, 0, {0x00000000, brandJph, brandJp2, 0xFFFFFFFF});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand with multiple entries in compatibility list, jp2 is NOT present
TEST_F(IsValidBoxFileTypeTest_1751, Jp2BrandNotInMultipleEntries_1751) {
    auto data = buildBoxData(brandJp2, 0, {0x00000000, brandJph, 0xFFFFFFFF});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JPH brand with multiple entries in compatibility list, jph is present
TEST_F(IsValidBoxFileTypeTest_1751, JphBrandInMultipleEntries_1751) {
    auto data = buildBoxData(brandJph, 0, {0x00000000, brandJp2, brandJph, 0xFFFFFFFF});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// JPH brand with multiple entries, jph NOT present
TEST_F(IsValidBoxFileTypeTest_1751, JphBrandNotInMultipleEntries_1751) {
    auto data = buildBoxData(brandJph, 0, {0x00000000, brandJp2, 0xFFFFFFFF});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand, minorVersion=0, compatibility list has jp2 as only entry (already tested above, just ensuring)
TEST_F(IsValidBoxFileTypeTest_1751, Jp2SingleEntryMatch_1751) {
    auto data = buildBoxData(brandJp2, 0, {brandJp2});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// Brand is jp2, compatibility list has jph (cross brand mismatch)
TEST_F(IsValidBoxFileTypeTest_1751, CrossBrandMismatchJp2Jph_1751) {
    auto data = buildBoxData(brandJp2, 0, {brandJph});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Brand is jph, compatibility list has jp2 (cross brand mismatch)
TEST_F(IsValidBoxFileTypeTest_1751, CrossBrandMismatchJphJp2_1751) {
    auto data = buildBoxData(brandJph, 0, {brandJp2});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Minor version = max uint32 value
TEST_F(IsValidBoxFileTypeTest_1751, LargeMinorVersion_1751) {
    auto data = buildBoxData(brandJp2, 0xFFFFFFFF, {brandJp2});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Size exactly 4 bytes (less than minimum 8)
TEST_F(IsValidBoxFileTypeTest_1751, FourBytes_1751) {
    std::vector<uint8_t> data(4, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Size 1 byte
TEST_F(IsValidBoxFileTypeTest_1751, OneByte_1751) {
    std::vector<uint8_t> data(1, 0);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand, minorVersion=0, very large compatibility list with jp2 at the end
TEST_F(IsValidBoxFileTypeTest_1751, Jp2MatchAtEndOfLargeList_1751) {
    std::vector<uint32_t> cl(100, 0x00000000);
    cl.back() = brandJp2;
    auto data = buildBoxData(brandJp2, 0, cl);
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// JP2 brand, minorVersion=0, large compatibility list with NO jp2
TEST_F(IsValidBoxFileTypeTest_1751, Jp2NoMatchInLargeList_1751) {
    std::vector<uint32_t> cl(100, 0x00000000);
    auto data = buildBoxData(brandJp2, 0, cl);
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// All zeros (brand=0, minorVersion=0, compatibility list={0})
TEST_F(IsValidBoxFileTypeTest_1751, AllZeros12Bytes_1751) {
    auto data = buildBoxData(0, 0, {0});
    EXPECT_FALSE(Exiv2::Internal::isValidBoxFileType(data));
}

// Brand jp2, minorVersion = 0, compatibility list with both jp2 and jph
TEST_F(IsValidBoxFileTypeTest_1751, Jp2BrandBothInList_1751) {
    auto data = buildBoxData(brandJp2, 0, {brandJp2, brandJph});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}

// Brand jph, minorVersion = 0, compatibility list with both jp2 and jph
TEST_F(IsValidBoxFileTypeTest_1751, JphBrandBothInList_1751) {
    auto data = buildBoxData(brandJph, 0, {brandJp2, brandJph});
    EXPECT_TRUE(Exiv2::Internal::isValidBoxFileType(data));
}
