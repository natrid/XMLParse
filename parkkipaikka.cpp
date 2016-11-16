#include "parkkipaikka.hh"
#include <QDebug>


void Parkkipaikka::setCoordinates(const QString &longitude, const QString &latitude)
{
    m_longitude = longitude.toDouble();
    m_latitude = latitude.toDouble();
}

bool Parkkipaikka::compareID(QString &id)
{
    if (id == m_id){
        return true;

    }
    return false;
}

void Parkkipaikka::print() const
{
    qDebug("Title: " + m_title.toLocal8Bit());
    qDebug("ID: " + m_id.toLocal8Bit());
    qDebug("Address: " + m_address.toLocal8Bit());
    qDebug("Parking Slots: " + QString::number(m_capacity).toLocal8Bit());
    qDebug("Occupied Slots: " + QString::number(m_occupiedSlots).toLocal8Bit());
    qDebug("Coordinates: LATITUDE:" + QString::number(m_latitude,'g',8).toLocal8Bit() + "," + " LONGITUDE:" + QString::number(m_longitude,'g',8).toLocal8Bit());
    qDebug("");
}
