// SPDX-License-Identifier: GPL-2.0-or-later
// File: xpathio_destructor_test_595.cpp

#include <gtest/gtest.h>

#include <basicio.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path makeUniquePath(const std::string& prefix) {
  const fs::path dir = fs::temp_directory_path();
  // Good-enough uniqueness for unit tests without relying on platform APIs.
  // (We avoid assumptions about Exiv2 internals; this is only for our test inputs.)
  const auto uniq = std::to_string(
      static_cast<unsigned long long>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  return dir / (prefix + "_" + uniq);
}

fs::path writeTempSourceFile(const std::string& contents) {
  fs::path p = makeUniquePath("exiv2_xpathio_src_595");
  p += ".bin";
  std::ofstream os(p, std::ios::binary);
  os << contents;
  os.close();
  return p;
}

}  // namespace

class XPathIoTest_595 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Best-effort cleanup if something fails mid-test.
    for (const auto& p : pathsToCleanup_) {
      std::error_code ec;
      fs::remove(p, ec);
    }
  }

  void trackForCleanup(const fs::path& p) { pathsToCleanup_.push_back(p); }

 private:
  std::vector<fs::path> pathsToCleanup_;
};

TEST_F(XPathIoTest_595, DestructorRemovesTempFile_595) {
  const fs::path src = writeTempSourceFile("hello xpathio");
  trackForCleanup(src);

  fs::path tempPath;
  {
    Exiv2::XPathIo io(src.string());

    // Observable behavior through the public FileIo interface: path().
    tempPath = fs::path(io.path());
    ASSERT_FALSE(tempPath.empty());

    // While alive, the backing file should exist (as it is constructed from writeDataToFile()).
    // If an exotic filesystem makes exists() unreliable, this test will surface it.
    EXPECT_TRUE(fs::exists(tempPath)) << "Expected XPathIo backing path to exist while object is alive: "
                                      << tempPath.string();
  }

  // Observable behavior from ~XPathIo(): it attempts to remove the temp file when isTemp_ is true.
  EXPECT_FALSE(fs::exists(tempPath)) << "Expected XPathIo backing path to be removed on destruction: "
                                     << tempPath.string();
}

TEST_F(XPathIoTest_595, DestructorDoesNotThrowIfTempAlreadyRemoved_595) {
  const fs::path src = writeTempSourceFile("remove-before-dtor");
  trackForCleanup(src);

  fs::path tempPath;
  {
    Exiv2::XPathIo io(src.string());
    tempPath = fs::path(io.path());
    ASSERT_FALSE(tempPath.empty());

    // Remove it early (best-effort). Destructor should tolerate failure / missing file.
    std::error_code ec;
    fs::remove(tempPath, ec);
    // Whether removal succeeds or not is platform/filesystem dependent, but destruction must not throw.
  }

  // The key observable requirement here: no crash/exception during scope exit.
  // Additionally, the temp path should not exist if we managed to remove it.
  // (If remove failed due to platform constraints, this assertion will reflect reality.)
  std::error_code ec;
  const bool existsAfter = fs::exists(tempPath, ec) && !ec;
  EXPECT_FALSE(existsAfter) << "Expected temp path to be absent after early removal + destruction (if removable): "
                            << tempPath.string();
}

TEST_F(XPathIoTest_595, MultipleInstancesCleanUpTheirTempFiles_595) {
  const fs::path src1 = writeTempSourceFile("one");
  const fs::path src2 = writeTempSourceFile("two");
  trackForCleanup(src1);
  trackForCleanup(src2);

  fs::path p1;
  fs::path p2;

  {
    Exiv2::XPathIo io1(src1.string());
    p1 = fs::path(io1.path());
    ASSERT_FALSE(p1.empty());
    EXPECT_TRUE(fs::exists(p1));

    Exiv2::XPathIo io2(src2.string());
    p2 = fs::path(io2.path());
    ASSERT_FALSE(p2.empty());
    EXPECT_TRUE(fs::exists(p2));

    // Distinct instances should generally yield distinct temp paths (observable via path()).
    // If the implementation reuses the same temp file, that invites data races; this test would reveal it.
    EXPECT_NE(p1, p2);
  }

  EXPECT_FALSE(fs::exists(p1)) << "Expected first XPathIo temp file removed on destruction: " << p1.string();
  EXPECT_FALSE(fs::exists(p2)) << "Expected second XPathIo temp file removed on destruction: " << p2.string();
}