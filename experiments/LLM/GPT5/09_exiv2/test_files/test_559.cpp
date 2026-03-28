// File: test_fileio_open_559.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path makeUniqueTempPath(const std::string& stem) {
  const fs::path dir = fs::temp_directory_path();
  // Good-enough uniqueness for unit tests.
  const auto uniq = std::to_string(
      static_cast<unsigned long long>(::time(nullptr))) +
      "_" + std::to_string(static_cast<unsigned long long>(::getpid()));
  return dir / (stem + "_" + uniq + ".bin");
}

void writeFile(const fs::path& p, const std::string& content) {
  std::ofstream os(p, std::ios::binary);
  ASSERT_TRUE(os.good());
  os.write(content.data(), static_cast<std::streamsize>(content.size()));
  os.close();
  ASSERT_TRUE(fs::exists(p));
}

}  // namespace

class FileIoOpenTest_559 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Best-effort cleanup.
    std::error_code ec;
    if (!created_.empty()) fs::remove(created_, ec);
  }

  fs::path created_;
};

TEST_F(FileIoOpenTest_559, OpenDefaultBehavesLikeOpenRbOnExistingFile_559) {
  created_ = makeUniqueTempPath("exiv2_fileio_open_ok");
  writeFile(created_, "abc");

  Exiv2::FileIo ioDefault(created_.string());
  Exiv2::FileIo ioExplicit(created_.string());

  const int rcDefault = ioDefault.open();
  const int rcExplicit = ioExplicit.open(std::string("rb"));

  // Observable equivalence: return code and open-state should match.
  EXPECT_EQ(rcDefault, rcExplicit);
  EXPECT_EQ(ioDefault.isopen(), ioExplicit.isopen());

  // If either opened, it should be closable.
  if (ioDefault.isopen()) {
    EXPECT_NO_THROW({
      const int c = ioDefault.close();
      (void)c;
    });
    EXPECT_FALSE(ioDefault.isopen());
  }
  if (ioExplicit.isopen()) {
    EXPECT_NO_THROW({
      const int c = ioExplicit.close();
      (void)c;
    });
    EXPECT_FALSE(ioExplicit.isopen());
  }
}

TEST_F(FileIoOpenTest_559, OpenDefaultBehavesLikeOpenRbOnMissingFile_559) {
  const fs::path missing = makeUniqueTempPath("exiv2_fileio_open_missing");
  ASSERT_FALSE(fs::exists(missing));

  Exiv2::FileIo ioDefault(missing.string());
  Exiv2::FileIo ioExplicit(missing.string());

  const int rcDefault = ioDefault.open();
  const int rcExplicit = ioExplicit.open(std::string("rb"));

  // For an error case, still require consistent observable behavior.
  EXPECT_EQ(rcDefault, rcExplicit);
  EXPECT_EQ(ioDefault.isopen(), ioExplicit.isopen());

  // If open failed, it should not report open.
  if (rcDefault != 0) {
    EXPECT_FALSE(ioDefault.isopen());
    EXPECT_FALSE(ioExplicit.isopen());
  }

  // Calling close should be safe regardless of open result (no crash).
  EXPECT_NO_THROW({
    (void)ioDefault.close();
    (void)ioExplicit.close();
  });
}

TEST_F(FileIoOpenTest_559, OpenCanBeCalledThenClosedWithoutCrashing_559) {
  created_ = makeUniqueTempPath("exiv2_fileio_open_close");
  writeFile(created_, "hello");

  Exiv2::FileIo io(created_.string());

  EXPECT_NO_THROW({
    (void)io.open();
  });

  // Regardless of whether it opened successfully, close should be safe.
  EXPECT_NO_THROW({
    (void)io.close();
  });

  // After close, isopen should be false (if the implementation reports open state).
  EXPECT_FALSE(io.isopen());
}