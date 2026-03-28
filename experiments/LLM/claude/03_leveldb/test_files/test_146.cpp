#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "db/dbformat.h"
#include "db/version_set.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <string>
#include <cstring>

namespace leveldb {

// We need access to the internal types and SaveValue function.
// Re-declare the anonymous namespace types to match the implementation.
namespace {

enum SaverState {
  kNotFound = 0,
  kFound = 1,
  kDeleted = 2,
  kCorrupt = 3
};

struct Saver {
  SaverState state;
  const Comparator* ucmp;
  Slice user_key;
  std::string* value;
};

}  // anonymous namespace

// Forward declare SaveValue - it's a static function in version_set.cc
// We need to either include it or test through Version::Get.
// Since SaveValue is static, we can't directly call it from outside the TU.
// However, we can test it indirectly through Version::Get or replicate the
// function for testing based on the provided code.

// Since SaveValue is static and not directly accessible, we replicate it here
// purely for unit testing purposes based on the provided implementation.
static void SaveValue(void* arg, const Slice& ikey, const Slice& v) {
  Saver* s = reinterpret_cast<Saver*>(arg);
  ParsedInternalKey parsed_key;
  if (!ParseInternalKey(ikey, &parsed_key)) {
    s->state = kCorrupt;
  } else {
    if (s->ucmp->Compare(parsed_key.user_key, s->user_key) == 0) {
      s->state = (parsed_key.type == kTypeValue) ? kFound : kDeleted;
      if (s->state == kFound) {
        s->value->assign(v.data(), v.size());
      }
    }
  }
}

// Helper to build an internal key encoding
static std::string MakeInternalKey(const Slice& user_key, SequenceNumber seq,
                                   ValueType type) {
  std::string result(user_key.data(), user_key.size());
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

// Use the bytewise comparator for tests
class SaveValueTest_146 : public ::testing::Test {
 protected:
  void SetUp() override {
    ucmp_ = BytewiseComparator();
    value_.clear();
  }

  const Comparator* ucmp_;
  std::string value_;

  Saver MakeSaver(const Slice& user_key) {
    Saver s;
    s.state = kNotFound;
    s.ucmp = ucmp_;
    s.user_key = user_key;
    s.value = &value_;
    return s;
  }
};

// Test: When a kTypeValue key matches the user_key, state should be kFound
// and value should be assigned.
TEST_F(SaveValueTest_146, FoundMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 100, kTypeValue);
  std::string val = "testvalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "testvalue");
}

// Test: When a kTypeDeletion key matches the user_key, state should be kDeleted
// and value should NOT be modified.
TEST_F(SaveValueTest_146, DeletedMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);
  value_ = "original";

  std::string ikey = MakeInternalKey(target_key, 100, kTypeDeletion);
  std::string val = "somevalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kDeleted);
  EXPECT_EQ(value_, "original");  // value should not be modified for deletion
}

// Test: When user_key does not match, state should remain kNotFound.
TEST_F(SaveValueTest_146, NonMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  std::string different_key = "otherkey";
  std::string ikey = MakeInternalKey(different_key, 100, kTypeValue);
  std::string val = "testvalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kNotFound);
  EXPECT_EQ(value_, "");
}

// Test: When the internal key is corrupt (cannot be parsed), state should be kCorrupt.
TEST_F(SaveValueTest_146, CorruptInternalKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  // An internal key that is too short to be valid (needs at least 8 bytes for
  // sequence+type after user key, so an empty or very short key is invalid)
  std::string corrupt_ikey = "short";

  SaveValue(reinterpret_cast<void*>(&s), Slice(corrupt_ikey), Slice("val"));

  EXPECT_EQ(s.state, kCorrupt);
}

// Test: Empty user key that matches
TEST_F(SaveValueTest_146, EmptyUserKeyMatch_146) {
  std::string target_key = "";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey("", 50, kTypeValue);
  std::string val = "emptyval";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "emptyval");
}

// Test: Empty value with matching key
TEST_F(SaveValueTest_146, EmptyValueFound_146) {
  std::string target_key = "mykey";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 200, kTypeValue);
  std::string val = "";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "");
}

// Test: Key matches but is a deletion - value string should not be overwritten
TEST_F(SaveValueTest_146, DeletionDoesNotOverwriteValue_146) {
  std::string target_key = "delkey";
  value_ = "previousvalue";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 300, kTypeDeletion);

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice("newvalue"));

  EXPECT_EQ(s.state, kDeleted);
  EXPECT_EQ(value_, "previousvalue");
}

// Test: Completely empty internal key should be corrupt
TEST_F(SaveValueTest_146, EmptyInternalKeyIsCorrupt_146) {
  std::string target_key = "key";
  Saver s = MakeSaver(target_key);

  SaveValue(reinterpret_cast<void*>(&s), Slice(""), Slice("val"));

  EXPECT_EQ(s.state, kCorrupt);
}

// Test: Large value is correctly assigned
TEST_F(SaveValueTest_146, LargeValueFound_146) {
  std::string target_key = "bigkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 999, kTypeValue);
  std::string large_val(100000, 'x');

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(large_val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, large_val);
}

// Test: Key with binary data
TEST_F(SaveValueTest_146, BinaryKeyMatch_146) {
  std::string target_key("\x00\x01\x02\x03", 4);
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 42, kTypeValue);
  std::string val = "binaryresult";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "binaryresult");
}

// Test: Different sequence numbers should not affect matching (user key comparison only)
TEST_F(SaveValueTest_146, DifferentSequenceNumbersMatch_146) {
  std::string target_key = "seqkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = MakeInternalKey(target_key, 1, kTypeValue);
  std::string val = "seqval";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "seqval");
}

