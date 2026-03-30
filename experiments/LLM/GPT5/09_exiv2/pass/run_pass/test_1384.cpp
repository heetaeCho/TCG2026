// File: test_tags_int_print0x0005_1384.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// The function under test lives in tags_int.cpp (Exiv2::Internal namespace).
// Forward declaration is enough for unit tests as long as it is linked from the real library/object.
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0005(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class TagsIntPrint0x0005Test_1384 : public ::testing::Test {
 protected:
  // Helper to build a Value of a given TypeId and read from a string.
  static Exiv2::Value::UniquePtr makeValueFromString(Exiv2::TypeId typeId, const std::string& s) {
    auto v = Exiv2::Value::create(typeId);
    // read() is part of the public Value interface; return code semantics are not assumed here.
    (void)v->read(s);
    return v;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::print0x0005(os, v, md);
    return os.str();
  }
};

TEST_F(TagsIntPrint0x0005Test_1384, ReturnsSameStreamReference_1384) {
  auto v = makeValueFromString(Exiv2::unsignedByte, "0");

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::print0x0005(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(TagsIntPrint0x0005Test_1384, PrintsAboveSeaLevelForZero_1384) {
  auto v = makeValueFromString(Exiv2::unsignedByte, "0");

  const std::string outNullMd = render(*v, nullptr);
  EXPECT_NE(outNullMd.find("Above sea level"), std::string::npos);

  Exiv2::ExifData md;
  const std::string outWithMd = render(*v, &md);
  EXPECT_NE(outWithMd.find("Above sea level"), std::string::npos);
}

TEST_F(TagsIntPrint0x0005Test_1384, PrintsBelowSeaLevelForOne_1384) {
  auto v = makeValueFromString(Exiv2::unsignedByte, "1");

  const std::string outNullMd = render(*v, nullptr);
  EXPECT_NE(outNullMd.find("Below sea level"), std::string::npos);

  Exiv2::ExifData md;
  const std::string outWithMd = render(*v, &md);
  EXPECT_NE(outWithMd.find("Below sea level"), std::string::npos);
}

TEST_F(TagsIntPrint0x0005Test_1384, UnknownValueDoesNotCrashAndProducesOutput_1384) {
  // Boundary / out-of-range value for the known mapping (0, 1).
  auto v = makeValueFromString(Exiv2::unsignedByte, "2");

  std::ostringstream os;
  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::print0x0005(os, *v, nullptr);
    EXPECT_EQ(&ret, &os);
  });

  // We do not assume exact formatting for unknown values; just that something is written.
  EXPECT_FALSE(os.str().empty());
}

}  // namespace