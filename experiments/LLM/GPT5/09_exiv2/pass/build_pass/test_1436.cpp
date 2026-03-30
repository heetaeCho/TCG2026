// TEST_ID: 1436
// File: test_olympus_mn_header_1436.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::OlympusMnHeader;

// Helper: call sizeOfSignature() on either const or non-const object (whichever exists).
template <typename T>
static auto CallSizeOfSignature(T& obj) -> decltype(obj.sizeOfSignature()) {
  return obj.sizeOfSignature();
}

class OlympusMnHeaderTest_1436 : public ::testing::Test {};

}  // namespace

TEST_F(OlympusMnHeaderTest_1436, InstanceSizeOfSignatureReturnsNonZero_1436) {
  OlympusMnHeader h;
  const size_t s = CallSizeOfSignature(h);
  EXPECT_GT(s, 0u);
}

TEST_F(OlympusMnHeaderTest_1436, InstanceSizeOfSignatureIsStableAcrossCalls_1436) {
  OlympusMnHeader h;
  const size_t s1 = CallSizeOfSignature(h);
  const size_t s2 = CallSizeOfSignature(h);
  const size_t s3 = CallSizeOfSignature(h);
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(OlympusMnHeaderTest_1436, InstanceMatchesStaticSizeOfSignature_1436) {
  OlympusMnHeader h;
  const size_t instanceSize = CallSizeOfSignature(h);

  const size_t staticSize = OlympusMnHeader::sizeOfSignature();
  EXPECT_EQ(instanceSize, staticSize);
  EXPECT_GT(staticSize, 0u);
}

TEST_F(OlympusMnHeaderTest_1436, MultipleInstancesReportSameSignatureSize_1436) {
  OlympusMnHeader a;
  OlympusMnHeader b;

  const size_t sa = CallSizeOfSignature(a);
  const size_t sb = CallSizeOfSignature(b);

  EXPECT_EQ(sa, sb);
  EXPECT_GT(sa, 0u);
}