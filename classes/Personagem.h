#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Personagem
{
public:
	int velocidade;

	int forca;

	int g;

	int pos_x;

	int pos_y;
        
        int invertido;
      
        Personagem *objeto_colisao;
        
        BITMAP *imagem;
        
        int _colisao;

        int colisao_esquerda;
        
        int colisao_direita;
        
        int colisao_topo;
        
        int colisao_base;

public:
        Personagem(int x, int y, BITMAP *frame);
        
	void baixo();

	void cima();

	void esquerda();

	void direita();

	void gravidade(volatile char key[]);
        
        void posicao();

	int colisao(Personagem *objeto);

	void controle(volatile char key[]);

	void desenha(BITMAP *buffer);
        
};
Personagem::Personagem(int x, int y,BITMAP *frame)
{

    this->pos_y=y;
    this->pos_x=x;
    this->imagem=frame;
    this->posicao();
    this->_colisao=FALSE;
    this->invertido=FALSE;
    
}

void Personagem::baixo()
{
    pos_y++;
}

void Personagem::cima()
{
    pos_y--;
}

void Personagem::esquerda()
{
    pos_x--;
    invertido=TRUE;
}

void Personagem::direita()
{
    pos_x++;
    invertido=FALSE;
}

void Personagem::gravidade(volatile char key[])
{
     if(key[KEY_UP])
    {
	this->cima();
    }else {
        this->baixo();
    }
    
}

void Personagem::posicao()
{
    this->colisao_esquerda = pos_x;
    this->colisao_topo=pos_y;
    this->colisao_direita = (this->colisao_esquerda +this->imagem->w );
    this->colisao_base = (this->colisao_topo +this->imagem->h );
    
}
int Personagem::colisao(Personagem *objeto)
{
    
    this->_colisao = TRUE; // Assume that there is no collision

    // NOTE: This could easily be concatenated into one big if statement across
			//	 four 'or' clauses -- but it's split up this way for easy reading
    if(this->colisao_base < objeto->colisao_topo)
    {
	this->_colisao = FALSE;
    }
    else if(this->colisao_topo > objeto->colisao_base)
    {
	this->_colisao = FALSE;
    }
    else if(this->colisao_direita < objeto->colisao_esquerda)
    {
        this->_colisao = FALSE;
    }
    else if(this->colisao_esquerda > objeto->colisao_direita)
    {
	this->_colisao = FALSE;
    }
    
    
    return this->_colisao;
}

void Personagem::controle(volatile char key[])
{
   if(key[KEY_RIGHT])
    {
	this->direita();
    }
    if(key[KEY_LEFT])
    {
	this->esquerda();
    }
    if(key[KEY_UP])
    {
	this->cima();
    }
    if(key[KEY_DOWN])
    {
	this->baixo();
    }
    
    this->posicao();
			
}

void Personagem::desenha(BITMAP *buffer)
{
    if (invertido==FALSE) {
        draw_sprite(buffer, this->imagem, this->pos_x, this->pos_y);//Draw the first frame
    }else {
        draw_sprite_h_flip(buffer, this->imagem, this->pos_x, this->pos_y);
    }
   
			
}


#endif
