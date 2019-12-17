/*
 --------------------------------------------------------------------------
 Fichier       : Labo_09_Farine_Terrani.cpp
 Auteurs       : Kevin Farine, Terrani Fabien
 Date          : 12.12.2019
 
 But           : TODO
 
 Remarque(s)   : TODO
 
 Compilateur   : gcc
 --------------------------------------------------------------------------
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <ctime>

using namespace std;


ostream& operator<<(ostream& os, const vector<int>& vec)
{
   os << '[';
   
   if (vec.size() > 0)
   {
      os << vec.at(0);
      
      for ( vector<int>::const_iterator it = vec.cbegin()+1; it != vec.cend(); ++it )
      {
         os << ',';
         os << *it;
      }
   }
   
   os << ']';
   
   return os;
}

int sommeLigne(const vector<int>& ligne) {
   return accumulate(ligne.begin(), ligne.end(), 0);
}

vector<int> sommeLignes( const vector<vector<int>>& matrice )
{
   vector<int> sommes( matrice.size() );
   transform( matrice.cbegin(), matrice.cend(), sommes.begin(), sommeLigne );
   
   return sommes;
}

void shuffleMatrice( vector<vector<int>>& matrice )
{
   shuffle( matrice.begin(), matrice.end(), default_random_engine( time(nullptr) ) );
}

bool comparerMaximums( const vector<int>& a, const vector<int>& b )
{
   return *max_element(a.cbegin(), a.cend()) < *max_element(b.cbegin(), b.cend());
}

void sortMatrice( vector<vector<int>>& matrice )
{
   sort( matrice.begin(), matrice.end(), comparerMaximums );
}

bool sommeDiagGD( const vector<vector<int>>& matrice, int& somme )
{
   //if ( !estCarree(matrice) )
   //   return false;
   
   int i = 0;
   somme = 0;
   
   // for ( vector<vector<int>>::const_reverse_iterator itLigne = matrice.crbegin(); itLigne != matrice.crend(); ++itLigne, ++i )
   for ( vector<vector<int>>::const_iterator itLigne = matrice.cbegin(); itLigne != matrice.cend(); ++itLigne, ++i )
   {
      vector<int>::const_iterator itColonne = (*itLigne).cbegin() + i;
      
      somme += *itColonne;
   }
   
   return true;
}

int main()
{
   const unsigned int W = 40;
   vector<vector<int>> m = {
                            {1,2,3,4},
                            {5,6,7,8},
                            {9,10,11,12},
                            {13,14,15,16}
                           };
   
   vector<int> v = {1,2,3,4,5};
   cout << left;
   cout << setw(W) << "Affichage de vecteur" << " : " << v << endl;
   cout << setw(W) << "Somme des lignes de la matrice" << " : " << sommeLignes(m) << endl;
   
   
   int diagGD = 0;
   sommeDiagGD( m, diagGD );
   cout << setw(W) << "Somme diagonale gauche-droite" << " : " << diagGD << endl;
   
   shuffleMatrice( m );
   //cout << setw(W) <<  "Melange de la matrice" << " : " << m << endl;
   
   sortMatrice( m );
   //cout << setw(W) << "Tri de la matrice selon max ligne" << " : " << m << endl;
   
   return EXIT_SUCCESS;
}