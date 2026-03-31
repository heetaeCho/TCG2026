#include "gtest/gtest.h"
#include "ptr_vector.h"
#include <memory>
#include <string>

// A simple test type
struct TestItem {
    int value;
    explicit TestItem(int v = 0) : value(v) {}
};

class PtrVectorTest_68 : public ::testing::Test {
protected:
    YAML::ptr_vector<TestItem> vec;
};

// --- Empty / Size tests ---

TEST_F(PtrVectorTest_68, DefaultConstructedIsEmpty_68) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_68, NotEmptyAfterPushBack_68) {
    vec.push_back(std::make_unique<TestItem>(1));
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.size(), 1u);
}

TEST_F(PtrVectorTest_68, SizeIncreasesWithMultiplePushBacks_68) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    vec.push_back(std::make_unique<TestItem>(3));
    EXPECT_EQ(vec.size(), 3u);
}

// --- push_back and operator[] tests ---

TEST_F(PtrVectorTest_68, PushBackAndAccessByIndex_68) {
    vec.push_back(std::make_unique<TestItem>(42));
    EXPECT_EQ(vec[0].value, 42);
}

TEST_F(PtrVectorTest_68, MultipleElementsAccessedByIndex_68) {
    vec.push_back(std::make_unique<TestItem>(10));
    vec.push_back(std::make_unique<TestItem>(20));
    vec.push_back(std::make_unique<TestItem>(30));
    EXPECT_EQ(vec[0].value, 10);
    EXPECT_EQ(vec[1].value, 20);
    EXPECT_EQ(vec[2].value, 30);
}

// --- back() tests ---

TEST_F(PtrVectorTest_68, BackReturnsMostRecentlyAdded_68) {
    vec.push_back(std::make_unique<TestItem>(5));
    EXPECT_EQ(vec.back().value, 5);
    
    vec.push_back(std::make_unique<TestItem>(99));
    EXPECT_EQ(vec.back().value, 99);
}

// --- clear() tests ---

TEST_F(PtrVectorTest_68, ClearMakesVectorEmpty_68) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.push_back(std::make_unique<TestItem>(2));
    EXPECT_FALSE(vec.empty());
    
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_68, ClearOnAlreadyEmptyVector_68) {
    EXPECT_TRUE(vec.empty());
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_68, CanAddElementsAfterClear_68) {
    vec.push_back(std::make_unique<TestItem>(1));
    vec.clear();
    
    vec.push_back(std::make_unique<TestItem>(100));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 100);
}

// --- Modification through references ---

TEST_F(PtrVectorTest_68, ModifyElementThroughIndex_68) {
    vec.push_back(std::make_unique<TestItem>(7));
    vec[0].value = 77;
    EXPECT_EQ(vec[0].value, 77);
}

TEST_F(PtrVectorTest_68, ModifyElementThroughBack_68) {
    vec.push_back(std::make_unique<TestItem>(3));
    vec.back().value = 33;
    EXPECT_EQ(vec[0].value, 33);
}

// --- Move semantics ---

TEST_F(PtrVectorTest_68, MoveConstructor_68) {
    vec.push_back(std::make_unique<TestItem>(11));
    vec.push_back(std::make_unique<TestItem>(22));
    
    YAML::ptr_vector<TestItem> moved(std::move(vec));
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].value, 11);
    EXPECT_EQ(moved[1].value, 22);
}

TEST_F(PtrVectorTest_68, MoveAssignment_68) {
    vec.push_back(std::make_unique<TestItem>(55));
    
    YAML::ptr_vector<TestItem> other;
    other.push_back(std::make_unique<TestItem>(66));
    other = std::move(vec);
    
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other[0].value, 55);
}

// --- Boundary: single element ---

TEST_F(PtrVectorTest_68, SingleElementBackAndIndexAreSame_68) {
    vec.push_back(std::make_unique<TestItem>(999));
    EXPECT_EQ(&vec[0], &vec.back());
}

// --- Large number of elements ---

TEST_F(PtrVectorTest_68, LargeNumberOfElements_68) {
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

// --- Different type ---

TEST_F(PtrVectorTest_68, WorksWithStringType_68) {
    YAML::ptr_vector<std::string> svec;
    svec.push_back(std::make_unique<std::string>("hello"));
    svec.push_back(std::make_unique<std::string>("world"));
    
    EXPECT_EQ(svec.size(), 2u);
    EXPECT_EQ(svec[0], "hello");
    EXPECT_EQ(svec[1], "world");
    EXPECT_EQ(svec.back(), "world");
    
    svec.clear();
    EXPECT_TRUE(svec.empty());
}
