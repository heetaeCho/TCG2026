// File: test_sigma_mn_header_1495.cpp
#include <gtest/gtest.h>

#include <vector>

// Exiv2 headers (project-local)
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::SigmaMnHeader;

class SigmaMnHeaderTest_1495 : public ::testing::Test {};

TEST_F(SigmaMnHeaderTest_1495, DefaultConstruction_IsStableAcrossRepeatedCalls_1495) {
  SigmaMnHeader hdr;

  const auto off1 = hdr.ifdOffset();
  const auto off2 = hdr.ifdOffset();
  EXPECT_EQ(off1, off2);

  const auto sz1 = hdr.size();
  const auto sz2 = hdr.size();
  EXPECT_EQ(sz1, sz2);
}

TEST_F(SigmaMnHeaderTest_1495, ConstAndNonConstIfdOffset_AreConsistent_1496) {
  SigmaMnHeader hdr;

  const auto nonConstOffset = hdr.ifdOffset();

  const SigmaMnHeader& chdr = hdr;
  const auto constOffset = chdr.ifdOffset();

  EXPECT_EQ(nonConstOffset, constOffset);
}

TEST_F(SigmaMnHeaderTest_1495, ConstAndNonConstSize_AreConsistent_1497) {
  SigmaMnHeader hdr;

  const auto nonConstSize = hdr.size();

  const SigmaMnHeader& chdr = hdr;
  const auto constSize = chdr.size();

  EXPECT_EQ(nonConstSize, constSize);
}

TEST_F(SigmaMnHeaderTest_1495, SignatureSize_StaticAndInstance_AreConsistent_1498) {
  SigmaMnHeader hdr;

  const auto staticSig = SigmaMnHeader::sizeOfSignature();
  const auto instanceSig = hdr.sizeOfSignature();

  EXPECT_EQ(staticSig, instanceSig);
}

TEST_F(SigmaMnHeaderTest_1495, Read_WithZeroSize_ReturnsFalseAndDoesNotThrow_1499) {
  SigmaMnHeader hdr;

  const SigmaMnHeader& chdrBefore = hdr;
  const auto offBefore = chdrBefore.ifdOffset();
  const auto szBefore = chdrBefore.size();

  const Exiv2::byte dummy = 0;

  bool ok = true;
  EXPECT_NO_THROW({
    ok = hdr.read(&dummy, 0u, Exiv2::littleEndian);
  });

  // Observable error expectation for an empty buffer: should fail.
  EXPECT_FALSE(ok);

  const SigmaMnHeader& chdrAfter = hdr;
  EXPECT_EQ(offBefore, chdrAfter.ifdOffset());
  EXPECT_EQ(szBefore, chdrAfter.size());
}

TEST_F(SigmaMnHeaderTest_1495, Read_WithInsufficientBytesForSignature_ReturnsFalse_1500) {
  const auto sig = SigmaMnHeader::sizeOfSignature();
  if (sig == 0u) {
    GTEST_SKIP() << "Signature size is 0; cannot form an insufficient-size buffer boundary test.";
  }

  SigmaMnHeader hdr;

  const SigmaMnHeader& chdrBefore = hdr;
  const auto offBefore = chdrBefore.ifdOffset();
  const auto szBefore = chdrBefore.size();

  std::vector<Exiv2::byte> buf(sig - 1u, 0);

  bool ok = true;
  EXPECT_NO_THROW({
    ok = hdr.read(buf.data(), buf.size(), Exiv2::littleEndian);
  });

  EXPECT_FALSE(ok);

  const SigmaMnHeader& chdrAfter = hdr;
  EXPECT_EQ(offBefore, chdrAfter.ifdOffset());
  EXPECT_EQ(szBefore, chdrAfter.size());
}

}  // namespace