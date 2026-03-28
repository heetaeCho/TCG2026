// Revision6Hash_tests_1646.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "goo/GooString.h"
#include "poppler/Decrypt.h"

// NOTE: revision6Hash is a static (internal-linkage) function in Decrypt.cc.
// To test it as a black box via its real implementation, we include the .cc
// into this test translation unit so the symbol is visible here.
#include "poppler/Decrypt.cc"

namespace {

struct KWithGuard {
  std::array<unsigned char, 64> k{};
  std::array<unsigned char, 16> guard{};
};

static KWithGuard MakeKWithGuard(unsigned char k_seed, unsigned char guard_seed) {
  KWithGuard out;
  for (size_t i = 0; i < out.k.size(); ++i) out.k[i] = static_cast<unsigned char>(k_seed + i);
  for (size_t i = 0; i < out.guard.size(); ++i) out.guard[i] = static_cast<unsigned char>(guard_seed + i);
  return out;
}

static std::array<unsigned char, 48> MakeUserKey48(unsigned char seed) {
  std::array<unsigned char, 48> uk{};
  for (size_t i = 0; i < uk.size(); ++i) uk[i] = static_cast<unsigned char>(seed + 3 * i);
  return uk;
}

static std::array<unsigned char, 64> CallRevision6HashAndReturnK(
    const GooString& password,
    const std::array<unsigned char, 64>& initialK,
    const char* userKeyOrNull) {
  // Copy K because revision6Hash writes into it.
  std::array<unsigned char, 64> k = initialK;
  revision6Hash(&password, k.data(), userKeyOrNull);
  return k;
}

static bool ArraysEqual(const unsigned char* a, const unsigned char* b, size_t n) {
  return std::memcmp(a, b, n) == 0;
}

class Revision6HashTest_1646 : public ::testing::Test {};

}  // namespace

TEST_F(Revision6HashTest_1646, DeterministicSameInputs_1646) {
  const GooString pw("password");
  const auto userKey = MakeUserKey48(0x10);

  std::array<unsigned char, 64> initialK{};
  for (size_t i = 0; i < initialK.size(); ++i) initialK[i] = static_cast<unsigned char>(0xA0 + i);

  const auto out1 = CallRevision6HashAndReturnK(pw, initialK, reinterpret_cast<const char*>(userKey.data()));
  const auto out2 = CallRevision6HashAndReturnK(pw, initialK, reinterpret_cast<const char*>(userKey.data()));

  EXPECT_EQ(out1, out2);
}

TEST_F(Revision6HashTest_1646, DifferentPasswordUsuallyChangesOutput_1646) {
  const GooString pw1("password");
  const GooString pw2("password2");
  const auto userKey = MakeUserKey48(0x22);

  std::array<unsigned char, 64> initialK{};
  for (size_t i = 0; i < initialK.size(); ++i) initialK[i] = static_cast<unsigned char>(0x11 + i);

  const auto out1 = CallRevision6HashAndReturnK(pw1, initialK, reinterpret_cast<const char*>(userKey.data()));
  const auto out2 = CallRevision6HashAndReturnK(pw2, initialK, reinterpret_cast<const char*>(userKey.data()));

  EXPECT_NE(out1, out2);
}

TEST_F(Revision6HashTest_1646, DifferentInitialKUsuallyChangesOutput_1646) {
  const GooString pw("password");
  const auto userKey = MakeUserKey48(0x33);

  std::array<unsigned char, 64> initialK1{};
  std::array<unsigned char, 64> initialK2{};
  for (size_t i = 0; i < initialK1.size(); ++i) {
    initialK1[i] = static_cast<unsigned char>(0x01 + i);
    initialK2[i] = static_cast<unsigned char>(0xF0 - i);
  }

  const auto out1 = CallRevision6HashAndReturnK(pw, initialK1, reinterpret_cast<const char*>(userKey.data()));
  const auto out2 = CallRevision6HashAndReturnK(pw, initialK2, reinterpret_cast<const char*>(userKey.data()));

  EXPECT_NE(out1, out2);
}

TEST_F(Revision6HashTest_1646, UserKeyNullVsPresentUsuallyChangesOutput_1646) {
  const GooString pw("password");
  const auto userKey = MakeUserKey48(0x44);

  std::array<unsigned char, 64> initialK{};
  for (size_t i = 0; i < initialK.size(); ++i) initialK[i] = static_cast<unsigned char>(0x55 + i);

  const auto outWithNull =
      CallRevision6HashAndReturnK(pw, initialK, /*userKeyOrNull=*/nullptr);
  const auto outWithKey =
      CallRevision6HashAndReturnK(pw, initialK, reinterpret_cast<const char*>(userKey.data()));

  EXPECT_NE(outWithNull, outWithKey);
}

TEST_F(Revision6HashTest_1646, EmptyPasswordDoesNotClobberGuardBytes_1646) {
  const GooString emptyPw("");
  const auto userKey = MakeUserKey48(0x12);

  KWithGuard buf = MakeKWithGuard(/*k_seed=*/0x7A, /*guard_seed=*/0xC1);
  const auto guardBefore = buf.guard;

  revision6Hash(&emptyPw, buf.k.data(), reinterpret_cast<const char*>(userKey.data()));

  // Observable safety property: should not write past the provided K buffer.
  EXPECT_EQ(buf.guard, guardBefore);
}

TEST_F(Revision6HashTest_1646, TypicalCallDoesNotClobberGuardBytes_1646) {
  const GooString pw("password");
  const auto userKey = MakeUserKey48(0x99);

  KWithGuard buf = MakeKWithGuard(/*k_seed=*/0x00, /*guard_seed=*/0xEE);
  const auto guardBefore = buf.guard;

  revision6Hash(&pw, buf.k.data(), reinterpret_cast<const char*>(userKey.data()));

  EXPECT_EQ(buf.guard, guardBefore);
}

TEST_F(Revision6HashTest_1646, BinaryPasswordWithEmbeddedNullAffectsOutput_1646) {
  // Construct a password containing an embedded '\0' to exercise boundary input.
  const char rawPw[] = {'a', '\0', 'b', 'c'};
  const GooString pwWithNull(rawPw, sizeof(rawPw));
  const GooString pwShort("a");

  const auto userKey = MakeUserKey48(0x5D);

  std::array<unsigned char, 64> initialK{};
  for (size_t i = 0; i < initialK.size(); ++i) initialK[i] = static_cast<unsigned char>(0x80 + i);

  const auto out1 =
      CallRevision6HashAndReturnK(pwWithNull, initialK, reinterpret_cast<const char*>(userKey.data()));
  const auto out2 =
      CallRevision6HashAndReturnK(pwShort, initialK, reinterpret_cast<const char*>(userKey.data()));

  EXPECT_NE(out1, out2);
}