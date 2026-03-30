// File: xml_document_savefile_filename_tests_281.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#endif

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentSaveFileTest_281 : public ::testing::Test {
protected:
  static std::string UniqueToken_281() {
    // Good-enough uniqueness for tests (no reliance on platform-specific PID APIs).
    static int counter = 0;
    ++counter;
    return std::to_string(counter) + "_" + std::to_string(static_cast<unsigned long long>(std::time(nullptr)));
  }

  static std::string TempFilePath_281(const char* suffix) {
#if __has_include(<filesystem>)
    fs::path base = fs::temp_directory_path();
    fs::path file = base / ("tinyxml2_savefile_281_" + UniqueToken_281() + suffix);
    return file.string();
#else
    // Fallback: relative path in working directory.
    return std::string("tinyxml2_savefile_281_") + UniqueToken_281() + suffix;
#endif
  }

  static std::string TempDirPath_281() {
#if __has_include(<filesystem>)
    fs::path base = fs::temp_directory_path();
    fs::path dir = base / ("tinyxml2_savefile_dir_281_" + UniqueToken_281());
    return dir.string();
#else
    return std::string("tinyxml2_savefile_dir_281_") + UniqueToken_281();
#endif
  }

  static bool FileExistsAndNonEmpty_281(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in.good()) return false;
    in.seekg(0, std::ios::end);
    return static_cast<std::streamoff>(in.tellg()) > 0;
  }
};

}  // namespace

TEST_F(XMLDocumentSaveFileTest_281, NullFilenameReturnsOpenErrorOrAsserts_281) {
  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

#if !defined(NDEBUG)
  // In many builds TIXMLASSERT maps to assert(), which aborts in debug.
  // We verify the observable "asserts" behavior without relying on internal state.
  EXPECT_DEATH(
      {
        (void)doc.SaveFile(nullptr, /*compact=*/false);
      },
      "");
#else
  // In release builds asserts are commonly compiled out; then we can observe error handling.
  XMLError err = doc.SaveFile(nullptr, /*compact=*/false);
  EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
  EXPECT_TRUE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_COULD_NOT_BE_OPENED);

  const char* errStr = doc.ErrorStr();
  ASSERT_NE(errStr, nullptr);
  EXPECT_NE(std::string(errStr).find("filename="), std::string::npos);
#endif
}

TEST_F(XMLDocumentSaveFileTest_281, EmptyFilenameReturnsCouldNotBeOpened_281) {
  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

  XMLError err = doc.SaveFile("", /*compact=*/false);

  // fopen("", "w") should fail across platforms.
  EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
  EXPECT_TRUE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_COULD_NOT_BE_OPENED);

  const char* errStr = doc.ErrorStr();
  ASSERT_NE(errStr, nullptr);
  EXPECT_NE(std::string(errStr).find("filename="), std::string::npos);
}

TEST_F(XMLDocumentSaveFileTest_281, NonExistentDirectoryPathReturnsCouldNotBeOpened_281) {
  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

  // Choose a directory name that is extremely unlikely to exist.
  std::string path = std::string("this_directory_should_not_exist_281_") + UniqueToken_281() + "/out.xml";

  XMLError err = doc.SaveFile(path.c_str(), /*compact=*/true);

  EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
  EXPECT_TRUE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_COULD_NOT_BE_OPENED);

  const char* errStr = doc.ErrorStr();
  ASSERT_NE(errStr, nullptr);
  EXPECT_NE(std::string(errStr).find("filename="), std::string::npos);
}

TEST_F(XMLDocumentSaveFileTest_281, DirectoryAsFilenameReturnsCouldNotBeOpened_281) {
#if __has_include(<filesystem>)
  std::string dirPath = TempDirPath_281();
  fs::create_directory(dirPath);

  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

  // Passing a directory path to fopen(...,"w") should fail.
  XMLError err = doc.SaveFile(dirPath.c_str(), /*compact=*/false);

  EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
  EXPECT_TRUE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_COULD_NOT_BE_OPENED);

  // Cleanup best-effort.
  std::error_code ec;
  fs::remove_all(dirPath, ec);
#else
  GTEST_SKIP() << "std::filesystem not available; skipping directory-as-filename test.";
#endif
}

TEST_F(XMLDocumentSaveFileTest_281, ValidPathWritesFileAndReturnsSuccess_281) {
  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

  // Create minimal content to save.
  ASSERT_EQ(doc.Parse("<root/>", 7), XML_SUCCESS);
  ASSERT_FALSE(doc.Error());
  ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

  const std::string outPath = TempFilePath_281(".xml");

  XMLError err = doc.SaveFile(outPath.c_str(), /*compact=*/false);

  EXPECT_EQ(err, XML_SUCCESS);
  EXPECT_FALSE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

  EXPECT_TRUE(FileExistsAndNonEmpty_281(outPath));

#if __has_include(<filesystem>)
  std::error_code ec;
  fs::remove(outPath, ec);
#else
  std::remove(outPath.c_str());
#endif
}

TEST_F(XMLDocumentSaveFileTest_281, CompactFlagDoesNotPreventSuccessfulWrite_281) {
  XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);
  doc.ClearError();

  ASSERT_EQ(doc.Parse("<root><child/></root>", 20), XML_SUCCESS);
  ASSERT_FALSE(doc.Error());
  ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);

  const std::string outPath = TempFilePath_281("_compact.xml");

  XMLError err = doc.SaveFile(outPath.c_str(), /*compact=*/true);

  EXPECT_EQ(err, XML_SUCCESS);
  EXPECT_FALSE(doc.Error());
  EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

  EXPECT_TRUE(FileExistsAndNonEmpty_281(outPath));

#if __has_include(<filesystem>)
  std::error_code ec;
  fs::remove(outPath, ec);
#else
  std::remove(outPath.c_str());
#endif
}
