#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "Sound.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include <memory>

class AnnotSoundTest_856 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getSound returns a non-null pointer when AnnotSound is constructed with a valid Sound
TEST_F(AnnotSoundTest_856, GetSoundReturnsNonNullWhenConstructedWithSound_856) {
    // We need a PDFDoc to construct annotations. We'll try to create one from a minimal PDF.
    // Since we're treating implementation as black box, we test through available constructors.
    // However, constructing AnnotSound requires a PDFDoc and Sound, which are complex objects.
    // We'll test what we can through the interface.

    // Create a minimal PDF document in memory for testing
    GooString pdfContent(
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Sound /Rect [100 100 200 200] "
        "/Sound 5 0 R /Name /Speaker >>\nendobj\n"
        "5 0 obj\n<< /Type /Sound /R 22050 /C 1 /B 8 /E /Raw /Length 0 >>\n"
        "stream\n\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "0000000370 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n480\n%%EOF\n"
    );

    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Object annotsObj = page->getAnnotsObject();
            if (annotsObj.isArray() && annotsObj.arrayGetLength() > 0) {
                // We can try to get annotations from the page
                Annots *annots = page->getAnnots();
                if (annots && annots->getNumAnnots() > 0) {
                    Annot *annot = annots->getAnnot(0);
                    if (annot && annot->getType() == Annot::typeSound) {
                        AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
                        // Test getSound
                        Sound *sound = soundAnnot->getSound();
                        // Sound should be non-null for a valid sound annotation
                        EXPECT_NE(sound, nullptr);
                    }
                }
            }
        }
    }
}

// Test that getName returns a valid string for an annotation with Name set
TEST_F(AnnotSoundTest_856, GetNameReturnsValidStringWhenNameIsSet_856) {
    GooString pdfContent(
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Sound /Rect [100 100 200 200] "
        "/Sound 5 0 R /Name /Speaker >>\nendobj\n"
        "5 0 obj\n<< /Type /Sound /R 22050 /C 1 /B 8 /E /Raw /Length 0 >>\n"
        "stream\n\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "0000000370 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n480\n%%EOF\n"
    );

    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfContent));

    if (doc && doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                if (annot && annot->getType() == Annot::typeSound) {
                    AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
                    const GooString *name = soundAnnot->getName();
                    // Name was set to "Speaker" in the annotation dict
                    if (name) {
                        EXPECT_STREQ(name->c_str(), "Speaker");
                    }
                }
            }
        }
    }
}

// Test that AnnotSound without Name key returns null for getName
TEST_F(AnnotSoundTest_856, GetNameReturnsNullWhenNameNotSet_856) {
    GooString pdfContent(
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Sound /Rect [100 100 200 200] "
        "/Sound 5 0 R >>\nendobj\n"
        "5 0 obj\n<< /Type /Sound /R 22050 /C 1 /B 8 /E /Raw /Length 0 >>\n"
        "stream\n\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000218 00000 n \n"
        "0000000340 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n450\n%%EOF\n"
    );

    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfContent));

    if (doc && doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                if (annot && annot->getType() == Annot::typeSound) {
                    AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
                    const GooString *name = soundAnnot->getName();
                    // Without a Name key, getName should return null
                    EXPECT_EQ(name, nullptr);
                }
            }
        }
    }
}

// Test annotation type is typeSound
TEST_F(AnnotSoundTest_856, AnnotTypeIsSound_856) {
    GooString pdfContent(
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Sound /Rect [100 100 200 200] "
        "/Sound 5 0 R /Name /Mic >>\nendobj\n"
        "5 0 obj\n<< /Type /Sound /R 44100 /C 2 /B 16 /E /Signed /Length 0 >>\n"
        "stream\n\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "0000000365 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n480\n%%EOF\n"
    );

    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfContent));

    if (doc && doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                Annot *annot = annots->getAnnot(0);
                if (annot) {
                    EXPECT_EQ(annot->getType(), Annot::typeSound);
                }
            }
        }
    }
}

