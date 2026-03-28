// File: gfile_gftell_test_43.cpp
// Unit tests for ./TestProjects/poppler/goo/gfile.cc (Gftell)

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <vector>

// Prefer including the public header if available in the build.
// If your build exposes a different include path, adjust as needed.
#include "goo/gfile.h"

// Some Poppler builds use Goffset typedefs; if not visible via goo/gfile.h,
// you may need to include the header that defines it.
#ifndef Goffset
// If Goffset isn't defined by included headers, fail clearly rather than guessing.
#error "Goffset is not defined. Please include the Poppler header that defines Goffset (e.g., goo/gtypes.h) before including this test."
#endif

namespace {

class GfileGftellTest_43 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (f_) {
      std::fclose(f_);
      f_ = nullptr;
    }
  }

  FILE* OpenTempFile() {
#if defined(_WIN32)
    // tmpfile() is supported on Windows too, but may be restricted by policies.
    // Use it anyway; tests will fail cleanly if it returns nullptr.
#endif
    FILE* f = std::tmpfile();
    return f;
  }

  void WriteBytes(FILE* f, size_t n) {
    std::vector<unsigned char> buf(n, 0xAB);
    const size_t written = std::fwrite(buf.data(), 1, buf.size(), f);
    ASSERT_EQ(written, buf.size());
  }

  FILE* f_ = nullptr;
};

}  // namespace

// Normal operation: on a freshly opened empty file, position should be 0.
TEST_F(GfileGftellTest_43, ReturnsZeroForEmptyFileAtStart_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  // Ensure starting position is at beginning.
  ASSERT_EQ(std::fseek(f_, 0, SEEK_SET), 0);

  const Goffset pos = Gftell(f_);
  EXPECT_EQ(pos, static_cast<Goffset>(0));
}

// Normal operation: after writing N bytes, position should advance by N.
TEST_F(GfileGftellTest_43, ReturnsCurrentPositionAfterWrite_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  ASSERT_EQ(std::fseek(f_, 0, SEEK_SET), 0);

  constexpr size_t kN = 17;
  WriteBytes(f_, kN);

  const Goffset pos = Gftell(f_);
  EXPECT_EQ(pos, static_cast<Goffset>(kN));
}

// Boundary-ish: seek to beginning after writing and verify position is 0.
TEST_F(GfileGftellTest_43, ReturnsZeroAfterSeekToBeginning_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  WriteBytes(f_, 64);
  ASSERT_EQ(std::fseek(f_, 0, SEEK_SET), 0);

  const Goffset pos = Gftell(f_);
  EXPECT_EQ(pos, static_cast<Goffset>(0));
}

// Normal operation: seek to end and verify position equals file size written.
TEST_F(GfileGftellTest_43, ReturnsFileSizeAfterSeekToEnd_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  constexpr size_t kSize = 1234;
  WriteBytes(f_, kSize);

  ASSERT_EQ(std::fflush(f_), 0);
  ASSERT_EQ(std::fseek(f_, 0, SEEK_END), 0);

  const Goffset pos = Gftell(f_);
  EXPECT_EQ(pos, static_cast<Goffset>(kSize));
}

// Boundary condition: seek to a non-trivial offset within the file and verify.
TEST_F(GfileGftellTest_43, ReturnsOffsetAfterSeekToMiddle_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  constexpr size_t kSize = 4096;
  constexpr long kMid = 2000;

  WriteBytes(f_, kSize);
  ASSERT_EQ(std::fflush(f_), 0);
  ASSERT_EQ(std::fseek(f_, kMid, SEEK_SET), 0);

  const Goffset pos = Gftell(f_);
  EXPECT_EQ(pos, static_cast<Goffset>(kMid));
}

// Error case (observable): calling Gftell on a stream in an error state may return -1.
// We avoid undefined behavior like using a closed FILE*; instead we induce an error by
// attempting an invalid seek and then check whether Gftell reports an error position.
// Note: C stdlib behavior may vary; this test is written defensively.
TEST_F(GfileGftellTest_43, ReturnsMinusOneAfterInvalidSeekIfStreamError_43) {
  f_ = OpenTempFile();
  ASSERT_NE(f_, nullptr);

  // Attempt an invalid seek from SEEK_SET with a negative offset.
  // fseek should fail (non-zero) on conforming implementations.
  const int seek_rc = std::fseek(f_, -1, SEEK_SET);
  if (seek_rc == 0) {
    // If the platform accepts this (unlikely), the stream isn't in error; skip the check.
    GTEST_SKIP() << "Platform accepted negative SEEK_SET offset; cannot validate error behavior.";
  }

  // If the library reports error, ftell/Gftell commonly returns -1.
  // We don't assume it MUST, but we assert that it does not return a valid non-negative position.
  const Goffset pos = Gftell(f_);
  EXPECT_LT(pos, static_cast<Goffset>(0));
}