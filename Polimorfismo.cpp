#include <cstdlib>
#include <iostream>
/*
* Compilador Dev C++
* Exemplo de Plimorfismo
* Autor: André Eppinghaus
* 
*/
using namespace std;
class Monstro {
public: 
        int velocidade, forca;
        
        void setVelocidade(int v) {
         this->velocidade = v;
        }
        void setForca(int f) {
         this->forca = f;
        }

        void  atacar(){
          cout << "\natacando " ;
          cout << "\nForca: "<<
               this->forca
               <<endl;
        }
};
      
class MVoador : public Monstro {
public:
       int asas;

     void voar(){     
          cout << "Voando Velocidade"<<
               this->velocidade
               <<endl;
      
      }
};
int main(int argc, char *argv[])
{
 Monstro *m= new Monstro();    
 MVoador *grou = new MVoador();
 m->setVelocidade(5);
 m->setForca(10);
 m->atacar();
 
 grou->setForca(100);
 grou->setVelocidade(200);
 grou->atacar();
 grou->voar();
m->atacar();
    system("PAUSE");
    return EXIT_SUCCESS;
}
