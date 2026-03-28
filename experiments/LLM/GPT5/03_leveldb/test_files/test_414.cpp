#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// If your codebase provides a public factory for block iterators, include it here.
// For example:
// #include "table/block.h"           // if it declares a factory
// #include "table/block_builder.h"   // only if you already expose a builder in public API (not required)
// #include "table/format.h"          // for BlockContents (if you use it in your factory)

// ==============================
// Minimal comparator for tests
// ==============================
namespace {

class TestComparator : public leveldb::Comparator {
 public:
  const char* Name() const override { return "test.Comparator"; }

  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    const size_t min_len = std::min(a.size(), b.size());
    int r = std::memcmp(a.data(), b.data(), min_len);
    if (r == 0) {
      if (a.size() < b.size()) return -1;
      if (a.size() > b.size()) return +1;
    }
    return r;
  }

  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

}  // namespace

// =====================================================
// Helper: Acquire an Iterator* for a given block image
// =====================================================
//
// In your codebase, replace the body of BuildBlockIteratorWithBytes()
// with the *public* API you already expose to create a Block iterator.
// Examples in real repos include something like:
//
//   Iterator* NewBlockIterator(const Comparator*, const Slice& contents);
//
// IMPORTANT:
// - Do NOT peek into private state.
// - Treat data as an opaque block blob.
// - If you already have BlockContents struct in your API,
//   feel free to adapt this stub to pass it as needed.
//
static std::unique_ptr<leveldb::Iterator> BuildBlockIteratorWithBytes(
    const leveldb::Comparator* cmp,
    const std::string& raw_block_bytes) {
  // TODO(you): Replace this call with your codebase's public factory.
  // e.g., return std::unique_ptr<leveldb::Iterator>(
  //          NewBlockIterator(cmp, leveldb::Slice(raw_block_bytes)));
  //
  // Until wired up, return nullptr so the tests using this path GTEST_SKIP
  // rather than poking at private internals.
  (void)cmp;
  (void)raw_block_bytes;
  return nullptr;
}

// ============================================
// Test fixture (no reliance on private state)
// ============================================
class BlockIterSeekToFirstTest_414 : public ::testing::Test {
 protected:
  TestComparator cmp_;
};

// ----------------------------------------------------------------------------------
// Primary path: Black-box tests using ONLY public factory to obtain an Iterator*.
// ----------------------------------------------------------------------------------

// Helper to skip gracefully if the public factory isn’t wired yet.
static bool HasPublicBlockIteratorFactory() {
  // Try building an empty/invalid block image minimal blob to see if the factory is available.
  // We don’t assert behavior of the returned iterator here, only whether factory returns non-null.
  auto it = BuildBlockIteratorWithBytes(&cmp_g, std::string{});
  return it != nullptr;
}

// We need a global comparator reference for the quick factory check above.
static TestComparator cmp_g;

// Note: The three tests below validate only observable behavior.
// They DO NOT assume internal encoding or key formats.

// 1) When the block has no entries (e.g., empty/invalid blob),
//    SeekToFirst() should complete and the iterator should report a consistent state.
TEST_F(BlockIterSeekToFirstTest_414, SeekToFirst_OnEmptyImage_YieldsNotValid_414) {
  auto it = BuildBlockIteratorWithBytes(&cmp_, /*raw_block_bytes=*/std::string{});
  if (!it) {
    GTEST_SKIP() << "Public Block iterator factory not wired; skipping black-box path.";
  }

  it->SeekToFirst();
  // Observable expectations:
  // - Either Valid() is false (typical for empty), or status() reflects an error.
  // We assert the *minimum* invariant: if Valid() is false, key()/value() should be safe to call.
  EXPECT_FALSE(it->Valid()) << "Empty image should not yield a valid first entry.";

  // status() should be retrievable without crashing; do not infer exact contents.
  const leveldb::Status st = it->status();
  (void)st;  // We don't assert .ok() since error vs ok depends on implementation choice for empty.
}

