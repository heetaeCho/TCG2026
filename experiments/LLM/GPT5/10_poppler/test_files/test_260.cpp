// File: test_xref_isEncrypted_260.cpp
// TEST_ID: 260

#include <gtest/gtest.h>

#include "poppler/XRef.h"

namespace {

class XRefTest_260 : public ::testing::Test {
protected:
  // Helper to provide a stable, valid file key buffer.
  static const unsigned char *fileKey32() {
    static unsigned char key[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    };
    return key;
  }

  // We intentionally avoid relying on specific CryptAlgorithm enumerators
  // (treating the class as a black box). Using a cast keeps the test robust
  // across enum value naming differences.
  static CryptAlgorithm someAlgorithm() {
    return static_cast<CryptAlgorithm>(0);
  }
};

// Normal operation: the method is callable and returns a stable value.
TEST_F(XRefTest_260, IsEncrypted_IsCallableAndStable_260) {
  XRef xref;
  const bool v1 = xref.isEncrypted();
  const bool v2 = xref.isEncrypted();
  const bool v3 = xref.isEncrypted();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

// Normal operation: markUnencrypted should result in a non-encrypted state.
TEST_F(XRefTest_260, MarkUnencrypted_MakesIsEncryptedFalse_260) {
  XRef xref;

  xref.markUnencrypted();

  EXPECT_FALSE(xref.isEncrypted());
}

// Normal operation: setEncryption should result in an encrypted state.
TEST_F(XRefTest_260, SetEncryption_MakesIsEncryptedTrue_260) {
  XRef xref;

  const int permFlags = 0;
  const bool ownerPasswordOk = false;
  const int keyLength = 16;     // arbitrary non-negative length
  const int encVersion = 1;     // arbitrary
  const int encRevision = 2;    // arbitrary

  xref.setEncryption(permFlags, ownerPasswordOk, fileKey32(), keyLength, encVersion,
                     encRevision, someAlgorithm());

  EXPECT_TRUE(xref.isEncrypted());
}

// Boundary-ish: setEncryption called with keyLength=0 should still be observable
// and should indicate encrypted if encryption is set (no assumptions beyond name).
TEST_F(XRefTest_260, SetEncryption_WithZeroKeyLength_StillEncrypted_260) {
  XRef xref;

  const int permFlags = 0;
  const bool ownerPasswordOk = true;
  const int keyLength = 0;      // boundary
  const int encVersion = 0;
  const int encRevision = 0;

  xref.setEncryption(permFlags, ownerPasswordOk, fileKey32(), keyLength, encVersion,
                     encRevision, someAlgorithm());

  EXPECT_TRUE(xref.isEncrypted());
}

// State transition: markUnencrypted after setEncryption should clear encryption.
TEST_F(XRefTest_260, SetEncryptionThenMarkUnencrypted_ClearsEncryptedState_260) {
  XRef xref;

  xref.setEncryption(/*permFlagsA=*/0,
                     /*ownerPasswordOkA=*/false,
                     /*fileKeyA=*/fileKey32(),
                     /*keyLengthA=*/16,
                     /*encVersionA=*/1,
                     /*encRevisionA=*/2,
                     /*encAlgorithmA=*/someAlgorithm());
  ASSERT_TRUE(xref.isEncrypted());

  xref.markUnencrypted();

  EXPECT_FALSE(xref.isEncrypted());
}

// State transition: setting encryption again after markUnencrypted should re-enable it.
TEST_F(XRefTest_260, MarkUnencryptedThenSetEncryption_ReEnablesEncryptedState_260) {
  XRef xref;

  xref.markUnencrypted();
  ASSERT_FALSE(xref.isEncrypted());

  xref.setEncryption(/*permFlagsA=*/123,
                     /*ownerPasswordOkA=*/true,
                     /*fileKeyA=*/fileKey32(),
                     /*keyLengthA=*/32,
                     /*encVersionA=*/4,
                     /*encRevisionA=*/5,
                     /*encAlgorithmA=*/someAlgorithm());

  EXPECT_TRUE(xref.isEncrypted());
}

}  // namespace