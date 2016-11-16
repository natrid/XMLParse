#ifndef PARKDATA_HH
#define PARKDATA_HH

#include "parkkipaikka.hh"
#include <QList>
#include <QString>


//A class(container) that is constructed of parking facilities
class Parkdata
{
public:
    void addParkkipaikka(Parkkipaikka *parkkipaikka);
    void addParkkipaikkaStatus(QString &id, int &availableSlots);
    void print() const;
private:
    QList<Parkkipaikka*> m_parkkipaikat;
};

#endif // PARKDATA_HH
