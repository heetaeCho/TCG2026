// TEST_ID 675
// Unit tests for Exiv2::Iptcdatum::typeName()
// File: test_iptcdatum_typename_675.cpp

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <string>

namespace {

class IptcdatumTest_675 : public ::testing::Test {
 protected:
  // Use a commonly-valid IPTC key string (exact validity is handled by Exiv2).
  // If the library accepts other keys in your build, these tests still only
  // assert observable relationships through the public interface.
  static Exiv2::IptcKey MakeKey() {
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumTest_675, TypeNameMatchesTypeInfoForCurrentTypeId_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const Exiv2::TypeId tid = datum.typeId();
  const char* expected = Exiv2::TypeInfo::typeName(tid);

  // Black-box contract check for the visible implementation:
  // typeName() should match TypeInfo::typeName(typeId()).
  EXPECT_EQ(datum.typeName(), expected);
}

TEST_F(IptcdatumTest_675, TypeNameIsStableAcrossRepeatedCalls_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const char* first = datum.typeName();
  const char* second = datum.typeName();
  const char* third = datum.typeName();

  EXPECT_EQ(second, first);
  EXPECT_EQ(third, first);

  // Also matches TypeInfo for the current type id.
  EXPECT_EQ(datum.typeName(), Exiv2::TypeInfo::typeName(datum.typeId()));
}

TEST_F(IptcdatumTest_675, TypeNameWorksThroughConstReference_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const Exiv2::Iptcdatum& cref = datum;
  EXPECT_EQ(cref.typeName(), Exiv2::TypeInfo::typeName(cref.typeId()));
}

TEST_F(IptcdatumTest_675, TypeNameMatchesTypeInfoAfterValueAssignments_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  // Exercise observable mutators without assuming how they affect internal state.
  // After each mutation, the relationship typeName() == TypeInfo::typeName(typeId())
  // must still hold.
  (void)(datum = static_cast<uint16_t>(0));
  EXPECT_EQ(datum.typeName(), Exiv2::TypeInfo::typeName(datum.typeId()));

  (void)(datum = static_cast<uint16_t>(65535));
  EXPECT_EQ(datum.typeName(), Exiv2::TypeInfo::typeName(datum.typeId()));

  (void)(datum = std::string());
  EXPECT_EQ(datum.typeName(), Exiv2::TypeInfo::typeName(datum.typeId()));

  (void)(datum = std::string("abc"));
  EXPECT_EQ(datum.typeName(), Exiv2::TypeInfo::typeName(datum.typeId()));
}

TEST_F(IptcdatumTest_675, TypeNameMatchesTypeInfoAfterCopyAndAssignment_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum original(key, /*pValue=*/nullptr);
  (void)(original = std::string("value"));

  Exiv2::Iptcdatum copy(original);
  EXPECT_EQ(copy.typeName(), Exiv2::TypeInfo::typeName(copy.typeId()));

  Exiv2::Iptcdatum assigned(key, /*pValue=*/nullptr);
  assigned = original;
  EXPECT_EQ(assigned.typeName(), Exiv2::TypeInfo::typeName(assigned.typeId()));
}

TEST_F(IptcdatumTest_675, TypeNameHandlesPotentiallyUnknownTypeIdGracefully_675) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  // We do NOT assume whether datum.typeId() maps to a known name or nullptr.
  // We only verify that datum.typeName() mirrors TypeInfo::typeName(datum.typeId()).
  const Exiv2::TypeId tid = datum.typeId();
  const char* expected = Exiv2::TypeInfo::typeName(tid);

  // If expected is nullptr, datum.typeName() should also be nullptr; if not, it should match.
  EXPECT_EQ(datum.typeName(), expected);
}

}  // namespace