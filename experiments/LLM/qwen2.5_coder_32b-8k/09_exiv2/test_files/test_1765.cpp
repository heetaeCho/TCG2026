#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



class CiffComponentTest_1765 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1765, DataLocationReturnsCorrectValue_1765) {

    uint16_t tag = 0x1234;

    DataLocId expectedDataLocId = static_cast<DataLocId>(4321); // Assuming some value for demonstration

    EXPECT_CALL(component, dataLocation(tag)).WillOnce(::testing::Return(expectedDataLocId));

    

    EXPECT_EQ(component.dataLocation(), expectedDataLocId);

}



TEST_F(CiffComponentTest_1765, DataLocationStaticFunctionReturnsCorrectValue_1765) {

    uint16_t tag = 0x1234;

    DataLocId expectedDataLocId = static_cast<DataLocId>(4321); // Assuming some value for demonstration

    EXPECT_EQ(CiffComponent::dataLocation(tag), expectedDataLocId);

}



TEST_F(CiffComponentTest_1765, TagReturnsCorrectValue_1765) {

    uint16_t tag = 0x1234;

    CiffComponent componentWithTag(tag, 0);



    EXPECT_EQ(componentWithTag.tag(), tag);

}



TEST_F(CiffComponentTest_1765, DirReturnsCorrectValue_1765) {

    uint16_t dir = 0x5678;

    CiffComponent componentWithDir(0, dir);



    EXPECT_EQ(componentWithDir.dir(), dir);

}



TEST_F(CiffComponentTest_1765, EmptyFunctionReturnsTrueWhenEmpty_1765) {

    EXPECT_TRUE(component.empty());

}



TEST_F(CiffComponentTest_1765, EmptyFunctionReturnsFalseWhenNotEmpty_1765) {

    // Assuming some way to make the component non-empty

    // For demonstration purposes, we mock doEmpty to return false

    EXPECT_CALL(component, doEmpty()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(component.empty());

}



TEST_F(CiffComponentTest_1765, FindComponentReturnsNullptrWhenNotFound_1765) {

    uint16_t crwTagId = 0x9ABC;

    uint16_t crwDir = 0xCDEF;



    EXPECT_CALL(component, doFindComponent(crwTagId, crwDir)).WillOnce(::testing::Return(nullptr));



    EXPECT_EQ(component.findComponent(crwTagId, crwDir), nullptr);

}



TEST_F(CiffComponentTest_1765, FindComponentReturnsValidPointerWhenFound_1765) {

    uint16_t crwTagId = 0x9ABC;

    uint16_t crwDir = 0xCDEF;



    CiffComponent* mockComponent = new CiffComponent();

    EXPECT_CALL(component, doFindComponent(crwTagId, crwDir)).WillOnce(::testing::Return(mockComponent));



    EXPECT_EQ(component.findComponent(crwTagId, crwDir), mockComponent);

}



TEST_F(CiffComponentTest_1765, AddMethodWorksProperly_1765) {

    UniquePtr componentToAdd(new CiffComponent());

    const UniquePtr& result = component.add(std::move(componentToAdd));



    EXPECT_NE(result.get(), nullptr);

}



TEST_F(CiffComponentTest_1765, ReadMethodSetsDataCorrectly_1765) {

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    size_t dataSize = sizeof(data);

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;



    component.read(data, dataSize, start, byteOrder);



    EXPECT_NE(component.pData(), nullptr);

}



TEST_F(CiffComponentTest_1765, WriteMethodReturnsCorrectSize_1765) {

    Blob blob(1024);

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;



    size_t expectedSize = 32; // Assuming some value for demonstration

    EXPECT_CALL(component, doWrite(::testing::Ref(blob), byteOrder, offset)).WillOnce(::testing::Return(expectedSize));



    EXPECT_EQ(component.write(blob, byteOrder, offset), expectedSize);

}



TEST_F(CiffComponentTest_1765, WriteValueDataMethodWorksProperly_1765) {

    Blob blob(1024);

    size_t offset = 0;



    component.writeValueData(blob, offset);



    // Assuming some way to verify the result

    EXPECT_EQ(offset, 32); // Assuming some value for demonstration

}



TEST_F(CiffComponentTest_1765, SetAndGetTypeMethodsWorkProperly_1765) {

    DataBuf dataBuffer(reinterpret_cast<byte*>("test"), 4);

    component.setValue(std::move(dataBuffer));



    EXPECT_EQ(component.typeId(), static_cast<TypeId>(42)); // Assuming some value for demonstration

}
