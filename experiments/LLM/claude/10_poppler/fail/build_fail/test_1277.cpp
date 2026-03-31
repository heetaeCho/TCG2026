#include <gtest/gtest.h>
#include <QModelIndex>
#include <QAbstractItemModel>

// We need to define minimal stubs to make the code compile without the full Poppler infrastructure.

namespace Poppler {

class OptContentItem {
public:
    OptContentItem() = default;
    virtual ~OptContentItem() = default;
};

// Minimal forward declarations
class OptContentModel;

class OptContentModelPrivate {
public:
    OptContentModel *q = nullptr;
    OptContentItem *m_rootNode = nullptr;

    OptContentItem *nodeFromIndex(const QModelIndex &index, bool canBeNull) const
    {
        if (index.isValid()) {
            return static_cast<OptContentItem *>(index.internalPointer());
        }
        return canBeNull ? nullptr : m_rootNode;
    }
};

} // namespace Poppler

// Helper to create a valid QModelIndex with an internal pointer.
// We use a trick: QAbstractItemModel::createIndex is protected, so we make a small helper model.
class FakeModel : public QAbstractItemModel {
public:
    QModelIndex createIndexPublic(int row, int column, void *ptr) const
    {
        return createIndex(row, column, ptr);
    }

    // Required overrides (unused but needed to compile)
    QModelIndex index(int, int, const QModelIndex &) const override { return {}; }
    QModelIndex parent(const QModelIndex &) const override { return {}; }
    int rowCount(const QModelIndex &) const override { return 0; }
    int columnCount(const QModelIndex &) const override { return 0; }
    QVariant data(const QModelIndex &, int) const override { return {}; }
};

class OptContentModelPrivateTest_1277 : public ::testing::Test {
protected:
    void SetUp() override
    {
        rootNode = new Poppler::OptContentItem();
        priv.m_rootNode = rootNode;
    }

    void TearDown() override
    {
        delete rootNode;
    }

    Poppler::OptContentModelPrivate priv;
    Poppler::OptContentItem *rootNode = nullptr;
    FakeModel fakeModel;
};

// Test: Invalid index with canBeNull=false returns the root node
TEST_F(OptContentModelPrivateTest_1277, InvalidIndex_CanBeNullFalse_ReturnsRootNode_1277)
{
    QModelIndex invalidIndex; // default-constructed = invalid
    Poppler::OptContentItem *result = priv.nodeFromIndex(invalidIndex, false);
    EXPECT_EQ(result, rootNode);
}

// Test: Invalid index with canBeNull=true returns nullptr
TEST_F(OptContentModelPrivateTest_1277, InvalidIndex_CanBeNullTrue_ReturnsNull_1277)
{
    QModelIndex invalidIndex;
    Poppler::OptContentItem *result = priv.nodeFromIndex(invalidIndex, true);
    EXPECT_EQ(result, nullptr);
}

// Test: Valid index returns the internal pointer cast to OptContentItem*
TEST_F(OptContentModelPrivateTest_1277, ValidIndex_ReturnsCastedInternalPointer_1277)
{
    Poppler::OptContentItem item;
    QModelIndex validIndex = fakeModel.createIndexPublic(0, 0, &item);
    ASSERT_TRUE(validIndex.isValid());

    Poppler::OptContentItem *result = priv.nodeFromIndex(validIndex, false);
    EXPECT_EQ(result, &item);
}

// Test: Valid index with canBeNull=true still returns the internal pointer (not null)
TEST_F(OptContentModelPrivateTest_1277, ValidIndex_CanBeNullTrue_ReturnsInternalPointer_1277)
{
    Poppler::OptContentItem item;
    QModelIndex validIndex = fakeModel.createIndexPublic(0, 0, &item);
    ASSERT_TRUE(validIndex.isValid());

    Poppler::OptContentItem *result = priv.nodeFromIndex(validIndex, true);
    EXPECT_EQ(result, &item);
}

// Test: Valid index with canBeNull=false also returns internal pointer (not root)
TEST_F(OptContentModelPrivateTest_1277, ValidIndex_CanBeNullFalse_ReturnsInternalPointerNotRoot_1277)
{
    Poppler::OptContentItem item;
    QModelIndex validIndex = fakeModel.createIndexPublic(1, 2, &item);
    ASSERT_TRUE(validIndex.isValid());

    Poppler::OptContentItem *result = priv.nodeFromIndex(validIndex, false);
    EXPECT_EQ(result, &item);
    EXPECT_NE(result, rootNode);
}

// Test: When rootNode is nullptr and invalid index with canBeNull=false, returns nullptr
TEST_F(OptContentModelPrivateTest_1277, InvalidIndex_NullRootNode_CanBeNullFalse_ReturnsNull_1277)
{
    priv.m_rootNode = nullptr;
    QModelIndex invalidIndex;
    Poppler::OptContentItem *result = priv.nodeFromIndex(invalidIndex, false);
    EXPECT_EQ(result, nullptr);
}

// Test: When rootNode is nullptr and invalid index with canBeNull=true, returns nullptr
TEST_F(OptContentModelPrivateTest_1277, InvalidIndex_NullRootNode_CanBeNullTrue_ReturnsNull_1277)
{
    priv.m_rootNode = nullptr;
    QModelIndex invalidIndex;
    Poppler::OptContentItem *result = priv.nodeFromIndex(invalidIndex, true);
    EXPECT_EQ(result, nullptr);
}

// Test: Different items at different valid indices are returned correctly
TEST_F(OptContentModelPrivateTest_1277, MultipleValidIndices_ReturnCorrectItems_1277)
{
    Poppler::OptContentItem item1;
    Poppler::OptContentItem item2;
    Poppler::OptContentItem item3;

    QModelIndex idx1 = fakeModel.createIndexPublic(0, 0, &item1);
    QModelIndex idx2 = fakeModel.createIndexPublic(1, 0, &item2);
    QModelIndex idx3 = fakeModel.createIndexPublic(2, 0, &item3);

    EXPECT_EQ(priv.nodeFromIndex(idx1, false), &item1);
    EXPECT_EQ(priv.nodeFromIndex(idx2, false), &item2);
    EXPECT_EQ(priv.nodeFromIndex(idx3, true), &item3);
}

// Test: Valid index whose internal pointer happens to equal rootNode
TEST_F(OptContentModelPrivateTest_1277, ValidIndex_InternalPointerIsRootNode_ReturnsRootNode_1277)
{
    QModelIndex validIndex = fakeModel.createIndexPublic(0, 0, rootNode);
    ASSERT_TRUE(validIndex.isValid());

    Poppler::OptContentItem *result = priv.nodeFromIndex(validIndex, false);
    EXPECT_EQ(result, rootNode);
}
