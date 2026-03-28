// File: ImageOutputDev_enableJpeg_test_2639.cc

#include <gtest/gtest.h>

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

char *DupCString(const std::string &s) {
  // Allocate with malloc so it's safe if the implementation frees with free().
  char *p = static_cast<char *>(std::malloc(s.size() + 1));
  if (!p) {
    return nullptr;
  }
  std::memcpy(p, s.c_str(), s.size() + 1);
  return p;
}

std::string MakeUniqueRoot(const char *suffix) {
  const auto base = std::filesystem::temp_directory_path() / "poppler_gtest_ImageOutputDev";
  std::error_code ec;
  std::filesystem::create_directories(base, ec);

  // Use a reasonably unique component without relying on platform-specific APIs.
  const auto uniq =
      std::to_string(reinterpret_cast<std::uintptr_t>(&base)) + "_" + std::to_string(::getpid());
  return (base / (std::string("root_") + uniq + "_" + suffix)).string();
}

class ImageOutputDevTest_2639 : public ::testing::Test {
 protected:
  ImageOutputDevTest_2639() = default;

  std::unique_ptr<ImageOutputDev> MakeDev(bool pageNames, bool listImages) {
    // Constructor takes char*, and the implementation may take ownership.
    std::string root = MakeUniqueRoot("2639");
    char *rootC = DupCString(root);
    // If allocation failed, fail the test early.
    EXPECT_NE(rootC, nullptr);
    if (!rootC) {
      return nullptr;
    }
    return std::make_unique<ImageOutputDev>(rootC, pageNames, listImages);
  }
};

}  // namespace

TEST_F(ImageOutputDevTest_2639, EnableJpegTrueDoesNotCrash_2639) {
  auto dev = MakeDev(/*pageNames=*/false, /*listImages=*/false);
  ASSERT_TRUE(dev);

  // Observable requirement: method can be called successfully.
  EXPECT_NO_THROW(dev->enableJpeg(true));

  // Ensure other public queries remain callable after toggling.
  EXPECT_NO_THROW((void)dev->getErrorCode());
  EXPECT_NO_THROW((void)dev->isOk());
}

TEST_F(ImageOutputDevTest_2639, EnableJpegFalseDoesNotCrash_2639) {
  auto dev = MakeDev(/*pageNames=*/true, /*listImages=*/true);
  ASSERT_TRUE(dev);

  EXPECT_NO_THROW(dev->enableJpeg(false));

  EXPECT_NO_THROW((void)dev->getErrorCode());
  EXPECT_NO_THROW((void)dev->isOk());
}

TEST_F(ImageOutputDevTest_2639, EnableJpegToggleRepeatedlyDoesNotCrash_2639) {
  auto dev = MakeDev(/*pageNames=*/false, /*listImages=*/true);
  ASSERT_TRUE(dev);

  // Boundary-ish behavior: repeated toggles and idempotent calls should be safe.
  EXPECT_NO_THROW(dev->enableJpeg(true));
  EXPECT_NO_THROW(dev->enableJpeg(true));   // idempotent
  EXPECT_NO_THROW(dev->enableJpeg(false));
  EXPECT_NO_THROW(dev->enableJpeg(false));  // idempotent
  EXPECT_NO_THROW(dev->enableJpeg(true));

  // Still callable.
  EXPECT_NO_THROW((void)dev->getErrorCode());
  EXPECT_NO_THROW((void)dev->isOk());
}