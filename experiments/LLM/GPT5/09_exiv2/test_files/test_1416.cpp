// File: test_print0xa406_1416.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& print0xa406(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa406Test_1416 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeValueFromString(Exiv2::TypeId type, const std::string& s) {
    auto v = Exiv2::Value::create(type);
    ASSERT_NE(v.get(), nullptr);
    // Use only the public interface; assume read(string) exists and is observable through output.
    (void)v->read(s);
    return v;
  }

  static std::string renderWithMetadata(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    Exiv2::Internal::print0xa406(oss, v, md);
    return oss.str();
  }
};

TEST_F(Print0xa406Test_1416, ReturnsSameStreamReference_1416) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "0");
  std::ostringstream oss;

  std::ostream& ret = Exiv2::Internal::print0xa406(oss, *v, nullptr);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
}

TEST_F(Print0xa406Test_1416, PrintsStandardForZero_1416) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "0");

  const std::string out = renderWithMetadata(*v, nullptr);

  EXPECT_EQ(out, "Standard");
}

TEST_F(Print0xa406Test_1416, PrintsNightSceneForThree_1416) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "3");

  const std::string out = renderWithMetadata(*v, nullptr);

  EXPECT_EQ(out, "Night scene");
}

TEST_F(Print0xa406Test_1416, AppendsToExistingStreamContent_1416) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "1");
  std::ostringstream oss;
  oss << "prefix:";

  Exiv2::Internal::print0xa406(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "prefix:Landscape");
}

TEST_F(Print0xa406Test_1416, OutputIsConsistentWithAndWithoutMetadata_1416) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "2");

  Exiv2::ExifData md;  // empty metadata should still be a valid pointer argument

  const std::string out_null = renderWithMetadata(*v, nullptr);
  const std::string out_md = renderWithMetadata(*v, &md);

  EXPECT_EQ(out_null, out_md);
  EXPECT_EQ(out_md, "Portrait");
}

TEST_F(Print0xa406Test_1416, BoundaryValuesZeroAndThreeAreDistinct_1416) {
  auto v0 = makeValueFromString(Exiv2::unsignedShort, "0");
  auto v3 = makeValueFromString(Exiv2::unsignedShort, "3");

  const std::string out0 = renderWithMetadata(*v0, nullptr);
  const std::string out3 = renderWithMetadata(*v3, nullptr);

  EXPECT_NE(out0, out3);
  EXPECT_EQ(out0, "Standard");
  EXPECT_EQ(out3, "Night scene");
}

}  // namespace