// File: version_edit_set_comparator_name_test_61.cc

#include <gtest/gtest.h>
#include "db/version_edit.h"
#include "leveldb/slice.h"

namespace leveldb {

class VersionEditTest_61 : public ::testing::Test {
 protected:
  static bool DebugStringContains(const VersionEdit& ve, const std::string& needle) {
    // Use only the public interface to observe state
    return ve.DebugString().find(needle) != std::string::npos;
  }

  static VersionEdit RoundTrip(const VersionEdit& src, Status* out_status = nullptr) {
    std::string encoded;
    src.EncodeTo(&encoded);
    VersionEdit dst;
    Status s = dst.DecodeFrom(Slice(encoded));
    if (out_status) *out_status = s;
    return dst;
  }
};

// Verifies that setting a comparator name is observable via DebugString,
// and survives an EncodeTo/DecodeFrom round trip.
TEST_F(VersionEditTest_61, SetComparatorName_RoundTripPreserves_61) {
  VersionEdit ve;
  const std::string kName = "leveldb.BytewiseComparator";

  ve.SetComparatorName(Slice(kName));
  EXPECT_TRUE(DebugStringContains(ve, kName)) << "Comparator name should appear in DebugString()";

  Status st;
  VersionEdit decoded = RoundTrip(ve, &st);
  EXPECT_TRUE(st.ok());
  EXPECT_TRUE(DebugStringContains(decoded, kName))
      << "Comparator name should survive EncodeTo/DecodeFrom";
}

// Verifies that Clear() removes any observable trace of the previously set comparator
// through the public DebugString().
TEST_F(VersionEditTest_61, Clear_RemovesComparatorFromDebugString_61) {
  VersionEdit ve;
  const std::string kName = "leveldb.BytewiseComparator";
  ve.SetComparatorName(Slice(kName));

  ASSERT_TRUE(DebugStringContains(ve, kName));

  ve.Clear();
  EXPECT_FALSE(DebugStringContains(ve, kName))
      << "After Clear(), DebugString() should not contain the previously set comparator name";
}

// Setting comparator twice should reflect the latest value (observable via DebugString())
// and round-trip correctly.
TEST_F(VersionEditTest_61, SetComparatorName_Overwrite_61) {
  VersionEdit ve;
  const std::string first = "first.Comparator";
  const std::string second = "second.Comparator";

  ve.SetComparatorName(Slice(first));
  ASSERT_TRUE(DebugStringContains(ve, first));

  ve.SetComparatorName(Slice(second));
  EXPECT_FALSE(DebugStringContains(ve, first))
      << "Old name should no longer be observable after overwrite";
  EXPECT_TRUE(DebugStringContains(ve, second));

  VersionEdit decoded = RoundTrip(ve);
  EXPECT_TRUE(DebugStringContains(decoded, second))
      << "Latest comparator name should survive EncodeTo/DecodeFrom";
}

// Encoding should change after setting a comparator name (observable via EncodeTo output bytes).
// This avoids assuming any specific encoding format while still confirming an externally visible effect.
TEST_F(VersionEditTest_61, EncodeOutput_ChangesWhenComparatorSet_61) {
  VersionEdit empty_edit;
  std::string empty_encoded;
  empty_edit.EncodeTo(&empty_encoded);

  VersionEdit with_comp;
  with_comp.SetComparatorName(Slice("cmp.X"));
  std::string with_comp_encoded;
  with_comp.EncodeTo(&with_comp_encoded);

  EXPECT_NE(empty_encoded, with_comp_encoded)
      << "EncodeTo output should differ once a comparator name is set";
}

}  // namespace leveldb
