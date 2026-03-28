// Object_CtorObjTypeStringView_test_2758.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <string>
#include <string_view>

#include "Object.h"

class ObjectCtorObjTypeStringViewTest_2758 : public ::testing::Test {};

// Normal operation: objName with a typical string.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, NameStoresAndReportsTypeAndValue_2758) {
  Object obj(objName, std::string_view("Foo"));

  EXPECT_EQ(obj.getType(), objName);
  EXPECT_TRUE(obj.isName());
  EXPECT_FALSE(obj.isCmd());

  const char *name = obj.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Foo");

  EXPECT_TRUE(obj.isName(std::string_view("Foo")));
  EXPECT_FALSE(obj.isName(std::string_view("Bar")));
}

// Normal operation: objCmd with a typical string.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, CmdStoresAndReportsTypeAndValue_2758) {
  Object obj(objCmd, std::string_view("Do"));

  EXPECT_EQ(obj.getType(), objCmd);
  EXPECT_TRUE(obj.isCmd());
  EXPECT_FALSE(obj.isName());

  const char *cmd = obj.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_STREQ(cmd, "Do");

  EXPECT_TRUE(obj.isCmd(std::string_view("Do")));
  EXPECT_FALSE(obj.isCmd(std::string_view("Dont")));
}

// Boundary: empty string_view.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, EmptyStringIsHandled_2758) {
  Object nameObj(objName, std::string_view(""));

  EXPECT_EQ(nameObj.getType(), objName);
  EXPECT_TRUE(nameObj.isName());

  const char *name = nameObj.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "");

  Object cmdObj(objCmd, std::string_view(""));
  EXPECT_EQ(cmdObj.getType(), objCmd);
  EXPECT_TRUE(cmdObj.isCmd());

  const char *cmd = cmdObj.getCmd();
  ASSERT_NE(cmd, nullptr);
  EXPECT_STREQ(cmd, "");
}

// Boundary: non-null-terminated source buffer; constructor should still provide a C-string.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, NonNullTerminatedSourceBufferBecomesNullTerminated_2758) {
  const std::array<char, 3> raw = {'a', 'b', 'c'};
  std::string_view v(raw.data(), raw.size());

  Object obj(objName, v);

  const char *name = obj.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "abc");  // relies only on public getName() returning a C-string
}

// Boundary: reasonably large input.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, LargeStringIsPreserved_2758) {
  std::string big(10000, 'x');
  Object obj(objCmd, std::string_view(big));

  const char *cmd = obj.getCmd();
  ASSERT_NE(cmd, nullptr);

  // Compare size and content via C-string view; avoid touching internals.
  EXPECT_EQ(std::strlen(cmd), big.size());
  EXPECT_EQ(std::string(cmd), big);
}

// Observable behavior: object must not depend on the lifetime/mutation of the original buffer.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, DoesNotAliasInputBufferAfterConstruction_2758) {
  std::string src = "KeepMe";
  Object obj(objName, std::string_view(src));

  // Mutate the original string after construction.
  src.assign("Changed");

  const char *name = obj.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "KeepMe");
}

// Exercise the delegating const char* overload.
TEST_F(ObjectCtorObjTypeStringViewTest_2758, ConstCharOverloadWorks_2758) {
  Object obj(objName, "Hello");

  EXPECT_EQ(obj.getType(), objName);
  EXPECT_TRUE(obj.isName());

  const char *name = obj.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Hello");
}

// Exceptional/error case (observable via assert): invalid ObjType should trigger an assertion.
// This is only meaningful when assertions are enabled.
#ifndef NDEBUG
TEST_F(ObjectCtorObjTypeStringViewTest_2758, InvalidObjTypeAsserts_2758) {
  ASSERT_DEATH(
      {
        Object bad(objInt, std::string_view("Nope"));
        (void)bad;
      },
      ".*");
}
#endif