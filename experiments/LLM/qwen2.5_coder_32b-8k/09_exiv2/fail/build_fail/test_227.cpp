#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffPathItemTest_227 : public ::testing::Test {

protected:

    static constexpr uint32_t kExtendedTag = 0x12345678;

    static constexpr IfdId kGroup = 1;



    TiffPathItem tiffPathItem_{kExtendedTag, kGroup};

};



TEST_F(TiffPathItemTest_227, GroupReturnsCorrectValue_227) {

    EXPECT_EQ(tiffPathItem_.group(), kGroup);

}



// Assuming tag() and extendedTag() are also part of the interface to be tested

TEST_F(TiffPathItemTest_227, ExtendedTagReturnsCorrectValue_227) {

    EXPECT_EQ(tiffPathItem_.extendedTag(), kExtendedTag);

}
