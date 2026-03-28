// File: get_optional_content_rbgroups_test_2240.cc
//
// Unit tests for static helper in:
//   ./TestProjects/poppler/glib/poppler-document.cc
//
// NOTE: The function under test is `static`, so we include the implementation
// file to access it from this test translation unit.

#include <gtest/gtest.h>

#include <glib.h>

// Poppler core types used to build inputs for OCGs
#include "poppler/Array.h"
#include "poppler/Object.h"
#include "poppler/OptionalContent.h"

// Include the .cc to access the `static` function under test.
#include "poppler-document.cc"

namespace {

class GetOptionalContentRbGroupsTest_2240 : public ::testing::Test {
protected:
  static void FreeNestedGroups(GList *groups) {
    // `groups` is a list of GList* (each element is a "group" list).
    for (GList *it = groups; it != nullptr; it = it->next) {
      GList *group = static_cast<GList *>(it->data);
      if (group) {
        g_list_free(group);
      }
    }
    if (groups) {
      g_list_free(groups);
    }
  }

  static Object MakeOcgObjectWithRBGroups(Object &&rbGroupsObj) {
    // Build an OCG Properties-like dict:
    //   props: { "D": { "RBGroups": <rbGroupsObj> } }
    //
    // We only rely on the public Object/Dict APIs to add keys.
    auto *defaultCfgDict = new Dict(nullptr);
    Object defaultCfgObj(defaultCfgDict);
    defaultCfgObj.dictAdd("RBGroups", std::move(rbGroupsObj));

    auto *propsDict = new Dict(nullptr);
    Object propsObj(propsDict);
    propsObj.dictAdd("D", std::move(defaultCfgObj));

    return propsObj;
  }

  static std::unique_ptr<Array> MakeArrayWithOneInt(int v) {
    auto arr = std::make_unique<Array>(nullptr);
    arr->add(Object(v));
    return arr;
  }

  static std::unique_ptr<Array> MakeTopLevelRBGroups(Array *child0, Array *child1) {
    auto top = std::make_unique<Array>(nullptr);
    if (child0) {
      top->add(Object(child0));
    }
    if (child1) {
      top->add(Object(child1));
    }
    return top;
  }
};

TEST_F(GetOptionalContentRbGroupsTest_2240, NullRBGroupsReturnsNull_2240) {
  // No "RBGroups" -> expect nullptr result list.
  auto *defaultCfgDict = new Dict(nullptr);
  Object defaultCfgObj(defaultCfgDict);

  auto *propsDict = new Dict(nullptr);
  Object propsObj(propsDict);
  propsObj.dictAdd("D", std::move(defaultCfgObj));

  OCGs ocgs(propsObj, nullptr);

  GList *groups = get_optional_content_rbgroups(&ocgs);
  EXPECT_EQ(groups, nullptr);
}

TEST_F(GetOptionalContentRbGroupsTest_2240, EmptyRBGroupsReturnsNull_2240) {
  // RBGroups is an empty array -> loop doesn't add anything -> nullptr.
  auto top = std::make_unique<Array>(nullptr);
  Object propsObj = MakeOcgObjectWithRBGroups(Object(top.get()));

  OCGs ocgs(propsObj, nullptr);

  GList *groups = get_optional_content_rbgroups(&ocgs);
  EXPECT_EQ(groups, nullptr);
}

TEST_F(GetOptionalContentRbGroupsTest_2240, RBGroupsNonArrayEntriesAreIgnored_2240) {
  // RBGroups contains a non-array element; it should be skipped and result remains nullptr.
  auto top = MakeArrayWithOneInt(123); // element is int, not array
  Object propsObj = MakeOcgObjectWithRBGroups(Object(top.get()));

  OCGs ocgs(propsObj, nullptr);

  GList *groups = get_optional_content_rbgroups(&ocgs);
  EXPECT_EQ(groups, nullptr);
}

TEST_F(GetOptionalContentRbGroupsTest_2240, RBGroupsArrayEntriesProduceGroupNodes_2240) {
  // RBGroups is an array of arrays. Even if inner arrays contain no valid refs,
  // the function prepends a (possibly null) group for each top-level array entry.
  auto inner0 = std::make_unique<Array>(nullptr);  // empty inner array -> group stays nullptr
  auto inner1 = MakeArrayWithOneInt(7);            // int is not Ref -> group stays nullptr

  auto top = MakeTopLevelRBGroups(inner0.get(), inner1.get());
  Object propsObj = MakeOcgObjectWithRBGroups(Object(top.get()));

  OCGs ocgs(propsObj, nullptr);

  GList *groups = get_optional_content_rbgroups(&ocgs);
  ASSERT_NE(groups, nullptr);

  // Two top-level arrays => two group nodes.
  EXPECT_EQ(g_list_length(groups), 2u);

  // With no Ref elements, each group's pointer should remain null.
  for (GList *it = groups; it != nullptr; it = it->next) {
    EXPECT_EQ(it->data, nullptr);
  }

  FreeNestedGroups(groups);
}

TEST_F(GetOptionalContentRbGroupsTest_2240, MixedTopLevelEntriesOnlyArraysCount_2240) {
  // Top-level RBGroups: [ int, [ ... ], int, [ ... ] ]
  // Only array entries should contribute to the returned list length.
  auto top = std::make_unique<Array>(nullptr);
  top->add(Object(1)); // non-array -> ignored

  auto innerA = std::make_unique<Array>(nullptr);
  innerA->add(Object(10)); // non-ref -> group stays nullptr
  top->add(Object(innerA.get())); // array -> contributes one node

  top->add(Object(2)); // non-array -> ignored

  auto innerB = std::make_unique<Array>(nullptr);
  // empty -> group stays nullptr
  top->add(Object(innerB.get())); // array -> contributes one node

  Object propsObj = MakeOcgObjectWithRBGroups(Object(top.get()));
  OCGs ocgs(propsObj, nullptr);

  GList *groups = get_optional_content_rbgroups(&ocgs);
  ASSERT_NE(groups, nullptr);

  EXPECT_EQ(g_list_length(groups), 2u);
  for (GList *it = groups; it != nullptr; it = it->next) {
    EXPECT_EQ(it->data, nullptr);
  }

  FreeNestedGroups(groups);
}

} // namespace