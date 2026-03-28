#include <gtest/gtest.h>
#include "exiv2/futils.hpp"

namespace Exiv2 {
    Protocol fileProtocol(const std::string& path);
}

using namespace Exiv2;

// Test HTTP protocol detection
TEST(FileProtocolTest_1805, HttpProtocol_1805) {
    EXPECT_EQ(pHttp, fileProtocol("http://example.com"));
}

TEST(FileProtocolTest_1805, HttpProtocolMinimalPath_1805) {
    EXPECT_EQ(pHttp, fileProtocol("http://x"));
}

TEST(FileProtocolTest_1805, HttpProtocolExactPrefix_1805) {
    // "http://" alone has size == name.size(), so isUrl requires size > name.size()
    EXPECT_EQ(pFile, fileProtocol("http://"));
}

// Test HTTPS protocol detection
TEST(FileProtocolTest_1805, HttpsProtocol_1805) {
    EXPECT_EQ(pHttps, fileProtocol("https://example.com"));
}

TEST(FileProtocolTest_1805, HttpsProtocolMinimalPath_1805) {
    EXPECT_EQ(pHttps, fileProtocol("https://a"));
}

TEST(FileProtocolTest_1805, HttpsProtocolExactPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("https://"));
}

// Test FTP protocol detection
TEST(FileProtocolTest_1805, FtpProtocol_1805) {
    EXPECT_EQ(pFtp, fileProtocol("ftp://example.com"));
}

TEST(FileProtocolTest_1805, FtpProtocolExactPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("ftp://"));
}

// Test SFTP protocol detection
TEST(FileProtocolTest_1805, SftpProtocol_1805) {
    EXPECT_EQ(pSftp, fileProtocol("sftp://example.com"));
}

TEST(FileProtocolTest_1805, SftpProtocolExactPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("sftp://"));
}

// Test file:// URI protocol detection
TEST(FileProtocolTest_1805, FileUriProtocol_1805) {
    EXPECT_EQ(pFileUri, fileProtocol("file:///home/user/image.jpg"));
}

TEST(FileProtocolTest_1805, FileUriProtocolMinimalPath_1805) {
    EXPECT_EQ(pFileUri, fileProtocol("file://x"));
}

TEST(FileProtocolTest_1805, FileUriProtocolExactPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("file://"));
}

// Test data:// URI protocol detection
TEST(FileProtocolTest_1805, DataUriProtocol_1805) {
    EXPECT_EQ(pDataUri, fileProtocol("data://some_data"));
}

TEST(FileProtocolTest_1805, DataUriProtocolExactPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("data://"));
}

// Test stdin protocol detection
TEST(FileProtocolTest_1805, StdinProtocol_1805) {
    EXPECT_EQ(pStdin, fileProtocol("-"));
}

TEST(FileProtocolTest_1805, StdinProtocolLongerString_1805) {
    // "-" with isUrl=false requires path.size() == name.size() (i.e., exactly "-")
    EXPECT_EQ(pFile, fileProtocol("-something"));
}

// Test regular file paths
TEST(FileProtocolTest_1805, RegularFilePath_1805) {
    EXPECT_EQ(pFile, fileProtocol("/home/user/image.jpg"));
}

TEST(FileProtocolTest_1805, RegularFilePathRelative_1805) {
    EXPECT_EQ(pFile, fileProtocol("image.jpg"));
}

TEST(FileProtocolTest_1805, RegularFilePathWindows_1805) {
    EXPECT_EQ(pFile, fileProtocol("C:\\Users\\user\\image.jpg"));
}

// Test empty path
TEST(FileProtocolTest_1805, EmptyPath_1805) {
    EXPECT_EQ(pFile, fileProtocol(""));
}

// Test paths that look like protocols but aren't quite right
TEST(FileProtocolTest_1805, PartialHttpPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("http:/"));
}

TEST(FileProtocolTest_1805, PartialHttpsPrefix_1805) {
    EXPECT_EQ(pFile, fileProtocol("https:/"));
}

TEST(FileProtocolTest_1805, HttpNoColon_1805) {
    EXPECT_EQ(pFile, fileProtocol("http//example.com"));
}

TEST(FileProtocolTest_1805, CaseSensitivity_1805) {
    // Protocol matching should be case-sensitive
    EXPECT_EQ(pFile, fileProtocol("HTTP://example.com"));
    EXPECT_EQ(pFile, fileProtocol("Http://example.com"));
    EXPECT_EQ(pFile, fileProtocol("HTTPS://example.com"));
    EXPECT_EQ(pFile, fileProtocol("FTP://example.com"));
}

TEST(FileProtocolTest_1805, PathWithSpaces_1805) {
    EXPECT_EQ(pHttp, fileProtocol("http://example.com/path with spaces"));
}

TEST(FileProtocolTest_1805, DashInMiddleOfPath_1805) {
    EXPECT_EQ(pFile, fileProtocol("path-to-file"));
}

TEST(FileProtocolTest_1805, DashAtStartLonger_1805) {
    EXPECT_EQ(pFile, fileProtocol("--"));
}

TEST(FileProtocolTest_1805, FtpMinimalPath_1805) {
    EXPECT_EQ(pFtp, fileProtocol("ftp://a"));
}

TEST(FileProtocolTest_1805, SftpMinimalPath_1805) {
    EXPECT_EQ(pSftp, fileProtocol("sftp://a"));
}

TEST(FileProtocolTest_1805, DataUriMinimalPath_1805) {
    EXPECT_EQ(pDataUri, fileProtocol("data://a"));
}

// Test that only the first matching protocol is returned
TEST(FileProtocolTest_1805, OnlyFirstMatch_1805) {
    // A path starting with "http://" should match http, not anything else
    EXPECT_EQ(pHttp, fileProtocol("http://https://example.com"));
}

// Test very long path
TEST(FileProtocolTest_1805, VeryLongPath_1805) {
    std::string longPath = "http://" + std::string(2000, 'a');
    EXPECT_EQ(pHttp, fileProtocol(longPath));
}

TEST(FileProtocolTest_1805, VeryLongFilePath_1805) {
    std::string longPath = std::string(2000, 'a');
    EXPECT_EQ(pFile, fileProtocol(longPath));
}

// Test single character paths
TEST(FileProtocolTest_1805, SingleCharNotDash_1805) {
    EXPECT_EQ(pFile, fileProtocol("a"));
    EXPECT_EQ(pFile, fileProtocol("/"));
    EXPECT_EQ(pFile, fileProtocol("."));
}
