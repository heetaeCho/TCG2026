#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class MockPage : public Page {

public:

    MOCK_METHOD0(createAnnot, std::shared_ptr<Annot>());

};



class MockDocumentData { };



class ScreenAnnotationPrivateTest_1420 : public ::testing::Test {

protected:

    std::unique_ptr<ScreenAnnotationPrivate> screen_annotation_private;

    MockPage mock_page;

    MockDocumentData mock_doc;



    void SetUp() override {

        screen_annotation_private = std::make_unique<ScreenAnnotationPrivate>();

    }

};



TEST_F(ScreenAnnotationPrivateTest_1420, CreateNativeAnnot_ReturnsNullptr_1420) {

    // Arrange

    EXPECT_CALL(mock_page, createAnnot()).Times(0);



    // Act

    auto result = screen_annotation_private->createNativeAnnot(&mock_page, &mock_doc);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(ScreenAnnotationPrivateTest_1420, CreateNativeAnnot_IgnoresPageArgument_1420) {

    // Arrange

    EXPECT_CALL(mock_page, createAnnot()).Times(0);



    // Act

    auto result = screen_annotation_private->createNativeAnnot(&mock_page, &mock_doc);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(ScreenAnnotationPrivateTest_1420, CreateNativeAnnot_IgnoresDocArgument_1420) {

    // Arrange

    EXPECT_CALL(mock_page, createAnnot()).Times(0);



    // Act

    auto result = screen_annotation_private->createNativeAnnot(&mock_page, &mock_doc);



    // Assert

    ASSERT_EQ(result, nullptr);

}
