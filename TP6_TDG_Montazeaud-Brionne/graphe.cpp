//
// Created by benoit on 06/04/19.
//
#include <fstream>
#include <iostream>
#include "graphe.h"
#include <unordered_map>
#include <unordered_set>
#include <set>

graphe::graphe(std::string nomFichier) {
    std::ifstream ifs{nomFichier};
    std::ostream os;
    if (!ifs)
        throw std::runtime_error("Impossible d'ouvrir en lecture " + nomFichier);
    ifs >> m_ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x, y;
    //lecture des sommets
    for (int i = 0; i < m_ordre; ++i) {
        ifs >> id;
        if (ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id, new Sommet{id}});
        ifs
    }
    ifs >> m_taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i = 0; i < m_taille; ++i) {
        //lecture des ids des deux extr�mit�s
        ifs >> id;
        if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs >> id_voisin;
        if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�
    }
}

void graphe::afficher() const {
    std::cout << "graphe : " << std::endl;
    std::cout << "  Ordre : " << m_sommets.size() << std::endl;
    for (auto s:m_sommets) {
        std::cout << "  Sommet : ";
        s.second->afficherData();
        std::cout << "  ";
        s.second->afficherVoisins();
    }
}

void graphe::parcoursBFS(std::string id) const {
    Sommet *s0 = (m_sommets.find(id))->second;
    std::unordered_map<std::string, std::string> l_pred;
    l_pred = s0->parcoursBFS();
}

void graphe::afficherBFS(std::string id) const {
    Sommet *s0 = (m_sommets.find(id))->second;
    std::unordered_map<std::string, std::string> l_pred;
    std::cout << "parcoursBFS a partir de " << id << " :" << std::endl;
    l_pred = s0->parcoursBFS();
    for (const auto &s:l_pred) {
        std::cout << s.first << " <--- ";
        std::pair<std::string, std::string> pred = s;
        while (pred.second != id) {
            pred = *l_pred.find(pred.second);
            std::cout << pred.first << " <--- ";
        }
        std::cout << id << std::endl;
    }
}

void graphe::parcoursDFS(std::string id) const {
    Sommet *s0 = (m_sommets.find(id))->second;
    std::unordered_map<std::string, std::string> l_pred;
    l_pred = s0->parcoursDFS();
}

void graphe::afficherDFS(std::string id) const {
    Sommet *s0 = (m_sommets.find(id))->second;
    std::unordered_map<std::string, std::string> l_pred;
    std::cout << "parcoursDFS a partir de " << id << " :" << std::endl;
    l_pred = s0->parcoursDFS();
    for (const auto &s:l_pred) {
        std::cout << s.first << " <--- ";
        std::pair<std::string, std::string> pred = s;
        while (pred.second != id) {
            pred = *l_pred.find(pred.second);
            std::cout << pred.first << " <--- ";
        }
        std::cout << id << std::endl;
    }
}

int graphe::rechercher_afficherToutesCC() const {
    size_t i = 0;
    std::set<std::string> tasDeSommets;
    std::cout << "composantes connexes :";

    while (tasDeSommets.size() != m_ordre) {
        for (const auto &sommet : m_sommets) {
            if (!tasDeSommets.count(sommet.first)) {
                Sommet *s = (m_sommets.find(sommet.first))->second;
                auto composante = s->rechercherCC();
                std::cout << std::endl;
                composante.insert(sommet.first);
                std::cout << "  cc" << i++ << std::endl;
                for (const auto &c:composante) {
                    tasDeSommets.insert(c);
                    std::cout << "    " << c << "    ";
                }
            }
        }
    }
    std::cout << std::endl;
    std::cout << "nb cc :" << i << std::endl;
    return i;
}

std::string graphe::isEulerien() {
    int nbDegreImpaire = 0;
    int degre;
    for (auto it : m_sommets) {
        degre = it.second->getDegre();
        if (degre & 1)
            nbDegreImpaire++;
    }
    if ((nbDegreImpaire == 0) || (nbDegreImpaire == 2)) {
        if (nbDegreImpaire == 0) {
            return "  cercle eulerien";
        } else {
            return "  oui";
        }
    } else {
        return "  non";
    }

}

graphe::~graphe()
= default;

