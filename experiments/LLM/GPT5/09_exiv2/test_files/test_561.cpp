// File: test_fileio_isopen_561.cpp
// TEST_ID: 561

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <fstream>
#include <string>
#include <system_error>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No filesystem support available"
#endif

namespace {

class FileIoIsOpenTest_561 : public ::testing::Test {
 protected:
  static std::string MakeTempFilePath(const std::string& basename) {
    std::error_code ec;
    fs::path dir = fs::temp_directory_path(ec);
    if (ec) {
      // Fallback: current directory
      dir = fs::current_path();
    }
    fs::path p = dir / (basename + "_561.tmp");
    return p.string();
  }

  static void TouchFile(const std::string& path) {
    std::ofstream ofs(path, std::ios::binary);
    ASSERT_TRUE(ofs.good());
    ofs << "x";
  }

  static void RemoveFileNoThrow(const std::string& path) {
    std::error_code ec;
    fs::remove(fs::path(path), ec);
  }
};

TEST_F(FileIoIsOpenTest_561, InitiallyClosed_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_initial");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);
  EXPECT_FALSE(io.isopen());

  RemoveFileNoThrow(path);
}

TEST_F(FileIoIsOpenTest_561, OpenMakesIsOpenTrue_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_open");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);
  ASSERT_FALSE(io.isopen());

  // If open() succeeds, isopen() should become true.
  ASSERT_EQ(0, io.open());
  EXPECT_TRUE(io.isopen());

  // Cleanup
  (void)io.close();
  RemoveFileNoThrow(path);
}

TEST_F(FileIoIsOpenTest_561, CloseMakesIsOpenFalse_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_close");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open());
  ASSERT_TRUE(io.isopen());

  ASSERT_EQ(0, io.close());
  EXPECT_FALSE(io.isopen());

  RemoveFileNoThrow(path);
}

TEST_F(FileIoIsOpenTest_561, FailedOpenKeepsIsOpenFalse_561) {
  // Use a path in a definitely-nonexistent directory.
  const fs::path badDir = fs::path(MakeTempFilePath("exiv2_nonexistent_dir")) / "no_such_dir_561";
  const fs::path badPath = badDir / "no_such_file_561.bin";

  // Ensure directory doesn't exist.
  std::error_code ec;
  fs::remove_all(badDir, ec);

  Exiv2::FileIo io(badPath.string());
  EXPECT_FALSE(io.isopen());

  const int rc = io.open();  // expected to fail
  EXPECT_NE(0, rc);
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoIsOpenTest_561, DoubleCloseKeepsIsOpenFalse_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_double_close");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open());
  ASSERT_TRUE(io.isopen());

  (void)io.close();
  EXPECT_FALSE(io.isopen());

  // Second close should not make it "open" again and should not crash.
  (void)io.close();
  EXPECT_FALSE(io.isopen());

  RemoveFileNoThrow(path);
}

TEST_F(FileIoIsOpenTest_561, OpenCloseOpenAgain_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_reopen");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);

  ASSERT_EQ(0, io.open());
  EXPECT_TRUE(io.isopen());

  ASSERT_EQ(0, io.close());
  EXPECT_FALSE(io.isopen());

  ASSERT_EQ(0, io.open());
  EXPECT_TRUE(io.isopen());

  (void)io.close();
  RemoveFileNoThrow(path);
}

TEST_F(FileIoIsOpenTest_561, IsOpenCallableOnConstReference_561) {
  const std::string path = MakeTempFilePath("exiv2_fileio_isopen_const");
  RemoveFileNoThrow(path);
  TouchFile(path);

  Exiv2::FileIo io(path);
  const Exiv2::FileIo& cio = io;

  EXPECT_FALSE(cio.isopen());

  ASSERT_EQ(0, io.open());
  EXPECT_TRUE(cio.isopen());

  (void)io.close();
  EXPECT_FALSE(cio.isopen());

  RemoveFileNoThrow(path);
}

}  // namespace