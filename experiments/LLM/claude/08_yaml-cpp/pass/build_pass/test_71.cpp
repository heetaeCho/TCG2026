#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the header under test
#include "ptr_vector.h"

namespace {

// A simple test type to use with ptr_vector
struct TestItem {
    int value;
    std::string name;

    TestItem() : value(0), name("default") {}
    TestItem(int v, const std::string& n) : value(v), name(n) {}
};

// Test fixture
class PtrVectorTest_71 : public ::testing::Test {
protected:
    YAML::ptr_vector<TestItem> vec;
};

// ==================== Construction Tests ====================

TEST_F(PtrVectorTest_71, DefaultConstructorCreatesEmptyVector_71) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

// ==================== push_back Tests ====================

TEST_F(PtrVectorTest_71, PushBackIncreasesSize_71) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_71, PushBackMultipleElements_71) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    vec.push_back(std::make_unique<TestItem>(2, "second"));
    vec.push_back(std::make_unique<TestItem>(3, "third"));
    EXPECT_EQ(vec.size(), 3u);
}

// ==================== back() Tests ====================

TEST_F(PtrVectorTest_71, BackReturnsLastElement_71) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    vec.push_back(std::make_unique<TestItem>(2, "second"));
    
    TestItem& item = vec.back();
    EXPECT_EQ(item.value, 2);
    EXPECT_EQ(item.name, "second");
}

TEST_F(PtrVectorTest_71, BackReturnsSingleElement_71) {
    vec.push_back(std::make_unique<TestItem>(42, "only"));
    
    TestItem& item = vec.back();
    EXPECT_EQ(item.value, 42);
    EXPECT_EQ(item.name, "only");
}

TEST_F(PtrVectorTest_71, BackReturnsReference_71) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    
    TestItem& item = vec.back();
    item.value = 100;
    item.name = "modified";
    
    // Verify modification persists through back()
    EXPECT_EQ(vec.back().value, 100);
    EXPECT_EQ(vec.back().name, "modified");
}

// ==================== operator[] Tests ====================

TEST_F(PtrVectorTest_71, SubscriptOperatorAccessesCorrectElement_71) {
    vec.push_back(std::make_unique<TestItem>(10, "zero"));
    vec.push_back(std::make_unique<TestItem>(20, "one"));
    vec.push_back(std::make_unique<TestItem>(30, "two"));
    
    EXPECT_EQ(vec[0].value, 10);
    EXPECT_EQ(vec[0].name, "zero");
    EXPECT_EQ(vec[1].value, 20);
    EXPECT_EQ(vec[1].name, "one");
    EXPECT_EQ(vec[2].value, 30);
    EXPECT_EQ(vec[2].name, "two");
}

TEST_F(PtrVectorTest_71, SubscriptOperatorReturnsReference_71) {
    vec.push_back(std::make_unique<TestItem>(1, "original"));
    
    vec[0].value = 999;
    vec[0].name = "changed";
    
    EXPECT_EQ(vec[0].value, 999);
    EXPECT_EQ(vec[0].name, "changed");
}

// ==================== empty() Tests ====================

TEST_F(PtrVectorTest_71, EmptyReturnsTrueForNewVector_71) {
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_71, EmptyReturnsFalseAfterPushBack_71) {
    vec.push_back(std::make_unique<TestItem>());
    EXPECT_FALSE(vec.empty());
}

// ==================== size() Tests ====================

TEST_F(PtrVectorTest_71, SizeIsZeroForNewVector_71) {
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_71, SizeReflectsNumberOfElements_71) {
    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::make_unique<TestItem>(i, "item"));
    }
    EXPECT_EQ(vec.size(), 5u);
}

// ==================== clear() Tests ====================

TEST_F(PtrVectorTest_71, ClearEmptiesTheVector_71) {
    vec.push_back(std::make_unique<TestItem>(1, "a"));
    vec.push_back(std::make_unique<TestItem>(2, "b"));
    
    vec.clear();
    
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_71, ClearOnEmptyVectorIsNoOp_71) {
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_71, CanAddElementsAfterClear_71) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    vec.clear();
    
    vec.push_back(std::make_unique<TestItem>(2, "second"));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 2);
    EXPECT_EQ(vec[0].name, "second");
}

