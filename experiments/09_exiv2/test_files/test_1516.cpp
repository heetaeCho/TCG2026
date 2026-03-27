#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



namespace Exiv2 {

namespace Internal {



using ::testing::IsNull;

using ::testing::NotNull;



class FujiMnTest : public ::testing::Test {

protected:

    uint16_t tag = 0x1234;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdSubIfd1;

    ByteOrder byteOrder = littleEndian;

};



TEST_F(FujiMnTest_NormalOperation_1516, ValidSize_ReturnsNonNullPointer_1516) {

    const size_t validSize = FujiMnHeader::sizeOfSignature() + 18;

    std::unique_ptr<TiffIfdMakernote> result = newFujiMn(tag, group, mnGroup, nullptr, validSize, byteOrder);

    EXPECT_THAT(result, NotNull());

}



TEST_F(FujiMnTest_BoundaryConditions_1516, MinimumValidSize_ReturnsNonNullPointer_1516) {

    const size_t minValidSize = FujiMnHeader::sizeOfSignature() + 18;

    std::unique_ptr<TiffIfdMakernote> result = newFujiMn(tag, group, mnGroup, nullptr, minValidSize, byteOrder);

    EXPECT_THAT(result, NotNull());

}



TEST_F(FujiMnTest_BoundaryConditions_1516, SizeLessThanMinimum_ReturnsNullPointer_1516) {

    const size_t invalidSize = FujiMnHeader::sizeOfSignature() + 17;

    std::unique_ptr<TiffIfdMakernote> result = newFujiMn(tag, group, mnGroup, nullptr, invalidSize, byteOrder);

    EXPECT_THAT(result, IsNull());

}



TEST_F(FujiMnTest_BoundaryConditions_1516, ZeroSize_ReturnsNullPointer_1516) {

    const size_t zeroSize = 0;

    std::unique_ptr<TiffIfdMakernote> result = newFujiMn(tag, group, mnGroup, nullptr, zeroSize, byteOrder);

    EXPECT_THAT(result, IsNull());

}



}  // namespace Internal

}  // namespace Exiv2
