#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray*), (override));

    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray*), (override));

};



class TiffBinaryArrayTest_346 : public ::testing::Test {

protected:

    void SetUp() override {

        arrayCfg = std::make_unique<ArrayCfg>();

        arrayDef = std::make_unique<ArrayDef>();

        tiffBinaryArray = std::make_unique<TiffBinaryArray>(1, IfdId::rootIFD, *arrayCfg, arrayDef.get(), 1);

    }



    MockTiffVisitor mockVisitor;

    std::unique_ptr<ArrayCfg> arrayCfg;

    std::unique_ptr<ArrayDef> arrayDef;

    std::unique_ptr<TiffBinaryArray> tiffBinaryArray;

};



TEST_F(TiffBinaryArrayTest_346, DoAccept_VisitsBinaryArrayAndElements_346) {

    EXPECT_CALL(mockVisitor, visitBinaryArray(tiffBinaryArray.get())).Times(1);

    EXPECT_CALL(mockVisitor, go(TiffVisitor::geTraverse)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(tiffBinaryArray.get())).Times(1);



    tiffBinaryArray->doAccept(mockVisitor);

}



TEST_F(TiffBinaryArrayTest_346, DoAccept_DoesNotVisitElementsIfGoReturnsFalse_346) {

    EXPECT_CALL(mockVisitor, visitBinaryArray(tiffBinaryArray.get())).Times(1);

    EXPECT_CALL(mockVisitor, go(TiffVisitor::geTraverse)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(tiffBinaryArray.get())).Times(0);



    tiffBinaryArray->doAccept(mockVisitor);

}



TEST_F(TiffBinaryArrayTest_346, DoAccept_VisitsElementsIfGoReturnsTrue_346) {

    auto element = std::make_unique<TiffComponent>(1, IfdId::rootIFD);

    tiffBinaryArray->addElement(0, *arrayDef);



    EXPECT_CALL(mockVisitor, visitBinaryArray(tiffBinaryArray.get())).Times(1);

    EXPECT_CALL(mockVisitor, go(TiffVisitor::geTraverse)).WillOnce(::testing::Return(true));

    EXPECT_CALL(*element, accept(_)).Times(1);

    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(tiffBinaryArray.get())).Times(1);



    tiffBinaryArray->doAccept(mockVisitor);

}
