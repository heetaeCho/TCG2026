// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// File: test_omsystem_mnheader_1451.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Exiv2 headers (adjust include paths if your build uses different layout)
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

class OMSystemMnHeaderTest_1451 : public ::testing::Test {};

TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseWhenDataIsNull_1451) {
    Exiv2::Internal::OMSystemMnHeader header;

    // Any size should fail when pData is null (observable through return value).
    EXPECT_FALSE(header.read(nullptr, 0, Exiv2::littleEndian));
    EXPECT_FALSE(header.read(nullptr, 1, Exiv2::littleEndian));
    EXPECT_FALSE(header.read(nullptr, 1024, Exiv2::bigEndian));
}

TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseWhenSizeIsZeroEvenIfPointerNonNull_1451) {
    Exiv2::Internal::OMSystemMnHeader header;

    const Exiv2::byte dummy = 0x00;
    EXPECT_FALSE(header.read(&dummy, 0, Exiv2::littleEndian));
    EXPECT_FALSE(header.read(&dummy, 0, Exiv2::bigEndian));
}

TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseForVerySmallBuffers_1451) {
    Exiv2::Internal::OMSystemMnHeader header;

    // Boundary-oriented: small sizes should not be sufficient for a maker-note header.
    // We only assert observable failure (false), without assuming internal signature details.
    std::vector<Exiv2::byte> buf1(1, 0x00);
    std::vector<Exiv2::byte> buf2(2, 0x11);
    std::vector<Exiv2::byte> buf3(3, 0x22);

    EXPECT_FALSE(header.read(buf1.data(), buf1.size(), Exiv2::littleEndian));
    EXPECT_FALSE(header.read(buf2.data(), buf2.size(), Exiv2::littleEndian));
    EXPECT_FALSE(header.read(buf3.data(), buf3.size(), Exiv2::littleEndian));

    // Also verify ByteOrder does not change the observable behavior for these boundary failures.
    EXPECT_FALSE(header.read(buf1.data(), buf1.size(), Exiv2::bigEndian));
    EXPECT_FALSE(header.read(buf2.data(), buf2.size(), Exiv2::bigEndian));
    EXPECT_FALSE(header.read(buf3.data(), buf3.size(), Exiv2::bigEndian));
}

}  // namespace