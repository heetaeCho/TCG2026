// File: FileStream_getNeedsEncryptionOnSave_tests_155.cpp
// TEST_ID is 155

#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#if __has_include("poppler/Stream.h")
#include "poppler/Stream.h"
#else
#include "Stream.h"
#endif

#include "goo/GooString.h"
#include "goo/gfile.h"
#include "Object.h"

namespace {

// ---- Compile-time detection helpers for GooFile::open(...) overloads ----
template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_open_with_string : std::false_type {};
template <typename T>
struct has_open_with_string<T, void_t<decltype(T::open(std::declval<const std::string &>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_open_with_cstr : std::false_type {};
template <typename T>
struct has_open_with_cstr<T, void_t<decltype(T::open(std::declval<const char *>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_open_with_goostring_ptr : std::false_type {};
template <typename T>
struct has_open_with_goostring_ptr<T, void_t<decltype(T::open(std::declval<const GooString *>()))>> : std::true_type {};

// Opens a GooFile using whichever overload exists in the Poppler version being tested.
static GooFile *OpenGooFileForPath(const std::string &path) {
  if constexpr (has_open_with_string<GooFile>::value) {
    return GooFile::open(path);
  } else if constexpr (has_open_with_cstr<GooFile>::value) {
    return GooFile::open(path.c_str());
  } else if constexpr (has_open_with_goostring_ptr<GooFile>::value) {
    GooString gs(path.c_str());
    return GooFile::open(&gs);
  } else {
    // If Poppler changes the API such that none of these overloads exist,
    // we can’t open a GooFile without knowing the new signature.
    return nullptr;
  }
}

static std::string WriteTempFileWithContents(const std::string &contents) {
  // Simple temp path strategy that works in most CI environments.
  // (We avoid filesystem dependencies; Poppler only needs a path that exists.)
  const std::string path = "file_stream_test_155.tmp";
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  out.close();
  return path;
}

class FileStreamGetNeedsEncryptionOnSaveTest_155 : public ::testing::Test {
protected:
  void SetUp() override {
    tmpPath_ = WriteTempFileWithContents("abc");

    GooFile *file = OpenGooFileForPath(tmpPath_);
    if (!file) {
      GTEST_SKIP() << "Could not open GooFile for temp path; GooFile::open API or environment may differ.";
    }

    // Construct a minimal dictionary object. Default Object is typically "null",
    // and is sufficient for a FileStream in Poppler for many tests.
    Object dict;

    // Use an "unlimited" stream with start=0. The length argument is only relevant when limited=true.
    // We avoid relying on internal behavior; we just need a valid instance to call public APIs.
    stream_ = std::make_unique<FileStream>(file, /*startA=*/0, /*limitedA=*/false, /*lengthA=*/0, std::move(dict));
  }

  void TearDown() override {
    stream_.reset();

    // Best-effort cleanup; ignore failures.
    // (On Windows, file may still be in use depending on implementation.)
    std::remove(tmpPath_.c_str());
  }

  std::unique_ptr<FileStream> stream_;
  std::string tmpPath_;
};

} // namespace

// ---- Tests ----

TEST_F(FileStreamGetNeedsEncryptionOnSaveTest_155, ReturnsUpdatedValueAfterSetTrue_155) {
  ASSERT_NE(stream_, nullptr);

  stream_->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(stream_->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamGetNeedsEncryptionOnSaveTest_155, ReturnsUpdatedValueAfterSetFalse_155) {
  ASSERT_NE(stream_, nullptr);

  stream_->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(stream_->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamGetNeedsEncryptionOnSaveTest_155, ToggleValueMultipleTimes_155) {
  ASSERT_NE(stream_, nullptr);

  stream_->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(stream_->getNeedsEncryptionOnSave());

  stream_->setNeedsEncryptionOnSave(false);
  EXPECT_FALSE(stream_->getNeedsEncryptionOnSave());

  stream_->setNeedsEncryptionOnSave(true);
  EXPECT_TRUE(stream_->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamGetNeedsEncryptionOnSaveTest_155, CallableOnConstInstance_155) {
  ASSERT_NE(stream_, nullptr);

  stream_->setNeedsEncryptionOnSave(true);

  const FileStream &cref = *stream_;
  EXPECT_TRUE(cref.getNeedsEncryptionOnSave());
}