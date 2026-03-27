#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include "exiv2/image.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, readData, (char* buf, size_t n), (override));

    MOCK_METHOD(void, writeData, (const char* buf, size_t n), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(bool, good, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

};



class MockHeaderReader : public RiffVideo::HeaderReader {

public:

    MockHeaderReader(const BasicIo::UniquePtr& io) : RiffVideo::HeaderReader(io) {}



    MOCK_CONST_METHOD0(getSize, uint64_t());

    MOCK_CONST_METHOD0(getId, std::string());

};



class RiffVideoTest_79 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    BasicIo::UniquePtr io_ptr{&mock_io};

    MockHeaderReader mock_header{io_ptr};

    RiffVideo video{std::move(io_ptr)};

};



TEST_F(RiffVideoTest_79, ReadList_InfoChunk_NormalOperation_79) {

    EXPECT_CALL(mock_header, getId()).WillOnce(Return("LIST"));

    EXPECT_CALL(mock_header, getSize()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, readData(_, 4)).WillOnce([](char* buf, size_t n) { strncpy(buf, "INFO", n); });



    video.readList(mock_header);

}



TEST_F(RiffVideoTest_79, ReadList_MoviChunk_NormalOperation_79) {

    EXPECT_CALL(mock_header, getId()).WillOnce(Return("LIST"));

    EXPECT_CALL(mock_header, getSize()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, readData(_, 4)).WillOnce([](char* buf, size_t n) { strncpy(buf, "MOVI", n); });



    video.readList(mock_header);

}



TEST_F(RiffVideoTest_79, ReadList_UnknownChunk_NormalOperation_79) {

    EXPECT_CALL(mock_header, getId()).WillOnce(Return("LIST"));

    EXPECT_CALL(mock_header, getSize()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, readData(_, 4)).WillOnce([](char* buf, size_t n) { strncpy(buf, "UNKNOWN", n); });



    video.readList(mock_header);

}



TEST_F(RiffVideoTest_79, ReadList_BoundaryCondition_ZeroSize_79) {

    EXPECT_CALL(mock_header, getId()).WillOnce(Return("LIST"));

    EXPECT_CALL(mock_header, getSize()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, readData(_, 4)).Times(0);



    video.readList(mock_header);

}



TEST_F(RiffVideoTest_79, ReadList_ExceptionalCase_IoNotGood_79) {

    EXPECT_CALL(mock_header, getId()).WillOnce(Return("LIST"));

    EXPECT_CALL(mock_header, getSize()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, readData(_, 4)).WillOnce([](char* buf, size_t n) { strncpy(buf, "INFO", n); });

    EXPECT_CALL(mock_io, good()).WillOnce(Return(false));



    video.readList(mock_header);

}
