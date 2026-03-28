// TEST_ID 1425
// File: test_tags_int_groupList_1425.cpp

#include <gtest/gtest.h>

#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include("src/tags_int.hpp")
#include "src/tags_int.hpp"
#elif __has_include("./TestProjects/exiv2/src/tags_int.hpp")
#include "./TestProjects/exiv2/src/tags_int.hpp"
#else
#error "Cannot find tags_int.hpp (needed for Exiv2::Internal::GroupInfo and groupList())"
#endif

namespace Exiv2::Internal {
// groupList() is implemented in tags_int.cpp (given in the prompt)
const GroupInfo* groupList();

// groupInfo is defined in tags_int.cpp (given in the prompt)
extern const GroupInfo groupInfo[];
}  // namespace Exiv2::Internal

namespace {

TEST(GroupListTest_1425, ReturnsNonNullPointer_1425) {
  const Exiv2::Internal::GroupInfo* p = Exiv2::Internal::groupList();
  ASSERT_NE(p, nullptr);
}

TEST(GroupListTest_1425, ReturnsPointerToSecondElementOfGroupInfo_1425) {
  const Exiv2::Internal::GroupInfo* p = Exiv2::Internal::groupList();

  // Observable contract from the provided implementation: groupInfo + 1
  EXPECT_EQ(p, &Exiv2::Internal::groupInfo[1]);
}

TEST(GroupListTest_1425, DoesNotReturnPointerToFirstElement_1425) {
  const Exiv2::Internal::GroupInfo* p = Exiv2::Internal::groupList();
  EXPECT_NE(p, &Exiv2::Internal::groupInfo[0]);
}

TEST(GroupListTest_1425, MultipleCallsReturnSameAddress_1425) {
  const Exiv2::Internal::GroupInfo* p1 = Exiv2::Internal::groupList();
  const Exiv2::Internal::GroupInfo* p2 = Exiv2::Internal::groupList();
  EXPECT_EQ(p1, p2);
}

TEST(GroupListTest_1425, ReturnedPointerIsExactlyOnePastGroupInfoBase_1425) {
  const Exiv2::Internal::GroupInfo* p = Exiv2::Internal::groupList();

  // Pointer arithmetic relationship (boundary/offset property).
  EXPECT_EQ(p - 1, &Exiv2::Internal::groupInfo[0]);
}

TEST(GroupListTest_1425, ReturnedEntryMatchesGroupInfoSecondEntryFields_1425) {
  const Exiv2::Internal::GroupInfo* p = Exiv2::Internal::groupList();
  ASSERT_NE(p, nullptr);

  // Verify observable consistency: dereferencing returned entry matches groupInfo[1].
  EXPECT_EQ(p->ifdId_, Exiv2::Internal::groupInfo[1].ifdId_);
  EXPECT_STREQ(p->ifdName_, Exiv2::Internal::groupInfo[1].ifdName_);
  EXPECT_STREQ(p->groupName_, Exiv2::Internal::groupInfo[1].groupName_);
  EXPECT_EQ(p->tagList_, Exiv2::Internal::groupInfo[1].tagList_);
}

}  // namespace