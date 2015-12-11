#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <iostream>

typedef enum{ISI_F, ILC_F, RISE_F} Formation_t;

class Etudiant
{
public:
    Etudiant();
    Etudiant(std::string name, int age, Formation_t formation);

    //Accesseurs//
    std::string Name() const;
    int Age() const;
    std::string FormationString() const;
    Formation_t Formation() const;
    int Id() const;

    //Op//

private:
    std::string         m_name;
    int                 m_age;
    Formation_t         m_formation;
    int                 m_id;
    static int          s_count;
};

std::ostream& operator<< (std::ostream &stream, const Etudiant &object);
void E_display (const Etudiant &object);
bool E_biggest (const Etudiant &object, const Etudiant &other);

//=====================================================================
//=====================================================================
//=====================================================================

class Fnct_Display
{
public:
    Fnct_Display();

    void operator()(const Etudiant &object);
};

#endif // ETUDIANT_H
