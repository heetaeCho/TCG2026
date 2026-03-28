// TEST_ID 1441
// File: test_olympus2_mn_header_1441.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace Exiv2::Internal {

class Olympus2MnHeaderTest_1441 : public ::testing::Test {};

TEST_F(Olympus2MnHeaderTest_1441, MemberSizeOfSignature_IsNonZero_1441) {
  Olympus2MnHeader h;
  const size_t n = h.sizeOfSignature();
  EXPECT_GT(n, 0u);
}

TEST_F(Olympus2MnHeaderTest_1441, StaticAndMemberSizeOfSignature_Match_1441) {
  Olympus2MnHeader h;
  const size_t member = h.sizeOfSignature();
  const size_t statik = Olympus2MnHeader::sizeOfSignature();
  EXPECT_EQ(member, statik);
}

TEST_F(Olympus2MnHeaderTest_1441, RepeatedCalls_ReturnSameValue_1441) {
  Olympus2MnHeader h;
  const size_t first = h.sizeOfSignature();
  const size_t second = h.sizeOfSignature();
  const size_t third = h.sizeOfSignature();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(Olympus2MnHeaderTest_1441, MultipleInstances_ReturnSameValue_1441) {
  Olympus2MnHeader a;
  Olympus2MnHeader b;
  EXPECT_EQ(a.sizeOfSignature(), b.sizeOfSignature());
  EXPECT_EQ(Olympus2MnHeader::sizeOfSignature(), a.sizeOfSignature());
}

}  // namespace Exiv2::Internal