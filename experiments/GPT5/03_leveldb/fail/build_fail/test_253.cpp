// File: db/options_set_comparator_test_253.cc

#include <gtest/gtest.h>
#include "leveldb/options.h"

// The following declarations mirror the provided interface snippets.
// We are NOT re-implementing logic—just exposing the public fields/types
// needed to observe effects of the C API call.
extern "C" {

// From db/c.cc (provided):
struct leveldb_options_t { leveldb::Options rep; };

// From db/c.cc (provided; concrete subclass of Comparator):
struct leveldb_comparator_t : public leveldb::Comparator {
  void* state_;
  void (*destructor_)(void*);
  int (*compare_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);
  ~leveldb_comparator_t() override;
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override;
  const char* Name() const override;
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override;
  void FindShortSuccessor(std::string* key) const override;
};

// Target function under test:
void leveldb_options_set_comparator(leveldb_options_t* opt, leveldb_comparator_t* cmp);

} // extern "C"

// Test 1: Normal operation — sets the comparator pointer to the provided comparator.
TEST(LevelDB_OptionsSetComparator_253, SetsCustomComparator_253) {
  leveldb_options_t opt;                 // Uses default-constructed Options
  leveldb_comparator_t cmp_instance;     // Concrete comparator object (already implemented elsewhere)

  // Precondition sanity: the comparator may have some default; we don't assert it.
  leveldb_options_set_comparator(&opt, &cmp_instance);

  // Observable effect: public field points to the comparator we passed in.
  EXPECT_EQ(opt.rep.comparator, static_cast<const leveldb::Comparator*>(&cmp_instance));
}

// Test 2: Overwrite behavior — calling again replaces the previous comparator pointer.
TEST(LevelDB_OptionsSetComparator_253, OverwritesExistingComparator_253) {
  leveldb_options_t opt;
  leveldb_comparator_t cmp_a;
  leveldb_comparator_t cmp_b;

  leveldb_options_set_comparator(&opt, &cmp_a);
  ASSERT_EQ(opt.rep.comparator, static_cast<const leveldb::Comparator*>(&cmp_a));

  leveldb_options_set_comparator(&opt, &cmp_b);
  EXPECT_EQ(opt.rep.comparator, static_cast<const leveldb::Comparator*>(&cmp_b));
}

// Test 3: Boundary condition — accepting a null comparator pointer sets the field to nullptr.
TEST(LevelDB_OptionsSetComparator_253, AcceptsNullComparator_253) {
  leveldb_options_t opt;

  // Ensure it doesn't crash and updates to nullptr.
  leveldb_options_set_comparator(&opt, /*cmp=*/nullptr);
  EXPECT_EQ(opt.rep.comparator, nullptr);
}

// Test 4: Non-interference — setting the comparator does not modify unrelated Options fields.
TEST(LevelDB_OptionsSetComparator_253, DoesNotAffectOtherOptions_253) {
  leveldb_options_t opt;
  // Capture some unrelated fields' initial values (public, observable).
  const bool create_if_missing_before = opt.rep.create_if_missing;
  const size_t write_buffer_size_before = opt.rep.write_buffer_size;
  const int max_open_files_before = opt.rep.max_open_files;
  const size_t block_size_before = opt.rep.block_size;
  const int block_restart_interval_before = opt.rep.block_restart_interval;
  const size_t max_file_size_before = opt.rep.max_file_size;
  const auto compression_before = opt.rep.compression;
  const int zstd_level_before = opt.rep.zstd_compression_level;
  const bool reuse_logs_before = opt.rep.reuse_logs;

  leveldb_comparator_t cmp_instance;
  leveldb_options_set_comparator(&opt, &cmp_instance);

  // Verify unrelated fields remain unchanged (observable through the public API).
  EXPECT_EQ(opt.rep.create_if_missing, create_if_missing_before);
  EXPECT_EQ(opt.rep.write_buffer_size, write_buffer_size_before);
  EXPECT_EQ(opt.rep.max_open_files, max_open_files_before);
  EXPECT_EQ(opt.rep.block_size, block_size_before);
  EXPECT_EQ(opt.rep.block_restart_interval, block_restart_interval_before);
  EXPECT_EQ(opt.rep.max_file_size, max_file_size_before);
  EXPECT_EQ(opt.rep.compression, compression_before);
  EXPECT_EQ(opt.rep.zstd_compression_level, zstd_level_before);
  EXPECT_EQ(opt.rep.reuse_logs, reuse_logs_before);
}
