// TEST_ID: 83
// Unit tests for Object::isCmd() (poppler/Object.h)

#include <gtest/gtest.h>

#include "poppler/Object.h"

// Note: We treat Object as a black box. These tests only use public constructors
// and public query functions (getType()/isCmd()).

namespace {

class ObjectIsCmdTest_83 : public ::testing::Test {};

TEST_F(ObjectIsCmdTest_83, DefaultConstructedIsNotCmd_83) {
  Object obj;
  EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, ConstructedWithNameTypeIsNotCmd_83) {
  Object obj(objName, "SomeName");
  EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, ConstructedWithCmdTypeIsCmd_83) {
  Object obj(objCmd, "q"); // any command token string
  EXPECT_TRUE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, NullFactoryIsNotCmd_83) {
  Object obj = Object::null();
  EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, ErrorFactoryIsNotCmd_83) {
  Object obj = Object::error();
  EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, EofFactoryIsNotCmd_83) {
  Object obj = Object::eof();
  EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectIsCmdTest_83, MovePreservesIsCmdObservableBehavior_83) {
  Object cmd(objCmd, "BT");
  EXPECT_TRUE(cmd.isCmd());

  Object moved(std::move(cmd));
  EXPECT_TRUE(moved.isCmd());
  // Do not assert anything about the moved-from object (unspecified state).
}

TEST_F(ObjectIsCmdTest_83, GetTypeConsistentWithIsCmdForCmdAndNonCmd_83) {
  Object cmd(objCmd, "ET");
  EXPECT_EQ(cmd.getType(), objCmd);
  EXPECT_TRUE(cmd.isCmd());

  Object nonCmd(objString, std::string_view("hello"));
  EXPECT_NE(nonCmd.getType(), objCmd);
  EXPECT_FALSE(nonCmd.isCmd());
}

} // namespace