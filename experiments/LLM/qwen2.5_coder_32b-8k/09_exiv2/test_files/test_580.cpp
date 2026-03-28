#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest_580 : public ::testing::Test {

protected:

    void SetUp() override {

        memIo = std::make_unique<MemIo>();

    }



    void TearDown() override {

        memIo.reset();

    }



    std::unique_ptr<MemIo> memIo;

};



TEST_F(MemIoTest_580, PutbWritesData_580) {

    byte data = 42;

    int result = memIo->putb(data);

    EXPECT_EQ(result, static_cast<int>(data));

}



TEST_F(MemIoTest_580, PutbReturnsWrittenByte_580) {

    byte data = 'A';

    int result = memIo->putb(data);

    EXPECT_EQ(result, static_cast<int>('A'));

}



TEST_F(MemIoTest_580, PutbMultipleBytes_580) {

    byte data1 = 65;

    byte data2 = 66;

    memIo->putb(data1);

    int result = memIo->putb(data2);

    EXPECT_EQ(result, static_cast<int>(data2));

}



TEST_F(MemIoTest_580, PutbBoundaryCondition_580) {

    byte maxByte = std::numeric_limits<byte>::max();

    int result = memIo->putb(maxByte);

    EXPECT_EQ(result, static_cast<int>(maxByte));

}
