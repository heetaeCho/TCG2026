// TEST_ID 547
// File: test_fileio_impl_stat_547.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

class FileIoImplStatTest_547 : public ::testing::Test {
 protected:
  fs::path tempDir_;

  void SetUp() override {
    tempDir_ = fs::temp_directory_path() / fs::path("exiv2_fileio_impl_stat_547");
    std::error_code ec;
    fs::create_directories(tempDir_, ec);
  }

  void TearDown() override {
    std::error_code ec;
    fs::remove_all(tempDir_, ec);
  }

  fs::path MakeUniquePath(const std::string& base) const {
    // Use PID-ish uniqueness without relying on platform APIs.
    // If a collision happens, filesystem ops below will still be deterministic for the test.
    return tempDir_ / fs::path(base + "_547_" + std::to_string(reinterpret_cast<std::uintptr_t>(this)));
  }

  static void WriteBytes(const fs::path& p, const std::string& bytes) {
    std::ofstream ofs(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    ofs.flush();
    ASSERT_TRUE(ofs.good());
  }
};

}  // namespace

TEST_F(FileIoImplStatTest_547, StatOnExistingFileReturns0AndFillsSizeAndMode_547) {
  const fs::path filePath = MakeUniquePath("stat_existing_file");
  const std::string content = "hello exiv2";  // 10 bytes? (actually 10 incl space) -> let's compute via filesystem

  WriteBytes(filePath, content);

  Exiv2::FileIo::Impl impl(filePath.string());
  Exiv2::FileIo::Impl::StructStat st{};
  const int rc = impl.stat(st);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(fs::file_size(filePath), st.st_size);
  EXPECT_EQ(fs::status(filePath).permissions(), st.st_mode);
}

TEST_F(FileIoImplStatTest_547, StatOnEmptyFileReportsZeroSize_547) {
  const fs::path filePath = MakeUniquePath("stat_empty_file");
  WriteBytes(filePath, "");

  Exiv2::FileIo::Impl impl(filePath.string());
  Exiv2::FileIo::Impl::StructStat st{};
  const int rc = impl.stat(st);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(static_cast<std::uintmax_t>(0), st.st_size);
  EXPECT_EQ(fs::status(filePath).permissions(), st.st_mode);
}

TEST_F(FileIoImplStatTest_547, StatOnMissingPathReturnsMinusOne_547) {
  const fs::path missing = MakeUniquePath("stat_missing_file");

  Exiv2::FileIo::Impl impl(missing.string());
  Exiv2::FileIo::Impl::StructStat st{};
  const int rc = impl.stat(st);

  EXPECT_EQ(-1, rc);
}

TEST_F(FileIoImplStatTest_547, StatOnDirectoryReturnsMinusOne_547) {
  const fs::path dirPath = MakeUniquePath("stat_directory");
  std::error_code ec;
  fs::create_directories(dirPath, ec);
  ASSERT_FALSE(ec);

  Exiv2::FileIo::Impl impl(dirPath.string());
  Exiv2::FileIo::Impl::StructStat st{};
  const int rc = impl.stat(st);

  // file_size(directory) typically throws filesystem_error -> mapped to -1 by implementation.
  EXPECT_EQ(-1, rc);
}