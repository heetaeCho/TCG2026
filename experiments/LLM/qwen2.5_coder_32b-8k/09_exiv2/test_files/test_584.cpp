#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest_584 : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_584, TellReturnsZeroInitially_584) {

    EXPECT_EQ(memIo.tell(), 0u);

}



TEST_F(MemIoTest_584, OpenCloseCycle_584) {

    EXPECT_EQ(memIo.open(), 0);

    EXPECT_TRUE(memIo.isopen());

    EXPECT_EQ(memIo.close(), 0);

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_584, WriteIncreasesSize_584) {

    byte data[] = {1, 2, 3};

    size_t wcount = sizeof(data) / sizeof(byte);

    memIo.open();

    EXPECT_EQ(memIo.write(data, wcount), wcount);

    EXPECT_EQ(memIo.size(), wcount);

    memIo.close();

}



TEST_F(MemIoTest_584, PutbIncreasesSizeByOne_584) {

    byte data = 1;

    memIo.open();

    EXPECT_EQ(memIo.putb(data), 0);

    EXPECT_EQ(memIo.size(), 1u);

    memIo.close();

}



TEST_F(MemIoTest_584, SeekSetsPosition_584) {

    memIo.open();

    memIo.write(reinterpret_cast<const byte*>("test"), 4);

    memIo.seek(2, BasicIo::beg);

    EXPECT_EQ(memIo.tell(), 2u);

    memIo.close();

}



TEST_F(MemIoTest_584, ReadReturnsDataCorrectly_584) {

    const byte data[] = {1, 2, 3};

    size_t wcount = sizeof(data) / sizeof(byte);

    memIo.open();

    memIo.write(data, wcount);



    DataBuf readData = memIo.read(wcount);

    EXPECT_EQ(readData.size_, wcount);

    for (size_t i = 0; i < wcount; ++i) {

        EXPECT_EQ(readData.p_[i], data[i]);

    }

    memIo.close();

}



TEST_F(MemIoTest_584, GetbReadsByteCorrectly_584) {

    byte data = 1;

    memIo.open();

    memIo.write(&data, 1);

    memIo.seek(0, BasicIo::beg);



    EXPECT_EQ(memIo.getb(), static_cast<int>(data));

    EXPECT_TRUE(memIo.eof());

    memIo.close();

}



TEST_F(MemIoTest_584, ErrorReturnsZeroInitially_584) {

    EXPECT_EQ(memIo.error(), 0);

}
