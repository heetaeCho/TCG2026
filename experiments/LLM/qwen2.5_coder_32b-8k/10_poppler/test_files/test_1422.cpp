#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"

#include "Page.h"

#include "DocumentData.h"



using namespace Poppler;

using namespace testing;



class RichMediaAnnotationPrivateTest : public Test {

protected:

    Mock<Annot> mockAnnot;

    NiceMock<Mock<DocumentData>> mockDocData;

    NiceMock<Mock<Page>> mockPage;

    std::unique_ptr<RichMediaAnnotationPrivate> richMediaAnnotationPrivate;



    void SetUp() override {

        richMediaAnnotationPrivate = std::make_unique<RichMediaAnnotationPrivate>();

    }

};



TEST_F(RichMediaAnnotationPrivateTest_CreateNativeAnnot_ReturnsNullptr_1422, NormalOperation_1422) {

    auto result = richMediaAnnotationPrivate->createNativeAnnot(&mockPage, &mockDocData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(RichMediaAnnotationPrivateTest_CreateNativeAnnot_NullPtrDestPage_1422, BoundaryConditions_1422) {

    auto result = richMediaAnnotationPrivate->createNativeAnnot(nullptr, &mockDocData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(RichMediaAnnotationPrivateTest_CreateNativeAnnot_NullPtrDocument_1422, BoundaryConditions_1422) {

    auto result = richMediaAnnotationPrivate->createNativeAnnot(&mockPage, nullptr);

    EXPECT_EQ(result, nullptr);

}
