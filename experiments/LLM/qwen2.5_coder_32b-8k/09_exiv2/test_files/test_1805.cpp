#include <gtest/gtest.h>

#include "exiv2/futils.hpp"



using namespace Exiv2;



class FileProtocolTest_1805 : public ::testing::Test {

protected:

};



TEST_F(FileProtocolTest_1805, NormalOperation_File_1805) {

    EXPECT_EQ(fileProtocol("example.txt"), pFile);

}



TEST_F(FileProtocolTest_1805, NormalOperation_Http_1805) {

    EXPECT_EQ(fileProtocol("http://example.com"), pHttp);

}



TEST_F(FileProtocolTest_1805, NormalOperation_Https_1805) {

    EXPECT_EQ(fileProtocol("https://example.com"), pHttps);

}



TEST_F(FileProtocolTest_1805, NormalOperation_Ftp_1805) {

    EXPECT_EQ(fileProtocol("ftp://example.com"), pFtp);

}



TEST_F(FileProtocolTest_1805, NormalOperation_Sftp_1805) {

    EXPECT_EQ(fileProtocol("sftp://example.com"), pSftp);

}



TEST_F(FileProtocolTest_1805, NormalOperation_FileUri_1805) {

    EXPECT_EQ(fileProtocol("file:///path/to/example.txt"), pFileUri);

}



TEST_F(FileProtocolTest_1805, NormalOperation_DataUri_1805) {

    EXPECT_EQ(fileProtocol("data://example"), pDataUri);

}



TEST_F(FileProtocolTest_1805, NormalOperation_Stdin_1805) {

    EXPECT_EQ(fileProtocol("-"), pStdin);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_EmptyString_1805) {

    EXPECT_EQ(fileProtocol(""), pFile);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_Http_1805) {

    EXPECT_EQ(fileProtocol("http://"), pHttp);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_Https_1805) {

    EXPECT_EQ(fileProtocol("https://"), pHttps);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_Ftp_1805) {

    EXPECT_EQ(fileProtocol("ftp://"), pFtp);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_Sftp_1805) {

    EXPECT_EQ(fileProtocol("sftp://"), pSftp);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_FileUri_1805) {

    EXPECT_EQ(fileProtocol("file:///"), pFileUri);

}



TEST_F(FileProtocolTest_1805, BoundaryCondition_SchemeOnly_DataUri_1805) {

    EXPECT_EQ(fileProtocol("data://"), pDataUri);

}



TEST_F(FileProtocolTest_1805, ExceptionalCase_InvalidScheme_1805) {

    EXPECT_EQ(fileProtocol("unknown://example.com"), pFile);

}
