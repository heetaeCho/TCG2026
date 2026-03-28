// File: ./TestProjects/ninja/tests/hash_collision_bench_test_120.cc

#include <gtest/gtest.h>
#include <cstring>

// Forward declaration of the function under test.
// The real implementation lives in ./src/hash_collision_bench.cc.
void RandomCommand(char** s);

class RandomCommandTest_120 : public ::testing::Test {};

// Verifies that RandomCommand allocates a non-null, null-terminated C-string
// and that its length is within the expected bounds [5, 100].
TEST_F(RandomCommandTest_120, GeneratesNonEmptyStringWithReasonableLength_120) {
  char* cmd = nullptr;

  RandomCommand(&cmd);

  ASSERT_NE(cmd, nullptr) << "RandomCommand should allocate a non-null string";

  // Verify that the string is null-terminated by using strlen.
  size_t len = std::strlen(cmd);
  EXPECT_GE(len, 5u) << "Generated string should have length >= 5";
  EXPECT_LE(len, 100u) << "Generated string should have length <= 100";

  delete[] cmd;
}

// Verifies that all characters in the generated string are printable ASCII
// (based on the implementation, characters are in the range [32, 126]).
TEST_F(RandomCommandTest_120, GeneratedCharactersArePrintableAscii_120) {
  char* cmd = nullptr;

  RandomCommand(&cmd);
  ASSERT_NE(cmd, nullptr);

  for (size_t i = 0; cmd[i] != '\0'; ++i) {
    unsigned char c = static_cast<unsigned char>(cmd[i]);
    EXPECT_GE(c, 32u) << "Character at index " << i << " is below printable range";
    EXPECT_LE(c, 126u) << "Character at index " << i << " is above printable range";
  }

  delete[] cmd;
}

// Verifies that multiple calls to RandomCommand allocate independent buffers
// (different pointers) and both results are valid C-strings.
TEST_F(RandomCommandTest_120, MultipleCallsAllocateDistinctBuffers_120) {
  char* cmd1 = nullptr;
  char* cmd2 = nullptr;

  RandomCommand(&cmd1);
  RandomCommand(&cmd2);

  ASSERT_NE(cmd1, nullptr);
  ASSERT_NE(cmd2, nullptr);

  // The two buffers should be distinct while both are alive.
  EXPECT_NE(cmd1, cmd2) << "RandomCommand should allocate distinct buffers for each call";

  // Also sanity-check that both are null-terminated strings.
  EXPECT_GT(std::strlen(cmd1), 0u);
  EXPECT_GT(std::strlen(cmd2), 0u);

  delete[] cmd1;
  delete[] cmd2;
}

// Verifies that RandomCommand correctly overwrites an existing pointer value
// (e.g., caller passes a non-null pointer) and still returns a valid allocation.
TEST_F(RandomCommandTest_120, OverwritesExistingPointerWithNewAllocation_120) {
  char buffer[16] = "initial";
  char* cmd = buffer;  // Non-null initial pointer.

  RandomCommand(&cmd);

  // The pointer should now point to a new heap allocation, not the original buffer.
  EXPECT_NE(static_cast<void*>(cmd),
            static_cast<void*>(buffer))
      << "RandomCommand should overwrite the provided pointer with a new allocation";
  ASSERT_NE(cmd, nullptr);

  // Verify it's a proper C-string with a reasonable length.
  size_t len = std::strlen(cmd);
  EXPECT_GE(len, 5u);
  EXPECT_LE(len, 100u);

  delete[] cmd;
}
