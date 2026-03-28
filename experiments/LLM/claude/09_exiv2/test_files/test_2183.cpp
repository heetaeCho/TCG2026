#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <memory>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_2183 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction from string key ====================

TEST_F(ExifKeyTest_2183, ConstructFromValidStringKey_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

TEST_F(ExifKeyTest_2183, ConstructFromValidStringKeyImageWidth_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.ImageWidth"));
}

TEST_F(ExifKeyTest_2183, ConstructFromValidStringKeyPhoto_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal"));
}

TEST_F(ExifKeyTest_2183, ConstructFromInvalidStringKeyThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key("Invalid.Key.Format"), Exiv2::Error);
}

TEST_F(ExifKeyTest_2183, ConstructFromEmptyStringThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

TEST_F(ExifKeyTest_2183, ConstructFromWrongFamilyThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key("Iptc.Application2.Caption"), Exiv2::Error);
}

TEST_F(ExifKeyTest_2183, ConstructFromPartialKeyThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key("Exif.Image"), Exiv2::Error);
}

// ==================== Construction from tag and group name ====================

TEST_F(ExifKeyTest_2183, ConstructFromTagAndGroupName_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
}

TEST_F(ExifKeyTest_2183, ConstructFromTagAndGroupNamePhoto_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x9003, "Photo"));
}

// ==================== key() method ====================

TEST_F(ExifKeyTest_2183, KeyReturnsCorrectString_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

TEST_F(ExifKeyTest_2183, KeyReturnsCorrectStringForImageWidth_2183) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.key(), "Exif.Image.ImageWidth");
}

// ==================== familyName() method ====================

TEST_F(ExifKeyTest_2183, FamilyNameReturnsExif_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// ==================== groupName() method ====================

TEST_F(ExifKeyTest_2183, GroupNameReturnsImage_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_2183, GroupNameReturnsPhoto_2183) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
}

// ==================== tagName() method ====================

TEST_F(ExifKeyTest_2183, TagNameReturnsMake_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

TEST_F(ExifKeyTest_2183, TagNameReturnsImageWidth_2183) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

// ==================== tag() method ====================

TEST_F(ExifKeyTest_2183, TagReturnsCorrectValue_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

TEST_F(ExifKeyTest_2183, TagReturnsCorrectValueForImageWidth_2183) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
}

// ==================== tagLabel() method ====================

TEST_F(ExifKeyTest_2183, TagLabelReturnsNonEmpty_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_FALSE(key.tagLabel().empty());
}

// ==================== tagDesc() method ====================

TEST_F(ExifKeyTest_2183, TagDescReturnsString_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // tagDesc may or may not be empty, but shouldn't throw
    ASSERT_NO_THROW(key.tagDesc());
}

// ==================== Copy constructor ====================

TEST_F(ExifKeyTest_2183, CopyConstructorCreatesEqualKey_2183) {
    Exiv2::ExifKey original("Exif.Image.Make");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_STREQ(copy.familyName(), original.familyName());
}

// ==================== Assignment operator ====================

TEST_F(ExifKeyTest_2183, AssignmentOperatorCopiesCorrectly_2183) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.ImageWidth");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Image.Make");
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
}

// ==================== clone() method ====================

TEST_F(ExifKeyTest_2183, CloneCreatesEqualKey_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

// ==================== setIdx() and idx() methods ====================

TEST_F(ExifKeyTest_2183, DefaultIdxIsZero_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_2183, SetIdxAndGetIdx_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

TEST_F(ExifKeyTest_2183, SetIdxNegativeValue_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// ==================== Construction from tag number and group ====================

TEST_F(ExifKeyTest_2183, ConstructFromTagNumberReturnsCorrectKey_2183) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
}

// ==================== defaultTypeId() method ====================

TEST_F(ExifKeyTest_2183, DefaultTypeIdReturnsValidType_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Make tag has type asciiString
    ASSERT_NO_THROW(key.defaultTypeId());
}

TEST_F(ExifKeyTest_2183, DefaultTypeIdForImageWidth_2183) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    ASSERT_NO_THROW(key.defaultTypeId());
}

// ==================== ifdId() method ====================

TEST_F(ExifKeyTest_2183, IfdIdReturnsValidId_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    ASSERT_NO_THROW(key.ifdId());
}

// ==================== write() via Key base class ====================

TEST_F(ExifKeyTest_2183, WriteOutputsKey_2183) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::ostringstream os;
    os << key;
    EXPECT_EQ(os.str(), key.key());
}

// ==================== GPS group ====================

TEST_F(ExifKeyTest_2183, ConstructGPSKey_2183) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude"));
}

TEST_F(ExifKeyTest_2183, GPSKeyProperties_2183) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// ==================== Copy preserves idx ====================

TEST_F(ExifKeyTest_2183, CopyConstructorPreservesIdx_2183) {
    Exiv2::ExifKey original("Exif.Image.Make");
    original.setIdx(99);
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.idx(), 99);
}

TEST_F(ExifKeyTest_2183, AssignmentPreservesIdx_2183) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(77);
    Exiv2::ExifKey key2("Exif.Image.ImageWidth");
    key2 = key1;
    EXPECT_EQ(key2.idx(), 77);
}

// ==================== Unknown/hex tag in key string ====================

TEST_F(ExifKeyTest_2183, ConstructWithHexTagName_2183) {
    // Some implementations allow hex tag names like "0xffff"
    // This may or may not throw depending on implementation
    try {
        Exiv2::ExifKey key("Exif.Image.0x0001");
        // If it doesn't throw, it should still be a valid key
        EXPECT_FALSE(key.key().empty());
    } catch (const Exiv2::Error&) {
        // It's acceptable to throw for unknown tags
    }
}

// ==================== Invalid group name ====================

TEST_F(ExifKeyTest_2183, ConstructWithInvalidGroupThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key("Exif.NonExistentGroup.SomeTag"), Exiv2::Error);
}

// ==================== Multiple dots in key ====================

TEST_F(ExifKeyTest_2183, ConstructWithExtraDotsThrows_2183) {
    ASSERT_THROW(Exiv2::ExifKey key("Exif.Image.Make.Extra"), Exiv2::Error);
}

}  // namespace
