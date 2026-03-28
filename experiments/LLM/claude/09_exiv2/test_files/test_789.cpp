#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <string>
#include <memory>
#include <cmath>
#include <limits>

// Test fixture for Value tests
class ValueTest_789 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== StringValue Tests ====================

TEST_F(ValueTest_789, StringValueDefaultConstruction_789) {
  Exiv2::StringValue sv;
  EXPECT_EQ(sv.count(), 1u);
  EXPECT_EQ(sv.toString(), "");
}

TEST_F(ValueTest_789, StringValueReadFromString_789) {
  Exiv2::StringValue sv;
  sv.read("Hello World");
  EXPECT_EQ(sv.toString(), "Hello World");
}

TEST_F(ValueTest_789, StringValueCopy_789) {
  Exiv2::StringValue sv;
  sv.read("Test Copy");
  auto clone = sv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "Test Copy");
}

TEST_F(ValueTest_789, StringValueSize_789) {
  Exiv2::StringValue sv;
  sv.read("ABCDE");
  EXPECT_EQ(sv.size(), 5u);
}

TEST_F(ValueTest_789, StringValueEmptyString_789) {
  Exiv2::StringValue sv;
  sv.read("");
  EXPECT_EQ(sv.toString(), "");
  EXPECT_EQ(sv.size(), 0u);
}

TEST_F(ValueTest_789, StringValueToStringWithIndex_789) {
  Exiv2::StringValue sv;
  sv.read("Hello");
  // toString(n) should return same as toString() for StringValue
  EXPECT_EQ(sv.toString(0), sv.toString());
}

TEST_F(ValueTest_789, StringValueTypeId_789) {
  Exiv2::StringValue sv;
  EXPECT_EQ(sv.typeId(), Exiv2::string);
}

// ==================== XmpTextValue Tests ====================

TEST_F(ValueTest_789, XmpTextValueDefaultConstruction_789) {
  Exiv2::XmpTextValue xv;
  EXPECT_EQ(xv.toString(), "");
}

TEST_F(ValueTest_789, XmpTextValueRead_789) {
  Exiv2::XmpTextValue xv;
  xv.read("XMP Text Value");
  EXPECT_EQ(xv.toString(), "XMP Text Value");
}

TEST_F(ValueTest_789, XmpTextValueCount_789) {
  Exiv2::XmpTextValue xv;
  xv.read("test");
  EXPECT_EQ(xv.count(), 1u);
}

TEST_F(ValueTest_789, XmpTextValueTypeId_789) {
  Exiv2::XmpTextValue xv;
  EXPECT_EQ(xv.typeId(), Exiv2::xmpText);
}

TEST_F(ValueTest_789, XmpTextValueClone_789) {
  Exiv2::XmpTextValue xv;
  xv.read("Clone Me");
  auto clone = xv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "Clone Me");
}

// ==================== AsciiValue Tests ====================

TEST_F(ValueTest_789, AsciiValueDefaultConstruction_789) {
  Exiv2::AsciiValue av;
  EXPECT_EQ(av.typeId(), Exiv2::asciiString);
}

TEST_F(ValueTest_789, AsciiValueRead_789) {
  Exiv2::AsciiValue av;
  av.read("ASCII string");
  EXPECT_EQ(av.toString(), "ASCII string");
}

TEST_F(ValueTest_789, AsciiValueClone_789) {
  Exiv2::AsciiValue av;
  av.read("Clone ASCII");
  auto clone = av.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "Clone ASCII");
}

// ==================== UShortValue (ValueType<uint16_t>) Tests ====================

TEST_F(ValueTest_789, UShortValueDefaultConstruction_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  EXPECT_EQ(uv.typeId(), Exiv2::unsignedShort);
  EXPECT_EQ(uv.count(), 0u);
}

TEST_F(ValueTest_789, UShortValueReadSingleValue_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("42");
  EXPECT_EQ(uv.count(), 1u);
  EXPECT_EQ(uv.value_.at(0), 42);
}

TEST_F(ValueTest_789, UShortValueReadMultipleValues_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("1 2 3");
  EXPECT_EQ(uv.count(), 3u);
  EXPECT_EQ(uv.value_.at(0), 1);
  EXPECT_EQ(uv.value_.at(1), 2);
  EXPECT_EQ(uv.value_.at(2), 3);
}

TEST_F(ValueTest_789, UShortValueToString_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("100");
  EXPECT_EQ(uv.toString(), "100");
}

TEST_F(ValueTest_789, UShortValueClone_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("7 8 9");
  auto clone = uv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->count(), 3u);
}

