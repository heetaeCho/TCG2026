#include <gtest/gtest.h>

#include "tiffimage_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffMappingTest : public ::testing::Test {

protected:

    TiffMapping tiffMapping;

};



TEST_F(TiffMappingTest_1164, FindEncoder_ReturnsNullptrWhenNotFound_1164) {

    EncoderFct encoder = tiffMapping.findEncoder("NonExistentMake", 0x0000, IfdId::IFD0);

    EXPECT_EQ(encoder, nullptr);

}



TEST_F(TiffMappingTest_1164, FindEncoder_ReturnsValidPointerWhenFound_1164) {

    // Assuming there is a predefined entry in tiffMappingInfo_ for this key

    EncoderFct encoder = tiffMapping.findEncoder("Canon", 0x00FF, IfdId::IFD0);

    EXPECT_NE(encoder, nullptr);

}



TEST_F(TiffMappingTest_1164, FindEncoder_HandlesEmptyMakeString_1164) {

    EncoderFct encoder = tiffMapping.findEncoder("", 0x00FF, IfdId::IFD0);

    EXPECT_EQ(encoder, nullptr);

}



TEST_F(TiffMappingTest_1164, FindEncoder_HandlesZeroExtendedTag_1164) {

    EncoderFct encoder = tiffMapping.findEncoder("Canon", 0x0000, IfdId::IFD0);

    EXPECT_EQ(encoder, nullptr); // or some expected behavior

}



TEST_F(TiffMappingTest_1164, FindEncoder_HandlesMaxExtendedTag_1164) {

    EncoderFct encoder = tiffMapping.findEncoder("Canon", UINT32_MAX, IfdId::IFD0);

    EXPECT_EQ(encoder, nullptr); // or some expected behavior

}



TEST_F(TiffMappingTest_1164, FindEncoder_HandlesDifferentIfdGroups_1164) {

    EncoderFct encoderIFD0 = tiffMapping.findEncoder("Canon", 0x00FF, IfdId::IFD0);

    EncoderFct encoderEXIF = tiffMapping.findEncoder("Canon", 0x00FF, IfdId::ExifIFD);



    EXPECT_NE(encoderIFD0, encoderEXIF); // or both could be nullptr

}