// Test: Non-matching key with same prefix
TEST_F(SaveValueTest_146, PrefixMatchButDifferentKey_146) {
  std::string target_key = "key";
  Saver s = MakeSaver(target_key);

  std::string different_key = "key2";
  std::string ikey = MakeInternalKey(different_key, 100, kTypeValue);

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice("val"));

  EXPECT_EQ(s.state, kNotFound);
}

}  // namespace leveldb
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <string>
#include <cstring>

// Since SaveValue is static in version_set.cc, we include the source file
// to gain access. This is a common pattern for testing static functions.
#include "db/version_set.cc"

namespace leveldb {
namespace {

class SaveValueTest_146 : public ::testing::Test {
 protected:
  void SetUp() override {
    ucmp_ = BytewiseComparator();
    value_.clear();
  }

  const Comparator* ucmp_;
  std::string value_;

  Saver MakeSaver(const Slice& user_key) {
    Saver s;
    s.state = kNotFound;
    s.ucmp = ucmp_;
    s.user_key = user_key;
    s.value = &value_;
    return s;
  }

  // Encode an internal key from user_key, sequence, and type
  std::string EncodeInternalKey(const Slice& user_key, SequenceNumber seq,
                                ValueType type) {
    std::string encoded;
    AppendInternalKey(&encoded, ParsedInternalKey(user_key, seq, type));
    return encoded;
  }
};

// Test: Matching key with kTypeValue should set state to kFound and assign value
TEST_F(SaveValueTest_146, FoundMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 100, kTypeValue);
  std::string val = "testvalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "testvalue");
}

// Test: Matching key with kTypeDeletion should set state to kDeleted
TEST_F(SaveValueTest_146, DeletedMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);
  value_ = "original";

  std::string ikey = EncodeInternalKey(target_key, 100, kTypeDeletion);
  std::string val = "somevalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kDeleted);
  EXPECT_EQ(value_, "original");  // Value should not be modified for deletion
}

// Test: Non-matching key leaves state as kNotFound
TEST_F(SaveValueTest_146, NonMatchingKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  std::string different_key = "otherkey";
  std::string ikey = EncodeInternalKey(different_key, 100, kTypeValue);
  std::string val = "testvalue";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kNotFound);
  EXPECT_EQ(value_, "");
}

// Test: Corrupt internal key sets state to kCorrupt
TEST_F(SaveValueTest_146, CorruptInternalKey_146) {
  std::string target_key = "testkey";
  Saver s = MakeSaver(target_key);

  // Too short to be a valid internal key
  std::string corrupt_ikey = "short";

  SaveValue(reinterpret_cast<void*>(&s), Slice(corrupt_ikey), Slice("val"));

  EXPECT_EQ(s.state, kCorrupt);
}

// Test: Empty internal key is corrupt
TEST_F(SaveValueTest_146, EmptyInternalKeyIsCorrupt_146) {
  std::string target_key = "key";
  Saver s = MakeSaver(target_key);

  SaveValue(reinterpret_cast<void*>(&s), Slice(""), Slice("val"));

  EXPECT_EQ(s.state, kCorrupt);
}

// Test: Empty user key that matches
TEST_F(SaveValueTest_146, EmptyUserKeyMatch_146) {
  std::string target_key = "";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey("", 50, kTypeValue);
  std::string val = "emptyval";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "emptyval");
}

// Test: Empty value with matching key
TEST_F(SaveValueTest_146, EmptyValueFound_146) {
  std::string target_key = "mykey";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 200, kTypeValue);
  std::string val = "";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "");
}

// Test: Deletion does not overwrite pre-existing value string
TEST_F(SaveValueTest_146, DeletionDoesNotOverwriteValue_146) {
  std::string target_key = "delkey";
  value_ = "previousvalue";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 300, kTypeDeletion);

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice("newvalue"));

  EXPECT_EQ(s.state, kDeleted);
  EXPECT_EQ(value_, "previousvalue");
}

// Test: Large value is correctly assigned
TEST_F(SaveValueTest_146, LargeValueFound_146) {
  std::string target_key = "bigkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 999, kTypeValue);
  std::string large_val(100000, 'x');

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(large_val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, large_val);
}

// Test: Non-matching key with same prefix
TEST_F(SaveValueTest_146, PrefixMatchButDifferentKey_146) {
  std::string target_key = "key";
  Saver s = MakeSaver(target_key);

  std::string different_key = "key2";
  std::string ikey = EncodeInternalKey(different_key, 100, kTypeValue);

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice("val"));

  EXPECT_EQ(s.state, kNotFound);
}

// Test: Sequence number 0 with kTypeValue should still work
TEST_F(SaveValueTest_146, MinSequenceNumber_146) {
  std::string target_key = "seqkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 0, kTypeValue);
  std::string val = "seqval";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "seqval");
}

// Test: Maximum sequence number
TEST_F(SaveValueTest_146, MaxSequenceNumber_146) {
  std::string target_key = "maxseq";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, kMaxSequenceNumber, kTypeValue);
  std::string val = "maxval";

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_, "maxval");
}

// Test: Value with binary data (including null bytes)
TEST_F(SaveValueTest_146, BinaryValueFound_146) {
  std::string target_key = "binkey";
  Saver s = MakeSaver(target_key);

  std::string ikey = EncodeInternalKey(target_key, 42, kTypeValue);
  std::string val("\x00\x01\x02\x03", 4);

  SaveValue(reinterpret_cast<void*>(&s), Slice(ikey), Slice(val));

  EXPECT_EQ(s.state, kFound);
  EXPECT_EQ(value_.size(), 4u);
  EXPECT_EQ(value_, val);
}

}  // anonymous namespace
}  // namespace leveldb
