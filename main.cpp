#include <QFile>
#include <QDebug>
#include "parkdata.hh"
#include "parkkipaikka.hh"
#include "xmlparkdatareader.hh"


void readXml(const QString& fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        return;
    }

    Parkdata* parkdata = new Parkdata;
    XMLParkDataReader xmlReader(parkdata);
    qDebug() << parkdata;
    if (!xmlReader.read(&file))
        qDebug() << "Parse error in file " << xmlReader.errorString();
    else
    {
        Parkkipaikka* park = new Parkkipaikka;
        park->setTitle("dsafdsafasf");
        park->print();
        parkdata->print();
    }
}

int main(int argc, char *argv[])
{
    readXml("test.xml");
    return 0;
}
