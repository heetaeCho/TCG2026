// File: test_tags_int_print0xa301_1410.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& print0xa301(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa301Test_1410 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    // Use a numeric value type and feed "v" via the public string read interface.
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(val.get(), nullptr);
    std::ostringstream ss;
    ss << v;
    (void)val->read(ss.str());
    return val;
  }

  static std::string runPrint(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::print0xa301(os, v, md);
    return os.str();
  }
};

TEST_F(Print0xa301Test_1410, ReturnsSameStreamReference_1410) {
  auto v = makeUShortValue(1);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::print0xa301(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(Print0xa301Test_1410, PrintsKnownSceneTypeForValueOne_1410) {
  auto v = makeUShortValue(1);

  const std::string out = runPrint(*v, nullptr);

  // Based on the provided TagDetails table: {1, "Directly photographed"}
  EXPECT_NE(out.find("Directly photographed"), std::string::npos);
}

TEST_F(Print0xa301Test_1410, OutputDiffersBetweenKnownAndUnknownValues_1410) {
  auto known = makeUShortValue(1);
  auto unknown = makeUShortValue(2);

  const std::string outKnown = runPrint(*known, nullptr);
  const std::string outUnknown = runPrint(*unknown, nullptr);

  // Black-box expectation: an unknown value should not produce the exact same
  // rendering as the known mapped value.
  EXPECT_NE(outKnown, outUnknown);
  EXPECT_NE(outKnown.find("Directly photographed"), std::string::npos);
}

TEST_F(Print0xa301Test_1410, AcceptsNullMetadataPointer_1410) {
  auto v = makeUShortValue(1);

  EXPECT_NO_THROW({
    std::ostringstream os;
    Exiv2::Internal::print0xa301(os, *v, nullptr);
  });
}

TEST_F(Print0xa301Test_1410, MetadataDoesNotChangeRenderingForThisTag_1410) {
  auto v = makeUShortValue(1);

  Exiv2::ExifData md;  // empty metadata object

  const std::string outNull = runPrint(*v, nullptr);
  const std::string outMd = runPrint(*v, &md);

  EXPECT_EQ(outNull, outMd);
  EXPECT_NE(outMd.find("Directly photographed"), std::string::npos);
}

TEST_F(Print0xa301Test_1410, HandlesValueWithNoDataGracefully_1410) {
  // Create a value object but do not populate it with read()/setDataArea().
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  EXPECT_NO_THROW({
    std::ostringstream os;
    Exiv2::Internal::print0xa301(os, *v, nullptr);
    // We only require that the call is safe and produces some observable stream state.
    EXPECT_TRUE(os.good());
  });
}

}  // namespace