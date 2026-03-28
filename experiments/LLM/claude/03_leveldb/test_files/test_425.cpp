#include "util/no_destructor.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Test with a simple integer type
TEST(NoDestructorTest_425, ConstructWithInt_425) {
  NoDestructor<int> instance(42);
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_EQ(*instance.get(), 42);
}

// Test with zero value
TEST(NoDestructorTest_425, ConstructWithZero_425) {
  NoDestructor<int> instance(0);
  EXPECT_EQ(*instance.get(), 0);
}

// Test with negative value
TEST(NoDestructorTest_425, ConstructWithNegativeInt_425) {
  NoDestructor<int> instance(-100);
  EXPECT_EQ(*instance.get(), -100);
}

// Test with std::string
TEST(NoDestructorTest_425, ConstructWithString_425) {
  NoDestructor<std::string> instance("hello world");
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_EQ(*instance.get(), "hello world");
}

// Test with empty string
TEST(NoDestructorTest_425, ConstructWithEmptyString_425) {
  NoDestructor<std::string> instance("");
  EXPECT_EQ(*instance.get(), "");
}

// Test with std::vector
TEST(NoDestructorTest_425, ConstructWithVector_425) {
  NoDestructor<std::vector<int>> instance(std::initializer_list<int>{1, 2, 3, 4, 5});
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_EQ(instance.get()->size(), 5u);
  EXPECT_EQ((*instance.get())[0], 1);
  EXPECT_EQ((*instance.get())[4], 5);
}

// Test with empty vector (default constructed)
TEST(NoDestructorTest_425, ConstructWithEmptyVector_425) {
  NoDestructor<std::vector<int>> instance;
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_TRUE(instance.get()->empty());
}

// Test that get() returns consistent pointer
TEST(NoDestructorTest_425, GetReturnsConsistentPointer_425) {
  NoDestructor<int> instance(99);
  int* ptr1 = instance.get();
  int* ptr2 = instance.get();
  EXPECT_EQ(ptr1, ptr2);
}

// Test modifying the stored value through get()
TEST(NoDestructorTest_425, ModifyThroughGet_425) {
  NoDestructor<int> instance(10);
  EXPECT_EQ(*instance.get(), 10);
  *instance.get() = 20;
  EXPECT_EQ(*instance.get(), 20);
}

// Test with a struct that has multiple constructor args
struct TestStruct {
  int a;
  double b;
  std::string c;
  TestStruct(int a, double b, std::string c) : a(a), b(b), c(std::move(c)) {}
};

TEST(NoDestructorTest_425, ConstructWithMultipleArgs_425) {
  NoDestructor<TestStruct> instance(42, 3.14, "test");
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_EQ(instance.get()->a, 42);
  EXPECT_DOUBLE_EQ(instance.get()->b, 3.14);
  EXPECT_EQ(instance.get()->c, "test");
}

// Test with a large type (boundary condition)
TEST(NoDestructorTest_425, ConstructWithLargeType_425) {
  NoDestructor<std::vector<int>> instance(1000, 42);
  ASSERT_NE(instance.get(), nullptr);
  EXPECT_EQ(instance.get()->size(), 1000u);
  for (int val : *instance.get()) {
    EXPECT_EQ(val, 42);
  }
}

// Test with bool type
TEST(NoDestructorTest_425, ConstructWithBoolTrue_425) {
  NoDestructor<bool> instance(true);
  EXPECT_TRUE(*instance.get());
}

TEST(NoDestructorTest_425, ConstructWithBoolFalse_425) {
  NoDestructor<bool> instance(false);
  EXPECT_FALSE(*instance.get());
}

// Test with uint64_t boundary values
TEST(NoDestructorTest_425, ConstructWithMaxUint64_425) {
  NoDestructor<uint64_t> instance(UINT64_MAX);
  EXPECT_EQ(*instance.get(), UINT64_MAX);
}

TEST(NoDestructorTest_425, ConstructWithMinUint64_425) {
  NoDestructor<uint64_t> instance(0ULL);
  EXPECT_EQ(*instance.get(), 0ULL);
}

// Test that destructor of contained type is NOT called
// We verify this by checking that a type with a destructor that sets a flag
// does NOT have its destructor called when NoDestructor goes out of scope
static bool destructor_called = false;

struct DestructorTracker {
  int value;
  explicit DestructorTracker(int v) : value(v) { destructor_called = false; }
  ~DestructorTracker() { destructor_called = true; }
};

TEST(NoDestructorTest_425, DestructorNotCalled_425) {
  destructor_called = false;
  {
    NoDestructor<DestructorTracker> instance(42);
    EXPECT_EQ(instance.get()->value, 42);
    EXPECT_FALSE(destructor_called);
  }
  // The destructor of DestructorTracker should NOT be called
  // because NoDestructor prevents it
  EXPECT_FALSE(destructor_called);
}

// Test with double type
TEST(NoDestructorTest_425, ConstructWithDouble_425) {
  NoDestructor<double> instance(2.71828);
  EXPECT_DOUBLE_EQ(*instance.get(), 2.71828);
}

// Test with char type
TEST(NoDestructorTest_425, ConstructWithChar_425) {
  NoDestructor<char> instance('A');
  EXPECT_EQ(*instance.get(), 'A');
}

// Test modifying string through get()
TEST(NoDestructorTest_425, ModifyStringThroughGet_425) {
  NoDestructor<std::string> instance("initial");
  EXPECT_EQ(*instance.get(), "initial");
  instance.get()->append(" modified");
  EXPECT_EQ(*instance.get(), "initial modified");
}

}  // namespace leveldb
