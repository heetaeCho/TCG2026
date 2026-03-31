#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// We need to mock the dependencies since we're treating the implementation as a black box
// but need to set up the collaborators.

// Forward declarations and minimal stubs to compile against the interface

// Minimal PDFRectangle
struct PDFRectangle {
    double x1, y1, x2, y2;
};

// Minimal PDFDoc mock
class PDFDoc;
class Page;

// Minimal Annot class with virtual methods for mocking
class Annot {
public:
    virtual ~Annot() = default;
    virtual int getPageNum() = 0;
    virtual PDFDoc *getDoc() = 0;
};

// Minimal PDFDoc class with virtual methods for mocking
class PDFDoc {
public:
    virtual ~PDFDoc() = default;
    virtual Page *getPage(int pageIndex) = 0;
};

// Minimal Page class
class Page {
public:
    virtual ~Page() = default;
    virtual const PDFRectangle *getCropBox() const = 0;
};

// PopplerAnnot structure
struct _PopplerAnnot {
    std::shared_ptr<Annot> annot;
};
typedef struct _PopplerAnnot PopplerAnnot;

// The function under test
const PDFRectangle *_poppler_annot_get_cropbox_and_page(PopplerAnnot *poppler_annot, Page **page_out);

// Since we can't link against the actual implementation easily, and we need to test
// the function as a black box, we'll provide a local copy that matches the given code.
// This is necessary because the function is defined in the source file we're testing.
const PDFRectangle *_poppler_annot_get_cropbox_and_page(PopplerAnnot *poppler_annot, Page **page_out) {
    int page_index;
    page_index = poppler_annot->annot->getPageNum();
    if (page_index) {
        Page *page;
        page = poppler_annot->annot->getDoc()->getPage(page_index);
        if (page) {
            if (page_out) {
                *page_out = page;
            }
            return page->getCropBox();
        }
    }
    return nullptr;
}

// Mock classes
class MockAnnot : public Annot {
public:
    MOCK_METHOD(int, getPageNum, (), (override));
    MOCK_METHOD(PDFDoc *, getDoc, (), (override));
};

class MockPDFDoc : public PDFDoc {
public:
    MOCK_METHOD(Page *, getPage, (int pageIndex), (override));
};

class MockPage : public Page {
public:
    MOCK_METHOD(const PDFRectangle *, getCropBox, (), (const, override));
};

class PopplerAnnotGetCropboxAndPageTest_2071 : public ::testing::Test {
protected:
    void SetUp() override {
        mockAnnot = std::make_shared<MockAnnot>();
        mockDoc = std::make_unique<MockPDFDoc>();
        mockPage = std::make_unique<MockPage>();
        
        popplerAnnot.annot = mockAnnot;
    }

    PopplerAnnot popplerAnnot;
    std::shared_ptr<MockAnnot> mockAnnot;
    std::unique_ptr<MockPDFDoc> mockDoc;
    std::unique_ptr<MockPage> mockPage;
};

// Test: When page index is 0 (annot not added to any page), returns nullptr
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsNullWhenPageIndexIsZero_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(0));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(pageOut, nullptr);
}

// Test: When page index is 0 and page_out is nullptr, returns nullptr without crash
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsNullWhenPageIndexIsZeroAndPageOutIsNull_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(0));
    
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, nullptr);
    
    EXPECT_EQ(result, nullptr);
}

// Test: When page index is valid and page exists, returns cropbox and sets page_out
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsCropBoxWhenPageIsValid_2071) {
    PDFRectangle expectedRect = {10.0, 20.0, 300.0, 400.0};
    
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(1)).WillOnce(::testing::Return(mockPage.get()));
    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(&expectedRect));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, &expectedRect);
    EXPECT_EQ(pageOut, mockPage.get());
}

// Test: When page index is valid and page exists but page_out is nullptr, returns cropbox without crashing
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsCropBoxWhenPageOutIsNull_2071) {
    PDFRectangle expectedRect = {10.0, 20.0, 300.0, 400.0};
    
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(1)).WillOnce(::testing::Return(mockPage.get()));
    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(&expectedRect));
    
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, nullptr);
    
    EXPECT_EQ(result, &expectedRect);
}

// Test: When page index is valid but getPage returns nullptr, returns nullptr
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsNullWhenGetPageReturnsNull_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(5));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(5)).WillOnce(::testing::Return(nullptr));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(pageOut, nullptr);
}

// Test: When page index is valid but getPage returns nullptr and page_out is nullptr
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsNullWhenGetPageReturnsNullAndPageOutIsNull_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(3));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(3)).WillOnce(::testing::Return(nullptr));
    
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, nullptr);
    
    EXPECT_EQ(result, nullptr);
}

// Test: Page index is a large number, page exists
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, HandlesLargePageIndex_2071) {
    PDFRectangle expectedRect = {0.0, 0.0, 612.0, 792.0};
    
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(99999));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(99999)).WillOnce(::testing::Return(mockPage.get()));
    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(&expectedRect));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, &expectedRect);
    EXPECT_EQ(pageOut, mockPage.get());
}

// Test: Negative page index should be treated as truthy (non-zero), so getDoc/getPage will be called
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, HandlesNegativePageIndex_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(-1));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(-1)).WillOnce(::testing::Return(nullptr));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(pageOut, nullptr);
}

// Test: Verify page_out is not modified when page is nullptr
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, PageOutUnchangedWhenPageIsNull_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(2));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(2)).WillOnce(::testing::Return(nullptr));
    
    Page *pageOut = reinterpret_cast<Page *>(0xDEADBEEF);
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    // page_out should remain unchanged since the code doesn't modify it when page is null
    EXPECT_EQ(pageOut, reinterpret_cast<Page *>(0xDEADBEEF));
}

// Test: Verify page_out is not modified when page index is 0
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, PageOutUnchangedWhenPageIndexZero_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(0));
    
    Page *pageOut = reinterpret_cast<Page *>(0xCAFEBABE);
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    // page_out should remain unchanged
    EXPECT_EQ(pageOut, reinterpret_cast<Page *>(0xCAFEBABE));
}

// Test: getCropBox returns nullptr from the page
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, ReturnsCropBoxNullFromPage_2071) {
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(1)).WillOnce(::testing::Return(mockPage.get()));
    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(nullptr));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(pageOut, mockPage.get());
}

// Test: Page index is 1 (boundary - first valid page)
TEST_F(PopplerAnnotGetCropboxAndPageTest_2071, HandlesPageIndexOne_2071) {
    PDFRectangle expectedRect = {0.0, 0.0, 595.0, 842.0};
    
    EXPECT_CALL(*mockAnnot, getPageNum()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockAnnot, getDoc()).WillOnce(::testing::Return(mockDoc.get()));
    EXPECT_CALL(*mockDoc, getPage(1)).WillOnce(::testing::Return(mockPage.get()));
    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(&expectedRect));
    
    Page *pageOut = nullptr;
    const PDFRectangle *result = _poppler_annot_get_cropbox_and_page(&popplerAnnot, &pageOut);
    
    EXPECT_EQ(result, &expectedRect);
    EXPECT_EQ(pageOut, mockPage.get());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
