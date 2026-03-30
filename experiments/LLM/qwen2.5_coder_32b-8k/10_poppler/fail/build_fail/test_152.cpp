#include <gtest/gtest.h>

#include "Stream.h"



class FileStreamTest_152 : public ::testing::Test {

protected:

    GooFile *fileMock;

    Object dictMock;



    void SetUp() override {

        fileMock = new GooFile();

        dictMock.initNull();

    }



    void TearDown() override {

        delete fileMock;

        dictMock.free();

    }

};



TEST_F(FileStreamTest_152, GetStart_ReturnsInitialValue_152) {

    const Goffset startA = 4096;

    FileStream fs(fileMock, startA, false, 8192, std::move(dictMock));

    EXPECT_EQ(fs.getStart(), startA);

}



TEST_F(FileStreamTest_152, GetStart_UnchangedAfterRewind_152) {

    const Goffset startA = 4096;

    FileStream fs(fileMock, startA, false, 8192, std::move(dictMock));

    fs.rewind();

    EXPECT_EQ(fs.getStart(), startA);

}



TEST_F(FileStreamTest_152, GetStart_UnchangedAfterMoveStart_152) {

    const Goffset startA = 4096;

    FileStream fs(fileMock, startA, false, 8192, std::move(dictMock));

    fs.moveStart(1024);

    EXPECT_EQ(fs.getStart(), startA + 1024);

}



TEST_F(FileStreamTest_152, GetStart_UnchangedAfterSetPos_152) {

    const Goffset startA = 4096;

    FileStream fs(fileMock, startA, false, 8192, std::move(dictMock));

    fs.setPos(2048, -1);

    EXPECT_EQ(fs.getStart(), startA);

}



TEST_F(FileStreamTest_152, GetStart_UnchangedAfterClose_152) {

    const Goffset startA = 4096;

    FileStream fs(fileMock, startA, false, 8192, std::move(dictMock));

    fs.close();

    EXPECT_EQ(fs.getStart(), startA);

}
