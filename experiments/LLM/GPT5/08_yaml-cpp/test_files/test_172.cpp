// TEST_ID: 172
#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>
#include <memory>
#include <vector>

#include "stream.h"  // ./TestProjects/yaml-cpp/src/stream.h

namespace {

class StreamDestructorTest_172 : public ::testing::Test {};

TEST_F(StreamDestructorTest_172, HeapAllocatedStreamDeletesWithoutCrash_172) {
  std::istringstream input("abc");
  auto* s = new YAML::Stream(input);
  EXPECT_NO_THROW(delete s);
}

TEST_F(StreamDestructorTest_172, StackAllocatedStreamGoesOutOfScopeWithoutCrash_172) {
  std::istringstream input("abc");
  EXPECT_NO_THROW({
    YAML::Stream s(input);
    (void)s;
  });
}

TEST_F(StreamDestructorTest_172, MultipleStreamsDestroyIndependently_172) {
  std::istringstream input1("first");
  std::istringstream input2("second");
  std::istringstream input3("");

  auto s1 = std::make_unique<YAML::Stream>(input1);
  auto s2 = std::make_unique<YAML::Stream>(input2);
  auto s3 = std::make_unique<YAML::Stream>(input3);

  // Reset in non-creation order to exercise independent destruction.
  EXPECT_NO_THROW(s2.reset());
  EXPECT_NO_THROW(s1.reset());
  EXPECT_NO_THROW(s3.reset());
}

TEST_F(StreamDestructorTest_172, CopyAndMoveAreDeleted_172) {
  static_assert(!std::is_copy_constructible_v<YAML::Stream>,
                "Stream should not be copy constructible");
  static_assert(!std::is_copy_assignable_v<YAML::Stream>,
                "Stream should not be copy assignable");
  static_assert(!std::is_move_constructible_v<YAML::Stream>,
                "Stream should not be move constructible");
  static_assert(!std::is_move_assignable_v<YAML::Stream>,
                "Stream should not be move assignable");
  SUCCEED();
}

}  // namespace