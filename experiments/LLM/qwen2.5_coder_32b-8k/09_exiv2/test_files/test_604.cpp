#include <gtest/gtest.h>

#include "basicio.cpp"  // Assuming the class definition is in this file



using namespace Exiv2;



class RemoteIoTest_604 : public ::testing::Test {

protected:

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest_604, PutbReturnsZeroForAnyData_604) {

    EXPECT_EQ(remoteIo.putb(0), 0);

    EXPECT_EQ(remoteIo.putb(128), 0);

    EXPECT_EQ(remoteIo.putb(255), 0);

}



TEST_F(RemoteIoTest_604, PutbHandlesBoundaryValues_604) {

    EXPECT_EQ(remoteIo.putb(std::numeric_limits<byte>::min()), 0);

    EXPECT_EQ(remoteIo.putb(std::numeric_limits<byte>::max()), 0);

}
