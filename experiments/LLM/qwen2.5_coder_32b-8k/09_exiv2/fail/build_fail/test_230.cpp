#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

};



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visit, (TiffComponent&), (override));

};



class TiffComponentTest_230 : public ::testing::Test {

protected:

    TiffComponent* component;

    IfdId testGroup = 10;

    uint16_t testTag = 1;



    void SetUp() override {

        component = new TiffComponent(testTag, testGroup);

    }



    void TearDown() override {

        delete component;

    }

};



TEST_F(TiffComponentTest_230, GroupReturnsCorrectValue_230) {

    EXPECT_EQ(component->group(), testGroup);

}



TEST_F(TiffComponentTest_230, TagReturnsCorrectValue_230) {

    EXPECT_EQ(component->tag(), testTag);

}



TEST_F(TiffComponentTest_230, StartReturnsNullByDefault_230) {

    EXPECT_EQ(component->start(), nullptr);

}



TEST_F(TiffComponentTest_230, SetStartSetsCorrectPointer_230) {

    byte testData = 42;

    component->setStart(&testData);

    EXPECT_EQ(component->start(), &testData);

}



TEST_F(TiffComponentTest_230, AcceptCallsVisitorVisitMethod_230) {

    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visit(_)).Times(1);

    component->accept(visitor);

}



TEST_F(TiffComponentTest_230, WriteDoesNotCrashWithValidArguments_230) {

    MockIoWrapper ioWrapper;

    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(1);

    component->write(ioWrapper, littleEndian, offset, valueIdx, dataIdx, imageIdx);

}



TEST_F(TiffComponentTest_230, WriteDataDoesNotCrashWithValidArguments_230) {

    MockIoWrapper ioWrapper;

    size_t offset = 0, dataIdx = 0, imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(1);

    component->writeData(ioWrapper, littleEndian, offset, dataIdx, imageIdx);

}



TEST_F(TiffComponentTest_230, WriteImageDoesNotCrashWithValidArguments_230) {

    MockIoWrapper ioWrapper;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(1);

    component->writeImage(ioWrapper, littleEndian);

}



TEST_F(TiffComponentTest_230, SizeReturnsZeroByDefault_230) {

    EXPECT_EQ(component->size(), 0);

}



TEST_F(TiffComponentTest_230, CountReturnsZeroByDefault_230) {

    EXPECT_EQ(component->count(), 0);

}



TEST_F(TiffComponentTest_230, SizeDataReturnsZeroByDefault_230) {

    EXPECT_EQ(component->sizeData(), 0);

}



TEST_F(TiffComponentTest_230, SizeImageReturnsZeroByDefault_230) {

    EXPECT_EQ(component->sizeImage(), 0);

}
