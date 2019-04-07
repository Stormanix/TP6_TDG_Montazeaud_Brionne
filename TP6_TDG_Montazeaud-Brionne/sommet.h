//
// Created by benoit on 06/04/19.
//

#ifndef TP6_TDG_MONTAZEAUD_BRIONNE_SOMMET_H
#define TP6_TDG_MONTAZEAUD_BRIONNE_SOMMET_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

class Sommet {
public:
    ///constructeur qui reçoit en params les données du sommet
    Sommet(std::string);

    void ajouterVoisin(const Sommet *);

    void afficherData() const;

    void afficherVoisins() const;

    ///méthode de parcours en largeur du graphe à partir du sommet
    ///renvoie les prédécesseurs sous forme d'une map (clé=id du sommet,valeur=id de son prédécesseur)
    std::unordered_map<std::string, std::string> parcoursBFS() const;

    ///méthode de parcours en profondeur du graphe à partir du sommet
    std::unordered_map<std::string, std::string> parcoursDFS() const;

    ///méthode qui recherche la composante connexe du sommet
    ///renvoie la liste des ids des sommets de la composante
    std::set<std::string> rechercherCC() const;

    size_t getDegre();

    ~Sommet();

protected:

private:
    /// Voisinage : liste d'adjacence
    std::vector<const Sommet *> m_voisins;

    /// Données spécifiques du sommet
    std::string m_id; // Identifiant
    double m_x, m_y; // Position

};

#endif //TP6_TDG_MONTAZEAUD_BRIONNE_SOMMET_H
