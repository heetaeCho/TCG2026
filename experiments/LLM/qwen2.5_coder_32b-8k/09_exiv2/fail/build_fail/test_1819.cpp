#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "./TestProjects/exiv2/src/crwimage_int.hpp"

#include "./TestProjects/exiv2/src/crwimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class IsCrwTypeTest : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(IsCrwTypeTest, ValidCrwFile_AdvanceTrue_1819) {

    byte testData[14] = {'I', 'I', 0, 0, 0, 0, 'C', 'R', 'W', 'H', 'E', 'A', 'D', 'E'};

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(testData, testData + 14),

        Return(14)

    ));

    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    bool result = isCrwType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(IsCrwTypeTest, ValidCrwFile_AdvanceFalse_1819) {

    byte testData[14] = {'I', 'M', 0, 0, 0, 0, 'C', 'R', 'W', 'H', 'E', 'A', 'D', 'E'};

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(testData, testData + 14),

        Return(14)

    ));

    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    bool result = isCrwType(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(IsCrwTypeTest, InvalidStartBytes_AdvanceTrue_1819) {

    byte testData[14] = {'X', 'X', 0, 0, 0, 0, 'C', 'R', 'W', 'H', 'E', 'A', 'D', 'E'};

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(testData, testData + 14),

        Return(14)

    ));

    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    bool result = isCrwType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCrwTypeTest, InvalidSignature_AdvanceTrue_1819) {

    byte testData[14] = {'I', 'I', 0, 0, 0, 0, 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(testData, testData + 14),

        Return(14)

    ));

    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).Times(1);

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    bool result = isCrwType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCrwTypeTest, ReadError_AdvanceTrue_1819) {

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(Return(0));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(-1));



    bool result = isCrwType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCrwTypeTest, EndOfFile_AdvanceTrue_1819) {

    EXPECT_CALL(mockIo, read(_, 14)).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));



    bool result = isCrwType(mockIo, true);

    EXPECT_FALSE(result);

}
