#include <gtest/gtest.h>
#include <memory>
#include "ptr_vector.h"

namespace YAML {
namespace {

// A simple test type to use with ptr_vector
struct TestItem {
    int value;
    explicit TestItem(int v = 0) : value(v) {}
};

class PtrVectorTest_66 : public ::testing::Test {
protected:
    ptr_vector<TestItem> vec;
};

TEST_F(PtrVectorTest_66, DefaultConstructedIsEmpty_66) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_66, PushBackIncreasesSize_66) {
    vec.push_back(std::make_unique<TestItem>(1));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_66, PushBackMultipleElements_66) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.push_back(std::make_unique<TestItem>(20));
    vec.push_back(std::make_unique<TestItem>(30));
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_66, ClearMakesEmpty_66) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    EXPECT_EQ(vec.size(), 2u);

    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_66, ClearOnEmptyVector_66) {
    EXPECT_TRUE(vec.empty());
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_66, OperatorIndexReturnsCorrectElement_66) {
    vec.push_back(std::make_unique<TestItem>(100));
    vec.push_back(std::make_unique<TestItem>(200));
    vec.push_back(std::make_unique<TestItem>(300));

    EXPECT_EQ(vec[0].value, 100);
    EXPECT_EQ(vec[1].value, 200);
    EXPECT_EQ(vec[2].value, 300);
}

TEST_F(PtrVectorTest_66, BackReturnsLastElement_66) {
    vec.push_back(std::make_unique<TestItem>(42));
    EXPECT_EQ(vec.back().value, 42);

    vec.push_back(std::make_unique<TestItem>(99));
    EXPECT_EQ(vec.back().value, 99);
}

TEST_F(PtrVectorTest_66, OperatorIndexAllowsModification_66) {
    vec.push_back(std::make_unique<TestItem>(5));
    vec[0].value = 50;
    EXPECT_EQ(vec[0].value, 50);
}

TEST_F(PtrVectorTest_66, BackAllowsModification_66) {
    vec.push_back(std::make_unique<TestItem>(7));
    vec.back().value = 77;
    EXPECT_EQ(vec.back().value, 77);
    EXPECT_EQ(vec[0].value, 77);
}

TEST_F(PtrVectorTest_66, PushBackAfterClear_66) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    vec.clear();

    vec.push_back(std::make_unique<TestItem>(3));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 3);
    EXPECT_EQ(vec.back().value, 3);
}

TEST_F(PtrVectorTest_66, MoveConstruction_66) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.push_back(std::make_unique<TestItem>(20));

    ptr_vector<TestItem> moved(std::move(vec));
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].value, 10);
    EXPECT_EQ(moved[1].value, 20);
}

TEST_F(PtrVectorTest_66, MoveAssignment_66) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.push_back(std::make_unique<TestItem>(20));

    ptr_vector<TestItem> other;
    other.push_back(std::make_unique<TestItem>(99));

    other = std::move(vec);
    EXPECT_EQ(other.size(), 2u);
    EXPECT_EQ(other[0].value, 10);
    EXPECT_EQ(other[1].value, 20);
}

TEST_F(PtrVectorTest_66, SingleElementBackAndIndex_66) {
    vec.push_back(std::make_unique<TestItem>(555));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 555);
    EXPECT_EQ(vec.back().value, 555);
    // They should reference the same object
    EXPECT_EQ(&vec[0], &vec.back());
}

TEST_F(PtrVectorTest_66, EmptyAfterDefault_66) {
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_66, SizeIsConsistentWithPushBack_66) {
    for (int i = 0; i < 100; ++i) {
        vec.push_back(std::make_unique<TestItem>(i));
        EXPECT_EQ(vec.size(), static_cast<std::size_t>(i + 1));
    }
}

TEST_F(PtrVectorTest_66, ElementsRetainOrderAfterMultiplePushBacks_66) {
    for (int i = 0; i < 50; ++i) {
        vec.push_back(std::make_unique<TestItem>(i * 3));
    }
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(vec[i].value, i * 3);
    }
    EXPECT_EQ(vec.back().value, 49 * 3);
}

TEST_F(PtrVectorTest_66, ClearMultipleTimes_66) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.clear();
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

}  // namespace
}  // namespace YAML
