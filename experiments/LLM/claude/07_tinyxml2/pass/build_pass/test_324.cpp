#include <gtest/gtest.h>
#include <cstring>

// Minimal standalone version of the class under test based on the partial code provided
class XMLPrinterHTML5 {
public:
    virtual bool isVoidElement(const char *name) {
        static const char *list[] = {
            "area", "base", "br", "col", "command", "embed", "hr", "img",
            "input", "keygen", "link", "meta", "param", "source", "track",
            "wbr", NULL
        };
        for (const char **p = list; *p; ++p) {
            if (!strcasecmp(name, *p)) {
                return true;
            }
        }
        return false;
    }
    virtual ~XMLPrinterHTML5() = default;
};

class XMLPrinterHTML5Test_324 : public ::testing::Test {
protected:
    XMLPrinterHTML5 printer;
};

// ============================================================
// Normal operation: Test each void element returns true
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, AreaIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("area"));
}

TEST_F(XMLPrinterHTML5Test_324, BaseIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("base"));
}

TEST_F(XMLPrinterHTML5Test_324, BrIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("br"));
}

TEST_F(XMLPrinterHTML5Test_324, ColIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("col"));
}

TEST_F(XMLPrinterHTML5Test_324, CommandIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("command"));
}

TEST_F(XMLPrinterHTML5Test_324, EmbedIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("embed"));
}

TEST_F(XMLPrinterHTML5Test_324, HrIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("hr"));
}

TEST_F(XMLPrinterHTML5Test_324, ImgIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("img"));
}

TEST_F(XMLPrinterHTML5Test_324, InputIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("input"));
}

TEST_F(XMLPrinterHTML5Test_324, KeygenIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("keygen"));
}

TEST_F(XMLPrinterHTML5Test_324, LinkIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("link"));
}

TEST_F(XMLPrinterHTML5Test_324, MetaIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("meta"));
}

TEST_F(XMLPrinterHTML5Test_324, ParamIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("param"));
}

TEST_F(XMLPrinterHTML5Test_324, SourceIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("source"));
}

TEST_F(XMLPrinterHTML5Test_324, TrackIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("track"));
}

TEST_F(XMLPrinterHTML5Test_324, WbrIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("wbr"));
}

// ============================================================
// Case insensitivity tests
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, UpperCaseBrIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("BR"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseImgIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("Img"));
}

TEST_F(XMLPrinterHTML5Test_324, UpperCaseAreaIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("AREA"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseInputIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("InPuT"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseMetaIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("META"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseLinkIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("LiNk"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseSourceIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("SOURCE"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseEmbedIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("eMbEd"));
}

TEST_F(XMLPrinterHTML5Test_324, MixedCaseWbrIsVoidElement_324) {
    EXPECT_TRUE(printer.isVoidElement("WBR"));
}

// ============================================================
// Non-void elements return false
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, DivIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("div"));
}

TEST_F(XMLPrinterHTML5Test_324, SpanIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("span"));
}

TEST_F(XMLPrinterHTML5Test_324, PIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("p"));
}

TEST_F(XMLPrinterHTML5Test_324, AIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("a"));
}

TEST_F(XMLPrinterHTML5Test_324, ScriptIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("script"));
}

TEST_F(XMLPrinterHTML5Test_324, StyleIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("style"));
}

TEST_F(XMLPrinterHTML5Test_324, TableIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("table"));
}

TEST_F(XMLPrinterHTML5Test_324, BodyIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("body"));
}

TEST_F(XMLPrinterHTML5Test_324, HtmlIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("html"));
}

TEST_F(XMLPrinterHTML5Test_324, HeadIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("head"));
}

TEST_F(XMLPrinterHTML5Test_324, TitleIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("title"));
}

TEST_F(XMLPrinterHTML5Test_324, FormIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("form"));
}

TEST_F(XMLPrinterHTML5Test_324, H1IsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("h1"));
}

TEST_F(XMLPrinterHTML5Test_324, UlIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("ul"));
}

TEST_F(XMLPrinterHTML5Test_324, LiIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("li"));
}

// ============================================================
// Boundary conditions
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, EmptyStringIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement(""));
}

TEST_F(XMLPrinterHTML5Test_324, SingleCharNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("x"));
}

TEST_F(XMLPrinterHTML5Test_324, VeryLongStringIsNotVoidElement_324) {
    std::string longName(1000, 'a');
    EXPECT_FALSE(printer.isVoidElement(longName.c_str()));
}

TEST_F(XMLPrinterHTML5Test_324, SubstringOfVoidElementIsNotVoid_324) {
    // "are" is a substring of "area" but not a void element
    EXPECT_FALSE(printer.isVoidElement("are"));
}

TEST_F(XMLPrinterHTML5Test_324, SuperstringOfVoidElementIsNotVoid_324) {
    // "areas" contains "area" but is not a void element
    EXPECT_FALSE(printer.isVoidElement("areas"));
}

TEST_F(XMLPrinterHTML5Test_324, BrWithTrailingSpaceIsNotVoid_324) {
    EXPECT_FALSE(printer.isVoidElement("br "));
}

TEST_F(XMLPrinterHTML5Test_324, BrWithLeadingSpaceIsNotVoid_324) {
    EXPECT_FALSE(printer.isVoidElement(" br"));
}

TEST_F(XMLPrinterHTML5Test_324, NullTerminatorOnlyIsNotVoid_324) {
    // Just testing an empty C-string
    const char empty[] = "";
    EXPECT_FALSE(printer.isVoidElement(empty));
}

// ============================================================
// Similar names that are not void elements
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, ImagesIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("images"));
}

TEST_F(XMLPrinterHTML5Test_324, InputsIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("inputs"));
}

TEST_F(XMLPrinterHTML5Test_324, LinksIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("links"));
}

TEST_F(XMLPrinterHTML5Test_324, MetasIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("metas"));
}

TEST_F(XMLPrinterHTML5Test_324, CommandsIsNotVoidElement_324) {
    EXPECT_FALSE(printer.isVoidElement("commands"));
}

// ============================================================
// All uppercase for each void element
// ============================================================

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseBase_324) {
    EXPECT_TRUE(printer.isVoidElement("BASE"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseCol_324) {
    EXPECT_TRUE(printer.isVoidElement("COL"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseCommand_324) {
    EXPECT_TRUE(printer.isVoidElement("COMMAND"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseHr_324) {
    EXPECT_TRUE(printer.isVoidElement("HR"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseKeygen_324) {
    EXPECT_TRUE(printer.isVoidElement("KEYGEN"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseParam_324) {
    EXPECT_TRUE(printer.isVoidElement("PARAM"));
}

TEST_F(XMLPrinterHTML5Test_324, AllUpperCaseTrack_324) {
    EXPECT_TRUE(printer.isVoidElement("TRACK"));
}
