#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class BmffImageTest : public Test {

protected:

    void SetUp() override {

        io = std::make_unique<StrictMock<MockBasicIo>>();

        bmffImage = std::make_unique<BmffImage>(std::move(io), false, 10);

    }



    std::unique_ptr<MockBasicIo> io;

    std::unique_ptr<BmffImage> bmffImage;

};



TEST_F(BmffImageTest_1198, ParseXmpValidInput_1198) {

    const uint64_t length = 100;

    const uint64_t start = 50;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));

    EXPECT_CALL(*io, tell()).WillOnce(Return(start));

    EXPECT_CALL(*io, seek(start, BasicIo::beg)).Times(2);

    EXPECT_CALL(*io, read(_, length)).WillOnce(Return(length));



    EXPECT_NO_THROW(bmffImage->parseXmp(length, start));

}



TEST_F(BmffImageTest_1198, ParseXmpStartBeyondSize_1198) {

    const uint64_t length = 100;

    const uint64_t start = 300;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));



    EXPECT_THROW(bmffImage->parseXmp(length, start), Error);

}



TEST_F(BmffImageTest_1198, ParseXmpLengthBeyondSize_1198) {

    const uint64_t length = 200;

    const uint64_t start = 50;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));



    EXPECT_THROW(bmffImage->parseXmp(length, start), Error);

}



TEST_F(BmffImageTest_1198, ParseXmpReadError_1198) {

    const uint64_t length = 100;

    const uint64_t start = 50;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));

    EXPECT_CALL(*io, tell()).WillOnce(Return(start));

    EXPECT_CALL(*io, seek(start, BasicIo::beg)).Times(2);

    EXPECT_CALL(*io, read(_, length)).WillOnce(Return(length - 1));



    EXPECT_THROW(bmffImage->parseXmp(length, start), Error);

}



TEST_F(BmffImageTest_1198, ParseXmpDecodeError_1198) {

    const uint64_t length = 100;

    const uint64_t start = 50;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));

    EXPECT_CALL(*io, tell()).WillOnce(Return(start));

    EXPECT_CALL(*io, seek(start, BasicIo::beg)).Times(2);

    EXPECT_CALL(*io, read(_, length)).WillOnce(Return(length));



    EXPECT_CALL(XmpParser::decode, _).WillOnce(Throw(std::runtime_error("Decode error")));



    EXPECT_THROW(bmffImage->parseXmp(length, start), Error);

}



TEST_F(BmffImageTest_1198, ParseXmpIoError_1198) {

    const uint64_t length = 100;

    const uint64_t start = 50;



    EXPECT_CALL(*io, size()).WillRepeatedly(Return(200));

    EXPECT_CALL(*io, tell()).WillOnce(Return(start));

    EXPECT_CALL(*io, seek(start, BasicIo::beg)).Times(2);

    EXPECT_CALL(*io, read(_, length)).WillOnce(Return(length));

    EXPECT_CALL(*io, error()).WillOnce(Return(1));



    EXPECT_THROW(bmffImage->parseXmp(length, start), Error);

}
