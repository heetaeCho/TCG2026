// ============================================================================
// TEST_ID: 809
// File: test_stringvaluebase_toInt64_809.cpp
// Unit tests for Exiv2::StringValueBase (black-box, interface/observable behavior)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>

// Exiv2
#include "exiv2/value.hpp"

namespace {

// Test helper to access protected Value::ok_ (allowed via inheritance; no private state access).
class TestableStringValueBase final : public Exiv2::StringValueBase {
 public:
  TestableStringValueBase(Exiv2::TypeId typeId, const std::string& buf)
      : Exiv2::StringValueBase(typeId, buf) {}

  void ForceOk(bool v) { ok_ = v; }  // ok_ is protected in Exiv2::Value (base of StringValueBase)
};

// Pick a TypeId without assuming too much about the enum values.
// If the project defines Exiv2::asciiString, use it; otherwise fall back to a safe cast.
static Exiv2::TypeId PickStringTypeId() {
#ifdef EXV_HAVE_TYPEID_ASCIISTRING  // unlikely; keep as a hook if the build defines something similar
  return Exiv2::asciiString;
#else
  // Many Exiv2 builds define Exiv2::asciiString; if not, this still compiles and constructs.
  // We do not rely on specific semantics of the TypeId for these tests.
  return static_cast<Exiv2::TypeId>(0);
#endif
}

class StringValueBaseTest_809 : public ::testing::Test {
 protected:
  static TestableStringValueBase Make(const std::string& s) {
    return TestableStringValueBase(PickStringTypeId(), s);
  }
};

}  // namespace

TEST_F(StringValueBaseTest_809, ToInt64_InRangeIndex_DoesNotThrowAndSetsOkTrue_809) {
  auto v = Make("ABC");

  // Force ok() to false first, then verify toInt64 makes ok() true (observable via ok()).
  v.ForceOk(false);
  ASSERT_FALSE(v.ok());

  ASSERT_NO_THROW({
    (void)v.toInt64(0);
  });

  EXPECT_TRUE(v.ok());
}

TEST_F(StringValueBaseTest_809, ToInt64_SameIndex_ReturnsSameValue_809) {
  auto v = Make("ABC");

  // Black-box: we do not assume what the numeric value means, only that repeated calls are stable.
  const int64_t a = v.toInt64(0);
  const int64_t b = v.toInt64(0);
  EXPECT_EQ(a, b);
}

TEST_F(StringValueBaseTest_809, ToInt64_LastValidIndex_DoesNotThrow_809) {
  auto v = Make("ABC");

  const size_t c = v.count();
  ASSERT_GT(c, 0u);

  EXPECT_NO_THROW({
    (void)v.toInt64(c - 1);
  });
}

TEST_F(StringValueBaseTest_809, ToInt64_IndexEqualToCount_ThrowsOutOfRange_809) {
  auto v = Make("ABC");

  const size_t c = v.count();
  // For empty, index 0 is already out-of-range; for non-empty, index==count is out-of-range.
  EXPECT_THROW((void)v.toInt64(c), std::out_of_range);
}

TEST_F(StringValueBaseTest_809, ToInt64_OutOfRange_StillSetsOkTrue_809) {
  auto v = Make("ABC");

  const size_t c = v.count();
  v.ForceOk(false);
  ASSERT_FALSE(v.ok());

  try {
    (void)v.toInt64(c);  // out-of-range by definition for .at()-style access
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range&) {
    // ok() is observable; ensure it is true after the call attempt.
    EXPECT_TRUE(v.ok());
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}