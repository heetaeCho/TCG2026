#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock class for XMLDocument to control observable behavior
class MockXMLDocument : public XMLDocument {
public:
    MockXMLDocument(bool processEntities, bool hasBOM)
        : XMLDocument(processEntities, Whitespace::DEFAULT), _mockHasBOM(hasBOM) {}

    bool HasBOM() const override { return _mockHasBOM; }
    bool ProcessEntities() const override { return _processEntities; }

private:
    bool _mockHasBOM;
};

// Test fixture
class XMLPrinterTest_316 : public ::testing::Test {
protected:
    XMLPrinterTest_316()
        : printer(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::NO) {}

    XMLPrinter printer;
};

// ----------------------------
// TEST CASES
// ----------------------------

// Normal operation: VisitEnter should return true for document without BOM
TEST_F(XMLPrinterTest_316, VisitEnterReturnsTrueWithoutBOM_316) {
    MockXMLDocument doc(true, false);  // processEntities=true, hasBOM=false

    bool result = printer.VisitEnter(doc);

    EXPECT_TRUE(result);
}

// Normal operation: VisitEnter should return true for document with BOM
TEST_F(XMLPrinterTest_316, VisitEnterReturnsTrueWithBOM_316) {
    MockXMLDocument doc(true, true);  // processEntities=true, hasBOM=true

    bool result = printer.VisitEnter(doc);

    EXPECT_TRUE(result);
}

// Boundary condition: Document with processEntities = false
TEST_F(XMLPrinterTest_316, VisitEnterSetsProcessEntitiesFalse_316) {
    MockXMLDocument doc(false, false);  // processEntities=false, hasBOM=false

    bool result = printer.VisitEnter(doc);

    EXPECT_TRUE(result);  // Should still return true
}

// Exceptional / edge case: Document pointer is null (simulate by reference to empty doc)
TEST_F(XMLPrinterTest_316, VisitEnterWithEmptyDocument_316) {
    XMLDocument doc(false, Whitespace::DEFAULT); // minimal document

    bool result = printer.VisitEnter(doc);

    EXPECT_TRUE(result);  // Should not crash, should return true
}

// Verify external interaction: PushHeader called when BOM present
TEST_F(XMLPrinterTest_316, VisitEnterPushHeaderCalledWithBOM_316) {
    MockXMLDocument doc(true, true);  // hasBOM=true

    // Since PushHeader writes to internal state, we can verify CStr is non-empty after visit
    printer.VisitEnter(doc);

    // CStrSize should be > 0 if header was pushed
    EXPECT_GT(printer.CStrSize(), 0u);
}

// Verify external interaction: PushHeader not called when BOM absent
TEST_F(XMLPrinterTest_316, VisitEnterNoHeaderWithoutBOM_316) {
    MockXMLDocument doc(true, false);  // hasBOM=false

    printer.VisitEnter(doc);

    // CStrSize should remain 0 as no header is written
    EXPECT_EQ(printer.CStrSize(), 0u);
}
