#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using testing::NiceMock;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(void, accept, (TiffVisitor&), (override));

    MOCK_METHOD(void, encode, (TiffEncoder&, const Exifdatum*), (override));

    MOCK_METHOD(size_t, write, (IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&), (override));

};



class TiffBinaryArrayTest : public ::testing::Test {

protected:

    MockTiffComponent mockComponent;

    std::shared_ptr<TiffComponent> componentPtr = std::make_shared<MockTiffComponent>();

    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    uint16_t tag = 0x0100; // Example tag

    IfdId group = ifdExif;



    TiffBinaryArray tiffBinaryArray = TiffBinaryArray(tag, group, arrayCfg, &arrayDef, sizeof(arrayDef));

};



TEST_F(TiffBinaryArrayTest_331, DoAddChild_ReturnsAddedComponent_331) {

    TiffComponent* addedComponent = tiffBinaryArray.doAddChild(componentPtr);

    EXPECT_EQ(addedComponent, componentPtr.get());

}



TEST_F(TiffBinaryArrayTest_331, SetDecoded_IsSetToTrue_331) {

    EXPECT_FALSE(tiffBinaryArray.decoded());

    tiffBinaryArray.setDecoded(true);

    EXPECT_TRUE(tiffBinaryArray.decoded());

}
