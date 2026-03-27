// File: version_debug_string_test_156.cc

// NOTE: We only relax access to construct the object and seed inputs,
// and we verify behavior strictly via the public DebugString() output.
#define private public
#define protected public
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#undef private
#undef protected

#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace leveldb {

class VersionDebugStringTest_156 : public ::testing::Test {
protected:
  // Helper to make a FileMetaData with minimal fields set
  static FileMetaData* MakeFile(uint64_t number, uint64_t size) {
    auto* f = new FileMetaData();
    f->number = number;
    f->file_size = size;
    // smallest/largest left default-constructed; DebugString() should still format "[ .. ]"
    return f;
  }

  // Clean up all file pointers we push into files_
  static void CleanupFiles(Version* v) {
    for (int lvl = 0; lvl < config::kNumLevels; ++lvl) {
      for (auto* f : v->files_[lvl]) delete f;
      v->files_[lvl].clear();
    }
  }
};

// Empty version: should list all levels with headers and no files
TEST_F(VersionDebugStringTest_156, EmptyVersionListsAllLevels_156) {
  VersionSet* vs = nullptr;           // Not used by DebugString()
  Version v(vs);                      // Construct instance
  std::string out = v.DebugString();

  // Must contain headers for all 0..6 levels
  for (int lvl = 0; lvl < config::kNumLevels; ++lvl) {
    std::string hdr = std::string("--- level ") + std::to_string(lvl) + " ---\n";
    EXPECT_NE(std::string::npos, out.find(hdr)) << "Missing header for level " << lvl;
  }

  // No file lines expected
  // (Any file line would include ":<size>[", which shouldn't appear.)
  EXPECT_EQ(std::string::npos, out.find(":["));
}

// Single file at a middle level
TEST_F(VersionDebugStringTest_156, SingleFileAtLevel2FormatsCorrectly_156) {
  VersionSet* vs = nullptr;
  Version v(vs);

  v.files_[2].push_back(MakeFile(/*number=*/1u, /*size=*/100u));

  std::string out = v.DebugString();

  // Header must be present
  EXPECT_NE(std::string::npos, out.find("--- level 2 ---\n"));

  // Line should include " 1:100[" and the key range placeholder " .. "
  EXPECT_NE(std::string::npos, out.find(" 1:100["));
  EXPECT_NE(std::string::npos, out.find(" .. "));
  EXPECT_NE(std::string::npos, out.find("]\n"));

  CleanupFiles(&v);
}

// Files at boundary levels (0 and 6)
TEST_F(VersionDebugStringTest_156, FilesAtBoundaryLevelsAreShown_156) {
  VersionSet* vs = nullptr;
  Version v(vs);

  v.files_[0].push_back(MakeFile(10u, 0u));         // zero-size file boundary
  v.files_[6].push_back(MakeFile(999999u, 4096u));  // last level

  std::string out = v.DebugString();

  // Level 0 header and file line
  EXPECT_NE(std::string::npos, out.find("--- level 0 ---\n"));
  EXPECT_NE(std::string::npos, out.find(" 10:0["));

  // Level 6 header and file line
  EXPECT_NE(std::string::npos, out.find("--- level 6 ---\n"));
  EXPECT_NE(std::string::npos, out.find(" 999999:4096["));

  // Range placeholder should appear on both lines
  // (We just check it appears at least once in the output.)
  EXPECT_NE(std::string::npos, out.find(" .. "));

  CleanupFiles(&v);
}

// Multiple files in same level should each appear on their own line in order pushed
TEST_F(VersionDebugStringTest_156, MultipleFilesWithinLevelAreListed_156) {
  VersionSet* vs = nullptr;
  Version v(vs);

  v.files_[3].push_back(MakeFile(3u, 300u));
  v.files_[3].push_back(MakeFile(4u, 400u));
  v.files_[3].push_back(MakeFile(5u, 500u));

  std::string out = v.DebugString();

  // Header
  EXPECT_NE(std::string::npos, out.find("--- level 3 ---\n"));

  // Each file line should be present
  EXPECT_NE(std::string::npos, out.find(" 3:300["));
  EXPECT_NE(std::string::npos, out.find(" 4:400["));
  EXPECT_NE(std::string::npos, out.find(" 5:500["));

  // Basic bracket/range formatting token appears
  EXPECT_NE(std::string::npos, out.find(" .. "));

  CleanupFiles(&v);
}

// Large values formatting (stress numbers)
TEST_F(VersionDebugStringTest_156, LargeNumbersArePrintedVerbatim_156) {
  VersionSet* vs = nullptr;
  Version v(vs);

  const uint64_t big_num = 18446744073709551615ull; // max uint64
  const uint64_t big_sz  = 9223372036854775807ull;  // large value

  v.files_[1].push_back(MakeFile(big_num, big_sz));
  std::string out = v.DebugString();

  // Expect decimal rendering of both values
  EXPECT_NE(std::string::npos, out.find(std::to_string(big_num) + ":" + std::to_string(big_sz) + "["));

  CleanupFiles(&v);
}

} // namespace leveldb
