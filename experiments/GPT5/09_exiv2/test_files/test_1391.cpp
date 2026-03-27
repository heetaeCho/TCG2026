// File: test_tags_int_print0x001e_1391.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Unit-under-test declaration (implemented in ./TestProjects/exiv2/src/tags_int.cpp)
namespace Exiv2 {
namespace Internal {
std::ostream& print0x001e(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class TagsIntPrint0x001eTest_1391 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValueFromString(const std::string& s) {
    // Use public factory + read API only (black-box friendly).
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v, nullptr);
    (void)v->read(s);  // Behavior is implementation-defined; tests below avoid assuming return codes.
    return v;
  }

  static std::string printToString(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    std::ostream& ret = Exiv2::Internal::print0x001e(oss, v, md);
    // Observable behavior: returned reference should be the passed stream (common stream-manipulator contract).
    EXPECT_EQ(&ret, &oss);
    return oss.str();
  }
};

TEST_F(TagsIntPrint0x001eTest_1391, ReturnsSameStreamReference_NullMetadata_1391) {
  auto v = makeUShortValueFromString("0");
  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x001e(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(TagsIntPrint0x001eTest_1391, DoesNotThrow_WithNullMetadata_1391) {
  auto v = makeUShortValueFromString("0");
  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x001e(oss, *v, nullptr);
  });
}

TEST_F(TagsIntPrint0x001eTest_1391, DoesNotThrow_WithNonNullMetadata_1391) {
  // Metadata is an optional input for the interface; verify it is accepted.
  Exiv2::ExifData md;
  auto v = makeUShortValueFromString("1");
  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x001e(oss, *v, &md);
  });
}

TEST_F(TagsIntPrint0x001eTest_1391, PrintsMappedDescription_ForValueZero_1391) {
  // tags_int.cpp exposes TagDetails for exifGPSDifferential: 0 -> "Without correction".
  auto v = makeUShortValueFromString("0");
  const std::string out = printToString(*v, nullptr);

  // Observable expectation: human-readable mapping is typically used.
  // (We do NOT assume exact formatting, only that the description appears.)
  EXPECT_NE(out.find("Without correction"), std::string::npos);
}

TEST_F(TagsIntPrint0x001eTest_1391, PrintsMappedDescription_ForValueOne_1391) {
  // 1 -> "Correction applied"
  auto v = makeUShortValueFromString("1");
  const std::string out = printToString(*v, nullptr);

  EXPECT_NE(out.find("Correction applied"), std::string::npos);
}

TEST_F(TagsIntPrint0x001eTest_1391, ProducesDifferentOutput_ForDifferentMappedValues_1391) {
  auto v0 = makeUShortValueFromString("0");
  auto v1 = makeUShortValueFromString("1");

  const std::string out0 = printToString(*v0, nullptr);
  const std::string out1 = printToString(*v1, nullptr);

  EXPECT_NE(out0, out1);
}

TEST_F(TagsIntPrint0x001eTest_1391, OutOfRangeValue_DoesNotMatchKnownDescriptions_1391) {
  // Boundary/exceptional-ish case: value not present in TagDetails table (e.g., 2).
  auto v = makeUShortValueFromString("2");
  const std::string out = printToString(*v, nullptr);

  // We avoid assuming exact fallback formatting. We only assert it does not claim
  // one of the known mapped descriptions.
  EXPECT_EQ(out.find("Without correction"), std::string::npos);
  EXPECT_EQ(out.find("Correction applied"), std::string::npos);

  // And should still produce *some* output (could be numeric or "Unknown").
  EXPECT_FALSE(out.empty());
}

TEST_F(TagsIntPrint0x001eTest_1391, HandlesValueWithWhitespaceInput_1391) {
  // Boundary condition around parsing input. We don't assume parsing rules; just that printing is safe.
  auto v = makeUShortValueFromString(" 1 ");
  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x001e(oss, *v, nullptr);
  });
  EXPECT_EQ(&oss, &Exiv2::Internal::print0x001e(oss, *v, nullptr));
}

}  // namespace