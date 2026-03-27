// File: db_options_set_max_file_size_test.cc

#include <gtest/gtest.h>
#include <limits>

// We include the implementation unit so that the C wrapper type `leveldb_options_t`
// and the tested function are visible to the test TU, as shown in the prompt’s snippets.
// This avoids re-implementing any internals or relying on private state.
#include "db/c.cc"

using ::testing::Test;

class OptionsSetMaxFileSizeTest_265 : public Test {
protected:
  leveldb_options_t opt{}; // `rep` will default-construct `leveldb::Options`
};

// [Normal] Setting to a typical multi‑MB size should be reflected in the observable field.
TEST_F(OptionsSetMaxFileSizeTest_265, SetTypicalSize_265) {
  const size_t kEightMB = 8u * 1024u * 1024u;

  leveldb_options_set_max_file_size(&opt, kEightMB);

  EXPECT_EQ(opt.rep.max_file_size, kEightMB)
      << "max_file_size should equal the value passed to the C API setter";
}

// [Normal] Multiple calls should overwrite the previous value (latest call wins).
TEST_F(OptionsSetMaxFileSizeTest_265, OverwriteExistingValue_265) {
  const size_t first = 1u * 1024u * 1024u;
  const size_t second = 3u * 1024u * 1024u;

  leveldb_options_set_max_file_size(&opt, first);
  EXPECT_EQ(opt.rep.max_file_size, first);

  leveldb_options_set_max_file_size(&opt, second);
  EXPECT_EQ(opt.rep.max_file_size, second);
}

// [Boundary] Setting to zero should be accepted by the setter (no validation in interface).
TEST_F(OptionsSetMaxFileSizeTest_265, SetZero_265) {
  leveldb_options_set_max_file_size(&opt, 0u);
  EXPECT_EQ(opt.rep.max_file_size, 0u);
}

// [Boundary] Setting to size_t::max should be stored exactly (no truncation).
TEST_F(OptionsSetMaxFileSizeTest_265, SetMaxSizeT_265) {
  const size_t kMax = std::numeric_limits<size_t>::max();
  leveldb_options_set_max_file_size(&opt, kMax);
  EXPECT_EQ(opt.rep.max_file_size, kMax);
}

// [Exceptional] Passing a null options pointer is an interface misuse; the function
// will dereference it. Verify behavior via a death test if supported on this platform.
TEST_F(OptionsSetMaxFileSizeTest_265, NullPointerDeath_265) {
#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH_IF_SUPPORTED(
      leveldb_options_set_max_file_size(nullptr, 1234u),
      ".*");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}
