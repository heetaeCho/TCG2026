// -------------------------------------------------------------------------------------------------
// TEST_ID: 1301
// Unit tests for Exiv2::Xmpdatum::setValue(const std::string&)
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class XmpdatumSetValueTest_1301 : public ::testing::Test {
 protected:
  // Use a custom namespace/prefix to avoid relying on any particular built-in property list.
  static constexpr const char* kTestNs = "http://example.com/exiv2-test/1.0/";
  static constexpr const char* kTestPrefix = "test";

  void SetUp() override {
    // Ensure the prefix is registered so "Xmp.test.*" keys are valid in typical Exiv2 builds.
    // If it's already registered, Exiv2 should either keep the existing mapping or override;
    // tests below do not depend on the override behavior.
    Exiv2::XmpProperties::registerNs(kTestNs, kTestPrefix);
  }

  void TearDown() override {
    // Best-effort cleanup.
    Exiv2::XmpProperties::unregisterNs(kTestNs);
  }

  static Exiv2::XmpKey makeKey(const std::string& prop) {
    // Common Exiv2 XMP key string format: "Xmp.<prefix>.<property>"
    return Exiv2::XmpKey(std::string("Xmp.") + kTestPrefix + "." + prop);
  }
};

// Normal operation: when a Value is provided, setValue(string) should read into that existing Value.
TEST_F(XmpdatumSetValueTest_1301, WritesIntoProvidedTextValue_1301) {
  const Exiv2::XmpKey key = makeKey("myTextProp");

  // Provide an explicit xmpText Value so we don't depend on XmpProperties::propertyType mapping.
  const auto initial = Exiv2::Value::create(Exiv2::xmpText);
  ASSERT_NE(initial.get(), nullptr);

  Exiv2::Xmpdatum d(key, initial.get());

  const std::string input = "hello world";
  const int rc = d.setValue(input);

  // Observable behavior: the datum string representation should reflect the written text.
  EXPECT_EQ(d.toString(), input);

  // Return code: for a successful read into a textual Value, rc is expected to indicate success.
  // We keep this expectation soft by asserting success as "not failing".
  EXPECT_EQ(rc, 0);
}

// Boundary condition: empty string should be handled (no crash) and reflected in toString for text.
TEST_F(XmpdatumSetValueTest_1301, AcceptsEmptyStringForTextValue_1301) {
  const Exiv2::XmpKey key = makeKey("emptyTextProp");
  const auto initial = Exiv2::Value::create(Exiv2::xmpText);
  ASSERT_NE(initial.get(), nullptr);

  Exiv2::Xmpdatum d(key, initial.get());

  const int rc = d.setValue(std::string{});
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(d.toString(), std::string{});
}

// Normal operation: when no Value is provided, setValue should create one and use propertyType(key).
TEST_F(XmpdatumSetValueTest_1301, CreatesValueWhenNullAndTypeMatchesPropertyType_1301) {
  const Exiv2::XmpKey key = makeKey("autoTypedProp");

  // Construct with nullptr Value: implementation is expected to allocate on first setValue call.
  Exiv2::Xmpdatum d(key, nullptr);

  const TypeId expectedType = Exiv2::XmpProperties::propertyType(key);
  const int rc = d.setValue("some payload");

  // Must be able to observe that a value exists via typeId()/value() after setValue.
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(d.typeId(), expectedType);
}

// Boundary: large input should be accepted for text Value and preserved via toString.
TEST_F(XmpdatumSetValueTest_1301, HandlesLargeTextInput_1301) {
  const Exiv2::XmpKey key = makeKey("largeTextProp");
  const auto initial = Exiv2::Value::create(Exiv2::xmpText);
  ASSERT_NE(initial.get(), nullptr);

  Exiv2::Xmpdatum d(key, initial.get());

  std::string big(64 * 1024, 'A');  // 64 KiB
  big.replace(0, 5, "START");
  big.replace(big.size() - 3, 3, "END");

  const int rc = d.setValue(big);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(d.toString(), big);
}

// Exceptional/error case (observable): provide a numeric Value, parse valid then invalid input.
// We only assert observable outcomes: success should allow reading the number back; invalid input
// should either return non-zero or mark the Value not-ok (or both).
TEST_F(XmpdatumSetValueTest_1301, NumericValueValidThenInvalidInput_1301) {
  const Exiv2::XmpKey key = makeKey("numericProp");

  const auto initial = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(initial.get(), nullptr);

  Exiv2::Xmpdatum d(key, initial.get());

  // Valid numeric input
  {
    const int rc = d.setValue("123");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(123));
    EXPECT_TRUE(d.value().ok());
  }

  // Invalid numeric input (observable error via return code and/or ok()==false)
  {
    const int rc = d.setValue("not-a-number");
    const bool ok = d.value().ok();

    // At least one observable error signal should show up.
    EXPECT_TRUE(rc != 0 || !ok);
  }
}

}  // namespace