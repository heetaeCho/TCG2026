#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

    MockBasicIo mockSrc;

};



TEST_F(MemIoTest_578, TransferFromMemIo_Success_578) {

    MemIo srcMemIo(reinterpret_cast<const byte*>("test"), 4);

    memIo.transfer(srcMemIo);



    EXPECT_EQ(memIo.size(), 4u);

}



TEST_F(MemIoTest_578, TransferFromNonMemIo_OpenSuccess_WriteSuccess_CloseSuccess_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(4u));

    EXPECT_CALL(mockSrc, close()).WillOnce(::testing::Return(0));



    memIo.transfer(mockSrc);

}



TEST_F(MemIoTest_578, TransferFromNonMemIo_OpenFail_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(memIo.transfer(mockSrc), Error);

}



TEST_F(MemIoTest_578, TransferFromNonMemIo_WriteFail_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(0u));



    EXPECT_THROW(memIo.transfer(mockSrc), Error);

}



TEST_F(MemIoTest_578, TransferFromNonMemIo_CloseFail_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(4u));

    EXPECT_CALL(mockSrc, close()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(memIo.transfer(mockSrc), Error);

}



TEST_F(MemIoTest_578, TransferWithErrorInSource_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Invoke([](BasicIo&) { throw Error(ErrorCode::kerGeneralError); }));



    EXPECT_THROW(memIo.transfer(mockSrc), Error);

}



TEST_F(MemIoTest_578, TransferWithErrorInDestination_578) {

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Invoke([&](BasicIo&) { memIo.p_->isMalloced_ = true; memIo.p_->data_ = nullptr; return 4u; }));



    EXPECT_THROW(memIo.transfer(mockSrc), Error);

}
