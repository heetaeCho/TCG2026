#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "unicode_groups.h"

#include "absl/strings/string_view.h"



namespace re2 {



// Mock class for UGroup to facilitate testing if needed.

class MockUGroup : public UGroup {

public:

    MOCK_CONST_METHOD0(name, const char*());

};



TEST(LookupGroupTest_521, FoundExactMatch_521) {

    UGroup groups[] = {{"test", 1, nullptr, 0, nullptr, 0}};

    int ngroups = sizeof(groups) / sizeof(groups[0]);

    const UGroup* result = LookupGroup("test", groups, ngroups);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(absl::string_view(result->name), "test");

}



TEST(LookupGroupTest_521, NotFound_521) {

    UGroup groups[] = {{"example", 1, nullptr, 0, nullptr, 0}};

    int ngroups = sizeof(groups) / sizeof(groups[0]);

    const UGroup* result = LookupGroup("test", groups, ngroups);

    EXPECT_EQ(result, nullptr);

}



TEST(LookupGroupTest_521, EmptyGroupsArray_521) {

    UGroup groups[] = {};

    int ngroups = 0;

    const UGroup* result = LookupGroup("test", groups, ngroups);

    EXPECT_EQ(result, nullptr);

}



TEST(LookupGroupTest_521, MultipleEntriesFoundFirstMatch_521) {

    UGroup groups[] = {{"first", 1, nullptr, 0, nullptr, 0}, {"test", 1, nullptr, 0, nullptr, 0}, {"second", 1, nullptr, 0, nullptr, 0}};

    int ngroups = sizeof(groups) / sizeof(groups[0]);

    const UGroup* result = LookupGroup("test", groups, ngroups);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(absl::string_view(result->name), "test");

}



TEST(LookupGroupTest_521, CaseSensitiveSearch_521) {

    UGroup groups[] = {{"test", 1, nullptr, 0, nullptr, 0}};

    int ngroups = sizeof(groups) / sizeof(groups[0]);

    const UGroup* result = LookupGroup("TEST", groups, ngroups);

    EXPECT_EQ(result, nullptr);

}



} // namespace re2
