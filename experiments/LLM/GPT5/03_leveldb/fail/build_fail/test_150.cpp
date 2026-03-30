// File: version_record_read_sample_test_150.cc

#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <cstring>

namespace leveldb {

// ==== Minimal public types from headers (only what's needed for tests) ====

class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* s) : data_(s), size_(std::strlen(s)) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

using SequenceNumber = uint64_t;
enum ValueType { kTypeValue = 1 }; // exact value not important for tests

struct ParsedInternalKey {
  Slice user_key;
  SequenceNumber sequence{0};
  ValueType type{kTypeValue};
};

struct FileMetaData {
  int refs{0};
  int allowed_seeks{1 << 30};
  uint64_t number{0};
  uint64_t file_size{0};
  // InternalKey fields omitted – not needed by tests
};

struct Version {
  struct GetStats {
    FileMetaData* seek_file{nullptr};
    int seek_file_level{-1};
  };

  // The method under test (implemented in production)
  bool RecordReadSample(Slice internal_key);

  // These exist in production; we provide out-of-line test doubles below.
  void ForEachOverlapping(Slice user_key, Slice internal_key,
                          void* arg,
                          bool (*func)(void*, int, FileMetaData*));
  bool UpdateStats(const GetStats& stats);
};

// External collaborator parsed by RecordReadSample; test double below.
bool ParseInternalKey(const Slice& internal_key, ParsedInternalKey* result);

}  // namespace leveldb

// ===================== Test doubles and control knobs ======================
namespace {

// Controls for ParseInternalKey
static bool g_parse_ok = true;
static int  g_parse_calls = 0;

bool leveldb::ParseInternalKey(const leveldb::Slice& internal_key,
                               leveldb::ParsedInternalKey* out) {
  g_parse_calls++;
  if (!g_parse_ok) return false;
  // Provide any user_key; its content is irrelevant to the tests.
  *out = leveldb::ParsedInternalKey{ leveldb::Slice("user"), 0, leveldb::kTypeValue };
  return true;
}

// Controls & capture for ForEachOverlapping
struct CallbackPlan {
  int level;
  leveldb::FileMetaData* file;
};

static std::vector<CallbackPlan> g_overlap_plan; // planned callback invocations
static int g_overlap_func_calls = 0;             // how many times func actually called

void leveldb::Version::ForEachOverlapping(leveldb::Slice /*user_key*/,
                                          leveldb::Slice /*internal_key*/,
                                          void* arg,
                                          bool (*func)(void*, int, leveldb::FileMetaData*)) {
  g_overlap_func_calls = 0;
  // Simulate the production behavior: keep invoking until the callback returns false.
  for (const auto& step : g_overlap_plan) {
    g_overlap_func_calls++;
    if (!func(arg, step.level, step.file)) {
      break; // stop when callback says so
    }
  }
}

// Controls & capture for UpdateStats
static bool g_update_return = false;
static bool g_update_called = false;
static leveldb::Version::GetStats g_update_last_stats;

bool leveldb::Version::UpdateStats(const leveldb::Version::GetStats& stats) {
  g_update_called = true;
  g_update_last_stats = stats;
  return g_update_return;
}

// Helper to create an uninitialized Version storage without needing its ctor.
// RecordReadSample does not depend on Version instance state in these tests.
leveldb::Version* MakeBareVersion() {
  void* mem = ::operator new(sizeof(leveldb::Version));
  // Intentionally do not call constructor; not needed for these isolated calls.
  return reinterpret_cast<leveldb::Version*>(mem);
}

struct RecordReadSampleTest_150 : ::testing::Test {
  leveldb::FileMetaData f1, f2, f3; // stable addresses for plans
  leveldb::Version* ver{nullptr};

  void SetUp() override {
    ver = MakeBareVersion();

    g_parse_ok = true;
    g_parse_calls = 0;

    g_overlap_plan.clear();
    g_overlap_func_calls = 0;

    g_update_return = false;
    g_update_called = false;
    g_update_last_stats = leveldb::Version::GetStats{};
  }

