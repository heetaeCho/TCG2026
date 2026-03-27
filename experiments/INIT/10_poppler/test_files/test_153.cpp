// File: test_filestream_getunfilteredchar_153.cpp
//
// Unit tests for FileStream::getUnfilteredChar() from poppler/Stream.h
// TEST_ID: 153

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "poppler/Stream.h"

// Many Poppler builds keep GooFile under "goo/GooFile.h".
#include "goo/GooFile.h"

namespace {

class FileStreamTest_153 : public ::testing::Test {
protected:
  static std::filesystem::path MakeTempPath(const std::string &stem) {
    const auto dir = std::filesystem::temp_directory_path();
    // Basic uniqueness without relying on platform-specific mkstemp.
    const auto unique =
        stem + "_" + std::to_string(static_cast<unsigned long long>(std::rand())) + ".bin";
    return dir / unique;
  }

  static void WriteBytes(const std::filesystem::path &p, const std::vector<unsigned char> &bytes) {
    std::ofstream os(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.good());
    if (!bytes.empty()) {
      os.write(reinterpret_cast<const char *>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    }
    os.close();
    ASSERT_TRUE(std::filesystem::exists(p));
  }

  // --- Small compatibility helpers (avoid depending on one exact Poppler API shape). ---

  // Create an Object suitable for passing as dictA (best-effort: null is always acceptable).
  static Object MakeNullDictObject() {
    Object obj;

    // Prefer explicit initNull() if available.
#if defined(__cpp_if_constexpr)
    // We can’t use requires() in C++17, so we do a simple (non-failing) approach:
    // If initNull exists, this line compiles; otherwise it will be removed by the preprocessor? No.
    // So we use a classic overload trick below instead.
#endif
    struct InitNullHelper {
      static void Do(Object &o, int) { o.initNull(); }
      static void Do(Object &, ...) {
        // If Object defaults to a usable null object, leave as-is.
      }
    };
    InitNullHelper::Do(obj, 0);
    return obj;
  }

  // Open a GooFile with best-effort handling of common signatures.
  static GooFile *OpenGooFileRaw(const std::string &path) {
    // Common in Poppler: static GooFile *open(const char *fileName, GooString *ownerPassword=nullptr,
    // ...). But signatures vary a bit. We'll try the simplest common ones via overload sets.

    // 1) GooFile::open(const char*)
    struct OpenHelper {
      static GooFile *Do(const std::string &p, int) { return GooFile::open(p.c_str()); }
      static GooFile *Do(const std::string &p, long) {
        // 2) GooFile::open(const GooString*)
        GooString gs(p.c_str());
        return GooFile::open(&gs);
      }
      static GooFile *Do(const std::string &p, ...) {
        // If your build has a different GooFile::open signature, adapt here.
        // Returning nullptr will make tests fail clearly.
        (void)p;
        return nullptr;
      }
    };

    // Try the most likely overload first.
    if (GooFile *f = OpenHelper::Do(path, 0)) {
      return f;
    }
    return OpenHelper::Do(path, 0L);
  }

  static std::unique_ptr<FileStream> MakeFileStreamFromPath(const std::filesystem::path &p) {
    const auto size = static_cast<Goffset>(std::filesystem::file_size(p));
    GooFile *file = OpenGooFileRaw(p.string());
    EXPECT_NE(file, nullptr) << "Failed to open GooFile for temp path: " << p.string();

    Object dict = MakeNullDictObject();

    // FileStream is expected to own the GooFile* in many Poppler configurations; we do not delete it.
    auto fs = std::make_unique<FileStream>(
        file,
        /*startA=*/static_cast<Goffset>(0),
        /*limitedA=*/false,
        /*lengthA=*/size,
        std::move(dict));

    return fs;
  }
};

} // namespace

TEST_F(FileStreamTest_153, GetUnfilteredCharMatchesGetCharAtSamePosition_153) {
  const auto p = MakeTempPath("poppler_filestream_153_a");
  WriteBytes(p, {0x01, 0x02, 0x7f, 0x00});

  auto fs = MakeFileStreamFromPath(p);
  ASSERT_NE(fs, nullptr);

  ASSERT_TRUE(fs->rewind());

  const int c1 = fs->getChar();

  ASSERT_TRUE(fs->rewind());
  const int c2 = fs->getUnfilteredChar();

  EXPECT_EQ(c1, c2);

  // Cleanup
  fs->close();
  std::error_code ec;
  std::filesystem::remove(p, ec);
}

TEST_F(FileStreamTest_153, GetUnfilteredCharAdvancesLikeGetChar_153) {
  const auto p = MakeTempPath("poppler_filestream_153_b");
  WriteBytes(p, {'A', 'B', 'C'});

  auto fs = MakeFileStreamFromPath(p);
  ASSERT_NE(fs, nullptr);

  ASSERT_TRUE(fs->rewind());

  const int first = fs->getUnfilteredChar();
  const int second = fs->getChar();

  EXPECT_EQ(first, static_cast<unsigned char>('A'));
  EXPECT_EQ(second, static_cast<unsigned char>('B'));

  fs->close();
  std::error_code ec;
  std::filesystem::remove(p, ec);
}

TEST_F(FileStreamTest_153, EmptyFileReturnsEOFForGetCharAndGetUnfilteredChar_153) {
  const auto p = MakeTempPath("poppler_filestream_153_empty");
  WriteBytes(p, {}); // empty

  auto fs = MakeFileStreamFromPath(p);
  ASSERT_NE(fs, nullptr);

  ASSERT_TRUE(fs->rewind());
  const int a = fs->getChar();

  ASSERT_TRUE(fs->rewind());
  const int b = fs->getUnfilteredChar();

  // Poppler streams typically use EOF (-1) when no more data is available.
  EXPECT_EQ(a, -1);
  EXPECT_EQ(b, -1);

  fs->close();
  std::error_code ec;
  std::filesystem::remove(p, ec);
}

TEST_F(FileStreamTest_153, VirtualDispatchViaBaseStreamCallsSameUnderlyingRead_153) {
  const auto p = MakeTempPath("poppler_filestream_153_poly");
  WriteBytes(p, {0x10, 0x20});

  auto fs = MakeFileStreamFromPath(p);
  ASSERT_NE(fs, nullptr);

  BaseStream *bs = fs.get();
  ASSERT_NE(bs, nullptr);

  ASSERT_TRUE(fs->rewind());
  const int u = bs->getUnfilteredChar();

  ASSERT_TRUE(fs->rewind());
  const int c = bs->getChar();

  EXPECT_EQ(u, c);

  fs->close();
  std::error_code ec;
  std::filesystem::remove(p, ec);
}