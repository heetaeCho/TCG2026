#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "TestProjects/exiv2/src/rw2image_int.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

};



class IsRw2TypeTest_1583 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(IsRw2TypeTest_1583, ValidRw2Header_1583) {

    const int32_t len = 24;

    byte buf[len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                     0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x18, 0x00,

                     0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(len)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));



    bool result = isRw2Type(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(IsRw2TypeTest_1583, InvalidRw2Header_1583) {

    const int32_t len = 24;

    byte buf[len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                     0x00, 0x00, 0x00, 0x00, 0x55, 0x01, 0x18, 0x00,

                     0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(len)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));



    bool result = isRw2Type(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsRw2TypeTest_1583, IoErrorDuringRead_1583) {

    const int32_t len = 24;

    byte buf[len] = {0};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(0)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));



    bool result = isRw2Type(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsRw2TypeTest_1583, EofDuringRead_1583) {

    const int32_t len = 24;

    byte buf[len] = {0};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(0)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));



    bool result = isRw2Type(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsRw2TypeTest_1583, AdvanceFalseAndValidHeader_1583) {

    const int32_t len = 24;

    byte buf[len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                     0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x18, 0x00,

                     0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(len)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));



    bool result = isRw2Type(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(IsRw2TypeTest_1583, AdvanceFalseAndInvalidHeader_1583) {

    const int32_t len = 24;

    byte buf[len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                     0x00, 0x00, 0x00, 0x00, 0x55, 0x01, 0x18, 0x00,

                     0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(buf, buf + len),

        ::testing::Return(len)

    ));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));



    bool result = isRw2Type(mockIo, false);

    EXPECT_FALSE(result);

}
