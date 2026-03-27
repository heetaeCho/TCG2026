#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



namespace {



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest, OpenClose_576) {

    EXPECT_EQ(memIo.open(), 0);

    EXPECT_TRUE(memIo.isopen());

    EXPECT_EQ(memIo.close(), 0);

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest, WriteData_576) {

    memIo.open();

    const byte data[] = {1, 2, 3};

    size_t bytesWritten = memIo.write(data, sizeof(data));

    EXPECT_EQ(bytesWritten, sizeof(data));

    memIo.close();

}



TEST_F(MemIoTest, ReadData_576) {

    memIo.open();

    const byte writeData[] = {1, 2, 3};

    memIo.write(writeData, sizeof(writeData));



    byte readBuffer[3];

    size_t bytesRead = memIo.read(readBuffer, sizeof(readBuffer));

    EXPECT_EQ(bytesRead, sizeof(readBuffer));

    for (size_t i = 0; i < sizeof(writeData); ++i) {

        EXPECT_EQ(readBuffer[i], writeData[i]);

    }

    memIo.close();

}



TEST_F(MemIoTest, SeekPosition_576) {

    memIo.open();

    const byte data[] = {1, 2, 3};

    memIo.write(data, sizeof(data));



    int rc = memIo.seek(1, BasicIo::beg);

    EXPECT_EQ(rc, 0);

    EXPECT_EQ(memIo.tell(), 1);



    rc = memIo.seek(-1, BasicIo::cur);

    EXPECT_EQ(rc, 0);

    EXPECT_EQ(memIo.tell(), 0);



    rc = memIo.seek(2, BasicIo::end);

    EXPECT_EQ(rc, 0);

    EXPECT_EQ(memIo.tell(), sizeof(data) + 2);

    memIo.close();

}



TEST_F(MemIoTest, PutbGetb_576) {

    memIo.open();

    byte data = 42;

    int rc = memIo.putb(data);

    EXPECT_EQ(rc, 0);



    rc = memIo.seek(0, BasicIo::beg);

    EXPECT_EQ(rc, 0);



    int readData = memIo.getb();

    EXPECT_EQ(readData, static_cast<int>(data));

    memIo.close();

}



TEST_F(MemIoTest, ErrorHandling_576) {

    EXPECT_NE(memIo.read(nullptr, 1), 1);

    EXPECT_NE(memIo.write(nullptr, 1), 1);

    EXPECT_NE(memIo.seek(0, BasicIo::beg), 0);

    memIo.open();

    EXPECT_EQ(memIo.open(), 1); // already open

    memIo.close();

    EXPECT_EQ(memIo.close(), 1); // already closed

}



TEST_F(MemIoTest, MmapMunmap_576) {

    memIo.open();

    byte* mappedData = memIo.mmap(false);

    EXPECT_NE(mappedData, nullptr);

    int rc = memIo.munmap();

    EXPECT_EQ(rc, 0);

    memIo.close();

}



TEST_F(MemIoTest, ConstructorWithData_576) {

    const byte data[] = {1, 2, 3};

    MemIo memIoWithInitData(data, sizeof(data));

    memIoWithInitData.open();



    byte readBuffer[3];

    size_t bytesRead = memIoWithInitData.read(readBuffer, sizeof(readBuffer));

    EXPECT_EQ(bytesRead, sizeof(readBuffer));

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(readBuffer[i], data[i]);

    }

    memIoWithInitData.close();

}



} // namespace
