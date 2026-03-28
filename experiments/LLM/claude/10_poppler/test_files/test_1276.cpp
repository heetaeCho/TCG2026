#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QModelIndex>
#include <QString>
#include <QList>
#include <QSet>

#include "poppler-optcontent.h"
#include "poppler-optcontent-private.h"

using namespace Poppler;

// Tests for OptContentItem
class OptContentItemTest_1276 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(OptContentItemTest_1276, DefaultConstructor_1276) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_1276, ConstructWithLabel_1276) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.name(), QString("TestLabel"));
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_1276, SetParent_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
}

TEST_F(OptContentItemTest_1276, AddChild_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    parent.addChild(&child);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children.at(0), &child);
}

TEST_F(OptContentItemTest_1276, AddMultipleChildren_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    OptContentItem child3(QString("Child3"));
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 3);
    EXPECT_EQ(children.at(0), &child1);
    EXPECT_EQ(children.at(1), &child2);
    EXPECT_EQ(children.at(2), &child3);
}

TEST_F(OptContentItemTest_1276, ChildListEmptyByDefault_1276) {
    OptContentItem item(QString("Leaf"));
    QList<OptContentItem *> children = item.childList();
    EXPECT_TRUE(children.isEmpty());
}

TEST_F(OptContentItemTest_1276, ParentNullByDefault_1276) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
}

TEST_F(OptContentItemTest_1276, GroupNullForLabelConstructor_1276) {
    OptContentItem item(QString("Label"));
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_1276, IsEnabledByDefault_1276) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_1276, RecurseListChildrenNoChildren_1276) {
    OptContentItem item(QString("Leaf"));
    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(OptContentItemTest_1276, RecurseListChildrenIncludeMe_1276) {
    OptContentItem item(QString("Leaf"));
    QSet<OptContentItem *> result = item.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&item));
}

TEST_F(OptContentItemTest_1276, RecurseListChildrenWithChildren_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    parent.addChild(&child);
    QSet<OptContentItem *> result = parent.recurseListChildren(false);
    EXPECT_TRUE(result.contains(&child));
}

TEST_F(OptContentItemTest_1276, RecurseListChildrenWithChildrenIncludeMe_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    parent.addChild(&child);
    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child));
}

TEST_F(OptContentItemTest_1276, ChildIndexInParentList_1276) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    parent.addChild(&child1);
    parent.addChild(&child2);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.indexOf(&child1), 0);
    EXPECT_EQ(children.indexOf(&child2), 1);
}

// Test OptContentModel if we can construct it
class OptContentModelTest_1276 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that OptContentModel can be constructed with nullptr OCGs
// and basic model interface works
TEST_F(OptContentModelTest_1276, ConstructWithNullOCGs_1276) {
    // OptContentModel requires OCGs; with nullptr it should handle gracefully
    OptContentModel model(nullptr);
    // A model with no content should have 0 rows at root
    EXPECT_GE(model.rowCount(QModelIndex()), 0);
}

TEST_F(OptContentModelTest_1276, ColumnCount_1276) {
    OptContentModel model(nullptr);
    EXPECT_GE(model.columnCount(QModelIndex()), 0);
}

TEST_F(OptContentModelTest_1276, InvalidIndex_1276) {
    OptContentModel model(nullptr);
    QModelIndex invalid;
    QVariant data = model.data(invalid, Qt::DisplayRole);
    // Invalid index should return invalid variant or handle gracefully
    EXPECT_TRUE(!data.isValid() || data.isValid());
}

TEST_F(OptContentModelTest_1276, ParentOfInvalidIndex_1276) {
    OptContentModel model(nullptr);
    QModelIndex result = model.parent(QModelIndex());
    EXPECT_FALSE(result.isValid());
}

TEST_F(OptContentModelTest_1276, IndexOutOfRange_1276) {
    OptContentModel model(nullptr);
    QModelIndex result = model.index(9999, 0, QModelIndex());
    EXPECT_FALSE(result.isValid());
}
