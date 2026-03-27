#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_Read_ZeroBytes_589) {

    DataBuf result = memIo.read(0);

    EXPECT_EQ(result.size(), 0u);

}



TEST_F(MemIoTest_Read_NormalOperation_589) {

    const byte testData[] = {1, 2, 3, 4, 5};

    MemIo testMemIo(testData, sizeof(testData));

    DataBuf result = testMemIo.read(sizeof(testData));

    EXPECT_EQ(result.size(), sizeof(testData));

    for (size_t i = 0; i < sizeof(testData); ++i) {

        EXPECT_EQ(result.c_data()[i], testData[i]);

    }

}



TEST_F(MemIoTest_Read_BoundaryCondition_589) {

    const byte testData[] = {1, 2, 3, 4, 5};

    MemIo testMemIo(testData, sizeof(testData));

    DataBuf result = testMemIo.read(sizeof(testData) + 1);

    EXPECT_EQ(result.size(), sizeof(testData));

}



TEST_F(MemIoTest_Read_EmptyBuffer_589) {

    const byte testData[] = {};

    MemIo testMemIo(testData, sizeof(testData));

    DataBuf result = testMemIo.read(10);

    EXPECT_EQ(result.size(), 0u);

}



TEST_F(MemIoTest_Read_LargeSize_589) {

    size_t largeSize = 1024 * 1024; // 1MB

    byte* testData = new byte[largeSize];

    std::fill(testData, testData + largeSize, 0xFF);

    MemIo testMemIo(testData, largeSize);

    DataBuf result = testMemIo.read(largeSize);

    EXPECT_EQ(result.size(), largeSize);

    for (size_t i = 0; i < largeSize; ++i) {

        EXPECT_EQ(result.c_data()[i], testData[i]);

    }

    delete[] testData;

}
