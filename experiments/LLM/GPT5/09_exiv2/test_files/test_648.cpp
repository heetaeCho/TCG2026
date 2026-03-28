// File: test_iptckey_record_648.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>
#include <utility>

#include "exiv2/datasets.hpp"

namespace {

class IptcKeyRecordTest_648 : public ::testing::Test {};

TEST_F(IptcKeyRecordTest_648, Record_ReturnsConstructorProvidedValue_648) {
  const uint16_t tag = 5;
  const uint16_t record = 42;

  const Exiv2::IptcKey key(tag, record);

  EXPECT_EQ(key.record(), record);
}

TEST_F(IptcKeyRecordTest_648, Record_BoundaryZero_648) {
  const Exiv2::IptcKey key(/*tag=*/0, /*record=*/0);

  EXPECT_EQ(key.record(), 0);
}

TEST_F(IptcKeyRecordTest_648, Record_BoundaryMaxUint16_648) {
  const uint16_t max_u16 = std::numeric_limits<uint16_t>::max();
  const Exiv2::IptcKey key(/*tag=*/1, /*record=*/max_u16);

  EXPECT_EQ(key.record(), max_u16);
}

TEST_F(IptcKeyRecordTest_648, Record_IsCallableOnConstObject_648) {
  const Exiv2::IptcKey key(/*tag=*/7, /*record=*/13);

  const Exiv2::IptcKey& cref = key;
  EXPECT_EQ(cref.record(), 13);
}

TEST_F(IptcKeyRecordTest_648, Record_FromStringKeyConstructor_DefaultsToZero_648) {
  // Observable behavior based on the provided header snippet showing record_ initialized to 0
  // in the std::string constructor.
  const Exiv2::IptcKey key(std::string("Iptc.Application2.Caption"));

  EXPECT_EQ(key.record(), 0);
}

TEST_F(IptcKeyRecordTest_648, Record_CopyConstructionPreservesRecord_648) {
  const Exiv2::IptcKey original(/*tag=*/9, /*record=*/1234);

  const Exiv2::IptcKey copy = original;

  EXPECT_EQ(copy.record(), original.record());
  EXPECT_EQ(copy.record(), 1234);
}

TEST_F(IptcKeyRecordTest_648, Record_MoveConstructionPreservesRecordInDestination_648) {
  Exiv2::IptcKey original(/*tag=*/11, /*record=*/4321);
  const uint16_t expected = original.record();

  const Exiv2::IptcKey moved = std::move(original);

  EXPECT_EQ(moved.record(), expected);
}

TEST_F(IptcKeyRecordTest_648, Record_CopyAssignmentPreservesRecord_648) {
  const Exiv2::IptcKey source(/*tag=*/2, /*record=*/77);
  Exiv2::IptcKey dest(/*tag=*/3, /*record=*/88);

  dest = source;

  EXPECT_EQ(dest.record(), source.record());
  EXPECT_EQ(dest.record(), 77);
}

TEST_F(IptcKeyRecordTest_648, Record_MoveAssignmentPreservesRecordInDestination_648) {
  Exiv2::IptcKey source(/*tag=*/4, /*record=*/99);
  Exiv2::IptcKey dest(/*tag=*/6, /*record=*/11);

  const uint16_t expected = source.record();
  dest = std::move(source);

  EXPECT_EQ(dest.record(), expected);
}

}  // namespace