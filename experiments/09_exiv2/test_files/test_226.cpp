#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffPathItemTest_226 : public ::testing::Test {

protected:

    constexpr static uint32_t kExtendedTag = 0x1234;

    constexpr static IfdId kGroup = IfdId::rootIfd;



    TiffPathItem item{kExtendedTag, kGroup};

};



TEST_F(TiffPathItemTest_226, ExtendedTag_ReturnsCorrectValue_226) {

    EXPECT_EQ(item.extendedTag(), kExtendedTag);

}



TEST_F(TiffPathItemTest_226, Group_ReturnsCorrectValue_226) {

    EXPECT_EQ(item.group(), kGroup);

}
