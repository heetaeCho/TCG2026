// TEST_ID 638
// File: test_datasets_recordid_638.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/datasets.hpp"
#include "exiv2/error.hpp"

namespace {

// Helper to call recordId regardless of whether the API is static or requires an instance.
// This keeps the test robust across header/impl mismatches without inferring internals.
inline uint16_t CallRecordId(const std::string& name) {
#if defined(__cpp_if_consteval) // harmless guard; we just want a compile-time branch anchor
#endif
  // Prefer static call if available (as per datasets.hpp snippet).
  return Exiv2::IptcDataSets::recordId(name);
}

}  // namespace

TEST(IptcDataSetsRecordIdTest_638, ReturnsKnownRecordIdForEnvelope_638) {
  // Observable behavior: known record names map to their record ids.
  EXPECT_EQ(Exiv2::IptcDataSets::envelope, CallRecordId("Envelope"));
}

TEST(IptcDataSetsRecordIdTest_638, ReturnsKnownRecordIdForApplication2_638) {
  EXPECT_EQ(Exiv2::IptcDataSets::application2, CallRecordId("Application2"));
}

TEST(IptcDataSetsRecordIdTest_638, ParsesHexRecordIdWhenNameNotKnown_638) {
  // Observable behavior: when not a known record name, a valid hex string is accepted.
  // Use a value that corresponds to a known record id to avoid relying on range behavior.
  EXPECT_EQ(Exiv2::IptcDataSets::envelope, CallRecordId("0x0001"));
  EXPECT_EQ(Exiv2::IptcDataSets::application2, CallRecordId("0x0002"));
}

TEST(IptcDataSetsRecordIdTest_638, ParsesHexZeroAsInvalidRecordIdBoundary_638) {
  // Boundary: lowest hex value.
  EXPECT_EQ(Exiv2::IptcDataSets::invalidRecord, CallRecordId("0x0000"));
}

TEST(IptcDataSetsRecordIdTest_638, ThrowsForNonHexUnknownRecordName_638) {
  // Error case: unknown record name that is not a valid hex string.
  EXPECT_THROW((void)CallRecordId("NotARecordName"), Exiv2::Error);
}

TEST(IptcDataSetsRecordIdTest_638, ThrowsForInvalidRecordLiteralNameBoundary_638) {
  // Boundary: "(invalid)" exists in recordInfo_ but is *not* searched by the loop (only ids > 0).
  // Observable result should therefore be the same as any other non-hex unknown name: throw.
  EXPECT_THROW((void)CallRecordId("(invalid)"), Exiv2::Error);
}

TEST(IptcDataSetsRecordIdTest_638, ThrowsForCaseMismatchIfNotKnownAndNotHex_638) {
  // Boundary/error: behavior is case-sensitive if exact match is required.
  // We don't assert case-sensitivity directly; we only assert the observable outcome:
  // if it's not recognized as a name and it's not valid hex, it throws.
  EXPECT_THROW((void)CallRecordId("envelope"), Exiv2::Error);
}