// File: greallocn_test_15.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstdlib>

// Redirect the external collaborators used by the inline function to test doubles
#define gfree test_gfree
#define grealloc test_grealloc
#define checkedMultiply test_checkedMultiply
#include "./TestProjects/poppler/goo/gmem.h"
#undef gfree
#undef grealloc
#undef checkedMultiply

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

namespace {

struct GreallocnDepsMock {
  MOCK_METHOD(void, Free, (void* p));
  MOCK_METHOD(void*, Realloc, (void* p, int size, bool checkoverflow));
  MOCK_METHOD(bool, CheckedMultiply, (int count, int size, int* bytes));
};

GreallocnDepsMock* g_mock = nullptr;

// Test-double implementations that greallocn() (in this TU) will call.
void test_gfree(void* p) {
  if (g_mock) g_mock->Free(p);
}

void* test_grealloc(void* p, int size, bool checkoverflow) {
  return g_mock ? g_mock->Realloc(p, size, checkoverflow) : nullptr;
}

bool test_checkedMultiply(int count, int size, int* bytes) {
  return g_mock ? g_mock->CheckedMultiply(count, size, bytes) : true;
}

class GreallocnTest_15 : public ::testing::Test {
protected:
  StrictMock<GreallocnDepsMock> mock_;

  void SetUp() override { g_mock = &mock_; }
  void TearDown() override { g_mock = nullptr; }
};

}  // namespace

TEST_F(GreallocnTest_15, CountZeroFreesAndReturnsNullptr_15) {
  void* p = reinterpret_cast<void*>(0x1234);

  EXPECT_CALL(mock_, Free(p)).Times(1);
  EXPECT_CALL(mock_, Realloc(_, _, _)).Times(0);
  EXPECT_CALL(mock_, CheckedMultiply(_, _, _)).Times(0);

  EXPECT_EQ(greallocn(p, 0, 7, false), nullptr);
}

TEST_F(GreallocnTest_15, NegativeCountWithCheckoverflowTrueFreesAndReturnsNullptr_15) {
  void* p = reinterpret_cast<void*>(0xBEEF);

  EXPECT_CALL(mock_, Free(p)).Times(1);
  EXPECT_CALL(mock_, Realloc(_, _, _)).Times(0);
  EXPECT_CALL(mock_, CheckedMultiply(_, _, _)).Times(0);

  EXPECT_EQ(greallocn(p, -1, 10, true), nullptr);
}

TEST_F(GreallocnTest_15, NonPositiveSizeWithCheckoverflowTrueFreesAndReturnsNullptr_15) {
  void* p = reinterpret_cast<void*>(0xCAFE);

  EXPECT_CALL(mock_, Free(p)).Times(1);
  EXPECT_CALL(mock_, Realloc(_, _, _)).Times(0);
  EXPECT_CALL(mock_, CheckedMultiply(_, _, _)).Times(0);

  EXPECT_EQ(greallocn(p, 3, 0, true), nullptr);
}

TEST_F(GreallocnTest_15, BogusArgsWithCheckoverflowFalseAborts_15) {
  // Ensure greallocn reaches the "Bogus memory allocation size" abort path.
  EXPECT_CALL(mock_, Free(_)).Times(0);
  EXPECT_CALL(mock_, Realloc(_, _, _)).Times(0);
  EXPECT_CALL(mock_, CheckedMultiply(_, _, _)).Times(0);

  // The function writes an error message and aborts when checkoverflow==false.
  EXPECT_DEATH(
      {
        (void)greallocn(nullptr, -1, 1, false);
      },
      "Bogus memory allocation size");
}

TEST_F(GreallocnTest_15, CheckedMultiplyOverflowWithCheckoverflowTrueFreesAndReturnsNullptr_15) {
  void* p = reinterpret_cast<void*>(0x1111);

  EXPECT_CALL(mock_, CheckedMultiply(1000000, 1000000, _)).WillOnce(Return(true));
  EXPECT_CALL(mock_, Free(p)).Times(1);
  EXPECT_CALL(mock_, Realloc(_, _, _)).Times(0);

  EXPECT_EQ(greallocn(p, 1000000, 1000000, true), nullptr);
}

TEST_F(GreallocnTest_15, GreallocSuccessReturnsPointerAndDoesNotFree_15) {
  void* p = reinterpret_cast<void*>(0x2222);
  void* q = reinterpret_cast<void*>(0x3333);
  const int count = 3;
  const int size = 4;
  const int bytes = 12;

  EXPECT_CALL(mock_, CheckedMultiply(count, size, _))
      .WillOnce(DoAll(SetArgPointee<2>(bytes), Return(false)));
  EXPECT_CALL(mock_, Realloc(p, bytes, false)).WillOnce(Return(q));
  EXPECT_CALL(mock_, Free(_)).Times(0);

  EXPECT_EQ(greallocn(p, count, size, false), q);
}

TEST_F(GreallocnTest_15, GreallocFailureFreesOriginalPointerAndReturnsNullptr_15) {
  void* p = reinterpret_cast<void*>(0x4444);
  const int count = 2;
  const int size = 8;
  const int bytes = 16;

  EXPECT_CALL(mock_, CheckedMultiply(count, size, _))
      .WillOnce(DoAll(SetArgPointee<2>(bytes), Return(false)));
  EXPECT_CALL(mock_, Realloc(p, bytes, true)).WillOnce(Return(nullptr));
  EXPECT_CALL(mock_, Free(p)).Times(1);

  EXPECT_EQ(greallocn(p, count, size, true), nullptr);
}