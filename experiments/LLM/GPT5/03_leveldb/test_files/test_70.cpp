// File: version_set_current_test_70.cc

#include "db/version_set.h"

#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/options.h"

#include <gtest/gtest.h>

namespace leveldb {

class VersionSetTest_70 : public ::testing::Test {
protected:
  // Minimal, valid collaborators to construct VersionSet without exercising
  // any internal behavior.
  Options options_;
  InternalKeyComparator* ikc_ = nullptr;

  void SetUp() override {
    options_.env = Env::Default();  // Provide a valid Env pointer.
    // Use LevelDB's built-in bytewise comparator to build InternalKeyComparator.
    static InternalKeyComparator ikc(BytewiseComparator());
    ikc_ = &ikc;
  }
};

// [Normal] Immediately after construction, current() should reflect the
// constructor-initialized state (per provided snippet), which sets current_ to nullptr.
TEST_F(VersionSetTest_70, CurrentIsNullAfterConstruction_70) {
  TableCache* table_cache = nullptr;  // Not needed for this accessor test.
  VersionSet vs("testdb", &options_, table_cache, ikc_);

  // Observable behavior: current() returns the current Version*.
  // Based on the provided constructor snippet, it should be nullptr initially.
  EXPECT_EQ(vs.current(), nullptr);
}

// [Stability/Idempotence] Multiple calls to current() should return the same pointer
// without side effects.
TEST_F(VersionSetTest_70, CurrentIsStableAcrossCalls_70) {
  TableCache* table_cache = nullptr;
  VersionSet vs("testdb", &options_, table_cache, ikc_);

  Version* first = vs.current();
  Version* second = vs.current();
  EXPECT_EQ(first, second);
}

}  // namespace leveldb
