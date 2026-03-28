// TEST_ID 550
// Unit tests for Exiv2::FileIo::mmap(bool)
// File: basicio_fileio_mmap_test_550.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>
#include <vector>

namespace {

std::filesystem::path MakeUniqueTempPath_550(const std::string& prefix) {
  const auto dir = std::filesystem::temp_directory_path();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> dist;

  for (int i = 0; i < 50; ++i) {
    const auto candidate =
        dir / (prefix + "_" + std::to_string(dist(gen)) + ".bin");
    if (!std::filesystem::exists(candidate)) return candidate;
  }
  // Fallback (very unlikely collision).
  return dir / (prefix + "_fallback.bin");
}

void WriteBinaryFile_550(const std::filesystem::path& p,
                         const std::vector<Exiv2::byte>& data) {
  std::ofstream os(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(os.good());
  if (!data.empty()) {
    os.write(reinterpret_cast<const char*>(data.data()),
             static_cast<std::streamsize>(data.size()));
  }
  os.close();
  ASSERT_TRUE(os.good());
}

std::vector<Exiv2::byte> ReadBinaryFile_550(const std::filesystem::path& p) {
  std::ifstream is(p, std::ios::binary);
  EXPECT_TRUE(is.good());
  std::vector<Exiv2::byte> out;
  is.seekg(0, std::ios::end);
  const auto len = static_cast<std::streamsize>(is.tellg());
  is.seekg(0, std::ios::beg);
  if (len > 0) {
    out.resize(static_cast<size_t>(len));
    is.read(reinterpret_cast<char*>(out.data()), len);
  }
  return out;
}

}  // namespace

class FileIoMmapTest_550 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!tmpPath_.empty()) {
      std::error_code ec;
      std::filesystem::remove(tmpPath_, ec);
    }
  }

  std::filesystem::path tmpPath_;
};

TEST_F(FileIoMmapTest_550, MmapReadOnlyReturnsNonNullAndExposesFileBytes_550) {
  tmpPath_ = MakeUniqueTempPath_550("exiv2_fileio_mmap_ro_550");

  const std::vector<Exiv2::byte> payload = {
      static_cast<Exiv2::byte>(0x00), static_cast<Exiv2::byte>(0x11),
      static_cast<Exiv2::byte>(0x22), static_cast<Exiv2::byte>(0x33),
      static_cast<Exiv2::byte>(0x44), static_cast<Exiv2::byte>(0x55),
  };
  WriteBinaryFile_550(tmpPath_, payload);

  Exiv2::FileIo io(tmpPath_.string());
  ASSERT_EQ(0, io.open("rb"));

  ASSERT_EQ(payload.size(), io.size());

  Exiv2::byte* p = nullptr;
  ASSERT_NO_THROW(p = io.mmap(false));
  ASSERT_NE(nullptr, p);

  EXPECT_EQ(0, std::memcmp(p, payload.data(), payload.size()));

  // Cleanup should be observable (no-throw).
  EXPECT_NO_THROW((void)io.munmap());
  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoMmapTest_550, MmapWritableAllowsModificationPersistedToDisk_550) {
  tmpPath_ = MakeUniqueTempPath_550("exiv2_fileio_mmap_rw_550");

  std::vector<Exiv2::byte> payload = {
      static_cast<Exiv2::byte>(0xAA), static_cast<Exiv2::byte>(0xBB),
      static_cast<Exiv2::byte>(0xCC), static_cast<Exiv2::byte>(0xDD),
  };
  WriteBinaryFile_550(tmpPath_, payload);

  {
    Exiv2::FileIo io(tmpPath_.string());
    ASSERT_EQ(0, io.open("r+b"));

    Exiv2::byte* p = nullptr;
    ASSERT_NO_THROW(p = io.mmap(true));
    ASSERT_NE(nullptr, p);
    ASSERT_EQ(payload.size(), io.size());

    // Modify mapped memory (observable via later re-read).
    p[0] = static_cast<Exiv2::byte>(0x10);
    p[1] = static_cast<Exiv2::byte>(0x20);

    EXPECT_NO_THROW((void)io.munmap());
    EXPECT_EQ(0, io.close());
  }

  const auto reread = ReadBinaryFile_550(tmpPath_);
  ASSERT_EQ(payload.size(), reread.size());
  EXPECT_EQ(static_cast<Exiv2::byte>(0x10), reread[0]);
  EXPECT_EQ(static_cast<Exiv2::byte>(0x20), reread[1]);
  EXPECT_EQ(static_cast<Exiv2::byte>(0xCC), reread[2]);
  EXPECT_EQ(static_cast<Exiv2::byte>(0xDD), reread[3]);
}

TEST_F(FileIoMmapTest_550, MmapCanBeCalledTwiceSequentially_550) {
  tmpPath_ = MakeUniqueTempPath_550("exiv2_fileio_mmap_twice_550");

  const std::vector<Exiv2::byte> payload = {
      static_cast<Exiv2::byte>(0x01), static_cast<Exiv2::byte>(0x02),
      static_cast<Exiv2::byte>(0x03),
  };
  WriteBinaryFile_550(tmpPath_, payload);

  Exiv2::FileIo io(tmpPath_.string());
  ASSERT_EQ(0, io.open("rb"));

  Exiv2::byte* p1 = nullptr;
  ASSERT_NO_THROW(p1 = io.mmap(false));
  ASSERT_NE(nullptr, p1);
  EXPECT_EQ(0, std::memcmp(p1, payload.data(), payload.size()));

  // Call mmap again; implementation begins by munmap() internally.
  Exiv2::byte* p2 = nullptr;
  ASSERT_NO_THROW(p2 = io.mmap(false));
  ASSERT_NE(nullptr, p2);
  EXPECT_EQ(0, std::memcmp(p2, payload.data(), payload.size()));

  EXPECT_NO_THROW((void)io.munmap());
  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoMmapTest_550, MmapWritableOnReadOnlyFileThrowsError_550) {
  tmpPath_ = MakeUniqueTempPath_550("exiv2_fileio_mmap_rofile_550");

  const std::vector<Exiv2::byte> payload = {
      static_cast<Exiv2::byte>(0xFE), static_cast<Exiv2::byte>(0xED),
  };
  WriteBinaryFile_550(tmpPath_, payload);

  // Make the file read-only (best-effort across platforms).
  std::error_code ec;
  std::filesystem::permissions(
      tmpPath_,
      std::filesystem::perms::owner_read | std::filesystem::perms::group_read |
          std::filesystem::perms::others_read,
      std::filesystem::perm_options::replace, ec);

  Exiv2::FileIo io(tmpPath_.string());
  ASSERT_EQ(0, io.open("rb"));

  // Observable exceptional behavior: mapping as writeable should fail.
  EXPECT_THROW((void)io.mmap(true), Exiv2::Error);

  // Cleanup should still be safe to call.
  EXPECT_NO_THROW((void)io.munmap());
  EXPECT_EQ(0, io.close());
}