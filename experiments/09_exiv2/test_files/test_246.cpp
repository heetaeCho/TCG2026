#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



namespace Exiv2 {

namespace Internal {



class TiffIfdMakernoteTest_246 : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader_;

    TiffIfdMakernote tiffIfdMakernote_;



    TiffIfdMakernoteTest_246()

        : pHeader_(std::make_unique<MnHeader>()),

          tiffIfdMakernote_(0x123, ifdIdMain, ifdIdExif, std::move(pHeader_), false) {}

};



TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_NormalOperation_246) {

    ByteOrder initialOrder = tiffIfdMakernote_.byteOrder();

    ByteOrder newOrder = littleEndian;

    

    tiffIfdMakernote_.setImageByteOrder(newOrder);

    EXPECT_NE(initialOrder, tiffIfdMakernote_.byteOrder());

    EXPECT_EQ(newOrder, tiffIfdMakernote_.byteOrder());

}



TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_BoundaryConditions_246) {

    ByteOrder newOrder = invalidByteOrder;

    

    tiffIfdMakernote_.setImageByteOrder(newOrder);

    EXPECT_EQ(invalidByteOrder, tiffIfdMakernote_.byteOrder());

}



TEST_F(TiffIfdMakernoteTest_246, ByteOrder_DefaultValue_246) {

    EXPECT_EQ(invalidByteOrder, tiffIfdMakernote_.byteOrder());

}



}  // namespace Internal

}  // namespace Exiv2
