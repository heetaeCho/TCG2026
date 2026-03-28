#include "gtest/gtest.h"
#include "build_log.h"

using namespace std;

class LogEntryTest_117 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default-constructed LogEntry fields
TEST_F(LogEntryTest_117, DefaultConstructedFields_117) {
  BuildLog::LogEntry entry("output.o");
  EXPECT_EQ(entry.output, "output.o");
  EXPECT_EQ(entry.command_hash, 0u);
  EXPECT_EQ(entry.start_time, 0);
  EXPECT_EQ(entry.end_time, 0);
  EXPECT_EQ(entry.mtime, 0);
}

// Test: Full constructor sets all fields correctly
TEST_F(LogEntryTest_117, FullConstructorSetsFields_117) {
  BuildLog::LogEntry entry("foo.o", 12345u, 100, 200, 300);
  EXPECT_EQ(entry.output, "foo.o");
  EXPECT_EQ(entry.command_hash, 12345u);
  EXPECT_EQ(entry.start_time, 100);
  EXPECT_EQ(entry.end_time, 200);
  EXPECT_EQ(entry.mtime, 300);
}

// Test: Equality operator with identical entries
TEST_F(LogEntryTest_117, EqualityOperatorIdentical_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("foo.o", 42u, 10, 20, 30);
  EXPECT_TRUE(a == b);
}

// Test: Equality operator - different output
TEST_F(LogEntryTest_117, EqualityOperatorDifferentOutput_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("bar.o", 42u, 10, 20, 30);
  EXPECT_FALSE(a == b);
}

// Test: Equality operator - different command_hash
TEST_F(LogEntryTest_117, EqualityOperatorDifferentCommandHash_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("foo.o", 99u, 10, 20, 30);
  EXPECT_FALSE(a == b);
}

// Test: Equality operator - different start_time
TEST_F(LogEntryTest_117, EqualityOperatorDifferentStartTime_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("foo.o", 42u, 11, 20, 30);
  EXPECT_FALSE(a == b);
}

// Test: Equality operator - different end_time
TEST_F(LogEntryTest_117, EqualityOperatorDifferentEndTime_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("foo.o", 42u, 10, 21, 30);
  EXPECT_FALSE(a == b);
}

// Test: Equality operator - different mtime
TEST_F(LogEntryTest_117, EqualityOperatorDifferentMtime_117) {
  BuildLog::LogEntry a("foo.o", 42u, 10, 20, 30);
  BuildLog::LogEntry b("foo.o", 42u, 10, 20, 31);
  EXPECT_FALSE(a == b);
}

// Test: Equality operator - two default-constructed entries with same output
TEST_F(LogEntryTest_117, EqualityOperatorTwoDefaults_117) {
  BuildLog::LogEntry a("same.o");
  BuildLog::LogEntry b("same.o");
  EXPECT_TRUE(a == b);
}

// Test: Equality operator - two default-constructed entries with different output
TEST_F(LogEntryTest_117, EqualityOperatorTwoDefaultsDifferentOutput_117) {
  BuildLog::LogEntry a("a.o");
  BuildLog::LogEntry b("b.o");
  EXPECT_FALSE(a == b);
}

// Test: HashCommand returns consistent results for same command
TEST_F(LogEntryTest_117, HashCommandConsistent_117) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("gcc -c foo.c -o foo.o");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("gcc -c foo.c -o foo.o");
  EXPECT_EQ(hash1, hash2);
}

// Test: HashCommand returns different results for different commands
TEST_F(LogEntryTest_117, HashCommandDifferentCommands_117) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("gcc -c foo.c -o foo.o");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("gcc -c bar.c -o bar.o");
  EXPECT_NE(hash1, hash2);
}

// Test: HashCommand with empty string
TEST_F(LogEntryTest_117, HashCommandEmptyString_117) {
  uint64_t hash = BuildLog::LogEntry::HashCommand("");
  // Just ensure it doesn't crash and returns a value
  (void)hash;
}

// Test: HashCommand with single character
TEST_F(LogEntryTest_117, HashCommandSingleChar_117) {
  uint64_t hash1 = BuildLog::LogEntry::HashCommand("a");
  uint64_t hash2 = BuildLog::LogEntry::HashCommand("b");
  EXPECT_NE(hash1, hash2);
}

// Test: Equality operator reflexive property
TEST_F(LogEntryTest_117, EqualityOperatorReflexive_117) {
  BuildLog::LogEntry a("test.o", 100u, 1, 2, 3);
  EXPECT_TRUE(a == a);
}

// Test: Equality operator symmetric property
TEST_F(LogEntryTest_117, EqualityOperatorSymmetric_117) {
  BuildLog::LogEntry a("test.o", 100u, 1, 2, 3);
  BuildLog::LogEntry b("test.o", 100u, 1, 2, 3);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

// Test: Boundary - max uint64_t command_hash
TEST_F(LogEntryTest_117, BoundaryMaxCommandHash_117) {
  uint64_t maxHash = UINT64_MAX;
  BuildLog::LogEntry a("out.o", maxHash, 0, 0, 0);
  BuildLog::LogEntry b("out.o", maxHash, 0, 0, 0);
  EXPECT_TRUE(a == b);
  
  BuildLog::LogEntry c("out.o", maxHash - 1, 0, 0, 0);
  EXPECT_FALSE(a == c);
}

// Test: Boundary - zero values for all numeric fields
TEST_F(LogEntryTest_117, BoundaryAllZeroNumericFields_117) {
  BuildLog::LogEntry a("out.o", 0u, 0, 0, 0);
  BuildLog::LogEntry b("out.o", 0u, 0, 0, 0);
  EXPECT_TRUE(a == b);
}

// Test: Empty output string
TEST_F(LogEntryTest_117, EmptyOutputString_117) {
  BuildLog::LogEntry a("", 42u, 10, 20, 30);
  BuildLog::LogEntry b("", 42u, 10, 20, 30);
  EXPECT_TRUE(a == b);
}

// Test: Equality operator - all fields differ
TEST_F(LogEntryTest_117, EqualityOperatorAllFieldsDiffer_117) {
  BuildLog::LogEntry a("a.o", 1u, 1, 1, 1);
  BuildLog::LogEntry b("b.o", 2u, 2, 2, 2);
  EXPECT_FALSE(a == b);
}

// Test: HashCommand with very long string
TEST_F(LogEntryTest_117, HashCommandLongString_117) {
  std::string longCmd(10000, 'x');
  uint64_t hash1 = BuildLog::LogEntry::HashCommand(longCmd);
  uint64_t hash2 = BuildLog::LogEntry::HashCommand(longCmd);
  EXPECT_EQ(hash1, hash2);
}

// Test: Negative time values (if meaningful)
TEST_F(LogEntryTest_117, NegativeTimeValues_117) {
  BuildLog::LogEntry a("out.o", 1u, -1, -2, -3);
  BuildLog::LogEntry b("out.o", 1u, -1, -2, -3);
  EXPECT_TRUE(a == b);
  
  BuildLog::LogEntry c("out.o", 1u, -1, -2, -4);
  EXPECT_FALSE(a == c);
}
