#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t bytes), (override));

};



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visit, (const TiffComponent& component), (override));

};



class MockUniquePtr : public TiffComponent::UniquePtr {

public:

    using TiffComponent::UniquePtr::UniquePtr;

    MOCK_METHOD(TiffComponent*, get, (), (const, override));

    MOCK_METHOD(TiffComponent*, release, (), (override));

};



class MockSharedPtr : public std::shared_ptr<TiffComponent> {

public:

    using std::shared_ptr<TiffComponent>::shared_ptr;

    MOCK_METHOD(TiffComponent*, get, (), (const, override));

};



class TiffComponentTest_285 : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = ifdExif;

    std::unique_ptr<TiffComponent> component = std::make_unique<TiffComponent>(tag, group);

};



TEST_F(TiffComponentTest_285, CloneCreatesNewInstance_285) {

    auto clonedComponent = component->clone();

    EXPECT_NE(clonedComponent.get(), component.get());

}



TEST_F(TiffComponentTest_285, TagReturnsCorrectValue_285) {

    EXPECT_EQ(component->tag(), tag);

}



TEST_F(TiffComponentTest_285, GroupReturnsCorrectValue_285) {

    EXPECT_EQ(component->group(), group);

}



TEST_F(TiffComponentTest_285, AcceptInvokesVisitorVisit_285) {

    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visit(::testing::Ref(*component))).Times(1);

    component->accept(visitor);

}



TEST_F(TiffComponentTest_285, WriteDataReturnsZeroForEmptyComponent_285) {

    MockIoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0, dataIdx = 0, imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);

    EXPECT_EQ(component->writeData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_285, WriteImageReturnsZeroForEmptyComponent_285) {

    MockIoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);

    EXPECT_EQ(component->writeImage(ioWrapper, byteOrder), 0);

}



TEST_F(TiffComponentTest_285, SizeReturnsZeroForEmptyComponent_285) {

    EXPECT_EQ(component->size(), 0);

}



TEST_F(TiffComponentTest_285, CountReturnsZeroForEmptyComponent_285) {

    EXPECT_EQ(component->count(), 0);

}



TEST_F(TiffComponentTest_285, SizeDataReturnsZeroForEmptyComponent_285) {

    EXPECT_EQ(component->sizeData(), 0);

}



TEST_F(TiffComponentTest_285, SizeImageReturnsZeroForEmptyComponent_285) {

    EXPECT_EQ(component->sizeImage(), 0);

}
