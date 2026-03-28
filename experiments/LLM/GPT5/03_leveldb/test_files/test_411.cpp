// File: block_iter_next_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the public headers you normally use to access Block/Iterator.
// We deliberately avoid including private/internal headers.
// If your project exposes Block via a factory (e.g., Block::NewIterator),
// prefer including that header instead.
// Example (adjust as appropriate for your codebase):
// #include "table/block.h"
// #include "leveldb/comparator.h"
// #include "leveldb/iterator.h"

namespace leveldb {
  // Forward declarations to avoid depending on internals.
  // These must match your public API. Adjust includes above if you have them.
  class Comparator;
  class Iterator {
   public:
    virtual ~Iterator() = default;
    virtual bool Valid() const = 0;
    virtual void SeekToFirst() = 0;
    virtual void Next() = 0;
    virtual Slice key() const = 0;
    virtual Slice value() const = 0;
    virtual Status status() const = 0;
  };

  // If your code exposes a way to construct a Block::Iter via a factory (e.g., Block::NewIterator),
  // prefer using that. Here we forward-declare a minimal Block with a factory to stay black-box.
  class Block {
   public:
    // Typical LevelDB pattern: Block::NewIterator(const Comparator*).
    // If your real signature differs, update the call site in the fixture accordingly.
    Iterator* NewIterator(const Comparator* comparator) const;
  };
}  // namespace leveldb

using ::testing::HasSubstr;

class BlockIterNextTest_411 : public ::testing::Test {
 protected:
  // Helper to obtain an iterator purely through public factory.
  // NOTE: Replace construction with the actual way your code creates a Block and iterator.
  // Keep everything black-box: do not touch internal buffers or fields.
  std::unique_ptr<leveldb::Iterator> MakeIteratorInvalidByDefault() {
    // In many codebases, you'd build a minimal/empty Block and then call NewIterator.
    // Here we assume a default-constructed Block is enough to get an iterator.
    // If your Block requires parameters, use whatever minimal public ctor/builder exists.
    leveldb::Block blk;
    const leveldb::Comparator* cmp = nullptr;  // Comparator not needed for the precondition test path
    return std::unique_ptr<leveldb::Iterator>(blk.NewIterator(cmp));
  }

  std::unique_ptr<leveldb::Iterator> MakeIteratorPossiblyValid() {
    // Same creation path; the iterator may or may not become valid after SeekToFirst()
    // depending on the underlying block contents provided by the public APIs.
    auto it = MakeIteratorInvalidByDefault();
    if (it) it->SeekToFirst();
    return it;
  }
};

// -----------------------------
// Tests
// -----------------------------

// Verifies: Next requires Valid() == true beforehand.
// Behavior: Calling Next() when invalid should trigger the assert in debug builds.
// Name includes TEST_ID = 411 per requirement.
TEST_F(BlockIterNextTest_411, Next_RequiresValid_Precondition_411) {
  auto it = MakeIteratorInvalidByDefault();
  ASSERT_NE(it, nullptr) << "Iterator creation failed via public API";

#ifndef NDEBUG
  // We expect a debug assert death if the iterator is invalid.
  if (!it->Valid()) {
    ASSERT_DEATH({ it->Next(); }, "");  // message may be empty depending on assert implementation
  } else {
    GTEST_SKIP() << "Iterator unexpectedly valid by default; cannot exercise invalid precondition path.";
  }
#else
  GTEST_SKIP() << "Assertions are compiled out (NDEBUG); skipping death test.";
#endif
}

// Verifies: In normal operation (when Valid() is true), calling Next() should not
// corrupt the iterator's status (observable via status().ok()).
// We do not assume anything about key/value movement—only that status remains OK.
TEST_F(BlockIterNextTest_411, Next_DoesNotCorruptStatus_WhenValid_411) {
  auto it = MakeIteratorPossiblyValid();
  ASSERT_NE(it, nullptr) << "Iterator creation failed via public API";

  if (!it->Valid()) {
    GTEST_SKIP() << "Could not reach a valid state using only public API; "
                    "skipping success-path check to avoid inferring internals.";
  }

  // Status before
  auto s_before = it->status();

  // Exercise Next on a valid iterator; should not assert and should keep status sane.
  // If Next makes the iterator invalid (e.g., at end), that's fine—we only check status.
  ASSERT_NO_FATAL_FAILURE(it->Next());

  auto s_after = it->status();
  // We only assert that status does not become 'not ok' as an externally observable regression.
  // If your Status type has ok() method (LevelDB-style), use that. Otherwise, adapt the check.
  EXPECT_TRUE(s_after.ok()) << "Iterator status became non-OK after Next()";
  if (s_before.ok()) {
    EXPECT_TRUE(s_after.ok()) << "Status regressed from OK to non-OK after Next()";
  }
}
