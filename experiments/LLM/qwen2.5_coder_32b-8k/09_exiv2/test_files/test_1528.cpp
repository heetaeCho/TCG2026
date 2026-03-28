#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest_1528 : public ::testing::Test {

protected:

    uint16_t tag = 0x1234;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdInteroperability;

    ByteOrder byteOrder = littleEndian;



    std::unique_ptr<byte> createBuffer(size_t size) {

        return std::unique_ptr<byte>(new byte[size]);

    }

};



TEST_F(TiffIfdMakernoteTest_1528, NewSigmaMn_ReturnsNullForSmallSize_1528) {

    auto buffer = createBuffer(SigmaMnHeader::sizeOfSignature() + 17);

    size_t size = SigmaMnHeader::sizeOfSignature() + 17;

    EXPECT_EQ(newSigmaMn(tag, group, mnGroup, buffer.get(), size, byteOrder), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1528, NewSigmaMn_ReturnsNonNullForValidSize_1528) {

    auto buffer = createBuffer(SigmaMnHeader::sizeOfSignature() + 19);

    size_t size = SigmaMnHeader::sizeOfSignature() + 19;

    EXPECT_NE(newSigmaMn(tag, group, mnGroup, buffer.get(), size, byteOrder), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1528, NewSigmaMn_ReturnsNonNullForBoundarySize_1528) {

    auto buffer = createBuffer(SigmaMnHeader::sizeOfSignature() + 18);

    size_t size = SigmaMnHeader::sizeOfSignature() + 18;

    EXPECT_NE(newSigmaMn(tag, group, mnGroup, buffer.get(), size, byteOrder), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1528, NewSigmaMn_ReturnsNullForZeroSize_1528) {

    auto buffer = createBuffer(0);

    size_t size = 0;

    EXPECT_EQ(newSigmaMn(tag, group, mnGroup, buffer.get(), size, byteOrder), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1528, NewSigmaMn_ReturnsNullForTinySize_1528) {

    auto buffer = createBuffer(1);

    size_t size = 1;

    EXPECT_EQ(newSigmaMn(tag, group, mnGroup, buffer.get(), size, byteOrder), nullptr);

}
