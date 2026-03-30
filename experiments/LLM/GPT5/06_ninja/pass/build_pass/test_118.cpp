// File: build_log_entries_test_118.cc

#include "gtest/gtest.h"

#include <cstdio>
#include <string>
#include <vector>

#include "build_log.h"

class BuildLogEntriesTest_118 : public ::testing::Test {
protected:
  std::string log_path_ = "build_log_entries_test_118.log";

  void TearDown() override {
    // Best-effort cleanup of the temp log file.
    std::remove(log_path_.c_str());
  }

  /// Helper to create a .ninja_log-compatible file with the given data lines.
  /// We deliberately use a very large log version so that it is always
  /// >= kOldestSupportedVersion in BuildLog::Load.
  void WriteLogFile(const std::vector<std::string>& lines) {
    FILE* f = std::fopen(log_path_.c_str(), "wb");
    ASSERT_NE(f, nullptr);

    // Header: "# ninja log v<version>\n"
    const char kHeader[] = "# ninja log v100000\n";
    ASSERT_GE(std::fputs(kHeader, f), 0);

    for (const std::string& line : lines) {
      ASSERT_GE(std::fputs(line.c_str(), f), 0);
      if (line.empty() || line.back() != '\n') {
        std::fputc('\n', f);
      }
    }

    std::fclose(f);
  }
};

// 1) Newly constructed BuildLog has no entries.
TEST_F(BuildLogEntriesTest_118, EntriesInitiallyEmpty_118) {
  BuildLog log;

  const auto& entries = log.entries();
  EXPECT_EQ(0u, entries.size());
}

// 2) Loading a missing log file leaves entries() empty.
TEST_F(BuildLogEntriesTest_118, EntriesRemainEmptyWhenLoadingMissingFile_118) {
  const std::string missing_path = "nonexistent_build_log_entries_118.log";
  // Ensure the file does not exist.
  std::remove(missing_path.c_str());

  BuildLog log;
  std::string err;

  // Ignore the return value to be compatible with both bool and enum LoadStatus.
  log.Load(missing_path, &err);

  const auto& entries = log.entries();
  EXPECT_EQ(0u, entries.size());
}

// 3) entries() reflects unique outputs present in the loaded log file.
TEST_F(BuildLogEntriesTest_118, EntriesReflectLoadedUniqueOutputs_118) {
  // Two different outputs -> two entries.
  WriteLogFile({
      "1\t2\t3\tout1\t0",
      "4\t5\t6\tout2\t0",
  });

  BuildLog log;
  std::string err;
  log.Load(log_path_, &err);

  const auto& entries = log.entries();
  EXPECT_EQ(2u, entries.size());

  // Public lookup must see the same entries as entries().
  EXPECT_NE(nullptr, log.LookupByOutput("out1"));
  EXPECT_NE(nullptr, log.LookupByOutput("out2"));
}

// 4) Duplicate outputs in the log should result in a single entry for that path.
TEST_F(BuildLogEntriesTest_118, EntriesDeduplicateOutputsByPath_118) {
  // Same output path appears twice; loader should collapse to one entry.
  WriteLogFile({
      "1\t2\t3\tout\t0",
      "10\t20\t30\tout\t0",
  });

  BuildLog log;
  std::string err;
  log.Load(log_path_, &err);

  const auto& entries = log.entries();
  EXPECT_EQ(1u, entries.size());
}

// 5) entries() returns a const reference to the underlying container, not a copy.
TEST_F(BuildLogEntriesTest_118, EntriesReturnsConstReference_118) {
  BuildLog log;

  const auto& entries1 = log.entries();
  const auto& entries2 = log.entries();

  // Address must be identical if a reference is returned.
  EXPECT_EQ(&entries1, &entries2);
}
