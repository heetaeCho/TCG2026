#include "util/no_destructor.h"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace leveldb {

// Test with a simple POD type (int)
TEST(NoDestructorTest_493, ConstructWithInt_493) {
  NoDestructor<int> instance(42);
  EXPECT_EQ(*instance.get(), 42);
}

// Test with zero value
TEST(NoDestructorTest_493, ConstructWithZero_493) {
  NoDestructor<int> instance(0);
  EXPECT_EQ(*instance.get(), 0);
}

// Test with negative value
TEST(NoDestructorTest_493, ConstructWithNegativeInt_493) {
  NoDestructor<int> instance(-100);
  EXPECT_EQ(*instance.get(), -100);
}

// Test with std::string
TEST(NoDestructorTest_493, ConstructWithString_493) {
  NoDestructor<std::string> instance("hello world");
  EXPECT_EQ(*instance.get(), "hello world");
}

// Test with empty string
TEST(NoDestructorTest_493, ConstructWithEmptyString_493) {
  NoDestructor<std::string> instance("");
  EXPECT_EQ(*instance.get(), "");
}

// Test with std::string constructed from char* and length
TEST(NoDestructorTest_493, ConstructWithStringFromCharPtrAndLength_493) {
  NoDestructor<std::string> instance("hello", 3);
  EXPECT_EQ(*instance.get(), "hel");
}

// Test get() returns non-null pointer
TEST(NoDestructorTest_493, GetReturnsNonNull_493) {
  NoDestructor<int> instance(5);
  EXPECT_NE(instance.get(), nullptr);
}

// Test that get() returns consistent pointer (same address on repeated calls)
TEST(NoDestructorTest_493, GetReturnsConsistentPointer_493) {
  NoDestructor<int> instance(10);
  int* ptr1 = instance.get();
  int* ptr2 = instance.get();
  EXPECT_EQ(ptr1, ptr2);
}

// Test with a struct that has multiple constructor args
struct TestStruct {
  int a;
  double b;
  std::string c;

  TestStruct(int a, double b, std::string c) : a(a), b(b), c(std::move(c)) {}
};

TEST(NoDestructorTest_493, ConstructWithMultipleArgs_493) {
  NoDestructor<TestStruct> instance(42, 3.14, "test");
  EXPECT_EQ(instance.get()->a, 42);
  EXPECT_DOUBLE_EQ(instance.get()->b, 3.14);
  EXPECT_EQ(instance.get()->c, "test");
}

// Test with default-constructible type
struct DefaultConstructible {
  int value = 99;
  DefaultConstructible() = default;
};

TEST(NoDestructorTest_493, ConstructWithDefaultConstructor_493) {
  NoDestructor<DefaultConstructible> instance;
  EXPECT_EQ(instance.get()->value, 99);
}

// Test that the destructor of the held object is NOT called
// We use a static counter to detect this
static int destructor_call_count_493 = 0;

struct DestructorTracker {
  int value;
  explicit DestructorTracker(int v) : value(v) {}
  ~DestructorTracker() { destructor_call_count_493++; }
};

TEST(NoDestructorTest_493, DestructorNotCalled_493) {
  destructor_call_count_493 = 0;
  {
    // Allocate on heap so we can destroy the NoDestructor wrapper
    auto* instance = new NoDestructor<DestructorTracker>(123);
    EXPECT_EQ(instance->get()->value, 123);
    int count_before = destructor_call_count_493;
    delete instance;
    // The destructor of DestructorTracker should NOT be called
    // because NoDestructor's purpose is to prevent destruction
    EXPECT_EQ(destructor_call_count_493, count_before);
  }
}

// Test with std::vector
TEST(NoDestructorTest_493, ConstructWithVector_493) {
  NoDestructor<std::vector<int>> instance(std::initializer_list<int>{1, 2, 3, 4, 5});
  EXPECT_EQ(instance.get()->size(), 5u);
  EXPECT_EQ((*instance.get())[0], 1);
  EXPECT_EQ((*instance.get())[4], 5);
}

// Test modification through get() pointer
TEST(NoDestructorTest_493, ModifyThroughGet_493) {
  NoDestructor<int> instance(10);
  *instance.get() = 20;
  EXPECT_EQ(*instance.get(), 20);
}

// Test with large type
struct LargeType {
  char data[1024];
  int marker;
  explicit LargeType(int m) : marker(m) {
    std::memset(data, 0, sizeof(data));
  }
};

TEST(NoDestructorTest_493, ConstructWithLargeType_493) {
  NoDestructor<LargeType> instance(42);
  EXPECT_EQ(instance.get()->marker, 42);
}

// Test with uint64_t boundary values
TEST(NoDestructorTest_493, ConstructWithMaxUint64_493) {
  NoDestructor<uint64_t> instance(UINT64_MAX);
  EXPECT_EQ(*instance.get(), UINT64_MAX);
}

TEST(NoDestructorTest_493, ConstructWithMinInt64_493) {
  NoDestructor<int64_t> instance(INT64_MIN);
  EXPECT_EQ(*instance.get(), INT64_MIN);
}

// Test with bool
TEST(NoDestructorTest_493, ConstructWithBoolTrue_493) {
  NoDestructor<bool> instance(true);
  EXPECT_TRUE(*instance.get());
}

TEST(NoDestructorTest_493, ConstructWithBoolFalse_493) {
  NoDestructor<bool> instance(false);
  EXPECT_FALSE(*instance.get());
}

// Test with move-only type
struct MoveOnlyType {
  std::unique_ptr<int> ptr;
  explicit MoveOnlyType(std::unique_ptr<int> p) : ptr(std::move(p)) {}
};

TEST(NoDestructorTest_493, ConstructWithMoveOnlyType_493) {
  auto p = std::make_unique<int>(77);
  NoDestructor<MoveOnlyType> instance(std::move(p));
  EXPECT_NE(instance.get()->ptr, nullptr);
  EXPECT_EQ(*instance.get()->ptr, 77);
}

// Test alignment - get() should return a properly aligned pointer
TEST(NoDestructorTest_493, ProperAlignment_493) {
  NoDestructor<double> instance(1.5);
  uintptr_t addr = reinterpret_cast<uintptr_t>(instance.get());
  EXPECT_EQ(addr % alignof(double), 0u);
}

// Test with a type that has higher alignment requirement
struct alignas(64) HighlyAligned {
  int value;
  explicit HighlyAligned(int v) : value(v) {}
};

TEST(NoDestructorTest_493, HighAlignmentType_493) {
  NoDestructor<HighlyAligned> instance(55);
  uintptr_t addr = reinterpret_cast<uintptr_t>(instance.get());
  EXPECT_EQ(addr % alignof(HighlyAligned), 0u);
  EXPECT_EQ(instance.get()->value, 55);
}

}  // namespace leveldb
