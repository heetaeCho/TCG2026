// =================================================================================================
// Copyright ...
//
// Unit tests for Exiv2::Iptcdatum::tagLabel()
// File: ./TestProjects/exiv2/src/iptc.cpp (interface exercised via public headers)
//
// TEST_ID: 671
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>

namespace {

class IptcdatumTagLabelTest_671 : public ::testing::Test {
 protected:
  // Use commonly-known IPTC Application2 record (2) with a typical tag id (e.g., 5 = ObjectName).
  // The test never assumes any specific label text; it only compares observable outputs.
  static Exiv2::IptcKey MakeNumericKey() { return Exiv2::IptcKey(/*tag=*/5, /*record=*/2); }

  // A syntactically plausible key string. Again, we do not assume anything about the returned label.
  static Exiv2::IptcKey MakeStringKey() { return Exiv2::IptcKey("Iptc.Application2.ObjectName"); }
};

TEST_F(IptcdatumTagLabelTest_671, TagLabelMatchesKeyTagLabel_NumericKey_671) {
  const Exiv2::IptcKey key = MakeNumericKey();

  ASSERT_NO_THROW({
    const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);
    EXPECT_EQ(datum.tagLabel(), key.tagLabel());
  });
}

TEST_F(IptcdatumTagLabelTest_671, TagLabelMatchesKeyTagLabel_StringKey_671) {
  const Exiv2::IptcKey key = MakeStringKey();

  ASSERT_NO_THROW({
    const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);
    EXPECT_EQ(datum.tagLabel(), key.tagLabel());
  });
}

TEST_F(IptcdatumTagLabelTest_671, CopyConstructionPreservesTagLabel_671) {
  const Exiv2::IptcKey key = MakeNumericKey();
  const Exiv2::Iptcdatum original(key, /*pValue=*/nullptr);

  ASSERT_NO_THROW({
    const Exiv2::Iptcdatum copy(original);
    EXPECT_EQ(copy.tagLabel(), original.tagLabel());
    EXPECT_EQ(copy.tagLabel(), key.tagLabel());
  });
}

TEST_F(IptcdatumTagLabelTest_671, CopyAssignmentPreservesTagLabel_671) {
  const Exiv2::IptcKey keyA = MakeNumericKey();
  const Exiv2::IptcKey keyB = MakeStringKey();

  Exiv2::Iptcdatum a(keyA, /*pValue=*/nullptr);
  Exiv2::Iptcdatum b(keyB, /*pValue=*/nullptr);

  const std::string before = a.tagLabel();

  ASSERT_NO_THROW({
    a = b;
  });

  EXPECT_EQ(a.tagLabel(), b.tagLabel());
  EXPECT_NE(a.tagLabel(), before);  // boundary/behavioral check; if equal it's fine but unusual
}

TEST_F(IptcdatumTagLabelTest_671, SelfAssignmentDoesNotCrashAndKeepsTagLabel_671) {
  const Exiv2::IptcKey key = MakeNumericKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const std::string before = datum.tagLabel();

  ASSERT_NO_THROW({
    datum = datum;
  });

  EXPECT_EQ(datum.tagLabel(), before);
}

TEST_F(IptcdatumTagLabelTest_671, ConstructWithNullValuePointer_DoesNotThrow_671) {
  const Exiv2::IptcKey key = MakeNumericKey();

  EXPECT_NO_THROW({
    const Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);
    // Observable behavior: tagLabel is callable and consistent with the key.
    (void)datum.tagLabel();
    EXPECT_EQ(datum.tagLabel(), key.tagLabel());
  });
}

}  // namespace