TEST_F(ValueTest_789, UShortValueToInt64_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("500");
  EXPECT_EQ(uv.toInt64(0), 500);
}

// ==================== ULongValue (ValueType<uint32_t>) Tests ====================

TEST_F(ValueTest_789, ULongValueDefaultConstruction_789) {
  Exiv2::ValueType<uint32_t> ulv(Exiv2::unsignedLong);
  EXPECT_EQ(ulv.typeId(), Exiv2::unsignedLong);
  EXPECT_EQ(ulv.count(), 0u);
}

TEST_F(ValueTest_789, ULongValueRead_789) {
  Exiv2::ValueType<uint32_t> ulv(Exiv2::unsignedLong);
  ulv.read("100000");
  EXPECT_EQ(ulv.count(), 1u);
  EXPECT_EQ(ulv.value_.at(0), 100000u);
}

TEST_F(ValueTest_789, ULongValueMultipleValues_789) {
  Exiv2::ValueType<uint32_t> ulv(Exiv2::unsignedLong);
  ulv.read("1 2 3 4 5");
  EXPECT_EQ(ulv.count(), 5u);
}

// ==================== URationalValue Tests ====================

TEST_F(ValueTest_789, URationalValueDefaultConstruction_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  EXPECT_EQ(rv.typeId(), Exiv2::unsignedRational);
  EXPECT_EQ(rv.count(), 0u);
}

TEST_F(ValueTest_789, URationalValueRead_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("1/2");
  EXPECT_EQ(rv.count(), 1u);
  EXPECT_EQ(rv.toString(), "1/2");
}

TEST_F(ValueTest_789, URationalValueMultiple_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("1/2 3/4");
  EXPECT_EQ(rv.count(), 2u);
}

TEST_F(ValueTest_789, URationalValueToFloat_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("1/4");
  EXPECT_FLOAT_EQ(rv.toFloat(0), 0.25f);
}

TEST_F(ValueTest_789, URationalValueToInt64_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("10/5");
  EXPECT_EQ(rv.toInt64(0), 2);
}

TEST_F(ValueTest_789, URationalValueClone_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("3/7");
  auto clone = rv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "3/7");
}

TEST_F(ValueTest_789, URationalValueZeroDenominator_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("1/0");
  EXPECT_EQ(rv.count(), 1u);
  EXPECT_EQ(rv.toString(), "1/0");
}

// ==================== RationalValue (signed) Tests ====================

TEST_F(ValueTest_789, RationalValueRead_789) {
  Exiv2::RationalValue rv(Exiv2::signedRational);
  rv.read("-1/2");
  EXPECT_EQ(rv.count(), 1u);
  EXPECT_EQ(rv.toString(), "-1/2");
}

TEST_F(ValueTest_789, RationalValueToFloat_789) {
  Exiv2::RationalValue rv(Exiv2::signedRational);
  rv.read("-3/4");
  EXPECT_FLOAT_EQ(rv.toFloat(0), -0.75f);
}

TEST_F(ValueTest_789, RationalValueClone_789) {
  Exiv2::RationalValue rv(Exiv2::signedRational);
  rv.read("5/3");
  auto clone = rv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "5/3");
}

// ==================== DataValue Tests ====================

TEST_F(ValueTest_789, DataValueDefaultConstruction_789) {
  Exiv2::DataValue dv;
  EXPECT_EQ(dv.typeId(), Exiv2::undefined);
  EXPECT_EQ(dv.count(), 0u);
  EXPECT_EQ(dv.size(), 0u);
}

TEST_F(ValueTest_789, DataValueReadFromString_789) {
  Exiv2::DataValue dv;
  dv.read("48 49 50");  // ASCII for '0', '1', '2'
  EXPECT_EQ(dv.count(), 3u);
}

TEST_F(ValueTest_789, DataValueClone_789) {
  Exiv2::DataValue dv;
  dv.read("1 2 3");
  auto clone = dv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->count(), 3u);
}

TEST_F(ValueTest_789, DataValueTypeIdUndefined_789) {
  Exiv2::DataValue dv(Exiv2::undefined);
  EXPECT_EQ(dv.typeId(), Exiv2::undefined);
}

TEST_F(ValueTest_789, DataValueTypeIdUnsignedByte_789) {
  Exiv2::DataValue dv(Exiv2::unsignedByte);
  EXPECT_EQ(dv.typeId(), Exiv2::unsignedByte);
}

// ==================== CommentValue Tests ====================

TEST_F(ValueTest_789, CommentValueDefaultConstruction_789) {
  Exiv2::CommentValue cv;
  EXPECT_EQ(cv.typeId(), Exiv2::undefined);
}

