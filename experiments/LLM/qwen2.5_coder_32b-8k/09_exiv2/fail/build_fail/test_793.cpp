#include <gtest/gtest.h>

#include "value.cpp" // Assuming this file contains the DataValue class definition



using namespace Exiv2;



class DataValueTest_793 : public ::testing::Test {

protected:

    DataValue dataValue;

};



TEST_F(DataValueTest_793, ReadReturnsZeroOnSuccess_793) {

    byte buffer[] = {0x01, 0x02, 0x03};

    EXPECT_EQ(0, dataValue.read(buffer, sizeof(buffer), ByteOrder::bigEndian));

}



TEST_F(DataValueTest_793, ReadAssignsBufferContent_793) {

    byte buffer[] = {0x01, 0x02, 0x03};

    dataValue.read(buffer, sizeof(buffer), ByteOrder::bigEndian);

    EXPECT_EQ(std::vector<byte>(buffer, buffer + sizeof(buffer)), dataValue.value_);

}



TEST_F(DataValueTest_793, ReadHandlesZeroLengthBuffer_793) {

    byte buffer[] = {0x01, 0x02, 0x03};

    EXPECT_EQ(0, dataValue.read(buffer, 0, ByteOrder::bigEndian));

}



TEST_F(DataValueTest_793, ReadHandlesLargeBuffer_793) {

    std::vector<byte> largeBuffer(1024, 0xFF);

    EXPECT_EQ(0, dataValue.read(largeBuffer.data(), largeBuffer.size(), ByteOrder::bigEndian));

}
