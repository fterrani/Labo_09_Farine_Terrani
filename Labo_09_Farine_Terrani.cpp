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
#include <vector>

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


int main()
{
   vector<vector<int>> m = {{1,2,3},{4,5,6}};
   
   
   vector<int> v = {1,2,3,4,5};
   
   
   
   cout << v << endl;
   
   return EXIT_SUCCESS;
}