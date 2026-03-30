#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



namespace Exiv2 {

namespace Internal {



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = IfdId::IFD0;

    IfdId mnGroup = IfdId::ExifIFD;

};



TEST_F(TiffIfdMakernoteTest_1529, CreateInstanceWithValidParameters_1529) {

    auto makernote = newSigmaMn2(tag, group, mnGroup);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1529, VerifyUniquePtrOwnership_1529) {

    auto makernote1 = newSigmaMn2(tag, group, mnGroup);

    auto makernote2 = std::move(makernote1);

    EXPECT_EQ(makernote1.get(), nullptr);

    EXPECT_NE(makernote2.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1529, BoundaryConditionMinimumTagValue_1529) {

    auto makernote = newSigmaMn2(0x0000, group, mnGroup);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1529, BoundaryConditionMaximumTagValue_1529) {

    auto makernote = newSigmaMn2(0xFFFF, group, mnGroup);

    EXPECT_NE(makernote.get(), nullptr);

}



} // namespace Internal

} // namespace Exiv2
