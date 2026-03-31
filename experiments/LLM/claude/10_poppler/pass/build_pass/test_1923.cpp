#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <string>

// Poppler headers
#include "Outline.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "XRef.h"
#include "Dict.h"
#include "PDFDocFactory.h"

#include <cstdio>
#include <fstream>

class OutlineRemoveChildTest_1923 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF with outlines in memory
    // Returns a GooString containing a minimal PDF
    std::string createMinimalPDFWithOutlines(int numOutlineItems) {
        // Build a minimal PDF with outline items
        std::string pdf;
        pdf += "%PDF-1.4\n";

        // Object 1: Catalog
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R /Outlines 3 0 R >>\nendobj\n";

        // Object 2: Pages
        pdf += "2 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n";

        // Object 3: Outlines root
        if (numOutlineItems == 0) {
            pdf += "3 0 obj\n<< /Type /Outlines /Count 0 >>\nendobj\n";
        } else if (numOutlineItems == 1) {
            pdf += "3 0 obj\n<< /Type /Outlines /Count 1 /First 5 0 R /Last 5 0 R >>\nendobj\n";
        } else if (numOutlineItems == 2) {
            pdf += "3 0 obj\n<< /Type /Outlines /Count 2 /First 5 0 R /Last 6 0 R >>\nendobj\n";
        } else if (numOutlineItems == 3) {
            pdf += "3 0 obj\n<< /Type /Outlines /Count 3 /First 5 0 R /Last 7 0 R >>\nendobj\n";
        }

        // Object 4: Page
        pdf += "4 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        // Outline items
        if (numOutlineItems >= 1) {
            if (numOutlineItems == 1) {
                pdf += "5 0 obj\n<< /Title (Item1) /Parent 3 0 R >>\nendobj\n";
            } else {
                pdf += "5 0 obj\n<< /Title (Item1) /Parent 3 0 R /Next 6 0 R >>\nendobj\n";
            }
        }
        if (numOutlineItems >= 2) {
            if (numOutlineItems == 2) {
                pdf += "6 0 obj\n<< /Title (Item2) /Parent 3 0 R /Prev 5 0 R >>\nendobj\n";
            } else {
                pdf += "6 0 obj\n<< /Title (Item2) /Parent 3 0 R /Prev 5 0 R /Next 7 0 R >>\nendobj\n";
            }
        }
        if (numOutlineItems >= 3) {
            pdf += "7 0 obj\n<< /Title (Item3) /Parent 3 0 R /Prev 6 0 R >>\nendobj\n";
        }

        // xref and trailer
        int numObjects = 5 + numOutlineItems; // 0 + catalog + pages + outlines + page + items
        pdf += "xref\n";
        pdf += "0 " + std::to_string(numObjects) + "\n";
        // We'll use a simple approach - the actual offsets don't matter for 
        // in-memory testing with some PDF loaders, but let's try to be correct
        // For simplicity, we'll write the file and load it
        pdf += "0000000000 65535 f \n";
        
        // We need real offsets, so let's rebuild
        return pdf; // This won't work directly - we need file-based approach
    }

    std::string createTempPDF(int numItems) {
        static int counter = 0;
        std::string filename = "/tmp/test_outline_" + std::to_string(counter++) + "_1923.pdf";
        
        std::vector<std::string> objects;
        std::vector<size_t> offsets;

        std::string header = "%PDF-1.4\n";

        // We'll calculate offsets as we go
        std::string body;
        size_t currentOffset = header.size();

        // Object 1: Catalog
        offsets.push_back(currentOffset);
        std::string obj1;
        if (numItems > 0) {
            obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R /Outlines 3 0 R >>\nendobj\n";
        } else {
            obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        }
        body += obj1;
        currentOffset += obj1.size();

        // Object 2: Pages
        offsets.push_back(currentOffset);
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n";
        body += obj2;
        currentOffset += obj2.size();

        // Object 3: Outlines
        offsets.push_back(currentOffset);
        std::string obj3;
        if (numItems == 0) {
            obj3 = "3 0 obj\n<< /Type /Outlines /Count 0 >>\nendobj\n";
        } else if (numItems == 1) {
            obj3 = "3 0 obj\n<< /Type /Outlines /Count 1 /First 5 0 R /Last 5 0 R >>\nendobj\n";
        } else if (numItems == 2) {
            obj3 = "3 0 obj\n<< /Type /Outlines /Count 2 /First 5 0 R /Last 6 0 R >>\nendobj\n";
        } else {
            obj3 = "3 0 obj\n<< /Type /Outlines /Count " + std::to_string(numItems) + " /First 5 0 R /Last " + std::to_string(4 + numItems) + " 0 R >>\nendobj\n";
        }
        body += obj3;
        currentOffset += obj3.size();

        // Object 4: Page
        offsets.push_back(currentOffset);
        std::string obj4 = "4 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        body += obj4;
        currentOffset += obj4.size();

        // Outline items: objects 5, 6, 7, ...
        for (int i = 0; i < numItems; i++) {
            offsets.push_back(currentOffset);
            int objNum = 5 + i;
            std::string objStr = std::to_string(objNum) + " 0 obj\n<< /Title (Item" + std::to_string(i + 1) + ") /Parent 3 0 R";
            if (i > 0) {
                objStr += " /Prev " + std::to_string(objNum - 1) + " 0 R";
            }
            if (i < numItems - 1) {
                objStr += " /Next " + std::to_string(objNum + 1) + " 0 R";
            }
            objStr += " >>\nendobj\n";
            body += objStr;
            currentOffset += objStr.size();
        }

        // xref
        size_t xrefOffset = header.size() + body.size();
        int totalObjects = 5 + numItems;
        
        std::string xref = "xref\n";
        xref += "0 " + std::to_string(totalObjects) + "\n";
        
        char buf[64];
        snprintf(buf, sizeof(buf), "%010d 65535 f \n", 0);
        xref += buf;
        
        for (int i = 0; i < totalObjects - 1; i++) {
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
            xref += buf;
        }

        std::string trailer = "trailer\n<< /Size " + std::to_string(totalObjects) + " /Root 1 0 R >>\n";
        trailer += "startxref\n" + std::to_string(xrefOffset) + "\n%%EOF\n";

        std::string fullPdf = header + body + xref + trailer;

        std::ofstream out(filename, std::ios::binary);
        out.write(fullPdf.data(), fullPdf.size());
        out.close();

        return filename;
    }
};

