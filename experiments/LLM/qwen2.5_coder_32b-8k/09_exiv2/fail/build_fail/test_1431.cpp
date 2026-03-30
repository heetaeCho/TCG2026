#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



namespace Exiv2 { namespace Internal {



class MockTiffMnRegistry {

public:

    MOCK_CONST_METHOD1(find, TiffMnRegistry*(std::string_view make));

};



class TiffMnCreatorTest : public ::testing::Test {

protected:

    MockTiffMnRegistry mockRegistry;

    TiffMnCreator creator;



    void SetUp() override {

        // Assuming registry_ is accessible for testing purposes

        creator.registry_ = &mockRegistry;

    }

};



TEST_F(TiffMnCreatorTest_1431, CreateReturnsNonNullForKnownMake_1431) {

    std::string_view make = "TestMake";

    uint16_t tag = 0x0100;

    IfdId group = ifdExif;

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    TiffMnRegistry registryEntry;

    registryEntry.newMnFct_ = [](uint16_t, IfdId, IfdId, const byte*, size_t, ByteOrder) -> std::unique_ptr<TiffIfdMakernote> {

        return std::make_unique<TiffIfdMakernote>();

    };



    EXPECT_CALL(mockRegistry, find(make)).WillOnce(::testing::Return(&registryEntry));



    auto result = creator.create(tag, group, make, pData, size, byteOrder);

    ASSERT_NE(result, nullptr);

}



TEST_F(TiffMnCreatorTest_1431, CreateReturnsNullForUnknownMake_1431) {

    std::string_view make = "UnknownMake";

    uint16_t tag = 0x0100;

    IfdId group = ifdExif;

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockRegistry, find(make)).WillOnce(::testing::Return(nullptr));



    auto result = creator.create(tag, group, make, pData, size, byteOrder);

    ASSERT_EQ(result, nullptr);

}



TEST_F(TiffMnCreatorTest_1431, CreateBoundaryConditionWithEmptyData_1431) {

    std::string_view make = "TestMake";

    uint16_t tag = 0x0100;

    IfdId group = ifdExif;

    const byte* pData = nullptr; // Empty data

    size_t size = 0; // Zero size

    ByteOrder byteOrder = littleEndian;



    TiffMnRegistry registryEntry;

    registryEntry.newMnFct_ = [](uint16_t, IfdId, IfdId, const byte*, size_t, ByteOrder) -> std::unique_ptr<TiffIfdMakernote> {

        return std::make_unique<TiffIfdMakernote>();

    };



    EXPECT_CALL(mockRegistry, find(make)).WillOnce(::testing::Return(&registryEntry));



    auto result = creator.create(tag, group, make, pData, size, byteOrder);

    ASSERT_NE(result, nullptr);

}



TEST_F(TiffMnCreatorTest_1431, CreateBoundaryConditionWithNonZeroSizeButNullData_1431) {

    std::string_view make = "TestMake";

    uint16_t tag = 0x0100;

    IfdId group = ifdExif;

    const byte* pData = nullptr; // Null data

    size_t size = 10; // Non-zero size

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockRegistry, find(make)).WillOnce(::testing::Return(nullptr));



    auto result = creator.create(tag, group, make, pData, size, byteOrder);

    ASSERT_EQ(result, nullptr);

}



} } // namespace Exiv2::Internal