  void TearDown() override {
    ::operator delete(ver);
  }
};

} // namespace

// =============================== TESTS =====================================

// 1) Parse failure -> must return false, no overlap scan, no UpdateStats.
TEST_F(RecordReadSampleTest_150, ParseFailureReturnsFalse_150) {
  g_parse_ok = false;

  const bool ok = ver->RecordReadSample(leveldb::Slice("bad_internal"));

  EXPECT_FALSE(ok);
  EXPECT_EQ(1, g_parse_calls);
  EXPECT_EQ(0, g_overlap_func_calls) << "No overlapping scan when parse fails";
  EXPECT_FALSE(g_update_called) << "UpdateStats must not be called on parse failure";
}

// 2a) Parsed ok, but zero overlaps -> returns false, no UpdateStats.
TEST_F(RecordReadSampleTest_150, ZeroMatchesReturnsFalse_NoUpdate_150) {
  g_parse_ok = true;
  g_overlap_plan = {}; // no callback invocations

  const bool ok = ver->RecordReadSample(leveldb::Slice("ik"));

  EXPECT_FALSE(ok);
  EXPECT_EQ(1, g_parse_calls);
  EXPECT_EQ(0, g_overlap_func_calls);
  EXPECT_FALSE(g_update_called);
}

// 2b) Parsed ok, exactly one overlap -> returns false, no UpdateStats.
TEST_F(RecordReadSampleTest_150, OneMatchReturnsFalse_NoUpdate_150) {
  g_parse_ok = true;
  g_overlap_plan = {
      {4, &f1}, // one match only
  };

  const bool ok = ver->RecordReadSample(leveldb::Slice("ik"));

  EXPECT_FALSE(ok);
  EXPECT_EQ(1, g_parse_calls);
  EXPECT_EQ(1, g_overlap_func_calls);
  EXPECT_FALSE(g_update_called);
}

// 3) Two or more overlaps -> UpdateStats called with the *first* match info.
//    The return value of RecordReadSample must propagate UpdateStats's result.
TEST_F(RecordReadSampleTest_150, TwoMatches_PropagatesUpdateStatsResult_True_150) {
  g_parse_ok = true;
  g_update_return = true;  // make UpdateStats succeed

  // Plan includes 3 potential matches; callback should stop after the second.
  g_overlap_plan = {
      {4, &f1}, // first match — should be recorded in stats
      {2, &f2}, // second match — triggers UpdateStats
      {6, &f3}, // would-be third, but should not be invoked
  };

  const bool ok = ver->RecordReadSample(leveldb::Slice("ik"));

  EXPECT_TRUE(ok);
  EXPECT_EQ(1, g_parse_calls);
  EXPECT_EQ(2, g_overlap_func_calls) << "Callback should stop after the second match";
  ASSERT_TRUE(g_update_called);
  EXPECT_EQ(&f1, g_update_last_stats.seek_file) << "First match file must be forwarded";
  EXPECT_EQ(4,   g_update_last_stats.seek_file_level) << "First match level must be forwarded";
}

// 4) Same as (3) but UpdateStats returns false -> propagate false.
TEST_F(RecordReadSampleTest_150, TwoMatches_PropagatesUpdateStatsResult_False_150) {
  g_parse_ok = true;
  g_update_return = false; // make UpdateStats fail

  g_overlap_plan = {
      {1, &f2}, // first
      {3, &f3}, // second
  };

  const bool ok = ver->RecordReadSample(leveldb::Slice("ik"));

  EXPECT_FALSE(ok);
  EXPECT_EQ(2, g_overlap_func_calls);
  ASSERT_TRUE(g_update_called);
  EXPECT_EQ(&f2, g_update_last_stats.seek_file);
  EXPECT_EQ(1,   g_update_last_stats.seek_file_level);
}
