// db/memtable_iterator_key_test.cc
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "util/coding.h"

#include <gtest/gtest.h>

using namespace leveldb;

namespace {

// Helper: build the expected *internal key* slice that MemTableIterator::key()
// exposes (i.e., the length-prefixed field's payload).
static std::string BuildInternalKey(const Slice& user_key,
                                    SequenceNumber seq,
                                    ValueType type) {
  InternalKey ikey(user_key, seq, type);
  std::string encoded;
  AppendInternalKey(&encoded, ikey);  // encodes: user_key || 8-byte tag
  return encoded;                     // This is what key() should equal
}

class MemTableIteratorKeyTest_363 : public ::testing::Test {
 protected:
  MemTableIteratorKeyTest_363()
      : icmp_(BytewiseComparator()), mem_(icmp_) {}

  InternalKeyComparator icmp_;
  MemTable mem_;
};

}  // namespace

// Normal operation: key() returns the internal-key bytes for the current entry.
TEST_F(MemTableIteratorKeyTest_363, KeyReturnsInternalKeyBytes_363) {
  const Slice k("a");
  const Slice v("va");
  const SequenceNumber seq = 100;

  mem_.Add(seq, kTypeValue, k, v);

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());

  const Slice got = it->key();  // Observable behavior under test
  const std::string expected = BuildInternalKey(k, seq, kTypeValue);

  ASSERT_EQ(got.size(), expected.size());
  ASSERT_EQ(std::string(got.data(), got.size()), expected);
}

// Iteration: key() updates as the iterator advances.
TEST_F(MemTableIteratorKeyTest_363, KeyChangesAfterNext_363) {
  const SequenceNumber s1 = 7, s2 = 9;
  mem_.Add(s1, kTypeValue, Slice("a"), Slice("1"));
  mem_.Add(s2, kTypeValue, Slice("b"), Slice("2"));

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  std::string first_key = std::string(it->key().data(), it->key().size());

  it->Next();
  ASSERT_TRUE(it->Valid());
  std::string second_key = std::string(it->key().data(), it->key().size());

  // They should differ because the iterator moved to the next entry.
  EXPECT_NE(first_key, second_key);

  // And second matches the known internal form of the second user key.
  const std::string expected_second = BuildInternalKey(Slice("b"), s2, kTypeValue);
  EXPECT_EQ(second_key, expected_second);
}

// Boundary: empty user key is supported; key() exposes an 8-byte-only payload (tag) plus empty user key.
TEST_F(MemTableIteratorKeyTest_363, EmptyUserKey_363) {
  const Slice empty_key("");
  const Slice val("x");
  const SequenceNumber seq = 42;

  mem_.Add(seq, kTypeValue, empty_key, val);

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());

  const Slice got = it->key();
  const std::string expected = BuildInternalKey(empty_key, seq, kTypeValue);

  ASSERT_EQ(got.size(), expected.size());
  ASSERT_EQ(std::string(got.data(), got.size()), expected);
}

// Seek behavior: key() corresponds to the entry found by Seek().
TEST_F(MemTableIteratorKeyTest_363, KeyMatchesSeekTargetEntry_363) {
  mem_.Add(5,  kTypeValue, Slice("aa"), Slice("x"));
  mem_.Add(10, kTypeValue, Slice("ab"), Slice("y"));
  mem_.Add(15, kTypeValue, Slice("b"),  Slice("z"));

  std::unique_ptr<Iterator> it(mem_.NewIterator());

  // Seek to "ab" and verify key().
  it->Seek(Slice("ab"));
  ASSERT_TRUE(it->Valid());
  const std::string expected_ab = BuildInternalKey(Slice("ab"), 10, kTypeValue);
  EXPECT_EQ(std::string(it->key().data(), it->key().size()), expected_ab);
}

// Overwrite same user key with a newer sequence; key() should reflect the specific entry we are on.
// We avoid assuming order semantics beyond what Seek chooses.
TEST_F(MemTableIteratorKeyTest_363, SameUserKeyDifferentSeq_363) {
  // Two versions for the same user key "k"
  mem_.Add(1,  kTypeValue, Slice("k"), Slice("old"));
  mem_.Add(100, kTypeValue, Slice("k"), Slice("new"));

  std::unique_ptr<Iterator> it(mem_.NewIterator());

  // Seek directly to "k" and check that key() equals the internal key
  // for some "k" version that Seek positions at. Then verify that at least
  // one of the two encoded internal keys matches the observed key().
  it->Seek(Slice("k"));
  ASSERT_TRUE(it->Valid());
  const std::string observed = std::string(it->key().data(), it->key().size());

  const std::string ik_old = BuildInternalKey(Slice("k"), 1, kTypeValue);
  const std::string ik_new = BuildInternalKey(Slice("k"), 100, kTypeValue);

  // We do not assert which version Seek picks (to avoid encoding internal ordering rules),
  // but key() must equal one valid internal representation for "k".
  EXPECT_TRUE(observed == ik_old || observed == ik_new);
}
