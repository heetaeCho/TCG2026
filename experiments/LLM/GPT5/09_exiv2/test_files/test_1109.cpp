// File: test_imagefactory_create_path_1109.cpp
// TEST_ID: 1109

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cerrno>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

class ImageFactoryCreatePathTest_1109 : public ::testing::Test {
 protected:
  fs::path tempDir() const {
    std::error_code ec;
    auto p = fs::temp_directory_path(ec);
    if (ec) {
      // If temp_directory_path fails for some reason, fall back to current path.
      return fs::current_path();
    }
    return p;
  }

  fs::path uniquePath(const std::string& stem) const {
    // Use pid-ish + counter-like uniqueness via time since epoch address-ish not needed.
    // filesystem::unique_path is C++17 in some libs but not always available; keep it simple.
    static uint64_t n = 0;
    ++n;
    return tempDir() / (stem + "_" + std::to_string(n) + ".bin");
  }

  void removeIfExists(const fs::path& p) const {
    std::error_code ec;
    fs::remove(p, ec);
  }

  void removeAllIfExists(const fs::path& p) const {
    std::error_code ec;
    fs::remove_all(p, ec);
  }
};

TEST_F(ImageFactoryCreatePathTest_1109, InvalidDirectoryThrowsFileOpenFailed_1109) {
  // Path points into a directory that does not exist -> FileIo::open("w+b") is expected to fail.
  const fs::path nonExistentDir = uniquePath("exiv2_nonexistent_dir_1109");
  // Ensure it doesn't exist and treat it as a directory name.
  removeAllIfExists(nonExistentDir);
  ASSERT_FALSE(fs::exists(nonExistentDir));

  const fs::path pathInMissingDir = nonExistentDir / "out.img";

  Exiv2::ImageFactory factory;
  try {
    (void)factory.create(static_cast<Exiv2::ImageType>(0), pathInMissingDir.string());
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileOpenFailed);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }

  // File should not exist because open should have failed.
  EXPECT_FALSE(fs::exists(pathInMissingDir));
}

TEST_F(ImageFactoryCreatePathTest_1109, EmptyPathThrowsFileOpenFailed_1109) {
  Exiv2::ImageFactory factory;
  try {
    (void)factory.create(static_cast<Exiv2::ImageType>(0), std::string{});
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Based on the provided implementation, the only thrown error here is kerFileOpenFailed
    // when FileIo::open("w+b") returns non-zero.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileOpenFailed);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(ImageFactoryCreatePathTest_1109, UnsupportedTypeCreatesFileThenThrowsUnsupportedImageType_1109) {
  // Observable behavior from provided implementation:
  // 1) It opens the path with "w+b" and closes it (creating/truncating the file),
  // 2) then delegates to create(type, io),
  // 3) if that returns null, it throws kerUnsupportedImageType.
  const fs::path outPath = uniquePath("exiv2_created_then_unsupported_1109");
  removeIfExists(outPath);
  ASSERT_FALSE(fs::exists(outPath));

  Exiv2::ImageFactory factory;

  // Use an out-of-range/unknown ImageType value to make "unsupported" observable without
  // assuming specific supported formats.
  const auto unknownType = static_cast<Exiv2::ImageType>(0x7fffffff);

  try {
    (void)factory.create(unknownType, outPath.string());
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerUnsupportedImageType);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }

  // File creation/truncation is externally observable.
  EXPECT_TRUE(fs::exists(outPath));

  // Best-effort check: "w+b" typically creates an empty file initially.
  std::error_code ec;
  const auto sz = fs::file_size(outPath, ec);
  if (!ec) {
    EXPECT_EQ(sz, 0u);
  }

  removeIfExists(outPath);
}

TEST_F(ImageFactoryCreatePathTest_1109, ReadOnlyPathThrowsFileOpenFailed_1109) {
  // Boundary/error case: existing file without write permission (where supported) should cause
  // FileIo::open("w+b") to fail.
  const fs::path outPath = uniquePath("exiv2_readonly_1109");
  removeIfExists(outPath);

  // Create the file first.
  {
    std::ofstream os(outPath.string(), std::ios::binary);
    ASSERT_TRUE(os.good());
    os << "x";
  }
  ASSERT_TRUE(fs::exists(outPath));

  std::error_code ec;
  auto oldPerms = fs::status(outPath, ec).permissions();
  if (ec) {
    GTEST_SKIP() << "Unable to read file permissions on this platform/filesystem.";
  }

  // Try to remove write permissions for owner/group/others.
  fs::permissions(outPath,
                  fs::perms::owner_write | fs::perms::group_write | fs::perms::others_write,
                  fs::perm_options::remove, ec);
  if (ec) {
    GTEST_SKIP() << "Unable to modify file permissions on this platform/filesystem.";
  }

  Exiv2::ImageFactory factory;
  try {
    (void)factory.create(static_cast<Exiv2::ImageType>(0), outPath.string());
    // Restore perms before failing the test.
    fs::permissions(outPath, oldPerms, fs::perm_options::replace, ec);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileOpenFailed);
  } catch (...) {
    // Restore perms before failing the test.
    fs::permissions(outPath, oldPerms, fs::perm_options::replace, ec);
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }

  // Restore permissions and clean up.
  fs::permissions(outPath, oldPerms, fs::perm_options::replace, ec);
  removeIfExists(outPath);
}

}  // namespace