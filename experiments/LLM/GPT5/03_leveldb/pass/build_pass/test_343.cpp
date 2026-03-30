// File: version_edit_debugstring_test_343.cc

#include <gtest/gtest.h>
#include "db/version_edit.h"   // assumes VersionEdit, FileMetaData, InternalKey, etc. are declared here

using leveldb::VersionEdit;
using leveldb::InternalKey;
using leveldb::SequenceNumber;

namespace {

// Small helper to count occurrences of a substring in a string.
static int CountSubstr(const std::string& haystack, const std::string& needle) {
  if (needle.empty()) return 0;
  int count = 0;
  std::string::size_type pos = 0;
  while ((pos = haystack.find(needle, pos)) != std::string::npos) {
    ++count;
    pos += needle.size();
  }
  return count;
}

class VersionEditDebugStringTest_343 : public ::testing::Test {
 protected:
  VersionEdit ed_;
};

}  // namespace

// 1) Empty edit: only header/trailer; no fields appear.
TEST_F(VersionEditDebugStringTest_343, EmptyEdit_OnlyBraces_NoFields_343) {
  const std::string s = ed_.DebugString();

  // Always starts/ends with the container lines
  EXPECT_NE(std::string::npos, s.find("VersionEdit {"));
  EXPECT_NE(std::string::npos, s.find("\n}\n"));

  // Should NOT mention any of the optional sections when nothing was set
  EXPECT_EQ(std::string::npos, s.find("Comparator:"));
  EXPECT_EQ(std::string::npos, s.find("LogNumber:"));
  EXPECT_EQ(std::string::npos, s.find("PrevLogNumber:"));
  EXPECT_EQ(std::string::npos, s.find("NextFile:"));
  EXPECT_EQ(std::string::npos, s.find("LastSeq:"));
  EXPECT_EQ(std::string::npos, s.find("CompactPointer:"));
  EXPECT_EQ(std::string::npos, s.find("RemoveFile:"));
  EXPECT_EQ(std::string::npos, s.find("AddFile:"));
}

// 2) Set numeric fields: they should appear verbatim with their values.
TEST_F(VersionEditDebugStringTest_343, NumericFields_AppearWhenSet_343) {
  ed_.SetLogNumber(1234);
  ed_.SetPrevLogNumber(55);
  ed_.SetNextFile(777);
  ed_.SetLastSequence(static_cast<SequenceNumber>(9999));

  const std::string s = ed_.DebugString();

  EXPECT_NE(std::string::npos, s.find("\n LogNumber: 1234"));
  EXPECT_NE(std::string::npos, s.find("\n PrevLogNumber: 55"));
  EXPECT_NE(std::string::npos, s.find("\n NextFile: 777"));
  EXPECT_NE(std::string::npos, s.find("\n LastSeq: 9999"));
}

// 3) RemoveFile lines: one line per removed item (order not required).
TEST_F(VersionEditDebugStringTest_343, RemoveFile_EmitsOneLinePerEntry_343) {
  ed_.RemoveFile(0, 10);
  ed_.RemoveFile(2, 999);

  const std::string s = ed_.DebugString();

  // One "RemoveFile:" per call.
  EXPECT_EQ(2, CountSubstr(s, "RemoveFile:"));

  // Each entry encodes "level fileNumber" (pair<int, uint64_t>)
  EXPECT_NE(std::string::npos, s.find("\n RemoveFile: 0 10"));
  EXPECT_NE(std::string::npos, s.find("\n RemoveFile: 2 999"));
}

// 4) AddFile lines: include level, file number, and file size.
//    We pass default-constructed InternalKey objects; we don't assert their textual form.
TEST_F(VersionEditDebugStringTest_343, AddFile_IncludesLevelNumberSize_343) {
  InternalKey smallest;  // default constructed, treated as black box
  InternalKey largest;

  ed_.AddFile(/*level=*/2, /*file=*/100, /*file_size=*/2048, smallest, largest);

  const std::string s = ed_.DebugString();

  // One AddFile line emitted
  EXPECT_EQ(1, CountSubstr(s, "AddFile:"));

  // Must contain the numeric triplet in order: "<level> <number> <size>"
  EXPECT_NE(std::string::npos, s.find("\n AddFile: 2 100 2048"));
}

// 5) CompactPointer lines: one per pointer; level is shown, key is printed via InternalKey::DebugString().
//    We only verify presence and count, not the key's string contents.
TEST_F(VersionEditDebugStringTest_343, CompactPointer_OneLinePerPointer_343) {
  InternalKey k1, k2;  // default constructed; content considered a black box

  ed_.SetCompactPointer(/*level=*/1, k1);
  ed_.SetCompactPointer(/*level=*/3, k2);

  const std::string s = ed_.DebugString();

  EXPECT_EQ(2, CountSubstr(s, "CompactPointer:"));
  // Check levels are present after the tag. We don't assert on the key string itself.
  EXPECT_NE(std::string::npos, s.find("\n CompactPointer: 1 "));
  EXPECT_NE(std::string::npos, s.find("\n CompactPointer: 3 "));
}

// 6) Mixed entries: ensure all selected sections coexist and the trailer remains.
TEST_F(VersionEditDebugStringTest_343, Mixed_SettersAddRemoveCompact_TrailerPresent_343) {
  ed_.SetLogNumber(1);
  ed_.SetPrevLogNumber(2);
  ed_.SetNextFile(3);
  ed_.SetLastSequence(static_cast<SequenceNumber>(4));

  InternalKey a, b, c;
  ed_.SetCompactPointer(0, a);
  ed_.AddFile(1, 11, 111, b, c);
  ed_.RemoveFile(2, 22);

  const std::string s = ed_.DebugString();

  // Each selected section appears at least once
  EXPECT_NE(std::string::npos, s.find("LogNumber: 1"));
  EXPECT_NE(std::string::npos, s.find("PrevLogNumber: 2"));
  EXPECT_NE(std::string::npos, s.find("NextFile: 3"));
  EXPECT_NE(std::string::npos, s.find("LastSeq: 4"));
  EXPECT_NE(std::string::npos, s.find("CompactPointer: 0 "));
  EXPECT_NE(std::string::npos, s.find("AddFile: 1 11 111"));
  EXPECT_NE(std::string::npos, s.find("RemoveFile: 2 22"));

  // Trailer must be present
  EXPECT_NE(std::string::npos, s.find("\n}\n"));
}
