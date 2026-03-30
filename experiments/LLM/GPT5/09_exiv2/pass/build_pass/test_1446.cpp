// File: test_olympus2_mnheader_write_1446.cpp
#include <gtest/gtest.h>

#include "basicio.hpp"
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

class Olympus2MnHeaderTest_1446 : public ::testing::Test {
 protected:
  // IoWrapper needs a BasicIo reference plus an (optional) TIFF header pointer/size.
  // For these tests we don't want IoWrapper to write any TIFF header, so we pass nullptr/0.
  static Exiv2::Internal::IoWrapper makeIoWrapper(Exiv2::BasicIo& io) {
    return Exiv2::Internal::IoWrapper(io, /*pHeader*/ nullptr, /*size*/ 0L, /*pow*/ nullptr);
  }
};

TEST_F(Olympus2MnHeaderTest_1446, WriteReturnsSizeAndWritesToIo_1446) {
  Exiv2::MemIo memIo;
  auto ioWrapper = makeIoWrapper(memIo);

  Exiv2::Internal::Olympus2MnHeader header;

  const size_t beforeSize = static_cast<size_t>(memIo.size());
  const size_t written = header.write(ioWrapper, Exiv2::littleEndian);
  const size_t afterSize = static_cast<size_t>(memIo.size());

  // Observable contract: write() returns the number of bytes written.
  EXPECT_EQ(written, header.size());
  EXPECT_EQ(afterSize, beforeSize + written);

  // Also verify consistency with the public static sizeOfSignature() API.
  EXPECT_EQ(written, Exiv2::Internal::Olympus2MnHeader::sizeOfSignature());
}

TEST_F(Olympus2MnHeaderTest_1446, WriteAppendsOnRepeatedCalls_1446) {
  Exiv2::MemIo memIo;
  auto ioWrapper = makeIoWrapper(memIo);

  Exiv2::Internal::Olympus2MnHeader header;

  const size_t w1 = header.write(ioWrapper, Exiv2::littleEndian);
  const size_t sizeAfter1 = static_cast<size_t>(memIo.size());

  const size_t w2 = header.write(ioWrapper, Exiv2::littleEndian);
  const size_t sizeAfter2 = static_cast<size_t>(memIo.size());

  EXPECT_EQ(w1, header.size());
  EXPECT_EQ(w2, header.size());
  EXPECT_EQ(sizeAfter1, w1);
  EXPECT_EQ(sizeAfter2, w1 + w2);
}

TEST_F(Olympus2MnHeaderTest_1446, WriteIsStableAcrossByteOrders_1446) {
  Exiv2::Internal::Olympus2MnHeader header;

  // littleEndian
  Exiv2::MemIo memIo1;
  auto ioWrapper1 = makeIoWrapper(memIo1);
  const size_t wLE = header.write(ioWrapper1, Exiv2::littleEndian);

  // bigEndian
  Exiv2::MemIo memIo2;
  auto ioWrapper2 = makeIoWrapper(memIo2);
  const size_t wBE = header.write(ioWrapper2, Exiv2::bigEndian);

  // invalidByteOrder (if supported by the enum)
  Exiv2::MemIo memIo3;
  auto ioWrapper3 = makeIoWrapper(memIo3);
  const size_t wInv = header.write(ioWrapper3, Exiv2::invalidByteOrder);

  EXPECT_EQ(wLE, header.size());
  EXPECT_EQ(wBE, header.size());
  EXPECT_EQ(wInv, header.size());

  EXPECT_EQ(static_cast<size_t>(memIo1.size()), wLE);
  EXPECT_EQ(static_cast<size_t>(memIo2.size()), wBE);
  EXPECT_EQ(static_cast<size_t>(memIo3.size()), wInv);
}

TEST_F(Olympus2MnHeaderTest_1446, WriteOnFreshMemIoWritesNonZero_1446) {
  Exiv2::MemIo memIo;
  auto ioWrapper = makeIoWrapper(memIo);

  Exiv2::Internal::Olympus2MnHeader header;

  const size_t written = header.write(ioWrapper, Exiv2::littleEndian);
  EXPECT_GT(written, 0u);
  EXPECT_GT(static_cast<size_t>(memIo.size()), 0u);
}

}  // namespace