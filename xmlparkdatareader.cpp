#include "xmlparkdatareader.hh"
#include <QDebug>

XMLParkDataReader::XMLParkDataReader(Parkdata *parkdata)
{
    m_parkdata = parkdata;
}

bool XMLParkDataReader::read(QIODevice *device)
{

    reader.setDevice(device);

    if (reader.readNextStartElement()) {
        if (reader.name() == "d2LogicaModel")
        {
            qDebug() << "read()";
            readParkData();
        }
        else
            reader.raiseError(QObject::tr("Not a ParkData file"));
    }
    return !reader.error();


}

QString XMLParkDataReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(reader.errorString())
            .arg(reader.lineNumber())
            .arg(reader.columnNumber());
}

void XMLParkDataReader::readParkData()
{
    while(reader.readNextStartElement()){
        if(reader.name() == "payloadPublication")
        {
            while(reader.readNextStartElement()){
                if(reader.name() == "genericPublicationExtension")
                {
                    while(reader.readNextStartElement()){
                        if(reader.name() == "parkingFacilityTablePublication")
                        {
                            while(reader.readNextStartElement()){
                                if(reader.name() == "parkingFacilityTable")
                                {
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "parkingFacility")
                                        {
                                            //qDebug() << "readparkkipaikka()";
                                            readFacility();
                                        }
                                        else
                                        {
                                            reader.skipCurrentElement();
                                        }
                                    }

                                }
                                else
                                {
                                    reader.skipCurrentElement();

                                }
                            }
                        }
                        else if (reader.name() == "parkingFacilityTableStatusPublication")
                        {
                            qDebug() << "readparkkipaikkaStatus()";
                            readFacilityStatusInformation();
                        }
                        else
                        {
                            reader.skipCurrentElement();

                        }
                    }
                }
                else
                {
                    reader.skipCurrentElement();

                }
            }
        }
        else
        {
            reader.skipCurrentElement();

        }
    }
}


void XMLParkDataReader::readFacility()
{
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "parkingFacility");

    Parkkipaikka* park = new Parkkipaikka;

    QString id = reader.attributes().value("id").toString();
    park->setID(id);

    readFacilityInformation(park);

    park->setAvaliableSlots(0);

    m_parkdata->addParkkipaikka(park);
}

//Reads general information about a Facility
void XMLParkDataReader::readFacilityInformation(Parkkipaikka *parkkipaikka)
{
    QString latitude;
    QString longitude;
    while (reader.readNextStartElement()) {
        if (reader.name() == "parkingFacilityName")
        {
            QString title = reader.readElementText();
            parkkipaikka->setTitle(title);
        }
        else if (reader.name() == "carParkDetails") {
            while (reader.readNextStartElement()) {
                if(reader.name() == "value")
                {
                    QString address = reader.readElementText();
                    parkkipaikka->setAddress(address);
                }
                else
                {
                    reader.skipCurrentElement();
                }
            }
        }
        else if (reader.name() == "totalParkingCapacity")
        {
            QString capacity = reader.readElementText();
            parkkipaikka->setCapacity(capacity.toInt());
        }
        else if (reader.name() == "entranceLocation"){
            while (reader.readNextStartElement()) {
                if(reader.name() == "pointByCoordinates")
                {
                    while (reader.readNextStartElement()) {
                        if(reader.name() == "pointCoordinates")
                        {
                            while (reader.readNextStartElement()) {
                                if(reader.name() == "latitude")
                                {
                                    latitude = reader.readElementText();
                                }
                                else if(reader.name() == "longitude")
                                {
                                    longitude = reader.readElementText();
                                }
                                else
                                {
                                    reader.skipCurrentElement();
                                }
                            }
                            parkkipaikka->setCoordinates(longitude,latitude);
                        }
                        else
                        {
                            reader.skipCurrentElement();
                        }
                    }
                }
                else
                {
                    reader.skipCurrentElement();
                }
            }
        }
        else
        {
            reader.skipCurrentElement();

        }
    }

}

//Reads Status information about a facility. the information is linked with facility id.
//Occupied slots defaults at 0 if nothing is mentioned
void XMLParkDataReader::readFacilityStatusInformation()
{
    while (reader.readNextStartElement()) {
        if (reader.name() == "parkingFacilityStatus")
        {
            QString id;
            QString occupiedSpaces = "0";
            while (reader.readNextStartElement())
            {
                if (reader.name() == "parkingFacilityReference")
                {
                    id = reader.attributes().value("id").toString();
                    qDebug("match1");
                    qDebug(id.toLocal8Bit());

                }

                if(reader.name() == "totalNumberOfOccupiedParkingSpaces")
                {
                    occupiedSpaces = reader.readElementText();
                    qDebug("match2");
                    qDebug(occupiedSpaces.toLocal8Bit());


                }
                else if(reader.name() == "parkingFacilityStatus")
                {
                    QString s = reader.readElementText();
                    qDebug(s.toLocal8Bit());
                }
                else
                {
                    reader.skipCurrentElement();
                }
            }
            int spaces = occupiedSpaces.toInt();
            m_parkdata->addParkkipaikkaStatus(id,spaces);
            qDebug("match3");
            qDebug(id.toLocal8Bit());
            qDebug(occupiedSpaces.toLocal8Bit());

        }
        else
        {
            reader.skipCurrentElement();
        }
    }
}
