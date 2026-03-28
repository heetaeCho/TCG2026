// File: ./TestProjects/ninja/src/cleaned_files_count_test_161.cc

#include "clean.h"
#include "build.h"
#include "test.h"

#include <string>

// Fixture dedicated to testing Cleaner::cleaned_files_count().
struct CleanerTest_161 : public StateTestWithBuiltinRules {
  VirtualFileSystem fs_;
  BuildConfig config_;

  void SetUp() override {
    config_.verbosity = BuildConfig::QUIET;
  }
};

// Verifies that a newly constructed Cleaner starts with zero cleaned files.
TEST_F(CleanerTest_161, InitialCountIsZero_161) {
  // Simple graph is enough; actual edges are not important for this test.
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
                                      "build out: cat in\n"));

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

// Verifies that after CleanAll(), cleaned_files_count() reflects the number
// of files actually removed, and that a second CleanAll() resets the count.
TEST_F(CleanerTest_161, CountMatchesRemovedFilesOnCleanAll_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
                                      "build in1: cat src1\n"
                                      "build out1: cat in1\n"
                                      "build in2: cat src2\n"
                                      "build out2: cat in2\n"));

  // Create the files that can be cleaned.
  fs_.Create("in1", "");
  fs_.Create("out1", "");
  fs_.Create("in2", "");
  fs_.Create("out2", "");

  Cleaner cleaner(&state_, config_, &fs_);
  ASSERT_EQ(0, cleaner.cleaned_files_count());

  // First CleanAll: some files should be cleaned.
  EXPECT_EQ(0, cleaner.CleanAll());
  int cleaned_count_first = cleaner.cleaned_files_count();

  // The accessor should reflect the number of removed files.
  EXPECT_GT(cleaned_count_first, 0);
  EXPECT_EQ(static_cast<size_t>(cleaned_count_first),
            fs_.files_removed_.size());

  // Clear the collaborator’s record and run CleanAll again.
  fs_.files_removed_.clear();
  EXPECT_EQ(0u, fs_.files_removed_.size());

  EXPECT_EQ(0, cleaner.CleanAll());
  int cleaned_count_second = cleaner.cleaned_files_count();

  // When nothing is left to clean, accessor should report zero.
  EXPECT_EQ(0, cleaned_count_second);
  EXPECT_EQ(0u, fs_.files_removed_.size());
}

// Verifies that cleaned_files_count() reports the number of files cleaned
// by the last CleanTargets() call, and that it is reset when no files are
// cleaned in a subsequent call.
TEST_F(CleanerTest_161, CountResetsBetweenCleanTargets_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
                                      "build in1: cat src1\n"
                                      "build out1: cat in1\n"));

  fs_.Create("in1", "");
  fs_.Create("out1", "");

  Cleaner cleaner(&state_, config_, &fs_);
  ASSERT_EQ(0, cleaner.cleaned_files_count());

  const char* targets[] = {"out1"};

  // First call should clean both in1 and out1.
  EXPECT_EQ(0, cleaner.CleanTargets(1, const_cast<char**>(targets)));
  int cleaned_count_first = cleaner.cleaned_files_count();

  EXPECT_GT(cleaned_count_first, 0);
  EXPECT_EQ(static_cast<size_t>(cleaned_count_first),
            fs_.files_removed_.size());

  // Clear removed set and call again; nothing should be cleaned now.
  fs_.files_removed_.clear();
  EXPECT_EQ(0u, fs_.files_removed_.size());

  EXPECT_EQ(0, cleaner.CleanTargets(1, const_cast<char**>(targets)));
  int cleaned_count_second = cleaner.cleaned_files_count();

  EXPECT_EQ(0, cleaned_count_second);
  EXPECT_EQ(0u, fs_.files_removed_.size());
}

// Verifies that in dry-run mode, cleaned_files_count() still reports how
// many files *would* have been cleaned, even though the DiskInterface
// does not actually remove them.
TEST_F(CleanerTest_161, DryRunCountsWithoutRemovingFiles_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
                                      "build in1: cat src1\n"
                                      "build out1: cat in1\n"
                                      "build in2: cat src2\n"
                                      "build out2: cat in2\n"));

  fs_.Create("in1", "");
  fs_.Create("out1", "");
  fs_.Create("in2", "");
  fs_.Create("out2", "");

  config_.dry_run = true;
  Cleaner cleaner(&state_, config_, &fs_);
  ASSERT_EQ(0, cleaner.cleaned_files_count());

  EXPECT_EQ(0, cleaner.CleanAll());
  int cleaned_count = cleaner.cleaned_files_count();

  // Even in dry-run mode, the accessor should report files that would be cleaned.
  EXPECT_GT(cleaned_count, 0);

  // However, the DiskInterface should not have removed anything.
  EXPECT_EQ(0u, fs_.files_removed_.size());

  // The files should still exist on the virtual filesystem.
  std::string err;
  EXPECT_LT(0, fs_.Stat("in1", &err));
  EXPECT_LT(0, fs_.Stat("out1", &err));
  EXPECT_LT(0, fs_.Stat("in2", &err));
  EXPECT_LT(0, fs_.Stat("out2", &err));
}
