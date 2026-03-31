#include "gtest/gtest.h"
#include "build_log.h"
#include <string>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

// Test that HashCommand produces consistent results for the same input
TEST(HashCollisionBench_121, SameInputProducesSameHash_121) {
  const char* command = "gcc -o foo.o -c foo.c";
  uint64_t hash1 = BuildLog::LogEntry::HashCommand(command);
  uint64_t hash2 = BuildLog::LogEntry::HashCommand(command);
  EXPECT_EQ(hash1, hash2);
}

// Test that HashCommand produces different hashes for different inputs
TEST(HashCollisionBench_121, DifferentInputsProduceDifferentHashes_121) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("gcc -o foo.o -c foo.c");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("gcc -o bar.o -c bar.c");
  EXPECT_NE(hash1, hash2);
}

// Test empty string hashing
TEST(HashCollisionBench_121, EmptyStringHash_121) {
  uint64_t hash = BuildLog::LogEntry::HashCommand("");
  // Just ensure it doesn't crash and returns a value
  // The hash of empty string should be consistent
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("");
  EXPECT_EQ(hash, hash2);
}

// Test single character hashing
TEST(HashCollisionBench_121, SingleCharHash_121) {
  uint64_t hashA = BuildLog::LogEntry::HashCommand("a");
  uint64_t hashB = BuildLog::LogEntry::HashCommand("b");
  EXPECT_NE(hashA, hashB);
}

// Test that similar strings produce different hashes
TEST(HashCollisionBench_121, SimilarStringsProduceDifferentHashes_121) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("command1");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("command2");
  EXPECT_NE(hash1, hash2);
}

// Test hashing with long strings
TEST(HashCollisionBench_121, LongStringHash_121) {
  string longStr(10000, 'x');
  uint64_t hash1 = BuildLog::LogEntry::HashCommand(longStr);
  uint64_t hash2 = BuildLog::LogEntry::HashCommand(longStr);
  EXPECT_EQ(hash1, hash2);
}

// Test hashing with strings differing only in the last character
TEST(HashCollisionBench_121, StringsDifferingInLastChar_121) {
  string str1 = "abcdefghijklmnopqrstuvwxyz0";
  string str2 = "abcdefghijklmnopqrstuvwxyz1";
  uint64_t hash1 = BuildLog::LogEntry::HashCommand(str1);
  uint64_t hash2 = BuildLog::LogEntry::HashCommand(str2);
  EXPECT_NE(hash1, hash2);
}

// Test hashing with strings differing only in the first character
TEST(HashCollisionBench_121, StringsDifferingInFirstChar_121) {
  string str1 = "0abcdefghijklmnopqrstuvwxyz";
  string str2 = "1abcdefghijklmnopqrstuvwxyz";
  uint64_t hash1 = BuildLog::LogEntry::HashCommand(str1);
  uint64_t hash2 = BuildLog::LogEntry::HashCommand(str2);
  EXPECT_NE(hash1, hash2);
}

// Test that a set of varied commands produce unique hashes (no collisions in small set)
TEST(HashCollisionBench_121, NoCollisionsInSmallSet_121) {
  vector<string> commands = {
    "gcc -o foo.o -c foo.c",
    "gcc -o bar.o -c bar.c",
    "g++ -o baz.o -c baz.cc",
    "clang -o qux.o -c qux.c",
    "ar rcs libfoo.a foo.o bar.o",
    "ld -o program foo.o bar.o baz.o",
    "cc -shared -o libfoo.so foo.o",
    "strip program",
    "echo hello",
    "cat /dev/null"
  };

  set<uint64_t> hashSet;
  for (const auto& cmd : commands) {
    uint64_t h = BuildLog::LogEntry::HashCommand(cmd);
    hashSet.insert(h);
  }
  EXPECT_EQ(hashSet.size(), commands.size());
}

// Test LogEntry construction
TEST(HashCollisionBench_121, LogEntryConstruction_121) {
  BuildLog::LogEntry entry("output.o");
  // Default values
  EXPECT_EQ(entry.command_hash, 0u);
  EXPECT_EQ(entry.start_time, 0);
  EXPECT_EQ(entry.end_time, 0);
  EXPECT_EQ(entry.mtime, 0);
}

// Test LogEntry full construction
TEST(HashCollisionBench_121, LogEntryFullConstruction_121) {
  uint64_t hash = BuildLog::LogEntry::HashCommand("some command");
  BuildLog::LogEntry entry("output.o", hash, 100, 200, 300);
  EXPECT_EQ(entry.command_hash, hash);
  EXPECT_EQ(entry.start_time, 100);
  EXPECT_EQ(entry.end_time, 200);
  EXPECT_EQ(entry.mtime, 300);
}

// Test LogEntry equality operator
TEST(HashCollisionBench_121, LogEntryEquality_121) {
  uint64_t hash = BuildLog::LogEntry::HashCommand("cmd");
  BuildLog::LogEntry entry1("out.o", hash, 10, 20, 30);
  BuildLog::LogEntry entry2("out.o", hash, 10, 20, 30);
  EXPECT_TRUE(entry1 == entry2);
}

// Test LogEntry inequality
TEST(HashCollisionBench_121, LogEntryInequality_121) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("cmd1");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("cmd2");
  BuildLog::LogEntry entry1("out.o", hash1, 10, 20, 30);
  BuildLog::LogEntry entry2("out.o", hash2, 10, 20, 30);
  EXPECT_FALSE(entry1 == entry2);
}

// Test hashing with special characters
TEST(HashCollisionBench_121, SpecialCharactersHash_121) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("gcc -DFOO=\"bar baz\"");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("gcc -DFOO=\"bar baz\"");
  EXPECT_EQ(hash1, hash2);

  uint64_t hash3 = BuildLog::LogEntry::HashCommand("gcc -DFOO=\"bar qux\"");
  EXPECT_NE(hash1, hash3);
}

// Test hashing with whitespace variations
TEST(HashCollisionBench_121, WhitespaceVariationsHash_121) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("gcc  -o foo.o");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("gcc -o foo.o");
  // Different whitespace should produce different hashes
  EXPECT_NE(hash1, hash2);
}

// Test that hash is non-zero for non-empty strings
TEST(HashCollisionBench_121, NonEmptyStringHashNonZero_121) {
  uint64_t hash = BuildLog::LogEntry::HashCommand("anything");
  EXPECT_NE(hash, 0u);
}
