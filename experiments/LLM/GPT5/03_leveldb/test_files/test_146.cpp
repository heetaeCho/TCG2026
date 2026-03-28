// File: save_value_test_146.cc

#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"
#include "leveldb/comparator.h"

// Forward decls from db/dbformat.h we need (no logic here).
namespace leveldb {
  typedef uint64_t SequenceNumber;
  enum ValueType { kTypeDeletion = 0, kTypeValue = 1 };

  struct ParsedInternalKey {
    Slice user_key;
    SequenceNumber sequence;
    ValueType type;
  };

  // SaveValue under test
  void SaveValue(void* arg, const Slice& ikey, const Slice& v);

  // Saver and SaverState as used by SaveValue.
  // NOTE: We do not define logic; we just rely on fields used by SaveValue.
  // The real Saver in the codebase should match these members.
  struct Saver {
    /* enum SaverState field */ int state;   // we only compare integer values (0..3) per prompt
    const Comparator* ucmp;
    std::string* value;
    Slice user_key;  // used by SaveValue to match parsed.user_key
  };
}

// ---- Test-only seam for ParseInternalKey (external collaborator) ----
// We DO NOT re-implement its logic; we only supply a stubbed return to
// drive SaveValue's observable behavior.
namespace leveldb {
  // Forward declaration to match production signature.
  bool ParseInternalKey(const Slice& ikey, ParsedInternalKey* out);
}

// Controllable stub state for the tests (file-local).
namespace {
  struct ParseStubState {
    bool ok = true;
    leveldb::ParsedInternalKey parsed{
        leveldb::Slice(), 0 /*seq*/, leveldb::kTypeValue};
  } g_parse_stub;

  // Provide the symbol used by SaveValue.
  bool leveldb::ParseInternalKey(const Slice& ikey, ParsedInternalKey* out) {
    if (!g_parse_stub.ok) return false;
    *out = g_parse_stub.parsed;
    return true;
  }
}

// --------- A minimal comparator to control equality semantics ----------
class EqComparator final : public leveldb::Comparator {
public:
  // Return 0 when byte-wise equal, nonzero otherwise (simple & deterministic).
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    const int c = a.compare(b);
    return (c == 0) ? 0 : (c < 0 ? -1 : 1);
  }
  const char* Name() const override { return "test.EqComparator"; }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
  ~EqComparator() override = default;
};

// ----------------------- Test Fixture -----------------------
class SaveValueTest_146 : public ::testing::Test {
protected:
  EqComparator cmp_;
  std::string out_value_;
  leveldb::Saver saver_;

  void SetUp() override {
    out_value_.assign("INIT");          // so we can detect changes
    saver_.state = 0;                   // 0 == kNotFound (per prompt enum order)
    saver_.ucmp = &cmp_;
    saver_.value = &out_value_;
    saver_.user_key = leveldb::Slice(); // default empty; tests set as needed

    // Reset parse stub defaults
    g_parse_stub.ok = true;
    g_parse_stub.parsed.user_key = leveldb::Slice();
    g_parse_stub.parsed.sequence = 0;
    g_parse_stub.parsed.type = leveldb::kTypeValue;
  }
};

// --------------------------- Tests ---------------------------

// Parse failure -> state becomes kCorrupt (3), value unchanged.
TEST_F(SaveValueTest_146, ParseFailureSetsCorrupt_146) {
  g_parse_stub.ok = false;

  leveldb::Slice ikey("irrelevant");
  leveldb::Slice v("ignored");

  leveldb::SaveValue(&saver_, ikey, v);

  EXPECT_EQ(3, saver_.state) << "Expected kCorrupt == 3";
  EXPECT_EQ("INIT", out_value_) << "Value must not change on parse failure";
}

// Matching user_key and type==kTypeValue -> state kFound (1) and value assigned.
TEST_F(SaveValueTest_146, FoundAssignsValueWhenTypeValue_146) {
  saver_.user_key = leveldb::Slice("foo");          // what we are looking for
  g_parse_stub.parsed.user_key = leveldb::Slice("foo"); // matches
  g_parse_stub.parsed.type = leveldb::kTypeValue;

  leveldb::Slice ikey("any");
  leveldb::Slice v("bar");

  leveldb::SaveValue(&saver_, ikey, v);

  EXPECT_EQ(1, saver_.state) << "Expected kFound == 1";
  EXPECT_EQ("bar", out_value_);
}

// Matching user_key and type==kTypeDeletion -> state kDeleted (2), value unchanged.
TEST_F(SaveValueTest_146, MatchingKeyWithDeletionMarksDeleted_NoValueWrite_146) {
  saver_.user_key = leveldb::Slice("target");
  g_parse_stub.parsed.user_key = leveldb::Slice("target"); // matches
  g_parse_stub.parsed.type = leveldb::kTypeDeletion;

  leveldb::Slice ikey("any");
  leveldb::Slice v("should_not_assign");

  leveldb::SaveValue(&saver_, ikey, v);

  EXPECT_EQ(2, saver_.state) << "Expected kDeleted == 2";
  EXPECT_EQ("INIT", out_value_) << "Value must not change when deleted";
}

// Non-matching user_key -> state remains unchanged (kNotFound==0), value unchanged.
TEST_F(SaveValueTest_146, NonMatchingKey_NoStateOrValueChange_146) {
  saver_.user_key = leveldb::Slice("wanted");
  g_parse_stub.parsed.user_key = leveldb::Slice("other"); // does not match
  g_parse_stub.parsed.type = leveldb::kTypeValue;

  leveldb::Slice ikey("any");
  leveldb::Slice v("newvalue");

  leveldb::SaveValue(&saver_, ikey, v);

  EXPECT_EQ(0, saver_.state) << "Expected to remain kNotFound == 0";
  EXPECT_EQ("INIT", out_value_) << "Value must remain unchanged when key mismatches";
}

// Matching key, value slice empty -> state kFound (1) and assigned empty string.
TEST_F(SaveValueTest_146, FoundAssignsEmptyWhenValueSliceEmpty_146) {
  saver_.user_key = leveldb::Slice("k");
  g_parse_stub.parsed.user_key = leveldb::Slice("k");
  g_parse_stub.parsed.type = leveldb::kTypeValue;

  const char* empty_data = "";
  leveldb::Slice ikey("any");
  leveldb::Slice v(empty_data, 0);  // explicitly empty

  leveldb::SaveValue(&saver_, ikey, v);

  EXPECT_EQ(1, saver_.state);
  EXPECT_TRUE(out_value_.empty());
}
