#include <gtest/gtest.h>
#include <string>
#include <regex>

// Include the enums from PDFDoc.h
enum PDFSubtype { subtypeNull = 0, subtypePDFA = 1, subtypePDFE = 2, subtypePDFUA = 3, subtypePDFVT = 4, subtypePDFX = 5, subtypeNone = 6 };
enum PDFSubtypePart { subtypePartNull = 0, subtypePart1 = 1, subtypePart2 = 2, subtypePart3 = 3, subtypePart4 = 4, subtypePart5 = 5, subtypePart6 = 6, subtypePart7 = 7, subtypePart8 = 8, subtypePartNone = 9 };

// Copy of the function under test since it's static in the .cc file
static PDFSubtypePart pdfPartFromString(PDFSubtype subtype, const std::string &pdfsubver)
{
    const std::regex regex("PDF/(?:A|X|VT|E|UA)-([[:digit:]])(?:[[:alpha:]]{1,2})?:?([[:digit:]]{4})?");
    std::smatch match;
    PDFSubtypePart subtypePart = subtypePartNone;

    if (std::regex_search(pdfsubver, match, regex)) {
        int date = 0;
        const int part = std::stoi(match.str(1));
        if (match[2].matched) {
            date = std::stoi(match.str(2));
        }

        switch (subtype) {
        case subtypePDFX:
            switch (part) {
            case 1:
                switch (date) {
                case 2001:
                default:
                    subtypePart = subtypePart1;
                    break;
                case 2003:
                    subtypePart = subtypePart4;
                    break;
                }
                break;
            case 2:
                subtypePart = subtypePart5;
                break;
            case 3:
                switch (date) {
                case 2002:
                default:
                    subtypePart = subtypePart3;
                    break;
                case 2003:
                    subtypePart = subtypePart6;
                    break;
                }
                break;
            case 4:
                subtypePart = subtypePart7;
                break;
            case 5:
                subtypePart = subtypePart8;
                break;
            }
            break;
        default:
            subtypePart = (PDFSubtypePart)part;
            break;
        }
    }

    return subtypePart;
}

// Test fixture
class PdfPartFromStringTest_1853 : public ::testing::Test {
protected:
};

// ==================== Tests for non-matching strings ====================

TEST_F(PdfPartFromStringTest_1853, EmptyString_ReturnsNone_1853)
{
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFA, ""));
}

TEST_F(PdfPartFromStringTest_1853, GarbageString_ReturnsNone_1853)
{
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFA, "some random string"));
}

TEST_F(PdfPartFromStringTest_1853, PartialMatch_NoDigit_ReturnsNone_1853)
{
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFA, "PDF/A-"));
}

TEST_F(PdfPartFromStringTest_1853, InvalidFormat_ReturnsNone_1853)
{
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFA, "PDF/Z-1"));
}

// ==================== Tests for PDF/A (non-PDFX, uses default cast) ====================

TEST_F(PdfPartFromStringTest_1853, PDFA_Part1_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFA, "PDF/A-1"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part1a_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFA, "PDF/A-1a"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part1b_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFA, "PDF/A-1b"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part2_ReturnsPart2_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypePDFA, "PDF/A-2a"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part2u_ReturnsPart2_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypePDFA, "PDF/A-2u"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part3_ReturnsPart3_1853)
{
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFA, "PDF/A-3a"));
}

TEST_F(PdfPartFromStringTest_1853, PDFA_Part3b_ReturnsPart3_1853)
{
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFA, "PDF/A-3b"));
}

// ==================== Tests for PDF/X (special mapping logic) ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_2001_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFX, "PDF/X-1a:2001"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_NoDate_ReturnsPart1_1853)
{
    // No date means date=0, which hits the default case -> subtypePart1
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFX, "PDF/X-1a"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_2003_ReturnsPart4_1853)
{
    EXPECT_EQ(subtypePart4, pdfPartFromString(subtypePDFX, "PDF/X-1a:2003"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part2_ReturnsPart5_1853)
{
    EXPECT_EQ(subtypePart5, pdfPartFromString(subtypePDFX, "PDF/X-2"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_2002_ReturnsPart3_1853)
{
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFX, "PDF/X-3:2002"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_NoDate_ReturnsPart3_1853)
{
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFX, "PDF/X-3"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_2003_ReturnsPart6_1853)
{
    EXPECT_EQ(subtypePart6, pdfPartFromString(subtypePDFX, "PDF/X-3:2003"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part4_ReturnsPart7_1853)
{
    EXPECT_EQ(subtypePart7, pdfPartFromString(subtypePDFX, "PDF/X-4"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part4p_ReturnsPart7_1853)
{
    EXPECT_EQ(subtypePart7, pdfPartFromString(subtypePDFX, "PDF/X-4p"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part5_ReturnsPart8_1853)
{
    EXPECT_EQ(subtypePart8, pdfPartFromString(subtypePDFX, "PDF/X-5g"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part5n_ReturnsPart8_1853)
{
    EXPECT_EQ(subtypePart8, pdfPartFromString(subtypePDFX, "PDF/X-5n"));
}

// ==================== Tests for PDF/E ====================

TEST_F(PdfPartFromStringTest_1853, PDFE_Part1_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFE, "PDF/E-1"));
}

TEST_F(PdfPartFromStringTest_1853, PDFE_Part2_ReturnsPart2_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypePDFE, "PDF/E-2"));
}

// ==================== Tests for PDF/UA ====================

TEST_F(PdfPartFromStringTest_1853, PDFUA_Part1_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFUA, "PDF/UA-1"));
}

TEST_F(PdfPartFromStringTest_1853, PDFUA_Part2_ReturnsPart2_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypePDFUA, "PDF/UA-2"));
}

// ==================== Tests for PDF/VT ====================

TEST_F(PdfPartFromStringTest_1853, PDFVT_Part1_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFVT, "PDF/VT-1"));
}

TEST_F(PdfPartFromStringTest_1853, PDFVT_Part2_ReturnsPart2_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypePDFVT, "PDF/VT-2"));
}

