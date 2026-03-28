// TEST_ID 690
// Unit tests for Exiv2::Iptcdatum::setValue(const Value*)
// File: ./TestProjects/exiv2/src/iptc.cpp (black-box tests via public interface)

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

class IptcdatumSetValueTest_690 : public ::testing::Test {
 protected:
  static Exiv2::IptcKey MakeKey() {
    // Commonly valid IPTC key used across Exiv2 examples/tests.
    // We do not depend on any specific internal mapping beyond being constructible.
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }

  static std::unique_ptr<Exiv2::Value> MakeStringValueOrSkip(const std::string& s) {
    // Prefer a string-capable TypeId. If the enum differs in this codebase/config,
    // compilation will fail and should be adapted to the local TypeId naming.
    auto v = Exiv2::Value::create(Exiv2::string);
    if (!v) return nullptr;
    (void)v->read(s);
    return v;
  }

  static std::string ToStringOrEmpty(const std::unique_ptr<Exiv2::Value>& v) {
    return v ? v->toString() : std::string{};
  }
};

TEST_F(IptcdatumSetValueTest_690, SetValueClonesInput_690) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  auto src = MakeStringValueOrSkip("abc");
  if (!src) GTEST_SKIP() << "Value::create(TypeId::string) returned null in this build.";

  // Store "abc"
  ASSERT_NO_THROW(datum.setValue(src.get()));
  auto stored1 = datum.getValue();
  ASSERT_TRUE(stored1) << "Expected getValue() to return a value after setValue(non-null).";
  EXPECT_EQ(stored1->toString(), "abc");

  // Mutate source to "def" and ensure datum keeps the prior value (clone semantics).
  (void)src->read("def");
  auto stored2 = datum.getValue();
  ASSERT_TRUE(stored2);
  EXPECT_EQ(stored2->toString(), "abc");
  EXPECT_NE(stored2->toString(), src->toString());
}

TEST_F(IptcdatumSetValueTest_690, SetValueNullClearsPreviouslyStoredValue_690) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  auto src = MakeStringValueOrSkip("abc");
  if (!src) GTEST_SKIP() << "Value::create(TypeId::string) returned null in this build.";

  ASSERT_NO_THROW(datum.setValue(src.get()));
  auto before = datum.getValue();
  ASSERT_TRUE(before);
  EXPECT_EQ(before->toString(), "abc");

  // Clear
  ASSERT_NO_THROW(datum.setValue(nullptr));

  // Observable behavior: should no longer yield the previous "abc" value.
  // Some builds may represent "cleared" as nullptr; others may return an empty Value.
  auto after = datum.getValue();
  if (after) {
    EXPECT_NE(after->toString(), "abc");
  } else {
    SUCCEED() << "getValue() returned nullptr after setValue(nullptr), indicating cleared state.";
  }
}

TEST_F(IptcdatumSetValueTest_690, SetValueAcceptsEmptyStringValue_690) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  auto src = MakeStringValueOrSkip("");
  if (!src) GTEST_SKIP() << "Value::create(TypeId::string) returned null in this build.";

  ASSERT_NO_THROW(datum.setValue(src.get()));
  auto stored = datum.getValue();
  ASSERT_TRUE(stored);
  EXPECT_EQ(stored->toString(), "");
}

TEST_F(IptcdatumSetValueTest_690, SetValueNullWhenAlreadyEmptyDoesNotThrow_690) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_NO_THROW(datum.setValue(nullptr));
  EXPECT_NO_THROW((void)datum.getValue());
}

}  // namespace