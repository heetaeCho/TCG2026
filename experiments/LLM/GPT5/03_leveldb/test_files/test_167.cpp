// File: version_set_levelsummary_test.cc

#include <gtest/gtest.h>
#include <array>
#include <regex>
#include <string>
#include <vector>
#include <cstring>

// Headers from the provided partial interface
#include "db/version_set.h"     // Declares leveldb::VersionSet and LevelSummaryStorage
#include "db/dbformat.h"        // Declares leveldb::config::kNumLevels

using leveldb::VersionSet;
using leveldb::Version;
using leveldb::LevelSummaryStorage;

namespace {

// Helper: parse the "files[ a b c d e f g ]" line and extract exactly 7 ints.
static std::vector<int> ParseSevenCounts(const std::string& s) {
  // Be tolerant about spaces, but strict about having exactly 7 integers.
  std::regex re(R"(files\[\s*(-?\d+)\s+(-?\d+)\s+(-?\d+)\s+(-?\d+)\s+(-?\d+)\s+(-?\d+)\s+(-?\d+)\s*\])");
  std::smatch m;
  std::vector<int> out;
  if (std::regex_search(s, m, re)) {
    for (int i = 1; i <= 7; ++i) out.push_back(std::stoi(m[i].str()));
  }
  return out;
}

// Minimal scaffolding to build a VersionSet without depending on internal details.
// NOTE: We never mutate private fields; we only create an instance to call public methods.
// In typical LevelDB setups, you can construct VersionSet with real or dummy options.
// If your build already provides a convenient factory, use that instead.
struct VSFixture {
  // You may need to adapt these placeholders to your environment if your project
  // wires real Env/TableCache/Comparator/Options. The tests never use them directly.
  // They exist purely so we can instantiate VersionSet and call LevelSummary.
  struct DummyEnv {};
  struct DummyTableCache {};
  struct DummyComparator {};
  struct DummyOptions {
    // Only the pointer presence is relevant for construction in many harnesses.
    // If your real constructor needs more, wire accordingly.
    DummyEnv* env = nullptr;
  };

  std::unique_ptr<DummyEnv> env;
  std::unique_ptr<DummyTableCache> table_cache;
  std::unique_ptr<DummyComparator> cmp;
  std::unique_ptr<DummyOptions> options;

  // The VersionSet under test
  std::unique_ptr<VersionSet> vs;

  VSFixture() {
    env = std::make_unique<DummyEnv>();
    table_cache = std::make_unique<DummyTableCache>();
    cmp = std::make_unique<DummyComparator>();
    options = std::make_unique<DummyOptions>();
    options->env = env.get();

    // Construct VersionSet with dummy args that satisfy the signature.
    // Depending on your harness, you might replace Dummy* with your real types.
    vs = std::make_unique<VersionSet>(
        /*dbname=*/"test-db",
        reinterpret_cast<const leveldb::Options*>(options.get()),
        reinterpret_cast<leveldb::TableCache*>(table_cache.get()),
        reinterpret_cast<const leveldb::InternalKeyComparator*>(cmp.get()));
  }
};

}  // namespace

// --- Tests ---

// Verifies the function returns a C-string pointer to the provided scratch buffer,
// the format matches "files[ a b c d e f g ]", and contains exactly 7 integers.
TEST(VersionSet_LevelSummaryTest_167, ReturnsPointerToScratchAndFormatIsCorrect_167) {
  VSFixture f;
  LevelSummaryStorage scratch{};
  const char* p = f.vs->LevelSummary(&scratch);

  // The returned pointer must be the same as the scratch buffer.
  EXPECT_EQ(p, scratch.buffer);

  // String must be null-terminated and non-empty.
  std::string s(p);
  EXPECT_FALSE(s.empty());

  // Buffer should not overflow: ensure length < buffer size and last char is '\0'.
  EXPECT_LT(s.size(), sizeof(scratch.buffer));
  EXPECT_EQ(scratch.buffer[sizeof(scratch.buffer) - 1], '\0');  // typical snprintf behavior leaves trailing bytes untouched, but ensure no UB

  // Format must contain exactly 7 integers inside "files[ ... ]".
  auto counts = ParseSevenCounts(s);
  EXPECT_EQ(counts.size(), 7u) << "LevelSummary should report exactly 7 levels per config::kNumLevels";
}

// Validates that a fresh VersionSet (black-box) reports seven integers, all
// consistent with NumLevelFiles(level) for each level.
TEST(VersionSet_LevelSummaryTest_167, MatchesNumLevelFilesForAllLevels_167) {
  VSFixture f;
  LevelSummaryStorage scratch{};
  const char* p = f.vs->LevelSummary(&scratch);
  std::string s(p);
  auto counts = ParseSevenCounts(s);
  ASSERT_EQ(counts.size(), 7u);

  for (int level = 0; level < leveldb::config::kNumLevels; ++level) {
    // Compare string-reported count with the public accessor.
    int reported = counts[level];
    int via_api = f.vs->NumLevelFiles(level);
    EXPECT_EQ(reported, via_api) << "Mismatch at level " << level;
  }
}

// Calling LevelSummary multiple times with the same scratch should be stable:
// same pointer and same content (since we don't mutate via public API here).
TEST(VersionSet_LevelSummaryTest_167, IdempotentOnRepeatedCalls_167) {
  VSFixture f;
  LevelSummaryStorage scratch{};
  const char* first_ptr = f.vs->LevelSummary(&scratch);
  std::string first_str(first_ptr);

  const char* second_ptr = f.vs->LevelSummary(&scratch);
  std::string second_str(second_ptr);

  EXPECT_EQ(first_ptr, scratch.buffer);
  EXPECT_EQ(second_ptr, scratch.buffer);
  EXPECT_EQ(first_str, second_str);
}

// Sanity-check that the line always starts with "files[" and ends with "]"
// and remains under the storage capacity (guard against accidental overflow).
TEST(VersionSet_LevelSummaryTest_167, OutputBoundsAndPreamble_167) {
  VSFixture f;
  LevelSummaryStorage scratch{};
  const char* p = f.vs->LevelSummary(&scratch);
  std::string s(p);

  ASSERT_GE(s.size(), 8u); // "files[ ]" minimum-ish
  EXPECT_EQ(s.rfind("files[", 0), 0u); // starts with "files["

  // Trailing bracket present
  EXPECT_EQ(s.find(']'), s.size() - 1);

  // Well within buffer capacity
  EXPECT_LT(s.size(), sizeof(scratch.buffer));
}

