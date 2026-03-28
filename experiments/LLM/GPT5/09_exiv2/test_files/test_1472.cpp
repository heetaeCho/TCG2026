// TEST_ID 1472
// File: test_nikon3mnheader_setbyteorder_1472.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

// Some Exiv2 builds expose ByteOrder in different headers/namespaces.
// We rely only on the public interface of Nikon3MnHeader and the ByteOrder enum values.
namespace {
using Exiv2::ByteOrder;
using Exiv2::Internal::Nikon3MnHeader;
}  // namespace

class Nikon3MnHeaderTest_1472 : public ::testing::Test {
protected:
  Nikon3MnHeader hdr;
};

TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderToLittleEndianIsObservableViaGetter_1472) {
  hdr.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);
}

TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderToBigEndianIsObservableViaGetter_1472) {
  hdr.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::bigEndian);
}

TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderCanBeChangedMultipleTimes_1472) {
  // Do not assume any default; only verify that the last call wins (observable via byteOrder()).
  hdr.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);

  hdr.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::bigEndian);

  hdr.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);
}

TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderToInvalidIsObservableIfSupported_1472) {
  // Boundary/error-like input: invalidByteOrder (when available in the build).
  // This test does not assume semantics beyond "setter updates what getter returns".
  hdr.setByteOrder(Exiv2::invalidByteOrder);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::invalidByteOrder);
}