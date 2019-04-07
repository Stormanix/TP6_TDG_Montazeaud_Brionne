//
// Created by benoit on 06/04/19.
//
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include "sommet.h"
#include <set>
#include <list>

Sommet::Sommet(std::string id):m_id{std::move(id)}{

}

void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}

void Sommet::afficherData() const{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::set<std::string> tasDeClefs;
    std::queue<const Sommet*> file;
    file.push(this);
    while (!file.empty())
    {
        const Sommet* sommetActuel = file.front();
        file.pop();

        if (!tasDeClefs.count(sommetActuel->m_id))
        {
            tasDeClefs.insert(sommetActuel->m_id);
            for (const auto& voisin : sommetActuel->m_voisins)
            {
                if (!tasDeClefs.count(voisin->m_id))
                {
                    file.push(voisin);
                    l_pred.insert(std::pair<std::string,std::string>(voisin->m_id,sommetActuel->m_id));
                }
            }
        }
    }
    return l_pred;
}

std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::set<std::string> tasDeClefs;
    std::stack<const Sommet*> pile;
    pile.push(this);

    while (!pile.empty())
    {
        const Sommet* sommetActuel = pile.top();
        pile.pop();
        if (!tasDeClefs.count(sommetActuel->m_id))
        {
            tasDeClefs.insert(sommetActuel->m_id);
            for (const auto it : sommetActuel->m_voisins)
            {
                if (!tasDeClefs.count(it->m_id))
                {
                    pile.push(it);
                    l_pred.insert(std::pair<std::string,std::string>(it->m_id,sommetActuel->m_id));
                }
            }

        }
    }
    return l_pred;
}

std::set<std::string> Sommet::rechercherCC() const
{
    std::set<std::string> composantesConvexes;

    auto l_pred = parcoursBFS();
    for(auto& sommetActuel:l_pred)
    {
        composantesConvexes.insert(sommetActuel.first);
    }

    return composantesConvexes;
}

size_t Sommet::getDegre()
{
    size_t degre = 0;
    for(auto& voisin : m_voisins)
    {
        degre++;
    }

    return degre;
}

Sommet::~Sommet()
{
    //dtor
}

