// StructTreeRoot_getClassMap_1718_test.cc
#include <gtest/gtest.h>

#include "StructTreeRoot.h"
#include "Object.h"
#include "Dict.h"

namespace {

class StructTreeRootTest_1718 : public ::testing::Test {
protected:
  // Builds a Dict (owned by returned Object) suitable for passing into StructTreeRoot ctor.
  static Object MakeRootDictObj() {
    return Object(new Dict(nullptr));
  }

  static Object MakeDictObj() { return Object(new Dict(nullptr)); }
};

TEST_F(StructTreeRootTest_1718, GetClassMapReturnsNullWhenMissing_1718) {
  Object rootDictObj = MakeRootDictObj();
  ASSERT_NE(rootDictObj.getDict(), nullptr);

  StructTreeRoot root(/*docA=*/nullptr, *rootDictObj.getDict());

  EXPECT_EQ(root.getClassMap(), nullptr);
}

TEST_F(StructTreeRootTest_1718, GetClassMapReturnsNullWhenNotADict_1718) {
  Object rootDictObj = MakeRootDictObj();
  ASSERT_NE(rootDictObj.getDict(), nullptr);

  // Set ClassMap to a non-dict (int).
  rootDictObj.dictAdd("ClassMap", Object(123));

  StructTreeRoot root(/*docA=*/nullptr, *rootDictObj.getDict());

  EXPECT_EQ(root.getClassMap(), nullptr);
}

TEST_F(StructTreeRootTest_1718, GetClassMapReturnsNullWhenExplicitNull_1718) {
  Object rootDictObj = MakeRootDictObj();
  ASSERT_NE(rootDictObj.getDict(), nullptr);

  // Set ClassMap to null object.
  rootDictObj.dictAdd("ClassMap", Object::null());

  StructTreeRoot root(/*docA=*/nullptr, *rootDictObj.getDict());

  EXPECT_EQ(root.getClassMap(), nullptr);
}

TEST_F(StructTreeRootTest_1718, GetClassMapReturnsPointerWhenDictProvided_1718) {
  Object rootDictObj = MakeRootDictObj();
  ASSERT_NE(rootDictObj.getDict(), nullptr);

  Object classMapObj = MakeDictObj();
  Dict *expected = classMapObj.getDict();
  ASSERT_NE(expected, nullptr);

  // Populate the dict with some arbitrary content (should not matter).
  // This uses only public Object API.
  classMapObj.dictAdd("AnyKey", Object(1));

  rootDictObj.dictAdd("ClassMap", std::move(classMapObj));

  StructTreeRoot root(/*docA=*/nullptr, *rootDictObj.getDict());

  EXPECT_EQ(root.getClassMap(), expected);
}

TEST_F(StructTreeRootTest_1718, GetClassMapIsStableAcrossMultipleCalls_1718) {
  Object rootDictObj = MakeRootDictObj();
  ASSERT_NE(rootDictObj.getDict(), nullptr);

  Object classMapObj = MakeDictObj();
  Dict *expected = classMapObj.getDict();
  ASSERT_NE(expected, nullptr);

  rootDictObj.dictAdd("ClassMap", std::move(classMapObj));

  StructTreeRoot root(/*docA=*/nullptr, *rootDictObj.getDict());

  Dict *first = root.getClassMap();
  Dict *second = root.getClassMap();
  Dict *third = root.getClassMap();

  EXPECT_EQ(first, expected);
  EXPECT_EQ(second, expected);
  EXPECT_EQ(third, expected);
}

} // namespace