#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock class for XMLElement, since we only need to pass it to VisitExit
class MockXMLElement : public XMLElement {
public:
    MockXMLElement(XMLDocument* doc) : XMLElement(doc) {}
};

// Mock XMLPrinter to spy on CloseElement calls
class TestableXMLPrinter : public XMLPrinter {
public:
    using XMLPrinter::XMLPrinter;

    bool closeElementCalled = false;
    bool lastCompactMode = false;

    void CloseElement(bool compactMode) override {
        closeElementCalled = true;
        lastCompactMode = compactMode;
        XMLPrinter::CloseElement(compactMode); // optional: call base
    }

    // Expose CompactMode for testing if needed
    bool CompactModePublic(const XMLElement& element) {
        return CompactMode(element);
    }
};

TEST(XMLPrinter_318, VisitExitReturnsTrue_318) {
    XMLDocument doc;
    MockXMLElement elem(&doc);
    TestableXMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::NO);

    bool result = printer.VisitExit(elem);

    EXPECT_TRUE(result) << "VisitExit should always return true";
}

TEST(XMLPrinter_318, VisitExitCallsCloseElement_318) {
    XMLDocument doc;
    MockXMLElement elem(&doc);
    TestableXMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::NO);

    printer.VisitExit(elem);

    EXPECT_TRUE(printer.closeElementCalled) << "VisitExit should call CloseElement";
}

TEST(XMLPrinter_318, VisitExitPassesCorrectCompactMode_318) {
    XMLDocument doc;
    MockXMLElement elem(&doc);

    // Test with compact mode = true
    TestableXMLPrinter printerTrue(nullptr, true, 0, EscapeAposCharsInAttributes::NO);
    printerTrue.VisitExit(elem);
    EXPECT_EQ(printerTrue.lastCompactMode, printerTrue.CompactModePublic(elem));

    // Test with compact mode = false
    TestableXMLPrinter printerFalse(nullptr, false, 0, EscapeAposCharsInAttributes::NO);
    printerFalse.VisitExit(elem);
    EXPECT_EQ(printerFalse.lastCompactMode, printerFalse.CompactModePublic(elem));
}

// Boundary case: passing a default-constructed element (if allowed)
TEST(XMLPrinter_318, VisitExitWithDefaultElement_318) {
    XMLDocument doc;
    XMLElement elem(&doc); // default element
    TestableXMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::NO);

    bool result = printer.VisitExit(elem);

    EXPECT_TRUE(result);
    EXPECT_TRUE(printer.closeElementCalled);
}

// Exceptional behavior: if VisitExit can be called with nullptr element pointer
// (only if interface allowed pointers; in this case, reference, so no nullptr possible)
// This test is just illustrative; the compiler prevents nullptr reference
// TEST(XMLPrinter_318, VisitExitWithNullElement_318) {
//     TestableXMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::NO);
//     EXPECT_DEATH(printer.VisitExit(*static_cast<XMLElement*>(nullptr)), ".*");
// }
