// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_IptcDataSets_627.cpp

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace {

class IptcDataSetsTest_627 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_ReturnsNonNull_627) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_627, EnvelopeRecordList_IsStableAcrossCalls_627) {
  const Exiv2::DataSet* a = Exiv2::IptcDataSets::envelopeRecordList();
  const Exiv2::DataSet* b = Exiv2::IptcDataSets::envelopeRecordList();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(a, b);
}

TEST_F(IptcDataSetsTest_627, DataSetName_ModelVersionEnvelope_IsNonEmpty_627) {
  const std::string name =
      Exiv2::IptcDataSets::dataSetName(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_627, DataSetTitleDescPsName_ModelVersionEnvelope_AreNonNull_627) {
  const char* title =
      Exiv2::IptcDataSets::dataSetTitle(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  const char* desc =
      Exiv2::IptcDataSets::dataSetDesc(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  const char* ps =
      Exiv2::IptcDataSets::dataSetPsName(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);

  EXPECT_NE(title, nullptr);
  EXPECT_NE(desc, nullptr);
  EXPECT_NE(ps, nullptr);
}

TEST_F(IptcDataSetsTest_627, DataSetRepeatable_ModelVersionEnvelope_IsObservable_627) {
  // Observable behavior: function returns a bool and should be callable for a known dataset.
  const bool repeatable =
      Exiv2::IptcDataSets::dataSetRepeatable(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  (void)repeatable;  // Just ensure no exception/crash and value is obtainable.
  SUCCEED();
}

TEST_F(IptcDataSetsTest_627, DataSetType_ModelVersionEnvelope_IsExpectedUnsignedShort_627) {
  const Exiv2::TypeId t =
      Exiv2::IptcDataSets::dataSetType(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  EXPECT_EQ(t, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_627, DataSet_LookupByName_RoundTripsForModelVersion_627) {
  const std::string name =
      Exiv2::IptcDataSets::dataSetName(Exiv2::IptcDataSets::ModelVersion, Exiv2::IptcDataSets::envelope);
  ASSERT_FALSE(name.empty());

  const uint16_t number = Exiv2::IptcDataSets::dataSet(name, Exiv2::IptcDataSets::envelope);
  EXPECT_EQ(number, static_cast<uint16_t>(Exiv2::IptcDataSets::ModelVersion));
}

TEST_F(IptcDataSetsTest_627, RecordNameAndRecordId_RoundTripForEnvelope_627) {
  const std::string recordName = Exiv2::IptcDataSets::recordName(Exiv2::IptcDataSets::envelope);
  EXPECT_FALSE(recordName.empty());

  const uint16_t recordId = Exiv2::IptcDataSets::recordId(recordName);
  EXPECT_EQ(recordId, static_cast<uint16_t>(Exiv2::IptcDataSets::envelope));

  const char* recordDesc = Exiv2::IptcDataSets::recordDesc(Exiv2::IptcDataSets::envelope);
  EXPECT_NE(recordDesc, nullptr);
}

TEST_F(IptcDataSetsTest_627, DataSetList_ProducesSomeOutput_627) {
  std::ostringstream oss;
  Exiv2::IptcDataSets::dataSetList(oss);

  const std::string out = oss.str();
  EXPECT_FALSE(out.empty());

  // Boundary-ish check: output should contain at least one well-known dataset/identifier string.
  // (We only assert containment, not exact formatting.)
  EXPECT_NE(out.find("ModelVersion"), std::string::npos);
}

}  // namespace