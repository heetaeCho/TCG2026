#include <gtest/gtest.h>
#include <tinyxml2.h>
#include <sstream>
#include <memory>

using namespace tinyxml2;

// Helper to capture output to a string instead of a FILE*
class StringPrinter : public XMLPrinter {
public:
    StringPrinter() : XMLPrinter(nullptr, false, 0, EscapeAposCharsInAttributes::NO) {}

    std::string GetString() const { return buffer.str(); }

protected:
    void Putc(char ch) override { buffer << ch; }
    void Write(const char* data, size_t size) override { buffer.write(data, size); }

private:
    std::ostringstream buffer;
};

// Test fixture for XMLPrinter PushAttribute tests
class XMLPrinterTest_296 : public ::testing::Test {
protected:
    void SetUp() override {
        printer = std::make_unique<StringPrinter>();
        // Open an element first, as PushAttribute requires _elementJustOpened
        printer->OpenElement("TestElement", false);
    }

    std::unique_ptr<StringPrinter> printer;
};

// Normal operation: push a simple attribute
TEST_F(XMLPrinterTest_296, PushAttribute_SimpleString_296) {
    printer->PushAttribute("attr", "value");
    std::string output = printer->GetString();
    EXPECT_NE(output.find("attr=\"value\""), std::string::npos);
}

// Boundary: empty attribute name and value
TEST_F(XMLPrinterTest_296, PushAttribute_EmptyNameAndValue_296) {
    printer->PushAttribute("", "");
    std::string output = printer->GetString();
    EXPECT_NE(output.find("=\"\""), std::string::npos);
}

// Boundary: very long attribute value
TEST_F(XMLPrinterTest_296, PushAttribute_LongValue_296) {
    std::string longValue(1000, 'x');
    printer->PushAttribute("longAttr", longValue.c_str());
    std::string output = printer->GetString();
    EXPECT_NE(output.find(longValue), std::string::npos);
}

// Exceptional: null name pointer
TEST_F(XMLPrinterTest_296, PushAttribute_NullName_296) {
    // Behavior undefined in code, but ensure no crash
    EXPECT_NO_THROW(printer->PushAttribute(nullptr, "value"));
}

// Exceptional: null value pointer
TEST_F(XMLPrinterTest_296, PushAttribute_NullValue_296) {
    // Behavior undefined in code, but ensure no crash
    EXPECT_NO_THROW(printer->PushAttribute("attr", nullptr));
}

// Verify multiple attributes chaining
TEST_F(XMLPrinterTest_296, PushAttribute_MultipleAttributes_296) {
    printer->PushAttribute("a", "1");
    printer->PushAttribute("b", "2");
    std::string output = printer->GetString();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
}

// Verify space separation after PushAttribute
TEST_F(XMLPrinterTest_296, PushAttribute_SpacesBetweenAttributes_296) {
    printer->PushAttribute("first", "one");
    printer->PushAttribute("second", "two");
    std::string output = printer->GetString();
    // Expect space before second attribute
    EXPECT_NE(output.find("first=\"one\" second=\"two\""), std::string::npos);
}
