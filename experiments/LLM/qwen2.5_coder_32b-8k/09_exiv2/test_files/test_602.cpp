#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/basicio.cpp"



using namespace Exiv2;



// Test fixture for RemoteIo class

class RemoteIoTest_602 : public ::testing::Test {

protected:

    RemoteIo remote_io;

};



// Test normal operation with a non-zero size_t write count

TEST_F(RemoteIoTest_602, WriteNonZeroCount_602) {

    const byte data[] = {1, 2, 3};

    EXPECT_EQ(remote_io.write(data, sizeof(data)), 0);

}



// Test boundary condition with zero size_t write count

TEST_F(RemoteIoTest_602, WriteZeroCount_602) {

    const byte data[] = {1, 2, 3};

    EXPECT_EQ(remote_io.write(data, 0), 0);

}



// Test exceptional case where write fails (always true in this implementation)

TEST_F(RemoteIoTest_602, WriteFailure_602) {

    const byte data[] = {1, 2, 3};

    EXPECT_EQ(remote_io.write(data, sizeof(data)), 0);

}

```


