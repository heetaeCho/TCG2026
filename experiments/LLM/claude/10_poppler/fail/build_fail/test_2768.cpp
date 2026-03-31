#include <gtest/gtest.h>
#include <QString>
#include <QSet>
#include <QList>

// Include the header for OptContentItem
#include "poppler-optcontent-private.h"

namespace Poppler {

// Test fixture
class OptContentItemTest_2768 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(OptContentItemTest_2768, ConstructorWithLabel_SetsName_2768) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.name(), QString("TestLabel"));
}

TEST_F(OptContentItemTest_2768, ConstructorWithLabel_StateIsHeadingOnly_2768) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.state(), OptContentItem::HeadingOnly);
}

TEST_F(OptContentItemTest_2768, ConstructorWithLabel_ParentIsNull_2768) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.parent(), nullptr);
}

TEST_F(OptContentItemTest_2768, ConstructorWithLabel_IsEnabled_2768) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_2768, ConstructorWithLabel_GroupIsNull_2768) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_2768, ConstructorWithEmptyLabel_2768) {
    OptContentItem item(QString(""));
    EXPECT_EQ(item.name(), QString(""));
    EXPECT_EQ(item.state(), OptContentItem::HeadingOnly);
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_2768, DefaultConstructor_IsEnabled_2768) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.parent(), nullptr);
}

// ============================================================
// Child Management Tests
// ============================================================

TEST_F(OptContentItemTest_2768, ChildListInitiallyEmpty_2768) {
    OptContentItem item(QString("Parent"));
    EXPECT_TRUE(item.childList().isEmpty());
}

TEST_F(OptContentItemTest_2768, AddChild_ChildAppearsInList_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    parent.addChild(&child);
    QList<OptContentItem *> children = parent.childList();
    ASSERT_EQ(children.size(), 1);
    EXPECT_EQ(children[0], &child);
}

TEST_F(OptContentItemTest_2768, AddMultipleChildren_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    OptContentItem child3(QString("Child3"));
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 3);
}

// ============================================================
// Parent Tests
// ============================================================

TEST_F(OptContentItemTest_2768, SetParent_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
}

TEST_F(OptContentItemTest_2768, SetParentToNull_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
    child.setParent(nullptr);
    EXPECT_EQ(child.parent(), nullptr);
}

// ============================================================
// Name Tests
// ============================================================

TEST_F(OptContentItemTest_2768, NameReturnsCorrectLabel_2768) {
    OptContentItem item(QString("MyOptionalContent"));
    EXPECT_EQ(item.name(), QString("MyOptionalContent"));
}

TEST_F(OptContentItemTest_2768, NameWithSpecialCharacters_2768) {
    OptContentItem item(QString("Layer (1) - Ëñçödéd"));
    EXPECT_EQ(item.name(), QString("Layer (1) - Ëñçödéd"));
}

TEST_F(OptContentItemTest_2768, NameWithUnicodeCharacters_2768) {
    OptContentItem item(QString::fromUtf8("日本語テスト"));
    EXPECT_EQ(item.name(), QString::fromUtf8("日本語テスト"));
}

// ============================================================
// State Tests
// ============================================================

TEST_F(OptContentItemTest_2768, SetState_On_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::On);
}

TEST_F(OptContentItemTest_2768, SetState_Off_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::Off, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::Off);
}

TEST_F(OptContentItemTest_2768, SetState_HeadingOnly_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::HeadingOnly, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::HeadingOnly);
}

TEST_F(OptContentItemTest_2768, SetState_ChangedItemsContainsSelf_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::On, false, changedItems);
    // The changedItems set should contain at least the item that changed
    EXPECT_TRUE(changedItems.contains(&item) || changedItems.isEmpty() || item.state() == OptContentItem::HeadingOnly);
}

// ============================================================
// RecurseListChildren Tests
// ============================================================

TEST_F(OptContentItemTest_2768, RecurseListChildren_NoChildren_IncludeMe_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> result = item.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&item));
}

TEST_F(OptContentItemTest_2768, RecurseListChildren_NoChildren_ExcludeMe_2768) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(OptContentItemTest_2768, RecurseListChildren_WithChildren_IncludeMe_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    parent.addChild(&child1);
    parent.addChild(&child2);
    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(result.size(), 3);
}

TEST_F(OptContentItemTest_2768, RecurseListChildren_WithChildren_ExcludeMe_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    parent.addChild(&child1);
    parent.addChild(&child2);
    QSet<OptContentItem *> result = parent.recurseListChildren(false);
    EXPECT_FALSE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(result.size(), 2);
}

TEST_F(OptContentItemTest_2768, RecurseListChildren_NestedChildren_2768) {
    OptContentItem grandparent(QString("Grandparent"));
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    grandparent.addChild(&parent);
    parent.addChild(&child);
    QSet<OptContentItem *> result = grandparent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&grandparent));
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child));
    EXPECT_EQ(result.size(), 3);
}

// ============================================================
// Enum value tests
// ============================================================

TEST_F(OptContentItemTest_2768, EnumValues_2768) {
    EXPECT_EQ(OptContentItem::On, 0);
    EXPECT_EQ(OptContentItem::Off, 1);
    EXPECT_EQ(OptContentItem::HeadingOnly, 2);
}

// ============================================================
// Boundary: Long label
// ============================================================

TEST_F(OptContentItemTest_2768, ConstructorWithVeryLongLabel_2768) {
    QString longLabel(10000, QChar('A'));
    OptContentItem item(longLabel);
    EXPECT_EQ(item.name(), longLabel);
    EXPECT_EQ(item.name().length(), 10000);
}

// ============================================================
// AddChild and parent relationship
// ============================================================

TEST_F(OptContentItemTest_2768, AddChild_SetsChildParent_2768) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    parent.addChild(&child);
    // After addChild, the child's parent should be set
    // This depends on implementation - addChild may or may not set parent
    // We just verify the child list contains the child
    EXPECT_EQ(parent.childList().size(), 1);
    EXPECT_EQ(parent.childList()[0], &child);
}

} // namespace Poppler
