// File: test_copyString_17.cpp
//
// Unit tests for:
//   inline char *copyString(const char *s) {
//     char *r = static_cast<char *>(gmalloc(std::strlen(s) + 1, false));
//     return std::strcpy(r, s);
//   }
//
// Constraints respected:
// - Treats copyString as a black box: validates only observable behavior.
// - Uses Google Mock only to verify the external collaborator call (gmalloc).
// - Does not access any private/internal state.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <cstring>
#include <string>

// Include the real header under test.
#include "TestProjects/poppler/goo/gmem.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SaveArg;

// ---- External collaborator seam: gmalloc ----
// We provide a link-time override for gmalloc so we can verify interactions.
// This is an external function used by copyString, so mocking it is allowed.

class MockGmalloc_17 {
 public:
  MOCK_METHOD(void*, Call, (size_t size, bool flag), ());
};

static MockGmalloc_17* g_gmalloc_mock_17 = nullptr;

void* gmalloc(size_t size, bool flag) {
  if (g_gmalloc_mock_17) {
    return g_gmalloc_mock_17->Call(size, flag);
  }
  // Fallback if tests ever call without installing a mock.
  return std::malloc(size);
}

class ScopedGmallocMock_17 {
 public:
  explicit ScopedGmallocMock_17(MockGmalloc_17* mock) : prev_(g_gmalloc_mock_17) { g_gmalloc_mock_17 = mock; }
  ~ScopedGmallocMock_17() { g_gmalloc_mock_17 = prev_; }

  ScopedGmallocMock_17(const ScopedGmallocMock_17&) = delete;
  ScopedGmallocMock_17& operator=(const ScopedGmallocMock_17&) = delete;

 private:
  MockGmalloc_17* prev_;
};

// ---- Test fixture ----

class CopyStringTest_17 : public ::testing::Test {
 protected:
  static void FreeIfNotNull(char* p) { std::free(p); }
};

// ---- Tests ----

TEST_F(CopyStringTest_17, CopiesContentAndCallsGmallocWithExpectedSize_17) {
  MockGmalloc_17 mock;
  ScopedGmallocMock_17 scoped(&mock);

  const char* s = "hello";
  const size_t expectedSize = std::strlen(s) + 1;

  size_t seenSize = 0;
  bool seenFlag = true;

  EXPECT_CALL(mock, Call(_, _))
      .WillOnce(DoAll(SaveArg<0>(&seenSize), SaveArg<1>(&seenFlag), Return(std::malloc(expectedSize))));

  char* out = copyString(s);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(seenSize, expectedSize);
  EXPECT_FALSE(seenFlag);

  EXPECT_STREQ(out, s);
  EXPECT_NE(out, s);  // should be a distinct buffer

  FreeIfNotNull(out);
}

TEST_F(CopyStringTest_17, EmptyStringAllocatesOneByteAndCopies_17) {
  MockGmalloc_17 mock;
  ScopedGmallocMock_17 scoped(&mock);

  const char* s = "";
  const size_t expectedSize = 1;

  EXPECT_CALL(mock, Call(expectedSize, false)).WillOnce(Return(std::malloc(expectedSize)));

  char* out = copyString(s);
  ASSERT_NE(out, nullptr);

  EXPECT_STREQ(out, "");
  EXPECT_EQ(out[0], '\0');

  FreeIfNotNull(out);
}

TEST_F(CopyStringTest_17, LargeStringAllocatesLengthPlusOneAndCopies_17) {
  MockGmalloc_17 mock;
  ScopedGmallocMock_17 scoped(&mock);

  std::string big(1024, 'a');
  const size_t expectedSize = big.size() + 1;

  EXPECT_CALL(mock, Call(expectedSize, false)).WillOnce(Return(std::malloc(expectedSize)));

  char* out = copyString(big.c_str());
  ASSERT_NE(out, nullptr);

  EXPECT_STREQ(out, big.c_str());
  EXPECT_EQ(out[big.size()], '\0');

  FreeIfNotNull(out);
}

TEST_F(CopyStringTest_17, MultipleCallsReturnDistinctBuffers_17) {
  MockGmalloc_17 mock;
  ScopedGmallocMock_17 scoped(&mock);

  const char* s = "repeat";
  const size_t expectedSize = std::strlen(s) + 1;

  EXPECT_CALL(mock, Call(expectedSize, false))
      .Times(2)
      .WillRepeatedly(Return(std::malloc(expectedSize)));

  char* out1 = copyString(s);
  char* out2 = copyString(s);

  ASSERT_NE(out1, nullptr);
  ASSERT_NE(out2, nullptr);

  EXPECT_STREQ(out1, s);
  EXPECT_STREQ(out2, s);
  EXPECT_NE(out1, out2);

  FreeIfNotNull(out1);
  FreeIfNotNull(out2);
}