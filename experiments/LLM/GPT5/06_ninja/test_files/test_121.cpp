// File: hash_collision_bench_test.cc

#include "gtest/gtest.h"

#include "build_log.h"      // BuildLog::LogEntry, HashCommand
#include "string_piece.h"   // StringPiece

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

using std::string;
using std::vector;

class HashCollisionBenchTest_121 : public ::testing::Test {
protected:
  // Helper that calls the hash function as the benchmark does,
  // but with deterministic inputs rather than RandomCommand.
  uint64_t HashOf(const string& command) {
    return BuildLog::LogEntry::HashCommand(StringPiece(command));
  }
};

// Normal operation: same command string → same hash value on each call.
TEST_F(HashCollisionBenchTest_121, SameString_YieldsIdenticalHash_121) {
  const string command = "gcc -c foo.cc -o foo.o";

  uint64_t hash1 = HashOf(command);
  uint64_t hash2 = HashOf(command);
  uint64_t hash3 = HashOf(command);

  EXPECT_EQ(hash1, hash2);
  EXPECT_EQ(hash2, hash3);
}

// Boundary case: empty command string should be handled deterministically
// (no crash, and repeated calls give the same hash).
TEST_F(HashCollisionBenchTest_121, EmptyString_YieldsDeterministicHash_121) {
  const string empty_cmd = "";

  uint64_t hash1 = HashOf(empty_cmd);
  uint64_t hash2 = HashOf(empty_cmd);

  EXPECT_EQ(hash1, hash2);
}

// Normal operation: hashing several different strings should not devolve
// into a constant hash function. We do NOT assume “no collisions”; we only
// assert that not all hashes are identical.
TEST_F(HashCollisionBenchTest_121, DifferentStrings_NotAllHashesEqual_121) {
  const string cmd1 = "gcc -c a.cc -o a.o";
  const string cmd2 = "gcc -c b.cc -o b.o";
  const string cmd3 = "clang -c a.cc -o a.o";

  uint64_t h1 = HashOf(cmd1);
  uint64_t h2 = HashOf(cmd2);
  uint64_t h3 = HashOf(cmd3);

  // At least one pair of hashes should differ.
  bool all_equal = (h1 == h2) && (h2 == h3);
  EXPECT_FALSE(all_equal);
}

// Boundary-ish: long command string (many characters). We only assert that
// hashing is stable (same string → same hash), not any particular value.
TEST_F(HashCollisionBenchTest_121, LongString_HashIsStable_121) {
  // Construct a long artificial command.
  string long_cmd = "clang++ -O2 -Wall -Wextra ";
  for (int i = 0; i < 1000; ++i) {
    long_cmd += "-DDEFINE_" + std::to_string(i) + " ";
  }
  long_cmd += "main.cc -o main.out";

  uint64_t hash1 = HashOf(long_cmd);
  uint64_t hash2 = HashOf(long_cmd);

  EXPECT_EQ(hash1, hash2);
}

// Behavior similar to the benchmark: many deterministic commands, hashing
// them twice and confirming that each individual command’s hash is stable.
// This mirrors how hash_collision_bench uses HashCommand across a large N.
TEST_F(HashCollisionBenchTest_121, ManyCommands_HashIsStableForEach_121) {
  const int N = 1000;  // much smaller than the 20M used in hash_collision_bench
  vector<string> commands;
  commands.reserve(N);

  for (int i = 0; i < N; ++i) {
    commands.push_back("cmd_" + std::to_string(i) + " -flag " +
                       std::to_string(i % 10));
  }

  vector<uint64_t> first_hashes;
  first_hashes.reserve(N);

  // First pass: compute and store hashes.
  for (const auto& cmd : commands) {
    first_hashes.push_back(HashOf(cmd));
  }

  // Second pass: hashes for the same commands should match the first pass.
  for (int i = 0; i < N; ++i) {
    uint64_t h = HashOf(commands[i]);
    EXPECT_EQ(h, first_hashes[i]) << "Hash changed for command index " << i;
  }
}
