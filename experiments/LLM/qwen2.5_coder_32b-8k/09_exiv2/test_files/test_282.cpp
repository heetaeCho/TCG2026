#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD((size_t), write, (const byte* data, size_t wcount), (override));

};



class IoWrapperTest_282 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    const byte header[] = {0x49, 0x49, 0x2A, 0x00}; // Example TIFF header

    size_t header_size = sizeof(header);

    OffsetWriter* mock_offset_writer = nullptr; // Assuming OffsetWriter is a mockable class or interface



    IoWrapper io_wrapper;



    IoWrapperTest_282() : io_wrapper(mock_io, header, header_size, mock_offset_writer) {}

};



TEST_F(IoWrapperTest_282, WriteHeaderOnceOnFirstWrite_282) {

    const byte data[] = {0x12, 0x34};

    size_t wcount = sizeof(data);



    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, write(data, wcount)).Times(1).WillOnce(Return(wcount));



    io_wrapper.write(data, wcount);

}



TEST_F(IoWrapperTest_282, WriteHeaderNotOnSubsequentWrites_282) {

    const byte data[] = {0x12, 0x34};

    size_t wcount = sizeof(data);



    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, write(data, wcount)).Times(2).WillRepeatedly(Return(wcount));



    io_wrapper.write(data, wcount);

    io_wrapper.write(data, wcount);

}



TEST_F(IoWrapperTest_282, WriteZeroBytesDoesNotWriteHeader_282) {

    const byte data[] = {0x12, 0x34};

    size_t zero_wcount = 0;



    EXPECT_CALL(mock_io, write(header, header_size)).Times(0);

    EXPECT_CALL(mock_io, write(data, zero_wcount)).Times(1).WillOnce(Return(zero_wcount));



    io_wrapper.write(data, zero_wcount);

}



TEST_F(IoWrapperTest_282, WriteReturnsCorrectByteCount_282) {

    const byte data[] = {0x12, 0x34};

    size_t wcount = sizeof(data);



    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, write(data, wcount)).Times(1).WillOnce(Return(wcount));



    size_t result = io_wrapper.write(data, wcount);

    EXPECT_EQ(result, wcount);

}



TEST_F(IoWrapperTest_282, WriteHeaderFailsPropagatesError_282) {

    const byte data[] = {0x12, 0x34};

    size_t wcount = sizeof(data);



    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(data, wcount)).Times(0);



    size_t result = io_wrapper.write(data, wcount);

    EXPECT_EQ(result, 0);

}



TEST_F(IoWrapperTest_282, WriteDataFailsPropagatesErrorAfterHeaderWritten_282) {

    const byte data[] = {0x12, 0x34};

    size_t wcount = sizeof(data);



    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, write(data, wcount)).Times(1).WillOnce(Return(0));



    size_t result = io_wrapper.write(data, wcount);

    EXPECT_EQ(result, 0);

}
