#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffPathItemTest : public ::testing::Test {

protected:

    constexpr static uint32_t kExtendedTag = 0x12345678;

    constexpr static IfdId kGroup = 99;

    TiffPathItem pathItem{kExtendedTag, kGroup};

};



TEST_F(TiffPathItemTest_225, TagReturnsCorrectValue_225) {

    EXPECT_EQ(pathItem.tag(), static_cast<uint16_t>(kExtendedTag));

}



TEST_F(TiffPathItemTest_225, ExtendedTagReturnsCorrectValue_225) {

    EXPECT_EQ(pathItem.extendedTag(), kExtendedTag);

}



TEST_F(TiffPathItemTest_225, GroupReturnsCorrectValue_225) {

    EXPECT_EQ(pathItem.group(), kGroup);

}
