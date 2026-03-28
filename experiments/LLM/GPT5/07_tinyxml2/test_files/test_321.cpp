#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// A derived class to expose PushDeclaration for verification
class XMLPrinterTestable : public XMLPrinter {
public:
    explicit XMLPrinterTestable() : XMLPrinter(nullptr, false, 0, EscapeAposCharsInAttributes::Yes) {}

    std::string lastDeclaration;

    void PushDeclaration(const char* value) override {
        lastDeclaration = value ? value : "";
        XMLPrinter::PushDeclaration(value);
    }
};

class XMLPrinter_321 : public ::testing::Test {
protected:
    XMLPrinterTestable printer;
};

// Test normal operation: Visit should call PushDeclaration and return true
TEST_F(XMLPrinter_321, VisitCallsPushDeclaration_ReturnsTrue_321) {
    XMLDocument doc;
    XMLDeclaration declaration(&doc);

    bool result = printer.Visit(declaration);

    // The observable effect: Visit returns true
    EXPECT_TRUE(result);

    // The observable effect: PushDeclaration should have been called
    EXPECT_EQ(printer.lastDeclaration, declaration.Value());
}

// Test boundary condition: empty declaration value
TEST_F(XMLPrinter_321, VisitWithEmptyDeclaration_ReturnsTrue_321) {
    XMLDocument doc;
    XMLDeclaration declaration(&doc);
    declaration.SetValue("", true); // empty string

    bool result = printer.Visit(declaration);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastDeclaration, "");
}

// Test boundary condition: very long declaration value
TEST_F(XMLPrinter_321, VisitWithLongDeclaration_ReturnsTrue_321) {
    XMLDocument doc;
    XMLDeclaration declaration(&doc);

    std::string longValue(1024, 'A'); // 1 KB of 'A'
    declaration.SetValue(longValue.c_str(), true);

    bool result = printer.Visit(declaration);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastDeclaration, longValue);
}

// Test exceptional case: null declaration value (if allowed)
TEST_F(XMLPrinter_321, VisitWithNullDeclarationValue_ReturnsTrue_321) {
    XMLDocument doc;
    XMLDeclaration declaration(&doc);

    declaration.SetValue(nullptr, true); // explicitly null

    bool result = printer.Visit(declaration);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastDeclaration, "");
}
