#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "ptr_vector.h"

namespace YAML {
namespace {

// A simple test type
struct TestObj {
    int value;
    explicit TestObj(int v) : value(v) {}
};

class PtrVectorTest_69 : public ::testing::Test {
protected:
    ptr_vector<TestObj> vec;
};

TEST_F(PtrVectorTest_69, DefaultConstructedIsEmpty_69) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_69, PushBackIncreasesSize_69) {
    vec.push_back(std::make_unique<TestObj>(1));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_FALSE(vec.empty());
}

TEST_F(PtrVectorTest_69, PushBackMultipleElements_69) {
    vec.push_back(std::make_unique<TestObj>(10));
    vec.push_back(std::make_unique<TestObj>(20));
    vec.push_back(std::make_unique<TestObj>(30));
    EXPECT_EQ(vec.size(), 3u);
}

TEST_F(PtrVectorTest_69, SubscriptOperatorReturnsCorrectElement_69) {
    vec.push_back(std::make_unique<TestObj>(42));
    vec.push_back(std::make_unique<TestObj>(99));
    EXPECT_EQ(vec[0].value, 42);
    EXPECT_EQ(vec[1].value, 99);
}

TEST_F(PtrVectorTest_69, BackReturnsLastElement_69) {
    vec.push_back(std::make_unique<TestObj>(1));
    vec.push_back(std::make_unique<TestObj>(2));
    vec.push_back(std::make_unique<TestObj>(3));
    EXPECT_EQ(vec.back().value, 3);
}

TEST_F(PtrVectorTest_69, BackAfterSinglePush_69) {
    vec.push_back(std::make_unique<TestObj>(77));
    EXPECT_EQ(vec.back().value, 77);
}

TEST_F(PtrVectorTest_69, ClearMakesVectorEmpty_69) {
    vec.push_back(std::make_unique<TestObj>(1));
    vec.push_back(std::make_unique<TestObj>(2));
    EXPECT_FALSE(vec.empty());
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_69, ClearOnEmptyVector_69) {
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_69, PushBackAfterClear_69) {
    vec.push_back(std::make_unique<TestObj>(5));
    vec.clear();
    vec.push_back(std::make_unique<TestObj>(10));
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0].value, 10);
}

TEST_F(PtrVectorTest_69, SubscriptOperatorReturnsMutableReference_69) {
    vec.push_back(std::make_unique<TestObj>(100));
    vec[0].value = 200;
    EXPECT_EQ(vec[0].value, 200);
}

TEST_F(PtrVectorTest_69, BackReturnsMutableReference_69) {
    vec.push_back(std::make_unique<TestObj>(50));
    vec.back().value = 60;
    EXPECT_EQ(vec.back().value, 60);
}

TEST_F(PtrVectorTest_69, MoveConstructor_69) {
    vec.push_back(std::make_unique<TestObj>(11));
    vec.push_back(std::make_unique<TestObj>(22));

    ptr_vector<TestObj> vec2(std::move(vec));
    EXPECT_EQ(vec2.size(), 2u);
    EXPECT_EQ(vec2[0].value, 11);
    EXPECT_EQ(vec2[1].value, 22);
}

TEST_F(PtrVectorTest_69, MoveAssignment_69) {
    vec.push_back(std::make_unique<TestObj>(33));

    ptr_vector<TestObj> vec2;
    vec2.push_back(std::make_unique<TestObj>(44));

    vec2 = std::move(vec);
    EXPECT_EQ(vec2.size(), 1u);
    EXPECT_EQ(vec2[0].value, 33);
}

TEST_F(PtrVectorTest_69, EmptyOnDefaultConstructed_69) {
    EXPECT_TRUE(vec.empty());
}

TEST_F(PtrVectorTest_69, SizeOnDefaultConstructed_69) {
    EXPECT_EQ(vec.size(), 0u);
}

TEST_F(PtrVectorTest_69, LargeNumberOfElements_69) {
    const std::size_t count = 1000;
    for (std::size_t i = 0; i < count; ++i) {
        vec.push_back(std::make_unique<TestObj>(static_cast<int>(i)));
    }
    EXPECT_EQ(vec.size(), count);
    for (std::size_t i = 0; i < count; ++i) {
        EXPECT_EQ(vec[i].value, static_cast<int>(i));
    }
    EXPECT_EQ(vec.back().value, static_cast<int>(count - 1));
}

// Test with a different type to ensure template works
TEST(PtrVectorStringTest_69, WorksWithString_69) {
    ptr_vector<std::string> svec;
    svec.push_back(std::make_unique<std::string>("hello"));
    svec.push_back(std::make_unique<std::string>("world"));
    EXPECT_EQ(svec.size(), 2u);
    EXPECT_EQ(svec[0], "hello");
    EXPECT_EQ(svec[1], "world");
    EXPECT_EQ(svec.back(), "world");
}

// Verify that copy constructor and copy assignment are deleted (compile-time check is implicit;
// this test verifies the type traits)
TEST(PtrVectorTraitsTest_69, NotCopyable_69) {
    EXPECT_FALSE(std::is_copy_constructible<ptr_vector<TestObj>>::value);
    EXPECT_FALSE(std::is_copy_assignable<ptr_vector<TestObj>>::value);
}

TEST(PtrVectorTraitsTest_69, IsMovable_69) {
    EXPECT_TRUE(std::is_move_constructible<ptr_vector<TestObj>>::value);
    EXPECT_TRUE(std::is_move_assignable<ptr_vector<TestObj>>::value);
}

}  // namespace
}  // namespace YAML
