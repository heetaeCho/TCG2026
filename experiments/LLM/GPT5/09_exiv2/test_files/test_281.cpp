#include <gtest/gtest.h>
#include <string_view>
#include "tiffcomposite_int.hpp"  // Adjust the include path if necessary

namespace Exiv2 { namespace Internal {

// Test fixture for TiffMappingInfo
class TiffMappingInfoTest : public ::testing::Test {
protected:
    TiffMappingInfoTest() = default;
    ~TiffMappingInfoTest() override = default;
};

// Test for equality operator (normal case)
TEST_F(TiffMappingInfoTest, EqualsNormal_281) {
    // Arrange
    TiffMappingInfo::Key key1{"MakeA", 123, Tag::all};
    TiffMappingInfo::Key key2{"MakeA", 123, Tag::all};
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "MakeA";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_TRUE(tiffInfo == key1);
    EXPECT_TRUE(tiffInfo == key2);
}

// Test for equality operator (mismatch on make_)
TEST_F(TiffMappingInfoTest, NotEqualsMake_282) {
    // Arrange
    TiffMappingInfo::Key key1{"MakeA", 123, Tag::all};
    TiffMappingInfo::Key key2{"MakeB", 123, Tag::all};
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "MakeA";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_FALSE(tiffInfo == key1);
    EXPECT_FALSE(tiffInfo == key2);
}

// Test for equality operator (mismatch on extendedTag_)
TEST_F(TiffMappingInfoTest, NotEqualsTag_283) {
    // Arrange
    TiffMappingInfo::Key key1{"MakeA", 123, Tag::all};
    TiffMappingInfo::Key key2{"MakeA", 123, Tag::fuji};  // Different tag
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "MakeA";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_FALSE(tiffInfo == key1);
    EXPECT_FALSE(tiffInfo == key2);
}

// Test for equality operator (mismatch on group_)
TEST_F(TiffMappingInfoTest, NotEqualsGroup_284) {
    // Arrange
    TiffMappingInfo::Key key1{"MakeA", 123, Tag::all};
    TiffMappingInfo::Key key2{"MakeA", 456, Tag::all};  // Different group
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "MakeA";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_FALSE(tiffInfo == key1);
    EXPECT_FALSE(tiffInfo == key2);
}

// Test for equality operator (wildcard make_)
TEST_F(TiffMappingInfoTest, EqualsWildcardMake_285) {
    // Arrange
    TiffMappingInfo::Key key1{"*", 123, Tag::all};  // Wildcard make
    TiffMappingInfo::Key key2{"*", 123, Tag::all};
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "*";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_TRUE(tiffInfo == key1);
    EXPECT_TRUE(tiffInfo == key2);
}

// Test for equality operator (all tag)
TEST_F(TiffMappingInfoTest, EqualsAllTag_286) {
    // Arrange
    TiffMappingInfo::Key key1{"MakeA", 123, Tag::all};
    TiffMappingInfo::Key key2{"MakeA", 123, Tag::all};
    TiffMappingInfo tiffInfo;
    tiffInfo.make_ = "MakeA";
    tiffInfo.extendedTag_ = Tag::all;
    tiffInfo.group_ = 123;

    // Act & Assert
    EXPECT_TRUE(tiffInfo == key1);
    EXPECT_TRUE(tiffInfo == key2);
}

} } // namespace Exiv2::Internal