// File: test_tags_int_print0xa407_1417.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Declaration is expected to be available from Exiv2 internal headers.
#include "tags_int.hpp"

#include <sstream>
#include <string>

namespace {

// Helper: create a Value, read a numeric token into it (best-effort), and return it.
// We intentionally avoid relying on any internal behavior beyond the public interface.
static Exiv2::Value::UniquePtr makeNumericValueOrSkip(const std::string& token) {
  // Prefer an integer-like TypeId; if unavailable in this build, the test will still compile
  // but may fail at runtime. This is the most common choice for EXIF short/long tags.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  if (!v) return nullptr;
  // read(...) returns int; we don't assume exact semantics, only that it is callable.
  (void)v->read(token);
  return v;
}

static std::string renderPrint0xa407(const Exiv2::Value& value, const Exiv2::ExifData* md) {
  std::ostringstream os;
  Exiv2::Internal::print0xa407(os, value, md);
  return os.str();
}

}  // namespace

class Print0xa407Test_1417 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
};

TEST_F(Print0xa407Test_1417, MapsKnownValuesWithNullMetadata_1417) {
  struct Case {
    const char* token;
    const char* expected;
  };

  // Based strictly on the provided TagDetails table for exifGainControl.
  const Case cases[] = {
      {"0", "None"},
      {"1", "Low gain up"},
      {"2", "High gain up"},
      {"3", "Low gain down"},
      {"4", "High gain down"},
  };

  for (const auto& c : cases) {
    auto v = makeNumericValueOrSkip(c.token);
    ASSERT_NE(v, nullptr) << "Value::create returned null for token=" << c.token;

    const std::string out = renderPrint0xa407(*v, /*md=*/nullptr);

    // Observable behavior expectation: known codes should print the known label.
    EXPECT_EQ(out, std::string(c.expected)) << "token=" << c.token;
  }
}

TEST_F(Print0xa407Test_1417, MapsKnownValuesWithNonNullMetadata_1417) {
  auto v = makeNumericValueOrSkip("2");
  ASSERT_NE(v, nullptr);

  const std::string out = renderPrint0xa407(*v, &exif_);

  // With metadata present, output should still be a stable, user-facing label for known value.
  EXPECT_EQ(out, std::string("High gain up"));
}

TEST_F(Print0xa407Test_1417, OutOfRangeValueDoesNotCrashAndProducesSomeOutput_1417) {
  auto v = makeNumericValueOrSkip("5");
  ASSERT_NE(v, nullptr);

  const std::string out_null = renderPrint0xa407(*v, /*md=*/nullptr);
  const std::string out_md = renderPrint0xa407(*v, &exif_);

  // We do not assume "Unknown" vs numeric rendering; we only assert observable safety:
  // non-empty output and no crash for boundary/out-of-range.
  EXPECT_FALSE(out_null.empty());
  EXPECT_FALSE(out_md.empty());
}

TEST_F(Print0xa407Test_1417, NegativeLikeTokenDoesNotCrash_1417) {
  // Some Value implementations accept "-1" even for unsigned TypeIds by coercion or failing read().
  // We don't assume which; only that printing remains safe.
  auto v = makeNumericValueOrSkip("-1");
  ASSERT_NE(v, nullptr);

  const std::string out = renderPrint0xa407(*v, /*md=*/nullptr);
  EXPECT_FALSE(out.empty());
}

TEST_F(Print0xa407Test_1417, EmptyReadTokenStillAllowsPrinting_1417) {
  auto v = makeNumericValueOrSkip("");
  ASSERT_NE(v, nullptr);

  const std::string out = renderPrint0xa407(*v, /*md=*/nullptr);

  // We avoid assuming exact fallback text; just require observable, safe behavior.
  EXPECT_FALSE(out.empty());
}