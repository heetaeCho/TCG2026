// File: simplify_previsit_test_429.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::StrictMock;

namespace re2 {

// ---- Test-only seam for the collaborator (Regexp) ----
// We only declare the methods used by SimplifyWalker::PreVisit,
// treating Regexp as a black-box collaborator.
class Regexp {
public:
  virtual ~Regexp() = default;
  virtual bool simple() = 0;
  virtual Regexp* Incref() = 0;
};

// SUT declaration (matches the provided snippet).
class SimplifyWalker {
public:
  // Implementation is in production code; we don't re-implement it here.
  Regexp* PreVisit(Regexp* re, Regexp* parent_arg, bool* stop);
};

// ---- Mock for the collaborator ----
class MockRegexp : public Regexp {
public:
  MOCK_METHOD(bool, simple, (), (override));
  MOCK_METHOD(Regexp*, Incref, (), (override));
};

}  // namespace re2

// ------------------ Tests ------------------

namespace re2 {

class SimplifyWalkerPreVisitTest_429 : public ::testing::Test {
protected:
  SimplifyWalker walker_;
};

// Normal operation: simple() == true
// Expect: *stop set to true, returns Incref() result, Incref() called exactly once.
TEST_F(SimplifyWalkerPreVisitTest_429, ReturnsIncrefAndSetsStopWhenSimple_429) {
  StrictMock<MockRegexp> re;
  bool stop = false;
  Regexp* incref_result = &re;

  EXPECT_CALL(re, simple())
      .WillOnce(Return(true));
  EXPECT_CALL(re, Incref())
      .WillOnce(Return(incref_result));

  Regexp* out = walker_.PreVisit(&re, /*parent_arg=*/nullptr, &stop);

  EXPECT_TRUE(stop) << "stop should be set to true when re->simple() is true";
  EXPECT_EQ(out, incref_result) << "Should return re->Incref() result";
}

// Boundary/else-path: simple() == false
// Expect: *stop remains unchanged (false), returns nullptr, Incref() not called.
TEST_F(SimplifyWalkerPreVisitTest_429, ReturnsNullAndLeavesStopWhenNotSimple_429) {
  StrictMock<MockRegexp> re;
  bool stop = false;

  EXPECT_CALL(re, simple())
      .WillOnce(Return(false));
  // No EXPECT_CALL for Incref(); it must NOT be called.

  Regexp* out = walker_.PreVisit(&re, /*parent_arg=*/nullptr, &stop);

  EXPECT_FALSE(stop) << "stop should remain unchanged when re->simple() is false";
  EXPECT_EQ(out, nullptr) << "Should return nullptr when not simple";
}

// Sanity: *stop is actually written only in the simple-path.
// Initialize stop = true, verify it doesn't get overwritten when not simple.
TEST_F(SimplifyWalkerPreVisitTest_429, DoesNotOverwriteStopWhenNotSimple_429) {
  StrictMock<MockRegexp> re;
  bool stop = true;  // pre-set to true

  EXPECT_CALL(re, simple())
      .WillOnce(Return(false));

  Regexp* out = walker_.PreVisit(&re, /*parent_arg=*/nullptr, &stop);

  EXPECT_TRUE(stop) << "stop should not be force-written to false";
  EXPECT_EQ(out, nullptr);
}

}  // namespace re2
