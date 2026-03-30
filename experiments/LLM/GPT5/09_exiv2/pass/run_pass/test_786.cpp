// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_value_create_786.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

using Exiv2::TypeId;
using Exiv2::Value;

// Fixture name must include TEST_ID.
class ValueCreateTest_786 : public ::testing::Test {};

TEST_F(ValueCreateTest_786, CreateReturnsNonNullForRepresentativeTypeIds_786) {
  const TypeId ids[] = {
      Exiv2::invalidTypeId, Exiv2::unsignedByte,   Exiv2::signedByte,  Exiv2::asciiString,
      Exiv2::unsignedShort, Exiv2::unsignedLong,   Exiv2::tiffIfd,     Exiv2::unsignedRational,
      Exiv2::undefined,     Exiv2::signedShort,    Exiv2::signedLong,  Exiv2::signedRational,
      Exiv2::tiffFloat,     Exiv2::tiffDouble,     Exiv2::string,      Exiv2::date,
      Exiv2::time,          Exiv2::comment,        Exiv2::xmpText,     Exiv2::xmpAlt,
      Exiv2::xmpBag,        Exiv2::xmpSeq,         Exiv2::langAlt,
      // Known enum values not explicitly handled in the provided switch are still valid inputs.
      Exiv2::directory,     Exiv2::unsignedLongLong, Exiv2::signedLongLong, Exiv2::tiffIfd8,
      Exiv2::lastTypeId,
  };

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr) << "create(" << static_cast<int>(id) << ") returned null";
    // Observable via public interface.
    EXPECT_TRUE(v->ok()) << "ok() should be true after create(" << static_cast<int>(id) << ")";
  }
}

TEST_F(ValueCreateTest_786, CreateSetsTypeIdToRequestedId_786) {
  const TypeId ids[] = {
      Exiv2::invalidTypeId, Exiv2::unsignedByte, Exiv2::signedByte, Exiv2::asciiString,
      Exiv2::unsignedShort, Exiv2::unsignedLong, Exiv2::tiffIfd, Exiv2::unsignedRational,
      Exiv2::undefined, Exiv2::signedShort, Exiv2::signedLong, Exiv2::signedRational,
      Exiv2::tiffFloat, Exiv2::tiffDouble, Exiv2::string, Exiv2::date, Exiv2::time,
      Exiv2::comment, Exiv2::xmpText, Exiv2::xmpAlt, Exiv2::xmpBag, Exiv2::xmpSeq, Exiv2::langAlt,
      Exiv2::directory, Exiv2::unsignedLongLong, Exiv2::signedLongLong, Exiv2::tiffIfd8, Exiv2::lastTypeId,
  };

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), id) << "typeId() mismatch for create(" << static_cast<int>(id) << ")";
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsExpectedConcreteTypeForCommonMappings_786) {
  {
    auto v = Value::create(Exiv2::asciiString);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::AsciiValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::string);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::StringValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::date);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::DateValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::time);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::TimeValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::comment);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::CommentValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::xmpText);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::XmpTextValue*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::langAlt);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::LangAltValue*>(v.get()), nullptr);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsXmpArrayValueForXmpArrayTypeIds_786) {
  const TypeId ids[] = {Exiv2::xmpBag, Exiv2::xmpSeq, Exiv2::xmpAlt};

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::XmpArrayValue*>(v.get()), nullptr)
        << "Expected XmpArrayValue for typeId " << static_cast<int>(id);
    EXPECT_EQ(v->typeId(), id);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsDataValueForByteAndInvalidTypeIds_786) {
  const TypeId ids[] = {Exiv2::invalidTypeId, Exiv2::signedByte, Exiv2::unsignedByte};

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::DataValue*>(v.get()), nullptr)
        << "Expected DataValue for typeId " << static_cast<int>(id);
    EXPECT_EQ(v->typeId(), id);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsValueTypeForIntegralAndFloatMappings_786) {
  {
    auto v = Value::create(Exiv2::unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<uint16_t>*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::signedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<int16_t>*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::signedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<int32_t>*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::tiffFloat);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<float>*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::tiffDouble);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<double>*>(v.get()), nullptr);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsValueTypeUint32ForUnsignedLongAndTiffIfd_786) {
  const TypeId ids[] = {Exiv2::unsignedLong, Exiv2::tiffIfd};

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<uint32_t>*>(v.get()), nullptr)
        << "Expected ValueType<uint32_t> for typeId " << static_cast<int>(id);
    EXPECT_EQ(v->typeId(), id);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsValueTypeForRationalMappings_786) {
  {
    auto v = Value::create(Exiv2::unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<Exiv2::URational>*>(v.get()), nullptr);
  }
  {
    auto v = Value::create(Exiv2::signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::ValueType<Exiv2::Rational>*>(v.get()), nullptr);
  }
}

TEST_F(ValueCreateTest_786, CreateReturnsDataValueForUnhandledEnumValues_786) {
  // Based on the provided switch: these are not explicitly handled and therefore go to default.
  const TypeId ids[] = {Exiv2::directory, Exiv2::unsignedLongLong, Exiv2::signedLongLong, Exiv2::tiffIfd8,
                        Exiv2::lastTypeId};

  for (const auto id : ids) {
    auto v = Value::create(id);
    ASSERT_NE(v, nullptr);
    EXPECT_NE(dynamic_cast<Exiv2::DataValue*>(v.get()), nullptr)
        << "Expected default DataValue for typeId " << static_cast<int>(id);
    EXPECT_EQ(v->typeId(), id);
  }
}

TEST_F(ValueCreateTest_786, CreateAcceptsOutOfRangeTypeIdAndReturnsNonNull_786) {
  // Boundary / robustness: TypeId is an enum, but callers can cast arbitrary values.
  const auto weird = static_cast<TypeId>(-1);
  auto v = Value::create(weird);
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(v->typeId(), weird);
  EXPECT_TRUE(v->ok());
  // In the provided switch, default returns DataValue(typeId).
  EXPECT_NE(dynamic_cast<Exiv2::DataValue*>(v.get()), nullptr);
}

TEST_F(ValueCreateTest_786, CloneProducesDistinctObjectWithSameTypeId_786) {
  const TypeId ids[] = {Exiv2::asciiString, Exiv2::unsignedShort, Exiv2::unsignedLong, Exiv2::xmpAlt,
                        Exiv2::comment, Exiv2::undefined};

  for (const auto id : ids) {
    auto original = Value::create(id);
    ASSERT_NE(original, nullptr);

    auto copy = original->clone();
    ASSERT_NE(copy, nullptr) << "clone() returned null for typeId " << static_cast<int>(id);

    EXPECT_NE(copy.get(), original.get());
    EXPECT_EQ(copy->typeId(), original->typeId());
    EXPECT_EQ(copy->ok(), original->ok());
  }
}

}  // namespace