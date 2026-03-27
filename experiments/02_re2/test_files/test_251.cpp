#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class RE2Test : public ::testing::Test {

protected:

    RE2 re2_with_groups_("(?P<first>\\w+)-(?P<second>\\d+)");

    RE2 re2_without_groups_("abc");

};



TEST_F(RE2Test, CapturingGroupNames_ReturnsExpectedMapWithGroups_251) {

    const std::map<int, std::string>& group_names = re2_with_groups_.CapturingGroupNames();

    EXPECT_EQ(group_names.at(1), "first");

    EXPECT_EQ(group_names.at(2), "second");

}



TEST_F(RE2Test, CapturingGroupNames_ReturnsEmptyMapWithoutGroups_251) {

    const std::map<int, std::string>& group_names = re2_without_groups_.CapturingGroupNames();

    EXPECT_TRUE(group_names.empty());

}



TEST_F(RE2Test, CapturingGroupNames_CalledMultipleTimes_CachesResult_251) {

    const std::map<int, std::string>& first_call = re2_with_groups_.CapturingGroupNames();

    const std::map<int, std::string>& second_call = re2_with_groups_.CapturingGroupNames();

    EXPECT_EQ(&first_call, &second_call);  // Same map should be returned on subsequent calls

}



TEST_F(RE2Test, CapturingGroupNames_ReturnsConsistentOrder_251) {

    const std::map<int, std::string>& group_names = re2_with_groups_.CapturingGroupNames();

    auto it = group_names.begin();

    EXPECT_EQ(it->first, 1);

    EXPECT_EQ(it->second, "first");

    ++it;

    EXPECT_EQ(it->first, 2);

    EXPECT_EQ(it->second, "second");

}
