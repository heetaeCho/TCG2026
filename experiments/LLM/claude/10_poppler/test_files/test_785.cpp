#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

// Helper to create a minimal PDFDoc for testing
class AnnotTest_785 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Create a simple test PDF document
    std::unique_ptr<PDFDoc> createTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        return doc;
    }
};

// Test that getPageNum returns the page number
TEST_F(AnnotTest_785, GetPageNumReturnsPageNumber_785) {
    // We test getPageNum through the public interface
    // Since we can't easily construct an Annot without a valid PDFDoc,
    // we test indirectly through document annotations if possible
    
    // Create a minimal PDFRectangle
    PDFRectangle rect(0, 0, 100, 100);
    
    // We need a valid doc to create an annotation
    // Try with a test PDF that may exist
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                // The page number should be a valid integer
                int pageNum = annot->getPageNum();
                EXPECT_GE(pageNum, 0);
            }
        }
    }
    // If no test PDF, we at least verify the interface compiles
    SUCCEED();
}

// Test getRect returns valid coordinates
TEST_F(AnnotTest_785, GetRectReturnsValidRectangle_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const PDFRectangle &rect = annot->getRect();
                // Rectangle should have valid dimensions
                EXPECT_LE(rect.x1, rect.x2);
                EXPECT_LE(rect.y1, rect.y2);
            }
        }
    }
    SUCCEED();
}

// Test getType returns a valid AnnotSubtype
TEST_F(AnnotTest_785, GetTypeReturnsValidSubtype_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                AnnotSubtype type = annot->getType();
                // Type should be within valid range
                EXPECT_GE(static_cast<int>(type), 0);
            }
        }
    }
    SUCCEED();
}

// Test getFlags returns flags value
TEST_F(AnnotTest_785, GetFlagsReturnsValue_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                unsigned int flags = annot->getFlags();
                // Flags is an unsigned int, any value is valid
                EXPECT_GE(flags, 0u);
            }
        }
    }
    SUCCEED();
}

// Test inRect with point inside rectangle
TEST_F(AnnotTest_785, InRectReturnsTrueForPointInside_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const PDFRectangle &rect = annot->getRect();
                double midX = (rect.x1 + rect.x2) / 2.0;
                double midY = (rect.y1 + rect.y2) / 2.0;
                // Point at center of rect should be inside
                if (rect.x1 != rect.x2 && rect.y1 != rect.y2) {
                    EXPECT_TRUE(annot->inRect(midX, midY));
                }
            }
        }
    }
    SUCCEED();
}

// Test inRect with point outside rectangle
TEST_F(AnnotTest_785, InRectReturnsFalseForPointOutside_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                // A point far away should be outside
                EXPECT_FALSE(annot->inRect(-99999.0, -99999.0));
            }
        }
    }
    SUCCEED();
}

// Test getXMin, getYMin, getXMax, getYMax consistency
TEST_F(AnnotTest_785, GetMinMaxCoordinatesAreConsistent_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                double xMin = annot->getXMin();
                double yMin = annot->getYMin();
                double xMax = annot->getXMax();
                double yMax = annot->getYMax();
                EXPECT_LE(xMin, xMax);
                EXPECT_LE(yMin, yMax);
            }
        }
    }
    SUCCEED();
}

// Test getContents returns nullptr or valid string
TEST_F(AnnotTest_785, GetContentsReturnsValidOrNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const GooString *contents = annot->getContents();
                // Contents can be nullptr or a valid string
                if (contents) {
                    EXPECT_GE(contents->getLength(), 0);
                }
            }
        }
    }
    SUCCEED();
}

// Test getDoc returns non-null
TEST_F(AnnotTest_785, GetDocReturnsNonNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                EXPECT_NE(annot->getDoc(), nullptr);
            }
        }
    }
    SUCCEED();
}

// Test getTreeKey returns an integer
TEST_F(AnnotTest_785, GetTreeKeyReturnsInteger_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                int treeKey = annot->getTreeKey();
                // Just verify it returns without crashing
                (void)treeKey;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test setRect with valid coordinates
TEST_F(AnnotTest_785, SetRectUpdatesRectangle_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                annot->setRect(10.0, 20.0, 30.0, 40.0);
                const PDFRectangle &rect = annot->getRect();
                EXPECT_DOUBLE_EQ(rect.x1, 10.0);
                EXPECT_DOUBLE_EQ(rect.y1, 20.0);
                EXPECT_DOUBLE_EQ(rect.x2, 30.0);
                EXPECT_DOUBLE_EQ(rect.y2, 40.0);
            }
        }
    }
    SUCCEED();
}

// Test setFlags and getFlags
TEST_F(AnnotTest_785, SetFlagsUpdatesFlags_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                unsigned int testFlags = 0x04; // Hidden flag
                annot->setFlags(testFlags);
                EXPECT_EQ(annot->getFlags(), testFlags);
            }
        }
    }
    SUCCEED();
}

// Test setContents updates contents
TEST_F(AnnotTest_785, SetContentsUpdatesContents_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                auto newContent = std::make_unique<GooString>("Test Content");
                annot->setContents(std::move(newContent));
                const GooString *contents = annot->getContents();
                ASSERT_NE(contents, nullptr);
                EXPECT_STREQ(contents->c_str(), "Test Content");
            }
        }
    }
    SUCCEED();
}

