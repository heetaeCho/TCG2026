#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/basicio.cpp"



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_PutIncreasesCount_582, Mmap_ReturnsNonNULLForWritable_582) {

    byte* result = memIo.mmap(true);

    EXPECT_NE(result, nullptr);

}



TEST_F(MemIoTest_PutIncreasesCount_582, Mmap_ReturnsNonNULLForReadOnly_582) {

    byte* result = memIo.mmap(false);

    EXPECT_NE(result, nullptr);

}



TEST_F(MemIoTest_PutIncreasesCount_582, Mmap_ConsistentAddressForWritable_582) {

    byte* firstCall = memIo.mmap(true);

    byte* secondCall = memIo.mmap(true);

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(MemIoTest_PutIncreasesCount_582, Mmap_ConsistentAddressForReadOnly_582) {

    byte* firstCall = memIo.mmap(false);

    byte* secondCall = memIo.mmap(false);

    EXPECT_EQ(firstCall, secondCall);

}

```


