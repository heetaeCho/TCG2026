// TEST_ID: 91
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace {

class DeepRecursionTest_91 : public ::testing::Test {};

TEST_F(DeepRecursionTest_91, DepthReturnsConstructorDepth_91) {
  const YAML::Mark mark;
  const std::string msg = "too deep";

  YAML::DeepRecursion ex(7, mark, msg);
  EXPECT_EQ(ex.depth(), 7);
}

TEST_F(DeepRecursionTest_91, DepthWorksOnConstObject_91) {
  const YAML::Mark mark;
  const std::string msg = "const";

  const YAML::DeepRecursion ex(3, mark, msg);
  EXPECT_NO_THROW({
    const int d = ex.depth();
    (void)d;
  });
  EXPECT_EQ(ex.depth(), 3);
}

TEST_F(DeepRecursionTest_91, DepthHandlesZeroDepth_91) {
  const YAML::Mark mark;
  const std::string msg = "zero";

  YAML::DeepRecursion ex(0, mark, msg);
  EXPECT_EQ(ex.depth(), 0);
}

TEST_F(DeepRecursionTest_91, DepthHandlesNegativeDepth_91) {
  const YAML::Mark mark;
  const std::string msg = "negative";

  YAML::DeepRecursion ex(-1, mark, msg);
  EXPECT_EQ(ex.depth(), -1);
}

TEST_F(DeepRecursionTest_91, DepthHandlesLargeDepth_91) {
  const YAML::Mark mark;
  const std::string msg = "large";

  const int large = std::numeric_limits<int>::max();
  YAML::DeepRecursion ex(large, mark, msg);
  EXPECT_EQ(ex.depth(), large);
}

TEST_F(DeepRecursionTest_91, DepthPreservedAfterCopy_91) {
  const YAML::Mark mark;
  const std::string msg = "copy";

  YAML::DeepRecursion original(42, mark, msg);
  YAML::DeepRecursion copied = original;

  EXPECT_EQ(original.depth(), 42);
  EXPECT_EQ(copied.depth(), 42);
}

TEST_F(DeepRecursionTest_91, DepthPreservedAfterMove_91) {
  const YAML::Mark mark;
  const std::string msg = "move";

  YAML::DeepRecursion original(99, mark, msg);
  YAML::DeepRecursion moved = std::move(original);

  // Only assert what is observable through the public interface of the moved-to object.
  EXPECT_EQ(moved.depth(), 99);
}

}  // namespace
