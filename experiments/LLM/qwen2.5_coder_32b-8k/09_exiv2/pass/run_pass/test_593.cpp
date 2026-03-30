#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <memory>



using namespace Exiv2;



class MemIoTest_593 : public ::testing::Test {

protected:

    std::unique_ptr<MemIo> memIo;



    void SetUp() override {

        memIo = std::make_unique<MemIo>();

    }

};



TEST_F(MemIoTest_593, EofInitiallyFalse_593) {

    EXPECT_FALSE(memIo->eof());

}



TEST_F(MemIoTest_593, OpenCloseCycle_593) {

    EXPECT_EQ(0, memIo->open());

    EXPECT_TRUE(memIo->isopen());



    EXPECT_EQ(0, memIo->close());

    EXPECT_FALSE(memIo->isopen());

}



TEST_F(MemIoTest_593, WriteReadCycle_593) {

    const byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo->open());

    EXPECT_EQ(dataSize, memIo->write(data, dataSize));



    byte readData[dataSize];

    EXPECT_EQ(dataSize, memIo->read(readData, dataSize));

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(data[i], readData[i]);

    }



    EXPECT_EQ(0, memIo->close());

}



TEST_F(MemIoTest_593, SeekTellCycle_593) {

    const byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo->open());

    EXPECT_EQ(dataSize, memIo->write(data, dataSize));



    EXPECT_EQ(0, memIo->seek(1, BasicIo::beg));

    EXPECT_EQ(1, memIo->tell());



    byte readData;

    EXPECT_EQ(1, memIo->read(&readData, 1));

    EXPECT_EQ(data[1], readData);



    EXPECT_EQ(0, memIo->close());

}



TEST_F(MemIoTest_593, ReadBeyondSize_593) {

    const byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo->open());

    EXPECT_EQ(dataSize, memIo->write(data, dataSize));



    byte readData[dataSize + 1];

    EXPECT_EQ(dataSize, memIo->read(readData, dataSize + 1));

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(data[i], readData[i]);

    }

    // Last byte should not be modified

    EXPECT_NE(1, readData[dataSize]);



    EXPECT_EQ(0, memIo->close());

}



TEST_F(MemIoTest_593, ErrorHandling_593) {

    // Assuming error() returns non-zero on failure

    EXPECT_EQ(0, memIo->open());



    // Attempt to write without opening should fail

    MemIo anotherMemIo;

    const byte data[] = {1};

    size_t dataSize = sizeof(data);

    EXPECT_NE(0, anotherMemIo.write(data, dataSize));



    // Attempt to read from closed io

    EXPECT_EQ(0, memIo->close());

    byte readData;

    EXPECT_EQ(0, memIo->read(&readData, 1));



    EXPECT_EQ(0, memIo->open());

}



TEST_F(MemIoTest_593, MmapMunmapCycle_593) {

    const byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo->open());

    EXPECT_EQ(dataSize, memIo->write(data, dataSize));



    byte* mappedData = memIo->mmap(true);

    ASSERT_NE(nullptr, mappedData);



    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(data[i], mappedData[i]);

    }



    EXPECT_EQ(0, memIo->munmap());

}
