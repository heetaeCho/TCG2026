// SPDX-License-Identifier: GPL-2.0-or-later
// File: xpathio_transfer_test_596.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path makeUniquePath(std::string_view prefix) {
  const auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  return fs::temp_directory_path() / (std::string(prefix) + "_" + std::to_string(now));
}

void writeFile(const fs::path& p, const std::string& content) {
  std::ofstream ofs(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(ofs.good()) << "Failed to open for write: " << p.string();
  ofs.write(content.data(), static_cast<std::streamsize>(content.size()));
  ASSERT_TRUE(ofs.good()) << "Failed to write: " << p.string();
}

std::string readFile(const fs::path& p) {
  std::ifstream ifs(p, std::ios::binary);
  EXPECT_TRUE(ifs.good()) << "Failed to open for read: " << p.string();
  std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  return s;
}

class ScopedTempDir {
 public:
  ScopedTempDir() : dir_(makeUniquePath("exiv2_xpathio_596_dir")) { fs::create_directories(dir_); }
  ~ScopedTempDir() {
    std::error_code ec;
    fs::remove_all(dir_, ec);
  }
  const fs::path& path() const { return dir_; }

 private:
  fs::path dir_;
};

class XPathIoTransferTest_596 : public ::testing::Test {
 protected:
  ScopedTempDir tmp_;
};

}  // namespace

TEST_F(XPathIoTransferTest_596, TransferRenamesTempPathAndWritesSrcContent_596) {
  const fs::path orgPath = tmp_.path() / "original.bin";
  const fs::path srcPath = tmp_.path() / "src.bin";

  // Prepare input files for the real I/O implementations.
  writeFile(orgPath, "ORIGINAL_CONTENT");
  writeFile(srcPath, "SRC_CONTENT_ABC123");

  Exiv2::XPathIo dst(orgPath.string());
  const std::string beforePath = dst.path();  // expected temp path created by XPathIo
  ASSERT_FALSE(beforePath.empty());
  ASSERT_TRUE(fs::exists(beforePath)) << "Expected XPathIo temp file to exist: " << beforePath;

  Exiv2::FileIo src(srcPath.string());
  ASSERT_EQ(0, src.open()) << "Failed to open src FileIo";
  ASSERT_EQ(0, dst.open()) << "Failed to open dst XPathIo";

  ASSERT_NO_THROW(dst.transfer(src));

  const std::string afterPath = dst.path();
  EXPECT_FALSE(afterPath.empty());
  EXPECT_NE(afterPath, beforePath) << "Expected path() to change after transfer from temp to generated path";

  // Observable filesystem effects: rename should move temp -> generated.
  EXPECT_FALSE(fs::exists(beforePath)) << "Expected old temp path to no longer exist after rename";
  EXPECT_TRUE(fs::exists(afterPath)) << "Expected new path to exist after transfer";

  // Observable data effect: transferred file should contain source bytes.
  EXPECT_EQ(readFile(afterPath), "SRC_CONTENT_ABC123");

  EXPECT_EQ(0, src.close());
  EXPECT_EQ(0, dst.close());
}

TEST_F(XPathIoTransferTest_596, TransferCalledTwiceSecondCallDoesNotChangePathOrContent_596) {
  const fs::path orgPath = tmp_.path() / "original2.bin";
  const fs::path src1Path = tmp_.path() / "src1.bin";
  const fs::path src2Path = tmp_.path() / "src2.bin";

  writeFile(orgPath, "ORIGINAL_CONTENT_2");
  writeFile(src1Path, "FIRST_TRANSFER");
  writeFile(src2Path, "SECOND_TRANSFER_SHOULD_NOT_APPLY");

  Exiv2::XPathIo dst(orgPath.string());
  Exiv2::FileIo src1(src1Path.string());
  Exiv2::FileIo src2(src2Path.string());

  ASSERT_EQ(0, src1.open());
  ASSERT_EQ(0, src2.open());
  ASSERT_EQ(0, dst.open());

  ASSERT_NO_THROW(dst.transfer(src1));
  const std::string pathAfterFirst = dst.path();
  ASSERT_TRUE(fs::exists(pathAfterFirst));
  const std::string contentAfterFirst = readFile(pathAfterFirst);
  ASSERT_EQ(contentAfterFirst, "FIRST_TRANSFER");

  // Second transfer: based on the public observable behavior of XPathIo::transfer,
  // once it is no longer using a temp path, it should not perform another temp->gen rename.
  // The provided implementation snippet also shows no behavior when not temp.
  ASSERT_NO_THROW(dst.transfer(src2));

  const std::string pathAfterSecond = dst.path();
  EXPECT_EQ(pathAfterSecond, pathAfterFirst) << "Expected path() unchanged on second transfer";
  EXPECT_TRUE(fs::exists(pathAfterSecond));
  EXPECT_EQ(readFile(pathAfterSecond), contentAfterFirst) << "Expected content unchanged on second transfer";

  EXPECT_EQ(0, src1.close());
  EXPECT_EQ(0, src2.close());
  EXPECT_EQ(0, dst.close());
}

TEST_F(XPathIoTransferTest_596, TransferThrowsIfTempFileMissingDuringRename_596) {
  const fs::path orgPath = tmp_.path() / "original3.bin";
  const fs::path srcPath = tmp_.path() / "src3.bin";

  writeFile(orgPath, "ORIGINAL_CONTENT_3");
  writeFile(srcPath, "SRC_FOR_EXCEPTION_CASE");

  Exiv2::XPathIo dst(orgPath.string());
  const std::string tempPath = dst.path();
  ASSERT_TRUE(fs::exists(tempPath));

  // Force the rename step inside XPathIo::transfer to fail by deleting the temp file first.
  fs::remove(tempPath);
  ASSERT_FALSE(fs::exists(tempPath));

  Exiv2::FileIo src(srcPath.string());
  ASSERT_EQ(0, src.open());
  ASSERT_EQ(0, dst.open());

  // The snippet uses std::filesystem::rename without internal error handling.
  EXPECT_THROW(dst.transfer(src), fs::filesystem_error);

  EXPECT_EQ(0, src.close());
  EXPECT_EQ(0, dst.close());
}