TEST_F(ValueTest_789, CommentValueReadPlainString_789) {
  Exiv2::CommentValue cv;
  cv.read("A simple comment");
  EXPECT_EQ(cv.comment(), "A simple comment");
}

TEST_F(ValueTest_789, CommentValueReadWithCharset_789) {
  Exiv2::CommentValue cv;
  cv.read("charset=Ascii A comment with charset");
  std::string comment = cv.comment();
  EXPECT_FALSE(comment.empty());
}

TEST_F(ValueTest_789, CommentValueClone_789) {
  Exiv2::CommentValue cv;
  cv.read("Clone comment");
  auto clone = cv.clone();
  EXPECT_NE(clone.get(), nullptr);
}

TEST_F(ValueTest_789, CommentValueEmpty_789) {
  Exiv2::CommentValue cv;
  cv.read("");
  EXPECT_EQ(cv.comment(), "");
}

// ==================== DateValue Tests ====================

TEST_F(ValueTest_789, DateValueDefaultConstruction_789) {
  Exiv2::DateValue dv;
  EXPECT_EQ(dv.typeId(), Exiv2::date);
}

TEST_F(ValueTest_789, DateValueReadValidDate_789) {
  Exiv2::DateValue dv;
  int rc = dv.read("2023-06-15");
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(dv.toString(), "2023-06-15");
}

TEST_F(ValueTest_789, DateValueReadAnotherFormat_789) {
  Exiv2::DateValue dv;
  int rc = dv.read("20230615");
  EXPECT_EQ(rc, 0);
}

TEST_F(ValueTest_789, DateValueClone_789) {
  Exiv2::DateValue dv;
  dv.read("2023-01-01");
  auto clone = dv.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->toString(), "2023-01-01");
}

TEST_F(ValueTest_789, DateValueCount_789) {
  Exiv2::DateValue dv;
  dv.read("2023-12-25");
  EXPECT_EQ(dv.count(), 1u);
}

TEST_F(ValueTest_789, DateValueGetDate_789) {
  Exiv2::DateValue dv;
  dv.read("2023-06-15");
  const auto& date = dv.getDate();
  EXPECT_EQ(date.year, 2023);
  EXPECT_EQ(date.month, 6);
  EXPECT_EQ(date.day, 15);
}

// ==================== TimeValue Tests ====================

TEST_F(ValueTest_789, TimeValueDefaultConstruction_789) {
  Exiv2::TimeValue tv;
  EXPECT_EQ(tv.typeId(), Exiv2::time);
}

TEST_F(ValueTest_789, TimeValueReadValidTime_789) {
  Exiv2::TimeValue tv;
  int rc = tv.read("12:30:45");
  EXPECT_EQ(rc, 0);
}

TEST_F(ValueTest_789, TimeValueClone_789) {
  Exiv2::TimeValue tv;
  tv.read("08:15:30");
  auto clone = tv.clone();
  EXPECT_NE(clone.get(), nullptr);
}

TEST_F(ValueTest_789, TimeValueCount_789) {
  Exiv2::TimeValue tv;
  tv.read("23:59:59");
  EXPECT_EQ(tv.count(), 1u);
}

TEST_F(ValueTest_789, TimeValueGetTime_789) {
  Exiv2::TimeValue tv;
  tv.read("14:30:00");
  const auto& time = tv.getTime();
  EXPECT_EQ(time.hour, 14);
  EXPECT_EQ(time.minute, 30);
  EXPECT_EQ(time.second, 0);
}

// ==================== XmpArrayValue Tests ====================

TEST_F(ValueTest_789, XmpArrayValueBag_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpBag);
  EXPECT_EQ(xav.typeId(), Exiv2::xmpBag);
  EXPECT_EQ(xav.count(), 0u);
}

TEST_F(ValueTest_789, XmpArrayValueSeq_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpSeq);
  EXPECT_EQ(xav.typeId(), Exiv2::xmpSeq);
}

TEST_F(ValueTest_789, XmpArrayValueAlt_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpAlt);
  EXPECT_EQ(xav.typeId(), Exiv2::xmpAlt);
}

TEST_F(ValueTest_789, XmpArrayValueReadAddsElement_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpBag);
  xav.read("element1");
  EXPECT_EQ(xav.count(), 1u);
  EXPECT_EQ(xav.toString(0), "element1");
}

TEST_F(ValueTest_789, XmpArrayValueReadMultipleElements_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpBag);
  xav.read("element1");
  xav.read("element2");
  xav.read("element3");
  EXPECT_EQ(xav.count(), 3u);
  EXPECT_EQ(xav.toString(0), "element1");
  EXPECT_EQ(xav.toString(1), "element2");
  EXPECT_EQ(xav.toString(2), "element3");
}

