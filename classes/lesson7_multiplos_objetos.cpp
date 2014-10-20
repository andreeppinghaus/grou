/*******************
Allegro Newbie Tutorial

by
LoomSoft

http://loomsoft.net
email: jay@loomsoft.net
*******************/
/* Allegro Newbie Tutorial : Lesson 7 - Simple Sprite Animation
 *
 * This tutorial will just play a simple animation over and over again, 
 * regarless of what key you are pressing, or in what direction you are 
 * moving. It will keep playing even if you don't press anything.
 * To acheive different effects, you could create different variables to 
 * hold the states as to what direction the user is heading, or whether the 
 * user is even moving at all!
 */

/* This stuff should be pretty much memorized by now: */

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>



#include <allegro.h> // You must include the Allegro Header file
#include "Personagem.h"
//#include "Monstro.h"



/* Timer stuff */
volatile long speed_counter = 0; //A long integer which will store the value of the
								 //speed counter.

void increment_speed_counter() // A function to increment the speed counter
{
	speed_counter++; // This will just increment the speed counter by one.
}
END_OF_FUNCTION(increment_speed_counter);// Make sure you tell it that it's the end of the
										 // function


int main(int argc, char *argv[])
{
	allegro_init(); // Initialize Allegro
	install_keyboard(); // Initialize keyboard routines
	install_timer(); // Initialize the timer routines
	
	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's
	LOCK_FUNCTION(increment_speed_counter); //speed.
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60)); //Set our BPS
			
	set_color_depth(16); // Set the color depth
	set_gfx_mode(GFX_SAFE, 640,480,0,0); // Change our graphics mode to 640x480
			
	
	BITMAP *frame = load_bitmap("submarino.bmp", NULL); // Declare a bitmap and Load our picture in one single statement
	
	BITMAP *frame1 = load_bitmap("submarino-red.bmp", NULL); // Declare a bitmap and Load our picture in one single statement
	
//	BITMAP *frame2 = load_bitmap("salto2.bmp", NULL); // Declare a bitmap and Load our picture in one single statement
			
	/* This code is the same as in the previous lesson. Create the buffer, and location
	 * holders for the position of the frames.
	 */
	BITMAP *buffer = create_bitmap(640,480); // Declare and create an empty bitmap in one statment.
			
	
	/*
	 * CRIACAO dos personagens
	 */
	Personagem *monstro[5];
	for (int x=0; x<5;x++) {
		monstro[x] = new Personagem(monstro[x]->aleatorio(640),monstro[x]->aleatorio(480), frame1);
	}
	
	Personagem *heroi = new Personagem(0,0, frame);
	
	
	/* Here is a simple integer that we are going to increment on each logic loop,
	 * therefore it will be incremented at the speed of the speed counter, which 
	 * (in this program) is set at 60bps. That means when our frame_counter == 60,
	 * one full second has passed. Keep that in mind, as you will see how we use it later on.
	 */
	int frame_counter = 0;// A counter for which frame to draw
						
	/* This code stays the same as the previous lessons */
	while(!key[KEY_ESC])//If the user hits escape, quit the program
	{
		while(speed_counter > 0)
		{
			heroi->controle(key); //controle do teclado
			//heroi->gravidade(key); // aplicacao da gravidade
			
			for (int x=0; x<5;x++) {
			
				monstro[x]->posicao();
			}
						
			
			//teste de colisao só avisa se for colidir		
			if (monstro[0]->colisao(heroi)==TRUE) {
				textprintf_ex(buffer, font, 0,0, makecol(255,255,255), -1, "Collision!");
			}
			
			if (monstro[1]->colisao(heroi)==TRUE) {
				textprintf_ex(buffer, font, 0,0, makecol(255,255,255), -1, "Collision!");
			}
			
			
			speed_counter --;
								
			/* Increment our frame counter at the same speed of the speed counter. */
			frame_counter ++;
									
			/* Here we test to see if the frame counter is over 4 seconds. 
			 * If it is, we set it back to zero in order to restart the animation. We are only 
			 * testing for four seconds because we are only drawing 1 frame a second, and we're
			 * drawing a total of four frames. The next big chunk of explanation will clear 
			 * up any confusion regarding this. 
			 */
										
			if(frame_counter > 300) // 60 * 4 = 240 (When frame counter = 60, 1 second has passed)
			{
				frame_counter = 0;
			}
			
		} //Closing bracket for the while(speed_counter > 0) statment
												
		
		heroi->desenha(buffer); //imprime objeto
		
		for (int x=0; x<5;x++) {
			
				monstro[x]->desenha(buffer); //imprime objeto
			}
				
		/* End of the drawing portion -- same as the previous lesson's */
		blit(buffer, screen, 0,0,0,0,640,480); //Draw the buffer to the screen
		clear_bitmap(buffer);
	}
								
	/* Don't forget to destroy all the bitmaps we created, and do the rest of the deinitializing. */
	destroy_bitmap(frame); //Release the bitmap data
	destroy_bitmap(buffer); //Release the bitmap data 
											
	return(0); // Exit with no errors
}


END_OF_MAIN()

/*
#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Personagem
{
private:
	int velocidade;

	int forca;

	int g;

	int pos_x;

	int pos_y;


public:
	void baixo();

	void cima();

	void esquerda();

	void direita();

	void gravidade();

	void colisao();

	void posicao(volatile char key[]);

	virtual void desenha(BITMAP *buffer, BITMAP *frame[])=0;

};

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
}

void Personagem::direita()
{
    pos_x++;
}

void Personagem::gravidade()
{
}

void Personagem::colisao()
{
}

void Personagem::posicao(volatile char key[])
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
			
}
#endif

#endif
*/