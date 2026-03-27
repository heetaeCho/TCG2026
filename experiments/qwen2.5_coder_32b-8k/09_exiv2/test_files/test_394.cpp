#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader = std::make_unique<MnHeader>();

    IfdId group = IfdId::rootIFD;

    IfdId mnGroup = IfdId::exifIFD;

    uint16_t tag = 0x927C; // Example tag for makernote

    bool hasNext = false;



    TiffIfdMakernote testSubject{tag, group, mnGroup, std::move(pHeader), hasNext};

};



TEST_F(TiffIfdMakernoteTest, Constructor_394) {

    EXPECT_EQ(testSubject.tag(), tag);

    EXPECT_EQ(testSubject.group(), group);

}



TEST_F(TiffIfdMakernoteTest, SetByteOrderAndGetByteOrder_394) {

    ByteOrder byteOrder = littleEndian;

    testSubject.setByteOrder(byteOrder);

    EXPECT_EQ(testSubject.byteOrder(), byteOrder);



    byteOrder = bigEndian;

    testSubject.setByteOrder(byteOrder);

    EXPECT_EQ(testSubject.byteOrder(), byteOrder);

}



TEST_F(TiffIfdMakernoteTest, DoSize_ReturnsHeaderAndIfdSize_394) {

    size_t expectedSize = testSubject.sizeHeader() + testSubject.ifd_.size();

    EXPECT_EQ(testSubject.doSize(), expectedSize);

}



TEST_F(TiffIfdMakernoteTest, WriteHeader_ReturnsCorrectSize_394) {

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t writtenSize = testSubject.writeHeader(mockIoWrapper, byteOrder);

    EXPECT_EQ(writtenSize, testSubject.sizeHeader());

}



TEST_F(TiffIfdMakernoteTest, MnOffset_ReturnsZeroInitially_394) {

    EXPECT_EQ(testSubject.mnOffset(), 0U);

}



TEST_F(TiffIfdMakernoteTest, IfdOffset_ReturnsCorrectValue_394) {

    size_t mnOffset = 123;

    testSubject.mnOffset_ = mnOffset;

    EXPECT_EQ(testSubject.ifdOffset(), mnOffset + testSubject.sizeHeader());

}
