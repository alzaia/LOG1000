// Auteur: A. Zaimi dans le cadre du cours LOG1000
// Ce code est adapt� de l'exemple propos� sur https://openclassrooms.com/courses/programmation-objet-avancee-la-conception-avant-tout-design-patterns-a-l-emploi/le-patron-de-conception-observateur-observer 



#include <string>
#include <list>
#include <iostream>
using namespace std;

class Observateur
{
  public:
    virtual void notifier() = 0;
};

class Observable
{
  public:
    void notifierObservateurs() const
    {
        // Notifier tous les observateurs
        list<IObservateur*>::const_iterator end = m_observateurs.end();
        for (list<IObservateur*>::const_iterator it = m_observateurs.begin(); it != end; ++it)
            (*it)->notifier();
    }

    void ajouterObservateur(Observateur* observateur)
    {
        // On ajoute un abonn� � la liste en le pla�ant en premier (impl�ment� en pull).
        // On pourrait placer cet observateur en dernier (impl�ment� en push, plus commun).
        m_observateurs.push_front(observateur);
    }

    void supprimerObservateur(Observateur* observateur)
    {
        // Enlever un abonn� a la liste
        m_observateurs.remove(observateur);
    }
    
  private:
        list<Observateur*> m_observateurs;
};

class Etudiant : public Observateur
{
  public:
    void notifier()
    {
        cout << "Etudiant a recu une notification" << endl;
        // Changement d'�tage selon son sens et sa position pr�c�dente.
    }
};

class Professeur : public Observateur
{
  public:
    void notifier()
    {
        cout << "Professeur a recu une notification" << endl;
        // Verification que l'�tage soit dans les bornes autoris�es.
    }
};

class MessageriePoly : public Observable
{
  public:

   void run()
   {
       while(true)
       {
           if(nouveauMessage)
               notifierObservateurs();
       }
   }

   private:
     bool nouveauMessage;
};

int main()
{
    Etudiant unEtudiant;
    Professeur unProfesseur;

    MessageriePoly uneMessagerie;

    uneMessagerie.ajouterObservateur(&unEtudiant);
    uneMessagerie.ajouterObservateur(&unProfesseur);

    // On simule manuellement un message � diffuser
    uneMessagerie.notifierObservateurs();

    // L'�tudiant et le professeurs abonn�s ont re�u une notification sur leur m�thode notifier()

    uneMessagerie.supprimerObservateur(&unProfesseur);
    cout << "Le professeur decide de ne plus suivre la messagerie" << endl;

    // On simule un nouveau message � diffuser aux abonn�s
    uneMessagerie.notifierObservateurs();

    return 0;
}