TEST_F(ValueTest_789, XmpArrayValueClone_789) {
  Exiv2::XmpArrayValue xav(Exiv2::xmpBag);
  xav.read("item1");
  xav.read("item2");
  auto clone = xav.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->count(), 2u);
}

// ==================== LangAltValue Tests ====================

TEST_F(ValueTest_789, LangAltValueDefaultConstruction_789) {
  Exiv2::LangAltValue lav;
  EXPECT_EQ(lav.typeId(), Exiv2::langAlt);
  EXPECT_EQ(lav.count(), 0u);
}

TEST_F(ValueTest_789, LangAltValueReadWithLang_789) {
  Exiv2::LangAltValue lav;
  lav.read("lang=en-US Hello");
  EXPECT_EQ(lav.count(), 1u);
}

TEST_F(ValueTest_789, LangAltValueReadWithoutLang_789) {
  Exiv2::LangAltValue lav;
  lav.read("Hello without lang");
  EXPECT_EQ(lav.count(), 1u);
}

TEST_F(ValueTest_789, LangAltValueClone_789) {
  Exiv2::LangAltValue lav;
  lav.read("lang=de Hallo");
  auto clone = lav.clone();
  EXPECT_NE(clone.get(), nullptr);
  EXPECT_EQ(clone->count(), 1u);
}

// ==================== Value::create factory Tests ====================

TEST_F(ValueTest_789, ValueCreateUnsignedShort_789) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::unsignedShort);
}

TEST_F(ValueTest_789, ValueCreateString_789) {
  auto v = Exiv2::Value::create(Exiv2::string);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::string);
}

TEST_F(ValueTest_789, ValueCreateAsciiString_789) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::asciiString);
}

TEST_F(ValueTest_789, ValueCreateUnsignedLong_789) {
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::unsignedLong);
}

TEST_F(ValueTest_789, ValueCreateUnsignedRational_789) {
  auto v = Exiv2::Value::create(Exiv2::unsignedRational);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::unsignedRational);
}

TEST_F(ValueTest_789, ValueCreateSignedRational_789) {
  auto v = Exiv2::Value::create(Exiv2::signedRational);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::signedRational);
}

TEST_F(ValueTest_789, ValueCreateUndefined_789) {
  auto v = Exiv2::Value::create(Exiv2::undefined);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::undefined);
}

TEST_F(ValueTest_789, ValueCreateXmpText_789) {
  auto v = Exiv2::Value::create(Exiv2::xmpText);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::xmpText);
}

TEST_F(ValueTest_789, ValueCreateXmpBag_789) {
  auto v = Exiv2::Value::create(Exiv2::xmpBag);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::xmpBag);
}

TEST_F(ValueTest_789, ValueCreateXmpSeq_789) {
  auto v = Exiv2::Value::create(Exiv2::xmpSeq);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::xmpSeq);
}

TEST_F(ValueTest_789, ValueCreateLangAlt_789) {
  auto v = Exiv2::Value::create(Exiv2::langAlt);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::langAlt);
}

TEST_F(ValueTest_789, ValueCreateDate_789) {
  auto v = Exiv2::Value::create(Exiv2::date);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::date);
}

TEST_F(ValueTest_789, ValueCreateTime_789) {
  auto v = Exiv2::Value::create(Exiv2::time);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_EQ(v->typeId(), Exiv2::time);
}

// ==================== SignedShort ValueType Tests ====================

TEST_F(ValueTest_789, SignedShortValueRead_789) {
  Exiv2::ValueType<int16_t> sv(Exiv2::signedShort);
  sv.read("-100 200 -300");
  EXPECT_EQ(sv.count(), 3u);
  EXPECT_EQ(sv.value_.at(0), -100);
  EXPECT_EQ(sv.value_.at(1), 200);
  EXPECT_EQ(sv.value_.at(2), -300);
}

TEST_F(ValueTest_789, SignedShortValueToString_789) {
  Exiv2::ValueType<int16_t> sv(Exiv2::signedShort);
  sv.read("-42");
  EXPECT_EQ(sv.toString(), "-42");
}

// ==================== SignedLong ValueType Tests ====================

TEST_F(ValueTest_789, SignedLongValueRead_789) {
  Exiv2::ValueType<int32_t> slv(Exiv2::signedLong);
  slv.read("-1000000");
  EXPECT_EQ(slv.count(), 1u);
  EXPECT_EQ(slv.value_.at(0), -1000000);
}

