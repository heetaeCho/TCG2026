#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "bmpimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class IsBmpTypeTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsBmpTypeTest, ValidBmpHeader_1042) {

    std::array<byte, 2> bmp_header{'B', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(bmp_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    bool result = isBmpType(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsBmpTypeTest, InvalidBmpHeader_1042) {

    std::array<byte, 2> invalid_header{'A', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(invalid_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    bool result = isBmpType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmpTypeTest, ErrorDuringRead_1042) {

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(1));



    bool result = isBmpType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmpTypeTest, EofDuringRead_1042) {

    std::array<byte, 2> bmp_header{'B', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(bmp_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));



    bool result = isBmpType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmpTypeTest, AdvanceFalse_ValidHeader_1042) {

    std::array<byte, 2> bmp_header{'B', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(bmp_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    bool result = isBmpType(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(IsBmpTypeTest, AdvanceFalse_SeekCalled_1042) {

    std::array<byte, 2> bmp_header{'B', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(bmp_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(-2, BasicIo::cur)).Times(1);



    bool result = isBmpType(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(IsBmpTypeTest, AdvanceTrue_SeekNotCalled_1042) {

    std::array<byte, 2> bmp_header{'B', 'M'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(bmp_header.data(), 2),

        Return(2)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(_, _)).Times(0);



    bool result = isBmpType(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsBmpTypeTest, ReadPartialHeader_1042) {

    std::array<byte, 2> partial_header{'B'};

    EXPECT_CALL(mock_io, read(_, 2)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(partial_header.data(), 1),

        Return(1)

    ));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));



    bool result = isBmpType(mock_io, true);

    EXPECT_FALSE(result);

}
