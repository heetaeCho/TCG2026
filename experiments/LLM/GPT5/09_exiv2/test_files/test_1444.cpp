// File: test_olympus2_mnheader_baseoffset_1444.cpp
// The TEST_ID is 1444

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

// Include the public interface (as used by the codebase).
#include "makernote_int.hpp"

namespace {

class Olympus2MnHeaderTest_1444 : public ::testing::Test {
protected:
  Exiv2::Internal::Olympus2MnHeader header_;
};

TEST_F(Olympus2MnHeaderTest_1444, BaseOffset_ReturnsInputForZero_1444) {
  const size_t mnOffset = 0u;
  EXPECT_EQ(header_.baseOffset(mnOffset), mnOffset);
}

TEST_F(Olympus2MnHeaderTest_1444, BaseOffset_ReturnsInputForSmallValues_1444) {
  EXPECT_EQ(header_.baseOffset(1u), 1u);
  EXPECT_EQ(header_.baseOffset(2u), 2u);
  EXPECT_EQ(header_.baseOffset(42u), 42u);
  EXPECT_EQ(header_.baseOffset(1024u), 1024u);
}

TEST_F(Olympus2MnHeaderTest_1444, BaseOffset_ReturnsInputForLargeValue_1444) {
  const size_t mnOffset = static_cast<size_t>(1) << (sizeof(size_t) * 8 - 2);
  EXPECT_EQ(header_.baseOffset(mnOffset), mnOffset);
}

TEST_F(Olympus2MnHeaderTest_1444, BaseOffset_ReturnsInputForMaxSizeT_1444) {
  const size_t mnOffset = std::numeric_limits<size_t>::max();
  EXPECT_EQ(header_.baseOffset(mnOffset), mnOffset);
}

}  // namespace