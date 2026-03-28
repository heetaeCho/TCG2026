#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal stubs for dependencies
// We need to provide enough structure to compile against the interface

// Minimal stub for Annot
class Annot {
public:
    virtual ~Annot() = default;
};

// Minimal stub for Page
class Page {
public:
    virtual ~Page() = default;
};

// Since HtmlOutputDev uses 'override', it must inherit from some base class.
// We create a minimal base class that declares the virtual method.
class OutputDev {
public:
    virtual ~OutputDev() = default;
    virtual bool checkPageSlice(Page *p, double hDPI, double vDPI, int rotate,
                                bool useMediaBox, bool crop,
                                int sliceX, int sliceY, int sliceW, int sliceH,
                                bool printing,
                                bool (*abortCheckCbk)(void *data) = nullptr,
                                void *abortCheckCbkData = nullptr,
                                bool (*annotDisplayDecideCbk)(Annot *annot, void *user_data) = nullptr,
                                void *annotDisplayDecideCbkData = nullptr) {
        return false;
    }
};

// Recreate HtmlOutputDev based on the provided partial code
class HtmlOutputDev : public OutputDev {
public:
    Page *docPage = nullptr;

    bool checkPageSlice(Page *p, double /*hDPI*/, double /*vDPI*/, int /*rotate*/,
                        bool /*useMediaBox*/, bool /*crop*/,
                        int /*sliceX*/, int /*sliceY*/, int /*sliceW*/, int /*sliceH*/,
                        bool /*printing*/,
                        bool (*/*abortCheckCbk*/)(void *data) = nullptr,
                        void * /*abortCheckCbkData*/ = nullptr,
                        bool (*/*annotDisplayDecideCbk*/)(Annot *annot, void *user_data) = nullptr,
                        void * /*annotDisplayDecideCbkData*/ = nullptr) override {
        docPage = p;
        return true;
    }
};

// Test fixture
class HtmlOutputDevTest_2710 : public ::testing::Test {
protected:
    HtmlOutputDev dev;
    Page testPage;
};

// Test: checkPageSlice returns true with valid Page pointer
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceReturnsTrueWithValidPage_2710) {
    bool result = dev.checkPageSlice(&testPage, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test: checkPageSlice sets docPage to the provided Page pointer
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceSetsDocPage_2710) {
    EXPECT_EQ(dev.docPage, nullptr);
    dev.checkPageSlice(&testPage, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice returns true even with nullptr Page
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceReturnsTrueWithNullPage_2710) {
    bool result = dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test: checkPageSlice sets docPage to nullptr when nullptr is passed
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceSetsDocPageToNullptr_2710) {
    dev.docPage = &testPage;
    dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_EQ(dev.docPage, nullptr);
}

// Test: checkPageSlice with default optional parameters (callbacks are nullptr)
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceWithDefaultCallbacks_2710) {
    bool result = dev.checkPageSlice(&testPage, 300.0, 300.0, 90, true, true, 10, 20, 500, 600, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice with explicit callback parameters
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceWithExplicitCallbacks_2710) {
    auto abortCbk = [](void *) -> bool { return false; };
    auto annotCbk = [](Annot *, void *) -> bool { return true; };

    int userData = 42;
    bool result = dev.checkPageSlice(&testPage, 150.0, 150.0, 180, false, true,
                                     0, 0, 1000, 1000, false,
                                     abortCbk, &userData,
                                     annotCbk, &userData);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice with zero DPI values (boundary)
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceWithZeroDPI_2710) {
    bool result = dev.checkPageSlice(&testPage, 0.0, 0.0, 0, false, false, 0, 0, 0, 0, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice with negative slice values (boundary)
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceWithNegativeSliceValues_2710) {
    bool result = dev.checkPageSlice(&testPage, 72.0, 72.0, 0, false, false, -10, -20, -100, -200, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice with large DPI values (boundary)
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceWithLargeDPIValues_2710) {
    bool result = dev.checkPageSlice(&testPage, 1e10, 1e10, 360, true, true,
                                     0, 0, 100000, 100000, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: Calling checkPageSlice multiple times updates docPage each time
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceMultipleCallsUpdateDocPage_2710) {
    Page page1, page2, page3;

    dev.checkPageSlice(&page1, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_EQ(dev.docPage, &page1);

    dev.checkPageSlice(&page2, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_EQ(dev.docPage, &page2);

    dev.checkPageSlice(&page3, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_EQ(dev.docPage, &page3);
}

// Test: checkPageSlice always returns true regardless of parameters
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceAlwaysReturnsTrue_2710) {
    // Various combinations of parameters
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 0.0, 0.0, 0, false, false, 0, 0, 0, 0, false));
    EXPECT_TRUE(dev.checkPageSlice(&testPage, -1.0, -1.0, -90, true, true, -1, -1, -1, -1, true));
    EXPECT_TRUE(dev.checkPageSlice(&testPage, 999999.0, 999999.0, 270, false, true, 
                                   INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, false));
}

// Test: Polymorphic behavior through base class pointer
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceViaBasePointer_2710) {
    OutputDev *basePtr = &dev;
    bool result = basePtr->checkPageSlice(&testPage, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: Initial state of docPage before any call
TEST_F(HtmlOutputDevTest_2710, InitialDocPageIsNullptr_2710) {
    EXPECT_EQ(dev.docPage, nullptr);
}

// Test: checkPageSlice with all boolean flags true
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceAllBooleanFlagsTrue_2710) {
    bool result = dev.checkPageSlice(&testPage, 72.0, 72.0, 0, true, true, 0, 0, 100, 100, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}

// Test: checkPageSlice with all boolean flags false
TEST_F(HtmlOutputDevTest_2710, CheckPageSliceAllBooleanFlagsFalse_2710) {
    bool result = dev.checkPageSlice(&testPage, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(dev.docPage, &testPage);
}
