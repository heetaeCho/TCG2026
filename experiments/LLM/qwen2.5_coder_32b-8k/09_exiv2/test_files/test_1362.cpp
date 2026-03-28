#include <gtest/gtest.h>

#include "tags_int.cpp"



namespace {



class TagInfoTest_1362 : public ::testing::Test {

protected:

    const Exiv2::Internal::TagInfo* tagList() {

        return Exiv2::Internal::mnTagList();

    }

};



TEST_F(TagInfoTest_1362, FirstElementIsOffset_1362) {

    const auto* tags = tagList();

    ASSERT_NE(tags, nullptr);

    EXPECT_EQ(tags[0].tag_, 1);

    EXPECT_STREQ(tags[0].name_.c_str(), "Offset");

    EXPECT_STREQ(tags[0].title_.c_str(), "Offset");

    EXPECT_STREQ(tags[0].description_.c_str(), "Offset of the makernote from the start of the TIFF header.");

}



TEST_F(TagInfoTest_1362, SecondElementIsByteOrder_1362) {

    const auto* tags = tagList();

    ASSERT_NE(tags, nullptr);

    EXPECT_EQ(tags[1].tag_, 2);

    EXPECT_STREQ(tags[1].name_.c_str(), "ByteOrder");

    EXPECT_STREQ(tags[1].title_.c_str(), "Byte Order");

    EXPECT_STREQ(tags[1].description_.c_str(), "Byte order used to encode MakerNote tags, 'MM' (big-endian) or 'II' (little-endian).");

}



TEST_F(TagInfoTest_1362, LastElementIsUnknownMnTag_1362) {

    const auto* tags = tagList();

    ASSERT_NE(tags, nullptr);

    EXPECT_EQ(tags[2].tag_, 65535);

    EXPECT_STREQ(tags[2].name_.c_str(), "(UnknownMnTag)");

    EXPECT_STREQ(tags[2].title_.c_str(), "Unknown Exiv2 Makernote info tag");

    EXPECT_STREQ(tags[2].description_.c_str(), "Unknown Exiv2 Makernote info tag");

}



TEST_F(TagInfoTest_1362, BoundaryCheckForArraySize_1362) {

    const auto* tags = tagList();

    ASSERT_NE(tags, nullptr);

    // Assuming the array size is 3 based on provided global variable

    EXPECT_EQ(tags[2].tag_, 65535); // Last element check

    EXPECT_DEATH(tags[3], ""); // Out of bounds access should cause an error (assuming address sanitizer or similar)

}



}  // namespace
