// CachedFileStream_getUnfilteredChar_tests_162.cpp
// Unit tests for CachedFileStream::getUnfilteredChar()
// The TEST_ID is 162

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>
#include <memory>

#include "Stream.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

class CachedFileStreamTest_162 : public ::testing::Test {};

TEST_F(CachedFileStreamTest_162, Signature_ReturnTypeIsInt_162) {
  static_assert(std::is_same_v<decltype(std::declval<CachedFileStream&>().getUnfilteredChar()), int>,
                "CachedFileStream::getUnfilteredChar() must return int");
}

TEST_F(CachedFileStreamTest_162, DelegatesToGetChar_WhenConstructible_162) {
  // We only run runtime behavior checks if CachedFile is default-constructible in this build.
  if constexpr (std::is_default_constructible_v<CachedFile>) {
    auto cc = std::make_shared<CachedFile>();

    // Use minimal arguments; behavior is treated as a black box.
    CachedFileStream s(cc, /*startA=*/0, /*limitedA=*/false, /*lengthA=*/0, Object{});

    // Observable contract from the provided partial implementation:
    // getUnfilteredChar() returns getChar().
    EXPECT_EQ(s.getUnfilteredChar(), s.getChar());
  } else {
    GTEST_SKIP() << "CachedFile is not default-constructible in this build; cannot safely construct CachedFileStream.";
  }
}

class MockCachedFileStream_162 : public CachedFileStream {
 public:
  using CachedFileStream::CachedFileStream;
  MOCK_METHOD(int, getChar, (), (override));
};

TEST_F(CachedFileStreamTest_162, CallsGetCharExactlyOnce_AndReturnsItsValue_WhenConstructible_162) {
  if constexpr (std::is_default_constructible_v<CachedFile>) {
    auto cc = std::make_shared<CachedFile>();

    // NiceMock allows any constructor-time virtual calls (if any) without failing the test.
    NiceMock<MockCachedFileStream_162> s(cc, /*startA=*/0, /*limitedA=*/false, /*lengthA=*/0, Object{});

    constexpr int kSentinel = 0x5A;
    EXPECT_CALL(s, getChar()).Times(1).WillOnce(Return(kSentinel));

    EXPECT_EQ(s.getUnfilteredChar(), kSentinel);
  } else {
    GTEST_SKIP() << "CachedFile is not default-constructible in this build; cannot safely construct CachedFileStream.";
  }
}

}  // namespace