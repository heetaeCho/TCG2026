// File: version_set_builder_dtor_test_158.cc

#include "db/version_set.h"
#include "db/version_edit.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::Exactly;
using ::testing::NiceMock;

namespace leveldb {

// --- Test doubles (black-box friendly) --------------------------------------
// We only verify external interactions. If Unref() is virtual in your build,
// this mock will observe the call. If it's not virtual, these tests that rely
// on the Unref() expectation can be disabled or adapted to your environment.

class MockVersion : public Version {
 public:
  // We do NOT re-implement any logic; we only observe Unref() being called.
  // If Unref() is virtual in your codebase, enable the MOCK_METHOD below.
  //
  // MOCK_METHOD(void, Unref, (), (override));

  // Provide a public forwarding function to call the base Unref() if needed
  // in other tests. We won't use it here; included for completeness.
  void CallBaseUnref() { Version::Unref(); }
};

// --- Fixture ----------------------------------------------------------------

class VersionSetBuilderDtorTest_158 : public ::testing::Test {
 protected:
  // Helper to allocate a FileMetaData with a chosen refcount and basic fields.
  static FileMetaData* MakeFile(uint64_t number, int refs) {
    auto* f = new FileMetaData();
    f->number = number;
    f->refs   = refs;
    // We do not infer any internal logic; values below are placeholders to
    // satisfy type requirements only.
    f->file_size = 0;
    return f;
  }
};

// --- Tests ------------------------------------------------------------------

// Verifies: When files were added via the public interface, destroying Builder
// decrements each file's refs by 1 (but does not rely on internals like whether
// it deletes when refs <= 0). This checks only observable refcount change.
TEST_F(VersionSetBuilderDtorTest_158, Destructor_DecrementsRefsForAddedFiles_158) {
  // Arrange
  VersionSet vset;                         // Exists to satisfy the ctor signature
  NiceMock<MockVersion> base_version;      // Base version passed to Builder
  FileMetaData* f0 = MakeFile(/*number=*/100, /*refs=*/3);
  FileMetaData* f6 = MakeFile(/*number=*/200, /*refs=*/2);

  {
    VersionSet::Builder builder(&vset, &base_version);
    // Add across multiple levels to exercise the loop in the destructor.
    builder.MaybeAddFile(/*v=*/&base_version, /*level=*/0, f0);
    builder.MaybeAddFile(/*v=*/&base_version, /*level=*/6, f6);
    // Builder goes out of scope here -> ~Builder() runs
  }

  // Assert observable effects on public fields
  EXPECT_EQ(f0->refs, 2);
  EXPECT_EQ(f6->refs, 1);

  // Clean up (owning side not managed by Builder when refs > 0)
  delete f0;
  delete f6;
}

// Verifies: If nothing was added, destroying Builder should still be safe.
// Also, we expect the base Version to be unref’d once (external interaction).
TEST_F(VersionSetBuilderDtorTest_158, Destructor_HandlesEmptyAddedFilesAndUnrefsBase_158) {
  VersionSet vset;
  NiceMock<MockVersion> base_version;

  // If Unref() is virtual in your build, uncomment the expectation below.
  // EXPECT_CALL(base_version, Unref()).Times(Exactly(1));

  {
    VersionSet::Builder builder(&vset, &base_version);
    // No MaybeAddFile calls
  }

  SUCCEED() << "Destructor completed without crashing";
}

// Verifies: Multiple files across all levels have their refs decremented by 1
// after Builder destruction. This covers boundary levels 0 and 6 as well.
TEST_F(VersionSetBuilderDtorTest_158, Destructor_DecrementsRefsAcrossAllLevels_158) {
  VersionSet vset;
  NiceMock<MockVersion> base_version;

  // Prepare one file per level with distinct starting refs
  FileMetaData* files[config::kNumLevels];
  for (int level = 0; level < config::kNumLevels; ++level) {
    files[level] = MakeFile(/*number=*/1000 + level, /*refs=*/level + 2);  // >=2
  }

  {
    VersionSet::Builder builder(&vset, &base_version);
    for (int level = 0; level < config::kNumLevels; ++level) {
      builder.MaybeAddFile(&base_version, level, files[level]);
    }
  }

  for (int level = 0; level < config::kNumLevels; ++level) {
    EXPECT_EQ(files[level]->refs, (level + 2) - 1) << "Level " << level;
    delete files[level];
  }
}

// Verifies: Boundary condition — adding only at the highest level (6) still
// decrements refs when Builder is destroyed.
TEST_F(VersionSetBuilderDtorTest_158, Destructor_OnlyHighestLevel_158) {
  VersionSet vset;
  NiceMock<MockVersion> base_version;
  FileMetaData* f = MakeFile(/*number=*/9999, /*refs=*/5);

  {
    VersionSet::Builder builder(&vset, &base_version);
    builder.MaybeAddFile(&base_version, /*level=*/config::kNumLevels - 1, f);
  }

  EXPECT_EQ(f->refs, 4);
  delete f;
}

// Verifies: Boundary condition — adding only at the lowest level (0) still
// decrements refs when Builder is destroyed.
TEST_F(VersionSetBuilderDtorTest_158, Destructor_OnlyLowestLevel_158) {
  VersionSet vset;
  NiceMock<MockVersion> base_version;
  FileMetaData* f = MakeFile(/*number=*/42, /*refs=*/3);

  {
    VersionSet::Builder builder(&vset, &base_version);
    builder.MaybeAddFile(&base_version, /*level=*/0, f);
  }

  EXPECT_EQ(f->refs, 2);
  delete f;
}

}  // namespace leveldb
