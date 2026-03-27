// ***************************************************************** -*- C++ -*-
// unit tests for Exiv2::Internal::newCasio2Mn2
//
// File: TestProjects/exiv2/test/makernote_int_new_casio2mn2_test.cpp
// *****************************************************************

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include "makernote_int.hpp"  // for Exiv2::Internal::newCasio2Mn2, IfdId, TiffIfdMakernote

namespace {

using Exiv2::Internal::newCasio2Mn2;

class Casio2Mn2FactoryTest_1534 : public ::testing::Test {};

TEST_F(Casio2Mn2FactoryTest_1534, CreatesNonNullUniquePtr_1534) {
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW({
    mn = newCasio2Mn2(static_cast<uint16_t>(1),
                     static_cast<Exiv2::IfdId>(0),
                     static_cast<Exiv2::IfdId>(0));
  });
  ASSERT_NE(mn, nullptr);
}

TEST_F(Casio2Mn2FactoryTest_1534, AcceptsZeroTag_1534) {
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW({
    mn = newCasio2Mn2(static_cast<uint16_t>(0),
                     static_cast<Exiv2::IfdId>(0),
                     static_cast<Exiv2::IfdId>(0));
  });
  ASSERT_NE(mn, nullptr);
}

TEST_F(Casio2Mn2FactoryTest_1534, AcceptsMaxUint16Tag_1534) {
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW({
    mn = newCasio2Mn2(static_cast<uint16_t>(0xFFFF),
                     static_cast<Exiv2::IfdId>(1),
                     static_cast<Exiv2::IfdId>(2));
  });
  ASSERT_NE(mn, nullptr);
}

TEST_F(Casio2Mn2FactoryTest_1534, MultipleCallsReturnDistinctInstances_1534) {
  auto a = newCasio2Mn2(static_cast<uint16_t>(10),
                        static_cast<Exiv2::IfdId>(0),
                        static_cast<Exiv2::IfdId>(1));
  auto b = newCasio2Mn2(static_cast<uint16_t>(10),
                        static_cast<Exiv2::IfdId>(0),
                        static_cast<Exiv2::IfdId>(1));

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

}  // namespace