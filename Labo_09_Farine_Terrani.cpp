/*
 --------------------------------------------------------------------------
 Fichier       : Labo_09_Farine_Terrani.cpp
 Auteurs       : Kevin Farine, Terrani Fabien
 Date          : 12.12.2019
 
 But           : Mettre à disposition des fonctions permettant de manipuler des
                 vecteurs et des matrices au moyen des librairies <algorithm> et <numeric>.
                 Les vecteurs et matrices sont représentés au moyen du type vector de la librairie
                 <vector>. Le programme affiche le résultat des différentes fonctions programmées
                 sur le flux d'entrée standard, avec plusieurs matrices permettant de tester la
                 validité du code. L'opérateur << est surchargé afin de permettre d'afficher
                 directement les vecteurs et matrices dans n'importe quel flux de sortie ostream.
 
 Remarque(s)   : Les vecteurs sont représentés par le type Ligne, défini comme vector<int>.
                 Les matrices sont représentées par le type Matrice, définit comme vector<Ligne>.
                 Le default_random_engine de la librairie <random> est utilisé pour la
                 fonction shuffleMatrice. Le seed est initialisé selon l'heure courante avec
                 la fonction time().
 
 Compilateur   : gcc
 --------------------------------------------------------------------------
 */
#include <cstdlib>      // EXIT_SUCCESS et diverses fonctions utiles
#include <iostream>     // cout et ostream
#include <iomanip>      // setw(), left et boolalpha
#include <vector>       // type vector<T>
#include <algorithm>    // min_element(), max_element(), sort()
#include <random>       // default_random_engine
#include <numeric>      // accumulate()
#include <ctime>        // time()

using namespace std;



// Définition de types afin de faciliter l'utilisation de vector<T>
using Ligne   = vector<int>;
using Matrice = vector<Ligne>;



/**
 * Fonction permettant d'afficher une Ligne
 * @param os      Flux de sortie
 * @param ligne   Ligne à afficher
 * @return        Retourne le flux de sortie pour les appels chaînés
 */
ostream& operator<<( ostream& os, const Ligne& ligne )
{
   os << '[';
   
   if (ligne.size() > 0)
   {
      os << ligne[0];
      
      for ( size_t i = 1; i < ligne.size(); ++i )
      {
         os << ',' << ligne[i];
      }
   }
   
   os << ']';
   
   return os;
}



/**
 * Fonction permettant d'afficher une matrice
 * @param os         Flux de sortie
 * @param matrice    Matrice dont on souhaite afficher
 * @return           Retourne un flux de sortie
 */
ostream& operator<<( ostream& os, const Matrice& matrice )
{
   os << '[';
   
   if(matrice.size() > 0)
   {
      os << matrice[0];
      
      for(size_t i = 1; i < matrice.size(); ++i)
      {
         os << ',' << matrice[i];
      }   
   }
   
   os << ']';
   
   return os;
}

/**
 * Fonction permettant de faire la somme des valeurs d'une ligne
 * @param ligne   Ligne dont on doit calculer la somme
 * @return        Somme des nombres contenus dans la ligne
 */
int sommeLigne( const Ligne& ligne )
{
   return accumulate( ligne.begin(), ligne.end(), 0 );
}

/**
 * Fonction permettant de faire la somme des valeurs des lignes d'une matrice
 * @param matrice    Matrice dont on veut calculer la somme des lignes
 * @return           Un vector<int> contenant les sommes des valeurs des lignes de la matrice
 */
vector<int> sommeLignes( const Matrice& matrice )
{
   // Cette fonction retourne un vector<int> car conceptuellement, on retourne davantage
   // une collection de sommes qu'une "ligne".
   
   vector<int> sommes( matrice.size() );
   transform( matrice.cbegin(), matrice.cend(), sommes.begin(), sommeLigne );
   
   return sommes;
}

/**
 * Fonction permettant de mélanger les Ligne d'une matrice
 * @param matrice    Matrice dont les Lignes doivent être mélangés
 */
void shuffleMatrice( Matrice& matrice )
{
   shuffle( matrice.begin(), matrice.end(), default_random_engine( time(0) ) );
}

/**
 * Compare deux Lignes en fonction de leur valeur maximum
 * @param ligneA    Première Ligne
 * @param ligneB    Deuxième Ligne
 * @return          true si la plus grande valeur de ligneA est inférieur à la plus grande
 *                  valeur de ligneB, false sinon.
 */
bool comparerValeurMaxLignes( const Ligne& ligneA, const Ligne& ligneB )
{
   int maxLigneA = *max_element( ligneA.cbegin(), ligneA.cend() );
   int maxLigneB = *max_element( ligneB.cbegin(), ligneB.cend() );
   
   return maxLigneA < maxLigneB;
}

/**
 * Fonction permettant de trier les vecteurs d'une matrice.
 * @param matrice    Matrice dont on doit trier les vecteurs.
 */
void sortMatrice( Matrice& matrice )
{
   sort( matrice.begin(), matrice.end(), comparerValeurMaxLignes );
}

/**
 * Fonction permettant de contrôler si une matrice est carrée.
 * @param matrice    Matrice dont on doit contrôler si elle est carrée.
 * @return           true si matrice est carrée, false sinon.
 */
