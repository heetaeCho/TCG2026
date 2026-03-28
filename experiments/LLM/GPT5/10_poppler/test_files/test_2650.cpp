// File: ImageOutputDev_test_2650.cpp

#include <gtest/gtest.h>

#include <cstring>   // strdup (POSIX)
#include <cstdlib>   // free (in case strdup not available on some platforms)

#include "TestProjects/poppler/utils/ImageOutputDev.h"

// Some toolchains (e.g., MSVC) don't provide strdup by default.
// Provide a tiny compatibility shim for test input allocation only.
static char *dup_cstr_2650(const char *s)
{
#if defined(_MSC_VER)
  if (!s) {
    return nullptr;
  }
  size_t n = std::strlen(s);
  char *out = static_cast<char *>(std::malloc(n + 1));
  if (!out) {
    return nullptr;
  }
  std::memcpy(out, s, n + 1);
  return out;
#else
  return s ? ::strdup(s) : nullptr;
#endif
}

class ImageOutputDevTest_2650 : public ::testing::Test {
protected:
  // Note:
  // We intentionally do NOT free the returned pointers in tests because ownership
  // semantics of ImageOutputDev(fileRootA, ...) are unknown from the interface.
  // Passing dynamically allocated memory avoids invalid frees of string literals
  // if the implementation takes ownership and frees it in the destructor.
  static char *MakeFileRoot(const char *s) { return dup_cstr_2650(s); }
};

TEST_F(ImageOutputDevTest_2650, UseDrawCharReturnsFalse_BasicConstruction_2650)
{
  char *root = MakeFileRoot("imgout");
  ImageOutputDev dev(root, /*pageNamesA=*/false, /*listImagesA=*/false);

  EXPECT_FALSE(dev.useDrawChar());
}

TEST_F(ImageOutputDevTest_2650, UseDrawCharReturnsFalse_WithDifferentFlags_2650)
{
  {
    char *root = MakeFileRoot("rootA");
    ImageOutputDev dev(root, /*pageNamesA=*/true, /*listImagesA=*/false);
    EXPECT_FALSE(dev.useDrawChar());
  }
  {
    char *root = MakeFileRoot("rootB");
    ImageOutputDev dev(root, /*pageNamesA=*/false, /*listImagesA=*/true);
    EXPECT_FALSE(dev.useDrawChar());
  }
  {
    char *root = MakeFileRoot("rootC");
    ImageOutputDev dev(root, /*pageNamesA=*/true, /*listImagesA=*/true);
    EXPECT_FALSE(dev.useDrawChar());
  }
}

TEST_F(ImageOutputDevTest_2650, UseDrawCharReturnsFalse_OnEmptyFileRoot_2650)
{
  char *root = MakeFileRoot("");
  ImageOutputDev dev(root, /*pageNamesA=*/false, /*listImagesA=*/false);

  EXPECT_FALSE(dev.useDrawChar());
}

TEST_F(ImageOutputDevTest_2650, UseDrawCharIsStableAcrossMultipleCalls_2650)
{
  char *root = MakeFileRoot("stable");
  ImageOutputDev dev(root, /*pageNamesA=*/true, /*listImagesA=*/false);

  EXPECT_FALSE(dev.useDrawChar());
  EXPECT_FALSE(dev.useDrawChar());
  EXPECT_FALSE(dev.useDrawChar());
}

TEST_F(ImageOutputDevTest_2650, UseDrawCharReturnsFalse_ViaBasePointerDispatch_2650)
{
  char *root = MakeFileRoot("polymorphic");
  OutputDev *base = new ImageOutputDev(root, /*pageNamesA=*/false, /*listImagesA=*/false);

  EXPECT_FALSE(base->useDrawChar());

  delete base;
}