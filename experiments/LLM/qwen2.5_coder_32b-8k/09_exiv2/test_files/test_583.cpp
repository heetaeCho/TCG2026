#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_583, DefaultConstructorInitializesObject_583) {

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_583, OpenClosesSuccessfully_583) {

    EXPECT_EQ(0, memIo.open());

    EXPECT_TRUE(memIo.isopen());



    EXPECT_EQ(0, memIo.close());

    EXPECT_FALSE(memIo.isopen());

}



TEST_F(MemIoTest_583, WriteAndReadData_583) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo.open());

    EXPECT_EQ(dataSize, memIo.write(data, dataSize));



    memIo.seek(0, BasicIo::beg);

    DataBuf readData = memIo.read(dataSize);

    EXPECT_EQ(dataSize, readData.size());



    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(data[i], readData.p_[i]);

    }

}



TEST_F(MemIoTest_583, SeekPositionBoundaryConditions_583) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo.open());

    EXPECT_EQ(dataSize, memIo.write(data, dataSize));



    EXPECT_EQ(0, memIo.seek(0, BasicIo::beg));

    EXPECT_EQ(0, memIo.tell());



    EXPECT_EQ(0, memIo.seek(dataSize - 1, BasicIo::beg));

    EXPECT_EQ(dataSize - 1, memIo.tell());



    EXPECT_EQ(0, memIo.seek(-dataSize + 1, BasicIo::cur));

    EXPECT_EQ(0, memIo.tell());



    EXPECT_EQ(0, memIo.seek(dataSize, BasicIo::end));

    EXPECT_EQ(dataSize, memIo.tell());



    EXPECT_EQ(0, memIo.seek(-static_cast<int64_t>(dataSize), BasicIo::end));

    EXPECT_EQ(0, memIo.tell());

}



TEST_F(MemIoTest_583, MmapAndMunmapOperations_583) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo.open());

    EXPECT_EQ(dataSize, memIo.write(data, dataSize));



    byte* mappedData = memIo.mmap(false);

    ASSERT_NE(nullptr, mappedData);



    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(mappedData[i], data[i]);

    }



    EXPECT_EQ(0, memIo.munmap());

}



TEST_F(MemIoTest_583, ErrorHandlingOnClosedIO_583) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(data);



    memIo.write(data, dataSize);

    EXPECT_EQ(0, memIo.close());



    EXPECT_EQ(-1, memIo.seek(0, BasicIo::beg));

    EXPECT_EQ(-1, memIo.tell());

    EXPECT_TRUE(memIo.error() != 0);

}



TEST_F(MemIoTest_583, EofHandlingAfterRead_583) {

    const byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);



    EXPECT_EQ(0, memIo.open());

    EXPECT_EQ(dataSize, memIo.write(data, dataSize));



    memIo.seek(0, BasicIo::beg);

    DataBuf readData = memIo.read(dataSize);

    EXPECT_FALSE(memIo.eof());



    readData = memIo.read(dataSize); // Read beyond the end

    EXPECT_TRUE(memIo.eof());

}
