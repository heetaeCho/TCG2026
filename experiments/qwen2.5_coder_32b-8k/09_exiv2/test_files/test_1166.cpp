#include <gtest/gtest.h>

#include "tiffimage_int.hpp"

#include "tags.hpp"



using namespace Exiv2::Internal;



class TiffCreatorTest : public ::testing::Test {

protected:

    TiffCreator tiffCreator;

};



TEST_F(TiffCreatorTest, GetPath_NormalOperation_1166) {

    uint32_t extendedTag = 0x112; // Example tag

    IfdId group = IfdId::ifd0Id;

    uint32_t root = 0;



    TiffPath path = tiffCreator.getPath(extendedTag, group, root);

    EXPECT_FALSE(path.empty());

}



TEST_F(TiffCreatorTest, GetPath_BoundaryCondition_RootIsZero_1166) {

    uint32_t extendedTag = 0x112; // Example tag

    IfdId group = IfdId::ifd0Id;

    uint32_t root = 0;



    TiffPath path = tiffCreator.getPath(extendedTag, group, root);

    EXPECT_FALSE(path.empty());

}



TEST_F(TiffCreatorTest, GetPath_BoundaryCondition_ExtendedTagIsZero_1166) {

    uint32_t extendedTag = 0;

    IfdId group = IfdId::ifd0Id;

    uint32_t root = 0;



    TiffPath path = tiffCreator.getPath(extendedTag, group, root);

    EXPECT_FALSE(path.empty());

}



TEST_F(TiffCreatorTest, GetPath_ErrorCase_GroupIsNotSet_1166) {

    uint32_t extendedTag = 0x112; // Example tag

    IfdId group = IfdId::ifdIdNotSet;

    uint32_t root = 0;



    TiffPath path = tiffCreator.getPath(extendedTag, group, root);

    EXPECT_TRUE(path.empty());

}



TEST_F(TiffCreatorTest, GetPath_ErrorCase_InvalidGroup_1166) {

    uint32_t extendedTag = 0x112; // Example tag

    IfdId group = static_cast<IfdId>(145); // Invalid group ID

    uint32_t root = 0;



    TiffPath path = tiffCreator.getPath(extendedTag, group, root);

    EXPECT_TRUE(path.empty());

}
