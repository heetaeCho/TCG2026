// File: test_xref_getpermflags_261.cpp
// TEST_ID: 261

#include <gtest/gtest.h>

#include <climits>
#include <type_traits>

#include "poppler/XRef.h"

namespace {

class XRefTest_261 : public ::testing::Test {};

TEST_F(XRefTest_261, NotCopyConstructible_261) {
  static_assert(!std::is_copy_constructible_v<XRef>,
                "XRef must not be copy constructible (per header).");
  static_assert(!std::is_copy_assignable_v<XRef>,
                "XRef must not be copy assignable (per header).");
}

TEST_F(XRefTest_261, GetPermFlagsCallableOnConstObject_261) {
  const XRef xref;
  // Only verify it is callable and returns an int.
  const int flags = xref.getPermFlags();
  (void)flags;
  SUCCEED();
}

TEST_F(XRefTest_261, SetEncryptionUpdatesPermFlags_Positive_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = 0x12345678;

  // We avoid assuming any specific CryptAlgorithm enumerator exists.
  const auto algo = static_cast<CryptAlgorithm>(0);

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/1,
                     /*encRevisionA=*/2,
                     /*encAlgorithmA=*/algo);

  EXPECT_EQ(xref.getPermFlags(), expectedPermFlags);
}

TEST_F(XRefTest_261, SetEncryptionUpdatesPermFlags_Zero_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = 0;

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/false,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/0,
                     /*encRevisionA=*/0,
                     /*encAlgorithmA=*/static_cast<CryptAlgorithm>(0));

  EXPECT_EQ(xref.getPermFlags(), expectedPermFlags);
}

TEST_F(XRefTest_261, SetEncryptionUpdatesPermFlags_Negative_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = -1;

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/1,
                     /*encRevisionA=*/1,
                     /*encAlgorithmA=*/static_cast<CryptAlgorithm>(0));

  EXPECT_EQ(xref.getPermFlags(), expectedPermFlags);
}

TEST_F(XRefTest_261, SetEncryptionUpdatesPermFlags_IntMin_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = INT_MIN;

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/false,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/-1,
                     /*encRevisionA=*/-1,
                     /*encAlgorithmA=*/static_cast<CryptAlgorithm>(0));

  EXPECT_EQ(xref.getPermFlags(), expectedPermFlags);
}

TEST_F(XRefTest_261, SetEncryptionUpdatesPermFlags_IntMax_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = INT_MAX;

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/INT_MAX,
                     /*encRevisionA=*/INT_MAX,
                     /*encAlgorithmA=*/static_cast<CryptAlgorithm>(0));

  EXPECT_EQ(xref.getPermFlags(), expectedPermFlags);
}

TEST_F(XRefTest_261, SetEncryptionLastCallWinsForPermFlags_261) {
  XRef xref;

  unsigned char fileKeyA[32] = {};
  unsigned char fileKeyB[32] = {};
  const auto algo = static_cast<CryptAlgorithm>(0);

  xref.setEncryption(/*permFlagsA=*/123,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKeyA,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKeyA)),
                     /*encVersionA=*/1,
                     /*encRevisionA=*/2,
                     /*encAlgorithmA=*/algo);
  ASSERT_EQ(xref.getPermFlags(), 123);

  xref.setEncryption(/*permFlagsA=*/456,
                     /*ownerPasswordOkA=*/false,
                     /*fileKeyA=*/fileKeyB,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKeyB)),
                     /*encVersionA=*/3,
                     /*encRevisionA=*/4,
                     /*encAlgorithmA=*/algo);

  EXPECT_EQ(xref.getPermFlags(), 456);
}

TEST_F(XRefTest_261, GetPermFlagsDoesNotMutateState_261) {
  XRef xref;

  unsigned char fileKey[32] = {};
  const int expectedPermFlags = 42;

  xref.setEncryption(expectedPermFlags,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKey,
                     /*keyLengthA=*/static_cast<int>(sizeof(fileKey)),
                     /*encVersionA=*/1,
                     /*encRevisionA=*/1,
                     /*encAlgorithmA=*/static_cast<CryptAlgorithm>(0));

  const int first = xref.getPermFlags();
  const int second = xref.getPermFlags();

  EXPECT_EQ(first, expectedPermFlags);
  EXPECT_EQ(second, expectedPermFlags);
}

}  // namespace