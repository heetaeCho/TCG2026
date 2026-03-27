#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



// Mock classes for dependencies

class MockPage : public Page {

public:

    MOCK_METHOD0(createAnnot, std::shared_ptr<Annot>());

};



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD0(getPageCount, int());

};



// Test fixture for SoundAnnotationPrivate

class SoundAnnotationPrivateTest_1415 : public ::testing::Test {

protected:

    SoundAnnotationPrivate* sound_annotation_private;



    void SetUp() override {

        sound_annotation_private = new SoundAnnotationPrivate();

    }



    void TearDown() override {

        delete sound_annotation_private;

    }

};



// Test normal operation of makeAlias

TEST_F(SoundAnnotationPrivateTest_1415, MakeAlias_ReturnsUniquePtr_1415) {

    auto alias = sound_annotation_private->makeAlias();

    EXPECT_NE(alias.get(), nullptr);

}



// Test boundary condition of createNativeAnnot with valid parameters

TEST_F(SoundAnnotationPrivateTest_1415, CreateNativeAnnot_ValidParameters_ReturnsSharedPtr_1415) {

    NiceMock<MockPage> mock_page;

    NiceMock<MockDocumentData> mock_doc;



    auto native_annot = sound_annotation_private->createNativeAnnot(&mock_page, &mock_doc);

    EXPECT_NE(native_annot.get(), nullptr);

}



// Test boundary condition of createNativeAnnot with null page parameter

TEST_F(SoundAnnotationPrivateTest_1415, CreateNativeAnnot_NullPage_ReturnsNullSharedPtr_1415) {

    NiceMock<MockDocumentData> mock_doc;



    auto native_annot = sound_annotation_private->createNativeAnnot(nullptr, &mock_doc);

    EXPECT_EQ(native_annot.get(), nullptr);

}



// Test boundary condition of createNativeAnnot with null document parameter

TEST_F(SoundAnnotationPrivateTest_1415, CreateNativeAnnot_NullDocument_ReturnsNullSharedPtr_1415) {

    NiceMock<MockPage> mock_page;



    auto native_annot = sound_annotation_private->createNativeAnnot(&mock_page, nullptr);

    EXPECT_EQ(native_annot.get(), nullptr);

}



// Test boundary condition of createNativeAnnot with null parameters

TEST_F(SoundAnnotationPrivateTest_1415, CreateNativeAnnot_NullParameters_ReturnsNullSharedPtr_1415) {

    auto native_annot = sound_annotation_private->createNativeAnnot(nullptr, nullptr);

    EXPECT_EQ(native_annot.get(), nullptr);

}
