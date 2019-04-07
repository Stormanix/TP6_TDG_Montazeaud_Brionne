//
// Created by benoit on 06/04/19.
//

#ifndef TP6_TDG_MONTAZEAUD_BRIONNE_GRAPHE_H
#define TP6_TDG_MONTAZEAUD_BRIONNE_GRAPHE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"

class graphe
{
public:
    ///constructeur qui charge le graphe en mémoire
    //format du fichier ordre/liste des sommets/taille/liste des arêtes
    graphe(std::string);

    ///Destructeur
    ~graphe();

    ///Affiche le graphe
    void afficher() const;

    ///lance un parcours en largeur à partir du sommet d'identifiant id
    void parcoursBFS(std::string) const;

    ///lance et affiche le parcours en largeur à partir du sommet d'identifiant id
    void afficherBFS(std::string) const;

    ///lance un parcours en profondeur à partir du sommet d'identifiant id
    void parcoursDFS(std::string) const;

    ///lance et affiche le parcours en profondeur à partir du sommet d'identifiant id
    void afficherDFS(std::string) const;

    ///recherche et affiche les composantes connexes
    ///retourne le nombre de composantes connexes
    int rechercher_afficherToutesCC() const;

    ///Retoune si le graphe est eulerien ou non
    std::string isEulerien();

protected:

private:
    int m_ordre;
    int m_taille;
    /// Le réseau est constitué d'une collection de sommets
    std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

#endif //TP6_TDG_MONTAZEAUD_BRIONNE_GRAPHE_H
