// File: memtable_unref_test_104.cc

#include "db/memtable.h"
#include "db/dbformat.h"          // InternalKeyComparator
#include "leveldb/comparator.h"   // BytewiseComparator
#include "gtest/gtest.h"

using namespace leveldb;

namespace {

class MemTableTest_104 : public ::testing::Test {
protected:
  InternalKeyComparator ikc_{BytewiseComparator()};

  MemTable* NewMem() {
    // ctor is public; dtor is private — we must manage lifetime via Ref/Unref.
    return new MemTable(ikc_);
  }
};

// [Normal] Deleting when refcount reaches zero after a matching Ref.
TEST_F(MemTableTest_104, UnrefDeletesAtZero_104) {
  MemTable* m = NewMem();
  m->Ref();          // observable: increments internal refcount
  // When refcount goes to zero, Unref() self-deletes. No crash/UB here.
  m->Unref();
  // We cannot dereference m after this (object may be deleted). Test ends here.
}

// [Boundary] When there are remaining references, Unref should NOT delete yet;
// the object must remain usable for other public calls.
TEST_F(MemTableTest_104, UnrefWhileRefsRemain_ObjectUsable_104) {
  MemTable* m = NewMem();
  m->Ref();
  m->Ref();  // refcount == 2

  m->Unref(); // refcount == 1; should NOT delete
  // Object should still be usable via public methods.
  // We don't assume any internal details; just that this call should not crash.
  (void)m->ApproximateMemoryUsage();

  // Final Unref should delete the object.
  m->Unref();
}

// [Boundary/Stress] Multiple Refs/Unrefs balance: still usable until the last Unref.
TEST_F(MemTableTest_104, MultipleRefsThenUnrefs_StillAliveUntilFinal_104) {
  MemTable* m = NewMem();
  m->Ref();
  m->Ref();
  m->Ref();  // refcount == 3

  m->Unref(); // -> 2
  (void)m->ApproximateMemoryUsage();

  m->Unref(); // -> 1
  (void)m->ApproximateMemoryUsage();

  // Last Unref should delete.
  m->Unref();
}

// [Exceptional] Calling Unref without a prior Ref should trigger the assert.
// This is observable as process death in debug builds.
TEST_F(MemTableTest_104, UnrefWithoutRef_TriggersAssert_104) {
#if !defined(NDEBUG)
  MemTable* m = NewMem();
  // Expect the assert in Unref() to fire (refs_ goes negative), causing death.
  EXPECT_DEATH({ m->Unref(); }, "");  // pattern left empty: any assert/abort
  // No cleanup necessary; death ends that sub-process.
#else
  GTEST_SKIP() << "Assertions are disabled (NDEBUG); skip death test.";
#endif
}

} // namespace
