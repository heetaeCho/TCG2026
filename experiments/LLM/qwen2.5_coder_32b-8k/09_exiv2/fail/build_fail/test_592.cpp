#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_592, OpenReturnsSuccess_592) {

    EXPECT_EQ(memIo.open(), 0);

}



TEST_F(MemIoTest_592, CloseReturnsSuccess_592) {

    memIo.open();

    EXPECT_EQ(memIo.close(), 0);

}



TEST_F(MemIoTest_592, IsOpenInitiallyFalse_592) {

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_592, IsOpenTrueAfterOpen_592) {

    memIo.open();

    EXPECT_TRUE(memIo.isopen());

}



TEST_F(MemIoTest_592, IsOpenFalseAfterClose_592) {

    memIo.open();

    memIo.close();

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_592, ErrorInitiallyZero_592) {

    EXPECT_EQ(memIo.error(), 0);

}



TEST_F(MemIoTest_592, TellReturnsZeroInitially_592) {

    EXPECT_EQ(memIo.tell(), 0u);

}



TEST_F(MemIoTest_592, SizeReturnsZeroInitially_592) {

    EXPECT_EQ(memIo.size(), 0u);

}



TEST_F(MemIoTest_592, EofReturnsTrueInitially_592) {

    EXPECT_TRUE(memIo.eof());

}



TEST_F(MemIoTest_592, SeekWithoutOpenFails_592) {

    EXPECT_NE(memIo.seek(0, BasicIo::beg), 0);

}



TEST_F(MemIoTest_592, WriteWithoutOpenFails_592) {

    const byte data[] = {1};

    EXPECT_EQ(memIo.write(data, sizeof(data)), 0u);

}



TEST_F(MemIoTest_592, ReadWithoutOpenFails_592) {

    byte buffer[1];

    EXPECT_EQ(memIo.read(buffer, sizeof(buffer)), 0u);

}



TEST_F(MemIoTest_592, PutbWithoutOpenFails_592) {

    EXPECT_NE(memIo.putb(1), 0);

}



TEST_F(MemIoTest_592, GetbWithoutOpenFails_592) {

    EXPECT_EQ(memIo.getb(), -1);

}
