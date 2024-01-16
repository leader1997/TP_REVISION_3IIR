#include <iostream>
#include <string>

using namespace std;

class Note {
private:
    float note;
    int coef;
    string matiere;

public:
    Note() {
        // Constructeur par défaut
        cout << "Constructeur par défaut : Note" << endl;
        note = 0;
        coef = 1;
        matiere = "xxxx";
    }

    Note(const Note &n) {
        // Constructeur par copie
        cout << "Constructeur par copie : Note" << endl;
        note = n.note;
        coef = n.coef;
        matiere = n.matiere;
    }

    Note(int coef, string matiere, float note) {
        // Constructeur paramétré
        cout << "Constructeur paramétré : Note" << endl;
        this->note = note;
        this->coef = coef;
        this->matiere = matiere;
    }

    ~Note() {
        // Destructeur
        cout << "Destructeur : Note" << endl;
    }

    // Getters et Setters
    void setMatiere(string matiere) {
        this->matiere = matiere;
    }

    string getMatiere() {
        return matiere;
    }

    int getCoef() const {
        return coef;
    }

    float getNote() const {
        return note;
    }

    // Surcharge des opérateurs d'affichage et de saisie
    friend ostream& operator<<(ostream& out, const Note &n);
    friend istream& operator>>(istream& in, Note &n);

    // Surcharge de l'opérateur d'affectation
    Note& operator=(const Note &n) {
        if (this != &n) {
            note = n.note;
            coef = n.coef;
            matiere = n.matiere;
        }
        return *this;
    }

    friend class Etudiant;
};

ostream& operator<<(ostream& out, const Note &n) {
    // Surcharge de l'opérateur d'affichage
    out << "\t[Coef : " << n.coef << " , Matiere :" << n.matiere << " , Note : " << n.note;
    return out;
}

istream& operator>>(istream& in, Note &n) {
    // Surcharge de l'opérateur de saisie
    cout << "Donner le coef : ";
    in >> n.coef;
    cout << "Donner la matiere : ";
    in >> n.matiere;
    cout << "Donner la note : ";
    in >> n.note;

    return in;
}

class Etudiant {
private:
    string nom;
    int cne;
    Note *notes;
    int taille;
    static int nbEtudiant;

public:
    // Constructeurs et destructeur
    Etudiant();
    Etudiant(int taille, int cne, string nom);
    Etudiant(const Etudiant &);

    ~Etudiant();

    // Accesseurs et mutateurs
    string getNom();
    int getCne();
    int getTaille();

    void setNom(string);
    void setCne(int);
    Note* getNotes();
    // Méthodes statiques
    static float moyenne(const Etudiant &);
    static int getNbEtudiant();
    static Note getNoteMax(const Etudiant&);

    // Surcharge de l'opérateur d'affectation
    Etudiant& operator=(const Etudiant &);
    friend ostream& operator<<(ostream&, const Etudiant&);

};

int Etudiant::nbEtudiant = 0;

Etudiant::Etudiant() {
    // Constructeur par défaut
    cout << "Constructeur par défaut : Etudiant" << endl;
    nom = "xxxx";
    cne = 0;
    taille = 3; // Initialiser en fonction de vos besoins
    notes = new Note[taille](); // Initialiser correctement le tableau de notes

    nbEtudiant++;
}

Etudiant::Etudiant(int taille, int cne, string nom) {
    // Constructeur paramétré
    cout << "Constructeur paramétré : Etudiant" << endl;
    this->nom = nom;
    this->cne = cne;
    this->taille = taille; // Initialiser en fonction du paramètre fourni ou utiliser une valeur par défaut
    notes = new Note[taille](); // Initialiser correctement le tableau de notes

    nbEtudiant++;
}

Etudiant::Etudiant(const Etudiant &e) {
    // Constructeur par copie
    cout << "Constructeur par copie : Etudiant" << endl;
    this->nom = e.nom;
    this->cne = e.cne;
    this->taille = e.taille;
    notes = new Note[taille]();

    for (int i = 0; i < taille; i++) {
        notes[i] = e.notes[i];
    }

    nbEtudiant++;
}

Etudiant::~Etudiant() {
    // Destructeur
    cout << "Destructeur Etudiant" << endl;
    delete[] notes;
    nbEtudiant--;
}

Etudiant& Etudiant::operator=(const Etudiant &e) {
    // Surcharge de l'opérateur d'affectation
    if (this != &e) {
        delete[] notes;

        this->nom = e.nom;
        this->cne = e.cne;
        this->taille = e.taille;
        notes = new Note[taille]();

        for (int i = 0; i < taille; i++) {
            notes[i] = e.notes[i];
        }
    }
    return *this;
}

