#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "TestProjects/exiv2/src/cr2image.cpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

};



class IsCr2TypeTest_1748 : public testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsCr2TypeTest_1748, NormalOperation_HeaderValid_SeeksBackAndReturnsTrue_1748) {

    byte validHeader[16] = { /* some valid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(validHeader, validHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(-16, BasicIo::cur)).WillOnce(Return(0));



    bool result = Exiv2::isCr2Type(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsCr2TypeTest_1748, NormalOperation_HeaderInvalid_SeeksBackAndReturnsFalse_1748) {

    byte invalidHeader[16] = { /* some invalid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(invalidHeader, invalidHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(-16, BasicIo::cur)).WillOnce(Return(0));



    bool result = Exiv2::isCr2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCr2TypeTest_1748, BoundaryCondition_ReadLessThan16Bytes_SeeksBackAndReturnsFalse_1748) {

    byte partialHeader[10] = { /* some partial CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(partialHeader, partialHeader + 10), Return(10)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(-16, BasicIo::cur)).WillOnce(Return(0));



    bool result = Exiv2::isCr2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCr2TypeTest_1748, ErrorCase_IoError_SeeksBackAndReturnsFalse_1748) {

    byte validHeader[16] = { /* some valid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(validHeader, validHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(1));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(-16, BasicIo::cur)).WillOnce(Return(0));



    bool result = Exiv2::isCr2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCr2TypeTest_1748, ErrorCase_EndOfFile_SeeksBackAndReturnsFalse_1748) {

    byte validHeader[16] = { /* some valid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(validHeader, validHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, seek(-16, BasicIo::cur)).WillOnce(Return(0));



    bool result = Exiv2::isCr2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsCr2TypeTest_1748, AdvanceFalse_HeaderValid_DoesNotSeekBackAndReturnsTrue_1748) {

    byte validHeader[16] = { /* some valid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(validHeader, validHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(_, _)).Times(0);



    bool result = Exiv2::isCr2Type(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(IsCr2TypeTest_1748, AdvanceFalse_HeaderInvalid_DoesNotSeekBackAndReturnsFalse_1748) {

    byte invalidHeader[16] = { /* some invalid CR2 header bytes */ };

    EXPECT_CALL(mock_io, read(_, 16)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(invalidHeader, invalidHeader + 16), Return(16)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, seek(_, _)).Times(0);



    bool result = Exiv2::isCr2Type(mock_io, false);

    EXPECT_FALSE(result);

}
