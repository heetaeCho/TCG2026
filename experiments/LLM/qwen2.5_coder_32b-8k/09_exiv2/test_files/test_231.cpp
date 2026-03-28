#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included for TiffComponent and its dependencies



using namespace Exiv2::Internal;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

};



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visit, (const TiffComponent&), (override));

};



class TiffComponentTest_231 : public ::testing::Test {

protected:

    TiffComponent* tiffComponent;

    MockIoWrapper mockIoWrapper;

    MockTiffVisitor mockTiffVisitor;



    void SetUp() override {

        tiffComponent = new TiffComponent(0x0001, ifdExif);

    }



    void TearDown() override {

        delete tiffComponent;

    }

};



TEST_F(TiffComponentTest_231, SetStartAndGetStart_NormalOperation_231) {

    byte testBuffer[10] = { 0 };

    tiffComponent->setStart(testBuffer);

    EXPECT_EQ(tiffComponent->start(), testBuffer);

}



TEST_F(TiffComponentTest_231, TagAndGroup_ReturnCorrectValues_231) {

    EXPECT_EQ(tiffComponent->tag(), 0x0001);

    EXPECT_EQ(tiffComponent->group(), ifdExif);

}



TEST_F(TiffComponentTest_231, Clone_CreatesNewInstance_231) {

    auto clonedComponent = tiffComponent->clone();

    EXPECT_NE(clonedComponent.get(), tiffComponent);

    EXPECT_EQ(clonedComponent->tag(), tiffComponent->tag());

    EXPECT_EQ(clonedComponent->group(), tiffComponent->group());

}



TEST_F(TiffComponentTest_231, Accept_VisitorCalledOnce_231) {

    EXPECT_CALL(mockTiffVisitor, visit(::testing::Ref(*tiffComponent))).Times(1);

    tiffComponent->accept(mockTiffVisitor);

}



TEST_F(TiffComponentTest_231, WriteData_ReturnsSizeZero_DefaultOperation_231) {

    size_t offset = 0;

    size_t dataIdx = 0;

    EXPECT_EQ(tiffComponent->writeData(mockIoWrapper, littleEndian, offset, dataIdx), 0);

}



TEST_F(TiffComponentTest_231, WriteImage_ReturnsSizeZero_DefaultOperation_231) {

    EXPECT_EQ(tiffComponent->writeImage(mockIoWrapper, littleEndian), 0);

}



TEST_F(TiffComponentTest_231, SizeAndCount_ReturnsZero_DefaultOperation_231) {

    EXPECT_EQ(tiffComponent->size(), 0);

    EXPECT_EQ(tiffComponent->count(), 0);

    EXPECT_EQ(tiffComponent->sizeData(), 0);

    EXPECT_EQ(tiffComponent->sizeImage(), 0);

}



TEST_F(TiffComponentTest_231, AddChild_ReturnsSelf_DefaultOperation_231) {

    auto childComponent = std::make_shared<TiffComponent>(0x0002, ifdExif);

    EXPECT_EQ(tiffComponent->addChild(childComponent), tiffComponent);

}



TEST_F(TiffComponentTest_231, AddNext_ReturnsSelf_DefaultOperation_231) {

    auto nextComponent = std::make_unique<TiffComponent>(0x0003, ifdExif);

    EXPECT_EQ(tiffComponent->addNext(std::move(nextComponent)), tiffComponent);

}



TEST_F(TiffComponentTest_231, AddPath_ReturnsSelf_DefaultOperation_231) {

    TiffPath path;

    auto componentToAdd = std::make_unique<TiffComponent>(0x0004, ifdExif);

    EXPECT_EQ(tiffComponent->addPath(0x0005, path, tiffComponent, std::move(componentToAdd)), tiffComponent);

}
