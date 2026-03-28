// ============================================================================
//  TEST_ID: 691
//  Unit tests for Exiv2::Iptcdatum::setValue(const std::string&)
//  File under test: ./TestProjects/exiv2/src/iptc.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class IptcdatumTest_691 : public ::testing::Test {
 protected:
  // Commonly-used, well-known IPTC keys in Exiv2:
  // - ObjectName: string-like
  // - Urgency: numeric-like
  static Exiv2::IptcKey MakeKey_ObjectName() { return Exiv2::IptcKey("Iptc.Application2.ObjectName"); }
  static Exiv2::IptcKey MakeKey_Urgency() { return Exiv2::IptcKey("Iptc.Application2.Urgency"); }
};

TEST_F(IptcdatumTest_691, SetValueOnNullInitialValue_SucceedsAndUpdatesToString_691) {
  const Exiv2::IptcKey key = MakeKey_ObjectName();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const int rc = datum.setValue(std::string("hello"));
  EXPECT_EQ(0, rc);

  // Observable behavior via public interface.
  EXPECT_EQ("hello", datum.toString());
}

TEST_F(IptcdatumTest_691, SetValueTwice_UpdatesObservableValue_691) {
  const Exiv2::IptcKey key = MakeKey_ObjectName();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(0, datum.setValue(std::string("first")));
  EXPECT_EQ("first", datum.toString());

  EXPECT_EQ(0, datum.setValue(std::string("second")));
  EXPECT_EQ("second", datum.toString());
}

TEST_F(IptcdatumTest_691, SetValueEmptyString_HandledWithoutCrashAndObservable_691) {
  const Exiv2::IptcKey key = MakeKey_ObjectName();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const int rc = datum.setValue(std::string());
  // For string-like datasets, empty strings are typically valid.
  EXPECT_EQ(0, rc);
  EXPECT_EQ("", datum.toString());
}

TEST_F(IptcdatumTest_691, SetValueLargeString_HandledWithoutCrash_691) {
  const Exiv2::IptcKey key = MakeKey_ObjectName();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const std::string large(1024, 'x');
  const int rc = datum.setValue(large);
  EXPECT_EQ(0, rc);
  EXPECT_EQ(large, datum.toString());
}

TEST_F(IptcdatumTest_691, SetValueDoesNotChangeTypeIdWhenAlreadyHasValue_691) {
  const Exiv2::IptcKey key = MakeKey_ObjectName();

  // Create an initial Value with the dataset's typeId (via public API).
  const Exiv2::TypeId tid = Exiv2::IptcDataSets::dataSetType(key.tag(), key.record());
  Exiv2::Value::UniquePtr initial = Exiv2::Value::create(tid);
  ASSERT_NE(nullptr, initial.get());

  Exiv2::Iptcdatum datum(key, initial.get());

  const Exiv2::TypeId before = datum.typeId();
  EXPECT_EQ(0, datum.setValue(std::string("abc")));
  const Exiv2::TypeId after = datum.typeId();

  EXPECT_EQ(before, after);
}

TEST_F(IptcdatumTest_691, SetValueWithNumericDataset_InvalidStringReturnsErrorOrNonZero_691) {
  // For a numeric-like IPTC dataset, passing a non-numeric string should be observable
  // via the return code (int) if the underlying Value::read(string) rejects it.
  const Exiv2::IptcKey key = MakeKey_Urgency();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const int rc = datum.setValue(std::string("not_a_number"));

  // We can only assert observable behavior. For a numeric dataset, a non-zero return
  // is the typical error indication from Value::read(string).
  EXPECT_NE(0, rc);
}

TEST_F(IptcdatumTest_691, SetValueWithNumericDataset_ValidNumberReturnsSuccess_691) {
  const Exiv2::IptcKey key = MakeKey_Urgency();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const int rc = datum.setValue(std::string("5"));
  EXPECT_EQ(0, rc);

  // Use only public/observable behavior. Exact formatting is implementation-defined,
  // but toString() should reflect the newly set value in some form.
  EXPECT_FALSE(datum.toString().empty());
}

}  // namespace