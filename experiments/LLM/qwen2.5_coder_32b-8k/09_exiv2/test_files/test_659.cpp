#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

};



TEST(readStringTest_659, NormalOperation_659) {

    MockBasicIo mock_io;

    std::string expected = "test";

    EXPECT_CALL(mock_io, size()).WillOnce(Return(10));

    EXPECT_CALL(mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce([](byte* buf, size_t) {

        memcpy(buf, "test", 4);

        return 4;

    });



    std::string result = Exiv2::readString(mock_io, 4);

    EXPECT_EQ(result, expected);

}



TEST(readStringTest_659, BoundaryCondition_SizeZero_659) {

    MockBasicIo mock_io;

    std::string expected = "";



    EXPECT_CALL(mock_io, size()).WillOnce(Return(10));

    EXPECT_CALL(mock_io, tell()).WillOnce(Return(0));



    std::string result = Exiv2::readString(mock_io, 0);

    EXPECT_EQ(result, expected);

}



TEST(readStringTest_659, BoundaryCondition_EndOfFile_659) {

    MockBasicIo mock_io;

    std::string expected = "";



    EXPECT_CALL(mock_io, size()).WillOnce(Return(10));

    EXPECT_CALL(mock_io, tell()).WillOnce(Return(10));



    std::string result = Exiv2::readString(mock_io, 4);

    EXPECT_EQ(result, expected);

}



TEST(readStringTest_659, Exceptional_CorruptedMetadata_659) {

    MockBasicIo mock_io;



    EXPECT_CALL(mock_io, size()).WillOnce(Return(10));

    EXPECT_CALL(mock_io, tell()).WillOnce(Return(8));



    EXPECT_THROW(Exiv2::readString(mock_io, 4), Error);

}



TEST(readStringTest_659, Exceptional_ReadError_659) {

    MockBasicIo mock_io;



    EXPECT_CALL(mock_io, size()).WillOnce(Return(10));

    EXPECT_CALL(mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(Return(3));



    EXPECT_THROW(Exiv2::readString(mock_io, 4), Error);

}
