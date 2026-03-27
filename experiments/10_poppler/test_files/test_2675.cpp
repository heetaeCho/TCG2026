

### Test Cases for `Dict` Class



```cpp

#include <gtest/gtest.h>

#include "Dict.h"



TEST(DictTest, LookupExistingKey) {

    Dict dict;

    Object value(PDF_STRING);

    value.initString(new GooString("testValue"));

    dict.dictAdd(copyString("key1"), &value);



    Object result;

    EXPECT_TRUE(dict.lookup("key1", &result));

    EXPECT_EQ(result.getString()->getCString(), "testValue");

}



TEST(DictTest, LookupNonExistingKey) {

    Dict dict;



    Object result;

    EXPECT_FALSE(dict.lookup("nonexistentKey", &result));

}



TEST(DictTest, RemoveExistingKey) {

    Dict dict;

    Object value(PDF_STRING);

    value.initString(new GooString("testValue"));

    dict.dictAdd(copyString("key1"), &value);



    dict.dictRemove("key1");



    Object result;

    EXPECT_FALSE(dict.lookup("key1", &result));

}



TEST(DictTest, RemoveNonExistingKey) {

    Dict dict;



    dict.dictRemove("nonexistentKey");

}

```



### Test Cases for `XRef` Class



```cpp

#include <gtest/gtest.h>

#include "XRef.h"



TEST(XRefTest, LookupExistingEntry) {

    XRef xref;

    Object obj(PDF_STRING);

    obj.initString(new GooString("testValue"));

    int num = 10;

    int gen = 0;



    xref.setEntry(num, gen, &obj);



    Object result;

    EXPECT_TRUE(xref.fetch(num, gen, &result));

    EXPECT_EQ(result.getString()->getCString(), "testValue");

}



TEST(XRefTest, LookupNonExistingEntry) {

    XRef xref;



    Object result;

    EXPECT_FALSE(xref.fetch(10, 0, &result));

}

```



### Test Cases for `PDFDoc` Class



```cpp

#include <gtest/gtest.h>

#include "PDFDoc.h"



TEST(PDFDocTest, OpenValidFile) {

    PDFDoc doc("test.pdf", nullptr, nullptr);

    EXPECT_TRUE(doc.isOk());

}



TEST(PDFDocTest, OpenInvalidFile) {

    PDFDoc doc("nonexistent.pdf", nullptr, nullptr);

    EXPECT_FALSE(doc.isOk());

}

```



### Test Cases for `UnicodeMap` Class



```cpp

#include <gtest/gtest.h>

#include "UnicodeMap.h"



TEST(UnicodeMapTest, MatchEncodingName) {

    UnicodeMap uniMap("UTF-8", true, 10);

    EXPECT_TRUE(uniMap.match("UTF-8"));

}



TEST(UnicodeMapTest, MapUnicode) {

    UnicodeMap uniMap("UTF-8", true, 10);

    char buffer[4];

    int result = uniMap.mapUnicode('A', buffer, sizeof(buffer));

    EXPECT_EQ(result, 1);

    EXPECT_EQ(buffer[0], 'A');

}

```



### Test Cases for `JSInfo` Class



```cpp

#include <gtest/gtest.h>

#include "JSInfo.h"

#include "PDFDoc.h"



TEST(JSInfoTest, ContainsNoJavaScript) {

    PDFDoc doc("test.pdf", nullptr, nullptr);

    JSInfo jsInfo(&doc, 1);



    jsInfo.scanJS(1);

    EXPECT_FALSE(jsInfo.containsJS());

}

```



### Test Cases for Global Variables



```cpp

#include <gtest/gtest.h>



extern int firstPage;

extern int lastPage;



TEST(GlobalVariablesTest, DefaultFirstAndLastPages) {

    EXPECT_EQ(firstPage, 1);

    EXPECT_EQ(lastPage, 0);

}



extern bool printBoxes;

extern bool isoDates;

extern bool rawDates;



TEST(GlobalVariablesTest, DefaultPrintingFlags) {

    EXPECT_FALSE(printBoxes);

    EXPECT_FALSE(isoDates);

    EXPECT_FALSE(rawDates);

}

```


