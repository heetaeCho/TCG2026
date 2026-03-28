#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte * pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));



    MockIoWrapper(BasicIo & io, const byte * pHeader, size_t size, OffsetWriter * pow)

        : IoWrapper(io, pHeader, size, pow) {}

};



class TiffComponentTest_375 : public ::testing::Test {

protected:

    ByteOrder byteOrder = ByteOrder::littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    MockIoWrapper mockIoWrapper{io, nullptr, 0, nullptr};

    TiffComponent tiffComponent{0x123, IfdId::rootIfd};



    BasicIo io;

};



TEST_F(TiffComponentTest_375, WriteDataNormalOperation_375) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(1).WillOnce(Return(4));

    size_t result = tiffComponent.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(result, 4);

}



TEST_F(TiffComponentTest_375, WriteDataBoundaryConditions_375) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(1).WillOnce(Return(0));

    size_t result = tiffComponent.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(result, 0);

}



TEST_F(TiffComponentTest_375, WriteDataExceptionalCase_375) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(1).WillOnce(Return(-1));

    size_t result = tiffComponent.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(result, static_cast<size_t>(-1));

}



TEST_F(TiffComponentTest_375, WriteDataImageIndexUpdate_375) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(1).WillOnce(Return(4));

    tiffComponent.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    EXPECT_EQ(imageIdx, 4); // Assuming imageIdx is updated by the amount written

}
