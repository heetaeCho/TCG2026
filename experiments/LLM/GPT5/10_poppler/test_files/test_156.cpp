// File: FileStream_setNeedsEncryptionOnSave_156_test.cpp
// Covers: FileStream::setNeedsEncryptionOnSave(bool) (+ observable getter)
// TEST_ID: 156

#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <filesystem>

#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "goo/GooFile.h"

namespace {

class FileStreamTest_156 : public ::testing::Test {
protected:
  static std::string MakeTempFileWithContents(const std::string &contents)
  {
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path();

    // Use a reasonably-unique name for parallel test runs.
    const fs::path path =
        dir / fs::path("poppler_filestream_test_156_" + std::to_string(::getpid()) + "_" +
                       std::to_string(reinterpret_cast<uintptr_t>(&dir)) + ".bin");

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    EXPECT_TRUE(out.good());
    out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    out.close();

    return path.string();
  }

  static void RemoveIfExists(const std::string &path)
  {
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }

  // Best-effort helper to open a GooFile across Poppler variants.
  // If your Poppler tree uses different GooFile::open overloads, adjust here.
  static GooFile *OpenGooFileOrDie(const std::string &path)
  {
    // Common Poppler signature: GooFile::open(const char *fileName)
    GooFile *f = GooFile::open(path.c_str());
    EXPECT_NE(f, nullptr) << "Failed to open temp file with GooFile::open";
    return f;
  }

  static std::unique_ptr<FileStream> MakeFileStreamOrDie(const std::string &path)
  {
    GooFile *gooFile = OpenGooFileOrDie(path);
    // FileStream takes Object&& for dict. A default-constructed Object is sufficient
    // for exercising this setter/getter behavior.
    Object dictObj;
    return std::make_unique<FileStream>(gooFile, /*startA=*/0, /*limitedA=*/false,
                                        /*lengthA=*/0, std::move(dictObj));
  }
};

TEST_F(FileStreamTest_156, SetTrueThenGetterReflectsTrue_156)
{
  const std::string path = MakeTempFileWithContents("abc");
  auto fs = MakeFileStreamOrDie(path);

  fs->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(fs->getNeedsEncryptionOnSave());

  RemoveIfExists(path);
}

TEST_F(FileStreamTest_156, SetFalseThenGetterReflectsFalse_156)
{
  const std::string path = MakeTempFileWithContents("abc");
  auto fs = MakeFileStreamOrDie(path);

  fs->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(fs->getNeedsEncryptionOnSave());

  RemoveIfExists(path);
}

TEST_F(FileStreamTest_156, ToggleValueMultipleTimes_156)
{
  const std::string path = MakeTempFileWithContents("abc");
  auto fs = MakeFileStreamOrDie(path);

  fs->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(fs->getNeedsEncryptionOnSave());

  fs->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(fs->getNeedsEncryptionOnSave());

  fs->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(fs->getNeedsEncryptionOnSave());

  RemoveIfExists(path);
}

TEST_F(FileStreamTest_156, IdempotentSetDoesNotBreakObservableState_156)
{
  const std::string path = MakeTempFileWithContents("abc");
  auto fs = MakeFileStreamOrDie(path);

  fs->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(fs->getNeedsEncryptionOnSave());

  // Setting to same value again should keep the observable state consistent.
  fs->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(fs->getNeedsEncryptionOnSave());

  fs->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(fs->getNeedsEncryptionOnSave());

  fs->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(fs->getNeedsEncryptionOnSave());

  RemoveIfExists(path);
}

} // namespace