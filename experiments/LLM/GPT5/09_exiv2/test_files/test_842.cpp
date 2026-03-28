// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmptextvalue_toRational_842.cpp
//
// Unit tests for:
//   Exiv2::XmpTextValue::toRational(size_t) const
//
// Constraints respected:
// - Treat implementation as a black box
// - Only test observable behavior via the public interface
// - No private state access
//
// Note:
// The provided snippet does not show how to construct/assign an XmpTextValue with a given text,
// nor any public setter/ctor. To still create meaningful black-box tests, we use an established
// Exiv2 pattern: construct the value through the public Value factory and set it from string,
// then downcast to XmpTextValue if it is the concrete type.
//
// If your build exposes a different public creation path for XmpTextValue, adjust the factory
// portion accordingly (the assertions and behaviors remain interface-based).

#include <gtest/gtest.h>

#include <exiv2/value.hpp>   // Value, Value::create, TypeId, Rational
#include <exiv2/types.hpp>   // Rational (sometimes declared here depending on version)

#include <memory>
#include <string>
#include <typeinfo>

namespace {

// Helper that tries to obtain an Exiv2::XmpTextValue instance via public APIs.
// If the concrete type cannot be created in this build/config, the test is skipped.
static Exiv2::XmpTextValue* MakeXmpTextValueOrSkip(const std::string& text,
                                                  std::unique_ptr<Exiv2::Value>& owner) {
  // Prefer the XMP text type if available in this Exiv2 build.
  // In many Exiv2 versions, XMP text values are represented by TypeId::xmpText.
  owner.reset(Exiv2::Value::create(Exiv2::xmpText));

  if (!owner) {
    GTEST_SKIP() << "Value::create(xmpText) returned nullptr; cannot construct XmpTextValue.";
  }

  owner->read(text);

  // Downcast using RTTI-safe dynamic_cast.
  auto* p = dynamic_cast<Exiv2::XmpTextValue*>(owner.get());
  if (!p) {
    // Some builds may return a different concrete Value even for xmpText.
    GTEST_SKIP() << "Value::create(xmpText) did not yield Exiv2::XmpTextValue in this build (got "
                 << typeid(*owner).name() << ").";
  }
  return p;
}

}  // namespace

// TEST_ID 842

TEST(XmpTextValueTest_842, ToRational_ParsesSimpleFraction_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("1/2", v);

  const Exiv2::Rational r = x->toRational(0);
  EXPECT_EQ(1, r.first);
  EXPECT_EQ(2, r.second);
}

TEST(XmpTextValueTest_842, ToRational_IgnoresIndexParameterForSameInput_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("3/4", v);

  const Exiv2::Rational r0 = x->toRational(0);
  const Exiv2::Rational r1 = x->toRational(1);
  const Exiv2::Rational r999 = x->toRational(999);

  // Observable expectation: since the signature explicitly comments /*n*/ (unused),
  // the index parameter should not affect the output for a scalar XmpTextValue.
  EXPECT_EQ(r0.first, r1.first);
  EXPECT_EQ(r0.second, r1.second);
  EXPECT_EQ(r0.first, r999.first);
  EXPECT_EQ(r0.second, r999.second);

  EXPECT_EQ(3, r0.first);
  EXPECT_EQ(4, r0.second);
}

TEST(XmpTextValueTest_842, ToRational_HandlesWhitespaceAroundFraction_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("  10 /  20  ", v);

  const Exiv2::Rational r = x->toRational(0);

  // We do not assume reduction; only that it parses to equivalent components if supported.
  // Many parsers accept whitespace and return (10,20) rather than reducing to (1,2).
  EXPECT_EQ(10, r.first);
  EXPECT_EQ(20, r.second);
}

TEST(XmpTextValueTest_842, ToRational_InvalidStringYieldsObservableDefault_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("not-a-rational", v);

  const Exiv2::Rational r = x->toRational(0);

  // Black-box expectation for error cases:
  // parseRational(...) is passed an 'ok_' flag; if parsing fails, many Exiv2 parsers
  // return a default Rational (0/1). We assert a conservative observable default.
  //
  // If your Exiv2 build returns a different sentinel (e.g., 0/0), adjust this assertion.
  EXPECT_EQ(0, r.first);
  EXPECT_TRUE(r.second == 1 || r.second == 0);
}

TEST(XmpTextValueTest_842, ToRational_EmptyStringYieldsObservableDefault_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("", v);

  const Exiv2::Rational r = x->toRational(0);

  EXPECT_EQ(0, r.first);
  EXPECT_TRUE(r.second == 1 || r.second == 0);
}

TEST(XmpTextValueTest_842, ToRational_AllowsNegativeNumerator_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("-5/7", v);

  const Exiv2::Rational r = x->toRational(0);
  EXPECT_EQ(-5, r.first);
  EXPECT_EQ(7, r.second);
}

TEST(XmpTextValueTest_842, ToRational_DenominatorZeroIsHandledGracefully_842) {
  std::unique_ptr<Exiv2::Value> v;
  Exiv2::XmpTextValue* x = MakeXmpTextValueOrSkip("1/0", v);

  const Exiv2::Rational r = x->toRational(0);

  // Boundary/error case: denominator zero.
  // We do NOT assume internal policy; we only assert the call does not crash and returns
  // some Rational value. Additionally, a common choice is to clamp/return default.
  EXPECT_EQ(1, r.first);
  // Accept either 0 (preserved), 1 (default), or another nonzero (sanitized) denominator.
  EXPECT_TRUE(r.second == 0 || r.second == 1 || r.second == -0 /*same as 0*/);
}