#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"



using namespace Poppler;

using ::testing::NiceMock;



// Mocking Page and DocumentData classes since they are dependencies

class MockPage : public ::Page {

public:

    MOCK_METHOD0(copy, ::Page*());

};



class MockDocumentData {

public:

    MOCK_METHOD0(getFilePath, std::string());

};



TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnot_ReturnsNullptr_NormalOperation_1414) {

    FileAttachmentAnnotationPrivate faap;

    NiceMock<MockPage> mockPage;

    MockDocumentData mockDoc;



    auto result = faap.createNativeAnnot(&mockPage, &mockDoc);



    EXPECT_EQ(result, nullptr);

}



TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnot_ReturnsNullptr_BoundaryConditions_1414) {

    FileAttachmentAnnotationPrivate faap;

    NiceMock<MockPage> mockPage;

    MockDocumentData mockDoc;



    auto result = faap.createNativeAnnot(nullptr, &mockDoc);



    EXPECT_EQ(result, nullptr);

}



TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnot_ReturnsNullptr_BoundaryConditions2_1414) {

    FileAttachmentAnnotationPrivate faap;

    NiceMock<MockPage> mockPage;

    MockDocumentData mockDoc;



    auto result = faap.createNativeAnnot(&mockPage, nullptr);



    EXPECT_EQ(result, nullptr);

}



TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnot_ReturnsNullptr_BoundaryConditions3_1414) {

    FileAttachmentAnnotationPrivate faap;

    NiceMock<MockPage> mockPage;

    MockDocumentData mockDoc;



    auto result = faap.createNativeAnnot(nullptr, nullptr);



    EXPECT_EQ(result, nullptr);

}
