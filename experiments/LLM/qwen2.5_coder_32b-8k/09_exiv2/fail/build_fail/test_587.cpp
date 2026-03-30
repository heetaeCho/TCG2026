#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_587, IsOpenReturnsTrueInitially_587) {

    EXPECT_TRUE(memIo.isopen());

}



TEST_F(MemIoTest_587, OpenMethodReturnsSuccess_587) {

    EXPECT_EQ(0, memIo.open());

}



TEST_F(MemIoTest_587, CloseMethodReturnsSuccess_587) {

    EXPECT_EQ(0, memIo.close());

}



TEST_F(MemIoTest_587, WriteWithNullDataPointer_ReturnsZero_587) {

    const byte* data = nullptr;

    size_t wcount = 10;

    EXPECT_EQ(0U, memIo.write(data, wcount));

}



TEST_F(MemIoTest_587, WriteWithZeroCount_ReturnsZero_587) {

    const byte* data = reinterpret_cast<const byte*>("test");

    size_t wcount = 0;

    EXPECT_EQ(0U, memIo.write(data, wcount));

}



TEST_F(MemIoTest_587, ReadWithNullBufferPointer_ReturnsEmptyDataBuf_587) {

    size_t rcount = 10;

    DataBuf dataBuf = memIo.read(rcount);

    EXPECT_EQ(0U, dataBuf.size_);

}



TEST_F(MemIoTest_587, ReadWithZeroCount_ReturnsEmptyDataBuf_587) {

    byte buffer[10];

    size_t rcount = 0;

    EXPECT_EQ(0U, memIo.read(buffer, rcount));

}



TEST_F(MemIoTest_587, PutbMethodReturnsSuccess_587) {

    byte data = 'A';

    EXPECT_EQ(0, memIo.putb(data));

}



TEST_F(MemIoTest_587, GetbMethodReturnsEOFInitially_587) {

    EXPECT_EQ(-1, memIo.getb());

}



TEST_F(MemIoTest_587, SeekWithInvalidOffset_ReturnsError_587) {

    int64_t offset = -1;

    Position pos = BasicIo::beg;

    EXPECT_NE(0, memIo.seek(offset, pos));

}



TEST_F(MemIoTest_587, TellReturnsZeroInitially_587) {

    EXPECT_EQ(0U, memIo.tell());

}



TEST_F(MemIoTest_587, SizeReturnsZeroInitially_587) {

    EXPECT_EQ(0U, memIo.size());

}



TEST_F(MemIoTest_587, ErrorMethodReturnsNoErrorInitially_587) {

    EXPECT_EQ(0, memIo.error());

}



TEST_F(MemIoTest_587, EofMethodReturnsTrueInitially_587) {

    EXPECT_TRUE(memIo.eof());

}



TEST_F(MemIoTest_587, PathMethodReturnsEmptyStringInitially_587) {

    EXPECT_EQ("", memIo.path());

}
