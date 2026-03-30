// File: ./TestProjects/re2/re2/testing/prefilter_info_quest_test.cc

#include "gtest/gtest.h"
#include "re2/prefilter.h"   // Assumes Info is available via this or a transitive include
// If Info lives in another header in your tree, include that instead.

namespace re2 {

class PrefilterInfoQuestTest_547 : public ::testing::Test {};

// Normal operation: non-null input
TEST_F(PrefilterInfoQuestTest_547, Quest_FromNonNullInput_ReturnsNonExact_WithMatch_547) {
  // Arrange: create some Info via a public factory (treat as black box).
  // Using EmptyString() to obtain a valid Info instance; any other public factory would also be fine.
  Prefilter::Info* seed = Prefilter::Info::EmptyString();
  ASSERT_NE(seed, nullptr);

  // Act
  Prefilter::Info* out = Prefilter::Info::Quest(seed);

  // Assert: returned object exists
  ASSERT_NE(out, nullptr);

  // Assert: observable state via public API — Quest should not be exact per interface exposure
  EXPECT_FALSE(out->is_exact());

  // Assert: a match object exists and is retrievable via public API
  Prefilter* m = out->TakeMatch();
  EXPECT_NE(m, nullptr);

  // Clean up (ownership per interface: TakeMatch returns a Prefilter*, Info* is heap-allocated by factory/Quest)
  delete m;
  delete out;

  // Note: We do not dereference or otherwise use 'seed' after passing to Quest,
  // and we do not assume anything about its lifetime beyond the interface.
}

// Boundary condition: null input pointer
TEST_F(PrefilterInfoQuestTest_547, Quest_FromNullInput_ReturnsNonExact_WithMatch_547) {
  // Act: Pass nullptr (allowed in C++; deletion of nullptr is a no-op)
  Prefilter::Info* out = Prefilter::Info::Quest(nullptr);

  // Assert
  ASSERT_NE(out, nullptr);
  EXPECT_FALSE(out->is_exact());

  Prefilter* m = out->TakeMatch();
  EXPECT_NE(m, nullptr);

  // Clean up
  delete m;
  delete out;
}

}  // namespace re2
