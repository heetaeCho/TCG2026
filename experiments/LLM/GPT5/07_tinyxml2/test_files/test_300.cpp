// TEST_ID: 300
// File: test_xmlprinter_pushattribute_uint64_300.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>

#include "TestProjects/tinyxml2/tinyxml2.h"

// These tests treat tinyxml2::XMLPrinter as a black box and verify only
// observable behavior via public APIs (CStr/CStrSize) and equivalence
// between overloads (uint64_t vs const char*).

namespace {

using namespace tinyxml2;

// Construct XMLPrinter in a way that is resilient to constructor signature
// differences (some tinyxml2 versions add extra params and/or defaults).
template <typename... Args>
constexpr bool CanConstructPrinter() {
    return std::is_constructible<XMLPrinter, Args...>::value;
}

static XMLPrinter MakePrinter_300(FILE* fp = nullptr, bool compact = false, int depth = 0) {
    if constexpr (CanConstructPrinter<FILE*>()) {
        (void)compact;
        (void)depth;
        return XMLPrinter(fp);
    } else if constexpr (CanConstructPrinter<FILE*, bool>()) {
        (void)depth;
        return XMLPrinter(fp, compact);
    } else if constexpr (CanConstructPrinter<FILE*, bool, int>()) {
        return XMLPrinter(fp, compact, depth);
    } else if constexpr (CanConstructPrinter<FILE*, bool, int, EscapeAposCharsInAttributes>()) {
        // If this signature is required, use the "zero" enum value without assuming meaning.
        return XMLPrinter(fp, compact, depth, static_cast<EscapeAposCharsInAttributes>(0));
    } else {
        // If none match, the build environment's tinyxml2.h differs from the provided snippet.
        // Force a clear compile-time error.
        static_assert(CanConstructPrinter<FILE*, bool, int, EscapeAposCharsInAttributes>(),
                      "No compatible XMLPrinter constructor found for this build.");
        return XMLPrinter(fp, compact, depth, static_cast<EscapeAposCharsInAttributes>(0));
    }
}

static std::string PrinterOutput_300(XMLPrinter& p) {
    const char* s = p.CStr();
    return s ? std::string(s) : std::string();
}

static void BuildSingleElementWithAttr_300(XMLPrinter& p,
                                           const char* elemName,
                                           const char* attrName,
                                           uint64_t value) {
    // Use only public interface; do not assume exact formatting beyond being stable for equivalence tests.
    p.OpenElement(elemName, /*compactMode*/ false);
    p.PushAttribute(attrName, value);
    p.CloseElement(/*compactMode*/ false);
}

static void BuildSingleElementWithAttrStr_300(XMLPrinter& p,
                                              const char* elemName,
                                              const char* attrName,
                                              const char* valueStr) {
    p.OpenElement(elemName, /*compactMode*/ false);
    p.PushAttribute(attrName, valueStr);
    p.CloseElement(/*compactMode*/ false);
}

}  // namespace

