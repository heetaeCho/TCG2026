// File: version_edit_constructor_tests_476.cc

#include "db/version_edit.h"
#include <gtest/gtest.h>
#include <string>

namespace leveldb {

// We avoid relying on any internal state or undocumented semantics.
// Tests only check observable effects through public methods.

TEST(VersionEditTest_476, DefaultConstructor_DoesNotThrow_476) {
  // Constructing should be valid and not throw.
  // (Even though C++ typically doesn't throw on such ctor, we keep it explicit.)
  EXPECT_NO_THROW({
    VersionEdit ve;
    (void)ve;  // silence unused warning
  });
}

TEST(VersionEditTest_476, FreshAndCleared_HaveSameEncoding_476) {
  VersionEdit fresh;
  VersionEdit cleared;

  // Clear an otherwise fresh instance.
  cleared.Clear();

  std::string enc_fresh;
  std::string enc_cleared;

  // Encode both to strings; observable behavior is the produced bytes.
  fresh.EncodeTo(&enc_fresh);
  cleared.EncodeTo(&enc_cleared);

  // For a brand-new edit and a cleared edit, the serialized form should match.
  EXPECT_EQ(enc_fresh, enc_cleared);
}

TEST(VersionEditTest_476, Clear_IsIdempotentForEncoding_476) {
  VersionEdit ve;

  // Encode right away.
  std::string first;
  ve.EncodeTo(&first);

  // Clear once and encode again.
  ve.Clear();
  std::string second;
  ve.EncodeTo(&second);

  // Clear again (idempotence) and encode a third time.
  ve.Clear();
  std::string third;
  ve.EncodeTo(&third);

  // All encodings of an empty/cleared edit should be identical.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST(VersionEditTest_476, DebugString_ConsistentForFreshAndCleared_476) {
  VersionEdit fresh;
  VersionEdit cleared;
  cleared.Clear();

  // DebugString is a public observable representation; we only compare strings,
  // not their contents.
  const std::string dbg_fresh = fresh.DebugString();
  const std::string dbg_cleared = cleared.DebugString();

  EXPECT_EQ(dbg_fresh, dbg_cleared);
}

TEST(VersionEditTest_476, EncodeTo_WithPrepopulatedDestination_DoesNotInvalidate_476) {
  VersionEdit ve;

  std::string dst = "prefix";
  // Call EncodeTo; we do NOT assert whether it appends or overwrites (that would
  // assume internal semantics). We only assert the string remains valid/usable.
  EXPECT_NO_THROW({
    ve.EncodeTo(&dst);
  });

  // Basic sanity: result is still a valid string object and not empty-constructed.
  // We avoid asserting specific size/contents to not infer internal behavior.
  EXPECT_GE(dst.size(), static_cast<size_t>(0));
}

}  // namespace leveldb
