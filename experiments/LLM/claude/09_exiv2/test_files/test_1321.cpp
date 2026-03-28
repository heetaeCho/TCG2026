#include <gtest/gtest.h>
#include <exiv2/tags.hpp>

using namespace Exiv2;

class GroupInfoTest_1321 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that operator== with GroupName returns true when groupName matches
TEST_F(GroupInfoTest_1321, OperatorEqualGroupName_MatchingName_ReturnsTrue_1321) {
    // We need to find a known GroupInfo instance from the Exiv2 library
    // Use the built-in group info structures
    const GroupInfo* groups = ExifTags::groupList();
    if (groups && groups->groupName_) {
        GroupInfo gi = *groups;
        std::string name(gi.groupName_);
        EXPECT_TRUE(gi == name);
    }
}

// Test that operator== with GroupName returns false when groupName does not match
TEST_F(GroupInfoTest_1321, OperatorEqualGroupName_NonMatchingName_ReturnsFalse_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups && groups->groupName_) {
        GroupInfo gi = *groups;
        std::string nonMatchingName("ThisGroupNameShouldNotExist_XYZ_12345");
        EXPECT_FALSE(gi == nonMatchingName);
    }
}

// Test operator== with IfdId returns true when ifdId matches
TEST_F(GroupInfoTest_1321, OperatorEqualIfdId_MatchingId_ReturnsTrue_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups) {
        GroupInfo gi = *groups;
        IfdId id = gi.ifdId_;
        EXPECT_TRUE(gi == id);
    }
}

// Test operator== with IfdId returns false when ifdId does not match
TEST_F(GroupInfoTest_1321, OperatorEqualIfdId_NonMatchingId_ReturnsFalse_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups) {
        GroupInfo gi = *groups;
        // Use a different IfdId that shouldn't match the first group
        IfdId nonMatchingId = IfdId::lastId;
        if (gi.ifdId_ == nonMatchingId) {
            nonMatchingId = IfdId::ifd0Id;
        }
        if (gi.ifdId_ != nonMatchingId) {
            EXPECT_FALSE(gi == nonMatchingId);
        }
    }
}

// Test operator== with empty GroupName
TEST_F(GroupInfoTest_1321, OperatorEqualGroupName_EmptyString_ReturnsFalse_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups && groups->groupName_ && std::string(groups->groupName_).length() > 0) {
        GroupInfo gi = *groups;
        std::string emptyName("");
        EXPECT_FALSE(gi == emptyName);
    }
}

// Test multiple groups for consistency
TEST_F(GroupInfoTest_1321, OperatorEqualGroupName_MultipleGroups_ConsistentBehavior_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups) {
        for (const GroupInfo* g = groups; g->groupName_ != nullptr; ++g) {
            std::string name(g->groupName_);
            EXPECT_TRUE(*g == name) << "Failed for group: " << name;
            
            std::string wrongName = name + "_WRONG";
            EXPECT_FALSE(*g == wrongName) << "False positive for group: " << wrongName;
        }
    }
}

// Test multiple groups for IfdId consistency
TEST_F(GroupInfoTest_1321, OperatorEqualIfdId_MultipleGroups_ConsistentBehavior_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups) {
        for (const GroupInfo* g = groups; g->groupName_ != nullptr; ++g) {
            IfdId id = g->ifdId_;
            EXPECT_TRUE(*g == id) << "Failed for group with ifdName: " << g->ifdName_;
        }
    }
}

// Boundary: Test that two different groups with different names don't cross-match
TEST_F(GroupInfoTest_1321, OperatorEqualGroupName_CrossGroupComparison_ReturnsFalse_1321) {
    const GroupInfo* groups = ExifTags::groupList();
    if (groups && groups->groupName_) {
        const GroupInfo* first = groups;
        const GroupInfo* second = nullptr;
        for (const GroupInfo* g = groups; g->groupName_ != nullptr; ++g) {
            if (std::string(g->groupName_) != std::string(first->groupName_)) {
                second = g;
                break;
            }
        }
        if (second) {
            std::string secondName(second->groupName_);
            EXPECT_FALSE(*first == secondName);
        }
    }
}
