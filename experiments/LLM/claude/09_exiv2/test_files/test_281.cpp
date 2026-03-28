#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class TiffMappingInfoTest_281 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test exact make match with exact tag and group match
TEST_F(TiffMappingInfoTest_281, ExactMakeExactTagGroupMatch_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test wildcard make with exact tag and group match
TEST_F(TiffMappingInfoTest_281, WildcardMakeExactTagGroupMatch_281) {
    TiffMappingInfo info{"*", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Nikon", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test wildcard make with Tag::all and group match
TEST_F(TiffMappingInfoTest_281, WildcardMakeAllTagGroupMatch_281) {
    TiffMappingInfo info{"*", Tag::all, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Sony", 0x9999, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test exact make mismatch
TEST_F(TiffMappingInfoTest_281, MakeMismatch_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Nikon", 0x0001, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}

// Test tag mismatch
TEST_F(TiffMappingInfoTest_281, TagMismatch_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0002, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}

// Test group mismatch
TEST_F(TiffMappingInfoTest_281, GroupMismatch_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0001, IfdId::exifId};
    EXPECT_FALSE(info == key);
}

// Test make prefix match (key make starts with info make)
TEST_F(TiffMappingInfoTest_281, MakePrefixMatch_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon EOS", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test make prefix does not match (info make is longer)
TEST_F(TiffMappingInfoTest_281, MakePrefixNoMatch_281) {
    TiffMappingInfo info{"Canon EOS", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0001, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}

// Test Tag::all matches any tag in key
TEST_F(TiffMappingInfoTest_281, TagAllMatchesAnyTag_281) {
    TiffMappingInfo info{"Canon", Tag::all, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0xFFFF, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test all conditions fail: make mismatch, tag mismatch, group mismatch
TEST_F(TiffMappingInfoTest_281, AllConditionsFail_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Nikon", 0x0002, IfdId::exifId};
    EXPECT_FALSE(info == key);
}

// Test wildcard make with group mismatch
TEST_F(TiffMappingInfoTest_281, WildcardMakeGroupMismatch_281) {
    TiffMappingInfo info{"*", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0001, IfdId::exifId};
    EXPECT_FALSE(info == key);
}

// Test wildcard make with tag mismatch
TEST_F(TiffMappingInfoTest_281, WildcardMakeTagMismatch_281) {
    TiffMappingInfo info{"*", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0002, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}

// Test empty make in key with wildcard
TEST_F(TiffMappingInfoTest_281, EmptyKeyMakeWildcard_281) {
    TiffMappingInfo info{"*", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test empty make in key with non-wildcard info make
TEST_F(TiffMappingInfoTest_281, EmptyKeyMakeNonWildcard_281) {
    TiffMappingInfo info{"Canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"", 0x0001, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}

// Test empty make in info (not wildcard) with empty key make
TEST_F(TiffMappingInfoTest_281, EmptyInfoMakeEmptyKeyMake_281) {
    TiffMappingInfo info{"", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test Tag::all in info with Tag::all in key
TEST_F(TiffMappingInfoTest_281, TagAllInInfoTagAllInKey_281) {
    TiffMappingInfo info{"*", Tag::all, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", Tag::all, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test specific tag 0 match
TEST_F(TiffMappingInfoTest_281, TagZeroMatch_281) {
    TiffMappingInfo info{"*", 0x0000, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0000, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test that make comparison is prefix-based (key.m_ starts_with make_)
TEST_F(TiffMappingInfoTest_281, MakeStartsWithButNotEqual_281) {
    TiffMappingInfo info{"Nik", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Nikon", 0x0001, IfdId::ifd0Id};
    EXPECT_TRUE(info == key);
}

// Test that make comparison is case-sensitive
TEST_F(TiffMappingInfoTest_281, MakeCaseSensitive_281) {
    TiffMappingInfo info{"canon", 0x0001, IfdId::ifd0Id, nullptr, nullptr};
    TiffMappingInfo::Key key{"Canon", 0x0001, IfdId::ifd0Id};
    EXPECT_FALSE(info == key);
}
