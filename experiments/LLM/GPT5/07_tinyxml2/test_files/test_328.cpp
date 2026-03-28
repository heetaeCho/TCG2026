// File: ./TestProjects/tinyxml2/test_xmlprinter_constructor_328.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

using ::tinyxml2::XMLPrinter;

class XMLPrinterConstructorTest_328 : public ::testing::Test {
protected:
	static std::string ToString(const XMLPrinter& p) {
		const char* s = p.CStr();
		return s ? std::string(s) : std::string();
	}
};

TEST_F(XMLPrinterConstructorTest_328, InitialBufferIsValidEmptyCStr_328) {
	XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0,
	                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	const char* s = printer.CStr();
	ASSERT_NE(s, nullptr);
	EXPECT_STREQ(s, "");                 // constructor pushes a null terminator
	EXPECT_EQ(std::strlen(s), printer.CStrSize());
}

TEST_F(XMLPrinterConstructorTest_328, ClearBufferResetsToEmpty_328) {
	XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0,
	                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	printer.OpenElement("root", /*compactMode=*/false);
	printer.PushText("x", /*cdata=*/false);
	printer.CloseElement(/*compactMode=*/false);

	ASSERT_NE(printer.CStr(), nullptr);
	EXPECT_GT(std::strlen(printer.CStr()), 0u);

	printer.ClearBuffer(true);
	EXPECT_STREQ(printer.CStr(), "");
	EXPECT_EQ(printer.CStrSize(), 0u);
}

TEST_F(XMLPrinterConstructorTest_328, EscapesRestrictedEntitiesInText_328) {
	XMLPrinter printer(nullptr, /*compact=*/true, /*depth=*/0,
	                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	printer.OpenElement("root", /*compactMode=*/true);
	printer.PushText("&<>", /*cdata=*/false);
	printer.CloseElement(/*compactMode=*/true);

	const std::string out = ToString(printer);
	// These are the restricted entities configured by the constructor.
	EXPECT_NE(out.find("&amp;"), std::string::npos);
	EXPECT_NE(out.find("&lt;"), std::string::npos);
	EXPECT_NE(out.find("&gt;"), std::string::npos);
}

TEST_F(XMLPrinterConstructorTest_328, EscapeAposInAttributesWhenEnabled_328) {
	XMLPrinter printer(nullptr, /*compact=*/true, /*depth=*/0,
	                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	printer.OpenElement("a", /*compactMode=*/true);
	printer.PushAttribute("x", "'");
	printer.CloseElement(/*compactMode=*/true);

	const std::string out = ToString(printer);
	EXPECT_NE(out.find("x="), std::string::npos);
	EXPECT_NE(out.find("&apos;"), std::string::npos);
}

TEST_F(XMLPrinterConstructorTest_328, DoesNotEscapeAposInAttributesWhenDisabled_328) {
	XMLPrinter printer(nullptr, /*compact=*/true, /*depth=*/0,
	                   XMLPrinter::DONT_ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	printer.OpenElement("a", /*compactMode=*/true);
	printer.PushAttribute("x", "'");
	printer.CloseElement(/*compactMode=*/true);

	const std::string out = ToString(printer);
	EXPECT_NE(out.find("x="), std::string::npos);
	// In this mode, constructor does not enable escaping for SINGLE_QUOTE in attributes.
	EXPECT_EQ(out.find("&apos;"), std::string::npos);
	EXPECT_NE(out.find("'"), std::string::npos);
}

TEST_F(XMLPrinterConstructorTest_328, CanWriteToFILEPointer_328) {
	FILE* fp = std::tmpfile();
	ASSERT_NE(fp, nullptr);

	{
		XMLPrinter printer(fp, /*compact=*/true, /*depth=*/0,
		                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);
		printer.OpenElement("root", /*compactMode=*/true);
		printer.PushAttribute("k", "v");
		printer.PushText("t", /*cdata=*/false);
		printer.CloseElement(/*compactMode=*/true);
	}

	std::fflush(fp);
	std::rewind(fp);

	char buf[4096];
	const size_t n = std::fread(buf, 1, sizeof(buf) - 1, fp);
	buf[n] = '\0';
	std::fclose(fp);

	std::string fileOut(buf);
	EXPECT_NE(fileOut.find("<root"), std::string::npos);
	EXPECT_NE(fileOut.find("k="), std::string::npos);
	EXPECT_NE(fileOut.find("v"), std::string::npos);
	EXPECT_NE(fileOut.find("t"), std::string::npos);
}

TEST_F(XMLPrinterConstructorTest_328, NegativeDepthDoesNotBreakBasicPrinting_328) {
	XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/-1,
	                   XMLPrinter::ESCAPE_APOS_CHARS_IN_ATTRIBUTES);

	printer.OpenElement("root", /*compactMode=*/false);
	printer.OpenElement("child", /*compactMode=*/false);
	printer.CloseElement(/*compactMode=*/false);
	printer.CloseElement(/*compactMode=*/false);

	const char* s = printer.CStr();
	ASSERT_NE(s, nullptr);
	EXPECT_NE(std::strlen(s), 0u);
	// Still a well-formed-ish output containing tags we asked for.
	std::string out(s);
	EXPECT_NE(out.find("root"), std::string::npos);
	EXPECT_NE(out.find("child"), std::string::npos);
}

}  // namespace