// ==================== Tests with subtypeNull and subtypeNone ====================

TEST_F(PdfPartFromStringTest_1853, SubtypeNull_UsesDefaultCast_1853)
{
    // subtypeNull is not subtypePDFX, so default branch: cast part to PDFSubtypePart
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypeNull, "PDF/A-1b"));
}

TEST_F(PdfPartFromStringTest_1853, SubtypeNone_UsesDefaultCast_1853)
{
    EXPECT_EQ(subtypePart2, pdfPartFromString(subtypeNone, "PDF/A-2a"));
}

// ==================== Boundary: PDFX with unknown part number ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part6_UnknownPart_ReturnsNone_1853)
{
    // Part 6 is not handled in the PDFX switch, so subtypePart stays as subtypePartNone
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFX, "PDF/X-6"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part9_UnknownPart_ReturnsNone_1853)
{
    EXPECT_EQ(subtypePartNone, pdfPartFromString(subtypePDFX, "PDF/X-9"));
}

// ==================== Boundary: PDFX Part1 with unusual date ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_UnknownDate_ReturnsPart1_1853)
{
    // Date 1999 hits the default in the inner switch -> subtypePart1
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFX, "PDF/X-1a:1999"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_UnknownDate_ReturnsPart3_1853)
{
    // Date 1999 hits default in the inner switch -> subtypePart3
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFX, "PDF/X-3:1999"));
}

// ==================== Tests with two-letter suffix ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part5pg_TwoLetterSuffix_ReturnsPart8_1853)
{
    EXPECT_EQ(subtypePart8, pdfPartFromString(subtypePDFX, "PDF/X-5pg"));
}

// ==================== String embedded in longer text ====================

TEST_F(PdfPartFromStringTest_1853, PDFA_EmbeddedInText_MatchesSubstring_1853)
{
    // regex_search should find the pattern in a longer string
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFA, "conforms to PDF/A-1b standard"));
}

// ==================== Date with colon format ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_WithColon2001_ReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFX, "PDF/X-1:2001"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part1_WithColon2003_ReturnsPart4_1853)
{
    EXPECT_EQ(subtypePart4, pdfPartFromString(subtypePDFX, "PDF/X-1:2003"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_WithColon2002_ReturnsPart3_1853)
{
    EXPECT_EQ(subtypePart3, pdfPartFromString(subtypePDFX, "PDF/X-3:2002"));
}

TEST_F(PdfPartFromStringTest_1853, PDFX_Part3_WithColon2003_ReturnsPart6_1853)
{
    EXPECT_EQ(subtypePart6, pdfPartFromString(subtypePDFX, "PDF/X-3:2003"));
}

// ==================== Verify PDFX Part2 ignores date ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part2_WithDate_ReturnsPart5_1853)
{
    EXPECT_EQ(subtypePart5, pdfPartFromString(subtypePDFX, "PDF/X-2:2003"));
}

// ==================== Non-PDFX with date (date ignored in default path) ====================

TEST_F(PdfPartFromStringTest_1853, PDFA_Part1_WithDate_StillReturnsPart1_1853)
{
    EXPECT_EQ(subtypePart1, pdfPartFromString(subtypePDFA, "PDF/A-1b:2005"));
}

// ==================== PDFX Part4 with date ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part4_WithDate_ReturnsPart7_1853)
{
    EXPECT_EQ(subtypePart7, pdfPartFromString(subtypePDFX, "PDF/X-4:2010"));
}

// ==================== PDFX Part5 with date ====================

TEST_F(PdfPartFromStringTest_1853, PDFX_Part5_WithDate_ReturnsPart8_1853)
{
    EXPECT_EQ(subtypePart8, pdfPartFromString(subtypePDFX, "PDF/X-5g:2010"));
}
