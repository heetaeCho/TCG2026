// ImageOutputDev_enableTiff_test_2638.cpp

#include <gtest/gtest.h>

#include <cstring>   // std::strdup (POSIX); fall back below if unavailable
#include <cstdlib>   // std::malloc, std::free

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

// Some toolchains may not provide ::strdup in <cstring> without feature macros.
// Provide a tiny helper that always returns malloc-allocated memory.
static char *DupCString(const char *s) {
  if (!s) {
    return nullptr;
  }
  const size_t n = std::strlen(s);
  char *out = static_cast<char *>(std::malloc(n + 1));
  if (!out) {
    return nullptr;
  }
  std::memcpy(out, s, n);
  out[n] = '\0';
  return out;
}

// IMPORTANT: We intentionally do NOT free the passed-in fileRoot buffers in tests.
// The constructor takes `char *fileRootA` (non-const), and ownership semantics are
// not specified in the provided interface. Avoiding frees prevents double-free
// if the implementation takes ownership.
static ImageOutputDev *MakeDev(const char *fileRoot, bool pageNames, bool listImages) {
  char *root = DupCString(fileRoot);
  return new ImageOutputDev(root, pageNames, listImages);
}

class ImageOutputDevTest_2638 : public ::testing::Test {};

}  // namespace

TEST_F(ImageOutputDevTest_2638, EnableTiffTrue_NoCrash_2638) {
  ImageOutputDev *dev = MakeDev("img-out", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));

  delete dev;
}

TEST_F(ImageOutputDevTest_2638, EnableTiffFalse_NoCrash_2638) {
  ImageOutputDev *dev = MakeDev("img-out", /*pageNames=*/true, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));

  delete dev;
}

TEST_F(ImageOutputDevTest_2638, EnableTiffToggleMultipleTimes_NoCrash_2638) {
  ImageOutputDev *dev = MakeDev("img-out", /*pageNames=*/false, /*listImages=*/true);
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));
  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));

  delete dev;
}

TEST_F(ImageOutputDevTest_2638, EnableTiff_BoundaryNullFileRoot_NoCrash_2638) {
  // Boundary/error-style input: nullptr fileRoot. Observable behavior is not
  // specified, so we only verify calls are safe through the public interface.
  // (If the real implementation rejects this, it may still remain well-defined
  // via isOk()/getErrorCode(), but we do not assert those semantics here.)
  ImageOutputDev *dev = new ImageOutputDev(/*fileRootA=*/nullptr,
                                          /*pageNamesA=*/false,
                                          /*listImagesA=*/false);
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
  EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));

  delete dev;
}