#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "table/merger.h"
#include "util/testutil.h"
#include "db/table_cache.h"
#include "db/log_writer.h"

#include <string>
#include <vector>

namespace leveldb {

// Helper to build an internal key string
static std::string MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq, ValueType type) {
  std::string result;
  result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

static void PutFixed64(std::string* dst, uint64_t value) {
  char buf[sizeof(value)];
  std::memcpy(buf, &value, sizeof(value));
  dst->append(buf, sizeof(buf));
}

static uint64_t PackSequenceAndType(uint64_t seq, ValueType t) {
  return (seq << 8) | static_cast<uint64_t>(t);
}

class VersionRecordReadSampleTest_150 : public ::testing::Test {
 protected:
  VersionRecordReadSampleTest_150()
      : env_(Env::Default()),
        db_name_(testing::TempDir() + "/version_test_150"),
        table_cache_(nullptr),
        vset_(nullptr) {}

  void SetUp() override {
    env_->CreateDir(db_name_);

    Options options;
    options.env = env_;
    options.comparator = BytewiseComparator();

    const int table_cache_size = 100;
    table_cache_ = new TableCache(db_name_, options, table_cache_size);

    vset_ = new VersionSet(db_name_, &options_, table_cache_, &icmp_);

    options_.comparator = BytewiseComparator();
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
  }

  Env* env_;
  std::string db_name_;
  Options options_;
  InternalKeyComparator icmp_{BytewiseComparator()};
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that an invalid (empty) internal key returns false
TEST_F(VersionRecordReadSampleTest_150, InvalidKeyReturnsFalse_150) {
  // Get the current version
  Version* v = vset_->current();
  v->Ref();

  // Empty key cannot be parsed as internal key
  Slice empty_key("");
  bool result = v->RecordReadSample(empty_key);
  EXPECT_FALSE(result);

  v->Unref();
}

// Test that a key too short to be a valid internal key returns false
TEST_F(VersionRecordReadSampleTest_150, TooShortKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();

  // Internal key needs at least 8 bytes for the trailer
  Slice short_key("short");  // only 5 bytes, not enough
  bool result = v->RecordReadSample(short_key);
  EXPECT_FALSE(result);

  v->Unref();
}

// Test that a valid internal key with no overlapping files returns false
TEST_F(VersionRecordReadSampleTest_150, NoOverlappingFilesReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();

  // Build a valid internal key
  std::string key;
  key = "testkey";
  PutFixed64(&key, PackSequenceAndType(100, kTypeValue));

  Slice internal_key(key);
  bool result = v->RecordReadSample(internal_key);
  EXPECT_FALSE(result);

  v->Unref();
}

// Test that RecordReadSample with a single byte returns false (invalid parse)
TEST_F(VersionRecordReadSampleTest_150, SingleByteKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();

  Slice one_byte("x");
  bool result = v->RecordReadSample(one_byte);
  EXPECT_FALSE(result);

  v->Unref();
}

// Test with exactly 8 bytes (minimum valid internal key with empty user key)
TEST_F(VersionRecordReadSampleTest_150, MinimalValidKeyNoFiles_150) {
  Version* v = vset_->current();
  v->Ref();

  // Empty user key + 8 byte trailer
  std::string key;
  PutFixed64(&key, PackSequenceAndType(1, kTypeValue));

  Slice internal_key(key);
  bool result = v->RecordReadSample(internal_key);
  // No files exist, so fewer than 2 matches => false
  EXPECT_FALSE(result);

  v->Unref();
}

// Test with 7 bytes - just under the minimum for a valid internal key
TEST_F(VersionRecordReadSampleTest_150, SevenBytesKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();

  std::string key(7, 'a');
  Slice internal_key(key);
  bool result = v->RecordReadSample(internal_key);
  EXPECT_FALSE(result);

  v->Unref();
}

// Test NumFiles on empty version
TEST_F(VersionRecordReadSampleTest_150, EmptyVersionNumFiles_150) {
  Version* v = vset_->current();
  v->Ref();

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }

  v->Unref();
}

// Test that a valid internal key with bad type byte still parses
// (ParseInternalKey checks type validity)
TEST_F(VersionRecordReadSampleTest_150, InvalidTypeInKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();

  std::string key = "userkey";
  // Use an invalid type value (e.g., 0xFF which is not kTypeValue or kTypeDeletion)
  uint64_t bad_trailer = (100ULL << 8) | 0xFF;
  PutFixed64(&key, bad_trailer);

  Slice internal_key(key);
  bool result = v->RecordReadSample(internal_key);
  // Should fail to parse with invalid type
  EXPECT_FALSE(result);

  v->Unref();
}

}  // namespace leveldb
#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "leveldb/slice.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "util/coding.h"

