#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <string>



using namespace Exiv2;



class FileIoTest_548 : public ::testing::Test {

protected:

    std::string filePath = "testfile.txt";

};



TEST_F(FileIoTest_548, OpenFileInReadMode_548) {

    FileIo file(filePath);

    int result = file.open("r");

    EXPECT_EQ(result, 0); // Assuming 0 indicates success

}



TEST_F(FileIoTest_548, OpenFileWithoutMode_548) {

    FileIo file(filePath);

    int result = file.open();

    EXPECT_EQ(result, 0); // Assuming 0 indicates success

}



TEST_F(FileIoTest_548, CloseFileAfterOpen_548) {

    FileIo file(filePath);

    file.open("r");

    int closeResult = file.close();

    EXPECT_EQ(closeResult, 0); // Assuming 0 indicates success

}



TEST_F(FileIoTest_548, SetPathAndCheckPath_548) {

    FileIo file(filePath);

    std::string newPath = "newfile.txt";

    file.setPath(newPath);

    EXPECT_EQ(file.path(), newPath);

}



TEST_F(FileIoTest_548, CheckIsOpenAfterOpenAndClose_548) {

    FileIo file(filePath);

    file.open("r");

    EXPECT_TRUE(file.isopen());

    file.close();

    EXPECT_FALSE(file.isopen());

}



TEST_F(FileIoTest_548, WriteDataToFile_548) {

    FileIo file(filePath);

    file.open("w");

    const byte data[] = "Hello";

    size_t writeResult = file.write(data, sizeof(data));

    EXPECT_EQ(writeResult, sizeof(data));

    file.close();

}



TEST_F(FileIoTest_548, ReadDataFromFile_548) {

    FileIo file(filePath);

    file.open("w");

    const byte data[] = "Hello";

    file.write(data, sizeof(data));

    file.close();



    file.open("r");

    DataBuf readResult = file.read(sizeof(data));

    EXPECT_EQ(memcmp(readResult.pData_, data, sizeof(data)), 0);

    file.close();

}



TEST_F(FileIoTest_548, SeekToFilePosition_548) {

    FileIo file(filePath);

    file.open("w");

    const byte data[] = "Hello";

    file.write(data, sizeof(data));

    file.close();



    file.open("r");

    int seekResult = file.seek(2, BasicIo::beg);

    EXPECT_EQ(seekResult, 0); // Assuming 0 indicates success

    size_t tellPosition = file.tell();

    EXPECT_EQ(tellPosition, 2u);

    file.close();

}



TEST_F(FileIoTest_548, CheckFileSizeAfterWrite_548) {

    FileIo file(filePath);

    file.open("w");

    const byte data[] = "Hello";

    file.write(data, sizeof(data));

    size_t fileSize = file.size();

    EXPECT_EQ(fileSize, sizeof(data));

    file.close();

}



TEST_F(FileIoTest_548, CheckEofAfterReadingToEnd_548) {

    FileIo file(filePath);

    file.open("w");

    const byte data[] = "Hello";

    file.write(data, sizeof(data));

    file.close();



    file.open("r");

    DataBuf readResult = file.read(sizeof(data));

    EXPECT_FALSE(file.eof());

    readResult = file.read(sizeof(data));

    EXPECT_TRUE(file.eof());

    file.close();

}



TEST_F(FileIoTest_548, CheckErrorHandlingOnInvalidPath_548) {

    FileIo file("nonexistentfile.txt");

    int openResult = file.open("r");

    EXPECT_NE(openResult, 0); // Assuming non-zero indicates failure

}
