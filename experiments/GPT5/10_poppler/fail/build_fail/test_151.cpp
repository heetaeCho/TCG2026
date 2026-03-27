// File: test_filestream_getpos_151.cc
// TEST_ID: 151
//
// Unit tests for FileStream::getPos() (black-box), using only observable behavior.

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Stream.h"
#include "Object.h"

// Poppler goo headers (path may vary by build, but these are typical)
#include "goo/GooFile.h"
#include "goo/gtypes.h"

namespace {

// --- Small RAII temp file helper ------------------------------------------------
class TempFile final {
public:
  explicit TempFile(const std::string &content) {
    // Create a unique-ish filename in current working directory.
    // (Avoid platform-specific temp APIs to keep this self-contained.)
    static int counter = 0;
    path_ = "poppler_filestream_test_" + std::to_string(++counter) + ".bin";

    std::ofstream out(path_, std::ios::binary);
    out.write(content.data(), static_cast<std::streamsize>(content.size()));
    out.close();
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

// --- GooFile open() adapter (tries common Poppler signatures) -------------------
//
// We do NOT mock GooFile (often non-virtual). Instead we open a real file.
// Poppler has had small API variations across versions; this adapter attempts
// a few common ones at compile time via SFINAE.

template <typename... Args>
using GooOpenExpr = decltype(GooFile::open(std::declval<Args>()...));

template <typename, typename = void>
struct has_open_cstr_gbool : std::false_type {};
template <typename T>
struct has_open_cstr_gbool<T, std::void_t<GooOpenExpr<const char *, GBool>>> : std::true_type {};

template <typename, typename = void>
struct has_open_cstr_bool : std::false_type {};
template <typename T>
struct has_open_cstr_bool<T, std::void_t<GooOpenExpr<const char *, bool>>> : std::true_type {};

template <typename, typename = void>
struct has_open_cstr_int : std::false_type {};
template <typename T>
struct has_open_cstr_int<T, std::void_t<GooOpenExpr<const char *, int>>> : std::true_type {};

template <typename, typename = void>
struct has_open_string_bool : std::false_type {};
template <typename T>
struct has_open_string_bool<T, std::void_t<GooOpenExpr<std::string, bool>>> : std::true_type {};

static std::unique_ptr<GooFile> OpenGooFileOrDie(const std::string &path) {
  GooFile *raw = nullptr;

  // Try: GooFile::open(const char*, GBool)
  if constexpr (has_open_cstr_gbool<GooFile>::value) {
    raw = GooFile::open(path.c_str(), gFalse);
  }
  // Try: GooFile::open(const char*, bool)
  else if constexpr (has_open_cstr_bool<GooFile>::value) {
    raw = GooFile::open(path.c_str(), false);
  }
  // Try: GooFile::open(const char*, int)
  else if constexpr (has_open_cstr_int<GooFile>::value) {
    // Some versions use an integer "mode" or "file descriptor" style argument.
    // We pass 0 as a conservative default (read-only).
    raw = GooFile::open(path.c_str(), 0);
  }
  // Try: GooFile::open(std::string, bool)
  else if constexpr (has_open_string_bool<GooFile>::value) {
    raw = GooFile::open(path, false);
  } else {
    // If none matched, fail clearly.
    // (This is still better than silently compiling invalid assumptions.)
    ADD_FAILURE() << "No compatible GooFile::open(...) signature found at compile time.";
    return nullptr;
  }

  if (!raw) {
    ADD_FAILURE() << "Failed to open GooFile for path: " << path;
    return nullptr;
  }
  return std::unique_ptr<GooFile>(raw);
}

static Object MakeNullDict() {
  // We avoid relying on any private/internal state; just create a default Object.
  // In Poppler, default Object is typically a null object, which is acceptable for dictA.
  Object obj;
  return obj;
}

class FileStreamGetPosTest_151 : public ::testing::Test {};

} // namespace

// -----------------------------------------------------------------------------

TEST_F(FileStreamGetPosTest_151, LookCharDoesNotChangePosition_151) {
  const std::string content = "Hello, FileStream!\n";
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  // Provide full length; limited=false means length is not expected to restrict.
  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/static_cast<Goffset>(content.size()),
                std::move(dict));

  const Goffset p0 = fs.getPos();

  const int c1 = fs.lookChar();
  (void)c1; // content-dependent, not asserted here.

  const Goffset p1 = fs.getPos();
  EXPECT_EQ(p1, p0);

