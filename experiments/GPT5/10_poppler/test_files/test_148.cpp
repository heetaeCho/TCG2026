// File: FileStream_getKind_tests_148.cpp
// The TEST_ID is 148

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <utility>

#include "poppler/Stream.h"

// Poppler headers vary by build; Stream.h often pulls these in already,
// but include guards keep this safe if they exist.
#include "poppler/Object.h"
#include "poppler/goo/GooFile.h"

namespace {

// ---- GooFile opener helper (handles minor signature differences across versions) ----

template <typename = void>
struct GooFileOpen1 {
  static GooFile *open(const std::string &) { return nullptr; }
};

template <>
struct GooFileOpen1<std::void_t<decltype(GooFile::open(static_cast<const char *>(nullptr)))>> {
  static GooFile *open(const std::string &path) { return GooFile::open(path.c_str()); }
};

template <typename = void>
struct GooFileOpen2 {
  static GooFile *open(const std::string &) { return nullptr; }
};

template <>
struct GooFileOpen2<
    std::void_t<decltype(GooFile::open(static_cast<const char *>(nullptr), static_cast<const char *>(nullptr)))>> {
  static GooFile *open(const std::string &path) { return GooFile::open(path.c_str(), nullptr); }
};

template <typename = void>
struct GooFileOpen3 {
  static GooFile *open(const std::string &) { return nullptr; }
};

template <>
struct GooFileOpen3<std::void_t<decltype(GooFile::open(static_cast<const char *>(nullptr), bool{}))>> {
  static GooFile *open(const std::string &path) { return GooFile::open(path.c_str(), false); }
};

static std::unique_ptr<GooFile> OpenGooFileAny(const std::string &path)
{
  if (auto *f = GooFileOpen1<>::open(path)) {
    return std::unique_ptr<GooFile>(f);
  }
  if (auto *f = GooFileOpen2<>::open(path)) {
    return std::unique_ptr<GooFile>(f);
  }
  if (auto *f = GooFileOpen3<>::open(path)) {
    return std::unique_ptr<GooFile>(f);
  }
  return nullptr;
}

static std::string WriteTempFile(const std::string &contents)
{
  // Use a simple temp filename pattern (kept in CWD to avoid platform-specific tmp APIs).
  // The test cleans it up in TearDown.
  std::string path = "poppler_filestream_test_148_tmp.bin";
  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  os.close();
  return path;
}

} // namespace

class FileStreamGetKindTest_148 : public ::testing::Test {
protected:
  void SetUp() override
  {
    tempPath_ = WriteTempFile("hello");
    gooFile_ = OpenGooFileAny(tempPath_);
    ASSERT_NE(gooFile_, nullptr) << "Failed to open GooFile for test input";

    // Construct FileStream with a small range; we only need a valid object.
    Object dict; // default/empty dictionary object
    stream_ = std::make_unique<FileStream>(gooFile_.get(),
                                          static_cast<Goffset>(0),
                                          /*limitedA=*/false,
                                          static_cast<Goffset>(0),
                                          std::move(dict));
  }

  void TearDown() override
  {
    // Be defensive: close may be a no-op or may depend on state.
    if (stream_) {
      EXPECT_NO_THROW(stream_->close());
    }
    stream_.reset();
    gooFile_.reset();
    if (!tempPath_.empty()) {
      std::remove(tempPath_.c_str());
    }
  }

  std::string tempPath_;
  std::unique_ptr<GooFile> gooFile_;
  std::unique_ptr<FileStream> stream_;
};

TEST_F(FileStreamGetKindTest_148, ReturnsStrFile_148)
{
  ASSERT_NE(stream_, nullptr);
  EXPECT_EQ(stream_->getKind(), strFile);
}

TEST_F(FileStreamGetKindTest_148, ReturnsStrFileThroughBaseStreamPolymorphism_148)
{
  ASSERT_NE(stream_, nullptr);

  BaseStream *asBase = stream_.get();
  ASSERT_NE(asBase, nullptr);

  EXPECT_EQ(asBase->getKind(), strFile);
}

TEST_F(FileStreamGetKindTest_148, MultipleCallsAreStable_148)
{
  ASSERT_NE(stream_, nullptr);

  const StreamKind k1 = stream_->getKind();
  const StreamKind k2 = stream_->getKind();
  const StreamKind k3 = stream_->getKind();

  EXPECT_EQ(k1, strFile);
  EXPECT_EQ(k2, strFile);
  EXPECT_EQ(k3, strFile);
}

TEST_F(FileStreamGetKindTest_148, GetKindDoesNotThrowAfterClose_148)
{
  ASSERT_NE(stream_, nullptr);

  EXPECT_NO_THROW(stream_->close());
  EXPECT_NO_THROW({
    StreamKind k = stream_->getKind();
    EXPECT_EQ(k, strFile);
  });
}

TEST_F(FileStreamGetKindTest_148, CopyPreservesKindIfCopySucceeds_148)
{
  ASSERT_NE(stream_, nullptr);

  std::unique_ptr<BaseStream> cpy;
  EXPECT_NO_THROW({ cpy = stream_->copy(); });

  // Observable behavior only: if copy is supported and returns non-null,
  // it should still report a kind (and FileStream's kind is strFile).
  if (cpy) {
    EXPECT_EQ(cpy->getKind(), strFile);
  }
}

TEST_F(FileStreamGetKindTest_148, ConstGetKindReturnsStrFile_148)
{
  ASSERT_NE(stream_, nullptr);

  const FileStream &cs = *stream_;
  EXPECT_EQ(cs.getKind(), strFile);
}