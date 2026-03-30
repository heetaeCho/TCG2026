// TEST_ID: 28
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperColTest_28 : public ::testing::Test {
protected:
  std::ostringstream oss;
};

TEST_F(OstreamWrapperColTest_28, DefaultConstructor_ColStartsAtZero_28) {
  YAML::ostream_wrapper w;
  EXPECT_EQ(0u, w.col());
}

TEST_F(OstreamWrapperColTest_28, StreamConstructor_ColStartsAtZero_28) {
  YAML::ostream_wrapper w(oss);
  EXPECT_EQ(0u, w.col());
}

TEST_F(OstreamWrapperColTest_28, ColIsConstAndReturnsSizeT_28) {
  static_assert(std::is_same_v<decltype(std::declval<const YAML::ostream_wrapper&>().col()),
                               std::size_t>,
                "col() must return std::size_t");
  const YAML::ostream_wrapper w;
  EXPECT_NO_THROW((void)w.col());
}

TEST_F(OstreamWrapperColTest_28, ColRepeatedCallsAreStableWithoutMutation_28) {
  YAML::ostream_wrapper w(oss);

  const std::size_t c1 = w.col();
  const std::size_t c2 = w.col();
  const std::size_t c3 = w.col();

  EXPECT_EQ(c1, c2);
  EXPECT_EQ(c2, c3);
}

TEST_F(OstreamWrapperColTest_28, EmptyWritesDoNotCrashAndDoNotChangeInitialCol_28) {
  YAML::ostream_wrapper w(oss);

  const std::size_t before = w.col();

  EXPECT_NO_THROW(w.write(std::string()));
  EXPECT_EQ(before, w.col());

  // Boundary: nullptr with size 0 should be safe to pass for "write(ptr, size)" style APIs.
  EXPECT_NO_THROW(w.write(static_cast<const char*>(nullptr), 0u));
  EXPECT_EQ(before, w.col());

  EXPECT_NO_THROW(w.write("", 0u));
  EXPECT_EQ(before, w.col());
}

TEST_F(OstreamWrapperColTest_28, LargeWriteDoesNotCrashAndColStaysWithinReasonableBound_28) {
  YAML::ostream_wrapper w(oss);

  // Large input boundary (but still reasonable for a unit test)
  std::string big(1u << 20, 'a');  // 1 MiB
  EXPECT_NO_THROW(w.write(big));

  // Observable, non-invasive sanity checks:
  // - col() is a size_t and must be representable
  // - it should not exceed the number of characters written in this single call
  EXPECT_LE(w.col(), big.size());
}

}  // namespace