  // Multiple lookChar calls should still not advance.
  const int c2 = fs.lookChar();
  (void)c2;
  const Goffset p2 = fs.getPos();
  EXPECT_EQ(p2, p0);
}

TEST_F(FileStreamGetPosTest_151, GetCharAdvancesPositionByOneWhenDataAvailable_151) {
  const std::string content = "ABCDE";
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/static_cast<Goffset>(content.size()),
                std::move(dict));

  // Read up to 3 chars and verify position increments by 1 each time data is returned.
  for (int i = 0; i < 3; ++i) {
    const Goffset before = fs.getPos();
    const int ch = fs.getChar();
    ASSERT_NE(ch, EOF) << "Expected data to be available at i=" << i;
    const Goffset after = fs.getPos();
    EXPECT_EQ(after, before + 1) << "Position should advance by 1 per getChar()";
  }
}

TEST_F(FileStreamGetPosTest_151, PositionDoesNotChangeAfterEOF_151) {
  const std::string content = "X";
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/static_cast<Goffset>(content.size()),
                std::move(dict));

  // Consume the only byte.
  ASSERT_NE(fs.getChar(), EOF);
  const Goffset atEnd = fs.getPos();

  // Next getChar should be EOF; position should remain stable.
  EXPECT_EQ(fs.getChar(), EOF);
  EXPECT_EQ(fs.getPos(), atEnd);

  // lookChar at EOF should not move position either.
  EXPECT_EQ(fs.lookChar(), EOF);
  EXPECT_EQ(fs.getPos(), atEnd);
}

TEST_F(FileStreamGetPosTest_151, RewindResetsPositionAndReadingRestarts_151) {
  const std::string content = "012345";
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/static_cast<Goffset>(content.size()),
                std::move(dict));

  // Capture initial position and first byte.
  const Goffset pStart = fs.getPos();
  const int first = fs.getChar();
  ASSERT_NE(first, EOF);

  // Advance a bit.
  ASSERT_NE(fs.getChar(), EOF);
  ASSERT_NE(fs.getChar(), EOF);
  const Goffset pMid = fs.getPos();
  ASSERT_GT(pMid, pStart);

  // Rewind should succeed and return to the initial position.
  EXPECT_TRUE(fs.rewind());
  EXPECT_EQ(fs.getPos(), pStart);

  // And reading should restart from the first byte.
  const int firstAgain = fs.getChar();
  EXPECT_EQ(firstAgain, first);
}

TEST_F(FileStreamGetPosTest_151, LimitedLengthStopsAtLengthBoundary_151) {
  const std::string content = "abcdef";
  const Goffset start = 1;   // start from 'b'
  const Goffset length = 3;  // allow 'b','c','d' only
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/start, /*limitedA=*/true,
                /*lengthA=*/length, std::move(dict));

  // We only assert observable boundaries:
  // - Position should never exceed start + length while reading within the limit.
  // - After reading length bytes, EOF should be observed (or at least no further progress).
  Goffset p0 = fs.getPos();

  int readCount = 0;
  for (; readCount < static_cast<int>(length); ++readCount) {
    const int ch = fs.getChar();
    ASSERT_NE(ch, EOF) << "Expected data within the limited length";
    const Goffset p = fs.getPos();
    EXPECT_LE(p, p0 + length) << "Position should not advance beyond the declared limit";
  }

  const Goffset pAtLimit = fs.getPos();
  EXPECT_LE(pAtLimit, p0 + length);

  // Next read should be EOF (or, minimally, position must not advance further).
  const int eofCh = fs.getChar();
  if (eofCh != EOF) {
    // If implementation chooses to return data anyway (unexpected for "limited"),
    // we still enforce that getPos does not advance beyond the limit.
    EXPECT_LE(fs.getPos(), p0 + length);
  } else {
    EXPECT_EQ(fs.getPos(), pAtLimit);
  }
}

TEST_F(FileStreamGetPosTest_151, EmptyFileHasStablePositionAndEOF_151) {
  const std::string content = "";
  TempFile tmp(content);
  auto file = OpenGooFileOrDie(tmp.path());
  ASSERT_NE(file, nullptr);

  Object dict = MakeNullDict();
  FileStream fs(file.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/0, std::move(dict));

  const Goffset p0 = fs.getPos();

  EXPECT_EQ(fs.lookChar(), EOF);
  EXPECT_EQ(fs.getPos(), p0);

  EXPECT_EQ(fs.getChar(), EOF);
  EXPECT_EQ(fs.getPos(), p0);
}