// TEST_ID: 107
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "poppler/Object.h"

class ObjectGetCmdTest_107 : public ::testing::Test {};

// Normal operation: objCmd created with a C-string exposes the same command via getCmd().
TEST_F(ObjectGetCmdTest_107, ReturnsCommandStringForCmdObject_107) {
  Object obj(objCmd, "q");

  const char *cmd = obj.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_STREQ(cmd, "q");
}

// Normal operation: empty command should round-trip as an empty C-string.
TEST_F(ObjectGetCmdTest_107, ReturnsEmptyStringWhenCmdIsEmpty_107) {
  Object obj(objCmd, "");

  const char *cmd = obj.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_STREQ(cmd, "");
}

// Boundary-ish: longer command string round-trips.
TEST_F(ObjectGetCmdTest_107, ReturnsLongCommandString_107) {
  const std::string longCmd(4096, 'x');
  Object obj(objCmd, longCmd.c_str());

  const char *cmd = obj.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_EQ(std::strlen(cmd), longCmd.size());
  EXPECT_STREQ(cmd, longCmd.c_str());
}

// Observable behavior: repeated calls should be consistent.
TEST_F(ObjectGetCmdTest_107, RepeatedCallsReturnConsistentResult_107) {
  Object obj(objCmd, "BT");

  const char *cmd1 = obj.getCmd();
  const char *cmd2 = obj.getCmd();

  ASSERT_NE(cmd1, nullptr);
  ASSERT_NE(cmd2, nullptr);
  EXPECT_STREQ(cmd1, "BT");
  EXPECT_STREQ(cmd2, "BT");

  // Pointer stability is an observable property; if implementation changes, this may fail,
  // but it can still catch regressions where the returned pointer becomes dangling.
  EXPECT_EQ(cmd1, cmd2);
}

// Move behavior: moved-to object should preserve observable command behavior.
TEST_F(ObjectGetCmdTest_107, MoveConstructedCmdObjectKeepsCommand_107) {
  Object src(objCmd, "ET");
  Object dst(std::move(src));

  const char *cmd = dst.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_STREQ(cmd, "ET");
}

#if GTEST_HAS_DEATH_TEST
// Error/exceptional (observable): calling getCmd() on a non-cmd Object should fail the type check.
// We do not assume the exact failure mechanism beyond "it terminates the process".
TEST_F(ObjectGetCmdTest_107, DeathWhenCalledOnNullObject_107) {
  Object obj = Object::null();
  ASSERT_DEATH({ (void)obj.getCmd(); }, "");
}

TEST_F(ObjectGetCmdTest_107, DeathWhenCalledOnErrorObject_107) {
  Object obj = Object::error();
  ASSERT_DEATH({ (void)obj.getCmd(); }, "");
}

TEST_F(ObjectGetCmdTest_107, DeathWhenCalledOnEOFObject_107) {
  Object obj = Object::eof();
  ASSERT_DEATH({ (void)obj.getCmd(); }, "");
}

TEST_F(ObjectGetCmdTest_107, DeathWhenCalledOnDefaultConstructedNoneObject_107) {
  Object obj;
  ASSERT_DEATH({ (void)obj.getCmd(); }, "");
}

TEST_F(ObjectGetCmdTest_107, DeathWhenCalledOnNonCmdTypeObject_107) {
  Object obj(123);
  ASSERT_DEATH({ (void)obj.getCmd(); }, "");
}
#endif