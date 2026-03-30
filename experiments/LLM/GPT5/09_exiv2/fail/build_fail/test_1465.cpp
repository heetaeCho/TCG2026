// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// Helper that can call either a static sizeOfSignature() or a member sizeOfSignature(),
// depending on what the real codebase provides.
template <typename T, typename = void>
struct SizeOfSignatureCaller;

template <typename T>
struct SizeOfSignatureCaller<T, std::void_t<decltype(T::sizeOfSignature())>> {
  static size_t Call(const T&) { return T::sizeOfSignature(); }
};

template <typename T>
struct SizeOfSignatureCaller<T, std::void_t<decltype(std::declval<T&>().sizeOfSignature())>> {
  static size_t Call(T& obj) { return obj.sizeOfSignature(); }
};

}  // namespace

class Nikon3MnHeaderTest_1465 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MnHeader header_;
};

TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignature_IsNonZero_1465) {
  auto& h = header_;
  const size_t sigSize = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h);
  EXPECT_GT(sigSize, 0u);
}

TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignature_IsStableAcrossCalls_1465) {
  auto& h = header_;
  const size_t s1 = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h);
  const size_t s2 = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h);
  const size_t s3 = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h);
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignature_SameForDifferentInstances_1465) {
  Exiv2::Internal::Nikon3MnHeader h1;
  Exiv2::Internal::Nikon3MnHeader h2;

  const size_t s1 = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h1);
  const size_t s2 = SizeOfSignatureCaller<Exiv2::Internal::Nikon3MnHeader>::Call(h2);

  EXPECT_GT(s1, 0u);
  EXPECT_EQ(s1, s2);
}