#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include <cstdint>

#include <cstddef>



namespace Exiv2 { namespace Internal {

    class TiffIfdMakernote;

    enum class IfdId : int {};

    using byte = uint8_t;



    std::unique_ptr<TiffIfdMakernote> newNikonMn(uint16_t tag, IfdId group, IfdId, const byte* pData, size_t size, ByteOrder);

}}



using namespace Exiv2;

using namespace Exiv2::Internal;

using namespace testing;



class NikonMnTest : public Test {

protected:

    uint16_t tag = 0x002a; // Example tag

    IfdId group = IfdId(); // Default group

    IfdId ifdId = IfdId();

    ByteOrder byteOrder = static_cast<ByteOrder>(1); // Little Endian example



    std::unique_ptr<TiffIfdMakernote> callNewNikonMn(const byte* pData, size_t size) {

        return newNikonMn(tag, group, ifdId, pData, size, byteOrder);

    }

};



TEST_F(NikonMnTest_1518, InvalidSize_ReturnsNullptr_1518) {

    const byte data[] = "Nikon";

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, IncorrectSignature_ReturnsNullptr_1518) {

    const byte data[] = "Canon\0";

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, ValidNikon1Header_ReturnsNikon1Makernote_1518) {

    const byte data[] = "Nikon\0";

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, ValidNikon2Header_ReturnsNikon2Makernote_1518) {

    const byte data[] = "Nikon\0\0\0\0\0\0\0\0\0\0\0\0\x2a\x00";

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, ValidNikon3Header_ReturnsNikon3Makernote_1518) {

    const byte data[] = "Nikon\0\0\0\0\0\0\0\0\0\0\0\0\x2a\x00";

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, InvalidTiffHeader_ReturnsNullptr_1518) {

    const byte data[] = "Nikon\0\0\0\0\0\0\x2b\x00"; // Incorrect tag

    auto result = callNewNikonMn(data, sizeof(data));

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(NikonMnTest_1518, BoundarySizeForNikon3_ReturnsNullptr_1518) {

    const byte data[] = "Nikon\0";

    auto result = callNewNikonMn(data, 17); // Size too small for Nikon3

    EXPECT_EQ(result.get(), nullptr);

}
