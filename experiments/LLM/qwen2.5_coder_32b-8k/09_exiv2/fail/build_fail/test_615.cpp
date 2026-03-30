#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



namespace Exiv2 {

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

        MOCK_METHOD(byte*, mmap, (bool unnamed), (override));

        MOCK_METHOD(int, munmap, (), (override));

        MOCK_METHOD(size_t, tell, (), (const, override));

        MOCK_METHOD(size_t, size, (), (const, override));

        MOCK_METHOD(bool, isopen, (), (const, override));

        MOCK_METHOD(int, error, (), (const, override));

        MOCK_METHOD(bool, eof, (), (const, override));

        MOCK_METHOD(const std::string &, path, (), (const, noexcept, override));

    };

}



using namespace Exiv2;



class RemoteIoTest_615 : public ::testing::Test {

protected:

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest_615, OpenReturnsZeroForSuccess_615) {

    EXPECT_EQ(remoteIo.open(), 0);

}



TEST_F(RemoteIoTest_615, CloseReturnsZeroForSuccess_615) {

    EXPECT_EQ(remoteIo.close(), 0);

}



TEST_F(RemoteIoTest_615, WriteWithBufferReturnsZero_615) {

    byte data[4] = {0x01, 0x02, 0x03, 0x04};

    EXPECT_EQ(remoteIo.write(data, sizeof(data)), 0);

}



TEST_F(RemoteIoTest_615, WriteWithSrcReturnsZero_615) {

    MockBasicIo mockSrc;

    EXPECT_CALL(mockSrc, size()).WillOnce(testing::Return(4));

    EXPECT_CALL(mockSrc, read(testing::_, testing::_)).WillOnce(testing::Return(4));

    EXPECT_EQ(remoteIo.write(mockSrc), 0);

}



TEST_F(RemoteIoTest_615, PutbReturnsZero_615) {

    EXPECT_EQ(remoteIo.putb(static_cast<byte>(0x01)), 0);

}



TEST_F(RemoteIoTest_615, ReadWithRcountReturnsEmptyDataBuf_615) {

    DataBuf data = remoteIo.read(4);

    EXPECT_EQ(data.pData_, nullptr);

    EXPECT_EQ(data.size_, 0);

}



TEST_F(RemoteIoTest_615, ReadWithBufferAndRcountReturnsZeroBytesRead_615) {

    byte buffer[4];

    EXPECT_EQ(remoteIo.read(buffer, sizeof(buffer)), 0);

}



TEST_F(RemoteIoTest_615, GetbReturnsZero_615) {

    EXPECT_EQ(remoteIo.getb(), 0);

}



TEST_F(RemoteIoTest_615, TransferDoesNotThrow_615) {

    MockBasicIo mockSrc;

    EXPECT_NO_THROW(remoteIo.transfer(mockSrc));

}



TEST_F(RemoteIoTest_615, SeekReturnsZeroForSuccess_615) {

    EXPECT_EQ(remoteIo.seek(0, BasicIo::beg), 0);

}



TEST_F(RemoteIoTest_615, MmapReturnsNullptr_615) {

    EXPECT_EQ(remoteIo.mmap(true), nullptr);

}



TEST_F(RemoteIoTest_615, MunmapReturnsZeroForSuccess_615) {

    EXPECT_EQ(remoteIo.munmap(), 0);

}



TEST_F(RemoteIoTest_615, TellReturnsZero_615) {

    EXPECT_EQ(remoteIo.tell(), 0);

}



TEST_F(RemoteIoTest_615, SizeReturnsZero_615) {

    EXPECT_EQ(remoteIo.size(), 0);

}



TEST_F(RemoteIoTest_615, IsopenReturnsFalse_615) {

    EXPECT_FALSE(remoteIo.isopen());

}



TEST_F(RemoteIoTest_615, ErrorReturnsZero_615) {

    EXPECT_EQ(remoteIo.error(), 0);

}



TEST_F(RemoteIoTest_615, EofReturnsTrueInitially_615) {

    EXPECT_TRUE(remoteIo.eof());

}



TEST_F(RemoteIoTest_615, PathReturnsEmptyString_615) {

    EXPECT_EQ(remoteIo.path(), "");

}
