

### Test Cases for `pdfimages`



```cpp

#include <gtest/gtest.h>

#include "pdfimages.cpp"



TEST(PDFImagesTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdfimages"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFImagesTest, EnablePNG) {

    int argc = 2;

    char* argv[] = {"pdfimages", "-png"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFImagesTest, EnableTIFF) {

    int argc = 2;

    char* argv[] = {"pdfimages", "-tiff"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFImagesTest, DumpJPEG) {

    int argc = 2;

    char* argv[] = {"pdfimages", "-j"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFImagesTest, AllFormats) {

    int argc = 2;

    char* argv[] = {"pdfimages", "-all"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFImagesTest, ListImages) {

    int argc = 2;

    char* argv[] = {"pdfimages", "-list"};

    EXPECT_EQ(main(argc, argv), 0);

}

```



### Test Cases for `pdftohtml`



```cpp

#include <gtest/gtest.h>

#include "pdftohtml.cpp"



TEST(PDFToHTMLTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdftohtml"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFToHTMLTest, RawOrder) {

    rawOrder = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftohtml", "-raw"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(rawOrder);

}



TEST(PDFToHTMLTest, ComplexMode) {

    complexMode = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftohtml", "-c"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(complexMode);

}



TEST(PDFToHTMLTest, SingleHtml) {

    singleHtml = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftohtml", "-s"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(singleHtml);

}

```



### Test Cases for `pdfdetach`



```cpp

#include <gtest/gtest.h>

#include "pdfdetach.cpp"



TEST(PDFDetachTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdfdetach"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFDetachTest, ListEmbeddedFiles) {

    doList = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdfdetach", "-list"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(doList);

}



TEST(PDFDetachTest, SaveFileByNumber) {

    saveNum = -1; // Set to invalid value for testing

    int argc = 3;

    char* argv[] = {"pdfdetach", "-save", "1"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_EQ(saveNum, 1);

}



TEST(PDFDetachTest, SaveFileByName) {

    memset(saveFile, 0, sizeof(saveFile)); // Clear saveFile for testing

    int argc = 3;

    char* argv[] = {"pdfdetach", "-savefile", "example.pdf"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_STREQ(saveFile, "example.pdf");

}

```



### Test Cases for `pdftops`



```cpp

#include <gtest/gtest.h>

#include "pdftops.cpp"



TEST(PDFToPSTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdftops"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFToPSTest, Level1) {

    level1 = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftops", "-level1"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(level1);

}



TEST(PDFToPSTest, EPSOutput) {

    doEPS = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftops", "-eps"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(doEPS);

}



TEST(PDFToPSTest, BinaryPSOutput) {

    psBinary = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftops", "-binary"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(psBinary);

}

```



### Test Cases for `pdftotext`



```cpp

#include <gtest/gtest.h>

#include "pdftotext.cpp"



TEST(PDFToTextTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdftotext"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFToTextTest, LayoutMode) {

    physLayout = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftotext", "-layout"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(physLayout);

}



TEST(PDFToTextTest, FixedPitch) {

    fixedPitch = -1; // Set to invalid value for testing

    int argc = 3;

    char* argv[] = {"pdftotext", "-fixed", "12.0"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_DOUBLE_EQ(fixedPitch, 12.0);

}



TEST(PDFToTextTest, BoundingBox) {

    bbox = false; // Set to false for testing

    int argc = 2;

    char* argv[] = {"pdftotext", "-bbox"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_TRUE(bbox);

}

```



### Test Cases for `pdfseparate`



```cpp

#include <gtest/gtest.h>

#include "pdfseparate.cpp"



TEST(PDFSeparateTest, DefaultOptions) {

    int argc = 1;

    char* argv[] = {"pdfseparate"};

    EXPECT_EQ(main(argc, argv), 0);

}



TEST(PDFSeparateTest, FirstPage) {

    firstPage = -1; // Set to invalid value for testing

    int argc = 3;

    char* argv[] = {"pdfseparate", "-f", "2"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_EQ(firstPage, 2);

}



TEST(PDFSeparateTest, LastPage) {

    lastPage = -1; // Set to invalid value for testing

    int argc = 3;

    char* argv[] = {"pdfseparate", "-l", "5"};

    EXPECT_EQ(main(argc, argv), 0);

    EXPECT_EQ(lastPage, 5);

}

```


