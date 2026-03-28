// File: ./TestProjects/ninja/src/clean_is_verbose_test.cc

#include "gtest/gtest.h"

#include "clean.h"
#include "build.h"

// NOTE:
// We treat Cleaner as a black box and only use the public interface.
// We only construct Cleaner and call IsVerbose(), without relying on any
// internal state or re-implementing its logic.

namespace {

// Helper to construct a Cleaner with a given BuildConfig.
// We pass nullptr for State and DiskInterface since IsVerbose()
// only depends on the configuration and not on those collaborators.
Cleaner MakeCleaner(const BuildConfig& config) {
  return Cleaner(/*state=*/nullptr, config, /*disk_interface=*/nullptr);
}

// QUIET + dry_run == false → not verbose
TEST(CleanerIsVerboseTest_162, QuietAndNoDryRun_IsNotVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::QUIET;
  config.dry_run = false;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// QUIET + dry_run == true → still not verbose
TEST(CleanerIsVerboseTest_162, QuietAndDryRun_IsNotVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::QUIET;
  config.dry_run = true;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// NORMAL + dry_run == false → not verbose
TEST(CleanerIsVerboseTest_162, NormalAndNoDryRun_IsNotVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NORMAL;
  config.dry_run = false;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// NORMAL + dry_run == true → verbose (dry-run mode with non-quiet verbosity)
TEST(CleanerIsVerboseTest_162, NormalAndDryRun_IsVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NORMAL;
  config.dry_run = true;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_TRUE(cleaner.IsVerbose());
}

// VERBOSE + dry_run == false → verbose
TEST(CleanerIsVerboseTest_162, VerboseAndNoDryRun_IsVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::VERBOSE;
  config.dry_run = false;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_TRUE(cleaner.IsVerbose());
}

// NO_STATUS_UPDATE + dry_run combinations:
//  - without dry_run: not verbose
//  - with dry_run: verbose (non-quiet + dry-run)
TEST(CleanerIsVerboseTest_162, NoStatusUpdateAndNoDryRun_IsNotVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NO_STATUS_UPDATE;
  config.dry_run = false;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_FALSE(cleaner.IsVerbose());
}

TEST(CleanerIsVerboseTest_162, NoStatusUpdateAndDryRun_IsVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NO_STATUS_UPDATE;
  config.dry_run = true;

  Cleaner cleaner = MakeCleaner(config);
  EXPECT_TRUE(cleaner.IsVerbose());
}

}  // namespace
