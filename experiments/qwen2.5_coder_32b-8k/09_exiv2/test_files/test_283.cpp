#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class IoWrapperTest_283 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    const byte header[10] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };

    size_t header_size = sizeof(header);

    OffsetWriter* mock_offset_writer = nullptr; // Assuming this is a mockable interface

    IoWrapper io_wrapper;



    IoWrapperTest_283() : io_wrapper(mock_io, header, header_size, mock_offset_writer) {}

};



TEST_F(IoWrapperTest_283, PutbWritesHeaderOnce_283) {

    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, putb(_)).Times(1).WillOnce(Return(0));



    io_wrapper.putb(0xFF);

}



TEST_F(IoWrapperTest_283, PutbCallsPutbOnIo_283) {

    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, putb(_)).Times(1).WillOnce(Return(0));



    io_wrapper.putb(0xFF);

}



TEST_F(IoWrapperTest_283, PutbWritesHeaderOnlyFirstTime_283) {

    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, putb(_)).Times(2).WillRepeatedly(Return(0));



    io_wrapper.putb(0xFF);

    io_wrapper.putb(0xFE); // Header should not be written again

}



TEST_F(IoWrapperTest_283, PutbReturnsValueFromIoPutb_283) {

    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, putb(_)).Times(1).WillOnce(Return(1));



    int result = io_wrapper.putb(0xFF);

    EXPECT_EQ(result, 1);

}



TEST_F(IoWrapperTest_283, PutbHandlesIoPutbError_283) {

    EXPECT_CALL(mock_io, write(header, header_size)).Times(1).WillOnce(Return(header_size));

    EXPECT_CALL(mock_io, putb(_)).Times(1).WillOnce(Return(-1));



    int result = io_wrapper.putb(0xFF);

    EXPECT_EQ(result, -1);

}
