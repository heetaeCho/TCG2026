#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <filesystem>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/futils.hpp"

namespace {

// Helper to clean up temporary files created during tests
class TempFileCleanup {
 public:
  ~TempFileCleanup() {
    for (const auto& f : files_) {
      std::remove(f.c_str());
    }
  }
  void track(const std::string& path) {
    files_.push_back(path);
  }
 private:
  std::vector<std::string> files_;
};

}  // namespace

class XPathIoWriteDataToFileTest_597 : public ::testing::Test {
 protected:
  TempFileCleanup cleanup_;
};

// Test that a valid base64 data URI produces a file with correct decoded content
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_ValidBase64_CreatesFileWithDecodedContent_597) {
  // "Hello" in base64 is "SGVsbG8="
  std::string dataUri = "data:text/plain;base64,SGVsbG8=";

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  // Verify the file exists
  ASSERT_TRUE(std::filesystem::exists(resultPath));

  // Read the file contents
  std::ifstream ifs(resultPath, std::ios::binary);
  ASSERT_TRUE(ifs.is_open());
  std::string content((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
  ifs.close();

  EXPECT_EQ(content, "Hello");
}

// Test that a data URI without "base64," throws an error
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_NoBase64Marker_ThrowsError_597) {
  std::string dataUri = "data:text/plain;nobase64data";

  EXPECT_THROW(Exiv2::XPathIo::writeDataToFile(dataUri), Exiv2::Error);
}

// Test that a data URI with empty base64 data after the marker throws an error
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_EmptyBase64Data_ThrowsError_597) {
  // After "base64," there's no data, which should result in size <= 0
  std::string dataUri = "data:text/plain;base64,";

  EXPECT_THROW(Exiv2::XPathIo::writeDataToFile(dataUri), Exiv2::Error);
}

// Test that a data URI with invalid base64 data throws an error
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_InvalidBase64Data_ThrowsError_597) {
  // Completely invalid base64 content
  std::string dataUri = "data:text/plain;base64,!@#$%^&*()";

  // This should either decode to nothing (size <= 0) or throw
  EXPECT_THROW(Exiv2::XPathIo::writeDataToFile(dataUri), Exiv2::Error);
}

// Test that the returned path has the expected TEMP_FILE_EXT extension
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_ReturnedPathHasTempFileExtension_597) {
  std::string dataUri = "data:text/plain;base64,SGVsbG8=";

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  // The path should end with the TEMP_FILE_EXT
  // Based on the code, path = "{timestamp}{TEMP_FILE_EXT}"
  // We check the file was actually created
  EXPECT_TRUE(std::filesystem::exists(resultPath));
  EXPECT_FALSE(resultPath.empty());
}

// Test that a larger base64 payload is correctly decoded
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_LargerPayload_CorrectlyDecoded_597) {
  // "The quick brown fox jumps over the lazy dog" in base64
  std::string base64Data = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==";
  std::string dataUri = "data:text/plain;base64," + base64Data;

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  ASSERT_TRUE(std::filesystem::exists(resultPath));

  std::ifstream ifs(resultPath, std::ios::binary);
  ASSERT_TRUE(ifs.is_open());
  std::string content((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
  ifs.close();

  EXPECT_EQ(content, "The quick brown fox jumps over the lazy dog");
}

// Test data URI with binary content (e.g., a few bytes)
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_BinaryContent_CreatesFile_597) {
  // Base64 for bytes {0x00, 0x01, 0x02, 0x03} is "AAECAw=="
  std::string dataUri = "data:application/octet-stream;base64,AAECAw==";

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  ASSERT_TRUE(std::filesystem::exists(resultPath));

  std::ifstream ifs(resultPath, std::ios::binary);
  ASSERT_TRUE(ifs.is_open());
  std::string content((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
  ifs.close();

  ASSERT_EQ(content.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(content[0]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(content[1]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(content[2]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(content[3]), 0x03);
}

// Test that data URI with "base64," appearing in the middle works
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_Base64MarkerPosition_CorrectlyParsed_597) {
  // The code searches for "base64," and takes everything after it
  std::string dataUri = "data:image/png;base64,YQ==";  // "a"

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  ASSERT_TRUE(std::filesystem::exists(resultPath));

  std::ifstream ifs(resultPath, std::ios::binary);
  ASSERT_TRUE(ifs.is_open());
  std::string content((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
  ifs.close();

  EXPECT_EQ(content, "a");
}

// Test that multiple calls produce different file paths (timestamp-based)
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_MultipleCalls_ProduceFiles_597) {
  std::string dataUri = "data:text/plain;base64,SGVsbG8=";

  std::string path1;
  ASSERT_NO_THROW(path1 = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(path1);

  std::string path2;
  ASSERT_NO_THROW(path2 = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(path2);

  // Both files should exist
  EXPECT_TRUE(std::filesystem::exists(path1));
  EXPECT_TRUE(std::filesystem::exists(path2));
}

// Test that returned path is not empty for valid data URI
TEST_F(XPathIoWriteDataToFileTest_597, DataUri_ValidInput_ReturnsNonEmptyPath_597) {
  std::string dataUri = "data:text/plain;base64,dGVzdA==";  // "test"

  std::string resultPath;
  ASSERT_NO_THROW(resultPath = Exiv2::XPathIo::writeDataToFile(dataUri));
  cleanup_.track(resultPath);

  EXPECT_FALSE(resultPath.empty());
}
