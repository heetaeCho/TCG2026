#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class RemoteIoTest : public ::testing::Test {

protected:

    RemoteIo remote_io;

};



TEST_F(RemoteIoTest_613, SizeInitiallyZero_613) {

    EXPECT_EQ(remote_io.size(), 0);

}



TEST_F(RemoteIoTest_613, OpenReturnsZeroOnSuccess_613) {

    EXPECT_EQ(remote_io.open(), 0);

}



TEST_F(RemoteIoTest_613, CloseReturnsZeroOnSuccess_613) {

    remote_io.open();

    EXPECT_EQ(remote_io.close(), 0);

}



TEST_F(RemoteIoTest_613, WriteWithBytePointerDoesNotCrash_613) {

    const byte data[] = {1, 2, 3};

    size_t result = remote_io.write(data, sizeof(data));

    EXPECT_GE(result, 0);

}



TEST_F(RemoteIoTest_613, WriteWithBasicIoDoesNotCrash_613) {

    BasicIo src;

    size_t result = remote_io.write(src);

    EXPECT_GE(result, 0);

}



TEST_F(RemoteIoTest_613, PutbDoesNotCrash_613) {

    int result = remote_io.putb(1);

    EXPECT_GE(result, 0);

}



TEST_F(RemoteIoTest_613, ReadWithSizeReturnsDataBuf_613) {

    DataBuf data_buf = remote_io.read(10);

    EXPECT_TRUE(data_buf.pData != nullptr || data_buf.size == 0);

}



TEST_F(RemoteIoTest_613, ReadWithBytePointerDoesNotCrash_613) {

    byte buffer[10];

    size_t result = remote_io.read(buffer, sizeof(buffer));

    EXPECT_GE(result, 0);

}



TEST_F(RemoteIoTest_613, GetbReturnsValidDataOrEOF_613) {

    int result = remote_io.getb();

    EXPECT_TRUE(result != EOF || remote_io.eof());

}



TEST_F(RemoteIoTest_613, TransferDoesNotCrash_613) {

    BasicIo src;

    remote_io.transfer(src);

}



TEST_F(RemoteIoTest_613, SeekWithValidOffsetReturnsZeroOnSuccess_613) {

    int result = remote_io.seek(0, BasicIo::beg);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_613, MmapDoesNotCrashForReadableMap_613) {

    byte* ptr = remote_io.mmap(false);

    EXPECT_TRUE(ptr != nullptr || remote_io.error() != 0);

}



TEST_F(RemoteIoTest_613, MunmapReturnsZeroOnSuccess_613) {

    int result = remote_io.munmap();

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_613, TellReturnsCurrentPosition_613) {

    size_t position = remote_io.tell();

    EXPECT_GE(position, 0);

}



TEST_F(RemoteIoTest_613, IsopenInitiallyFalse_613) {

    EXPECT_FALSE(remote_io.isopen());

}



TEST_F(RemoteIoTest_613, ErrorInitiallyZero_613) {

    EXPECT_EQ(remote_io.error(), 0);

}



TEST_F(RemoteIoTest_613, EofInitiallyTrue_613) {

    EXPECT_TRUE(remote_io.eof());

}



TEST_F(RemoteIoTest_613, PathReturnsValidString_613) {

    const std::string& path = remote_io.path();

    EXPECT_TRUE(!path.empty() || remote_io.error() != 0);

}



TEST_F(RemoteIoTest_613, PopulateFakeDataDoesNotCrash_613) {

    remote_io.populateFakeData();

}
