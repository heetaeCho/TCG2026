#include "graph.h"

#include <limits>
#include <string>

#include "gtest/gtest.h"

namespace {

class NodeMTimeTest_38 : public ::testing::Test {
 protected:
  NodeMTimeTest_38() : node_("out.o", 0u) {}

  Node node_;
};

// Verifies that a newly constructed Node has an "unknown" mtime (sentinel).
TEST_F(NodeMTimeTest_38, DefaultMtimeIsUnknown_38) {
  // From the public header, the default is initialized to -1 (unknown).
  EXPECT_EQ(static_cast<TimeStamp>(-1), node_.mtime());
}

// Verifies that UpdatePhonyMtime sets the value returned by mtime().
TEST_F(NodeMTimeTest_38, UpdatePhonyMtimeSetsMtime_38) {
  const TimeStamp kStamp = static_cast<TimeStamp>(123456);

  node_.UpdatePhonyMtime(kStamp);

  EXPECT_EQ(kStamp, node_.mtime());
}

// Verifies that multiple calls to UpdatePhonyMtime keep the last value.
TEST_F(NodeMTimeTest_38, MultipleUpdatesKeepLastValue_38) {
  const TimeStamp kFirst = static_cast<TimeStamp>(111);
  const TimeStamp kSecond = static_cast<TimeStamp>(222);

  node_.UpdatePhonyMtime(kFirst);
  EXPECT_EQ(kFirst, node_.mtime());

  node_.UpdatePhonyMtime(kSecond);
  EXPECT_EQ(kSecond, node_.mtime());
}

// Verifies boundary values (0 and the maximum representable TimeStamp).
TEST_F(NodeMTimeTest_38, HandlesBoundaryTimestamps_38) {
  const TimeStamp kZero = static_cast<TimeStamp>(0);
  const TimeStamp kMax = std::numeric_limits<TimeStamp>::max();

  node_.UpdatePhonyMtime(kZero);
  EXPECT_EQ(kZero, node_.mtime());

  node_.UpdatePhonyMtime(kMax);
  EXPECT_EQ(kMax, node_.mtime());
}

// Verifies that ResetState restores the "unknown" mtime sentinel.
TEST_F(NodeMTimeTest_38, ResetStateResetsMtimeToUnknown_38) {
  node_.UpdatePhonyMtime(static_cast<TimeStamp>(42));
  ASSERT_NE(static_cast<TimeStamp>(-1), node_.mtime());

  node_.ResetState();

  EXPECT_EQ(static_cast<TimeStamp>(-1), node_.mtime());
}

}  // namespace
