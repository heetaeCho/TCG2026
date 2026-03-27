#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::Return;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> mockHeader = std::make_unique<MnHeader>();

    TiffIfdMakernote makernote = TiffIfdMakernote(0x123, ifdIdExif, ifdIdExifSubIFD, std::move(mockHeader), true);

};



TEST_F(TiffIfdMakernoteTest_310, SizeHeader_ReturnsZeroWhenNoHeader_310) {

    EXPECT_EQ(makernote.sizeHeader(), 0);

}



TEST_F(TiffIfdMakernoteTest_310, SizeHeader_ReturnsHeaderSizeWhenHeaderExists_310) {

    auto mockHeader = std::make_unique<MnHeader>();

    EXPECT_CALL(*mockHeader, size()).WillOnce(Return(42));

    TiffIfdMakernote makernoteWithHeader(0x123, ifdIdExif, ifdIdExifSubIFD, std::move(mockHeader), true);

    EXPECT_EQ(makernoteWithHeader.sizeHeader(), 42);

}
