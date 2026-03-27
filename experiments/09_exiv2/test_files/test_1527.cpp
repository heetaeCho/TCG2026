#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffIfdMakernoteTest_1527 : public ::testing::Test {

protected:

    std::unique_ptr<TiffIfdMakernote> makernote;

};



TEST_F(TiffIfdMakernoteTest_1527, CreateInstanceWithValidParameters_1527) {

    uint16_t tag = 0x1000;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdSubImage;



    makernote = newSamsungMn2(tag, group, mnGroup);

    

    ASSERT_NE(makernote.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1527, CreateInstanceWithZeroTag_1527) {

    uint16_t tag = 0x0;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdSubImage;



    makernote = newSamsungMn2(tag, group, mnGroup);

    

    ASSERT_NE(makernote.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1527, CreateInstanceWithMaxTagValue_1527) {

    uint16_t tag = 0xFFFF;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdSubImage;



    makernote = newSamsungMn2(tag, group, mnGroup);

    

    ASSERT_NE(makernote.get(), nullptr);

}