// ==================== Move Semantics Tests ====================

TEST_F(PtrVectorTest_71, MoveConstructorTransfersOwnership_71) {
    vec.push_back(std::make_unique<TestItem>(1, "a"));
    vec.push_back(std::make_unique<TestItem>(2, "b"));
    
    YAML::ptr_vector<TestItem> moved(std::move(vec));
    
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].value, 1);
    EXPECT_EQ(moved[1].value, 2);
}

TEST_F(PtrVectorTest_71, MoveAssignmentTransfersOwnership_71) {
    vec.push_back(std::make_unique<TestItem>(1, "a"));
    vec.push_back(std::make_unique<TestItem>(2, "b"));
    
    YAML::ptr_vector<TestItem> other;
    other = std::move(vec);
    
    EXPECT_EQ(other.size(), 2u);
    EXPECT_EQ(other[0].value, 1);
    EXPECT_EQ(other[1].value, 2);
}

// ==================== Consistency Tests ====================

TEST_F(PtrVectorTest_71, BackAndSubscriptLastAreConsistent_71) {
    vec.push_back(std::make_unique<TestItem>(10, "ten"));
    vec.push_back(std::make_unique<TestItem>(20, "twenty"));
    vec.push_back(std::make_unique<TestItem>(30, "thirty"));
    
    EXPECT_EQ(&vec.back(), &vec[vec.size() - 1]);
}

TEST_F(PtrVectorTest_71, LargeNumberOfElements_71) {
    const std::size_t count = 1000;
    for (std::size_t i = 0; i < count; ++i) {
        vec.push_back(std::make_unique<TestItem>(static_cast<int>(i), "item"));
    }
    
    EXPECT_EQ(vec.size(), count);
    
    for (std::size_t i = 0; i < count; ++i) {
        EXPECT_EQ(vec[i].value, static_cast<int>(i));
    }
    
    EXPECT_EQ(vec.back().value, static_cast<int>(count - 1));
}

// ==================== Test with different types ====================

class PtrVectorIntTest_71 : public ::testing::Test {
protected:
    YAML::ptr_vector<int> vec;
};

TEST_F(PtrVectorIntTest_71, WorksWithPrimitiveTypes_71) {
    vec.push_back(std::make_unique<int>(42));
    vec.push_back(std::make_unique<int>(100));
    
    EXPECT_EQ(vec.size(), 2u);
    EXPECT_EQ(vec[0], 42);
    EXPECT_EQ(vec[1], 100);
    EXPECT_EQ(vec.back(), 100);
}

// ==================== Destruction / clear verifies cleanup ====================

TEST_F(PtrVectorTest_71, ClearDestroysObjects_71) {
    static int destructorCount = 0;
    
    struct Tracked {
        int id;
        int* counter;
        Tracked(int i, int* c) : id(i), counter(c) {}
        ~Tracked() { ++(*counter); }
    };

    {
        YAML::ptr_vector<Tracked> trackedVec;
        destructorCount = 0;
        trackedVec.push_back(std::make_unique<Tracked>(1, &destructorCount));
        trackedVec.push_back(std::make_unique<Tracked>(2, &destructorCount));
        
        trackedVec.clear();
        EXPECT_EQ(destructorCount, 2);
    }
}

TEST_F(PtrVectorTest_71, DestructorDestroysObjects_71) {
    static int destructorCount = 0;
    
    struct Tracked {
        int* counter;
        Tracked(int* c) : counter(c) {}
        ~Tracked() { ++(*counter); }
    };

    destructorCount = 0;
    {
        YAML::ptr_vector<Tracked> trackedVec;
        trackedVec.push_back(std::make_unique<Tracked>(&destructorCount));
        trackedVec.push_back(std::make_unique<Tracked>(&destructorCount));
        trackedVec.push_back(std::make_unique<Tracked>(&destructorCount));
    }
    EXPECT_EQ(destructorCount, 3);
}

}  // namespace
