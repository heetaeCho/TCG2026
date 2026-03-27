#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



namespace {



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_590, ReadWithinBounds_590) {

    const byte data[] = { 1, 2, 3, 4, 5 };

    MemIo io(data, sizeof(data));

    

    byte buffer[3];

    size_t bytesRead = io.read(buffer, sizeof(buffer));

    

    EXPECT_EQ(bytesRead, 3u);

    EXPECT_EQ(buffer[0], data[0]);

    EXPECT_EQ(buffer[1], data[1]);

    EXPECT_EQ(buffer[2], data[2]);

}



TEST_F(MemIoTest_590, ReadExactEndOfFile_590) {

    const byte data[] = { 1, 2, 3 };

    MemIo io(data, sizeof(data));

    

    byte buffer[3];

    size_t bytesRead = io.read(buffer, sizeof(buffer));

    

    EXPECT_EQ(bytesRead, 3u);

    EXPECT_EQ(buffer[0], data[0]);

    EXPECT_EQ(buffer[1], data[1]);

    EXPECT_EQ(buffer[2], data[2]);

}



TEST_F(MemIoTest_590, ReadPastEndOfFile_590) {

    const byte data[] = { 1, 2, 3 };

    MemIo io(data, sizeof(data));

    

    byte buffer[5];

    size_t bytesRead = io.read(buffer, sizeof(buffer));

    

    EXPECT_EQ(bytesRead, 3u);

    EXPECT_EQ(buffer[0], data[0]);

    EXPECT_EQ(buffer[1], data[1]);

    EXPECT_EQ(buffer[2], data[2]);

}



TEST_F(MemIoTest_590, ReadZeroBytes_590) {

    const byte data[] = { 1, 2, 3 };

    MemIo io(data, sizeof(data));

    

    byte buffer[3];

    size_t bytesRead = io.read(buffer, 0);

    

    EXPECT_EQ(bytesRead, 0u);

}



TEST_F(MemIoTest_590, ReadAfterEndOfFile_590) {

    const byte data[] = { 1, 2, 3 };

    MemIo io(data, sizeof(data));

    

    byte buffer[3];

    io.read(buffer, sizeof(buffer)); // First read to reach EOF

    size_t bytesRead = io.read(buffer, sizeof(buffer)); // Second read after EOF

    

    EXPECT_EQ(bytesRead, 0u);

}



}  // namespace
