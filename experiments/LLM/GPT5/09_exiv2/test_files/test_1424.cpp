// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tags_int_print_xmp_date_1424.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>

// Exiv2 public headers
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Internal function under test
#include "tags_int.hpp"

namespace {

class PrintXmpDateTest_1424 : public ::testing::Test {
 protected:
  static std::string Print(const Exiv2::Value& v) {
    std::ostringstream os;
    Exiv2::Internal::printXmpDate(os, v, nullptr);
    return os.str();
  }

  static std::unique_ptr<Exiv2::Value> MakeValue(Exiv2::TypeId type, const std::string& s) {
    std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(type));
    EXPECT_NE(v.get(), nullptr);
    v->read(s);
    return v;
  }
};

TEST_F(PrintXmpDateTest_1424, FormatsXmpTextSize19_ReplacesTAndHyphens_1424) {
  auto v = MakeValue(Exiv2::xmpText, "2010-12-31T23:59:59");
  EXPECT_EQ(Print(*v), "2010:12:31 23:59:59");
}

TEST_F(PrintXmpDateTest_1424, FormatsXmpTextSize20_TrailingZIsRemoved_1424) {
  auto v = MakeValue(Exiv2::xmpText, "2010-12-31T23:59:59Z");
  EXPECT_EQ(Print(*v), "2010:12:31 23:59:59");
}

TEST_F(PrintXmpDateTest_1424, NonXmpTextType_PassthroughToValueOutput_1424) {
  // Same-looking string, but typeId != xmpText => must stream the Value as-is.
  auto v = MakeValue(Exiv2::asciiString, "2010-12-31T23:59:59Z");
  EXPECT_EQ(Print(*v), v->toString());
}

TEST_F(PrintXmpDateTest_1424, XmpTextWrongSize_PassthroughToValueOutput_1424) {
  // Size is not 19 or 20 => must stream the Value as-is.
  auto v = MakeValue(Exiv2::xmpText, "2010-12-31T23:59");  // length != 19/20
  EXPECT_EQ(Print(*v), v->toString());
}

TEST_F(PrintXmpDateTest_1424, XmpTextSize20WithoutZ_DoesNotStripLastChar_1424) {
  // Size 20, but last char != 'Z' => no stripping, only replacements.
  auto v = MakeValue(Exiv2::xmpText, "2010-12-31T23:59:59+");
  EXPECT_EQ(Print(*v), "2010:12:31 23:59:59+");
}

}  // namespace