#include <string>
#include <cstdint>

#include "gtest/gtest.h"
#include "build_log.h"
// If needed in your project, you may also need:
// #include "string_piece.h"
// #include "timestamp.h"

using std::string;

class BuildLogLogEntryTest_117 : public ::testing::Test {
protected:
  // Helper to create a fully-initialized LogEntry in a consistent way.
  BuildLog::LogEntry MakeEntry(const string& output,
                               uint64_t command_hash,
                               int start_time,
                               int end_time,
                               TimeStamp mtime) {
    return BuildLog::LogEntry(output, command_hash, start_time, end_time, mtime);
  }
};

//------------------------------------------------------------------------------
// Constructor behavior
//------------------------------------------------------------------------------

TEST_F(BuildLogLogEntryTest_117,
       ExplicitOutputConstructorInitializesOutputAndZeroesOthers_117) {
  const string kOutput = "out/file.o";

  BuildLog::LogEntry entry(kOutput);

  EXPECT_EQ(kOutput, entry.output);
  EXPECT_EQ(static_cast<uint64_t>(0), entry.command_hash);
  EXPECT_EQ(0, entry.start_time);
  EXPECT_EQ(0, entry.end_time);
  EXPECT_EQ(static_cast<TimeStamp>(0), entry.mtime);
}

TEST_F(BuildLogLogEntryTest_117,
       FullConstructorInitializesAllFields_117) {
  const string kOutput = "bin/prog";
  const uint64_t kHash = 0x12345678u;
  const int kStart = 10;
  const int kEnd = 20;
  const TimeStamp kMtime = static_cast<TimeStamp>(12345);

  BuildLog::LogEntry entry(kOutput, kHash, kStart, kEnd, kMtime);

  EXPECT_EQ(kOutput, entry.output);
  EXPECT_EQ(kHash, entry.command_hash);
  EXPECT_EQ(kStart, entry.start_time);
  EXPECT_EQ(kEnd, entry.end_time);
  EXPECT_EQ(kMtime, entry.mtime);
}

//------------------------------------------------------------------------------
// operator== : normal operation and basic properties
//------------------------------------------------------------------------------

TEST_F(BuildLogLogEntryTest_117,
       EqualityAllFieldsEqual_117) {
  BuildLog::LogEntry a("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);  // symmetry check as part of normal equality
}

TEST_F(BuildLogLogEntryTest_117,
       SelfEquality_117) {
  BuildLog::LogEntry a("self.o", 42u, 5, 15, static_cast<TimeStamp>(100));

  EXPECT_TRUE(a == a);
}

TEST_F(BuildLogLogEntryTest_117,
       EqualityIsSymmetricAndTransitive_117) {
  BuildLog::LogEntry a("same.o", 7u, 1, 2, static_cast<TimeStamp>(3));
  BuildLog::LogEntry b("same.o", 7u, 1, 2, static_cast<TimeStamp>(3));
  BuildLog::LogEntry c("same.o", 7u, 1, 2, static_cast<TimeStamp>(3));

  // symmetry
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);

  // transitivity
  EXPECT_TRUE(b == c);
  EXPECT_TRUE(a == c);
}

//------------------------------------------------------------------------------
// operator== : boundary / difference in each individual field
//------------------------------------------------------------------------------

TEST_F(BuildLogLogEntryTest_117,
       InequalityWhenOutputDiffers_117) {
  BuildLog::LogEntry a("a.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("b.o", 1u, 10, 20, static_cast<TimeStamp>(30));

  EXPECT_FALSE(a == b);
}

TEST_F(BuildLogLogEntryTest_117,
       InequalityWhenCommandHashDiffers_117) {
  BuildLog::LogEntry a("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("out.o", 2u, 10, 20, static_cast<TimeStamp>(30));

  EXPECT_FALSE(a == b);
}

TEST_F(BuildLogLogEntryTest_117,
       InequalityWhenStartTimeDiffers_117) {
  BuildLog::LogEntry a("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("out.o", 1u, 11, 20, static_cast<TimeStamp>(30));

  EXPECT_FALSE(a == b);
}

TEST_F(BuildLogLogEntryTest_117,
       InequalityWhenEndTimeDiffers_117) {
  BuildLog::LogEntry a("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("out.o", 1u, 10, 21, static_cast<TimeStamp>(30));

  EXPECT_FALSE(a == b);
}

TEST_F(BuildLogLogEntryTest_117,
       InequalityWhenMtimeDiffers_117) {
  BuildLog::LogEntry a("out.o", 1u, 10, 20, static_cast<TimeStamp>(30));
  BuildLog::LogEntry b("out.o", 1u, 10, 20, static_cast<TimeStamp>(31));

  EXPECT_FALSE(a == b);
}

//------------------------------------------------------------------------------
// HashCommand : observable, black-box properties
//------------------------------------------------------------------------------

TEST_F(BuildLogLogEntryTest_117,
       HashCommandDeterministicForSameInput_117) {
  const string cmd = "cc -c main.cc -o main.o";
  StringPiece cmd_piece(cmd);

  uint64_t h1 = BuildLog::LogEntry::HashCommand(cmd_piece);
  uint64_t h2 = BuildLog::LogEntry::HashCommand(cmd_piece);

  // Same input must always produce the same hash.
  EXPECT_EQ(h1, h2);
}

TEST_F(BuildLogLogEntryTest_117,
       HashCommandHandlesEmptyCommand_117) {
  StringPiece empty_cmd;  // default-constructed / empty

  uint64_t h1 = BuildLog::LogEntry::HashCommand(empty_cmd);
  uint64_t h2 = BuildLog::LogEntry::HashCommand(empty_cmd);

  // Empty command should be handled consistently and deterministically.
  EXPECT_EQ(h1, h2);
}
