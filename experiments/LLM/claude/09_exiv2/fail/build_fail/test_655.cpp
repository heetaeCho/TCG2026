#include <gtest/gtest.h>
#include <exiv2/types.hpp>

// Since dataIgnoreList is a static function in the Internal namespace,
// we need to include the source or have it exposed for testing.
// We'll assume the function is accessible for testing purposes.
namespace Exiv2 {
namespace Internal {
bool dataIgnoreList(Exiv2::DataBuf& buf);
}
}

class DataIgnoreListTest_655 : public ::testing::Test {
protected:
    Exiv2::DataBuf createBufFromTag(const char* tag) {
        // Tags are 4 bytes, but the ignoreList entries are 5 bytes (4 chars + null)
        // equalsQTimeTag likely compares 4 bytes
        return Exiv2::DataBuf(reinterpret_cast<const Exiv2::byte*>(tag), 4);
    }
};

// Test all tags in the ignore list return true
TEST_F(DataIgnoreListTest_655, MoovReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("moov");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, MdiaReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("mdia");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, MinfReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("minf");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, DinfReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("dinf");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, AlisReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("alis");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, StblReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("stbl");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, CmovReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("cmov");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, MetaReturnsTrue_655) {
    Exiv2::DataBuf buf = createBufFromTag("meta");
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

// Test tags NOT in the ignore list return false
TEST_F(DataIgnoreListTest_655, FtypReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("ftyp");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, TrakReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("trak");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, UdtaReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("udta");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, FreeReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("free");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, MdatReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("mdat");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, EmptyStringReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("\0\0\0\0");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

// Test case sensitivity - uppercase versions should return false
TEST_F(DataIgnoreListTest_655, MOOVUppercaseReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("MOOV");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, METAUppercaseReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("META");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

// Test partial match - "moox" should not match "moov"
TEST_F(DataIgnoreListTest_655, PartialMatchReturnsFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("moox");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

// Test with buffer containing extra data after the tag
TEST_F(DataIgnoreListTest_655, MoovWithExtraDataReturnsTrue_655) {
    const char data[] = "moovextradata";
    Exiv2::DataBuf buf(reinterpret_cast<const Exiv2::byte*>(data), sizeof(data) - 1);
    EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(DataIgnoreListTest_655, RandomBytesReturnFalse_655) {
    const Exiv2::byte data[] = {0xFF, 0xFE, 0xFD, 0xFC};
    Exiv2::DataBuf buf(data, 4);
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

// Test with spaces
TEST_F(DataIgnoreListTest_655, SpacesReturnFalse_655) {
    Exiv2::DataBuf buf = createBufFromTag("    ");
    EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}
