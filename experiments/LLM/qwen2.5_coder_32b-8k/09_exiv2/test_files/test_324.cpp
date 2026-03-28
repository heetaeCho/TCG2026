#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffimage_int.hpp"



using namespace Exiv2::Internal;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(TiffComponent*, addPath, (uint16_t tag, TiffPath & tiffPath, TiffComponent * pRoot, UniquePtr object), (override));

    MOCK_METHOD(TiffComponent*, addChild, (SharedPtr tiffComponent), (override));

};



class MockTiffCreator : public TiffCreator {

public:

    MOCK_STATIC(std::unique_ptr<TiffComponent>, create, (uint32_t extendedTag, IfdId group));

    MOCK_STATIC(TiffPath, getPath, (uint32_t extendedTag, IfdId group, uint32_t root));

};



class TiffBinaryArrayTest_324 : public ::testing::Test {

protected:

    void SetUp() override {

        arrayCfg = ArrayCfg{TiffType::undefined, 0};

        arrayDef = new ArrayDef{};

        tiffPath.push(TiffPathItem{1, IfdId::root});

        mockComponent = std::make_shared<MockTiffComponent>();

        object = std::make_unique<MockTiffComponent>();

    }



    void TearDown() override {

        delete arrayDef;

    }



    TiffBinaryArray tba{1, IfdId::root, arrayCfg, arrayDef, 0};

    ArrayCfg arrayCfg;

    ArrayDef* arrayDef;

    TiffPath tiffPath;

    std::shared_ptr<MockTiffComponent> mockComponent;

    MockTiffComponent::UniquePtr object;

};



TEST_F(TiffBinaryArrayTest_324, DoAddPath_ReturnsThisWhenTiffPathSizeIsOne_324) {

    EXPECT_CALL(*mockComponent, addPath(testing::_, testing::_, testing::_, testing::_))

        .Times(0);

    

    tba.addChild(mockComponent);



    auto result = tba.doAddPath(1, tiffPath, mockComponent.get(), std::move(object));

    EXPECT_EQ(result, &tba);

}



TEST_F(TiffBinaryArrayTest_324, DoAddPath_CallsElementAddPathWhenTagAndGroupMatch_324) {

    TiffPathItem tpi{1, IfdId::root};

    tiffPath.push(tpi);



    EXPECT_CALL(*mockComponent, tag())

        .WillOnce(testing::Return(1));

    EXPECT_CALL(*mockComponent, group())

        .WillOnce(testing::Return(IfdId::root));

    EXPECT_CALL(*mockComponent, addPath(testing::_, testing::Ref(tiffPath), testing::_, testing::_))

        .Times(1);



    tba.addChild(mockComponent);

    tba.doAddPath(2, tiffPath, mockComponent.get(), std::move(object));

}



TEST_F(TiffBinaryArrayTest_324, DoAddPath_CallsCreateWhenNoMatchingElementFound_324) {

    TiffPathItem tpi{1, IfdId::root};

    tiffPath.push(tpi);



    EXPECT_CALL(*mockComponent, tag())

        .WillOnce(testing::Return(2));

    EXPECT_CALL(MockTiffCreator::create, (testing::_, testing::_))

        .Times(1)

        .WillOnce(testing::Return(std::make_unique<MockTiffComponent>()));



    tba.addChild(mockComponent);

    tba.doAddPath(2, tiffPath, mockComponent.get(), std::move(object));

}



TEST_F(TiffBinaryArrayTest_324, DoAddPath_SetsCountAfterAddingChild_324) {

    TiffPathItem tpi{1, IfdId::root};

    tiffPath.push(tpi);



    EXPECT_CALL(MockTiffCreator::create, (testing::_, testing::_))

        .Times(1)

        .WillOnce(testing::Return(std::make_unique<MockTiffComponent>()));



    tba.addChild(mockComponent);

    tba.doAddPath(2, tiffPath, mockComponent.get(), std::move(object));

    

    EXPECT_EQ(tba.count(), 1);

}



TEST_F(TiffBinaryArrayTest_324, DoAddPath_ReturnsNullptrWhenObjectIsNull_324) {

    object = nullptr;

    auto result = tba.doAddPath(1, tiffPath, mockComponent.get(), std::move(object));

    EXPECT_EQ(result, nullptr);

}



TEST_F(TiffBinaryArrayTest_324, DoAddPath_ReturnsCorrectChildWhenAddingNewElement_324) {

    TiffPathItem tpi{1, IfdId::root};

    tiffPath.push(tpi);



    MockTiffComponent* expectedChild = new MockTiffComponent();

    EXPECT_CALL(MockTiffCreator::create, (testing::_, testing::_))

        .Times(1)

        .WillOnce(testing::Return(std::unique_ptr<MockTiffComponent>(expectedChild)));



    tba.addChild(mockComponent);

    auto result = tba.doAddPath(2, tiffPath, mockComponent.get(), std::move(object));

    

    EXPECT_EQ(result, expectedChild);

}
