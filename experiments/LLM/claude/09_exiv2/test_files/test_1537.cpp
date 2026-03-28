#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "makernote_int.hpp"

namespace Exiv2 {
namespace Internal {

// Forward declaration - the function under test
DataBuf nikonCrypt(uint16_t tag, const byte* pData, size_t size, TiffComponent* pRoot);

class NikonCryptTest_1537 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: size less than 4 should return empty DataBuf
TEST_F(NikonCryptTest_1537, SizeLessThan4ReturnsEmptyBuf_1537) {
    byte data[3] = {0x30, 0x32, 0x30};
    // Use any tag, doesn't matter since size < 4 is checked first
    // We need a valid TiffComponent, but it shouldn't matter since we return early
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 3, &root);
    EXPECT_TRUE(result.empty());
}

// Test: size == 0 returns empty DataBuf
TEST_F(NikonCryptTest_1537, SizeZeroReturnsEmptyBuf_1537) {
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, nullptr, 0, &root);
    EXPECT_TRUE(result.empty());
}

// Test: size == 1 returns empty DataBuf
TEST_F(NikonCryptTest_1537, SizeOneReturnsEmptyBuf_1537) {
    byte data[1] = {0x30};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 1, &root);
    EXPECT_TRUE(result.empty());
}

// Test: size == 2 returns empty DataBuf
TEST_F(NikonCryptTest_1537, SizeTwoReturnsEmptyBuf_1537) {
    byte data[2] = {0x30, 0x32};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 2, &root);
    EXPECT_TRUE(result.empty());
}

// Test: size == 3 returns empty DataBuf
TEST_F(NikonCryptTest_1537, SizeThreeReturnsEmptyBuf_1537) {
    byte data[3] = {0x30, 0x32, 0x30};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 3, &root);
    EXPECT_TRUE(result.empty());
}

// Test: tag not in nikonArrayIdx returns empty DataBuf
TEST_F(NikonCryptTest_1537, UnknownTagReturnsEmptyBuf_1537) {
    byte data[8] = {0x30, 0x32, 0x30, 0x38, 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    // Use a tag that doesn't exist in nikonArrayIdx (e.g., 9999)
    DataBuf result = nikonCrypt(9999, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: tag exists but version string doesn't match any entry returns empty
TEST_F(NikonCryptTest_1537, MismatchedVersionReturnsEmptyBuf_1537) {
    // Tag 145 with version "9999" - doesn't match any known version
    byte data[8] = {'9', '9', '9', '9', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: size exactly 4, matching tag/version but nci->start_ == 4 means size <= start
// Tag 145 "0208" has start_ = 4, so if size == 4, size <= nci->start_ is true (4 <= 4)
TEST_F(NikonCryptTest_1537, SizeEqualsStartReturnsEmptyBuf_1537) {
    byte data[4] = {'0', '2', '0', '8'};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 4, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Valid tag/version but empty TIFF tree (no 0x00a7 entry) returns empty
TEST_F(NikonCryptTest_1537, NoShutterCountEntryReturnsEmptyBuf_1537) {
    // Tag 145 "0208" has start_ = 4, so we need size > 4
    byte data[8] = {'0', '2', '0', '8', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(145, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Tag 151 "0100" has start_ = max uint32, which is NA
TEST_F(NikonCryptTest_1537, StartIsNAReturnsEmptyBuf_1537) {
    byte data[8] = {'0', '1', '0', '0', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(151, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Tag 152 "0100" has start_ = max uint32 (NA), returns empty
TEST_F(NikonCryptTest_1537, Tag152StartNAReturnsEmptyBuf_1537) {
    byte data[8] = {'0', '1', '0', '0', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(152, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Tag 168 "0100" has start_ = max uint32 (NA), returns empty
TEST_F(NikonCryptTest_1537, Tag168StartNAReturnsEmptyBuf_1537) {
    byte data[8] = {'0', '1', '0', '0', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(168, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Tag 183 with version "0100" has start_ = max (NA), returns empty
TEST_F(NikonCryptTest_1537, Tag183StartNAReturnsEmptyBuf_1537) {
    // nikonArrayIdx has {183, "0100", 30, 0, max} - start_ is max = NA
    byte data[8] = {'0', '1', '0', '0', 0x00, 0x00, 0x00, 0x00};
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(183, data, 8, &root);
    EXPECT_TRUE(result.empty());
}

// Test: Null pData with size >= 4 and unknown tag still returns empty (no match)
TEST_F(NikonCryptTest_1537, NullDataUnknownTagReturnsEmpty_1537) {
    TiffDirectory root(0, IfdId::ifd0Id);
    DataBuf result = nikonCrypt(9999, nullptr, 8, &root);
    EXPECT_TRUE(result.empty());
}

}  // namespace Internal
}  // namespace Exiv2
