// File: db/c_iter_destroy_test.cc

#include <gtest/gtest.h>

// Forward declarations that mirror the provided interface.
// We do NOT implement leveldb_iter_destroy here; we only call it.
class Iterator {
 public:
  virtual ~Iterator() = default;
};

struct leveldb_iterator_t { public: Iterator* rep; };

extern "C" {
  // Provided by the production code (db/c.cc)
  void leveldb_iter_destroy(leveldb_iterator_t* iter);
}

// A test-double for Iterator that records destruction as observable behavior.
class CountingIterator : public Iterator {
 public:
  static int& DestroyedCount() {
    static int count = 0;
    return count;
  }

  ~CountingIterator() override { ++DestroyedCount(); }

  // Helper to reset the counter between tests.
  static void Reset() { DestroyedCount() = 0; }
};

// --------------------------- Tests ---------------------------

TEST(LeveldbIterDestroy_234, DestroysRepAndWrapper_234) {
  // Arrange
  CountingIterator::Reset();
  auto* wrapper = new leveldb_iterator_t;
  wrapper->rep = new CountingIterator();

  // Act
  // Expectation: both wrapper->rep and wrapper itself are destroyed.
  leveldb_iter_destroy(wrapper);

  // Assert
  // Observable behavior: the Iterator-derived object's destructor ran exactly once.
  EXPECT_EQ(1, CountingIterator::DestroyedCount());
}

TEST(LeveldbIterDestroy_234, SafeWhenRepIsNull_234) {
  // Arrange
  CountingIterator::Reset();
  auto* wrapper = new leveldb_iterator_t;
  wrapper->rep = nullptr;

  // Act
  // Expectation: deleting a null rep is a no-op; function should not attempt to
  // access freed memory or crash. We can only assert that no Iterator dtor ran.
  leveldb_iter_destroy(wrapper);

  // Assert
  EXPECT_EQ(0, CountingIterator::DestroyedCount());
}
