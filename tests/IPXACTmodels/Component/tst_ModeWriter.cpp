//-----------------------------------------------------------------------------
// File: tst_ModeWriter.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 07.08.2023
//
// Description:
// Unit test for class ModeWriter.
//-----------------------------------------------------------------------------

#include <IPXACTmodels/Component/Mode.h>
#include <IPXACTmodels/Component/ModeWriter.h>
#include <IPXACTmodels/common/VendorExtension.h>

#include <QtTest>

class tst_ModeWriter : public QObject
{
    Q_OBJECT

public:
    tst_ModeWriter();

private slots:

    void testWriteNameGroup();
    void testWritePortSlices();
};

//-----------------------------------------------------------------------------
// Function: tst_ModeWriter::tst_ModeWriter()
//-----------------------------------------------------------------------------
tst_ModeWriter::tst_ModeWriter()
{

}

//-----------------------------------------------------------------------------
// Function: tst_ModeWriter::testWriteNameGroup()
//-----------------------------------------------------------------------------
void tst_ModeWriter::testWriteNameGroup()
{
    QString output;
    QXmlStreamWriter xmlStreamWriter(&output);


    QSharedPointer<Mode> testMode(new Mode("testMode"));
    testMode->setDisplayName("testDisplay");
    testMode->setShortDescription("testShortDescription");
    testMode->setDescription("testDescription");
    
    ModeWriter::writeMode(xmlStreamWriter, testMode);

    QString expectedOutput(
        "<ipxact:mode>"
            "<ipxact:name>testMode</ipxact:name>"
            "<ipxact:displayName>testDisplay</ipxact:displayName>"
            "<ipxact:shortDescription>testShortDescription</ipxact:shortDescription>"
            "<ipxact:description>testDescription</ipxact:description>"
        "</ipxact:mode>"
    );

    QCOMPARE(output, expectedOutput);
}

//-----------------------------------------------------------------------------
// Function: tst_ModeWriter::testWritePortSlices()
//-----------------------------------------------------------------------------
void tst_ModeWriter::testWritePortSlices()
{
    QString output;
    QXmlStreamWriter xmlStreamWriter(&output);

    QSharedPointer<Mode> testMode(new Mode("testMode"));

    QSharedPointer<PortSlice> portSlice(new PortSlice("testSlice"));
    portSlice->setDisplayName("sliceDisplay");
    portSlice->setShortDescription("sliceShort");
    portSlice->setDescription("sliceDescription");
    portSlice->setPortRef("testPortRef");
    testMode->getPortSlices()->append(portSlice);

    QSharedPointer<PartSelect> partSelect(new PartSelect);
    partSelect->setLeftRange("1");
    partSelect->setRightRange("0");
    portSlice->setPartSelect(partSelect);

    ModeWriter::writeMode(xmlStreamWriter, testMode);

    QString expectedOutput(
        "<ipxact:mode>"
            "<ipxact:name>testMode</ipxact:name>"
            "<ipxact:portSlice>"
                "<ipxact:name>testSlice</ipxact:name>"
                "<ipxact:displayName>sliceDisplay</ipxact:displayName>"
                "<ipxact:shortDescription>sliceShort</ipxact:shortDescription>"
                "<ipxact:description>sliceDescription</ipxact:description>"
                "<ipxact:portRef portRef=\"testPortRef\"/>"
                "<ipxact:partSelect>"
                    "<ipxact:range>"
                        "<ipxact:left>1</ipxact:left>"
                        "<ipxact:right>0</ipxact:right>"
                    "</ipxact:range>"
                "</ipxact:partSelect>"
            "</ipxact:portSlice>"
        "</ipxact:mode>"
    );

    QCOMPARE(output, expectedOutput);
}

QTEST_APPLESS_MAIN(tst_ModeWriter)

#include "tst_ModeWriter.moc"