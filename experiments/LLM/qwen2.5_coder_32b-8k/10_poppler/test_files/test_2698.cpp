#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "Dict.h"

#include "XRef.h"

#include "Object.h"



using namespace std;



class PDFDocTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or objects here.

        srcXRef = new XRef();

        countXRef = new XRef();

        numOffset = 10;

        oldRefNum = 5;

        newRefNum = 20;



        pageDict = new Dict(srcXRef);

        Object objName("TestObjectName", srcXRef);

        Object objNum(newRefNum, srcXRef);

        pageDict->dictAdd("Name", &objName);

        pageDict->dictAdd("Number", &objNum);



        doc = new PDFDoc();

    }



    void TearDown() override {

        // Clean up any resources used in the tests.

        delete srcXRef;

        delete countXRef;

        delete pageDict;

        delete doc;

    }



    XRef* srcXRef;

    XRef* countXRef;

    unsigned int numOffset;

    int oldRefNum;

    int newRefNum;



    Dict* pageDict;

    PDFDoc* doc;

};



TEST_F(PDFDocTest, MarkPageObjects_NoAnnotations) {

    EXPECT_TRUE(doc->markPageObjects(pageDict, srcXRef, countXRef, numOffset, oldRefNum, newRefNum));

}



TEST_F(PDFDocTest, MarkPageObjects_WithAnnotations) {

    Dict* annotations = new Dict(srcXRef);

    pageDict->dictAdd("Annots", Object(annotations));



    EXPECT_TRUE(doc->markPageObjects(pageDict, srcXRef, countXRef, numOffset, oldRefNum, newRefNum));

}



TEST_F(PDFDocTest, MarkPageObjects_WithNestedDictionary) {

    Dict* nestedDict = new Dict(srcXRef);

    pageDict->dictAdd("Resources", Object(nestedDict));



    EXPECT_TRUE(doc->markPageObjects(pageDict, srcXRef, countXRef, numOffset, oldRefNum, newRefNum));

}



TEST_F(PDFDocTest, MarkPageObjects_WithStream) {

    // Add a stream to the page dictionary

    Dict* streamDict = new Dict(srcXRef);

    Stream* dummyStream = new DummyStream(streamDict);  // Assuming DummyStream is defined elsewhere for testing

    Object streamObj(dummyStream);



    pageDict->dictAdd("Contents", streamObj);



    EXPECT_TRUE(doc->markPageObjects(pageDict, srcXRef, countXRef, numOffset, oldRefNum, newRefNum));

}



TEST_F(PDFDocTest, MarkPageObjects_WithNullObject) {

    pageDict->dictAdd("EmptyEntry", Object());



    EXPECT_TRUE(doc->markPageObjects(pageDict, srcXRef, countXRef, numOffset, oldRefNum, newRefNum));

}

```


