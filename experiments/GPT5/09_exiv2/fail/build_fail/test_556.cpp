// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 556
//
// Unit tests for Exiv2::FileIo::seek(int64_t, Position)
//
// Constraints honored:
// - Treat implementation as black box
// - Use only public interface (open/close/write/read/getb/tell/size/isopen/path/seek)
// - No private state access, no internal logic re-implementation

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class TempFile_556 {
 public:
  TempFile_556() {
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path();
    const fs::path name =
        fs::path("exiv2_fileio_seek_556_") / fs::path(std::to_string(::getpid()));

    // Create a reasonably unique file name (avoid collisions across repeated runs).
    for (int i = 0; i < 1000; ++i) {
      path_ = (dir / (std::string("exiv2_fileio_seek_556_") + std::to_string(::getpid()) + "_" +
                     std::to_string(i) + ".bin"))
                  .string();
      std::ifstream in(path_, std::ios::binary);
      if (!in.good()) break;
    }

    // Ensure the file exists.
    std::ofstream out(path_, std::ios::binary);
    out.close();
  }

  ~TempFile_556() {
    if (!path_.empty()) {
      std::error_code ec;
      std::filesystem::remove(path_, ec);
    }
  }

  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

static std::vector<Exiv2::byte> MakeBytes_556(size_t n) {
  std::vector<Exiv2::byte> v;
  v.reserve(n);
  for (size_t i = 0; i < n; ++i) v.push_back(static_cast<Exiv2::byte>(i & 0xFF));
  return v;
}

class FileIoSeekTest_556 : public ::testing::Test {
 protected:
  TempFile_556 tmp_;
};

}  // namespace

TEST_F(FileIoSeekTest_556, SeekBegSetsPositionAndAffectsReads_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));
  ASSERT_TRUE(io.isopen());

  const auto bytes = MakeBytes_556(10);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));
  ASSERT_EQ(bytes.size(), io.size());

  ASSERT_EQ(0, io.seek(0, Exiv2::BasicIo::beg));
  EXPECT_EQ(0u, io.tell());

  ASSERT_EQ(0, io.seek(5, Exiv2::BasicIo::beg));
  EXPECT_EQ(5u, io.tell());

  // Reading one byte after seeking should reflect the new position.
  const int b = io.getb();
  ASSERT_NE(-1, b);
  EXPECT_EQ(static_cast<int>(bytes[5]), b);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSeekTest_556, SeekCurMovesRelativeToCurrent_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));

  const auto bytes = MakeBytes_556(12);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));

  ASSERT_EQ(0, io.seek(2, Exiv2::BasicIo::beg));
  EXPECT_EQ(2u, io.tell());

  ASSERT_EQ(0, io.seek(3, Exiv2::BasicIo::cur));
  EXPECT_EQ(5u, io.tell());

  const int b = io.getb();
  ASSERT_NE(-1, b);
  EXPECT_EQ(static_cast<int>(bytes[5]), b);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSeekTest_556, SeekEndNegativeOffsetPositionsFromEnd_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));

  const auto bytes = MakeBytes_556(9);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));
  ASSERT_EQ(bytes.size(), io.size());

  // Seek to the last byte.
  ASSERT_EQ(0, io.seek(-1, Exiv2::BasicIo::end));
  EXPECT_EQ(bytes.size() - 1, io.tell());

  const int b = io.getb();
  ASSERT_NE(-1, b);
  EXPECT_EQ(static_cast<int>(bytes.back()), b);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSeekTest_556, SeekEndZeroMovesToEndPosition_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));

  const auto bytes = MakeBytes_556(7);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));

  ASSERT_EQ(0, io.seek(0, Exiv2::BasicIo::end));
  EXPECT_EQ(bytes.size(), io.tell());

  // At end-of-file: getb() may return -1 (EOF). We only assert it doesn't crash and is consistent
  // with being at EOF.
  const int b = io.getb();
  EXPECT_TRUE(b == -1 || b == static_cast<int>(bytes.back()));

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSeekTest_556, SeekWhenNotOpenReturnsNonZero_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_FALSE(io.isopen());

  // Observable error behavior: seek should fail when file isn't open.
  EXPECT_NE(0, io.seek(0, Exiv2::BasicIo::beg));
}

TEST_F(FileIoSeekTest_556, SeekBeyondEndIsEitherAllowedOrReturnsError_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));

  const auto bytes = MakeBytes_556(5);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));
  ASSERT_EQ(bytes.size(), io.size());

  const int rc = io.seek(100, Exiv2::BasicIo::beg);
  if (rc == 0) {
    // Many platforms allow seeking beyond EOF; if so, tell() should reflect it.
    EXPECT_EQ(100u, io.tell());
  } else {
    // If disallowed, ensure we observe an error return without assuming errno specifics.
    EXPECT_NE(0, rc);
  }

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSeekTest_556, SeekWithInvalidPositionDoesNotCrash_556) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("w+b"));

  const auto bytes = MakeBytes_556(3);
  ASSERT_EQ(bytes.size(), io.write(bytes.data(), bytes.size()));

  // Force an invalid enum value. We only assert call is safe and returns an int.
  const auto badPos = static_cast<Exiv2::BasicIo::Position>(999);
  const int rc = io.seek(0, badPos);

  // Black-box: it may succeed or fail depending on implementation/platform.
  // We just ensure it returns a value and leaves the object usable.
  (void)rc;
  EXPECT_TRUE(io.isopen());

  EXPECT_EQ(0, io.close());
}