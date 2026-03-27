#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest_594 : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_594, PathReturnsMemIoString_594) {

    EXPECT_EQ(memIo.path(), "MemIo");

}



TEST_F(MemIoTest_594, OpenAndCloseOperations_594) {

    EXPECT_EQ(memIo.open(), 0);

    EXPECT_TRUE(memIo.isopen());

    EXPECT_EQ(memIo.close(), 0);

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_594, SeekBoundaryConditions_594) {

    memIo.open();

    EXPECT_EQ(memIo.seek(0, BasicIo::beg), 0);

    EXPECT_EQ(memIo.tell(), 0);

    EXPECT_EQ(memIo.seek(10, BasicIo::cur), 10);

    EXPECT_EQ(memIo.tell(), 10);

    EXPECT_EQ(memIo.seek(-5, BasicIo::cur), 5);

    EXPECT_EQ(memIo.tell(), 5);

    memIo.close();

}



TEST_F(MemIoTest_594, ReadBoundaryConditions_594) {

    memIo.open();

    byte buffer[10];

    EXPECT_EQ(memIo.read(buffer, 10), 0); // No data written yet

    memIo.close();

}



TEST_F(MemIoTest_594, WriteAndReadOperations_594) {

    memIo.open();

    const byte data[] = {1, 2, 3, 4, 5};

    EXPECT_EQ(memIo.write(data, 5), 5);

    EXPECT_EQ(memIo.size(), 5);



    byte readBuffer[5];

    EXPECT_EQ(memIo.seek(0, BasicIo::beg), 0);

    EXPECT_EQ(memIo.read(readBuffer, 5), 5);

    for (size_t i = 0; i < 5; ++i) {

        EXPECT_EQ(data[i], readBuffer[i]);

    }

    memIo.close();

}



TEST_F(MemIoTest_594, PutbAndGetbOperations_594) {

    memIo.open();

    EXPECT_EQ(memIo.putb(1), 0);

    EXPECT_EQ(memIo.tell(), 1);



    EXPECT_EQ(memIo.seek(0, BasicIo::beg), 0);

    EXPECT_EQ(memIo.getb(), 1);

    memIo.close();

}



TEST_F(MemIoTest_594, ErrorAndEofOperations_594) {

    memIo.open();

    EXPECT_EQ(memIo.error(), 0);

    EXPECT_FALSE(memIo.eof());

    memIo.close();

}
