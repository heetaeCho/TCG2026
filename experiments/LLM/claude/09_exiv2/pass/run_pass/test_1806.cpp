#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstdio>

// Include the header for the functions under test
#include "exiv2/futils.hpp"

namespace {

// Helper to create a temporary file
class TempFile {
 public:
  explicit TempFile(const std::string& path) : path_(path) {
    std::ofstream ofs(path_);
    ofs << "test content";
    ofs.close();
  }
  ~TempFile() { std::remove(path_.c_str()); }
  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

}  // namespace

// Test that fileExists returns true for a file that actually exists on disk
TEST(FileExistsTest_1806, ExistingFileReturnsTrue_1806) {
  TempFile tmp("test_fileexists_1806.tmp");
  bool result = Exiv2::fileExists(tmp.path());
#ifdef EXV_ENABLE_FILESYSTEM
  EXPECT_TRUE(result);
#else
  // Without filesystem support, local files return false
  EXPECT_FALSE(result);
#endif
}

// Test that fileExists returns false for a file that does not exist on disk
TEST(FileExistsTest_1806, NonExistingFileReturnsFalse_1806) {
  bool result = Exiv2::fileExists("this_file_should_not_exist_1806.xyz");
  EXPECT_FALSE(result);
}

// Test that fileExists returns true for an HTTP URL (non-pFile protocol)
TEST(FileExistsTest_1806, HttpProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("http://example.com/image.jpg");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for an HTTPS URL (non-pFile protocol)
TEST(FileExistsTest_1806, HttpsProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("https://example.com/image.jpg");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for an FTP URL (non-pFile protocol)
TEST(FileExistsTest_1806, FtpProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("ftp://example.com/image.jpg");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for an SFTP URL (non-pFile protocol)
TEST(FileExistsTest_1806, SftpProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("sftp://example.com/image.jpg");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for a data URI (non-pFile protocol)
TEST(FileExistsTest_1806, DataUriProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("data:image/png;base64,abc");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for a file URI (non-pFile protocol)
TEST(FileExistsTest_1806, FileUriProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("file:///tmp/image.jpg");
  EXPECT_TRUE(result);
}

// Test that fileExists returns true for stdin protocol (non-pFile protocol)
TEST(FileExistsTest_1806, StdinProtocolReturnsTrue_1806) {
  bool result = Exiv2::fileExists("-");
  EXPECT_TRUE(result);
}

// Test with an empty string - treated as a local file path
TEST(FileExistsTest_1806, EmptyStringReturnsFalse_1806) {
  bool result = Exiv2::fileExists("");
  EXPECT_FALSE(result);
}

// Test with a path that is just whitespace (treated as local file)
TEST(FileExistsTest_1806, WhitespacePathReturnsFalse_1806) {
  bool result = Exiv2::fileExists("   ");
  EXPECT_FALSE(result);
}

// Test with a very long non-existent path
TEST(FileExistsTest_1806, VeryLongNonExistentPathReturnsFalse_1806) {
  std::string longPath(2048, 'a');
  longPath += ".tmp";
  bool result = Exiv2::fileExists(longPath);
  EXPECT_FALSE(result);
}

// Test fileProtocol function directly for various protocols
TEST(FileProtocolTest_1806, LocalFileProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("somefile.jpg"), Exiv2::pFile);
}

TEST(FileProtocolTest_1806, HttpProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("http://example.com/img.jpg"), Exiv2::pHttp);
}

TEST(FileProtocolTest_1806, HttpsProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("https://example.com/img.jpg"), Exiv2::pHttps);
}

TEST(FileProtocolTest_1806, FtpProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("ftp://example.com/img.jpg"), Exiv2::pFtp);
}

TEST(FileProtocolTest_1806, SftpProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("sftp://example.com/img.jpg"), Exiv2::pSftp);
}

TEST(FileProtocolTest_1806, FileUriProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("file:///tmp/img.jpg"), Exiv2::pFileUri);
}

TEST(FileProtocolTest_1806, DataUriProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("data:image/png;base64,abc"), Exiv2::pDataUri);
}

TEST(FileProtocolTest_1806, StdinProtocol_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("-"), Exiv2::pStdin);
}

TEST(FileProtocolTest_1806, EmptyStringIsFile_1806) {
  EXPECT_EQ(Exiv2::fileProtocol(""), Exiv2::pFile);
}

TEST(FileProtocolTest_1806, RelativePathIsFile_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("./relative/path.jpg"), Exiv2::pFile);
}

TEST(FileProtocolTest_1806, AbsolutePathIsFile_1806) {
  EXPECT_EQ(Exiv2::fileProtocol("/absolute/path.jpg"), Exiv2::pFile);
}
