#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "./TestProjects/exiv2/src/asfvideo.cpp"



using namespace Exiv2;

using testing::Return;

using testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class AsfTypeTest_1574 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(AsfTypeTest_1574, ValidGUIDRead_1574) {

    byte validGuid[GUID] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(validGuid, validGuid + GUID),

        Return(GUID)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(AsfTypeTest_1574, InvalidGUIDRead_1574) {

    byte invalidGuid[GUID] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(invalidGuid, invalidGuid + GUID),

        Return(GUID)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(AsfTypeTest_1574, ReadError_1574) {

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(Return(0));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(1));  // Simulate an error condition

    EXPECT_CALL(mockIo, eof()).Times(0);

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(AsfTypeTest_1574, ReadEOF_1574) {

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(Return(0));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));  // No error

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true));  // Simulate EOF condition

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(AsfTypeTest_1574, AdvanceFalseMatched_1574) {

    byte validGuid[GUID] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(validGuid, validGuid + GUID),

        Return(GUID)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(AsfTypeTest_1574, AdvanceFalseNotMatched_1574) {

    byte invalidGuid[GUID] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, GUID)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(invalidGuid, invalidGuid + GUID),

        Return(GUID)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isAsfType(mockIo, false);

    EXPECT_FALSE(result);

}