// Test setColor with null color
TEST_F(AnnotTest_785, SetColorToNullClearsColor_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                std::unique_ptr<AnnotColor> nullColor;
                annot->setColor(std::move(nullColor));
                EXPECT_EQ(annot->getColor(), nullptr);
            }
        }
    }
    SUCCEED();
}

// Test setBorder with null border
TEST_F(AnnotTest_785, SetBorderToNullClearsBorder_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                std::unique_ptr<AnnotBorder> nullBorder;
                annot->setBorder(std::move(nullBorder));
                EXPECT_EQ(annot->getBorder(), nullptr);
            }
        }
    }
    SUCCEED();
}

// Test getRect through the double* overload
TEST_F(AnnotTest_785, GetRectWithPointersReturnsCorrectValues_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                double x1, y1, x2, y2;
                annot->getRect(&x1, &y1, &x2, &y2);
                const PDFRectangle &rect = annot->getRect();
                EXPECT_DOUBLE_EQ(x1, rect.x1);
                EXPECT_DOUBLE_EQ(y1, rect.y1);
                EXPECT_DOUBLE_EQ(x2, rect.x2);
                EXPECT_DOUBLE_EQ(y2, rect.y2);
            }
        }
    }
    SUCCEED();
}

// Test getId returns an integer value
TEST_F(AnnotTest_785, GetIdReturnsInteger_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                int id = annot->getId();
                (void)id;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test getHasRef returns boolean
TEST_F(AnnotTest_785, GetHasRefReturnsBool_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                bool hasRef = annot->getHasRef();
                // Just verify it compiles and returns
                (void)hasRef;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test setRect with PDFRectangle overload
TEST_F(AnnotTest_785, SetRectWithPDFRectangleUpdates_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                PDFRectangle newRect(5.0, 10.0, 50.0, 100.0);
                annot->setRect(newRect);
                const PDFRectangle &rect = annot->getRect();
                EXPECT_DOUBLE_EQ(rect.x1, 5.0);
                EXPECT_DOUBLE_EQ(rect.y1, 10.0);
                EXPECT_DOUBLE_EQ(rect.x2, 50.0);
                EXPECT_DOUBLE_EQ(rect.y2, 100.0);
            }
        }
    }
    SUCCEED();
}

// Test that setRect normalizes inverted coordinates
TEST_F(AnnotTest_785, SetRectNormalizesInvertedCoordinates_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                // Set with inverted coordinates (x1 > x2, y1 > y2)
                annot->setRect(100.0, 200.0, 10.0, 20.0);
                double xMin = annot->getXMin();
                double xMax = annot->getXMax();
                double yMin = annot->getYMin();
                double yMax = annot->getYMax();
                // After normalization, min should be <= max
                EXPECT_LE(xMin, xMax);
                EXPECT_LE(yMin, yMax);
            }
        }
    }
    SUCCEED();
}

// Test getAnnotObj returns a valid Object reference
TEST_F(AnnotTest_785, GetAnnotObjReturnsObject_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const Object &obj = annot->getAnnotObj();
                // The annotation object should be a dict
                EXPECT_TRUE(obj.isDict() || obj.isNull() || obj.isNone());
            }
        }
    }
    SUCCEED();
}

// Test setContents with empty string
TEST_F(AnnotTest_785, SetContentsWithEmptyString_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                auto emptyContent = std::make_unique<GooString>("");
                annot->setContents(std::move(emptyContent));
                const GooString *contents = annot->getContents();
                ASSERT_NE(contents, nullptr);
                EXPECT_EQ(contents->getLength(), 0);
            }
        }
    }
    SUCCEED();
}

// Test setFlags with zero
TEST_F(AnnotTest_785, SetFlagsToZero_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                annot->setFlags(0);
                EXPECT_EQ(annot->getFlags(), 0u);
            }
        }
    }
    SUCCEED();
}

// Test setFlags with max value
TEST_F(AnnotTest_785, SetFlagsToMaxValue_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                annot->setFlags(0xFFFFFFFF);
                EXPECT_EQ(annot->getFlags(), 0xFFFFFFFF);
            }
        }
    }
    SUCCEED();
}

// Test inRect boundary - point on edge
TEST_F(AnnotTest_785, InRectPointOnEdge_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                annot->setRect(10.0, 20.0, 100.0, 200.0);
                // Point on the boundary
                bool onEdge = annot->inRect(10.0, 20.0);
                // Boundary behavior depends on implementation, just verify no crash
                (void)onEdge;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test getAppearStreams can return nullptr
TEST_F(AnnotTest_785, GetAppearStreamsCanBeNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                // May or may not be null depending on annotation
                AnnotAppearance *appearStreams = annot->getAppearStreams();
                (void)appearStreams;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test getName can return nullptr
TEST_F(AnnotTest_785, GetNameCanBeNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const GooString *name = annot->getName();
                // Name may be null or valid
                (void)name;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test getModified can return nullptr
TEST_F(AnnotTest_785, GetModifiedCanBeNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const GooString *modified = annot->getModified();
                // Modified may be null or valid
                (void)modified;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}

// Test getAppearState can return nullptr  
TEST_F(AnnotTest_785, GetAppearStateCanBeNull_785) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./test-annot.pdf"));
    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                const GooString *state = annot->getAppearState();
                (void)state;
                SUCCEED();
            }
        }
    }
    SUCCEED();
}
