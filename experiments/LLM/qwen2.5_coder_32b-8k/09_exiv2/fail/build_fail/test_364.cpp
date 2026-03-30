#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_364 : public ::testing::Test {

protected:

    IoWrapper ioWrapperMock;

    TiffComponent tiffComponentMock;



    TiffComponentTest_364()

        : ioWrapperMock(nullptr, nullptr, 0, nullptr),

          tiffComponentMock(0, IfdId())

    {}

};



TEST_F(TiffComponentTest_364, WriteReturnsValueFromDoWrite_364) {

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(1);

    size_t result = tiffComponentMock.write(ioWrapperMock, ByteOrder::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_EQ(result, tiffComponentMock.doWrite(ioWrapperMock, ByteOrder::littleEndian, 0, 0, 0, imageIdx));

}



TEST_F(TiffComponentTest_364, WriteUpdatesImageIndex_364) {

    size_t initialImageIdx = 10;

    size_t expectedNewImageIdx = initialImageIdx + 5; // Assuming doWrite modifies imageIdx

    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(1);

    tiffComponentMock.write(ioWrapperMock, ByteOrder::littleEndian, 0, 0, 0, initialImageIdx);

    EXPECT_EQ(initialImageIdx, expectedNewImageIdx); // This will fail if doWrite does not modify imageIdx

}



TEST_F(TiffComponentTest_364, WriteWithBoundaryConditions_364) {

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(1);

    size_t result = tiffComponentMock.write(ioWrapperMock, ByteOrder::littleEndian, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), imageIdx);

    EXPECT_EQ(result, tiffComponentMock.doWrite(ioWrapperMock, ByteOrder::littleEndian, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), imageIdx));

}



TEST_F(TiffComponentTest_364, WriteWithZeroValues_364) {

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(1);

    size_t result = tiffComponentMock.write(ioWrapperMock, ByteOrder::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_EQ(result, tiffComponentMock.doWrite(ioWrapperMock, ByteOrder::littleEndian, 0, 0, 0, imageIdx));

}
