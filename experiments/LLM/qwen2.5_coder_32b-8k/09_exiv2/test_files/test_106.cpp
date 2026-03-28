#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "matroskavideo.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(bool, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class IsMkvTypeTest_106 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsMkvTypeTest_106, ValidMkvHeader_AdvanceTrue_ReturnsTrue_106) {

    byte valid_header[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(valid_header, valid_header + 4), Return(4)));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(0);



    bool result = isMkvType(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsMkvTypeTest_106, ValidMkvHeader_AdvanceFalse_ReturnsTrue_SeeksToStart_106) {

    byte valid_header[] = {0x1a, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(valid_header, valid_header + 4), Return(4)));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(1);



    bool result = isMkvType(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(IsMkvTypeTest_106, InvalidMkvHeader_ReturnsFalse_SeeksToStart_106) {

    byte invalid_header[] = {0x00, 0x45, 0xdf, 0xa3};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(invalid_header, invalid_header + 4), Return(4)));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(1);



    bool result = isMkvType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsMkvTypeTest_106, ReadError_ReturnsFalse_SeeksToStart_106) {

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(1);



    bool result = isMkvType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsMkvTypeTest_106, EndOfFile_ReturnsFalse_SeeksToStart_106) {

    byte partial_header[] = {0x1a};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(partial_header, partial_header + 1), Return(1)));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(1);



    bool result = isMkvType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsMkvTypeTest_106, ReadLessThanFourBytes_ReturnsFalse_SeeksToStart_106) {

    byte partial_header[] = {0x1a, 0x45};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(partial_header, partial_header + 2), Return(2)));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg)).Times(1);



    bool result = isMkvType(mock_io, true);

    EXPECT_FALSE(result);

}
