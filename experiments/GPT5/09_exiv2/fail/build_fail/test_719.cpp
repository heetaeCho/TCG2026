// TEST_ID 719
// File: test_logmsg_719.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "exiv2/error.hpp"

namespace {

using Exiv2::LogMsg;

TEST(LogMsgTest_719, CopyOperationsAreDeleted_719) {
  static_assert(!std::is_copy_constructible<LogMsg>::value,
                "LogMsg must not be copy constructible");
  static_assert(!std::is_copy_assignable<LogMsg>::value,
                "LogMsg must not be copy assignable");
}

TEST(LogMsgTest_719, OsReturnsSameReferenceEachCall_719) {
  LogMsg msg(static_cast<LogMsg::Level>(0));

  std::ostringstream* p1 = &msg.os();
  std::ostringstream* p2 = &msg.os();

  EXPECT_EQ(p1, p2);
}

TEST(LogMsgTest_719, OsInitiallyEmpty_719) {
  LogMsg msg(static_cast<LogMsg::Level>(0));

  EXPECT_TRUE(msg.os().str().empty());
}

TEST(LogMsgTest_719, OsAppendsStreamedData_719) {
  LogMsg msg(static_cast<LogMsg::Level>(0));

  msg.os() << "hello";
  EXPECT_EQ(msg.os().str(), "hello");

  msg.os() << " " << 123;
  EXPECT_EQ(msg.os().str(), "hello 123");
}

TEST(LogMsgTest_719, OsCanBeClearedByResettingBuffer_719) {
  LogMsg msg(static_cast<LogMsg::Level>(0));

  msg.os() << "data";
  ASSERT_FALSE(msg.os().str().empty());

  msg.os().str(std::string{});
  msg.os().clear();  // clear any flags, should be safe on a standard stream

  EXPECT_TRUE(msg.os().str().empty());

  msg.os() << "again";
  EXPECT_EQ(msg.os().str(), "again");
}

TEST(LogMsgTest_719, OsHandlesLargeWritesBoundary_719) {
  LogMsg msg(static_cast<LogMsg::Level>(0));

  const std::string big(1024 * 1024, 'x');  // 1 MiB
  msg.os() << big;

  const std::string out = msg.os().str();
  EXPECT_EQ(out.size(), big.size());
  EXPECT_EQ(out.front(), 'x');
  EXPECT_EQ(out.back(), 'x');
}

}  // namespace