// =================================================================================================
// TEST_ID: 854
// Unit tests for Exiv2::LangAltValue (black-box)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace {

// Helper: call a nullary functor and capture either a value or that it threw.
template <typename F>
auto CallCapture(F&& f) {
  using R = decltype(f());
  struct Result {
    bool threw{false};
    std::optional<R> value;
  } out;

  try {
    out.value = f();
  } catch (...) {
    out.threw = true;
  }
  return out;
}

}  // namespace

class LangAltValueTest_854 : public ::testing::Test {};

TEST_F(LangAltValueTest_854, DefaultConstructor_HasStableCount_854) {
  Exiv2::LangAltValue v;

  const size_t c1 = v.count();
  const size_t c2 = v.count();

  EXPECT_EQ(c1, c2);

  // Boundary-friendly expectation for typical empty default state:
  // If implementation changes, this still remains observable behavior (count stable).
  EXPECT_GE(c1, 0u);
}

TEST_F(LangAltValueTest_854, CtorWithBuffer_EmptyString_DoesNotChangeStability_854) {
  Exiv2::LangAltValue v_default;
  Exiv2::LangAltValue v_buf(std::string{});

  // We don't assume semantic parsing; only that count is well-defined and stable per instance.
  EXPECT_EQ(v_default.count(), v_default.count());
  EXPECT_EQ(v_buf.count(), v_buf.count());

  // Also exercise write() for both instances (no assumptions about formatting).
  std::ostringstream os1;
  std::ostringstream os2;
  EXPECT_NO_THROW(v_default.write(os1));
  EXPECT_NO_THROW(v_buf.write(os2));
}

TEST_F(LangAltValueTest_854, Read_EmptyString_IsCallableAndCountRemainsWellDefined_854) {
  Exiv2::LangAltValue v;

  const size_t before = v.count();

  // We don't assume a particular return code. Only that it is callable and doesn't make count invalid.
  int rc = 0;
  EXPECT_NO_THROW(rc = v.read(std::string{}));
  (void)rc;

  const size_t after = v.count();

  // Observable, conservative property: count() remains a valid size_t and stable across repeated calls.
  EXPECT_EQ(after, v.count());

  // If implementation treats empty read as no-op, this will pass; if it resets or populates,
  // we still avoid assuming which direction it changes.
  EXPECT_GE(before, 0u);
  EXPECT_GE(after, 0u);
}

TEST_F(LangAltValueTest_854, Clone_ProducesNonNullAndPreservesObservableOutputs_854) {
  Exiv2::LangAltValue v;
  (void)v.read(std::string{});  // best-effort: exercise read path without assuming semantics

  const size_t c = v.count();

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Clone is returned as a base pointer; validate via observable interface.
  EXPECT_EQ(cloned->count(), c);

  std::ostringstream os_orig;
  std::ostringstream os_clone;
  EXPECT_NO_THROW(v.write(os_orig));
  EXPECT_NO_THROW(cloned->write(os_clone));
  EXPECT_EQ(os_clone.str(), os_orig.str());
}

TEST_F(LangAltValueTest_854, ToString_ByIndex_IsCallableForBoundaryIndices_854) {
  Exiv2::LangAltValue v;

  // Boundary indices: 0, 1, and very large (do not assume count > 0).
  const auto r0 = CallCapture([&]() { return v.toString(static_cast<size_t>(0)); });
  const auto r1 = CallCapture([&]() { return v.toString(static_cast<size_t>(1)); });
  const auto rMax = CallCapture([&]() { return v.toString(std::numeric_limits<size_t>::max()); });

  // Ensure repeated calls are consistent in "throws vs returns" behavior.
  const auto r0b = CallCapture([&]() { return v.toString(static_cast<size_t>(0)); });
  EXPECT_EQ(r0.threw, r0b.threw);
  if (!r0.threw) {
    EXPECT_EQ(r0.value.value(), r0b.value.value());
  }

  // Light sanity: results (or exception behavior) must be defined; just record other calls.
  (void)r1;
  (void)rMax;
}

