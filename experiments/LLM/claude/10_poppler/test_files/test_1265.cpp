#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>
#include <QSet>
#include <QList>

// Include the header under test
#include "poppler-optcontent-private.h"

namespace Poppler {

class OptContentItemTest_1265 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes parent to nullptr
TEST_F(OptContentItemTest_1265, DefaultConstructor_ParentIsNull_1265) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
}

// Test default constructor initializes enabled to true
TEST_F(OptContentItemTest_1265, DefaultConstructor_IsEnabled_1265) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test setParent sets the parent correctly
TEST_F(OptContentItemTest_1265, SetParent_SetsParentCorrectly_1265) {
    OptContentItem parent;
    OptContentItem child;
    
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
}

// Test setParent to nullptr
TEST_F(OptContentItemTest_1265, SetParent_SetToNull_1265) {
    OptContentItem parent;
    OptContentItem child;
    
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
    
    child.setParent(nullptr);
    EXPECT_EQ(child.parent(), nullptr);
}

// Test setParent can change parent
TEST_F(OptContentItemTest_1265, SetParent_ChangeParent_1265) {
    OptContentItem parent1;
    OptContentItem parent2;
    OptContentItem child;
    
    child.setParent(&parent1);
    EXPECT_EQ(child.parent(), &parent1);
    
    child.setParent(&parent2);
    EXPECT_EQ(child.parent(), &parent2);
}

// Test parent() returns nullptr by default
TEST_F(OptContentItemTest_1265, Parent_ReturnsNullByDefault_1265) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
}

// Test addChild adds a child to the child list
TEST_F(OptContentItemTest_1265, AddChild_ChildAppearsInList_1265) {
    OptContentItem parent;
    OptContentItem child;
    
    parent.addChild(&child);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children.at(0), &child);
}

// Test addChild sets parent of child
TEST_F(OptContentItemTest_1265, AddChild_SetsChildParent_1265) {
    OptContentItem parent;
    OptContentItem child;
    
    parent.addChild(&child);
    EXPECT_EQ(child.parent(), &parent);
}

// Test addChild with multiple children
TEST_F(OptContentItemTest_1265, AddChild_MultipleChildren_1265) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    OptContentItem child3;
    
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 3);
}

// Test childList returns empty list when no children
TEST_F(OptContentItemTest_1265, ChildList_EmptyByDefault_1265) {
    OptContentItem item;
    QList<OptContentItem *> children = item.childList();
    EXPECT_TRUE(children.isEmpty());
}

// Test group() returns nullptr for default constructed item
TEST_F(OptContentItemTest_1265, Group_ReturnsNullForDefaultItem_1265) {
    OptContentItem item;
    EXPECT_EQ(item.group(), nullptr);
}

// Test constructor with QString label
TEST_F(OptContentItemTest_1265, StringConstructor_SetsName_1265) {
    QString label("TestLabel");
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
}

// Test name() for default constructed item
TEST_F(OptContentItemTest_1265, Name_DefaultConstructor_1265) {
    OptContentItem item;
    // Default constructed item should have some name (possibly empty)
    QString name = item.name();
    // Just verify it doesn't crash - the exact value depends on implementation
}

// Test setParent to self (edge case)
TEST_F(OptContentItemTest_1265, SetParent_SetToSelf_1265) {
    OptContentItem item;
    item.setParent(&item);
    EXPECT_EQ(item.parent(), &item);
}

// Test recurseListChildren with no children and includeMe = false
TEST_F(OptContentItemTest_1265, RecurseListChildren_NoChildrenExcludeSelf_1265) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

// Test recurseListChildren with no children and includeMe = true
TEST_F(OptContentItemTest_1265, RecurseListChildren_NoChildrenIncludeSelf_1265) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(true);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(&item));
}

// Test recurseListChildren with children
TEST_F(OptContentItemTest_1265, RecurseListChildren_WithChildren_1265) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    
    parent.addChild(&child1);
    parent.addChild(&child2);
    
    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(result.size(), 3);
}

// Test recurseListChildren with nested children
TEST_F(OptContentItemTest_1265, RecurseListChildren_NestedChildren_1265) {
    OptContentItem grandparent;
    OptContentItem parent;
    OptContentItem child;
    
    grandparent.addChild(&parent);
    parent.addChild(&child);
    
    QSet<OptContentItem *> result = grandparent.recurseListChildren(false);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child));
    EXPECT_FALSE(result.contains(&grandparent));
}

// Test isEnabled for string-constructed item
TEST_F(OptContentItemTest_1265, IsEnabled_StringConstructor_1265) {
    QString label("Test");
    OptContentItem item(label);
    EXPECT_TRUE(item.isEnabled());
}

// Test that multiple setParent calls work correctly
TEST_F(OptContentItemTest_1265, SetParent_MultipleCalls_1265) {
    OptContentItem p1, p2, p3;
    OptContentItem child;
    
    child.setParent(&p1);
    EXPECT_EQ(child.parent(), &p1);
    
    child.setParent(&p2);
    EXPECT_EQ(child.parent(), &p2);
    
    child.setParent(&p3);
    EXPECT_EQ(child.parent(), &p3);
    
    child.setParent(nullptr);
    EXPECT_EQ(child.parent(), nullptr);
}

} // namespace Poppler
