#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the header under test
#include "ptr_vector.h"

// A simple test class to use as the template parameter
struct TestItem {
    int value;
    std::string name;
    
    TestItem() : value(0), name("default") {}
    TestItem(int v, const std::string& n) : value(v), name(n) {}
};

class PtrVectorTest_70 : public ::testing::Test {
protected:
    YAML::ptr_vector<TestItem> vec;
};

// Test that a newly constructed ptr_vector is empty
TEST_F(PtrVectorTest_70, DefaultConstructorCreatesEmptyVector_70) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

// Test push_back increases size
TEST_F(PtrVectorTest_70, PushBackIncreasesSize_70) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}

// Test push_back multiple elements
TEST_F(PtrVectorTest_70, PushBackMultipleElements_70) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    vec.push_back(std::make_unique<TestItem>(2, "second"));
    vec.push_back(std::make_unique<TestItem>(3, "third"));
    EXPECT_EQ(vec.size(), 3u);
}

// Test operator[] returns correct element
TEST_F(PtrVectorTest_70, OperatorBracketReturnsCorrectElement_70) {
    vec.push_back(std::make_unique<TestItem>(10, "ten"));
    vec.push_back(std::make_unique<TestItem>(20, "twenty"));
    vec.push_back(std::make_unique<TestItem>(30, "thirty"));
    
    EXPECT_EQ(vec[0].value, 10);
    EXPECT_EQ(vec[0].name, "ten");
    EXPECT_EQ(vec[1].value, 20);
    EXPECT_EQ(vec[1].name, "twenty");
    EXPECT_EQ(vec[2].value, 30);
    EXPECT_EQ(vec[2].name, "thirty");
}

// Test operator[] allows modification
TEST_F(PtrVectorTest_70, OperatorBracketAllowsModification_70) {
    vec.push_back(std::make_unique<TestItem>(1, "original"));
    vec[0].value = 42;
    vec[0].name = "modified";
    
    EXPECT_EQ(vec[0].value, 42);
    EXPECT_EQ(vec[0].name, "modified");
}

// Test back() returns the last element
TEST_F(PtrVectorTest_70, BackReturnsLastElement_70) {
    vec.push_back(std::make_unique<TestItem>(1, "first"));
    vec.push_back(std::make_unique<TestItem>(2, "second"));
    vec.push_back(std::make_unique<TestItem>(3, "last"));
    
    EXPECT_EQ(vec.back().value, 3);
    EXPECT_EQ(vec.back().name, "last");
}

// Test back() with single element
TEST_F(PtrVectorTest_70, BackWithSingleElement_70) {
    vec.push_back(std::make_unique<TestItem>(99, "only"));
    EXPECT_EQ(vec.back().value, 99);
    EXPECT_EQ(vec.back().name, "only");
}

// Test back() allows modification
TEST_F(PtrVectorTest_70, BackAllowsModification_70) {
    vec.push_back(std::make_unique<TestItem>(1, "original"));
    vec.back().value = 100;
    vec.back().name = "changed";
    
    EXPECT_EQ(vec[0].value, 100);
    EXPECT_EQ(vec[0].name, "changed");
}

// Test clear empties the vector
TEST_F(PtrVectorTest_70, ClearEmptiesVector_70) {
    vec.push_back(std::make_unique<TestItem>(1, "a"));
    vec.push_back(std::make_unique<TestItem>(2, "b"));
    vec.push_back(std::make_unique<TestItem>(3, "c"));
    
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

// Test clear on already empty vector
TEST_F(PtrVectorTest_70, ClearOnEmptyVector_70) {
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

// Test push_back after clear
TEST_F(PtrVectorTest_70, PushBackAfterClear_70) {
    vec.push_back(std::make_unique<TestItem>(1, "before"));
    vec.clear();
    vec.push_back(std::make_unique<TestItem>(2, "after"));
    
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 2);
    EXPECT_EQ(vec[0].name, "after");
}

// Test empty returns true for empty vector, false otherwise
TEST_F(PtrVectorTest_70, EmptyReflectsState_70) {
    EXPECT_TRUE(vec.empty());
    vec.push_back(std::make_unique<TestItem>());
    EXPECT_FALSE(vec.empty());
    vec.clear();
    EXPECT_TRUE(vec.empty());
}

// Test move constructor
TEST_F(PtrVectorTest_70, MoveConstructor_70) {
    vec.push_back(std::make_unique<TestItem>(1, "one"));
    vec.push_back(std::make_unique<TestItem>(2, "two"));
    
    YAML::ptr_vector<TestItem> moved(std::move(vec));
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved[0].value, 1);
    EXPECT_EQ(moved[1].value, 2);
}

// Test move assignment operator
TEST_F(PtrVectorTest_70, MoveAssignment_70) {
    vec.push_back(std::make_unique<TestItem>(5, "five"));
    
    YAML::ptr_vector<TestItem> other;
    other.push_back(std::make_unique<TestItem>(10, "ten"));
    
    other = std::move(vec);
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other[0].value, 5);
    EXPECT_EQ(other[0].name, "five");
}

// Test with int type
TEST(PtrVectorIntTest_70, WorksWithIntType_70) {
    YAML::ptr_vector<int> intVec;
    intVec.push_back(std::make_unique<int>(42));
    intVec.push_back(std::make_unique<int>(100));
    
    EXPECT_EQ(intVec.size(), 2u);
    EXPECT_EQ(intVec[0], 42);
    EXPECT_EQ(intVec[1], 100);
    EXPECT_EQ(intVec.back(), 100);
}

// Test sequential access pattern
TEST_F(PtrVectorTest_70, SequentialAccessAllElements_70) {
    const int N = 100;
    for (int i = 0; i < N; i++) {
        vec.push_back(std::make_unique<TestItem>(i, std::to_string(i)));
    }
    
    EXPECT_EQ(vec.size(), static_cast<std::size_t>(N));
    
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(vec[i].value, i);
        EXPECT_EQ(vec[i].name, std::to_string(i));
    }
}

// Test that back and operator[size-1] return the same element
TEST_F(PtrVectorTest_70, BackConsistentWithLastIndex_70) {
    vec.push_back(std::make_unique<TestItem>(1, "a"));
    vec.push_back(std::make_unique<TestItem>(2, "b"));
    vec.push_back(std::make_unique<TestItem>(3, "c"));
    
    EXPECT_EQ(&vec.back(), &vec[vec.size() - 1]);
}

// Test operator[] returns reference (verify it's the same object)
TEST_F(PtrVectorTest_70, OperatorBracketReturnsReference_70) {
    vec.push_back(std::make_unique<TestItem>(7, "seven"));
    
    TestItem& ref1 = vec[0];
    TestItem& ref2 = vec[0];
    
    EXPECT_EQ(&ref1, &ref2);
}

// Test size boundary - zero elements
TEST_F(PtrVectorTest_70, SizeZeroBoundary_70) {
    EXPECT_EQ(vec.size(), 0u);
}

// Test size boundary - one element
TEST_F(PtrVectorTest_70, SizeOneBoundary_70) {
    vec.push_back(std::make_unique<TestItem>());
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}
