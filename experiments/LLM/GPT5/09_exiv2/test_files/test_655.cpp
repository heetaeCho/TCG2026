// File: test_quicktimevideo_dataIgnoreList_655.cpp
// TEST_ID: 655

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/types.hpp"

// We need access to the internal/static function under test.
// The class/function is treated as a black box; we only observe calls/returns.
// Including the .cpp places the `static` function in this translation unit.
#include "./TestProjects/exiv2/src/quicktimevideo.cpp"

namespace {

// A small mock "collaborator" for the free function dependency used by dataIgnoreList().
// dataIgnoreList() calls Exiv2::Internal::equalsQTimeTag(buf, tag).
class EqualsQTimeTagMock {
 public:
  MOCK_METHOD(bool, Call, (Exiv2::DataBuf& buf, const char* tag), ());
};

// Test-owned pointer used by our test-double equalsQTimeTag implementation.
EqualsQTimeTagMock* g_equals_mock = nullptr;

}  // namespace

namespace Exiv2::Internal {

// Test double for the free function dependency.
// This lets us verify external interactions (calls + parameters) without
// re-implementing/inferencing any internal logic of dataIgnoreList().
bool equalsQTimeTag(Exiv2::DataBuf& buf, const char* tag) {
  if (g_equals_mock == nullptr) {
    // If no mock installed, be conservative and return false.
    // (Prevents UB / surprises if a test forgets to install the mock.)
    return false;
  }
  return g_equals_mock->Call(buf, tag);
}

}  // namespace Exiv2::Internal

namespace {

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrEq;

class QuickTimeVideoDataIgnoreListTest_655 : public ::testing::Test {
 protected:
  void SetUp() override { g_equals_mock = &mock_; }
  void TearDown() override { g_equals_mock = nullptr; }

  EqualsQTimeTagMock mock_;
};

TEST_F(QuickTimeVideoDataIgnoreListTest_655, ReturnsFalseWhenNoTagsMatch_655) {
  Exiv2::DataBuf buf;  // boundary: empty/default buffer should still be handled

  {
    InSequence seq;
    EXPECT_CALL(mock_, Call(_, StrEq("moov"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("mdia"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("minf"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("dinf"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("alis"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("stbl"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("cmov"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("meta"))).WillOnce(Return(false));
  }

  EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(QuickTimeVideoDataIgnoreListTest_655, ReturnsTrueWhenFirstTagMatchesAndStopsEarly_655) {
  Exiv2::DataBuf buf;

  EXPECT_CALL(mock_, Call(_, StrEq("moov"))).WillOnce(Return(true));
  // If it doesn't stop early, these would be called and fail the test due to no expectations.
  EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(QuickTimeVideoDataIgnoreListTest_655, ReturnsTrueWhenMiddleTagMatchesAndStopsAfterMatch_655) {
  Exiv2::DataBuf buf;

  {
    InSequence seq;
    EXPECT_CALL(mock_, Call(_, StrEq("moov"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("mdia"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("minf"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("dinf"))).WillOnce(Return(true));
    // Must not proceed beyond the first match
  }

  EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(QuickTimeVideoDataIgnoreListTest_655, ReturnsTrueWhenLastTagMatches_655) {
  Exiv2::DataBuf buf;

  {
    InSequence seq;
    EXPECT_CALL(mock_, Call(_, StrEq("moov"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("mdia"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("minf"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("dinf"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("alis"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("stbl"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("cmov"))).WillOnce(Return(false));
    EXPECT_CALL(mock_, Call(_, StrEq("meta"))).WillOnce(Return(true));
  }

  EXPECT_TRUE(Exiv2::Internal::dataIgnoreList(buf));
}

TEST_F(QuickTimeVideoDataIgnoreListTest_655, DoesNotPassUnexpectedTags_655) {
  Exiv2::DataBuf buf;

  // Exceptional/negative: ensure only the expected 8 tags are ever passed.
  // We enforce this by allowing only these calls, exactly once each, returning false.
  EXPECT_CALL(mock_, Call(_, StrEq("moov"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("mdia"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("minf"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("dinf"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("alis"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("stbl"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("cmov"))).WillOnce(Return(false));
  EXPECT_CALL(mock_, Call(_, StrEq("meta"))).WillOnce(Return(false));

  EXPECT_FALSE(Exiv2::Internal::dataIgnoreList(buf));
}

}  // namespace