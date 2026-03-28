// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Forward declaration (implementation lives in src/tags_int.cpp)
namespace Exiv2 {
namespace Internal {
std::ostream& printNormalSoftHard(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintNormalSoftHardTest_1421 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    if (v) {
      EXPECT_EQ(0, v->read(s));
    }
    return v;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::printNormalSoftHard(os, v, md);
    return os.str();
  }
};

TEST_F(PrintNormalSoftHardTest_1421, PrintsNormalForZero_1421) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_NE(out.find("Normal"), std::string::npos);
}

TEST_F(PrintNormalSoftHardTest_1421, PrintsSoftForOne_1421) {
  auto v = makeUShortValue("1");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_NE(out.find("Soft"), std::string::npos);
}

TEST_F(PrintNormalSoftHardTest_1421, PrintsHardForTwo_1421) {
  auto v = makeUShortValue("2");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_NE(out.find("Hard"), std::string::npos);
}

TEST_F(PrintNormalSoftHardTest_1421, WorksWithNonNullMetadataPointer_1421) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData md;
  const std::string out = render(*v, &md);
  EXPECT_NE(out.find("Normal"), std::string::npos);
}

TEST_F(PrintNormalSoftHardTest_1421, UnknownValueStillProducesSomeOutput_1421) {
  auto v = makeUShortValue("3");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_FALSE(out.empty());
}

TEST_F(PrintNormalSoftHardTest_1421, SameKnownValueIsConsistentWithNullOrEmptyMetadata_1421) {
  auto v = makeUShortValue("1");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData md;
  const std::string out_null = render(*v, nullptr);
  const std::string out_md = render(*v, &md);

  // For known values, the human-readable label should be present regardless of metadata.
  EXPECT_NE(out_null.find("Soft"), std::string::npos);
  EXPECT_NE(out_md.find("Soft"), std::string::npos);
}

}  // namespace