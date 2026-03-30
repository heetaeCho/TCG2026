// File: db/version_set_level_file_num_iterator_test.cc

#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "util/testutil.h"   // If available for helpers (optional)
#include "leveldb/comparator.h"

using leveldb::FileMetaData;
using leveldb::InternalKey;
using leveldb::InternalKeyComparator;
using leveldb::Iterator;
using leveldb::Slice;
using leveldb::Status;
using leveldb::Version;
using leveldb::BytewiseComparator;

namespace {

// Helper: create an InternalKey from a user key, with fixed seq/type.
// We do not assert anything about how the iterator interprets keys;
// we just need valid InternalKey objects to populate FileMetaData.
InternalKey IK(const std::string& user_key) {
  InternalKey k;
  // Use a fixed sequence/type suitable for seeks; this is a public API.
  k.Set(user_key, /*sequence=*/100, leveldb::kValueTypeForSeek);
  return k;
}

// Helper: allocate a FileMetaData with the given fields set.
// We *only* set documented public fields we need for construction.
FileMetaData* MakeFile(uint64_t number,
                       const std::string& smallest,
                       const std::string& largest) {
  auto* f = new FileMetaData();
  f->number = number;
  f->smallest = IK(smallest);
  f->largest  = IK(largest);
  return f;
}

// Owns a vector of FileMetaData* and deletes them in dtor to avoid leaks.
struct FileList {
  std::vector<FileMetaData*> files;
  ~FileList() {
    for (auto* f : files) delete f;
  }
};

}  // namespace

// TEST_ID: 137
class LevelFileNumIteratorTest_137 : public ::testing::Test {
 protected:
  InternalKeyComparator icmp_{*BytewiseComparator()};
};

// [Normal] Empty file list: SeekToFirst should make iterator invalid.
TEST_F(LevelFileNumIteratorTest_137, SeekToFirst_OnEmpty_IsInvalid_137) {
  FileList owned;
  const std::vector<FileMetaData*>* flist = &owned.files;

  Version::LevelFileNumIterator it(icmp_, flist);

  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

// [Normal] Single file: SeekToFirst -> Valid, key() corresponds to that file,
// Next() -> becomes invalid. We set smallest==largest to avoid assuming which
// boundary the iterator uses for key() — still black-box compliant.
TEST_F(LevelFileNumIteratorTest_137, SeekToFirst_SingleFile_ThenNext_137) {
  FileList owned;
  owned.files.push_back(MakeFile(/*number=*/11, /*smallest=*/"a", /*largest=*/"a"));
  const std::vector<FileMetaData*>* flist = &owned.files;

  Version::LevelFileNumIterator it(icmp_, flist);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid()) << "Iterator should be valid when list has one file";

  // key() should equal the only file's boundary key. We set smallest==largest=="a".
  Slice k = it.key();
  EXPECT_EQ(k.compare(InternalKey("a", 100, leveldb::kValueTypeForSeek).Encode()), 0);

  // value() should be stable and non-empty for a valid iterator position.
  Slice v = it.value();
  EXPECT_GT(v.size(), 0u);

  it.Next();
  EXPECT_FALSE(it.Valid()) << "Next() from the only element should invalidate";
  EXPECT_TRUE(it.status().ok());
}

// [Normal/Ordering] Multiple files already in sorted boundary order:
// SeekToFirst should land at the first logical element by the comparator.
// We again set smallest==largest per file to avoid making assumptions about
// which boundary key() returns — only relative order is asserted.
TEST_F(LevelFileNumIteratorTest_137, SeekToFirst_MultipleFiles_Order_137) {
  FileList owned;
  owned.files.push_back(MakeFile(/*number=*/21, "a", "a"));
  owned.files.push_back(MakeFile(/*number=*/22, "m", "m"));
  owned.files.push_back(MakeFile(/*number=*/23, "z", "z"));

  const std::vector<FileMetaData*>* flist = &owned.files;
  Version::LevelFileNumIterator it(icmp_, flist);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  // Expect first key == "a"
  Slice k1 = it.key();
  EXPECT_EQ(k1.compare(InternalKey("a", 100, leveldb::kValueTypeForSeek).Encode()), 0);

  it.Next();
  ASSERT_TRUE(it.Valid());
  Slice k2 = it.key();
  EXPECT_EQ(k2.compare(InternalKey("m", 100, leveldb::kValueTypeForSeek).Encode()), 0);

  it.Next();
  ASSERT_TRUE(it.Valid());
  Slice k3 = it.key();
  EXPECT_EQ(k3.compare(InternalKey("z", 100, leveldb::kValueTypeForSeek).Encode()), 0);

  it.Next();
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

// [Boundary] SeekToFirst then Prev(): behavior at the lower bound.
// Typical iterator semantics make Prev() invalid at the beginning.
// We assert only the observable validity/result without relying on internals.
TEST_F(LevelFileNumIteratorTest_137, Prev_FromFirst_GoesInvalid_137) {
  FileList owned;
  owned.files.push_back(MakeFile(/*number=*/31, "b", "b"));
  owned.files.push_back(MakeFile(/*number=*/32, "c", "c"));

  const std::vector<FileMetaData*>* flist = &owned.files;
  Version::LevelFileNumIterator it(icmp_, flist);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  it.Prev();
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

// [Boundary] Calling SeekToFirst repeatedly is idempotent and safe.
TEST_F(LevelFileNumIteratorTest_137, SeekToFirst_Idempotent_137) {
  FileList owned;
  owned.files.push_back(MakeFile(/*number=*/41, "k", "k"));

  const std::vector<FileMetaData*>* flist = &owned.files;
  Version::LevelFileNumIterator it(icmp_, flist);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  Slice k1 = it.key();

  it.SeekToFirst();  // repeat
  ASSERT_TRUE(it.Valid());
  Slice k2 = it.key();

  EXPECT_EQ(k1.compare(k2), 0);
  EXPECT_TRUE(it.status().ok());
}

