#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Eq;



class RemoteIoTest_617 : public ::testing::Test {

protected:

    RemoteIo io;

};



TEST_F(RemoteIoTest_617, OpenCloseCycle_617) {

    EXPECT_EQ(io.open(), 0);

    EXPECT_TRUE(io.isopen());

    EXPECT_EQ(io.close(), 0);

    EXPECT_FALSE(io.isopen());

}



TEST_F(RemoteIoTest_617, DoubleOpenCheck_617) {

    EXPECT_EQ(io.open(), 0);

    EXPECT_EQ(io.open(), 0); // Opening an already open file should not fail

    EXPECT_TRUE(io.isopen());

    io.close();

}



TEST_F(RemoteIoTest_617, CloseWhenNotOpen_617) {

    EXPECT_EQ(io.close(), -1); // Closing a non-open file should return error

}



TEST_F(RemoteIoTest_617, PathInitialValue_617) {

    EXPECT_EQ(io.path(), "");

}



// Assuming that RemoteIo can be opened and closed multiple times without affecting path

TEST_F(RemoteIoTest_617, PathAfterOpenCloseCycle_617) {

    io.open();

    EXPECT_EQ(io.path(), "");

    io.close();

    EXPECT_EQ(io.path(), "");

}