#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

class RecordReadSampleTest_150 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    db_name_ = testing::TempDir() + "/recordreadsample_test_150";
    env_->CreateDir(db_name_);
    
    options_.env = env_;
    options_.comparator = BytewiseComparator();
    
    table_cache_ = new TableCache(db_name_, options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    vset_ = new VersionSet(db_name_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
  }

  std::string BuildInternalKey(const std::string& user_key, uint64_t seq,
                                ValueType type) {
    std::string result = user_key;
    uint64_t trailer = (seq << 8) | static_cast<uint64_t>(type);
    char buf[8];
    EncodeFixed64(buf, trailer);
    result.append(buf, 8);
    return result;
  }

  Env* env_;
  std::string db_name_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Empty/invalid key should fail to parse and return false
TEST_F(RecordReadSampleTest_150, EmptyKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  EXPECT_FALSE(v->RecordReadSample(Slice("")));
  v->Unref();
}

// Key shorter than 8 bytes cannot be a valid internal key
TEST_F(RecordReadSampleTest_150, ShortKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  EXPECT_FALSE(v->RecordReadSample(Slice("short")));
  v->Unref();
}

// Key with exactly 7 bytes is still too short
TEST_F(RecordReadSampleTest_150, SevenByteKeyReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string key(7, 'x');
  EXPECT_FALSE(v->RecordReadSample(Slice(key)));
  v->Unref();
}

// Valid internal key but no files in version - fewer than 2 matches
TEST_F(RecordReadSampleTest_150, ValidKeyNoFilesReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string ikey = BuildInternalKey("testkey", 100, kTypeValue);
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey)));
  v->Unref();
}

// Valid internal key with empty user key, no files
TEST_F(RecordReadSampleTest_150, EmptyUserKeyNoFilesReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string ikey = BuildInternalKey("", 1, kTypeValue);
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey)));
  v->Unref();
}

// Key with invalid value type should fail ParseInternalKey
TEST_F(RecordReadSampleTest_150, InvalidValueTypeReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string key = "userkey";
  // Pack an invalid type (e.g., type = 3 which is beyond kTypeValue)
  uint64_t trailer = (100ULL << 8) | 0x03;
  char buf[8];
  EncodeFixed64(buf, trailer);
  key.append(buf, 8);
  EXPECT_FALSE(v->RecordReadSample(Slice(key)));
  v->Unref();
}

// Deletion type key with no overlapping files
TEST_F(RecordReadSampleTest_150, DeletionKeyNoFilesReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string ikey = BuildInternalKey("deleted", 50, kTypeDeletion);
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey)));
  v->Unref();
}

// Verify empty version has zero files at all levels
TEST_F(RecordReadSampleTest_150, EmptyVersionHasNoFiles_150) {
  Version* v = vset_->current();
  v->Ref();
  for (int i = 0; i < config::kNumLevels; i++) {
    EXPECT_EQ(0, v->NumFiles(i));
  }
  v->Unref();
}

// Large sequence number key with no files
TEST_F(RecordReadSampleTest_150, LargeSequenceKeyNoFilesReturnsFalse_150) {
  Version* v = vset_->current();
  v->Ref();
  std::string ikey = BuildInternalKey("bigseq", kMaxSequenceNumber, kTypeValue);
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey)));
  v->Unref();
}

// Multiple calls to RecordReadSample on empty version all return false
TEST_F(RecordReadSampleTest_150, MultipleCalls_150) {
  Version* v = vset_->current();
  v->Ref();
  
  std::string ikey1 = BuildInternalKey("key1", 10, kTypeValue);
  std::string ikey2 = BuildInternalKey("key2", 20, kTypeValue);
  std::string ikey3 = BuildInternalKey("key3", 30, kTypeDeletion);
  
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey1)));
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey2)));
  EXPECT_FALSE(v->RecordReadSample(Slice(ikey3)));
  
  v->Unref();
}

}  // namespace leveldb
