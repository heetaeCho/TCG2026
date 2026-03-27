// TEST_ID 555
// File: test_fileio_putb_555.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace {

class FileIoPutbTest_555 : public ::testing::Test {
 protected:
  static std::string makeTempPath_555() {
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path();

    // Create a reasonably-unique filename without relying on platform-specific APIs.
    // If it already exists, try a few variants.
    for (int i = 0; i < 100; ++i) {
      fs::path p = dir / ("exiv2_fileio_putb_555_" + std::to_string(::getpid()) + "_" +
                          std::to_string(i) + ".bin");
      std::error_code ec;
      if (!fs::exists(p, ec)) return p.string();
    }

    // Fallback
    return (dir / "exiv2_fileio_putb_555_fallback.bin").string();
  }

  static std::vector<unsigned char> readAllBytes_555(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    std::vector<unsigned char> out;
    if (!ifs) return out;
    ifs.seekg(0, std::ios::end);
    const std::streamoff len = ifs.tellg();
    if (len < 0) return out;
    ifs.seekg(0, std::ios::beg);
    out.resize(static_cast<size_t>(len));
    if (!out.empty()) {
      ifs.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(out.size()));
    }
    return out;
  }

  void TearDown() override {
    if (!tmpPath_.empty()) {
      std::error_code ec;
      std::filesystem::remove(tmpPath_, ec);
    }
  }

  std::string tmpPath_;
};

TEST_F(FileIoPutbTest_555, PutbWritesSingleByteAndReturnsWrittenValue_555) {
  tmpPath_ = makeTempPath_555();

  Exiv2::FileIo io(tmpPath_);
  ASSERT_EQ(0, io.open("wb"));

  const Exiv2::byte b = static_cast<Exiv2::byte>(0x41);  // 'A'
  const int rc = io.putb(b);

  // Observable behavior from provided snippet: putb returns putc(...) result or EOF.
  ASSERT_NE(EOF, rc);
  EXPECT_EQ(static_cast<int>(static_cast<unsigned char>(b)), rc);

  EXPECT_EQ(0, io.close());

  const auto bytes = readAllBytes_555(tmpPath_);
  ASSERT_EQ(1u, bytes.size());
  EXPECT_EQ(0x41, bytes[0]);
}

TEST_F(FileIoPutbTest_555, PutbWritesMultipleBytesInOrder_555) {
  tmpPath_ = makeTempPath_555();

  Exiv2::FileIo io(tmpPath_);
  ASSERT_EQ(0, io.open("wb"));

  const std::vector<unsigned char> expected = {0x00, 0x7F, 0x80, 0xFF};
  for (unsigned char v : expected) {
    const Exiv2::byte b = static_cast<Exiv2::byte>(v);
    const int rc = io.putb(b);
    ASSERT_NE(EOF, rc);
    EXPECT_EQ(static_cast<int>(v), rc);
  }

  EXPECT_EQ(0, io.close());

  const auto bytes = readAllBytes_555(tmpPath_);
  ASSERT_EQ(expected.size(), bytes.size());
  EXPECT_EQ(expected, bytes);
}

TEST_F(FileIoPutbTest_555, PutbOnFreshUnopenedInstanceReturnsEof_555) {
  tmpPath_ = makeTempPath_555();

  Exiv2::FileIo io(tmpPath_);

  // From the provided implementation snippet: if switchMode(opWrite) != 0 => EOF.
  // A reasonable observable error case is attempting to write while not open.
  EXPECT_EQ(EOF, io.putb(static_cast<Exiv2::byte>(0x11)));

  // File should either not exist or be empty (both are acceptable observable outcomes here).
  const auto bytes = readAllBytes_555(tmpPath_);
  EXPECT_TRUE(bytes.empty());
}

TEST_F(FileIoPutbTest_555, PutbAfterCloseReturnsEofAndDoesNotAppend_555) {
  tmpPath_ = makeTempPath_555();

  Exiv2::FileIo io(tmpPath_);
  ASSERT_EQ(0, io.open("wb"));

  ASSERT_NE(EOF, io.putb(static_cast<Exiv2::byte>(0xAA)));
  ASSERT_EQ(0, io.close());

  const auto before = readAllBytes_555(tmpPath_);
  ASSERT_EQ(1u, before.size());
  ASSERT_EQ(0xAA, before[0]);

  // After closing, attempting to putb should fail (observable error case).
  EXPECT_EQ(EOF, io.putb(static_cast<Exiv2::byte>(0xBB)));

  const auto after = readAllBytes_555(tmpPath_);
  EXPECT_EQ(before, after);
}

}  // namespace