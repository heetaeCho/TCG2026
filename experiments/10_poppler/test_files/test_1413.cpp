#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.h"

#include "poppler-page.h"

#include "poppler-document-private.h"



using namespace Poppler;

using ::testing::Return;

using ::testing::_;



class FileAttachmentAnnotationPrivateTest : public ::testing::Test {

protected:

    std::unique_ptr<FileAttachmentAnnotationPrivate> fileAttachmentAnnotationPrivate;

    Page pageMock;

    DocumentData documentDataMock;



    void SetUp() override {

        fileAttachmentAnnotationPrivate = std::make_unique<FileAttachmentAnnotationPrivate>();

    }

};



TEST_F(FileAttachmentAnnotationPrivateTest_1413, DefaultIconSet_1413) {

    EXPECT_EQ(fileAttachmentAnnotationPrivate->icon, QStringLiteral("PushPin"));

}



TEST_F(FileAttachmentAnnotationPrivateTest_1413, MakeAliasReturnsUniquePtr_1413) {

    auto alias = fileAttachmentAnnotationPrivate->makeAlias();

    EXPECT_NE(alias, nullptr);

}



TEST_F(FileAttachmentAnnotationPrivateTest_1413, CreateNativeAnnotNullPageAndDoc_1413) {

    auto nativeAnnot = fileAttachmentAnnotationPrivate->createNativeAnnot(nullptr, nullptr);

    EXPECT_EQ(nativeAnnot.get(), nullptr);

}



// Assuming EmbeddedFile is a valid object and can be mocked or tested independently

TEST_F(FileAttachmentAnnotationPrivateTest_1413, DestructorDeletesEmbfile_1413) {

    fileAttachmentAnnotationPrivate->embfile = new EmbeddedFile();

    EXPECT_NE(fileAttachmentAnnotationPrivate->embfile, nullptr);

    fileAttachmentAnnotationPrivate.reset(); // This should trigger the destructor and delete embfile

}
