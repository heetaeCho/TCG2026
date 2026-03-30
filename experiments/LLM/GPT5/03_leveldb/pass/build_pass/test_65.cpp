// File: db/version_edit_set_last_sequence_test.cc

#include <gtest/gtest.h>
#include <limits>
#include <string>

// Assuming the LevelDB public headers are available as in the codebase.
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using leveldb::Slice;
using leveldb::Status;
using leveldb::VersionEdit;
using leveldb::SequenceNumber;

class VersionEditTest_65 : public ::testing::Test {};

// Verifies baseline encode when nothing is set (useful to compare against SetLastSequence effects).
TEST_F(VersionEditTest_65, EncodeIsEmptyWhenNoFieldsSet_65) {
  VersionEdit edit;
  std::string encoded;
  edit.EncodeTo(&encoded);
  EXPECT_TRUE(encoded.empty());
}

// Normal operation: setting a reasonable sequence number makes EncodeTo produce non-empty data.
TEST_F(VersionEditTest_65, SetLastSequence_EncodesNonEmpty_65) {
  VersionEdit edit;
  edit.SetLastSequence(static_cast<SequenceNumber>(100));

  std::string encoded;
  edit.EncodeTo(&encoded);

  EXPECT_FALSE(encoded.empty());
}

// Boundary: zero sequence should round-trip through Encode/Decode unchanged.
TEST_F(VersionEditTest_65, RoundTrip_PreservesZeroSequence_65) {
  VersionEdit edit1;
  edit1.SetLastSequence(static_cast<SequenceNumber>(0));

  std::string encoded1;
  edit1.EncodeTo(&encoded1);
  ASSERT_FALSE(encoded1.empty());  // observable effect

  VersionEdit edit2;
  Status s = edit2.DecodeFrom(Slice(encoded1));
  ASSERT_TRUE(s.ok());

  std::string encoded2;
  edit2.EncodeTo(&encoded2);

  EXPECT_EQ(encoded1, encoded2);   // black-box equality via encoding
}

// Boundary: max sequence should round-trip through Encode/Decode unchanged.
TEST_F(VersionEditTest_65, RoundTrip_PreservesMaxSequence_65) {
  const SequenceNumber kMax = std::numeric_limits<SequenceNumber>::max();

  VersionEdit edit1;
  edit1.SetLastSequence(kMax);

  std::string encoded1;
  edit1.EncodeTo(&encoded1);
  ASSERT_FALSE(encoded1.empty());

  VersionEdit edit2;
  Status s = edit2.DecodeFrom(Slice(encoded1));
  ASSERT_TRUE(s.ok());

  std::string encoded2;
  edit2.EncodeTo(&encoded2);

  EXPECT_EQ(encoded1, encoded2);
}

// Observable behavior: calling SetLastSequence again overwrites the previously encoded value.
TEST_F(VersionEditTest_65, SetLastSequence_OverwritesPreviousValue_65) {
  VersionEdit edit;

  std::string first;
  edit.SetLastSequence(static_cast<SequenceNumber>(1));
  edit.EncodeTo(&first);
  ASSERT_FALSE(first.empty());

  std::string second;
  edit.SetLastSequence(static_cast<SequenceNumber>(2));
  edit.EncodeTo(&second);
  ASSERT_FALSE(second.empty());

  // Encoded outputs should differ because the observable state changed.
  EXPECT_NE(first, second);

  // And the later encoding should be stable on decode/encode round-trip.
  VersionEdit decoded;
  ASSERT_TRUE(decoded.DecodeFrom(Slice(second)).ok());
  std::string reencoded;
  decoded.EncodeTo(&reencoded);
  EXPECT_EQ(second, reencoded);
}
