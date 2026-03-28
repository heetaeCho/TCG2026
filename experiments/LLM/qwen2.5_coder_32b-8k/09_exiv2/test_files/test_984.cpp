#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "mrwimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

};



class IsMrwTypeTest_984 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsMrwTypeTest_984, ValidMRWHeader_984) {

    const std::array<byte, 4> valid_header = {0x0, 0x4d, 0x52, 0x4d};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(valid_header.begin(), valid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_TRUE(isMrwType(mock_io, true));

}



TEST_F(IsMrwTypeTest_984, InvalidMRWHeader_984) {

    const std::array<byte, 4> invalid_header = {0x1, 0x2, 0x3, 0x4};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(invalid_header.begin(), invalid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_FALSE(isMrwType(mock_io, true));

}



TEST_F(IsMrwTypeTest_984, ReadError_984) {

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(-1));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_FALSE(isMrwType(mock_io, true));

}



TEST_F(IsMrwTypeTest_984, ReadEOF_984) {

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));



    EXPECT_FALSE(isMrwType(mock_io, true));

}



TEST_F(IsMrwTypeTest_984, AdvanceFalse_984) {

    const std::array<byte, 4> valid_header = {0x0, 0x4d, 0x52, 0x4d};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(valid_header.begin(), valid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_TRUE(isMrwType(mock_io, false));

}



TEST_F(IsMrwTypeTest_984, AdvanceFalseInvalidHeader_984) {

    const std::array<byte, 4> invalid_header = {0x1, 0x2, 0x3, 0x4};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(invalid_header.begin(), invalid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_FALSE(isMrwType(mock_io, false));

}



TEST_F(IsMrwTypeTest_984, AdvanceTrueValidHeader_SeekCalled_984) {

    const std::array<byte, 4> valid_header = {0x0, 0x4d, 0x52, 0x4d};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(valid_header.begin(), valid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(-4, BasicIo::cur)).Times(1);



    EXPECT_TRUE(isMrwType(mock_io, true));

}



TEST_F(IsMrwTypeTest_984, AdvanceFalseValidHeader_SeekNotCalled_984) {

    const std::array<byte, 4> valid_header = {0x0, 0x4d, 0x52, 0x4d};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(valid_header.begin(), valid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(-4, BasicIo::cur)).Times(0);



    EXPECT_TRUE(isMrwType(mock_io, false));

}



TEST_F(IsMrwTypeTest_984, AdvanceTrueInvalidHeader_SeekNotCalled_984) {

    const std::array<byte, 4> invalid_header = {0x1, 0x2, 0x3, 0x4};

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(invalid_header.begin(), invalid_header.end()),

        Return(4)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(-4, BasicIo::cur)).Times(0);



    EXPECT_FALSE(isMrwType(mock_io, true));

}
