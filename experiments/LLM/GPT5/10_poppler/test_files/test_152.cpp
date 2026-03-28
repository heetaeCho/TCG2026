// File: FileStream_getStart_tests_152.cpp
// TEST_ID: 152

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <utility>

#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "goo/gfile.h"

namespace {

class TempFile final {
public:
  explicit TempFile(const std::string &contents) {
    // Use tmpnam for broad portability in test environments.
    // (This is test-only; the codebase may already have better helpers.)
    char buf[L_tmpnam];
    const char *name = std::tmpnam(buf);
    path_ = name ? std::string(name) : std::string("filestream_test_152.tmp");

    std::ofstream ofs(path_, std::ios::binary);
    ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    ofs.close();
  }

  ~TempFile() {
    if (!path_.empty()) {
      std::remove(path_.c_str());
    }
  }

  const std::string &path() const { return path_; }

private:
  std::string path_;
};

class FileStreamTest_152 : public ::testing::Test {
protected:
  static std::unique_ptr<GooFile> OpenGooFileOrFail(const std::string &path) {
    // Poppler commonly provides GooFile::open overloads for const char* and std::string.
    // Prefer const char* to minimize assumptions.
    std::unique_ptr<GooFile> f(GooFile::open(path.c_str()));
    EXPECT_TRUE(f != nullptr);
    return f;
  }
};

} // namespace

TEST_F(FileStreamTest_152, GetStartReturnsConstructorStart_152) {
  TempFile tmp("hello");
  auto file = OpenGooFileOrFail(tmp.path());
  ASSERT_TRUE(file != nullptr);

  const Goffset kStart = 123;
  const bool kLimited = false;
  const Goffset kLength = 0;

  Object dict; // Default-constructed; treated as an opaque payload for this test.
  FileStream stream(file.get(), kStart, kLimited, kLength, std::move(dict));

  EXPECT_EQ(stream.getStart(), kStart);
}

TEST_F(FileStreamTest_152, GetStartHandlesZeroStart_152) {
  TempFile tmp("data");
  auto file = OpenGooFileOrFail(tmp.path());
  ASSERT_TRUE(file != nullptr);

  const Goffset kStart = 0;
  const bool kLimited = false;
  const Goffset kLength = 0;

  Object dict;
  FileStream stream(file.get(), kStart, kLimited, kLength, std::move(dict));

  EXPECT_EQ(stream.getStart(), static_cast<Goffset>(0));
}

TEST_F(FileStreamTest_152, GetStartHandlesNegativeAndLargeStartValues_152) {
  TempFile tmp("abcdefg");
  auto file = OpenGooFileOrFail(tmp.path());
  ASSERT_TRUE(file != nullptr);

  {
    const Goffset kStart = static_cast<Goffset>(-7);
    Object dict;
    FileStream stream(file.get(), kStart, /*limitedA=*/false, /*lengthA=*/0, std::move(dict));
    EXPECT_EQ(stream.getStart(), kStart);
  }

  {
    // Use a "large" but not extreme value to avoid platform-specific overflows.
    const Goffset kStart = static_cast<Goffset>(1) << 40;
    Object dict;
    FileStream stream(file.get(), kStart, /*limitedA=*/false, /*lengthA=*/0, std::move(dict));
    EXPECT_EQ(stream.getStart(), kStart);
  }
}