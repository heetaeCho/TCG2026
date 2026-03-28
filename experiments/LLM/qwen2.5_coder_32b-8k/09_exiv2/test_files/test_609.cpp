#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class RemoteIoTest_609 : public ::testing::Test {

protected:

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest_609, SeekFromBeg_609) {

    int result = remoteIo.seek(10, BasicIo::beg);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_609, SeekFromCur_609) {

    // Assuming initial position is 0

    remoteIo.seek(5, BasicIo::beg); // Move to position 5

    int result = remoteIo.seek(10, BasicIo::cur);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_609, SeekFromEnd_609) {

    // Assuming size is 20 for this test

    int result = remoteIo.seek(-5, BasicIo::end);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_609, SeekBeyondSize_609) {

    // Assuming size is 20 for this test

    int result = remoteIo.seek(25, BasicIo::beg);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_609, SeekNegativeFromCur_609) {

    // Assuming initial position is 10 for this test

    remoteIo.seek(10, BasicIo::beg); // Move to position 10

    int result = remoteIo.seek(-5, BasicIo::cur);

    EXPECT_EQ(result, 0);

}



TEST_F(RemoteIoTest_609, SeekNegativeFromBeg_609) {

    int result = remoteIo.seek(-10, BasicIo::beg);

    EXPECT_EQ(result, 0);

}