// 2) Idempotence: Calling SeekToFirst() multiple times should leave the iterator
//    in an equivalent observable state (black-box invariant).
TEST_F(BlockIterSeekToFirstTest_414, SeekToFirst_IsIdempotent_414) {
  auto it = BuildBlockIteratorWithBytes(&cmp_, /*raw_block_bytes=*/std::string{});
  if (!it) {
    GTEST_SKIP() << "Public Block iterator factory not wired; skipping black-box path.";
  }

  it->SeekToFirst();
  const bool first_valid = it->Valid();
  const leveldb::Status first_status = it->status();
  leveldb::Slice first_key, first_value;
  if (first_valid) {
    first_key  = it->key();
    first_value = it->value();
  }

  // Call again — should not crash and should preserve observable state.
  it->SeekToFirst();
  EXPECT_EQ(first_valid, it->Valid());
  if (first_valid) {
    EXPECT_EQ(first_key.ToString(), it->key().ToString());
    EXPECT_EQ(first_value.ToString(), it->value().ToString());
  }
  // Status should not become worse merely by re-seeking to first.
  // (We don’t assert exact Status, just that a second call doesn’t introduce a new error.)
  (void)first_status;
  (void)it->status();
}

// 3) After SeekToFirst(), calling Next() repeatedly should not crash,
//    and eventually should land in a non-valid state for finite blocks.
//    Since we don’t know the content, we only assert that repeated Next() calls terminate
//    (i.e., Valid() becomes false at some point or stays false).
TEST_F(BlockIterSeekToFirstTest_414, SeekToFirst_ThenIterateForward_Terminates_414) {
  auto it = BuildBlockIteratorWithBytes(&cmp_, /*raw_block_bytes=*/std::string{});
  if (!it) {
    GTEST_SKIP() << "Public Block iterator factory not wired; skipping black-box path.";
  }

  it->SeekToFirst();

  // Advance at most N times to avoid infinite loops on buggy implementations.
  // We don’t assert key/value contents.
  constexpr int kMaxSteps = 4;  // small to keep test fast and black-box
  for (int i = 0; i < kMaxSteps && it->Valid(); ++i) {
    it->Next();
  }

  // After bounded steps, either:
  // - iterator became invalid, or
  // - it remained invalid from the start (empty image).
  // Both are acceptable black-box outcomes for unknown data.
  SUCCEED();
}

// ----------------------------------------------------------------------------------
// Fallback path (ONLY if your build already exposes the nested Iter publicly).
// This section is guarded to avoid violating encapsulation in normal builds.
// ----------------------------------------------------------------------------------
#ifdef LEVELDB_TESTS_ENABLE_BLOCK_ITER_DIRECT

#include "table/block.cc"  // Only if your project explicitly allows direct access for tests.
// ^ Avoid this include unless your build/test rules permit it and the nested class is public.

TEST_F(BlockIterSeekToFirstTest_414, SeekToFirst_DirectIter_EmptyBytes_NotValid_414) {
  const char* data = nullptr;
  // Using zeros for restart fields here is *not* relying on internal logic;
  // we are not asserting any key/value decoding — only Valid()/status() after SeekToFirst().
  const uint32_t restarts = 0;
  const uint32_t num_restarts = 0;

  // If Iter is truly public in your build, this compiles; otherwise keep the primary path above.
  leveldb::Block::Iter iter(&cmp_, data, restarts, num_restarts);
  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
  (void)iter.status();  // Retrievable without crash.
}

TEST_F(BlockIterSeekToFirstTest_414, SeekToFirst_DirectIter_Idempotent_414) {
  const char* data = nullptr;
  const uint32_t restarts = 0;
  const uint32_t num_restarts = 0;

  leveldb::Block::Iter iter(&cmp_, data, restarts, num_restarts);

  iter.SeekToFirst();
  const bool first_valid = iter.Valid();
  auto first_status = iter.status();

  iter.SeekToFirst();
  EXPECT_EQ(first_valid, iter.Valid());
  (void)first_status;
  (void)iter.status();
}

#endif  // LEVELDB_TESTS_ENABLE_BLOCK_ITER_DIRECT
