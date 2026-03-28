// File: FileStream_getChar_149_test.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "goo/GooFile.h"

// ----------------------
// Helpers (test-only)
// ----------------------
namespace {

std::string writeTempFile_149(const std::vector<unsigned char> &bytes) {
#if defined(_WIN32)
  char tmpName[L_tmpnam_s]{};
  EXPECT_EQ(tmpnam_s(tmpName, sizeof(tmpName)), 0);
  std::string path = std::string(tmpName) + "_poppler_filestream_149.bin";
#else
  char tmpName[] = "/tmp/poppler_filestream_149_XXXXXX";
  int fd = mkstemp(tmpName);
  EXPECT_NE(fd, -1);
  close(fd);
  std::string path(tmpName);
#endif

  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  EXPECT_TRUE(os.is_open());
  os.write(reinterpret_cast<const char *>(bytes.data()),
           static_cast<std::streamsize>(bytes.size()));
  os.close();
  return path;
}

void removeFile_149(const std::string &path) {
  (void)std::remove(path.c_str());
}

// ---- GooFile::open() adapter (handles common Poppler signatures) ----
template <typename T>
struct is_unique_ptr : std::false_type {};
template <typename T, typename D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {};

template <typename Ret>
std::unique_ptr<GooFile> wrapOpenResult_149(Ret &&r) {
  if constexpr (is_unique_ptr<std::decay_t<Ret>>::value) {
    return std::forward<Ret>(r);
  } else {
    // Assume raw pointer (GooFile*) or compatible
    return std::unique_ptr<GooFile>(std::forward<Ret>(r));
  }
}

// Overload set tries a few likely GooFile::open(...) signatures using SFINAE.
template <typename = void>
struct GooFileOpener_149 {
  static std::unique_ptr<GooFile> open(const std::string &) {
    // If you hit this, adjust the overloads below to match your Poppler GooFile API.
    ADD_FAILURE() << "No matching GooFile::open(...) overload found for this Poppler version.";
    return nullptr;
  }
};

template <>
struct GooFileOpener_149<std::void_t<decltype(GooFile::open((const char *)nullptr))>> {
  static std::unique_ptr<GooFile> open(const std::string &path) {
    return wrapOpenResult_149(GooFile::open(path.c_str()));
  }
};

template <>
struct GooFileOpener_149<std::void_t<decltype(GooFile::open((const char *)nullptr, nullptr))>> {
  static std::unique_ptr<GooFile> open(const std::string &path) {
    return wrapOpenResult_149(GooFile::open(path.c_str(), nullptr));
  }
};

// Fallback chooser: prefer 2-arg if available, else 1-arg if available.
std::unique_ptr<GooFile> openGooFile_149(const std::string &path) {
  // Try 2-arg first if it compiles (specialization exists), else 1-arg.
  // We do this by checking which specialization is viable via decltype tricks.
  if constexpr (std::is_same_v<decltype(GooFile::open((const char *)nullptr, nullptr)), decltype(GooFile::open((const char *)nullptr, nullptr))>) {
    // If 2-arg exists, the specialization above is selected and this compiles.
    return GooFileOpener_149<std::void_t<decltype(GooFile::open((const char *)nullptr, nullptr))>>::open(path);
  } else {
    return GooFileOpener_149<std::void_t<decltype(GooFile::open((const char *)nullptr))>>::open(path);
  }
}

// ---- Object null/default adapter ----
Object makeNullDict_149() {
  // Most Poppler builds default-construct to null; if not, this still produces a valid Object.
  return Object();
}

}  // namespace

// ----------------------
// Tests
// ----------------------

class FileStreamGetCharTest_149 : public ::testing::Test {
protected:
  void TearDown() override {
    if (!tmpPath.empty()) removeFile_149(tmpPath);
  }

  std::string tmpPath;
};

