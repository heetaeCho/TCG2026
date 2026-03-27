#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class MockPage : public Page {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class LinkAnnotationPrivateTest_1409 : public ::testing::Test {

protected:

    std::unique_ptr<LinkAnnotationPrivate> linkAnnotationPrivate;

    MockPage mockDestPage;

    MockDocumentData mockDoc;



    void SetUp() override {

        linkAnnotationPrivate = std::make_unique<LinkAnnotationPrivate>();

    }

};



TEST_F(LinkAnnotationPrivateTest_1409, CreateNativeAnnot_ReturnsNullptr_NormalOperation_1409) {

    // Arrange

    EXPECT_CALL(mockDestPage, someMethod()).Times(0); // Ensure no methods are called on mockDestPage

    EXPECT_CALL(mockDoc, someMethod()).Times(0);       // Ensure no methods are called on mockDoc



    // Act

    std::shared_ptr<Annot> result = linkAnnotationPrivate->createNativeAnnot(&mockDestPage, &mockDoc);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(LinkAnnotationPrivateTest_1409, CreateNativeAnnot_ReturnsNullptr_BoundaryConditions_1409) {

    // Arrange

    EXPECT_CALL(mockDestPage, someMethod()).Times(0); // Ensure no methods are called on mockDestPage

    EXPECT_CALL(mockDoc, someMethod()).Times(0);       // Ensure no methods are called on mockDoc



    // Act & Assert

    ASSERT_EQ(linkAnnotationPrivate->createNativeAnnot(nullptr, nullptr), nullptr);

    ASSERT_EQ(linkAnnotationPrivate->createNativeAnnot(&mockDestPage, nullptr), nullptr);

    ASSERT_EQ(linkAnnotationPrivate->createNativeAnnot(nullptr, &mockDoc), nullptr);

}



// Since the function always returns nullptr and does not throw or have side effects observable through public functions,

// there are no exceptional cases to test.