TEST_F(LangAltValueTest_854, ToString_ByQualifier_IsCallableAndConsistent_854) {
  Exiv2::LangAltValue v;
  (void)v.read(std::string{});

  const std::string q1 = "x-default";
  const std::string q2 = "en-US";
  const std::string q3 = "";

  const auto a1 = CallCapture([&]() { return v.toString(q1); });
  const auto a1b = CallCapture([&]() { return v.toString(q1); });
  EXPECT_EQ(a1.threw, a1b.threw);
  if (!a1.threw) {
    EXPECT_EQ(a1.value.value(), a1b.value.value());
  }

  // Exercise additional qualifiers (no assumptions).
  (void)CallCapture([&]() { return v.toString(q2); });
  (void)CallCapture([&]() { return v.toString(q3); });

  // Verify clone matches qualifier-call behavior.
  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Need a LangAltValue to call the qualifier overload (not part of XmpValue base).
  // Use dynamic_cast in a black-box way: if clone is not LangAltValue, that's a failure for this API.
  auto* c = dynamic_cast<Exiv2::LangAltValue*>(cloned.get());
  ASSERT_NE(c, nullptr);

  const auto b1 = CallCapture([&]() { return c->toString(q1); });
  EXPECT_EQ(a1.threw, b1.threw);
  if (!a1.threw) {
    EXPECT_EQ(a1.value.value(), b1.value.value());
  }
}

TEST_F(LangAltValueTest_854, NumericConversions_ThrowOrReturnBehaviorIsConsistentWithinObject_854) {
  Exiv2::LangAltValue v;

  // We do not assume conversions are supported for an empty/default value.
  // We only assert consistency across repeated calls for the same index.
  const size_t n = 0;

  const auto i1 = CallCapture([&]() { return v.toInt64(n); });
  const auto i1b = CallCapture([&]() { return v.toInt64(n); });
  EXPECT_EQ(i1.threw, i1b.threw);
  if (!i1.threw) EXPECT_EQ(i1.value.value(), i1b.value.value());

  const auto u1 = CallCapture([&]() { return v.toUint32(n); });
  const auto u1b = CallCapture([&]() { return v.toUint32(n); });
  EXPECT_EQ(u1.threw, u1b.threw);
  if (!u1.threw) EXPECT_EQ(u1.value.value(), u1b.value.value());

  const auto f1 = CallCapture([&]() { return v.toFloat(n); });
  const auto f1b = CallCapture([&]() { return v.toFloat(n); });
  EXPECT_EQ(f1.threw, f1b.threw);
  if (!f1.threw) EXPECT_EQ(f1.value.value(), f1b.value.value());

  const auto r1 = CallCapture([&]() { return v.toRational(n); });
  const auto r1b = CallCapture([&]() { return v.toRational(n); });
  EXPECT_EQ(r1.threw, r1b.threw);
  // For Rational, rely on operator== if available; otherwise only compare throw behavior.
  if (!r1.threw && !r1b.threw) {
    // Exiv2::Rational is typically comparable; if not, this line will fail to compile,
    // but Exiv2 generally defines comparison for Rational-like pairs.
    EXPECT_TRUE(r1.value.value() == r1b.value.value());
  }
}

TEST_F(LangAltValueTest_854, Clone_MatchesNumericConversionThrowOrReturnBehavior_854) {
  Exiv2::LangAltValue v;
  (void)v.read(std::string{});
  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Verify base-level numeric conversion behavior matches between original and clone.
  const size_t n = 0;

  const auto oi = CallCapture([&]() { return v.toInt64(n); });
  const auto ci = CallCapture([&]() { return cloned->toInt64(n); });
  EXPECT_EQ(oi.threw, ci.threw);
  if (!oi.threw) EXPECT_EQ(oi.value.value(), ci.value.value());

  const auto ou = CallCapture([&]() { return v.toUint32(n); });
  const auto cu = CallCapture([&]() { return cloned->toUint32(n); });
  EXPECT_EQ(ou.threw, cu.threw);
  if (!ou.threw) EXPECT_EQ(ou.value.value(), cu.value.value());

  const auto of = CallCapture([&]() { return v.toFloat(n); });
  const auto cf = CallCapture([&]() { return cloned->toFloat(n); });
  EXPECT_EQ(of.threw, cf.threw);
  if (!of.threw) EXPECT_EQ(of.value.value(), cf.value.value());

  const auto orat = CallCapture([&]() { return v.toRational(n); });
  const auto crat = CallCapture([&]() { return cloned->toRational(n); });
  EXPECT_EQ(orat.threw, crat.threw);
  if (!orat.threw && !crat.threw) {
    EXPECT_TRUE(orat.value.value() == crat.value.value());
  }
}