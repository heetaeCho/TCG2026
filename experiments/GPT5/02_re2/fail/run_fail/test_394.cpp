#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

// Test fixture for Prog::Inst InitMatch
class ProgInstTest_394 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Normal operation: InitMatch sets opcode to kInstMatch and stores match_id
TEST_F(ProgInstTest_394, InitMatch_SetsOpcodeAndId_394) {
  int test_id = 42;

  inst_.InitMatch(test_id);

  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), test_id);
}

// Boundary condition: InitMatch with zero ID
TEST_F(ProgInstTest_394, InitMatch_WithZeroId_394) {
  int test_id = 0;

  inst_.InitMatch(test_id);

  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Boundary condition: InitMatch with negative ID
TEST_F(ProgInstTest_394, InitMatch_WithNegativeId_394) {
  int test_id = -1;

  inst_.InitMatch(test_id);

  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), -1);
}

// Boundary condition: InitMatch with large positive ID
TEST_F(ProgInstTest_394, InitMatch_WithLargeId_394) {
  int test_id = std::numeric_limits<int>::max();

  inst_.InitMatch(test_id);

  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), test_id);
}

// Exceptional case: calling InitMatch twice should overwrite previous value
TEST_F(ProgInstTest_394, InitMatch_CalledTwice_394) {
  inst_.InitMatch(100);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 100);

  inst_.InitMatch(200);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 200);
}

}  // namespace re2
