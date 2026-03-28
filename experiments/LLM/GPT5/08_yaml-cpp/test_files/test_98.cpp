// TEST_ID: 98
#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>

#include "stream.h"
#include "streamcharsource.h"

namespace {

using YAML::Stream;
using YAML::StreamCharSource;

class StreamCharSourceTest_98 : public ::testing::Test {};

TEST_F(StreamCharSourceTest_98, TypeTraits_CopyableNotAssignable_98) {
  static_assert(std::is_copy_constructible<StreamCharSource>::value,
                "StreamCharSource should be copy constructible");
  static_assert(std::is_move_constructible<StreamCharSource>::value,
                "StreamCharSource should be move constructible");
  static_assert(!std::is_copy_assignable<StreamCharSource>::value,
                "StreamCharSource copy assignment should be deleted");
  static_assert(!std::is_move_assignable<StreamCharSource>::value,
                "StreamCharSource move assignment should be deleted");
}

TEST_F(StreamCharSourceTest_98, IndexingReturnsCharactersFromUnderlyingStream_98) {
  std::stringstream ss;
  ss << "abcXYZ";

  Stream stream(ss);
  StreamCharSource src(stream);

  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');
  EXPECT_EQ(src[2], 'c');
  EXPECT_EQ(src[3], 'X');
  EXPECT_EQ(src[4], 'Y');
  EXPECT_EQ(src[5], 'Z');
}

TEST_F(StreamCharSourceTest_98, IndexingAtBoundary_LastCharacter_98) {
  std::stringstream ss;
  ss << "hello";

  Stream stream(ss);
  StreamCharSource src(stream);

  EXPECT_EQ(src[4], 'o');  // last valid character in "hello"
}

TEST_F(StreamCharSourceTest_98, OperatorPlusShiftsOffsetWithoutMutatingOriginal_98) {
  std::stringstream ss;
  ss << "abcdef";

  Stream stream(ss);
  StreamCharSource src(stream);

  const auto src_plus_1 = src + 1;
  const auto src_plus_3 = src + 3;

  // Original remains unchanged (observable via indexing)
  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');

  // Shifted sources read starting from the new offset
  EXPECT_EQ(src_plus_1[0], 'b');
  EXPECT_EQ(src_plus_1[1], 'c');

  EXPECT_EQ(src_plus_3[0], 'd');
  EXPECT_EQ(src_plus_3[1], 'e');
}

TEST_F(StreamCharSourceTest_98, CopyConstructorPreservesOffsetAndStreamReference_98) {
  std::stringstream ss;
  ss << "0123456789";

  Stream stream(ss);
  StreamCharSource src(stream);

  const auto advanced = src + 4;
  StreamCharSource copied(advanced);

  EXPECT_EQ(advanced[0], '4');
  EXPECT_EQ(copied[0], '4');

  EXPECT_EQ(advanced[3], '7');
  EXPECT_EQ(copied[3], '7');
}

TEST_F(StreamCharSourceTest_98, BoolAndNotAreConsistentOnNonEmptyAndEmptyStreams_98) {
  {
    std::stringstream ss;
    ss << "x";
    Stream stream(ss);
    StreamCharSource src(stream);

    const bool b = static_cast<bool>(src);
    EXPECT_EQ(!b, static_cast<bool>(!src));
  }
  {
    std::stringstream ss;  // empty
    Stream stream(ss);
    StreamCharSource src(stream);

    const bool b = static_cast<bool>(src);
    EXPECT_EQ(!b, static_cast<bool>(!src));
  }
}

TEST_F(StreamCharSourceTest_98, IndexingFarPastEndDoesNotThrow_98) {
  std::stringstream ss;
  ss << "short";

  Stream stream(ss);
  StreamCharSource src(stream);

  EXPECT_NO_THROW({
    volatile char c = src[1000];  // volatile to ensure it is actually evaluated
    (void)c;
  });
}

}  // namespace
