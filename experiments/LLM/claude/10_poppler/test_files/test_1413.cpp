#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// We need to include the relevant Poppler headers
// Based on the partial code, we're testing FileAttachmentAnnotationPrivate
// which is part of the Poppler::Annotation hierarchy

// Forward declarations and minimal includes needed
#include "poppler-annotation.h"
#include "poppler-qt5.h"

namespace {

// Test fixture for FileAttachmentAnnotation tests
class FileAttachmentAnnotationTest_1413 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a FileAttachmentAnnotation can be created and destroyed without issues
TEST_F(FileAttachmentAnnotationTest_1413, DefaultConstruction_1413) {
    // FileAttachmentAnnotation is publicly constructible
    Poppler::FileAttachmentAnnotation annotation;
    // Should not crash on construction
    SUCCEED();
}

// Test that the default icon is "PushPin" as indicated by the constructor
TEST_F(FileAttachmentAnnotationTest_1413, DefaultIconIsPushPin_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    QString icon = annotation.fileIconName();
    EXPECT_EQ(icon, QStringLiteral("PushPin"));
}

// Test that setting the file icon name works
TEST_F(FileAttachmentAnnotationTest_1413, SetFileIconName_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    annotation.setFileIconName(QStringLiteral("Paperclip"));
    EXPECT_EQ(annotation.fileIconName(), QStringLiteral("Paperclip"));
}

// Test that the embedded file is null by default
TEST_F(FileAttachmentAnnotationTest_1413, DefaultEmbeddedFileIsNull_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    Poppler::EmbeddedFile *embFile = annotation.embeddedFile();
    EXPECT_EQ(embFile, nullptr);
}

// Test that the subType returns AFileAttachment
TEST_F(FileAttachmentAnnotationTest_1413, SubTypeIsFileAttachment_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    EXPECT_EQ(annotation.subType(), Poppler::Annotation::AFileAttachment);
}

// Test that destruction with null embfile doesn't crash
TEST_F(FileAttachmentAnnotationTest_1413, DestructionWithNullEmbFile_1413) {
    // Create and immediately destroy - embfile is nullptr by default
    {
        Poppler::FileAttachmentAnnotation annotation;
    }
    SUCCEED();
}

// Test setting icon name to empty string
TEST_F(FileAttachmentAnnotationTest_1413, SetEmptyIconName_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    annotation.setFileIconName(QString());
    EXPECT_EQ(annotation.fileIconName(), QString());
}

// Test setting icon name multiple times
TEST_F(FileAttachmentAnnotationTest_1413, SetIconNameMultipleTimes_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    
    annotation.setFileIconName(QStringLiteral("Graph"));
    EXPECT_EQ(annotation.fileIconName(), QStringLiteral("Graph"));
    
    annotation.setFileIconName(QStringLiteral("Tag"));
    EXPECT_EQ(annotation.fileIconName(), QStringLiteral("Tag"));
    
    annotation.setFileIconName(QStringLiteral("PushPin"));
    EXPECT_EQ(annotation.fileIconName(), QStringLiteral("PushPin"));
}

// Test that setEmbeddedFile with nullptr works
TEST_F(FileAttachmentAnnotationTest_1413, SetEmbeddedFileNull_1413) {
    Poppler::FileAttachmentAnnotation annotation;
    annotation.setEmbeddedFile(nullptr);
    EXPECT_EQ(annotation.embeddedFile(), nullptr);
}

// Test that the annotation can be created on the heap and properly destroyed
TEST_F(FileAttachmentAnnotationTest_1413, HeapAllocationAndDeletion_1413) {
    Poppler::FileAttachmentAnnotation *annotation = new Poppler::FileAttachmentAnnotation();
    EXPECT_NE(annotation, nullptr);
    EXPECT_EQ(annotation->subType(), Poppler::Annotation::AFileAttachment);
    EXPECT_EQ(annotation->fileIconName(), QStringLiteral("PushPin"));
    delete annotation;
    SUCCEED();
}

} // namespace
