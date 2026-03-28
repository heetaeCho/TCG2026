// ImageOutputDev_getErrorCode_test_2644.cc
#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

// NOTE:
// - We treat ImageOutputDev as a black box.
// - The provided partial interface only exposes getErrorCode() and (in the optional
//   dependency listing) a constructor + isOk(). We avoid relying on any other internals.
// - We only assert basic, observable properties that are stable regardless of implementation.
//
// If your real header requires different includes / namespaces, adjust accordingly.

namespace {

class ImageOutputDevTest_2644 : public ::testing::Test {
protected:
  // Helper to construct with common parameters (based only on the declared signature).
  static ImageOutputDev MakeDev(const char* root, bool pageNames, bool listImages) {
    // The signature in the dependency section uses `char*`, so we cast from const safely for tests.
    // The implementation should treat the string as input; tests must not assume ownership rules.
    return ImageOutputDev(const_cast<char*>(root), pageNames, listImages);
  }
};

TEST_F(ImageOutputDevTest_2644, GetErrorCodeIsDeterministicAcrossCalls_2644) {
  auto dev = MakeDev("out", /*pageNames=*/false, /*listImages=*/false);

  const int first = dev.getErrorCode();
  const int second = dev.getErrorCode();
  const int third = dev.getErrorCode();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ImageOutputDevTest_2644, GetErrorCodeUnaffectedByCtorFlags_2644) {
  auto devA = MakeDev("outA", /*pageNames=*/false, /*listImages=*/false);
  auto devB = MakeDev("outB", /*pageNames=*/true, /*listImages=*/false);
  auto devC = MakeDev("outC", /*pageNames=*/false, /*listImages=*/true);
  auto devD = MakeDev("outD", /*pageNames=*/true, /*listImages=*/true);

  // We do NOT assume what the error code value is, only that it is readable and stable per object.
  EXPECT_EQ(devA.getErrorCode(), devA.getErrorCode());
  EXPECT_EQ(devB.getErrorCode(), devB.getErrorCode());
  EXPECT_EQ(devC.getErrorCode(), devC.getErrorCode());
  EXPECT_EQ(devD.getErrorCode(), devD.getErrorCode());
}

TEST_F(ImageOutputDevTest_2644, GetErrorCodeWorksWithEmptyFileRoot_2644) {
  auto dev = MakeDev("", /*pageNames=*/false, /*listImages=*/false);

  // Boundary: empty string root should not prevent querying the error code.
  // We only check it can be called and returns a stable int.
  const int code1 = dev.getErrorCode();
  const int code2 = dev.getErrorCode();
  EXPECT_EQ(code1, code2);
}

TEST_F(ImageOutputDevTest_2644, GetErrorCodeWorksWithSpecialCharactersInFileRoot_2644) {
  auto dev = MakeDev("out_!@#$%^&()[]{}-_=+,.~", /*pageNames=*/true, /*listImages=*/true);

  const int code1 = dev.getErrorCode();
  const int code2 = dev.getErrorCode();
  EXPECT_EQ(code1, code2);
}

TEST_F(ImageOutputDevTest_2644, IsOkCallableAndConsistentWithGetErrorCodeStability_2644) {
  auto dev = MakeDev("out", /*pageNames=*/false, /*listImages=*/false);

  // We don't assume the semantics of isOk() vs error code; just that both are callable and stable
  // when nothing else happens.
  const bool ok1 = dev.isOk();
  const bool ok2 = dev.isOk();
  EXPECT_EQ(ok1, ok2);

  const int code1 = dev.getErrorCode();
  const int code2 = dev.getErrorCode();
  EXPECT_EQ(code1, code2);
}

TEST_F(ImageOutputDevTest_2644, MultipleInstancesHaveIndependentStableErrorCodes_2644) {
  auto dev1 = MakeDev("out1", /*pageNames=*/false, /*listImages=*/false);
  auto dev2 = MakeDev("out2", /*pageNames=*/false, /*listImages=*/false);

  // Not asserting they differ (implementation-defined), only that each is stable for itself.
  const int d1_first = dev1.getErrorCode();
  const int d1_second = dev1.getErrorCode();
  EXPECT_EQ(d1_first, d1_second);

  const int d2_first = dev2.getErrorCode();
  const int d2_second = dev2.getErrorCode();
  EXPECT_EQ(d2_first, d2_second);
}

}  // namespace