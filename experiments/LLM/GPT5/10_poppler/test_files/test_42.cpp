// File: test_gfile_gfseek_42.cc
//
// Unit tests for Gfseek() wrapper in ./TestProjects/poppler/goo/gfile.cc
// Constraints honored: black-box testing via observable FILE* behavior only.

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>

#if __has_include("goo/gfile.h")
#include "goo/gfile.h"
#elif __has_include("gfile.h")
#include "gfile.h"
#else
// If your build exposes Poppler headers differently, adjust includes accordingly.
#include "../goo/gfile.h"
#endif

namespace {

class GfseekTest_42 : public ::testing::Test {
protected:
  void SetUp() override {
    file_ = std::tmpfile();
    ASSERT_NE(file_, nullptr) << "tmpfile() failed; cannot test Gfseek";

    const char* kData = "abcdefghijklmnopqrstuvwxyz";
    const size_t n = std::strlen(kData);
    ASSERT_EQ(std::fwrite(kData, 1, n, file_), n);
    ASSERT_EQ(std::fflush(file_), 0);

    // Start from a known position (beginning).
    ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_SET), 0);
  }

  void TearDown() override {
    if (file_) {
      std::fclose(file_);
      file_ = nullptr;
    }
  }

  static long long Tell(FILE* f) {
#if defined(HAVE_FTELLO) || defined(__APPLE__) || defined(__linux__)
    return static_cast<long long>(ftello(f));
#else
    return static_cast<long long>(std::ftell(f));
#endif
  }

  static int ReadByte(FILE* f) {
    return std::fgetc(f);
  }

  FILE* file_ = nullptr;
};

TEST_F(GfseekTest_42, SeekFromStartReadsExpectedByte_42) {
  // Seek to offset 5 -> 'f'
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(5), SEEK_SET), 0);
  const int c = ReadByte(file_);
  ASSERT_NE(c, EOF);
  EXPECT_EQ(static_cast<char>(c), 'f');
}

TEST_F(GfseekTest_42, SeekCurForwardThenBackwardReadsExpectedByte_42) {
  // Start at 0, go forward 10 -> 'k'
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(10), SEEK_SET), 0);
  int c = ReadByte(file_);
  ASSERT_NE(c, EOF);
  EXPECT_EQ(static_cast<char>(c), 'k');

  // We consumed one byte ('k'), so we're now at position 11.
  // Move back 2 -> should land at position 9 -> 'j' is at 9? (0-based: 9 = 'j')
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(-2), SEEK_CUR), 0);
  c = ReadByte(file_);
  ASSERT_NE(c, EOF);
  EXPECT_EQ(static_cast<char>(c), 'j');
}

TEST_F(GfseekTest_42, SeekFromEndNegativeOffsetReadsLastByte_42) {
  // Seek to last byte (end - 1) -> 'z'
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(-1), SEEK_END), 0);
  const int c = ReadByte(file_);
  ASSERT_NE(c, EOF);
  EXPECT_EQ(static_cast<char>(c), 'z');
}

TEST_F(GfseekTest_42, BoundarySeekToStartAndEndPositions_42) {
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_SET), 0);
  EXPECT_EQ(Tell(file_), 0);

  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_END), 0);
  const long long endPos = Tell(file_);
  // Data length is 26; end position should be >= 26 (exact for normal files).
  EXPECT_GE(endPos, 26);
}

TEST_F(GfseekTest_42, SeekBeyondEndThenWriteExtendsFile_42) {
  // Go to end, record size
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_END), 0);
  const long long origEnd = Tell(file_);
  ASSERT_GE(origEnd, 0);

  // Seek 10 bytes beyond end and write a byte; many stdio backends extend the file.
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(origEnd + 10), SEEK_SET), 0);
  const unsigned char marker = 0xAB;
  ASSERT_EQ(std::fwrite(&marker, 1, 1, file_), 1u);
  ASSERT_EQ(std::fflush(file_), 0);

  // New end should be at least origEnd + 11.
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_END), 0);
  const long long newEnd = Tell(file_);
  EXPECT_GE(newEnd, origEnd + 11);
}

TEST_F(GfseekTest_42, ErrorInvalidWhenceReturnsNonZero_42) {
  errno = 0;
  const int rc = Gfseek(file_, static_cast<Goffset>(0), 123456);  // invalid whence
  EXPECT_NE(rc, 0);

  // errno is observable but platform-dependent; at least ensure it doesn't look like success.
  // (Some platforms may leave errno unchanged, so don't assert exact value.)
}

TEST_F(GfseekTest_42, ErrorNegativeOffsetFromStartFails_42) {
  errno = 0;
  const int rc = Gfseek(file_, static_cast<Goffset>(-1), SEEK_SET);
  EXPECT_NE(rc, 0);

  // If it fails, position should remain valid (not EOF). We can still seek to 0 and read.
  ASSERT_EQ(Gfseek(file_, static_cast<Goffset>(0), SEEK_SET), 0);
  const int c = ReadByte(file_);
  ASSERT_NE(c, EOF);
  EXPECT_EQ(static_cast<char>(c), 'a');
}

}  // namespace