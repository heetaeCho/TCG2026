// File: version_edit_setnextfile_test.cc

#include "gtest/gtest.h"
#include "db/version_edit.h"

// If your project uses these public headers, keep them;
// they are only needed for the DecodeFrom roundtrip test.
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <limits>
#include <string>

namespace leveldb {

class VersionEditTest_64 : public ::testing::Test {
protected:
  static std::string EncodeOf(const VersionEdit& ve) {
    std::string out;
    ve.EncodeTo(&out);
    return out;
  }
};

// Verifies that encoding changes when next-file number is set.
TEST_F(VersionEditTest_64, EncodeChangesWhenNextFileSet_64) {
  VersionEdit baseline;
  VersionEdit with_next;

  const std::string encoded_baseline = EncodeOf(baseline);

  with_next.SetNextFile(12345);
  const std::string encoded_with_next = EncodeOf(with_next);

  // Observable effects: non-empty encoding and different from baseline.
  EXPECT_NE(encoded_baseline, encoded_with_next);
  EXPECT_FALSE(encoded_with_next.empty());
}

// Boundary values: 0 and max uint64_t should produce different encodings.
TEST_F(VersionEditTest_64, SettingDifferentValuesProducesDifferentEncodings_64) {
  VersionEdit e_zero;
  VersionEdit e_max;

  e_zero.SetNextFile(0);
  e_max.SetNextFile(std::numeric_limits<uint64_t>::max());

  const std::string enc_zero = EncodeOf(e_zero);
  const std::string enc_max  = EncodeOf(e_max);

  EXPECT_FALSE(enc_zero.empty());
  EXPECT_FALSE(enc_max.empty());
  EXPECT_NE(enc_zero, enc_max);  // Different observable encodings
}

// Setting the value twice should reflect the last call in the observable encoding.
TEST_F(VersionEditTest_64, LastSetWinsOnMultipleCalls_64) {
  VersionEdit e_once;
  e_once.SetNextFile(2);

  VersionEdit e_twice;
  e_twice.SetNextFile(1);
  e_twice.SetNextFile(2);  // Overwrite with the same final value as e_once

  EXPECT_EQ(EncodeOf(e_once), EncodeOf(e_twice));
}

// Clear() removes the effect of SetNextFile from the observable state.
TEST_F(VersionEditTest_64, ClearRemovesNextFileFromEncoding_64) {
  VersionEdit e_with;
  e_with.SetNextFile(42);
  e_with.Clear();

  VersionEdit e_fresh;  // Brand new edit with no fields set

  EXPECT_EQ(EncodeOf(e_fresh), EncodeOf(e_with));
}

// Encode/Decode roundtrip preserves the next-file information in observable form.
TEST_F(VersionEditTest_64, EncodeDecodeRoundtripPreservesNextFile_64) {
  VersionEdit original;
  original.SetNextFile(777);

  const std::string encoded_original = EncodeOf(original);

  VersionEdit decoded;
  Slice input(encoded_original);
  Status st = decoded.DecodeFrom(input);
  ASSERT_TRUE(st.ok()) << st.ToString();

  // Re-encoding the decoded edit should match the original observable encoding.
  EXPECT_EQ(encoded_original, EncodeOf(decoded));
}

}  // namespace leveldb