// Normal operation: uint64 overload produces same observable output as
// explicitly converting via XMLUtil::ToStr and calling const char* overload.
TEST(XMLPrinterPushAttributeUint64Test_300, MatchesCStringOverload_ForZero_300) {
    XMLPrinter pNum = MakePrinter_300(nullptr, false, 0);
    XMLPrinter pStr = MakePrinter_300(nullptr, false, 0);

    char buf[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    tinyxml2::XMLUtil::ToStr(static_cast<uint64_t>(0), buf, tinyxml2::XMLPrinter::BUF_SIZE);

    BuildSingleElementWithAttr_300(pNum, "root", "v", static_cast<uint64_t>(0));
    BuildSingleElementWithAttrStr_300(pStr, "root", "v", buf);

    EXPECT_EQ(PrinterOutput_300(pNum), PrinterOutput_300(pStr));
}

TEST(XMLPrinterPushAttributeUint64Test_300, MatchesCStringOverload_ForOne_300) {
    XMLPrinter pNum = MakePrinter_300(nullptr, false, 0);
    XMLPrinter pStr = MakePrinter_300(nullptr, false, 0);

    char buf[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    tinyxml2::XMLUtil::ToStr(static_cast<uint64_t>(1), buf, tinyxml2::XMLPrinter::BUF_SIZE);

    BuildSingleElementWithAttr_300(pNum, "root", "v", static_cast<uint64_t>(1));
    BuildSingleElementWithAttrStr_300(pStr, "root", "v", buf);

    EXPECT_EQ(PrinterOutput_300(pNum), PrinterOutput_300(pStr));
}

TEST(XMLPrinterPushAttributeUint64Test_300, MatchesCStringOverload_ForLargeValue_300) {
    XMLPrinter pNum = MakePrinter_300(nullptr, false, 0);
    XMLPrinter pStr = MakePrinter_300(nullptr, false, 0);

    const uint64_t value = 1844674407370955161ULL;  // large but not max
    char buf[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, tinyxml2::XMLPrinter::BUF_SIZE);

    BuildSingleElementWithAttr_300(pNum, "root", "v", value);
    BuildSingleElementWithAttrStr_300(pStr, "root", "v", buf);

    EXPECT_EQ(PrinterOutput_300(pNum), PrinterOutput_300(pStr));
}

// Boundary condition: maximum uint64_t.
TEST(XMLPrinterPushAttributeUint64Test_300, MatchesCStringOverload_ForMaxUint64_300) {
    XMLPrinter pNum = MakePrinter_300(nullptr, false, 0);
    XMLPrinter pStr = MakePrinter_300(nullptr, false, 0);

    const uint64_t value = std::numeric_limits<uint64_t>::max();
    char buf[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, tinyxml2::XMLPrinter::BUF_SIZE);

    BuildSingleElementWithAttr_300(pNum, "root", "v", value);
    BuildSingleElementWithAttrStr_300(pStr, "root", "v", buf);

    EXPECT_EQ(PrinterOutput_300(pNum), PrinterOutput_300(pStr));
}

// Observable consistency: CStrSize should match strlen(CStr()) for output-producing usage.
TEST(XMLPrinterPushAttributeUint64Test_300, CStrSizeMatchesStrlenAfterPushAttribute_300) {
    XMLPrinter p = MakePrinter_300(nullptr, false, 0);

    BuildSingleElementWithAttr_300(p, "root", "v", static_cast<uint64_t>(42));

    const char* s = p.CStr();
    ASSERT_NE(s, nullptr);

    EXPECT_EQ(p.CStrSize(), std::strlen(s));
}

// Error-ish / boundary usage (observable): pushing multiple uint64 attributes should be stable
// and produce the same output as pushing the corresponding string attributes.
TEST(XMLPrinterPushAttributeUint64Test_300, MultipleAttributes_MatchCStringOverload_300) {
    XMLPrinter pNum = MakePrinter_300(nullptr, false, 0);
    XMLPrinter pStr = MakePrinter_300(nullptr, false, 0);

    const uint64_t a = 0;
    const uint64_t b = 999;
    const uint64_t c = std::numeric_limits<uint64_t>::max();

    char bufA[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    char bufB[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    char bufC[tinyxml2::XMLPrinter::BUF_SIZE] = {};
    tinyxml2::XMLUtil::ToStr(a, bufA, tinyxml2::XMLPrinter::BUF_SIZE);
    tinyxml2::XMLUtil::ToStr(b, bufB, tinyxml2::XMLPrinter::BUF_SIZE);
    tinyxml2::XMLUtil::ToStr(c, bufC, tinyxml2::XMLPrinter::BUF_SIZE);

    pNum.OpenElement("root", /*compactMode*/ false);
    pNum.PushAttribute("a", a);
    pNum.PushAttribute("b", b);
    pNum.PushAttribute("c", c);
    pNum.CloseElement(/*compactMode*/ false);

    pStr.OpenElement("root", /*compactMode*/ false);
    pStr.PushAttribute("a", bufA);
    pStr.PushAttribute("b", bufB);
    pStr.PushAttribute("c", bufC);
    pStr.CloseElement(/*compactMode*/ false);

    EXPECT_EQ(PrinterOutput_300(pNum), PrinterOutput_300(pStr));
}
