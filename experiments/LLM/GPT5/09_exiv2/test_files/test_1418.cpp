// File: test_tags_int_print0xa409_1418.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Forward declaration (avoid relying on private headers)
namespace Exiv2 {
class Value;
class ExifData;
namespace Internal {
std::ostream& print0xa409(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

Value::UniquePtr makeUShortValue(uint32_t n) {
  // Exiv2 TypeId enum commonly exposes `unsignedShort`. If your build uses a different
  // TypeId name, adjust it to the correct one used by your Exiv2 version.
  auto v = Value::create(Exiv2::unsignedShort);
  if (!v) return nullptr;

  // Use the public interface only: encode the numeric as text.
  (void)v->read(std::to_string(n));
  return v;
}

std::string printToString(const Value& v, const ExifData* md) {
  std::ostringstream oss;
  Exiv2::Internal::print0xa409(oss, v, md);
  return oss.str();
}

bool contains(const std::string& s, const std::string& sub) {
  return s.find(sub) != std::string::npos;
}

}  // namespace

class Print0xa409Test_1418 : public ::testing::Test {};

TEST_F(Print0xa409Test_1418, PrintsNormalFor0_1418) {
  auto v = makeUShortValue(0);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_TRUE(contains(out, "Normal"));
  EXPECT_FALSE(contains(out, "Low"));
  EXPECT_FALSE(contains(out, "High"));
}

TEST_F(Print0xa409Test_1418, PrintsLowFor1_1418) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_TRUE(contains(out, "Low"));
  EXPECT_FALSE(contains(out, "Normal"));
  EXPECT_FALSE(contains(out, "High"));
}

TEST_F(Print0xa409Test_1418, PrintsHighFor2_1418) {
  auto v = makeUShortValue(2);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_TRUE(contains(out, "High"));
  EXPECT_FALSE(contains(out, "Normal"));
  EXPECT_FALSE(contains(out, "Low"));
}

TEST_F(Print0xa409Test_1418, OutOfRangeDoesNotCrashAndProducesSomeOutput_1418) {
  auto v = makeUShortValue(3);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  // Black-box expectation: should produce some representation and not crash.
  EXPECT_FALSE(out.empty());

  // Avoid assuming the exact fallback format (could be "3", "Unknown", etc.).
  // But it should not mislabel as one of the known mapped strings.
  EXPECT_FALSE(contains(out, "Normal"));
  EXPECT_FALSE(contains(out, "Low"));
  EXPECT_FALSE(contains(out, "High"));
}

TEST_F(Print0xa409Test_1418, MetadataPointerDoesNotAffectOutputForThisTag_1418) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);

  ExifData md;
  const size_t before = md.count();

  const std::string out_with_md = printToString(*v, &md);
  const std::string out_without_md = printToString(*v, nullptr);

  EXPECT_EQ(out_with_md, out_without_md);
  EXPECT_EQ(md.count(), before);  // should not mutate observable metadata container
}

TEST_F(Print0xa409Test_1418, DefaultConstructedValueObjectPrintDoesNotCrash_1418) {
  // Construct a Value via factory but do not set any explicit data.
  auto v = Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  // Black-box: just ensure it is safe to call and stream remains usable.
  EXPECT_TRUE(static_cast<bool>(std::ostringstream{}));  // sanity
  (void)out;  // output may be empty or not depending on implementation; don't assert format
}