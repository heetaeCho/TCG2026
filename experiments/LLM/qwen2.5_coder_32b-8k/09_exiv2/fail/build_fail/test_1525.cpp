#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest_1525 : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdInteroperability;

};



TEST_F(TiffIfdMakernoteTest_1525, CreateInstanceWithValidTagAndGroups_1525) {

    auto makernote = newPentaxDngMn2(tag, group, mnGroup);

    ASSERT_NE(makernote, nullptr);

}



TEST_F(TiffIfdMakernoteTest_1525, CreateInstanceWithZeroTag_1525) {

    uint16_t zeroTag = 0x0000;

    auto makernote = newPentaxDngMn2(zeroTag, group, mnGroup);

    ASSERT_NE(makernote, nullptr);

}



TEST_F(TiffIfdMakernoteTest_1525, CreateInstanceWithMaxTagValue_1525) {

    uint16_t maxTag = 0xFFFF;

    auto makernote = newPentaxDngMn2(maxTag, group, mnGroup);

    ASSERT_NE(makernote, nullptr);

}



TEST_F(TiffIfdMakernoteTest_1525, CreateInstanceWithVariousGroups_1525) {

    IfdId otherGroup = ifdGps;

    auto makernote = newPentaxDngMn2(tag, otherGroup, mnGroup);

    ASSERT_NE(makernote, nullptr);



    IfdId anotherGroup = ifdExifIFD;

    auto anotherMakernote = newPentaxDngMn2(tag, group, anotherGroup);

    ASSERT_NE(anotherMakernote, nullptr);

}



TEST_F(TiffIfdMakernoteTest_1525, VerifyUniquePointerOwnership_1525) {

    std::unique_ptr<TiffIfdMakernote> makernote = newPentaxDngMn2(tag, group, mnGroup);

    EXPECT_EQ(makernote.use_count(), 1);



    auto rawPtr = makernote.get();

    std::unique_ptr<TiffIfdMakernote> anotherMakernote(rawPtr);

    EXPECT_TRUE(makernote == nullptr); // Original unique_ptr should be empty

}
