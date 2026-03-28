// File: test_tags_operator_ostream_1347.cpp
#include <gtest/gtest.h>

#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace {

class TagInfoOstreamTest_1347 : public ::testing::Test {};

static std::string ToStringViaOstream(const Exiv2::TagInfo& ti) {
  std::ostringstream os;
  os << ti;
  return os.str();
}

TEST_F(TagInfoOstreamTest_1347, ReturnsSameOstreamReference_1347) {
  // Arrange
  const Exiv2::TagInfo ti{
      static_cast<uint16_t>(0x1234),
      "TestTag",
      "Test Title",
      "Test description",
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::SectionId>(0),
      Exiv2::unsignedShort,
      1,
      nullptr,
  };

  // Act
  std::ostringstream os;
  std::ostream& ref = (os << ti);

  // Assert
  EXPECT_EQ(&ref, &os);
}

TEST_F(TagInfoOstreamTest_1347, IncludesHexTagWithZeroPadding_1347) {
  // Arrange
  const Exiv2::TagInfo ti{
      static_cast<uint16_t>(0x0001),
      "TestTag",
      "Test Title",
      "Test description",
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::SectionId>(0),
      Exiv2::unsignedShort,
      1,
      nullptr,
  };

  // Act
  const std::string s = ToStringViaOstream(ti);

  // Assert (observable formatting from operator<<)
  EXPECT_NE(s.find(",0x0001,"), std::string::npos) << s;
}

TEST_F(TagInfoOstreamTest_1347, EscapesDoubleQuotesInDescription_1347) {
  // Arrange: description contains quotes which must be doubled, and whole field must be quoted.
  const Exiv2::TagInfo ti{
      static_cast<uint16_t>(0x1234),
      "TestTag",
      "Test Title",
      "Desc with \"quotes\" inside",
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::SectionId>(0),
      Exiv2::unsignedShort,
      1,
      nullptr,
  };

  // Act
  const std::string s = ToStringViaOstream(ti);

  // Assert: last field should contain the escaped/quoted description.
  // We don't assume earlier fields' exact values (black-box), only the observable escaping behavior.
  const std::string escaped = "\"Desc with \"\"quotes\"\" inside\"";
  EXPECT_NE(s.find(escaped), std::string::npos) << s;

  // Also ensure tag is present in hex with padding.
  EXPECT_NE(s.find(",0x1234,"), std::string::npos) << s;
}

TEST_F(TagInfoOstreamTest_1347, EmptyDescriptionStillQuoted_1347) {
  // Arrange
  const Exiv2::TagInfo ti{
      static_cast<uint16_t>(0x00ab),
      "TestTag",
      "Test Title",
      "",
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::SectionId>(0),
      Exiv2::unsignedShort,
      1,
      nullptr,
  };

  // Act
  const std::string s = ToStringViaOstream(ti);

  // Assert: description field should be an empty quoted string.
  EXPECT_NE(s.find("\"\""), std::string::npos) << s;
  EXPECT_NE(s.find(",0x00ab,"), std::string::npos) << s;
}

TEST_F(TagInfoOstreamTest_1347, DoesNotThrowWhenStreaming_1347) {
  const Exiv2::TagInfo ti{
      static_cast<uint16_t>(0xffff),
      "TestTag",
      "Test Title",
      "Any",
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::SectionId>(0),
      Exiv2::unsignedShort,
      1,
      nullptr,
  };

  std::ostringstream os;
  EXPECT_NO_THROW({ os << ti; });
}

}  // namespace