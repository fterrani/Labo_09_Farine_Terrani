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

using Ligne = vector<int>;
using Matrice = vector<Ligne>;

ostream& operator<<(ostream& os, const Ligne& vec)
{
   os << '[';
   
   if (vec.size() > 0)
   {
      os << vec.at(0);
      
      for ( Ligne::const_iterator it = vec.cbegin()+1; it != vec.cend(); ++it )
      {
         os << ',';
         os << *it;
      }
   }
   
   os << ']';
   
   return os;
}

int sommeLigne(const Ligne& ligne) {
   return accumulate(ligne.begin(), ligne.end(), 0);
}

Ligne sommeLignes( const Matrice& matrice )
{
   vector<int> sommes( matrice.size() );
   transform( matrice.cbegin(), matrice.cend(), sommes.begin(), sommeLigne );
   
   return sommes;
}

void shuffleMatrice( Matrice& matrice )
{
   shuffle( matrice.begin(), matrice.end(), default_random_engine( time(nullptr) ) );
}

bool comparerMaxSommeLignes( const Ligne& a, const Ligne& b )
{
   return *max_element(a.cbegin(), a.cend()) < *max_element(b.cbegin(), b.cend());
}

void sortMatrice( Matrice& matrice )
{
   sort( matrice.begin(), matrice.end(), comparerMaxSommeLignes );
}

bool estCarree(const Matrice& matrice){
   for(size_t i = 0; i < matrice.size(); ++i){
      if(matrice[i].size() != matrice.size())
         return false;
   }
   return true;
}


bool sommeDiagGD( const Matrice& matrice, int& somme )
{
   if ( !estCarree(matrice) )
      return false;
   
   int i = 0;
   somme = 0;
   
   // for ( vector<vector<int>>::const_reverse_iterator itLigne = matrice.crbegin(); itLigne != matrice.crend(); ++itLigne, ++i )
   for ( Matrice::const_iterator itLigne = matrice.cbegin(); itLigne != matrice.cend(); ++itLigne, ++i )
   {
      Ligne::const_iterator itColonne = (*itLigne).cbegin() + i;
      
      somme += *itColonne;
   }
   
   return true;
}

bool sommeDiagDG( const Matrice& matrice, int& somme )
{
   if ( !estCarree(matrice) )
      return false;
   
   int i = 0;
   somme = 0;
   
   for ( Matrice::const_reverse_iterator itLigne = matrice.crbegin(); itLigne != matrice.crend(); ++itLigne, ++i )
   {
      Ligne::const_iterator itColonne = (*itLigne).cbegin() + i;
      
      somme += *itColonne;
   }
   
   return true;
}

ostream& operator<<(ostream& os, const Matrice& matrice)
{
   os << '[';
   if(matrice.size() > 0){
      os << matrice[0];
      
      for(size_t i = 1; i < matrice.size(); ++i){
         os << ',';
         os << matrice[i];
      }   
   }
   os << ']';
   return os;
}


bool compareMinSommeLignes(Ligne ligneA, Ligne ligneB){
   return sommeLigne(ligneA) < sommeLigne(ligneB);
}

Ligne vectSommeMin(const Matrice& matrice){
   return *min_element(matrice.cbegin(), matrice.cend(), compareMinSommeLignes);
}

int main()
{
   const unsigned int W = 40;
   const string MSG_MATRICE_NON_CARRE = "Matrice non carree !";
   
   
   
   vector<Matrice> matrices = {
                                 //Matrice carrée d'ordre 4
                                 {
                                     {1,2,3,4},
                                     {5,6,7,8},
                                     {9,10,11,12},
                                     {13,14,15,16}
                                 },
                                 //Matrice non carrée
                                 {
                                     {5,6,7,8},
                                     {1,2,3,4}
                                 },
                                 //"Matrice" irrégulière
                                 {
                                     {1,2,3,4,5,6},
                                     {9},
                                     {7,8},
                                     {13,14,15,16}
                                 }
                              };
   
   Ligne v = {1,2,3,4,5};
   
   
   
   cout << left << boolalpha;
   
   
   
   cout << setw(W) << "Affichage de vecteur : " << v << endl;
   for(Matrice& matrice : matrices){
      cout << setw(W) << "Affichage de matrice : " << matrice << endl;
      cout << setw(W) << "Somme des lignes de la matrice : " << sommeLignes(matrice) << endl;

      cout << setw(W) << "Matrice carree ? " << estCarree(matrice) << endl;

      cout << setw(W) << "Vecteur avec somme minimale : " << vectSommeMin(matrice) << endl;

      int diag = 0;
      cout << setw(W) << "Somme diagonale gauche-droite : " << (sommeDiagGD(matrice, diag)? to_string(diag) : MSG_MATRICE_NON_CARRE) << endl;
      cout << setw(W) << "Somme diagonale droite-gauche : " << (sommeDiagDG(matrice, diag)? to_string(diag) : MSG_MATRICE_NON_CARRE) << endl;

      shuffleMatrice( matrice );
      cout << setw(W) <<  "Melange de la matrice : " << matrice << endl;

      sortMatrice( matrice );
      cout << setw(W) << "Tri de la matrice selon max ligne : " << matrice << endl;

      cout << endl << endl << endl;
   }
   
   
   
   
   cin.get();
   return EXIT_SUCCESS;
}