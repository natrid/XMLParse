#ifndef PARKKIPAIKKA_HH
#define PARKKIPAIKKA_HH

#include <QString>
#include <QStringList>

//A class that represents a parking facility
class Parkkipaikka
{
public:
    QString title() const {return m_title;}
    void setTitle(const QString& title) {this->m_title = title;}    
    void setID(const QString& id) {this->m_id = id;}
    void setAddress(const QString& address) {this->m_address = address;}
    void setCapacity(const int& capacity) {this->m_capacity = capacity;}
    void setAvaliableSlots(const int& availableSlots) {this->m_occupiedSlots = availableSlots;}
    void setCoordinates(const QString& longitude, const QString& latitude);
    bool compareID(QString &id);
    void print() const;
private:
    QString m_title;
    QString m_id;
    QString m_address;
    int m_capacity;
    int m_occupiedSlots;
    double m_longitude;
    double m_latitude;
};

#endif // PARKKIPAIKKA_HH
