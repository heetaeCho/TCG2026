#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QLinkedList>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QList>

// Poppler includes
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"
#include "PDFDoc.h"
#include "Page.h"
#include "Annot.h"
#include "GlobalParams.h"

using namespace Poppler;

class InkAnnotationPrivateTest_1407 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid PDF document to work with
        // Create a minimal document for testing
        globalParams = std::make_unique<GlobalParams>();
    }

    void TearDown() override {
        globalParams.reset();
    }

    // Helper to create a document from a minimal PDF
    std::unique_ptr<Poppler::Document> createTestDocument() {
        // Create a minimal valid PDF in memory
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }
};

// Test that InkAnnotation can be created with default state
TEST_F(InkAnnotationPrivateTest_1407, DefaultConstructionCreatesValidAnnotation_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    ASSERT_NE(ann, nullptr);
    EXPECT_EQ(ann->subType(), Poppler::Annotation::AInk);
}

// Test that InkAnnotation inkPaths are empty by default
TEST_F(InkAnnotationPrivateTest_1407, DefaultInkPathsAreEmpty_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    QList<QLinkedList<QPointF>> paths = ann->inkPaths();
    EXPECT_TRUE(paths.isEmpty());
}

// Test that setting ink paths works correctly
TEST_F(InkAnnotationPrivateTest_1407, SetInkPathsStoresPaths_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path1;
    path1.append(QPointF(0.1, 0.1));
    path1.append(QPointF(0.5, 0.5));
    path1.append(QPointF(0.9, 0.9));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path1);
    
    ann->setInkPaths(paths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    EXPECT_EQ(retrieved.size(), 1);
    EXPECT_EQ(retrieved[0].size(), 3);
}

// Test setting multiple ink paths
TEST_F(InkAnnotationPrivateTest_1407, SetMultipleInkPaths_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path1;
    path1.append(QPointF(0.0, 0.0));
    path1.append(QPointF(0.5, 0.5));
    
    QLinkedList<QPointF> path2;
    path2.append(QPointF(0.2, 0.3));
    path2.append(QPointF(0.7, 0.8));
    path2.append(QPointF(0.9, 0.1));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path1);
    paths.append(path2);
    
    ann->setInkPaths(paths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    EXPECT_EQ(retrieved.size(), 2);
    EXPECT_EQ(retrieved[0].size(), 2);
    EXPECT_EQ(retrieved[1].size(), 3);
}

// Test setting empty ink paths
TEST_F(InkAnnotationPrivateTest_1407, SetEmptyInkPaths_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QList<QLinkedList<QPointF>> emptyPaths;
    ann->setInkPaths(emptyPaths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    EXPECT_TRUE(retrieved.isEmpty());
}

// Test that overwriting ink paths replaces previous paths
TEST_F(InkAnnotationPrivateTest_1407, OverwriteInkPathsReplacesPrevious_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path1;
    path1.append(QPointF(0.1, 0.1));
    
    QList<QLinkedList<QPointF>> paths1;
    paths1.append(path1);
    ann->setInkPaths(paths1);
    
    EXPECT_EQ(ann->inkPaths().size(), 1);
    
    QLinkedList<QPointF> path2;
    path2.append(QPointF(0.2, 0.2));
    QLinkedList<QPointF> path3;
    path3.append(QPointF(0.3, 0.3));
    
    QList<QLinkedList<QPointF>> paths2;
    paths2.append(path2);
    paths2.append(path3);
    ann->setInkPaths(paths2);
    
    EXPECT_EQ(ann->inkPaths().size(), 2);
}

// Test that InkAnnotation boundary can be set
TEST_F(InkAnnotationPrivateTest_1407, SetBoundaryIsRetrievable_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QRectF boundary(0.1, 0.2, 0.5, 0.6);
    ann->setBoundary(boundary);
    
    QRectF retrieved = ann->boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), boundary.x());
    EXPECT_DOUBLE_EQ(retrieved.y(), boundary.y());
    EXPECT_DOUBLE_EQ(retrieved.width(), boundary.width());
    EXPECT_DOUBLE_EQ(retrieved.height(), boundary.height());
}

// Test that annotation subtype is AInk
TEST_F(InkAnnotationPrivateTest_1407, SubTypeIsInk_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    EXPECT_EQ(ann->subType(), Poppler::Annotation::AInk);
}

// Test setting author on InkAnnotation
TEST_F(InkAnnotationPrivateTest_1407, SetAuthorIsRetrievable_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QString author = "TestAuthor";
    ann->setAuthor(author);
    
    EXPECT_EQ(ann->author(), author);
}

