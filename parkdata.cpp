#include "parkdata.hh"
#include <QDebug>


void Parkdata::addParkkipaikka(Parkkipaikka *parkkipaikka)
{
    m_parkkipaikat.append(parkkipaikka);
}

void Parkdata::addParkkipaikkaStatus(QString &id, int &availableSlots)
{
        foreach (Parkkipaikka* parkkipaikka, m_parkkipaikat) {
            if (parkkipaikka->compareID(id)) {
                parkkipaikka->setAvaliableSlots(availableSlots);
            }
        }
}

void Parkdata::print() const
{
        qDebug() << "Parkdata print:";
    foreach (Parkkipaikka* parkkipaikka, m_parkkipaikat) {
        parkkipaikka->print();
    }
}
