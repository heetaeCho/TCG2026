// File: version_set_maybeaddfile_test.cc

#include <gtest/gtest.h>

#include "db/version_set.cc"     // Pulls in the Builder::MaybeAddFile implementation.
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

namespace leveldb {

// Minimal stub user comparator to satisfy InternalKeyComparator where needed.
// We never trigger comparator-based assertions in these tests.
class DummyUserComparator : public Comparator {
 public:
  const char* Name() const override { return "dummy"; }
  int Compare(const Slice& a, const Slice& b) const override {
    // Arbitrary but consistent ordering on bytes.
    if (a.compare(b) < 0) return -1;
    if (a.compare(b) > 0) return 1;
    return 0;
  }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

class MaybeAddFileTest_161 : public ::testing::Test {
 protected:
  // Many of VersionSet's collaborators are irrelevant for MaybeAddFile.
  // We only need a Version instance and a Builder bound to some vset pointer.
  // The comparator is never exercised in the covered paths (level==0, or first
  // file in higher level), but we still wire a valid object.
  DummyUserComparator user_cmp_;
  InternalKeyComparator ikey_cmp_{&user_cmp_};

  // The Builder requires a VersionSet* in its ctor but only dereferences it
  // when the level>0 ordering assertion path runs and the target level already
  // has files. These tests avoid that path unless explicitly stated.
  // We provide a trivially constructed VersionSet with minimal args; depending
  // on your build of leveldb, you may adapt Options/TableCache if needed.
  // Here we avoid constructing a full VersionSet and pass a dummy pointer,
  // since the covered code paths do not touch vset_ fields.
  VersionSet* dummy_vset_ = nullptr;

  // Helper to create a fresh Version-like object we can pass into MaybeAddFile.
  // In the provided stubs, Version is constructible for tests via default/new.
  Version* MakeEmptyVersion() {
    // In common leveldb test setups, Version is created by VersionSet.
    // For these tests, we rely on the simplified stubs in the prompt that allow
    // direct instantiation. If your environment requires a VersionSet factory,
    // adapt accordingly.
    return new Version(dummy_vset_);
  }

  // Utility to build a FileMetaData with a specific file number.
  static FileMetaData* NewFile(uint64_t number) {
    auto* f = new FileMetaData();
    f->number = number;
    // smallest/largest left default; not used in tested paths.
    return f;
  }
};

// Normal operation: adding a file at level 0 increments refs and appears in v->NumFiles(0).
TEST_F(MaybeAddFileTest_161, AddAtLevel0_IncrementsRefsAndCount_161) {
  std::unique_ptr<Version> v(MakeEmptyVersion());
  VersionSet::Builder builder(dummy_vset_, v.get());

  std::unique_ptr<FileMetaData> f(NewFile(/*number=*/101));
  ASSERT_EQ(0, f->refs);

  builder.MaybeAddFile(v.get(), /*level=*/0, f.get());

  EXPECT_EQ(1, f->refs);            // observable on the object we supplied
  EXPECT_EQ(1, v->NumFiles(0));     // observable via public accessor
}

// Boundary-ish: adding the first file at a higher level should also succeed,
// and the ordering precondition is not evaluated when the target level is empty.
TEST_F(MaybeAddFileTest_161, AddFirstFileAtHigherLevel_Succeeds_161) {
  std::unique_ptr<Version> v(MakeEmptyVersion());
  VersionSet::Builder builder(dummy_vset_, v.get());

  std::unique_ptr<FileMetaData> f(NewFile(/*number=*/202));

  builder.MaybeAddFile(v.get(), /*level=*/2, f.get());

  EXPECT_EQ(1, f->refs);
  EXPECT_EQ(1, v->NumFiles(2));
}

// Exceptional/edge case: when the file number is marked deleted for that level,
// MaybeAddFile must skip the insertion and must not bump refs.
TEST_F(MaybeAddFileTest_161, DeletedFile_IsSkipped_NoRefBump_NoCountChange_161) {
  std::unique_ptr<Version> v(MakeEmptyVersion());
  VersionSet::Builder builder(dummy_vset_, v.get());

  std::unique_ptr<FileMetaData> f(NewFile(/*number=*/303));

  // Simulate "deleted" via the Builder's observable collaborator path:
  // In real code this is normally driven by Apply(VersionEdit), but here we
  // mark the set directly to avoid re-implementing Apply logic.
  // This only influences the observable branch condition inside MaybeAddFile.
  builder.levels_[1].deleted_files.insert(f->number);

  builder.MaybeAddFile(v.get(), /*level=*/1, f.get());

  EXPECT_EQ(0, f->refs);            // no bump
  EXPECT_EQ(0, v->NumFiles(1));     // not added
}

// Normal operation: multiple adds at level 0 append and increase the count.
TEST_F(MaybeAddFileTest_161, MultipleAddsAtLevel0_IncreaseCount_161) {
  std::unique_ptr<Version> v(MakeEmptyVersion());
  VersionSet::Builder builder(dummy_vset_, v.get());

  std::unique_ptr<FileMetaData> f1(NewFile(401));
  std::unique_ptr<FileMetaData> f2(NewFile(402));

  builder.MaybeAddFile(v.get(), /*level=*/0, f1.get());
  builder.MaybeAddFile(v.get(), /*level=*/0, f2.get());

  EXPECT_EQ(1, f1->refs);
  EXPECT_EQ(1, f2->refs);
  EXPECT_EQ(2, v->NumFiles(0));
}

}  // namespace leveldb
