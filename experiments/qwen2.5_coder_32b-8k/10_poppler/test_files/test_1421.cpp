#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"



using namespace Poppler;

using ::testing::Return;



class WidgetAnnotationPrivateTest : public ::testing::Test {

protected:

    std::shared_ptr<WidgetAnnotationPrivate> widgetAnnotationPrivate;

    Page* mockPage;

    DocumentData* mockDocumentData;



    void SetUp() override {

        widgetAnnotationPrivate = std::make_shared<WidgetAnnotationPrivate>();

        mockPage = nullptr;  // Assuming the page pointer can be null for this test

        mockDocumentData = nullptr;  // Assuming the document data pointer can be null for this test

    }

};



TEST_F(WidgetAnnotationPrivateTest_1421, CreateNativeAnnot_ReturnsNullptr_NormalOperation_1421) {

    auto result = widgetAnnotationPrivate->createNativeAnnot(mockPage, mockDocumentData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(WidgetAnnotationPrivateTest_1421, CreateNativeAnnot_ReturnsNullptr_NullPage_1421) {

    Page* nullPage = nullptr;

    auto result = widgetAnnotationPrivate->createNativeAnnot(nullPage, mockDocumentData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(WidgetAnnotationPrivateTest_1421, CreateNativeAnnot_ReturnsNullptr_NullDocumentData_1421) {

    DocumentData* nullDocumentData = nullptr;

    auto result = widgetAnnotationPrivate->createNativeAnnot(mockPage, nullDocumentData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(WidgetAnnotationPrivateTest_1421, CreateNativeAnnot_ReturnsNullptr_NullBoth_1421) {

    Page* nullPage = nullptr;

    DocumentData* nullDocumentData = nullptr;

    auto result = widgetAnnotationPrivate->createNativeAnnot(nullPage, nullDocumentData);

    EXPECT_EQ(result, nullptr);

}
