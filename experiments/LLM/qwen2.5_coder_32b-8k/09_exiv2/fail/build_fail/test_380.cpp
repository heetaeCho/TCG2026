#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD6(write, size_t(IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t & imageIdx));

};



class MockIoWrapper : public IoWrapper {

public:

    using IoWrapper::IoWrapper;

    MOCK_METHOD2(write, size_t(const byte * pData, size_t wcount));

    MOCK_METHOD1(putb, int(byte data));

};



class TiffSubIfdTest_380 : public ::testing::Test {

protected:

    MockTiffComponent mockIfd1;

    MockTiffComponent mockIfd2;

    MockIoWrapper mockIoWrapper;

    std::vector<TiffComponent*> ifds_;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    TiffSubIfdTest_380() : mockIoWrapper(nullptr, nullptr, 0, nullptr) {

        ifds_.push_back(&mockIfd1);

        ifds_.push_back(&mockIfd2);

    }

};



TEST_F(TiffSubIfdTest_380, DoWriteData_NormalOperation_380) {

    EXPECT_CALL(mockIfd1, write(_, _, 0 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(5));

    EXPECT_CALL(mockIfd2, write(_, _, 5 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(3));

    EXPECT_CALL(mockIoWrapper, putb(0x0));



    TiffSubIfd tiffSubIfd(0, ifdExif, ifdExif);

    size_t result = tiffSubIfd.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 9);

}



TEST_F(TiffSubIfdTest_380, DoWriteData_NoAlignmentNeeded_380) {

    EXPECT_CALL(mockIfd1, write(_, _, 0 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(4));

    EXPECT_CALL(mockIoWrapper, putb(_)).Times(0);



    TiffSubIfd tiffSubIfd(0, ifdExif, ifdExif);

    size_t result = tiffSubIfd.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 4);

}



TEST_F(TiffSubIfdTest_380, DoWriteData_EmptyIFDs_380) {

    ifds_.clear();

    EXPECT_CALL(mockIoWrapper, putb(_)).Times(0);



    TiffSubIfd tiffSubIfd(0, ifdExif, ifdExif);

    size_t result = tiffSubIfd.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffSubIfdTest_380, DoWriteData_ExceptionalCase_WriteFails_380) {

    EXPECT_CALL(mockIfd1, write(_, _, 0 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(0));



    TiffSubIfd tiffSubIfd(0, ifdExif, ifdExif);

    size_t result = tiffSubIfd.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffSubIfdTest_380, DoWriteData_WriteMultipleIFDs_380) {

    EXPECT_CALL(mockIfd1, write(_, _, 0 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(5));

    EXPECT_CALL(mockIfd2, write(_, _, 5 + dataIdx, std::string::npos, std::string::npos, _)).WillOnce(Return(3));

    EXPECT_CALL(mockIoWrapper, putb(0x0));



    TiffSubIfd tiffSubIfd(0, ifdExif, ifdExif);

    size_t result = tiffSubIfd.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 9);

}