// ==================== Float ValueType Tests ====================

TEST_F(ValueTest_789, FloatValueRead_789) {
  Exiv2::ValueType<float> fv(Exiv2::tiffFloat);
  fv.read("3.14");
  EXPECT_EQ(fv.count(), 1u);
  EXPECT_NEAR(fv.value_.at(0), 3.14f, 0.01f);
}

TEST_F(ValueTest_789, FloatValueMultipleValues_789) {
  Exiv2::ValueType<float> fv(Exiv2::tiffFloat);
  fv.read("1.1 2.2 3.3");
  EXPECT_EQ(fv.count(), 3u);
}

// ==================== Double ValueType Tests ====================

TEST_F(ValueTest_789, DoubleValueRead_789) {
  Exiv2::ValueType<double> dv(Exiv2::tiffDouble);
  dv.read("3.141592653589793");
  EXPECT_EQ(dv.count(), 1u);
  EXPECT_NEAR(dv.value_.at(0), 3.141592653589793, 1e-10);
}

// ==================== Edge cases ====================

TEST_F(ValueTest_789, StringValueLongString_789) {
  Exiv2::StringValue sv;
  std::string longStr(10000, 'x');
  sv.read(longStr);
  EXPECT_EQ(sv.toString(), longStr);
  EXPECT_EQ(sv.size(), 10000u);
}

TEST_F(ValueTest_789, URationalValueLargeNumerator_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("4294967295/1");
  EXPECT_EQ(rv.count(), 1u);
  EXPECT_EQ(rv.toString(), "4294967295/1");
}

TEST_F(ValueTest_789, UShortValueBoundaryMax_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("65535");
  EXPECT_EQ(uv.count(), 1u);
  EXPECT_EQ(uv.value_.at(0), 65535);
}

TEST_F(ValueTest_789, UShortValueBoundaryZero_789) {
  Exiv2::ValueType<uint16_t> uv(Exiv2::unsignedShort);
  uv.read("0");
  EXPECT_EQ(uv.count(), 1u);
  EXPECT_EQ(uv.value_.at(0), 0);
}

TEST_F(ValueTest_789, StringValueSpecialCharacters_789) {
  Exiv2::StringValue sv;
  sv.read("Hello\tWorld\n");
  EXPECT_EQ(sv.toString(), "Hello\tWorld\n");
}

TEST_F(ValueTest_789, CommentValueUnicodeCharset_789) {
  Exiv2::CommentValue cv;
  cv.read("charset=Unicode Test comment");
  // Should be able to read without crashing
  std::string comment = cv.comment();
  // We don't assert on the exact value since charset handling may vary
}

TEST_F(ValueTest_789, DateValueBoundaryDates_789) {
  Exiv2::DateValue dv;
  int rc = dv.read("0001-01-01");
  EXPECT_EQ(rc, 0);
}

TEST_F(ValueTest_789, TimeValueMidnight_789) {
  Exiv2::TimeValue tv;
  int rc = tv.read("00:00:00");
  EXPECT_EQ(rc, 0);
  const auto& time = tv.getTime();
  EXPECT_EQ(time.hour, 0);
  EXPECT_EQ(time.minute, 0);
  EXPECT_EQ(time.second, 0);
}

TEST_F(ValueTest_789, DataValueReadFromBytes_789) {
  Exiv2::DataValue dv;
  const uint8_t bytes[] = {0x00, 0x01, 0x02, 0xFF};
  dv.read(bytes, sizeof(bytes), Exiv2::invalidByteOrder);
  EXPECT_EQ(dv.count(), 4u);
  EXPECT_EQ(dv.size(), 4u);
}

TEST_F(ValueTest_789, StringValueReadReplacesOld_789) {
  Exiv2::StringValue sv;
  sv.read("First");
  EXPECT_EQ(sv.toString(), "First");
  sv.read("Second");
  EXPECT_EQ(sv.toString(), "Second");
}

TEST_F(ValueTest_789, URationalValueToRational_789) {
  Exiv2::URationalValue rv(Exiv2::unsignedRational);
  rv.read("3/4");
  auto rational = rv.toRational(0);
  EXPECT_EQ(rational.first, 3);
  EXPECT_EQ(rational.second, 4);
}

TEST_F(ValueTest_789, RationalValueToRational_789) {
  Exiv2::RationalValue rv(Exiv2::signedRational);
  rv.read("-5/8");
  auto rational = rv.toRational(0);
  EXPECT_EQ(rational.first, -5);
  EXPECT_EQ(rational.second, 8);
}
