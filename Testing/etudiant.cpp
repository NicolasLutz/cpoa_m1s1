#include "etudiant.h"

int Etudiant::s_count=0;

Etudiant::Etudiant()
{
}

Etudiant::Etudiant(std::string name, int age, Formation_t formation) :
    m_name(name), m_age(age), m_formation(formation), m_id(s_count++)
{

}

//=====================================================================
//Accesseurs//

std::string Etudiant::Name() const
{
    return m_name;
}

int Etudiant::Age() const
{
    return m_age;
}

Formation_t Etudiant::Formation() const
{
    return m_formation;
}

std::string Etudiant::FormationString() const
{
    return ((m_formation==ISI_F) ? "Bogoss" : "Pas bogoss");
}

int Etudiant::Id() const
{
    return m_id;
}

//=====================================================================
//Opérations//


//=====================================================================

std::ostream& operator<< (std::ostream &stream, const Etudiant &object)
{
    stream << object.Name() << " - " << object.Id() << " : " << object.Age() << " ans, M1 " << object.FormationString();
    return stream;
}

void E_display (const Etudiant &object)
{
    std::cout << object << std::endl;
    return;
}

bool E_biggest (const Etudiant &object, const Etudiant &other)
{
    return object.Id()>other.Id();
}

//=====================================================================
//=====================================================================
//=====================================================================

Fnct_Display::Fnct_Display()
{

}

void Fnct_Display::operator()(const Etudiant &object)
{
    E_display(object);
}

