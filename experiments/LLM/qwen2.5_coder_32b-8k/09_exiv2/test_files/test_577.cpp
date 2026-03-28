#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest_577 : public ::testing::Test {

protected:

    void SetUp() override {

        memIo = std::make_unique<MemIo>();

    }



    std::unique_ptr<MemIo> memIo;

};



TEST_F(MemIoTest_577, WriteReturnsCountWhenDataIsNotNull_577) {

    const byte data[] = {1, 2, 3};

    size_t count = sizeof(data) / sizeof(byte);

    EXPECT_EQ(memIo->write(data, count), count);

}



TEST_F(MemIoTest_577, WriteReturnsZeroWhenDataIsNull_577) {

    size_t count = 10;

    EXPECT_EQ(memIo->write(nullptr, count), count);

}



TEST_F(MemIoTest_577, WriteHandlesLargeData_577) {

    const byte data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t count = sizeof(data) / sizeof(byte);

    EXPECT_EQ(memIo->write(data, count), count);

}



TEST_F(MemIoTest_577, WriteHandlesZeroCount_577) {

    const byte data[] = {1, 2, 3};

    size_t count = 0;

    EXPECT_EQ(memIo->write(data, count), count);

}
