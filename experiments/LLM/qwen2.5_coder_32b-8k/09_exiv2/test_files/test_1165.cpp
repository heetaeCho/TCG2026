#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage_int.hpp"

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffCreatorTest : public ::testing::Test {

protected:

    TiffCreator creator;

};



TEST_F(TiffCreatorTest_1165, Create_ReturnsNonNullForValidTagAndGroup_1165) {

    // Assuming there is at least one valid (extendedTag, group) pair in tiffGroupTable_

    uint32_t extendedTag = 0x8769; // Example valid tag

    IfdId group = IfdId::ifdExif;

    EXPECT_NE(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNullForInvalidTagAndGroup_1165) {

    uint32_t extendedTag = 0x0000; // Example invalid tag

    IfdId group = IfdId::ifdExif;

    EXPECT_EQ(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNullForValidTagAndInvalidGroup_1165) {

    uint32_t extendedTag = 0x8769; // Example valid tag

    IfdId group = static_cast<IfdId>(-1); // Example invalid group

    EXPECT_EQ(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNonNullForAllTagAndValidGroup_1165) {

    uint32_t extendedTag = Tag::all;

    IfdId group = IfdId::ifdExif;

    EXPECT_NE(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNullForAllTagAndInvalidGroup_1165) {

    uint32_t extendedTag = Tag::all;

    IfdId group = static_cast<IfdId>(-1); // Example invalid group

    EXPECT_EQ(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNullForInvalidTagAndAllGroup_1165) {

    uint32_t extendedTag = 0x0000; // Example invalid tag

    IfdId group = IfdId::ifdAny;

    EXPECT_EQ(nullptr, creator.create(extendedTag, group));

}



TEST_F(TiffCreatorTest_1165, Create_ReturnsNonNullForValidTagAndRootGroup_1165) {

    uint32_t extendedTag = 0x8769; // Example valid tag

    IfdId group = IfdId::ifdRoot;

    EXPECT_NE(nullptr, creator.create(extendedTag, group));

}



} // namespace Internal

} // namespace Exiv2