// Test setting contents on InkAnnotation
TEST_F(InkAnnotationPrivateTest_1407, SetContentsIsRetrievable_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QString contents = "Test contents for ink annotation";
    ann->setContents(contents);
    
    EXPECT_EQ(ann->contents(), contents);
}

// Test setting flags on InkAnnotation
TEST_F(InkAnnotationPrivateTest_1407, SetFlagsIsRetrievable_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    ann->setFlags(Poppler::Annotation::Hidden);
    EXPECT_EQ(ann->flags(), static_cast<int>(Poppler::Annotation::Hidden));
}

// Test adding annotation to a document page creates native annotation
TEST_F(InkAnnotationPrivateTest_1407, CreateNativeAnnotWithDocument_1407) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from test document";
    }
    
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    ann->setBoundary(QRectF(0.1, 0.1, 0.3, 0.3));
    
    QLinkedList<QPointF> path;
    path.append(QPointF(0.1, 0.1));
    path.append(QPointF(0.2, 0.2));
    path.append(QPointF(0.3, 0.3));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path);
    ann->setInkPaths(paths);
    
    // Adding annotation to page triggers createNativeAnnot
    page->addAnnotation(ann.get());
    
    // After adding to page, the annotation should still be valid
    EXPECT_EQ(ann->subType(), Poppler::Annotation::AInk);
    
    delete page;
}

// Test single point path
TEST_F(InkAnnotationPrivateTest_1407, SinglePointPath_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path;
    path.append(QPointF(0.5, 0.5));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path);
    
    ann->setInkPaths(paths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    EXPECT_EQ(retrieved.size(), 1);
    EXPECT_EQ(retrieved[0].size(), 1);
    EXPECT_DOUBLE_EQ(retrieved[0].first().x(), 0.5);
    EXPECT_DOUBLE_EQ(retrieved[0].first().y(), 0.5);
}

// Test ink path with boundary coordinates at extremes
TEST_F(InkAnnotationPrivateTest_1407, BoundaryAtZero_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QRectF boundary(0.0, 0.0, 1.0, 1.0);
    ann->setBoundary(boundary);
    
    QRectF retrieved = ann->boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), 0.0);
    EXPECT_DOUBLE_EQ(retrieved.y(), 0.0);
    EXPECT_DOUBLE_EQ(retrieved.width(), 1.0);
    EXPECT_DOUBLE_EQ(retrieved.height(), 1.0);
}

// Test ink path points are stored in order
TEST_F(InkAnnotationPrivateTest_1407, InkPathPointsPreserveOrder_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path;
    path.append(QPointF(0.1, 0.2));
    path.append(QPointF(0.3, 0.4));
    path.append(QPointF(0.5, 0.6));
    path.append(QPointF(0.7, 0.8));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path);
    
    ann->setInkPaths(paths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    ASSERT_EQ(retrieved.size(), 1);
    ASSERT_EQ(retrieved[0].size(), 4);
    
    auto it = retrieved[0].begin();
    EXPECT_DOUBLE_EQ(it->x(), 0.1);
    EXPECT_DOUBLE_EQ(it->y(), 0.2);
    ++it;
    EXPECT_DOUBLE_EQ(it->x(), 0.3);
    EXPECT_DOUBLE_EQ(it->y(), 0.4);
    ++it;
    EXPECT_DOUBLE_EQ(it->x(), 0.5);
    EXPECT_DOUBLE_EQ(it->y(), 0.6);
    ++it;
    EXPECT_DOUBLE_EQ(it->x(), 0.7);
    EXPECT_DOUBLE_EQ(it->y(), 0.8);
}

// Test unique name setting
TEST_F(InkAnnotationPrivateTest_1407, SetUniqueNameIsRetrievable_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QString name = "unique-ink-annotation-123";
    ann->setUniqueName(name);
    
    EXPECT_EQ(ann->uniqueName(), name);
}

// Test empty path within multiple paths
TEST_F(InkAnnotationPrivateTest_1407, EmptyPathWithinMultiplePaths_1407) {
    auto ann = std::make_unique<Poppler::InkAnnotation>();
    
    QLinkedList<QPointF> path1;
    path1.append(QPointF(0.1, 0.1));
    
    QLinkedList<QPointF> emptyPath;
    
    QLinkedList<QPointF> path3;
    path3.append(QPointF(0.9, 0.9));
    
    QList<QLinkedList<QPointF>> paths;
    paths.append(path1);
    paths.append(emptyPath);
    paths.append(path3);
    
    ann->setInkPaths(paths);
    
    QList<QLinkedList<QPointF>> retrieved = ann->inkPaths();
    EXPECT_EQ(retrieved.size(), 3);
    EXPECT_EQ(retrieved[0].size(), 1);
    EXPECT_EQ(retrieved[1].size(), 0);
    EXPECT_EQ(retrieved[2].size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
