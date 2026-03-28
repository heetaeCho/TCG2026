#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/metadatum.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <memory>
#include <string>
#include <sstream>

namespace {

// We'll use concrete Key implementations from exiv2 to test the Key interface
// since Key itself is abstract. ExifKey, IptcKey, and XmpKey are concrete subclasses.

class KeyCloneTest_109 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that cloning an ExifKey produces a valid copy
TEST_F(KeyCloneTest_109, ExifKeyCloneProducesValidCopy_109) {
    Exiv2::ExifKey original("Exif.Image.Make");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->tag(), original.tag());
    EXPECT_EQ(cloned->tagName(), original.tagName());
    EXPECT_STREQ(cloned->familyName(), original.familyName());
    EXPECT_EQ(cloned->groupName(), original.groupName());
}

// Test that cloned key is independent from original
TEST_F(KeyCloneTest_109, ExifKeyCloneIsIndependent_109) {
    Exiv2::ExifKey original("Exif.Image.Make");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    // Verify that the cloned pointer is different from the original address
    EXPECT_NE(cloned.get(), &original);
    // Both should still have the same values
    EXPECT_EQ(cloned->key(), original.key());
}

// Test ExifKey properties
TEST_F(KeyCloneTest_109, ExifKeyProperties_109) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test ExifKey tag value
TEST_F(KeyCloneTest_109, ExifKeyTagValue_109) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Make tag is 0x010f = 271
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test IptcKey clone
TEST_F(KeyCloneTest_109, IptcKeyCloneProducesValidCopy_109) {
    Exiv2::IptcKey original("Iptc.Application2.Caption");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->tag(), original.tag());
    EXPECT_EQ(cloned->tagName(), original.tagName());
    EXPECT_STREQ(cloned->familyName(), original.familyName());
    EXPECT_EQ(cloned->groupName(), original.groupName());
}

// Test IptcKey properties
TEST_F(KeyCloneTest_109, IptcKeyProperties_109) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    EXPECT_EQ(key.key(), "Iptc.Application2.Caption");
    EXPECT_STREQ(key.familyName(), "Iptc");
    EXPECT_EQ(key.groupName(), "Application2");
    EXPECT_EQ(key.tagName(), "Caption");
}

// Test XmpKey clone
TEST_F(KeyCloneTest_109, XmpKeyCloneProducesValidCopy_109) {
    Exiv2::XmpKey original("Xmp.dc.title");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->tag(), original.tag());
    EXPECT_EQ(cloned->tagName(), original.tagName());
    EXPECT_STREQ(cloned->familyName(), original.familyName());
    EXPECT_EQ(cloned->groupName(), original.groupName());
}

// Test XmpKey properties
TEST_F(KeyCloneTest_109, XmpKeyProperties_109) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(KeyCloneTest_109, ExifKeyTagLabelNonEmpty_109) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test that invalid ExifKey construction throws
TEST_F(KeyCloneTest_109, InvalidExifKeyThrows_109) {
    EXPECT_THROW(Exiv2::ExifKey("Invalid.Key.Format.TooMany"), Exiv2::Error);
}

// Test that invalid IptcKey construction throws
TEST_F(KeyCloneTest_109, InvalidIptcKeyThrows_109) {
    EXPECT_THROW(Exiv2::IptcKey("Invalid.Key"), Exiv2::Error);
}

// Test ExifKey copy constructor
TEST_F(KeyCloneTest_109, ExifKeyCopyConstructor_109) {
    Exiv2::ExifKey original("Exif.Image.Model");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_STREQ(copy.familyName(), original.familyName());
    EXPECT_EQ(copy.groupName(), original.groupName());
}

// Test write method via ostream operator
TEST_F(KeyCloneTest_109, ExifKeyWriteToStream_109) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::ostringstream oss;
    oss << key;
    EXPECT_FALSE(oss.str().empty());
}

// Test cloning preserves tagDesc
TEST_F(KeyCloneTest_109, ClonePreservesTagDesc_109) {
    Exiv2::ExifKey original("Exif.Image.Make");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tagDesc(), original.tagDesc());
}

// Test cloning preserves tagLabel
TEST_F(KeyCloneTest_109, ClonePreservesTagLabel_109) {
    Exiv2::ExifKey original("Exif.Image.Make");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tagLabel(), original.tagLabel());
}

// Test multiple clones are all independent
TEST_F(KeyCloneTest_109, MultipleCloresAreIndependent_109) {
    Exiv2::ExifKey original("Exif.Image.Make");
    auto clone1 = original.clone();
    auto clone2 = original.clone();
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_NE(clone1.get(), clone2.get());
    EXPECT_EQ(clone1->key(), clone2->key());
}

// Test ExifKey constructed from tag number
TEST_F(KeyCloneTest_109, ExifKeyFromTagNumber_109) {
    // 0x010f is the Make tag in IFD0
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.tagName(), "Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test ExifKey constructed from tag number clone
TEST_F(KeyCloneTest_109, ExifKeyFromTagNumberClone_109) {
    Exiv2::ExifKey original(0x010f, "Image");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->tag(), original.tag());
}

// Test different ExifKey groups
TEST_F(KeyCloneTest_109, ExifKeyDifferentGroups_109) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Photo.DateTimeOriginal");
    EXPECT_NE(key1.groupName(), key2.groupName());
    EXPECT_NE(key1.tag(), key2.tag());
}

} // namespace
