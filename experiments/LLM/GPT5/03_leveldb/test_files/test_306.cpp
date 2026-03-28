// db_impl_get_test_306.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <atomic>

// --- Expose private members for wiring ONLY (no assertions on private state) ---
#define private public
#include "db/db_impl.h"
#undef private

// ===== Minimal stubs & link-time seams for collaborators in namespace leveldb =====
namespace leveldb {

// ----- Minimal Slice -----
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
  std::string ToString() const { return std::string(data_, size_); }
 private:
  const char* data_;
  size_t size_;
};

// ----- Minimal Status -----
class Status {
 public:
  Status() : ok_(true) {}
  static Status OK() { return Status(); }
  static Status NotFound(const Slice& /*msg*/, const Slice& /*msg2*/ = Slice()) {
    Status s; s.ok_ = false; s.tag_ = "NotFound"; return s;
  }
  bool ok() const { return ok_; }
  std::string ToString() const { return ok_ ? "OK" : tag_; }
 private:
  bool ok_{true};
  std::string tag_{"Error"};
};

// ----- Minimal Snapshot & SnapshotImpl -----
class Snapshot { public: virtual ~Snapshot() = default; };
typedef uint64_t SequenceNumber;

class SnapshotImpl : public Snapshot {
 public:
  explicit SnapshotImpl(SequenceNumber s) : seq_(s) {}
  SequenceNumber sequence_number() const { return seq_; }
 private:
  SequenceNumber seq_;
};

// ----- ReadOptions -----
struct ReadOptions {
  bool verify_checksums = false;
  bool fill_cache = true;
  const Snapshot* snapshot = nullptr;
};

// ----- LookupKey (only ctor signature needed) -----
class LookupKey {
 public:
  LookupKey(const Slice& /*user_key*/, SequenceNumber /*seq*/) {}
  Slice user_key() const { return Slice(); }
};

// Forward decls
class Version;
class VersionSet;

// ====== Global knobs to steer fakes from tests ======
static std::string g_mem_value = "mem";
static std::string g_imm_value = "imm";
static std::string g_ver_value = "version";

static bool g_mem_get_hit = false;
static bool g_imm_get_hit = false;
static bool g_mem_should_hit = false;  // if true, mem->Get returns true and sets value
static bool g_imm_should_hit = false;  // if true, imm->Get returns true and sets value

static int g_version_get_calls = 0;
static int g_versionset_lastseq_calls = 0;
static uint64_t g_versionset_lastseq_value = 777;

static bool g_version_updatestats_returns = false;
static int g_maybe_schedule_compaction_calls = 0;

// ----- Fake MemTable (providing real symbol definitions used by DBImpl::Get) -----
class MemTable {
 public:
  void Ref() {}
  void Unref() {}
  bool Get(const LookupKey& /*key*/, std::string* value, Status* s) {
    // We route based on which pointer we are (mem vs imm). The fixture will set
    // flags before calling DBImpl::Get.
    if (mem_identity_ == this) {
      g_mem_get_hit = true;
      if (g_mem_should_hit) { *value = g_mem_value; *s = Status::OK(); return true; }
    } else if (imm_identity_ == this) {
      g_imm_get_hit = true;
      if (g_imm_should_hit) { *value = g_imm_value; *s = Status::OK(); return true; }
    }
    return false;
  }
  // helpers to mark the identity of mem vs imm
  static void set_mem_identity(MemTable* p) { mem_identity_ = p; }
  static void set_imm_identity(MemTable* p) { imm_identity_ = p; }
 private:
  static MemTable* mem_identity_;
  static MemTable* imm_identity_;
};
MemTable* MemTable::mem_identity_ = nullptr;
MemTable* MemTable::imm_identity_ = nullptr;

