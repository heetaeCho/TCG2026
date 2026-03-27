#include <gtest/gtest.h>

#include "tinyxml2.h"

#include "contrib/html5-printer.cpp"



using namespace tinyxml2;



class XMLDocumentTest_325 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLPrinter printer;

    XMLPrinterHTML5 html5_printer;



    XMLDocumentTest_325() : doc(false), printer(nullptr, true), html5_printer(nullptr, false) {}



    void SetUp() override {

        input = "<html><body><p style='a'></p><br/>&copy;<col a='1' b='2'/><div a='1'></div></body></html>";

        doc.Parse(input);

    }



    const char* input;

};



TEST_F(XMLDocumentTest_325, ParseValidXML_325) {

    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_325, ParseInvalidXML_325) {

    doc.Parse("invalid xml");

    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_325, PrintWithXMLPrinter_325) {

    printer.ClearBuffer();

    doc.Print(&printer);

    EXPECT_FALSE(std::string(printer.CStr()).empty());

}



TEST_F(XMLDocumentTest_325, PrintWithHTML5Printer_325) {

    html5_printer.ClearBuffer();

    doc.Print(&html5_printer);

    EXPECT_FALSE(std::string(html5_printer.CStr()).empty());

}



TEST_F(XMLDocumentTest_325, XMLPrinterOutputContainsInputTags_325) {

    printer.ClearBuffer();

    doc.Print(&printer);

    std::string output(printer.CStr());

    EXPECT_TRUE(output.find("<html>") != std::string::npos);

    EXPECT_TRUE(output.find("</html>") != std::string::npos);

}



TEST_F(XMLDocumentTest_325, HTML5PrinterOutputContainsInputTags_325) {

    html5_printer.ClearBuffer();

    doc.Print(&html5_printer);

    std::string output(html5_printer.CStr());

    EXPECT_TRUE(output.find("<html>") != std::string::npos);

    EXPECT_TRUE(output.find("</html>") != std::string::npos);

}



TEST_F(XMLDocumentTest_325, HTML5PrinterHandlesVoidElementsCorrectly_325) {

    html5_printer.ClearBuffer();

    doc.Print(&html5_printer);

    std::string output(html5_printer.CStr());

    EXPECT_TRUE(output.find("<br/>") != std::string::npos);

    EXPECT_TRUE(output.find("</br>") == std::string::npos);

}



TEST_F(XMLDocumentTest_325, XMLPrinterHandlesVoidElementsCorrectly_325) {

    printer.ClearBuffer();

    doc.Print(&printer);

    std::string output(printer.CStr());

    EXPECT_TRUE(output.find("<br/>") != std::string::npos || output.find("<br></br>") != std::string::npos);

}



TEST_F(XMLDocumentTest_325, XMLPrinterHandlesEntitiesCorrectly_325) {

    printer.ClearBuffer();

    doc.Print(&printer);

    std::string output(printer.CStr());

    EXPECT_TRUE(output.find("&copy;") != std::string::npos);

}



TEST_F(XMLDocumentTest_325, HTML5PrinterHandlesEntitiesCorrectly_325) {

    html5_printer.ClearBuffer();

    doc.Print(&html5_printer);

    std::string output(html5_printer.CStr());

    EXPECT_TRUE(output.find("&copy;") != std::string::npos);

}



TEST_F(XMLDocumentTest_325, XMLPrinterHandlesCompactMode_325) {

    XMLPrinter compact_printer(nullptr, true);

    compact_printer.ClearBuffer();

    doc.Print(&compact_printer);

    std::string output(compact_printer.CStr());

    EXPECT_EQ(output.find("\n"), std::string::npos); // No newlines in compact mode

}



TEST_F(XMLDocumentTest_325, HTML5PrinterHandlesCompactMode_325) {

    XMLPrinterHTML5 compact_html5_printer(nullptr, true);

    compact_html5_printer.ClearBuffer();

    doc.Print(&compact_html5_printer);

    std::string output(compact_html5_printer.CStr());

    EXPECT_EQ(output.find("\n"), std::string::npos); // No newlines in compact mode

}
