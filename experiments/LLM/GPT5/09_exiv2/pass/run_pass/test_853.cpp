// SPDX-License-Identifier: GPL-2.0-or-later
// Test for Exiv2::LangAltValue::clone()
// TEST_ID: 853

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <sstream>
#include <string>
#include <typeinfo>

namespace {

class LangAltValueTest_853 : public ::testing::Test {
protected:
  static std::string writeToString(const Exiv2::LangAltValue& v) {
    std::ostringstream os;
    // write() returns an ostream reference; we only assert it doesn't throw and produces some output.
    EXPECT_NO_THROW(v.write(os));
    return os.str();
  }
};

TEST_F(LangAltValueTest_853, Clone_DefaultConstructedNotNullAndDifferentObject_853) {
  const Exiv2::LangAltValue v;

  Exiv2::LangAltValue::UniquePtr c;
  EXPECT_NO_THROW(c = v.clone());
  ASSERT_NE(c.get(), nullptr);

  // Must be a different object than the original.
  EXPECT_NE(c.get(), &v);

  // Should be cloneable repeatedly without crashing.
  Exiv2::LangAltValue::UniquePtr c2;
  EXPECT_NO_THROW(c2 = v.clone());
  ASSERT_NE(c2.get(), nullptr);
  EXPECT_NE(c2.get(), c.get());
}

TEST_F(LangAltValueTest_853, Clone_PreservesWriteOutput_853) {
  Exiv2::LangAltValue v;

  // Use the public interface only. We don't assume the exact parsing/formatting rules;
  // we just ensure clone produces the same observable output as the source at clone time.
  EXPECT_NO_THROW((void)v.read(std::string{}));  // boundary: empty input
  const std::string before = writeToString(v);

  Exiv2::LangAltValue::UniquePtr c;
  ASSERT_NO_THROW(c = v.clone());
  ASSERT_NE(c.get(), nullptr);

  // Compare observable behavior through write().
  auto* asLangAlt = dynamic_cast<Exiv2::LangAltValue*>(c.get());
  ASSERT_NE(asLangAlt, nullptr) << "clone() should return a LangAltValue instance via UniquePtr";
  const std::string cloned = writeToString(*asLangAlt);

  EXPECT_EQ(cloned, before);
}

TEST_F(LangAltValueTest_853, Clone_FromNonEmptyReadInputMatchesWriteOutput_853) {
  Exiv2::LangAltValue v;

  // "Non-empty" input: we do not assume it must succeed or what it means internally.
  // We only check that cloning after interacting through the public API yields equivalent output.
  const std::string input = "x-default=Hello";  // intentionally simple; treated as opaque input
  EXPECT_NO_THROW((void)v.read(input));

  const std::string srcOut = writeToString(v);

  Exiv2::LangAltValue::UniquePtr c;
  ASSERT_NO_THROW(c = v.clone());
  ASSERT_NE(c.get(), nullptr);

  auto* asLangAlt = dynamic_cast<Exiv2::LangAltValue*>(c.get());
  ASSERT_NE(asLangAlt, nullptr);

  EXPECT_EQ(writeToString(*asLangAlt), srcOut);
}

TEST_F(LangAltValueTest_853, Clone_OnConstObjectDoesNotThrow_853) {
  const Exiv2::LangAltValue v("arbitrary-buffer");

  Exiv2::LangAltValue::UniquePtr c;
  EXPECT_NO_THROW(c = v.clone());
  ASSERT_NE(c.get(), nullptr);

  // Minimal observable check: cloned object can be written without throwing.
  auto* asLangAlt = dynamic_cast<Exiv2::LangAltValue*>(c.get());
  ASSERT_NE(asLangAlt, nullptr);
  (void)writeToString(*asLangAlt);
}

}  // namespace