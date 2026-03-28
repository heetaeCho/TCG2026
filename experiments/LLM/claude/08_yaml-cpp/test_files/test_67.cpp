#include <gtest/gtest.h>
#include <memory>
#include "ptr_vector.h"

namespace {

struct TestItem {
    int value;
    explicit TestItem(int v) : value(v) {}
};

class PtrVectorTest_67 : public ::testing::Test {
protected:
    YAML::ptr_vector<TestItem> vec;
};

TEST_F(PtrVectorTest_67, DefaultConstructorCreatesEmptyVector_67) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_67, PushBackIncreasesSize_67) {
    vec.push_back(std::make_unique<TestItem>(1));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_67, PushBackMultipleElements_67) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.push_back(std::make_unique<TestItem>(20));
    vec.push_back(std::make_unique<TestItem>(30));
    EXPECT_EQ(vec.size(), 3u);
}

TEST_F(PtrVectorTest_67, SubscriptOperatorReturnsCorrectElement_67) {
    vec.push_back(std::make_unique<TestItem>(42));
    vec.push_back(std::make_unique<TestItem>(99));
    EXPECT_EQ(vec[0].value, 42);
    EXPECT_EQ(vec[1].value, 99);
}

TEST_F(PtrVectorTest_67, BackReturnsLastElement_67) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    vec.push_back(std::make_unique<TestItem>(3));
    EXPECT_EQ(vec.back().value, 3);
}

TEST_F(PtrVectorTest_67, BackReturnsSingleElement_67) {
    vec.push_back(std::make_unique<TestItem>(77));
    EXPECT_EQ(vec.back().value, 77);
}

TEST_F(PtrVectorTest_67, ClearRemovesAllElements_67) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    vec.push_back(std::make_unique<TestItem>(3));
    EXPECT_EQ(vec.size(), 3u);

    vec.clear();
    EXPECT_EQ(vec.size(), 0u);
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_67, ClearOnEmptyVectorIsNoOp_67) {
    vec.clear();
    EXPECT_EQ(vec.size(), 0u);
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_67, EmptyReturnsTrueForEmptyVector_67) {
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_67, EmptyReturnsFalseForNonEmptyVector_67) {
    vec.push_back(std::make_unique<TestItem>(5));
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_67, SubscriptOperatorAllowsModification_67) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec[0].value = 20;
    EXPECT_EQ(vec[0].value, 20);
}

TEST_F(PtrVectorTest_67, BackAllowsModification_67) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.back().value = 50;
    EXPECT_EQ(vec.back().value, 50);
    EXPECT_EQ(vec[0].value, 50);
}

TEST_F(PtrVectorTest_67, MoveConstructorTransfersOwnership_67) {
    vec.push_back(std::make_unique<TestItem>(100));
    vec.push_back(std::make_unique<TestItem>(200));

    YAML::ptr_vector<TestItem> moved(std::move(vec));
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].value, 100);
    EXPECT_EQ(moved[1].value, 200);
}

TEST_F(PtrVectorTest_67, MoveAssignmentTransfersOwnership_67) {
    vec.push_back(std::make_unique<TestItem>(100));
    vec.push_back(std::make_unique<TestItem>(200));

    YAML::ptr_vector<TestItem> other;
    other = std::move(vec);
    EXPECT_EQ(other.size(), 2u);
    EXPECT_EQ(other[0].value, 100);
    EXPECT_EQ(other[1].value, 200);
}

TEST_F(PtrVectorTest_67, CopyConstructorIsDeleted_67) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::ptr_vector<TestItem>>::value);
}

TEST_F(PtrVectorTest_67, CopyAssignmentIsDeleted_67) {
    EXPECT_FALSE(std::is_copy_assignable<YAML::ptr_vector<TestItem>>::value);
}

TEST_F(PtrVectorTest_67, PushBackAndClearMultipleTimes_67) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    EXPECT_EQ(vec.size(), 2u);

    vec.clear();
    EXPECT_EQ(vec.size(), 0u);
    EXPECT_TRUE(vec.empty());

    vec.push_back(std::make_unique<TestItem>(3));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 3);
}

TEST_F(PtrVectorTest_67, LargeNumberOfElements_67) {
    const std::size_t count = 1000;
    for (std::size_t i = 0; i < count; ++i) {
        vec.push_back(std::make_unique<TestItem>(static_cast<int>(i)));
    }
    EXPECT_EQ(vec.size(), count);
    for (std::size_t i = 0; i < count; ++i) {
        EXPECT_EQ(vec[i].value, static_cast<int>(i));
    }
    EXPECT_EQ(vec.back().value, static_cast<int>(count - 1));
}

}  // namespace