TEST_F(OutlineRemoveChildTest_1923, LoadPDFWithNoOutlines_1923) {
    std::string filename = createTempPDF(0);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    // With no outline items defined properly, outline may or may not exist
    // This tests basic loading
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, LoadPDFWithOneOutlineItem_1923) {
    std::string filename = createTempPDF(1);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 1u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, LoadPDFWithTwoOutlineItems_1923) {
    std::string filename = createTempPDF(2);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 2u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, LoadPDFWithThreeOutlineItems_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 3u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveOnlyOutlineItem_1923) {
    std::string filename = createTempPDF(1);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 1u);
    
    // Remove the only item (position 0)
    // This should trigger the prevItemObject.isNull() && nextItemObject.isNull() branch
    outline->removeChild(0);
    
    items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 0u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveFirstOfTwoOutlineItems_1923) {
    std::string filename = createTempPDF(2);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 2u);
    
    // Remove the first item (position 0)
    // This should trigger the prevItemObject.isNull() branch (first item has no Prev)
    outline->removeChild(0);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 1u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveLastOfTwoOutlineItems_1923) {
    std::string filename = createTempPDF(2);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 2u);
    
    // Remove the last item (position 1)
    // This should trigger the nextItemObject.isNull() branch (last item has no Next)
    outline->removeChild(1);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 1u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveMiddleOfThreeOutlineItems_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 3u);
    
    // Remove the middle item (position 1)
    // This should trigger the !prevItemObject.isNull() && !nextItemObject.isNull() branch
    outline->removeChild(1);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveOutOfBoundsIndex_1923) {
    std::string filename = createTempPDF(2);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 2u);
    
    // Remove at an out-of-bounds position - should be a no-op
    outline->removeChild(5);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveAllItemsSequentially_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 3u);
    
    // Remove all items one by one (always remove first)
    outline->removeChild(0);
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    outline->removeChild(0);
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 1u);
    
    outline->removeChild(0);
    items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 0u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveAllItemsFromEnd_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 3u);
    
    // Remove from the end
    outline->removeChild(2);
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    outline->removeChild(1);
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 1u);
    
    outline->removeChild(0);
    items = outline->getItems();
    if (items != nullptr) {
        EXPECT_EQ(items->size(), 0u);
    }
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveFirstOfThreeItems_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 3u);
    
    // Remove first item - triggers prevItemObject.isNull() && !nextItemObject.isNull()
    outline->removeChild(0);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveLastOfThreeItems_1923) {
    std::string filename = createTempPDF(3);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 3u);
    
    // Remove last item - triggers !prevItemObject.isNull() && nextItemObject.isNull()
    outline->removeChild(2);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 2u);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveAtExactBoundary_1923) {
    std::string filename = createTempPDF(2);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    size_t originalSize = items->size();
    
    // Try to remove at exactly the size (out of bounds) - should be no-op
    outline->removeChild(static_cast<unsigned int>(originalSize));
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), originalSize);
    
    std::remove(filename.c_str());
}

TEST_F(OutlineRemoveChildTest_1923, RemoveWithLargeIndex_1923) {
    std::string filename = createTempPDF(1);
    
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    
    Outline *outline = doc->getOutline();
    ASSERT_TRUE(outline != nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    ASSERT_EQ(items->size(), 1u);
    
    // Very large index - should be no-op
    outline->removeChild(999999);
    
    items = outline->getItems();
    ASSERT_TRUE(items != nullptr);
    EXPECT_EQ(items->size(), 1u);
    
    std::remove(filename.c_str());
}
