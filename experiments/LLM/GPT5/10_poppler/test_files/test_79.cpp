// TEST_ID = 79
// Unit tests for Object::isArray() from poppler/Object.h

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

#include "poppler/Object.h"
#include "poppler/Array.h"
#include "poppler/Dict.h"

namespace {

class ObjectIsArrayTest_79 : public ::testing::Test {};

TEST_F(ObjectIsArrayTest_79, DefaultConstructedIsNotArray_79)
{
  Object obj;
  EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectIsArrayTest_79, ConstructedFromArrayPointerIsArray_79)
{
  // In Poppler, Array is typically constructed with an XRef*; nullptr is commonly accepted in tests.
  auto *arr = new Array(nullptr);
  Object obj(arr);

  EXPECT_TRUE(obj.isArray());
}

TEST_F(ObjectIsArrayTest_79, ConstructedFromDictPointerIsNotArray_79)
{
  auto *dict = new Dict(nullptr);
  Object obj(dict);

  EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectIsArrayTest_79, PrimitiveConstructorsAreNotArray_79)
{
  Object b(true);
  Object i(123);
  Object r(3.25);
  Object s(std::string("hello"));

  EXPECT_FALSE(b.isArray());
  EXPECT_FALSE(i.isArray());
  EXPECT_FALSE(r.isArray());
  EXPECT_FALSE(s.isArray());
}

TEST_F(ObjectIsArrayTest_79, NameAndCmdTypesAreNotArray_79)
{
  Object nameObj(objName, "NameValue");
  Object cmdObj(objCmd, "CmdValue");

  EXPECT_FALSE(nameObj.isArray());
  EXPECT_FALSE(cmdObj.isArray());
}

TEST_F(ObjectIsArrayTest_79, NullEofAndErrorAreNotArray_79)
{
  Object n = Object::null();
  Object e = Object::eof();
  Object err = Object::error();

  EXPECT_FALSE(n.isArray());
  EXPECT_FALSE(e.isArray());
  EXPECT_FALSE(err.isArray());
}

TEST_F(ObjectIsArrayTest_79, SetToNullMakesFormerArrayNotArray_79)
{
  auto *arr = new Array(nullptr);
  Object obj(arr);
  ASSERT_TRUE(obj.isArray());

  obj.setToNull();
  EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectIsArrayTest_79, MoveConstructionPreservesArrayPropertyInDestination_79)
{
  auto *arr = new Array(nullptr);
  Object src(arr);
  ASSERT_TRUE(src.isArray());

  Object dst(std::move(src));
  EXPECT_TRUE(dst.isArray());

  // Do not assert on src after move: moved-from state is implementation-defined.
}

} // namespace