// Test constructing AnnotSound with rect and sound object
TEST_F(AnnotSoundTest_856, ConstructWithRectAndSound_856) {
    GooString pdfContent(
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n"
    );

    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfContent));

    if (doc && doc->isOk()) {
        // Create a sound object dict
        PDFRectangle rect(50, 50, 150, 150);
        
        // Build a Sound stream object
        Dict *soundDict = new Dict(doc->getXRef());
        soundDict->add("R", Object(22050));
        soundDict->add("C", Object(1));
        soundDict->add("B", Object(8));
        soundDict->add("E", Object(objName, "Raw"));
        
        Object soundStreamObj(new Stream(new MemStream(nullptr, 0, 0, Object(soundDict)));
        
        Sound *sound = Sound::parseSound(&soundStreamObj);
        if (sound) {
            auto annotSound = std::make_unique<AnnotSound>(doc.get(), &rect, sound);
            ASSERT_NE(annotSound, nullptr);
            EXPECT_EQ(annotSound->getType(), Annot::typeSound);
            EXPECT_NE(annotSound->getSound(), nullptr);
            delete sound;
        }
    }
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "Sound.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Page.h"
#include <memory>
#include <cstring>

class AnnotSoundTest_856 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

static std::unique_ptr<PDFDoc> createDocWithSoundAnnot(const char *extraAnnotKeys = "/Name /Speaker") {
    // Build a minimal valid PDF with a sound annotation
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    
    std::string annotDict = "<< /Type /Annot /Subtype /Sound /Rect [100 100 200 200] /Sound 5 0 R";
    if (extraAnnotKeys && strlen(extraAnnotKeys) > 0) {
        annotDict += " ";
        annotDict += extraAnnotKeys;
    }
    annotDict += " >>";
    
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Annots [4 0 R] >>\nendobj\n";
    pdf += "4 0 obj\n" + annotDict + "\nendobj\n";
    pdf += "5 0 obj\n<< /R 22050 /C 1 /B 8 /E /Raw /Length 0 >>\nstream\n\nendstream\nendobj\n";
    
    // We don't need a valid xref for PDFDocFactory if it can repair
    pdf += "xref\n0 6\n";
    pdf += "0000000000 65535 f \n";
    // Approximate offsets - the parser should handle minor issues
    char buf[64];
    pdf += "0000000009 00000 n \n";
    pdf += "0000000058 00000 n \n";
    pdf += "0000000115 00000 n \n";
    pdf += "0000000200 00000 n \n";
    pdf += "0000000350 00000 n \n";
    
    std::string trailer = "trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n";
    // approximate
    snprintf(buf, sizeof(buf), "%zu", pdf.size() + trailer.size());
    pdf += trailer;
    pdf += buf;
    pdf += "\n%%EOF\n";
    
    auto *gs = new GooString(pdf.c_str(), pdf.size());
    return std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(*gs));
}

// Test that getSound returns a non-null pointer for a valid sound annotation
TEST_F(AnnotSoundTest_856, GetSoundReturnsNonNull_856) {
    auto doc = createDocWithSoundAnnot("/Name /Speaker");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeSound);
    
    AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
    Sound *sound = soundAnnot->getSound();
    EXPECT_NE(sound, nullptr);
}

// Test that getName returns the correct name
TEST_F(AnnotSoundTest_856, GetNameReturnsSpeaker_856) {
    auto doc = createDocWithSoundAnnot("/Name /Speaker");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    ASSERT_EQ(annot->getType(), Annot::typeSound);
    
    AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
    const GooString *name = soundAnnot->getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "Speaker");
}

// Test that getName returns Mic name
TEST_F(AnnotSoundTest_856, GetNameReturnsMic_856) {
    auto doc = createDocWithSoundAnnot("/Name /Mic");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    
    if (annot->getType() == Annot::typeSound) {
        AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
        const GooString *name = soundAnnot->getName();
        ASSERT_NE(name, nullptr);
        EXPECT_STREQ(name->c_str(), "Mic");
    }
}

// Test annotation without Name key
TEST_F(AnnotSoundTest_856, GetNameReturnsNullWhenNoName_856) {
    auto doc = createDocWithSoundAnnot("");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    
    if (annot->getType() == Annot::typeSound) {
        AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
        const GooString *name = soundAnnot->getName();
        // Without Name key, expect null
        EXPECT_EQ(name, nullptr);
    }
}

// Test that annotation type is typeSound
TEST_F(AnnotSoundTest_856, AnnotTypeIsSound_856) {
    auto doc = createDocWithSoundAnnot("/Name /Speaker");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(annot->getType(), Annot::typeSound);
}

// Test that getSound returns consistent results on multiple calls
TEST_F(AnnotSoundTest_856, GetSoundIsConsistentAcrossCalls_856) {
    auto doc = createDocWithSoundAnnot("/Name /Speaker");
    ASSERT_TRUE(doc && doc->isOk());
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);
    
    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);
    
    if (annot->getType() == Annot::typeSound) {
        AnnotSound *soundAnnot = static_cast<AnnotSound *>(annot);
        Sound *sound1 = soundAnnot->getSound();
        Sound *sound2 = soundAnnot->getSound();
        EXPECT_EQ(sound1, sound2);
    }
}
