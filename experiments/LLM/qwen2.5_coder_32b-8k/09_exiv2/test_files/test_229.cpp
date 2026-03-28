#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class TiffComponentTest_229 : public ::testing::Test {

protected:

    TiffComponent* component;



    void SetUp() override {

        component = new TiffComponent(0x123, IfdId::rootIFD);

    }



    void TearDown() override {

        delete component;

    }

};



TEST_F(TiffComponentTest_229, TagReturnsCorrectValue_229) {

    EXPECT_EQ(component->tag(), 0x123);

}



TEST_F(TiffComponentTest_229, GroupReturnsDefaultValue_229) {

    EXPECT_EQ(component->group(), IfdId::rootIFD);

}



TEST_F(TiffComponentTest_229, StartSetsAndGetsCorrectValue_229) {

    byte data[] = {0x1, 0x2, 0x3};

    component->setStart(data);

    EXPECT_EQ(component->start(), data);

}



TEST_F(TiffComponentTest_229, CountReturnsDefaultValue_229) {

    EXPECT_EQ(component->count(), 0);

}



TEST_F(TiffComponentTest_229, SizeReturnsDefaultValue_229) {

    EXPECT_EQ(component->size(), 0);

}



TEST_F(TiffComponentTest_229, SizeDataReturnsDefaultValue_229) {

    EXPECT_EQ(component->sizeData(), 0);

}



TEST_F(TiffComponentTest_229, SizeImageReturnsDefaultValue_229) {

    EXPECT_EQ(component->sizeImage(), 0);

}



TEST_F(TiffComponentTest_229, CloneCreatesNewInstance_229) {

    auto cloned = component->clone();

    EXPECT_NE(cloned.get(), component);

    EXPECT_EQ(cloned->tag(), component->tag());

    EXPECT_EQ(cloned->group(), component->group());

    delete cloned;

}



TEST_F(TiffComponentTest_229, AddChildReturnsSelf_229) {

    auto child = std::make_shared<TiffComponent>(0x456, IfdId::rootIFD);

    auto result = component->addChild(child);

    EXPECT_EQ(result, component);

}



TEST_F(TiffComponentTest_229, AddNextReturnsSelf_229) {

    auto next = TiffComponent::UniquePtr(new TiffComponent(0x789, IfdId::rootIFD));

    auto result = component->addNext(std::move(next));

    EXPECT_EQ(result, component);

}



TEST_F(TiffComponentTest_229, AddPathReturnsSelf_229) {

    TiffPath path;

    auto object = TiffComponent::UniquePtr(new TiffComponent(0xabc, IfdId::rootIFD));

    auto result = component->addPath(0xdef, path, nullptr, std::move(object));

    EXPECT_EQ(result, component);

}



TEST_F(TiffComponentTest_229, AcceptDoesNotThrow_229) {

    class MockTiffVisitor : public TiffVisitor {

    public:

        MOCK_METHOD(void, visit, (const TiffComponent&), (override));

    };

    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visit(::testing::Ref(*component))).Times(1);

    component->accept(visitor);

}



TEST_F(TiffComponentTest_229, WriteDoesNotThrow_229) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };

    MockIoWrapper ioWrapper;

    ByteOrder byteOrder = bigEndian;

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(::testing::AnyNumber());

    component->write(ioWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx);

}



TEST_F(TiffComponentTest_229, WriteDataDoesNotThrow_229) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };

    MockIoWrapper ioWrapper;

    ByteOrder byteOrder = bigEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(::testing::AnyNumber());

    component->writeData(ioWrapper, byteOrder, offset, dataIdx, imageIdx);

}



TEST_F(TiffComponentTest_229, WriteImageDoesNotThrow_229) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    };

    MockIoWrapper ioWrapper;

    ByteOrder byteOrder = bigEndian;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(::testing::AnyNumber());

    component->writeImage(ioWrapper, byteOrder);

}
