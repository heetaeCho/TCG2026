// version_set_manifest_file_number_test_71.cc
#include <gtest/gtest.h>

// Include the interface under test.
#include "db/version_set.h"

// Minimal stubs for constructor collaborators (no internal behavior).
namespace leveldb {
class Env {};
struct Options { Env* env = nullptr; };
class TableCache {};
class InternalKeyComparator {
 public:
  InternalKeyComparator() = default;
  InternalKeyComparator(const InternalKeyComparator&) = default;
};
}  // namespace leveldb

using namespace leveldb;

class VersionSetTest_71 : public ::testing::Test {
 protected:
  Env env_;
  Options options_;
  TableCache cache_;
  InternalKeyComparator cmp_;
  std::string dbname_ = "test-db";

  void SetUp() override {
    options_.env = &env_;
  }
};

// Normal operation: Newly constructed VersionSet should expose the initial
// manifest file number via ManifestFileNumber(). The provided interface
// (constructor member-init list) indicates this starts at 0 and is later
// set by Recover().
TEST_F(VersionSetTest_71, ManifestFileNumber_DefaultIsZero_71) {
  VersionSet vs(dbname_, &options_, &cache_, &cmp_);
  EXPECT_EQ(static_cast<uint64_t>(0), vs.ManifestFileNumber());
}

// Boundary/const-correctness & stability: Calling the accessor on a const
// reference should compile and return the same value across repeated calls.
// (No assumptions about internal mutation.)
TEST_F(VersionSetTest_71, ManifestFileNumber_IsConstAndStable_71) {
  VersionSet vs(dbname_, &options_, &cache_, &cmp_);
  const VersionSet& cvs = vs;

  uint64_t first = cvs.ManifestFileNumber();
  uint64_t second = cvs.ManifestFileNumber();
  EXPECT_EQ(first, second);
  EXPECT_EQ(static_cast<uint64_t>(0), first);
}

// Compile-time interface check: return type is uint64_t (no runtime behavior inferred).
TEST_F(VersionSetTest_71, ManifestFileNumber_ReturnTypeIsUint64_71) {
  VersionSet vs(dbname_, &options_, &cache_, &cmp_);
  static_assert(std::is_same<decltype(vs.ManifestFileNumber()), uint64_t>::value,
                "ManifestFileNumber() must return uint64_t");
  (void)vs;  // silence unused warning when only static_assert is compiled
}
