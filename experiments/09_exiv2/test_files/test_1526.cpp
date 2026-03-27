#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include <cstdint>

#include <cstddef>



namespace Exiv2 {

    namespace Internal {

        class TiffIfdMakernote {};

        enum class IfdId : int {};

        using byte = uint8_t;

        struct ByteOrder {};



        std::unique_ptr<TiffIfdMakernote> newPentaxMn2(uint16_t tag, IfdId group, IfdId mnGroup);

        std::unique_ptr<TiffIfdMakernote> newSamsungMn2(uint16_t tag, IfdId group, IfdId mnGroup);



        std::unique_ptr<TiffIfdMakernote> newSamsungMn(uint16_t tag, IfdId group, IfdId mnGroup, const byte* pData, size_t size, ByteOrder);

    }

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class MakernoteIntTest_1526 : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = static_cast<IfdId>(1);

    IfdId mnGroup = static_cast<IfdId>(2);

    ByteOrder byteOrder{};

};



TEST_F(MakernoteIntTest_1526, NullptrWhenSizeLessThan4_1526) {

    const byte data[] = {0x01, 0x02};

    size_t size = sizeof(data);



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MakernoteIntTest_1526, NullptrWhenSizeLessThanPentaxSignaturePlus18ForAOC_1526) {

    const byte data[] = {'A', 'O', 'C', '\0', 0x01, 0x02};

    size_t size = sizeof(data);



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MakernoteIntTest_1526, NewPentaxMn2CalledWhenAOCAndSizeSufficient_1526) {

    const byte data[] = {'A', 'O', 'C', '\0', 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    size_t size = sizeof(data);



    EXPECT_CALL(::testing::MockFunction<std::unique_ptr<TiffIfdMakernote>(uint16_t, IfdId, IfdId)>(), Call(tag, group, IfdId::pentaxId))

        .WillOnce([](uint16_t tag, IfdId group, IfdId mnGroup) { return newPentaxMn2(tag, group, mnGroup); });



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_NE(result, nullptr);

}



TEST_F(MakernoteIntTest_1526, NewSamsungMn2CalledWhenNotAOCAndSizeSufficient_1526) {

    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    size_t size = sizeof(data);



    EXPECT_CALL(::testing::MockFunction<std::unique_ptr<TiffIfdMakernote>(uint16_t, IfdId, IfdId)>(), Call(tag, group, mnGroup))

        .WillOnce([](uint16_t tag, IfdId group, IfdId mnGroup) { return newSamsungMn2(tag, group, mnGroup); });



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_NE(result, nullptr);

}



TEST_F(MakernoteIntTest_1526, BoundaryConditionForAOCAndSizeSufficient_1526) {

    const byte data[] = {'A', 'O', 'C', '\0', 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    size_t size = sizeof(data);



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_NE(result, nullptr);

}



TEST_F(MakernoteIntTest_1526, BoundaryConditionForNotAOCAndSizeSufficient_1526) {

    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    size_t size = sizeof(data);



    auto result = newSamsungMn(tag, group, mnGroup, data, size, byteOrder);

    EXPECT_NE(result, nullptr);

}

```


