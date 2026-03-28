// TEST_ID 738
// File: test_exifdatum_operator_assign_value_738.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <sstream>
#include <string>

namespace {

using Exiv2::Exifdatum;
using Exiv2::ExifKey;
using Exiv2::Value;

static Value::UniquePtr MakeValueFromString(Exiv2::TypeId type, const std::string& text) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  // Value::read(std::string) returns int; "0 means ok" is not guaranteed here,
  // so we only require that it doesn't throw and that value().toString() becomes observable later.
  (void)v->read(text);
  return v;
}

static Exifdatum MakeDatumWithInitialValue(const ExifKey& key,
                                           Exiv2::TypeId type,
                                           const std::string& text) {
  auto v = MakeValueFromString(type, text);
  return Exifdatum(key, v.get());
}

}  // namespace

class ExifdatumOperatorAssignValueTest_738 : public ::testing::Test {
 protected:
  ExifKey key_{"Exif.Image.Make"};
};

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_ReturnsSelf_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");

  auto newVal = MakeValueFromString(Exiv2::asciiString, "new");
  Exifdatum* returned = & (d = *newVal);

  EXPECT_EQ(returned, &d);
}

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_UpdatesToString_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");

  auto newVal = MakeValueFromString(Exiv2::asciiString, "updated-string");
  d = *newVal;

  EXPECT_EQ(d.toString(), std::string("updated-string"));
}

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_PreservesKey_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");
  const std::string beforeKey = d.key();

  auto newVal = MakeValueFromString(Exiv2::asciiString, "changed");
  d = *newVal;

  EXPECT_EQ(d.key(), beforeKey);
}

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_AllowsEmptyString_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");

  auto emptyVal = MakeValueFromString(Exiv2::asciiString, "");
  d = *emptyVal;

  EXPECT_EQ(d.toString(), std::string(""));
  EXPECT_EQ(d.count(), d.value().count());  // Observable consistency through public API
}

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_HandlesLargeString_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");

  std::string big(4096, 'x');
  auto bigVal = MakeValueFromString(Exiv2::asciiString, big);
  d = *bigVal;

  EXPECT_EQ(d.toString(), big);
}

TEST_F(ExifdatumOperatorAssignValueTest_738, OperatorAssignValue_AllowsTypeChange_738) {
  Exifdatum d = MakeDatumWithInitialValue(key_, Exiv2::asciiString, "initial");
  const Exiv2::TypeId beforeType = d.typeId();

  // Assign a different Value type (boundary: type change across assignment).
  auto shortVal = MakeValueFromString(Exiv2::unsignedShort, "42");
  d = *shortVal;

  // Observable: typeId should reflect the assigned Value (if Exifdatum stores/copies it).
  // If the library chooses to coerce types, the test still validates that something observable changed.
  EXPECT_NE(d.typeId(), beforeType);
  EXPECT_TRUE(d.typeId() == Exiv2::unsignedShort || d.typeId() == beforeType);

  // Observable numeric conversion should not crash; value depends on implementation.
  (void)d.toInt64(0);
}