// ----- Minimal Version::Get + UpdateStats + Ref/Unref tracking -----
class Version {
 public:
  struct GetStats { void* seek_file = nullptr; int seek_file_level = -1; };
  void Ref() {}
  void Unref() {}
  Status Get(const ReadOptions& /*opts*/, const LookupKey& /*k*/,
             std::string* value, GetStats* /*stats*/) {
    ++g_version_get_calls;
    *value = g_ver_value;
    return Status::OK();
  }
  bool UpdateStats(const GetStats& /*stats*/) { return g_version_updatestats_returns; }
};

// ----- Minimal VersionSet::current/LastSequence -----
class VersionSet {
 public:
  explicit VersionSet(const std::string& /*dbname*/, const void* /*opts*/,
                      void* /*table_cache*/, const void* /*icmp*/) {}
  Version* current() const { return current_; }
  uint64_t LastSequence() const { ++g_versionset_lastseq_calls; return g_versionset_lastseq_value; }
  void set_current(Version* v) { current_ = v; }
 private:
  Version* current_ = nullptr;
};

// ----- Minimal port::Mutex + MutexLock (no-op) -----
namespace port {
class Mutex {
 public:
  void Lock() {}
  void Unlock() {}
  void AssertHeld() {}
};
} // namespace port

// ----- Minimal MutexLock helper used by DBImpl::Get -----
class MutexLock {
 public:
  explicit MutexLock(port::Mutex* mu) : mu_(mu) { mu_->Lock(); }
  ~MutexLock() { mu_->Unlock(); }
 private:
  port::Mutex* mu_;
};

// ----- Link-time seam for DBImpl::MaybeScheduleCompaction() -----
void DBImpl::MaybeScheduleCompaction() {
  ++g_maybe_schedule_compaction_calls;
}

} // namespace leveldb

// ======== Test Fixture ========
using namespace leveldb;

class DBImplGetTest_306 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Build a DBImpl with minimally valid internals we can point at our fakes.
    // We won’t open files etc.; we only use Get’s flow and our stubs.
    Options opts; // Options is referenced in DBImpl ctor; provide a minimal stub object.
    // Provide the bare fields needed by the DBImpl constructor signature.
    // We rely on the real header; the ctor will allocate its own VersionSet,
    // but we will overwrite pointers in the fixture setup.
    db = new DBImpl(opts, "testdb");
    // Wire fake mem and imm
    db->mem_ = &mem;
    mem.Ref(); // mimic ownership expectations
    MemTable::set_mem_identity(&mem);

    db->imm_ = &imm;
    MemTable::set_imm_identity(&imm);

    // Wire fake versions and current version
    fake_versions.set_current(&ver);
    db->versions_ = &fake_versions;

    // Reset knobs/counters
    g_mem_get_hit = g_imm_get_hit = false;
    g_mem_should_hit = g_imm_should_hit = false;
    g_version_get_calls = 0;
    g_versionset_lastseq_calls = 0;
    g_version_updatestats_returns = false;
    g_maybe_schedule_compaction_calls = 0;
  }

  void TearDown() override {
    // Avoid destructor trying to do real work; keep it minimal in stubs world.
    // Release fake refs set in SetUp (no-ops in our stubs).
    delete db;
  }

  // Provide a minimal Options type to satisfy DBImpl constructor signature.
  struct Options {
    void* env = nullptr;
    const void* comparator = nullptr;
    const void* filter_policy = nullptr;
    void* info_log = nullptr;
    void* block_cache = nullptr;
  };

  DBImpl* db = nullptr;
  MemTable mem;
  MemTable imm;
  Version ver;
  VersionSet fake_versions = VersionSet("testdb", nullptr, nullptr, nullptr);
};

// ======== Tests ========

