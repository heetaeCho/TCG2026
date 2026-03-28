// InMemoryFile_test_2636.cpp
#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/InMemoryFile.h"

namespace {

class InMemoryFileTest_2636 : public ::testing::Test {
protected:
  InMemoryFile file;
};

TEST_F(InMemoryFileTest_2636, GetBufferReturnsSameReferenceAcrossCalls_2636) {
  const std::vector<char> &buf1 = file.getBuffer();
  const std::vector<char> &buf2 = file.getBuffer();

  // Same underlying object (reference stability)
  EXPECT_EQ(&buf1, &buf2);
}

TEST_F(InMemoryFileTest_2636, GetBufferWorksOnConstObject_2636) {
  const InMemoryFile constFile;
  const std::vector<char> &buf = constFile.getBuffer();

  // Basic observable property: size is well-defined and non-negative.
  EXPECT_GE(buf.size(), static_cast<size_t>(0));
}

TEST_F(InMemoryFileTest_2636, NewlyConstructedBufferIsEmpty_2636) {
  // Boundary/initial-state expectation: a fresh in-memory file has no data.
  // If the implementation changes to pre-seed content, this test will catch it.
  const std::vector<char> &buf = file.getBuffer();
  EXPECT_TRUE(buf.empty());
}

TEST_F(InMemoryFileTest_2636, DifferentInstancesReturnDifferentBufferObjects_2636) {
  InMemoryFile other;
  const std::vector<char> &buf1 = file.getBuffer();
  const std::vector<char> &buf2 = other.getBuffer();

  // Each instance should expose its own buffer (no shared storage).
  EXPECT_NE(&buf1, &buf2);
}

}  // namespace