TEST_F(FileStreamGetCharTest_149, EmptyFileReturnsEOF_149) {
  tmpPath = writeTempFile_149({});
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  // limitedA=true, lengthA=0 => should be immediately at end for observable reads.
  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/true, /*lengthA=*/0, makeNullDict_149());
  EXPECT_EQ(fs.getChar(), EOF);
  // Repeated reads remain EOF (observable behavior).
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, ReadsBytesSequentiallyAndThenEOF_149) {
  const std::vector<unsigned char> bytes = {0x00, 0x01, 0x7f, 0x80, 0xff};
  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/true,
                /*lengthA=*/static_cast<Goffset>(bytes.size()), makeNullDict_149());

  for (size_t i = 0; i < bytes.size(); ++i) {
    const int c = fs.getChar();
    ASSERT_NE(c, EOF);
    EXPECT_EQ(c, static_cast<int>(bytes[i])) << "at index " << i;
  }
  EXPECT_EQ(fs.getChar(), EOF);
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, DoesNotSignExtendHighBitBytes_149) {
  const std::vector<unsigned char> bytes = {0x80, 0xff};
  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/true,
                /*lengthA=*/static_cast<Goffset>(bytes.size()), makeNullDict_149());

  EXPECT_EQ(fs.getChar(), 0x80);
  EXPECT_EQ(fs.getChar(), 0xff);
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, RespectsStartOffset_149) {
  const std::vector<unsigned char> bytes = {10, 11, 12, 13, 14, 15};
  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  const Goffset start = 3;  // start at value 13
  const Goffset len = 2;    // read 13, 14 then EOF
  FileStream fs(gooFile.get(), /*startA=*/start, /*limitedA=*/true, /*lengthA=*/len, makeNullDict_149());

  EXPECT_EQ(fs.getChar(), 13);
  EXPECT_EQ(fs.getChar(), 14);
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, LimitedLengthShorterThanFile_149) {
  const std::vector<unsigned char> bytes = {1, 2, 3, 4, 5, 6, 7, 8};
  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  const Goffset len = 3;
  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/true, /*lengthA=*/len, makeNullDict_149());

  EXPECT_EQ(fs.getChar(), 1);
  EXPECT_EQ(fs.getChar(), 2);
  EXPECT_EQ(fs.getChar(), 3);
  EXPECT_EQ(fs.getChar(), EOF);

  // Even though file has more bytes, observable reads should stay at EOF for the limited stream.
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, ReadsAcrossInternalBufferBoundary_149) {
  // fileStreamBufSize is known as 16384 from provided context; exercise crossing that boundary
  // without relying on private state. We only verify that sequential getChar() yields the bytes.
  constexpr size_t kBuf = 16384;
  const size_t total = kBuf + 32;

  std::vector<unsigned char> bytes(total);
  for (size_t i = 0; i < total; ++i) {
    bytes[i] = static_cast<unsigned char>(i & 0xff);
  }

  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/true,
                /*lengthA=*/static_cast<Goffset>(bytes.size()), makeNullDict_149());

  // Read up to just before the boundary.
  for (size_t i = 0; i < kBuf - 1; ++i) {
    int c = fs.getChar();
    ASSERT_NE(c, EOF);
    ASSERT_EQ(c, static_cast<int>(bytes[i])) << "at index " << i;
  }

  // Read the boundary byte and a few after.
  for (size_t i = kBuf - 1; i < kBuf + 8; ++i) {
    int c = fs.getChar();
    ASSERT_NE(c, EOF);
    EXPECT_EQ(c, static_cast<int>(bytes[i])) << "at index " << i;
  }

  // Drain remainder quickly and confirm EOF at the end.
  for (size_t i = kBuf + 8; i < total; ++i) {
    int c = fs.getChar();
    ASSERT_NE(c, EOF);
    ASSERT_EQ(c, static_cast<int>(bytes[i])) << "at index " << i;
  }
  EXPECT_EQ(fs.getChar(), EOF);
}

TEST_F(FileStreamGetCharTest_149, UnboundedReadsToEOFWhenLimitedFalse_149) {
  const std::vector<unsigned char> bytes = {9, 8, 7, 6};
  tmpPath = writeTempFile_149(bytes);
  auto gooFile = openGooFile_149(tmpPath);
  ASSERT_TRUE(gooFile);

  // When limitedA=false, lengthA should not truncate observable reads (we don't assume more than that).
  FileStream fs(gooFile.get(), /*startA=*/0, /*limitedA=*/false,
                /*lengthA=*/0, makeNullDict_149());

  EXPECT_EQ(fs.getChar(), 9);
  EXPECT_EQ(fs.getChar(), 8);
  EXPECT_EQ(fs.getChar(), 7);
  EXPECT_EQ(fs.getChar(), 6);
  EXPECT_EQ(fs.getChar(), EOF);
}