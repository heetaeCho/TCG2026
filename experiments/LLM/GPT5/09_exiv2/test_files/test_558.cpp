// File: test_fileio_size_558.cpp
// Unit tests for Exiv2::FileIo::size() based strictly on observable behavior.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

class TempFile {
 public:
  explicit TempFile(std::vector<unsigned char> content = {}) {
    path_ = MakeUniquePath();
    if (!content.empty()) {
      std::ofstream os(path_, std::ios::binary);
      os.write(reinterpret_cast<const char*>(content.data()),
               static_cast<std::streamsize>(content.size()));
    } else {
      // Create empty file
      std::ofstream os(path_, std::ios::binary);
    }
  }

  ~TempFile() {
    std::error_code ec;
    fs::remove(path_, ec);
  }

  const std::string& path() const { return path_; }

 private:
  static std::string MakeUniquePath() {
    const fs::path dir = fs::temp_directory_path();
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist;

    for (int i = 0; i < 100; ++i) {
      fs::path candidate =
          dir / ("exiv2_fileio_size_558_" + std::to_string(dist(gen)) + ".bin");
      std::error_code ec;
      if (!fs::exists(candidate, ec)) {
        return candidate.string();
      }
    }
    // Fallback: let the OS decide via tmpnam-style (still fine for tests)
    fs::path fallback = dir / "exiv2_fileio_size_558_fallback.bin";
    return fallback.string();
  }

  std::string path_;
};

class FileIoSizeTest_558 : public ::testing::Test {
 protected:
  static std::vector<unsigned char> MakePattern(size_t n) {
    std::vector<unsigned char> v(n);
    for (size_t i = 0; i < n; ++i) v[i] = static_cast<unsigned char>(i & 0xFF);
    return v;
  }
};

}  // namespace

TEST_F(FileIoSizeTest_558, EmptyFileReturnsZero_558) {
  TempFile tf(/*content=*/{});
  Exiv2::FileIo io(tf.path());

  const size_t sz = io.size();
  EXPECT_EQ(0u, sz);
}

TEST_F(FileIoSizeTest_558, ExistingFileReturnsExactSize_558) {
  const auto content = FileIoSizeTest_558::MakePattern(37);
  TempFile tf(content);
  Exiv2::FileIo io(tf.path());

  const size_t sz = io.size();
  EXPECT_EQ(content.size(), sz);
}

TEST_F(FileIoSizeTest_558, NonexistentPathReturnsMaxSizeT_558) {
  const fs::path missing =
      fs::temp_directory_path() / "exiv2_fileio_size_558_missing_DO_NOT_CREATE.bin";
  std::error_code ec;
  fs::remove(missing, ec);  // best-effort ensure it doesn't exist

  Exiv2::FileIo io(missing.string());

  const size_t sz = io.size();
  EXPECT_EQ(std::numeric_limits<size_t>::max(), sz);
}

TEST_F(FileIoSizeTest_558, SizeReflectsWritesWhileOpenInWriteMode_558) {
  TempFile tf(/*content=*/{});
  Exiv2::FileIo io(tf.path());

  ASSERT_EQ(0, io.open("wb+"));
  ASSERT_TRUE(io.isopen());

  std::vector<Exiv2::byte> data(128);
  for (size_t i = 0; i < data.size(); ++i) data[i] = static_cast<Exiv2::byte>(i & 0xFF);

  const size_t written = io.write(data.data(), data.size());
  ASSERT_EQ(data.size(), written);

  // Observable contract: size() should report current length.
  const size_t sz = io.size();
  EXPECT_EQ(data.size(), sz);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSizeTest_558, SizeAfterMultipleWritesAccumulates_558) {
  TempFile tf(/*content=*/{});
  Exiv2::FileIo io(tf.path());

  ASSERT_EQ(0, io.open("wb+"));
  ASSERT_TRUE(io.isopen());

  std::vector<Exiv2::byte> a(10, static_cast<Exiv2::byte>(0xAB));
  std::vector<Exiv2::byte> b(25, static_cast<Exiv2::byte>(0xCD));

  ASSERT_EQ(a.size(), io.write(a.data(), a.size()));
  ASSERT_EQ(b.size(), io.write(b.data(), b.size()));

  const size_t sz = io.size();
  EXPECT_EQ(a.size() + b.size(), sz);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSizeTest_558, SizeWorksWhenOpenedReadOnly_558) {
  const auto content = FileIoSizeTest_558::MakePattern(64);
  TempFile tf(content);
  Exiv2::FileIo io(tf.path());

  ASSERT_EQ(0, io.open("rb"));
  ASSERT_TRUE(io.isopen());

  const size_t sz = io.size();
  EXPECT_EQ(content.size(), sz);

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoSizeTest_558, SetPathUpdatesWhichFileSizeIsReported_558) {
  TempFile tf1(FileIoSizeTest_558::MakePattern(11));
  TempFile tf2(FileIoSizeTest_558::MakePattern(99));

  Exiv2::FileIo io(tf1.path());
  EXPECT_EQ(11u, io.size());

  io.setPath(tf2.path());
  EXPECT_EQ(99u, io.size());
}