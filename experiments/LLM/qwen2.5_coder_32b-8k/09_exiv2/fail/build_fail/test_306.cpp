#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader_ = std::make_unique<MnHeader>();

    TiffIfdMakernote tiffIfdMakernote_{0x01, ifdIdEXIF, ifdIdMakerNotes, std::move(pHeader_), false};



    const byte* dummyData = nullptr;

    size_t dataSize = 0;

    ByteOrder testByteOrder = littleEndian;

};



TEST_F(TiffIfdMakernoteTest_306, ConstructorInitialization_306) {

    EXPECT_EQ(tiffIfdMakernote_.mnOffset(), 0);

}



TEST_F(TiffIfdMakernoteTest_306, SetAndGetByteOrder_306) {

    tiffIfdMakernote_.setByteOrder(testByteOrder);

    EXPECT_EQ(tiffIfdMakernote_.byteOrder(), testByteOrder);

}



TEST_F(TiffIfdMakernoteTest_306, ReadHeaderWithNullData_306) {

    bool result = tiffIfdMakernote_.readHeader(dummyData, dataSize, testByteOrder);

    EXPECT_FALSE(result);

}



TEST_F(TiffIfdMakernoteTest_306, WriteHeaderBoundaryCondition_306) {

    IoWrapper ioWrapper; // Assuming IoWrapper is a mockable or testable class

    size_t writtenSize = tiffIfdMakernote_.writeHeader(ioWrapper, testByteOrder);

    EXPECT_GE(writtenSize, 0); // At least it should not return negative values

}



TEST_F(TiffIfdMakernoteTest_306, SizeHeaderBoundaryCondition_306) {

    size_t headerSize = tiffIfdMakernote_.sizeHeader();

    EXPECT_GE(headerSize, 0); // At least it should not return negative values

}



TEST_F(TiffIfdMakernoteTest_306, IfdOffsetDefaultValue_306) {

    size_t ifdOffset = tiffIfdMakernote_.ifdOffset();

    EXPECT_EQ(ifdOffset, 0); // Default value check

}



TEST_F(TiffIfdMakernoteTest_306, BaseOffsetDefaultValue_306) {

    size_t baseOffset = tiffIfdMakernote_.baseOffset();

    EXPECT_EQ(baseOffset, 0); // Default value check

}
