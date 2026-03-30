#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class RemoteIoTest_607 : public ::testing::Test {

protected:

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest_607, GetbReturnsDataWhenAvailable_607) {

    // Arrange

    byte data[] = {1, 2, 3};

    size_t dataSize = sizeof(data);

    DataBuf fakeData(data, dataSize);

    remoteIo.populateFakeData(fakeData.pData_, dataSize);



    // Act & Assert

    EXPECT_EQ(remoteIo.getb(), 1);

    EXPECT_EQ(remoteIo.getb(), 2);

    EXPECT_EQ(remoteIo.getb(), 3);

}



TEST_F(RemoteIoTest_607, GetbReturnsEofWhenAtEndOfFile_607) {

    // Arrange

    byte data[] = {1};

    size_t dataSize = sizeof(data);

    DataBuf fakeData(data, dataSize);

    remoteIo.populateFakeData(fakeData.pData_, dataSize);



    // Act & Assert

    EXPECT_EQ(remoteIo.getb(), 1);

    EXPECT_EQ(remoteIo.getb(), EOF);

}



TEST_F(RemoteIoTest_607, GetbHandlesBoundaryConditionsWithMultipleBlocks_607) {

    // Arrange

    byte data[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(data);

    DataBuf fakeData(data, dataSize);

    remoteIo.populateFakeData(fakeData.pData_, dataSize);



    // Act & Assert

    EXPECT_EQ(remoteIo.getb(), 1);

    EXPECT_EQ(remoteIo.getb(), 2);

    EXPECT_EQ(remoteIo.getb(), 3);

    EXPECT_EQ(remoteIo.getb(), 4);

    EXPECT_EQ(remoteIo.getb(), 5);

    EXPECT_EQ(remoteIo.getb(), EOF);

}



TEST_F(RemoteIoTest_607, GetbHandlesEmptyDataProperly_607) {

    // Arrange

    byte data[] = {};

    size_t dataSize = sizeof(data);

    DataBuf fakeData(data, dataSize);

    remoteIo.populateFakeData(fakeData.pData_, dataSize);



    // Act & Assert

    EXPECT_EQ(remoteIo.getb(), EOF);

}
