// Object_isCmd_unittest_90.cpp

#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <utility>

#include "Object.h"

class ObjectIsCmdTest_90 : public ::testing::Test {};

// Normal operation: a cmd object matches the exact command string.
TEST_F(ObjectIsCmdTest_90, CmdObjectMatchesExactString_90) {
  Object o(objCmd, std::string_view("q"));

  EXPECT_TRUE(o.isCmd());
  EXPECT_TRUE(o.isCmd("q"));
  EXPECT_FALSE(o.isCmd("Q"));
  EXPECT_FALSE(o.isCmd("qq"));
  EXPECT_FALSE(o.isCmd(""));
}

// Normal operation: constructing via const char* should behave the same for matching.
TEST_F(ObjectIsCmdTest_90, CmdObjectConstructedFromCStringMatches_90) {
  Object o(objCmd, "BT");

  EXPECT_TRUE(o.isCmd());
  EXPECT_TRUE(o.isCmd("BT"));
  EXPECT_FALSE(o.isCmd("Bt"));
  EXPECT_FALSE(o.isCmd("ET"));
}

// Boundary: empty command string.
TEST_F(ObjectIsCmdTest_90, EmptyCmdStringMatchesOnlyEmpty_90) {
  Object o(objCmd, std::string_view(""));

  EXPECT_TRUE(o.isCmd());
  EXPECT_TRUE(o.isCmd(""));
  EXPECT_FALSE(o.isCmd(" "));
  EXPECT_FALSE(o.isCmd("q"));
}

// Boundary: default-constructed object is not a cmd and never matches.
TEST_F(ObjectIsCmdTest_90, DefaultConstructedIsNotCmd_90) {
  Object o;

  EXPECT_FALSE(o.isCmd());
  EXPECT_FALSE(o.isCmd(""));
  EXPECT_FALSE(o.isCmd("q"));
  EXPECT_FALSE(o.isCmd("BT"));
}

// Error/negative: non-cmd types should not match isCmd(string_view), even if payload looks similar.
TEST_F(ObjectIsCmdTest_90, NonCmdTypeDoesNotMatchCmdString_90) {
  Object nameObj(objName, std::string_view("q"));
  Object stringObj(objString, std::string_view("q"));

  EXPECT_FALSE(nameObj.isCmd());
  EXPECT_FALSE(nameObj.isCmd("q"));

  EXPECT_FALSE(stringObj.isCmd());
  EXPECT_FALSE(stringObj.isCmd("q"));
}

// Boundary/robustness: moved-to object preserves observable cmd matching.
TEST_F(ObjectIsCmdTest_90, MoveConstructedPreservesCmdMatching_90) {
  Object src(objCmd, std::string_view("ET"));
  Object dst(std::move(src));

  EXPECT_TRUE(dst.isCmd());
  EXPECT_TRUE(dst.isCmd("ET"));
  EXPECT_FALSE(dst.isCmd("BT"));
}