bool estCarree( const Matrice& matrice )
{
   for ( size_t i = 0; i < matrice.size(); ++i )
   {
      if ( matrice[i].size() != matrice.size() )
         return false;
   }
   
   return true;
}

/**
 * Fonction permettant de calculer la somme des valeurs de la diagonale 
 * haut-gauche à bas-droite, d'une matrice carrée.
 * @param matrice    Matrice dont on doit calculer la diagonale
 * @param somme      Valeur référencée de la somme.
 * @return           true si la matrice est carrée et a donc une diagonale dont la
 *                   somme a pu être calculée, false sinon.
 */
bool sommeDiagGD( const Matrice& matrice, int& somme )
{
   if ( !estCarree( matrice ) )
      return false;
   
   // Réinitialisation du paramètre de sortie
   somme = 0;
   
   int i = 0;
   
   for ( const Ligne& ligne : matrice )
   {
      Ligne::const_iterator itColonne = ligne.cbegin() + i;
      
      somme += *itColonne;
      ++i;
   }
   
   return true;
}

/**
 * Fonction permettant de calculer la somme des valeurs de la diagonale
 * haut-droite à bas-gauche, d'une matrice carrée.
 * @param matrice    Matrice dont on doit calculer la diagonale
 * @param somme      Valeur référencée de la somme.
 * @return           true si la matrice est carrée et a donc une diagonale dont la
 *                   somme a pu être calculée, false sinon.
 */
bool sommeDiagDG( const Matrice& matrice, int& somme )
{
   if ( !estCarree( matrice ) )
      return false;
   
   int i = 0;
   somme = 0;
   
   for ( const Ligne& ligne : matrice )
   {
      Ligne::const_iterator itColonne = ligne.cbegin() + i;
      
      somme += *itColonne;
      ++i;
   }
   
   return true;
}

/**
 * Compare deux Lignes en fonction de la somme de leurs valeurs.
 * @param ligneA    Première Ligne pour la comparaison
 * @param ligneB    Deuxième Ligne pour la comparaison
 * @return          true si la somme des valeurs de ligneA est plus petite que celle
 *                  des valeurs de ligneB, false sinon.
 */
bool comparerMinSommeLignes( Ligne ligneA, Ligne ligneB )
{
   return sommeLigne( ligneA ) < sommeLigne( ligneB );
}

/**
 * Retourne la Ligne d'une matrice dont la somme des valeurs est la plus petite.
 * @param matrice    Matrice contenant les Lignes à comparer
 * @return           La ligne qui a la somme la plus petite.
 */
Ligne vectSommeMin(const Matrice& matrice)
{
   return *min_element( matrice.cbegin(), matrice.cend(), comparerMinSommeLignes );
}

int main()
{
   // Largeur d'affichage des titres de gauche
   const unsigned int W = 40;
   
   const string MSG_MATRICE_NON_CARRE = "Matrice non carree !";
   
   // Vecteur de test
   Ligne v = {1,2,3,4,5};
   
   // Matrices de test
   vector<Matrice> matrices = {
                                 // Matrice carrée d'ordre 4
                                 {
                                     {1,2,3,4},
                                     {5,6,7,8},
                                     {9,10,11,12},
                                     {13,14,15,16}
                                 },
                                 
                                 // Matrice non carrée
                                 {
                                     {5,6,7,8},
                                     {1,2,3,4}
                                 },
                                 
                                 // "Matrice" irrégulière
                                 {
                                     {1,2,3,4,5,6},
                                     {9},
                                     {7,8},
                                     {13,14,15,16}
                                 }
                              };
   
   
   
   
   // Alignement à gauche et affichage en toutes lettres des booléens
   cout << left << boolalpha;
   
   cout << setw(W) << "Affichage de vecteur : " << v << endl;
   cout << endl << endl << endl;
   
   // Toutes les fonctions ci-dessus sont appelées sur chaque matrice de test
   for ( Matrice& matrice : matrices )
   {
      cout << setw(W) << "Affichage de matrice : "           << matrice               << endl;
      cout << setw(W) << "Somme des lignes de la matrice : " << sommeLignes(matrice)  << endl;
      cout << setw(W) << "Matrice carree ? "                 << estCarree(matrice)    << endl;
      cout << setw(W) << "Vecteur avec somme minimale : "    << vectSommeMin(matrice) << endl;

      int diag = 0;
      cout << setw(W) << "Somme diagonale gauche-droite : "
           << ( sommeDiagGD( matrice, diag ) ? to_string( diag ) : MSG_MATRICE_NON_CARRE )
           << endl;
      
      cout << setw(W) << "Somme diagonale droite-gauche : "
           << ( sommeDiagDG( matrice, diag ) ? to_string( diag ) : MSG_MATRICE_NON_CARRE )
           << endl;

      shuffleMatrice( matrice );
      cout << setw(W) << "Melange de la matrice : " << matrice << endl;

      sortMatrice( matrice );
      cout << setw(W) << "Tri de la matrice selon max ligne : " << matrice << endl;

      cout << endl << endl << endl;
   }
   
   
   // Attente de l'appui sur ENTER pour quitter
   cout << "Presser ENTER pour quitter." << endl;
   while (getchar() != '\n');
   
   return EXIT_SUCCESS;
}