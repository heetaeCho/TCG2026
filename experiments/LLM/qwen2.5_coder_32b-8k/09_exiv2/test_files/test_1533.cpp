#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include <cstdint>

#include <string>



namespace Exiv2 {

    namespace Internal {

        class TiffIfdMakernote {};

        enum IfdId { casio2Id, casioId };

        using byte = uint8_t;

        enum ByteOrder {};



        std::unique_ptr<TiffIfdMakernote> newCasioMn(uint16_t tag, IfdId group, IfdId, const byte* pData, size_t size, ByteOrder);

    }

}



using namespace Exiv2::Internal;



class MakernoteIntTest_1533 : public ::testing::Test {

protected:

    // No specific setup or teardown needed for this test

};



TEST_F(MakernoteIntTest_1533, NewCasioMn_QvcHeader_ReturnsCasio2Mn2_1533) {

    const byte data[] = {'Q', 'V', 'C', 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::unique_ptr<TiffIfdMakernote> result = newCasioMn(1, IfdId::casio2Id, IfdId::casio2Id, data, sizeof(data), ByteOrder());

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(MakernoteIntTest_1533, NewCasioMn_SizeLessThan6_ReturnsNull_1533) {

    const byte data[] = {'Q', 'V'};

    std::unique_ptr<TiffIfdMakernote> result = newCasioMn(1, IfdId::casio2Id, IfdId::casio2Id, data, sizeof(data), ByteOrder());

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(MakernoteIntTest_1533, NewCasioMn_QvcHeaderButSizeLessThan14_ReturnsNull_1533) {

    const byte data[] = {'Q', 'V', 'C', 0, 0, 0};

    std::unique_ptr<TiffIfdMakernote> result = newCasioMn(1, IfdId::casio2Id, IfdId::casio2Id, data, sizeof(data), ByteOrder());

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(MakernoteIntTest_1533, NewCasioMn_NoQvcHeaderButSizeAtLeast14_ReturnsIfdMn2_1533) {

    const byte data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::unique_ptr<TiffIfdMakernote> result = newCasioMn(1, IfdId::casio2Id, IfdId::casio2Id, data, sizeof(data), ByteOrder());

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(MakernoteIntTest_1533, NewCasioMn_NullData_ReturnsNull_1533) {

    std::unique_ptr<TiffIfdMakernote> result = newCasioMn(1, IfdId::casio2Id, IfdId::casio2Id, nullptr, 14, ByteOrder());

    EXPECT_EQ(result.get(), nullptr);

}