// 1) Returns value from memtable when present; does not consult imm/current
TEST_F(DBImplGetTest_306, ReturnsFromMemTable_WhenHit_306) {
  g_mem_should_hit = true;   // mem will satisfy
  g_imm_should_hit = false;  // imm won't be consulted

  ReadOptions ro;  // no snapshot => LastSequence() should be used
  std::string out;
  Status s = db->Get(ro, Slice("key"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_mem_value);
  EXPECT_TRUE(g_mem_get_hit);
  EXPECT_FALSE(g_imm_get_hit);
  EXPECT_EQ(g_version_get_calls, 0);    // did not go to Version
  EXPECT_EQ(g_versionset_lastseq_calls, 1); // picked seq from VersionSet
  EXPECT_EQ(g_maybe_schedule_compaction_calls, 0); // no stats path
}

// 2) Falls back to immutable memtable when mem misses; does not consult Version
TEST_F(DBImplGetTest_306, ReturnsFromImmTable_WhenMemMiss_306) {
  g_mem_should_hit = false;  // mem miss
  g_imm_should_hit = true;   // imm hit

  ReadOptions ro;  // no snapshot => LastSequence() should be used
  std::string out;
  Status s = db->Get(ro, Slice("k"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_imm_value);
  EXPECT_TRUE(g_mem_get_hit);
  EXPECT_TRUE(g_imm_get_hit);
  EXPECT_EQ(g_version_get_calls, 0);          // no Version access
  EXPECT_EQ(g_versionset_lastseq_calls, 1);   // still constructs LookupKey
  EXPECT_EQ(g_maybe_schedule_compaction_calls, 0);
}

// 3) Falls back to Version when both mem and imm miss; no compaction scheduled if UpdateStats=false
TEST_F(DBImplGetTest_306, UsesVersionOnMiss_NoCompactionWhenNoStatUpdate_306) {
  g_mem_should_hit = false;
  g_imm_should_hit = false;
  g_version_updatestats_returns = false;  // UpdateStats() -> false

  ReadOptions ro;
  std::string out;
  Status s = db->Get(ro, Slice("any"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_ver_value);
  EXPECT_EQ(g_version_get_calls, 1);
  EXPECT_EQ(g_versionset_lastseq_calls, 1);
  EXPECT_EQ(g_maybe_schedule_compaction_calls, 0); // since UpdateStats==false
}

// 4) Schedules compaction when Version::Get path taken AND UpdateStats returns true
TEST_F(DBImplGetTest_306, UsesVersionOnMiss_SchedulesCompactionOnStatUpdate_306) {
  g_mem_should_hit = false;
  g_imm_should_hit = false;
  g_version_updatestats_returns = true;  // UpdateStats() -> true

  ReadOptions ro;
  std::string out;
  Status s = db->Get(ro, Slice("z"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_ver_value);
  EXPECT_EQ(g_version_get_calls, 1);
  EXPECT_EQ(g_versionset_lastseq_calls, 1);
  EXPECT_EQ(g_maybe_schedule_compaction_calls, 1); // compaction scheduled
}

// 5) Uses snapshot’s sequence (observable via: LastSequence() NOT called when snapshot is provided)
TEST_F(DBImplGetTest_306, UsesSnapshotSequenceWhenProvided_306) {
  g_mem_should_hit = false;
  g_imm_should_hit = false;
  g_version_updatestats_returns = false;

  SnapshotImpl snap(/*sequence=*/12345);
  ReadOptions ro;
  ro.snapshot = &snap;

  std::string out;
  Status s = db->Get(ro, Slice("a"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_ver_value);
  EXPECT_EQ(g_version_get_calls, 1);
  EXPECT_EQ(g_versionset_lastseq_calls, 0)   // critical: did NOT read LastSequence()
      << "DBImpl::Get should not consult VersionSet::LastSequence() when a snapshot is provided.";
  EXPECT_EQ(g_maybe_schedule_compaction_calls, 0);
}

// 6) When no snapshot is provided, LastSequence() is consulted exactly once on the miss-to-Version path
TEST_F(DBImplGetTest_306, UsesLastSequenceWhenNoSnapshot_306) {
  g_mem_should_hit = false;
  g_imm_should_hit = false;

  ReadOptions ro;  // no snapshot
  std::string out;
  Status s = db->Get(ro, Slice("b"), &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, g_ver_value);
  EXPECT_EQ(g_version_get_calls, 1);
  EXPECT_EQ(g_versionset_lastseq_calls, 1);  // used LastSequence
}

