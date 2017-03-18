// Auteur: A. Zaimi dans le cadre du cours LOG1000
// Ce code est adapté de l'exemple proposé sur https://openclassrooms.com/courses/programmation-objet-avancee-la-conception-avant-tout-design-patterns-a-l-emploi/le-patron-de-conception-observateur-observer 



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
        // On ajoute un abonné à la liste en le plaçant en premier (implémenté en pull).
        // On pourrait placer cet observateur en dernier (implémenté en push, plus commun).
        m_observateurs.push_front(observateur);
    }

    void supprimerObservateur(Observateur* observateur)
    {
        // Enlever un abonné a la liste
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
        // Changement d'étage selon son sens et sa position précédente.
    }
};

class Professeur : public Observateur
{
  public:
    void notifier()
    {
        cout << "Professeur a recu une notification" << endl;
        // Verification que l'étage soit dans les bornes autorisées.
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

    // On simule manuellement un message à diffuser
    uneMessagerie.notifierObservateurs();

    // L'étudiant et le professeurs abonnés ont reçu une notification sur leur méthode notifier()

    uneMessagerie.supprimerObservateur(&unProfesseur);
    cout << "Le professeur decide de ne plus suivre la messagerie" << endl;

    // On simule un nouveau message à diffuser aux abonnés
    uneMessagerie.notifierObservateurs();

    return 0;
}