float Etudiant::moyenne(const Etudiant &e) {
    // Méthode statique pour calculer la moyenne
    int coef = 0;
    float sum = 0;

    for (int i = 0; i < e.taille; i++) {
        coef += e.notes[i].getCoef(); // Supposant que Note a une fonction getCoef()
        sum += e.notes[i].getNote() * e.notes[i].getNote(); // Supposant que Note a une fonction getNote()
    }

    // Gérer le cas où coef est zéro pour éviter une division par zéro
    if(coef == 0) return 0;

    return sum / coef;
}

string Etudiant::getNom() {
    return nom;
}

int Etudiant::getCne() {
    return
    cne;
}

int Etudiant::getTaille() {
    return taille;
}

void Etudiant::setNom(string n) {
    // recuperer nom
    nom = n;
}

void Etudiant::setCne(int cne) {
    // recuperer le CNE
    this->cne = cne;
}

int Etudiant::getNbEtudiant() {
    // Méthode statique pour obtenir le nombre d'étudiants
    return nbEtudiant;
}

Note* Etudiant::getNotes(){
    //Recuperer le tableau notes
    return notes;
}

Note Etudiant::getNoteMax(const Etudiant &e) {
    // Méthode statique pour obtenir la note maximale
    if (e.taille == 0) {
        // Gérer le cas où le tableau est vide
        return Note();
    }

    Note n = e.notes[0];

    for (int i = 1; i < e.taille; i++) {
        if (e.notes[i].getNote() > n.getNote()) {
            n = e.notes[i];
        }
    }
    return n;
}

ostream& operator<<(ostream& out, const Etudiant &e) {
    // Surcharge de l'opérateur d'affichage
    out << "Etudiant :" << endl;
    out << "-Nom:" << e.nom << endl;
    out << "-CNE:" << e.cne << endl;
    out << "-Notes :" << endl;

    for (int i = 0; i < e.taille; i++) {
        out << e.notes[i]<<endl;
    }
    return out;
}


int main() {
    // Création d'un étudiant avec le constructeur par défaut
    Etudiant etudiant1;
    cout << "Etudiant 1:" << endl << etudiant1 << endl;

    // Modification des propriétés de l'étudiant
    etudiant1.setNom("John Doe");
    etudiant1.setCne(12345);
    cout << "Etudiant 1 après modification :" << endl << etudiant1 << endl;

    // Création d'un étudiant avec le constructeur paramétré
    Etudiant etudiant2(5, 67890, "Jane Doe");
    cout << "Etudiant 2:" << endl << etudiant2 << endl;

    // Création de notes pour les étudiants
    Note *note1 = new Note(3, "Math", 15.5);
    Note *note2 = new Note(2, "Physique", 12.0);

    // Ajout des notes aux étudiants
    etudiant1.getNotes()[0] = *note1;
    etudiant1.getNotes()[1] = *note2;

    // Libération de la mémoire allouée dynamiquement
    delete note1;
    delete note2;

    // Affichage de l'étudiant après l'ajout des notes
    cout << "Etudiant 1 après ajout de notes :" << endl << etudiant1 << endl;

    // Calcul de la moyenne pour l'étudiant 1
    float moyenneEtudiant1 = Etudiant::moyenne(etudiant1);
    cout << "Moyenne de l'Etudiant 1 : " << moyenneEtudiant1 << endl;

    // Création d'un étudiant avec le constructeur par copie
    Etudiant etudiant3 = etudiant1;
    cout << "Etudiant 3 (copie d'Etudiant 1) :" << endl << etudiant3 << endl;

    // Modification de l'étudiant 3
    etudiant3.setNom("Alice");
    etudiant3.getNotes()[0].setMatiere("Informatique");

    // Affichage des étudiants après modification
    cout << "Etudiant 1 après modification :" << endl << etudiant1 << endl;
    cout << "Etudiant 3 après modification :" << endl << etudiant3 << endl;

    // Utilisation de la méthode statique pour obtenir le nombre d'étudiants
    cout << "Nombre total d'étudiants : " << Etudiant::getNbEtudiant() << endl;

    // Utilisation de la méthode statique pour obtenir la note maximale
    Note noteMaxEtudiant1 = Etudiant::getNoteMax(etudiant1);
    cout << "Note maximale de l'Etudiant 1 : " <<endl << noteMaxEtudiant1 << endl;

    return 0;
}

