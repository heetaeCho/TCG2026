#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_413 : public ::testing::Test {

protected:

    void SetUp() override {

        component = std::make_shared<TiffComponent>(0x0100, IfdId::IFD0);

        otherComponent = std::make_shared<TiffComponent>(0x0101, IfdId::IFD0);

    }



    TiffComponent::SharedPtr component;

    TiffComponent::SharedPtr otherComponent;

};



TEST_F(TiffComponentTest_413, TagComparison_DifferentTags_413) {

    EXPECT_TRUE(cmpTagLt(component, otherComponent));

}



TEST_F(TiffComponentTest_413, TagComparison_SameTagsDifferentIdx_413) {

    component->idx = []() { return 0; };

    otherComponent->idx = []() { return 1; };



    EXPECT_TRUE(cmpTagLt(component, otherComponent));

}



TEST_F(TiffComponentTest_413, TagComparison_SameTagsSameIdx_413) {

    component->idx = []() { return 0; };

    otherComponent->idx = []() { return 0; };



    EXPECT_FALSE(cmpTagLt(component, otherComponent));

}



TEST_F(TiffComponentTest_413, AddChild_ReturnsSelf_413) {

    auto childComponent = std::make_shared<TiffComponent>(0x0102, IfdId::IFD0);

    EXPECT_EQ(component.get(), component->addChild(childComponent));

}



TEST_F(TiffComponentTest_413, AddNext_ReturnsSelf_413) {

    auto nextComponent = std::make_unique<TiffComponent>(0x0103, IfdId::IFD0);

    EXPECT_EQ(component.get(), component->addNext(std::move(nextComponent)));

}



TEST_F(TiffComponentTest_413, Accept_VisitorCalled_413) {

    class MockTiffVisitor : public TiffVisitor {

    public:

        MOCK_METHOD(void, visit, (const TiffComponent&), (override));

    };



    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(*component)));



    component->accept(mockVisitor);

}



TEST_F(TiffComponentTest_413, Clone_ReturnsValidObject_413) {

    auto clone = component->clone();

    EXPECT_NE(nullptr, clone.get());

    EXPECT_EQ(component->tag(), clone->tag());

    EXPECT_EQ(component->group(), clone->group());

}



TEST_F(TiffComponentTest_413, Write_ReturnsNonNegativeSize_413) {

    IoWrapper ioWrapper; // Assuming IoWrapper is default constructible

    ByteOrder byteOrder = ByteOrder::littleEndian;

    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;



    EXPECT_GE(component->write(ioWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_413, WriteData_ReturnsNonNegativeSize_413) {

    IoWrapper ioWrapper; // Assuming IoWrapper is default constructible

    ByteOrder byteOrder = ByteOrder::littleEndian;

    size_t offset = 0, dataIdx = 0, imageIdx = 0;



    EXPECT_GE(component->writeData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_413, WriteImage_ReturnsNonNegativeSize_413) {

    IoWrapper ioWrapper; // Assuming IoWrapper is default constructible

    ByteOrder byteOrder = ByteOrder::littleEndian;



    EXPECT_GE(component->writeImage(ioWrapper, byteOrder), 0);

}



TEST_F(TiffComponentTest_413, Size_ReturnsNonNegativeSize_413) {

    EXPECT_GE(component->size(), 0);

}



TEST_F(TiffComponentTest_413, Count_ReturnsNonNegativeCount_413) {

    EXPECT_GE(component->count(), 0);

}



TEST_F(TiffComponentTest_413, SizeData_ReturnsNonNegativeSize_413) {

    EXPECT_GE(component->sizeData(), 0);

}



TEST_F(TiffComponentTest_413, SizeImage_ReturnsNonNegativeSize_413) {

    EXPECT_GE(component->sizeImage(), 0);

}
