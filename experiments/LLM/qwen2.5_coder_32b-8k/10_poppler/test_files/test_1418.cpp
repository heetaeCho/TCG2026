#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"



using namespace Poppler;

using ::testing::Return;

using ::testing::_;



class MockPage : public Page {

public:

    MOCK_METHOD0(createNativeAnnot, std::shared_ptr<Annot>(DocumentData*));

};



class MockDocumentData : public DocumentData {};



class MovieAnnotationPrivateTest_1418 : public ::testing::Test {

protected:

    MovieAnnotationPrivate movie_annotation_private_;

    MockPage mock_page_;

    MockDocumentData mock_doc_data_;

};



TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnsNullptr_NormalOperation_1418) {

    EXPECT_EQ(movie_annotation_private_.createNativeAnnot(&mock_page_, &mock_doc_data_), nullptr);

}



TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotBoundaryCondition_PageNull_1418) {

    EXPECT_EQ(movie_annotation_private_.createNativeAnnot(nullptr, &mock_doc_data_), nullptr);

}



TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotBoundaryCondition_DocumentDataNull_1418) {

    EXPECT_EQ(movie_annotation_private_.createNativeAnnot(&mock_page_, nullptr), nullptr);

}



TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotBoundaryCondition_BothNull_1418) {

    EXPECT_EQ(movie_annotation_private_.createNativeAnnot(nullptr, nullptr), nullptr);

}
