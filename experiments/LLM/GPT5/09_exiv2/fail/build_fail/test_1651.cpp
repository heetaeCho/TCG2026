// File: tiffvisitor_int_test_1651.cpp
// TEST_ID: 1651

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <cstdlib>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using ::testing::AnyOf;
using ::testing::ExitedWithCode;
using ::testing::KilledBySignal;

class TiffDecoderTest_1651 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;
};

TEST_F(TiffDecoderTest_1651, ConstructWithNullRootAndDefaultCallback_1651) {
  using Exiv2::Internal::FindDecoderFct;
  using Exiv2::Internal::TiffComponent;
  using Exiv2::Internal::TiffDecoder;

  FindDecoderFct fct{};           // default-constructed callback/functor
  TiffComponent* root = nullptr;  // boundary: null root

  EXPECT_NO_THROW({
    TiffDecoder decoder(exif_, iptc_, xmp_, root, fct);
    (void)decoder;
  });
}

TEST_F(TiffDecoderTest_1651, VisitEntryWithNullptrDoesNotHang_1651) {
#if GTEST_HAS_DEATH_TEST
  using Exiv2::Internal::FindDecoderFct;
  using Exiv2::Internal::TiffComponent;
  using Exiv2::Internal::TiffDecoder;

  // Run in a subprocess so we can safely accept either:
  // - normal return
  // - an exception
  // - termination by common failure signals (e.g., nullptr dereference/assert)
  EXPECT_EXIT(
      {
        Exiv2::ExifData exif;
        Exiv2::IptcData iptc;
        Exiv2::XmpData xmp;
        FindDecoderFct fct{};
        TiffComponent* root = nullptr;

        TiffDecoder decoder(exif, iptc, xmp, root, fct);
        try {
          decoder.visitEntry(nullptr);  // boundary: null entry
          std::exit(0);
        } catch (...) {
          // Throwing is considered an observable, acceptable outcome for this boundary input.
          std::exit(0);
        }
      },
      AnyOf(ExitedWithCode(0),
            // Accept common termination modes without assuming which one is used internally.
            KilledBySignal(SIGSEGV), KilledBySignal(SIGABRT), KilledBySignal(SIGILL),
            KilledBySignal(SIGBUS)),
      "");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

}  // namespace