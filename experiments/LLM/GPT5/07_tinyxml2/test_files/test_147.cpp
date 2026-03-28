// File: ./TestProjects/tinyxml2/tests/XMLPrinter_VisitExit_147_test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLPrinterVisitExitTest_147 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLPrinterVisitExitTest_147, ReturnsTrueForDocument_147) {
    XMLPrinter printer;
    EXPECT_TRUE(printer.VisitExit(doc_));
}

TEST_F(XMLPrinterVisitExitTest_147, DoesNotThrow_147) {
    XMLPrinter printer;
    EXPECT_NO_THROW({
        (void)printer.VisitExit(doc_);
    });
}

TEST_F(XMLPrinterVisitExitTest_147, VirtualDispatchThroughBasePointer_147) {
    // XMLPrinter::VisitExit(const XMLDocument&) is declared "override", so it should dispatch
    // correctly when called through the base type in the real library (typically XMLVisitor).
    XMLPrinter printer;

    XMLVisitor* visitor = &printer;
    ASSERT_NE(visitor, nullptr);

    EXPECT_TRUE(visitor->VisitExit(doc_));
}

TEST_F(XMLPrinterVisitExitTest_147, DerivedOverrideIsCalledPolymorphically_147) {
    struct DerivedPrinter : public XMLPrinter {
        int calls = 0;
        bool VisitExit(const XMLDocument& doc) override {
            (void)doc;
            ++calls;
            return false;
        }
    };

    DerivedPrinter derived;
    XMLVisitor* visitor = &derived;

    EXPECT_FALSE(visitor->VisitExit(doc_));
    EXPECT_EQ(derived.calls, 1);
}

}  // namespace tinyxml2
