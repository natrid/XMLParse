#ifndef XMLPARKDATAREADER_HH
#define XMLPARKDATAREADER_HH

#include "parkdata.hh"
#include "parkkipaikka.hh"
#include <QIODevice>
#include <QXmlStreamReader>

//A class that can read a "d2LogicaModel" XML document
class XMLParkDataReader
{
public:
    XMLParkDataReader(Parkdata* parkdata);
    bool read(QIODevice *device);
    QString errorString() const;

private:
    QXmlStreamReader reader;
    Parkdata* m_parkdata;

    void readParkData();
    void readFacility();
    void readFacilityInformation(Parkkipaikka *parkkipaikka);
    //void readTitle(Parkkipaikka *parkkipaikka);
    void readFacilityStatusInformation();
};

#endif // XMLPARKDATAREADER_HH
