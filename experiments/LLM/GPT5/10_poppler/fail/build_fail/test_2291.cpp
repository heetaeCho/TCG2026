// poppler-action-build-goto-dest-test.cc
//
// Unit tests for build_goto_dest() in glib/poppler-action.cc
// TEST_ID: 2291
//
// Notes:
// - We treat build_goto_dest as a black box.
// - We intercept dest_new_goto / dest_new_named to observe external interactions
//   and avoid depending on PopplerDest internals.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <cstring>

extern "C" {
#include "poppler-action.h"
#include "poppler-private.h"
}

// Poppler core headers (C++ types used by build_goto_dest).
#include "poppler/Link.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// ---- Interception hooks (external interaction verification) ----

struct DestNewGotoCall {
  int count = 0;
  PopplerDocument* document = nullptr;
  const LinkDest* link_dest = nullptr;
};

struct DestNewNamedCall {
  int count = 0;
  const GooString* named_dest = nullptr;
};

DestNewGotoCall g_goto_calls;
DestNewNamedCall g_named_calls;

// We return distinct sentinel pointers so tests can verify which path was taken.
constexpr uintptr_t kSentinelGotoPtr  = 0x1001;
constexpr uintptr_t kSentinelNamedPtr = 0x2002;

} // namespace

// IMPORTANT: These macros must be defined before including the .cc under test.
// They redirect calls inside build_goto_dest() to our test interceptors.
#define dest_new_goto  test_dest_new_goto_2291
#define dest_new_named test_dest_new_named_2291

extern "C" PopplerDest* test_dest_new_goto_2291(PopplerDocument* document, const LinkDest* link_dest) {
  g_goto_calls.count++;
  g_goto_calls.document = document;
  g_goto_calls.link_dest = link_dest;
  return reinterpret_cast<PopplerDest*>(kSentinelGotoPtr);
}

extern "C" PopplerDest* test_dest_new_named_2291(const GooString* named_dest) {
  g_named_calls.count++;
  g_named_calls.named_dest = named_dest;
  return reinterpret_cast<PopplerDest*>(kSentinelNamedPtr);
}

// Include the production implementation into this translation unit so we can
// call the static function directly.
#include "glib/poppler-action.cc"

#undef dest_new_goto
#undef dest_new_named

namespace {

// ---- Test double for LinkGoTo ----
//
// We only override the methods build_goto_dest() uses.
// If the upstream signature differs, adjust accordingly; we do NOT reimplement
// Poppler logic—only control return values of the collaborator.

class MockLinkGoTo_2291 : public LinkGoTo {
public:
  MockLinkGoTo_2291() : LinkGoTo(nullptr) {}

  MOCK_METHOD(bool, isOk, (), (const, override));
  MOCK_METHOD(const LinkDest*, getDest, (), (const, override));
  MOCK_METHOD(const GooString*, getNamedDest, (), (const, override));
};

// Fixture to reset interceptors.
class BuildGotoDestTest_2291 : public ::testing::Test {
protected:
  void SetUp() override {
    g_goto_calls = DestNewGotoCall{};
    g_named_calls = DestNewNamedCall{};
    std::memset(&action_, 0, sizeof(action_));
  }

  PopplerAction action_{};
};

TEST_F(BuildGotoDestTest_2291, NotOk_UsesGotoWithNulls_2291) {
  StrictMock<MockLinkGoTo_2291> link;

  EXPECT_CALL(link, isOk()).WillOnce(Return(false));
  // If not OK, must return early and not query dest/named.
  EXPECT_CALL(link, getDest()).Times(0);
  EXPECT_CALL(link, getNamedDest()).Times(0);

  build_goto_dest(/*document=*/nullptr, &action_, &link);

  EXPECT_EQ(g_goto_calls.count, 1);
  EXPECT_EQ(g_goto_calls.document, nullptr);
  EXPECT_EQ(g_goto_calls.link_dest, nullptr);
  EXPECT_EQ(g_named_calls.count, 0);

  EXPECT_EQ(action_.goto_dest.dest, reinterpret_cast<PopplerDest*>(kSentinelGotoPtr));
}

TEST_F(BuildGotoDestTest_2291, Ok_WithExplicitLinkDest_UsesGotoWithDocumentAndDest_2291) {
  StrictMock<MockLinkGoTo_2291> link;

  PopplerDocument dummy_doc{};
  const LinkDest* fake_dest = reinterpret_cast<const LinkDest*>(0xABC);

  EXPECT_CALL(link, isOk()).WillOnce(Return(true));
  EXPECT_CALL(link, getDest()).WillOnce(Return(fake_dest));
  EXPECT_CALL(link, getNamedDest()).WillOnce(Return(nullptr));

  build_goto_dest(&dummy_doc, &action_, &link);

  EXPECT_EQ(g_goto_calls.count, 1);
  EXPECT_EQ(g_goto_calls.document, &dummy_doc);
  EXPECT_EQ(g_goto_calls.link_dest, fake_dest);
  EXPECT_EQ(g_named_calls.count, 0);

  EXPECT_EQ(action_.goto_dest.dest, reinterpret_cast<PopplerDest*>(kSentinelGotoPtr));
}

TEST_F(BuildGotoDestTest_2291, Ok_NoLinkDest_WithNamedDest_UsesNamed_2291) {
  StrictMock<MockLinkGoTo_2291> link;

  // We do not dereference GooString in the interceptor, so a non-null sentinel is sufficient.
  const GooString* fake_named = reinterpret_cast<const GooString*>(0xDEF);

  EXPECT_CALL(link, isOk()).WillOnce(Return(true));
  EXPECT_CALL(link, getDest()).WillOnce(Return(nullptr));
  EXPECT_CALL(link, getNamedDest()).WillOnce(Return(fake_named));

  build_goto_dest(/*document=*/nullptr, &action_, &link);

  EXPECT_EQ(g_goto_calls.count, 0);
  EXPECT_EQ(g_named_calls.count, 1);
  EXPECT_EQ(g_named_calls.named_dest, fake_named);

  EXPECT_EQ(action_.goto_dest.dest, reinterpret_cast<PopplerDest*>(kSentinelNamedPtr));
}

TEST_F(BuildGotoDestTest_2291, Ok_NoDest_NoNamed_UsesGotoWithNullDestAndDocument_2291) {
  StrictMock<MockLinkGoTo_2291> link;

  PopplerDocument dummy_doc{};

  EXPECT_CALL(link, isOk()).WillOnce(Return(true));
  EXPECT_CALL(link, getDest()).WillOnce(Return(nullptr));
  EXPECT_CALL(link, getNamedDest()).WillOnce(Return(nullptr));

  build_goto_dest(&dummy_doc, &action_, &link);

  EXPECT_EQ(g_goto_calls.count, 1);
  EXPECT_EQ(g_goto_calls.document, &dummy_doc);
  EXPECT_EQ(g_goto_calls.link_dest, nullptr);
  EXPECT_EQ(g_named_calls.count, 0);

  EXPECT_EQ(action_.goto_dest.dest, reinterpret_cast<PopplerDest*>(kSentinelGotoPtr));
}

} // namespace