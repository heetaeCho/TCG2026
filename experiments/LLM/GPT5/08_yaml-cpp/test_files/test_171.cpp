// File: ./TestProjects/yaml-cpp/test/queue_unicode_codepoint_test_171.cpp

#include <gtest/gtest.h>

#include <deque>
#include <limits>
#include <string>

#include "stream.h"

// Forward declaration (definition is provided by the yaml-cpp library/object files).
namespace YAML {
void QueueUnicodeCodepoint(std::deque<char>& q, unsigned long ch);
}  // namespace YAML

namespace {

class QueueUnicodeCodepointTest_171 : public ::testing::Test {
 protected:
  std::deque<char> q_;
};

TEST_F(QueueUnicodeCodepointTest_171, AsciiRangePushesOneByte_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x41UL);  // 'A'
  EXPECT_EQ(q_.size(), before + 1);
}

TEST_F(QueueUnicodeCodepointTest_171, TwoByteRangeLowerBoundaryPushesTwoBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x80UL);
  EXPECT_EQ(q_.size(), before + 2);
}

TEST_F(QueueUnicodeCodepointTest_171, TwoByteRangeUpperBoundaryPushesTwoBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x7FFUL);
  EXPECT_EQ(q_.size(), before + 2);
}

TEST_F(QueueUnicodeCodepointTest_171, ThreeByteRangeLowerBoundaryPushesThreeBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x800UL);
  EXPECT_EQ(q_.size(), before + 3);
}

TEST_F(QueueUnicodeCodepointTest_171, ThreeByteRangeUpperBoundaryPushesThreeBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0xFFFFUL);
  EXPECT_EQ(q_.size(), before + 3);
}

TEST_F(QueueUnicodeCodepointTest_171, FourByteRangeLowerBoundaryPushesFourBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x10000UL);
  EXPECT_EQ(q_.size(), before + 4);
}

TEST_F(QueueUnicodeCodepointTest_171, FourByteRangeTypicalMaxPushesFourBytes_171) {
  const size_t before = q_.size();
  YAML::QueueUnicodeCodepoint(q_, 0x10FFFFUL);
  EXPECT_EQ(q_.size(), before + 4);
}

TEST_F(QueueUnicodeCodepointTest_171, EofInputIsReplacedAndProducesThreeBytes_171) {
  const size_t before = q_.size();

  const unsigned long eof_as_ulong = static_cast<unsigned long>(YAML::Stream::eof());
  YAML::QueueUnicodeCodepoint(q_, eof_as_ulong);

  // Replacement character U+FFFD is in the 3-byte UTF-8 range.
  ASSERT_EQ(q_.size(), before + 3);

  // Stronger observable behavior: UTF-8 bytes for U+FFFD are EF BF BD.
  const unsigned char b0 = static_cast<unsigned char>(q_[before + 0]);
  const unsigned char b1 = static_cast<unsigned char>(q_[before + 1]);
  const unsigned char b2 = static_cast<unsigned char>(q_[before + 2]);
  EXPECT_EQ(b0, 0xEFu);
  EXPECT_EQ(b1, 0xBFu);
  EXPECT_EQ(b2, 0xBDu);
}

TEST_F(QueueUnicodeCodepointTest_171, AppendsToExistingContentWithoutChangingPrefix_171) {
  q_.push_back('x');
  q_.push_back('y');

  const std::string prefix_before(q_.begin(), q_.end());
  const size_t before = q_.size();

  YAML::QueueUnicodeCodepoint(q_, 0x24UL);  // '$' (ASCII)

  ASSERT_EQ(q_.size(), before + 1);
  const std::string prefix_after(q_.begin(), q_.begin() + static_cast<std::ptrdiff_t>(before));
  EXPECT_EQ(prefix_after, prefix_before);
}

TEST_F(QueueUnicodeCodepointTest_171, MultipleCallsAccumulateBytes_171) {
  const size_t before = q_.size();

  YAML::QueueUnicodeCodepoint(q_, 0x7FUL);     // 1 byte
  YAML::QueueUnicodeCodepoint(q_, 0x80UL);     // 2 bytes
  YAML::QueueUnicodeCodepoint(q_, 0x800UL);    // 3 bytes
  YAML::QueueUnicodeCodepoint(q_, 0x10000UL);  // 4 bytes

  EXPECT_EQ(q_.size(), before + (1u + 2u + 3u + 4u));
}

TEST_F(QueueUnicodeCodepointTest_171, VeryLargeCodepointDoesNotCrashAndPushesFourBytes_171) {
  const size_t before = q_.size();

  YAML::QueueUnicodeCodepoint(q_, std::numeric_limits<unsigned long>::max());

  // Observable behavior from the public interface: still appends 4 bytes for the "else" path.
  EXPECT_EQ(q_.size(), before + 4);
}

}  // namespace