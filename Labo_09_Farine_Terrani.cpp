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
#include <iostream>     // cout
#include <iomanip>      // setw
#include <vector>       // 
#include <algorithm>    // 
#include <random>       // rand
#include <numeric>      // 
#include <ctime>        // 

using namespace std;

// Nommer les vecteurs afin de faciliter leur utilisation
using Ligne = vector<int>;
using Matrice = vector<Ligne>;

/**
 * Fonction permettant d'afficher un vecteur
 * @param os      Flux de sortie
 * @param vec     Vecteur à afficher
 * @return        Retourne un flux de sortie
 */
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

/**
 * Fonction permettant de faire la somme des valeurs d'un vecteur spécifique
 * @param ligne   Vecteur dont on doit calculer la somme
 * @return        Retourne la somme
 */
int sommeLigne(const Ligne& ligne) {
   return accumulate(ligne.begin(), ligne.end(), 0);
}

/**
 * Fonction permettant de faire la somme des valeurs d'une matrice spécifique
 * @param matrice    Matrice dont on doit calculer la somme
 * @return           Retourne la somme
 */
Ligne sommeLignes( const Matrice& matrice )
{
   vector<int> sommes( matrice.size() );
   transform( matrice.cbegin(), matrice.cend(), sommes.begin(), sommeLigne );
   
   return sommes;
}

/**
 * Fonction permettant de mélanger les vecteurs d'une matrice
 * @param matrice    Matrice dont on doit mélanger les vecteurs
 */
void shuffleMatrice( Matrice& matrice )
{
   shuffle( matrice.begin(), matrice.end(), default_random_engine( time(nullptr) ) );
}

/**
 * Fonction permettant de comparer la somme d'un vecteur comparé à un autre et retourner
 * le maximum
 * @param a    Première vecteur pour la comparaison
 * @param b    Deuxième vecteur pour la comparaison
 * @return     Retourne si la somme du premier vecteur est plus grand que celle du deuxième vecteur
 */
bool comparerMaxSommeLignes( const Ligne& a, const Ligne& b )
{
   return *max_element(a.cbegin(), a.cend()) < *max_element(b.cbegin(), b.cend());
}

/**
 * Fonction permettant de trier les vecteurs d'une matrice.
 * @param matrice    Matrice dont on doit trier les vecteurs.
 */
void sortMatrice( Matrice& matrice )
{
   sort( matrice.begin(), matrice.end(), comparerMaxSommeLignes );
}

/**
 * Fonction permettant de contrôler si une matrice est carrée.
 * @param matrice    Matrice dont on doit contrôler si elle est carrée.
 * @return           Retourne un booléen indiquant son état.
 */
bool estCarree(const Matrice& matrice){
   for(size_t i = 0; i < matrice.size(); ++i){
      if(matrice[i].size() != matrice.size())
         return false;
   }
   return true;
}

/**
 * Fonction permettant de calculer la somme des valeurs de la diagonale 
 * haut-gauche à bas-droite, d'une matrice carrée.
 * @param matrice    Matrice dont on doit calculer la diagonale
 * @param somme      Valeur référencée de la somme.
 * @return           Retourne un booléen pour confirmer si le calcul s'est effectué ou non
 */
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

/**
 * Fonction permettant de calculer la somme des valeurs de la diagonale 
 * haut-droite à bas-gauche, d'une matrice carrée.
 * @param matrice    Matrice dont on doit calculer la diagonale
 * @param somme      Valeur référencée de la somme.
 * @return           Retourne un booléen pour confirmer si le calcul s'est effectué ou non
 */
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

/**
 * Fonction permettant d'afficher une matrice spécifique
 * @param os         Flux de sortie
 * @param matrice    Matrice dont on souhaite afficher
 * @return           Retourne un flux de sortie
 */
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

/**
 * Fonction permettant de comparer la somme d'un vecteur comparé à un autre et retourner
 * le minimum
 * @param ligneA    Première vecteur pour la comparaison
 * @param ligneB    Deuxième vecteur pour la comparaison
 * @return     Retourne si la somme du premier vecteur est plus petit que celle du deuxième vecteur
 */
bool compareMinSommeLignes(Ligne ligneA, Ligne ligneB){
   return sommeLigne(ligneA) < sommeLigne(ligneB);
}

/**
 * Fonction permettant de retourner le vecteur d'une matrice dont la somme des valeurs
 * est la plus petite.
 * @param matrice    Matrice dont on doit le vecteur en question
 * @return           Retourne le vecteur d'une matrice qui a la somme la plus petite.
 */
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