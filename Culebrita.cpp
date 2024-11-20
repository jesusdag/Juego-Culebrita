#include <iostream>
#include <windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;

// constantes que determinaran el tablero de juego
const int W=20, H=20;
// array estructura de datos que almacena una serie de datos del mismo tipo, localizados por índices y separados por comas: Tipo_dato nombre_array[número_elementos]

//Creamos uno para la posicion de la culebra y uno para la de la comida del juego 
int headPos[2], foodPos[2];

//Creamos un vector para la posicion en x,y de la cola 
int tailPosX[100], tailPosY[100], tailLenght;

// variable para almacenar la puntuacion 
int score;

enum directionEnum {STOP = 0, LEFT, RIGHT, UP, DOWN};

directionEnum  snakeDirection ;

bool gameOver;


// Metodo para inicializar variables 
void init(){ 
system ("cls");
// sirve para limpiar la pantalla cuando inicie una partida  

headPos[0]= W/2;
headPos[1]= H/2;

//la funcion rand() genera valores aleatorios entre un rango definido por %
foodPos[0]= rand() % W;
foodPos[1]= rand () % H;

snakeDirection = STOP;

score=0;


gameOver= false;	
	
}	


// Metodo para renderizar todo en pantalla 
void render(){


SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
for(int i=0;i<W+2; i++){
	
	cout<<"#";
		
}	

cout<<endl;


// se crea un cliclo anidado para que podamos crear los bordes verticales, horizontales,
//cabeza de la serpiente y comida 
for (int i = 0; i < H ;i++)
{
	for (int j=0; j<W ;  j++ )
	{
		
		if(j==0)
			cout<<"#";				
	
		if(j==headPos[0] && i==headPos[1] )
			cout<<"O";			
			
		else if (j==foodPos[0] && i==foodPos[1]) 
			cout<<"*";
		
		else
		{
			bool printTail=false;
			
			for(int k=0; k<tailLenght;k++){
				
				if(tailPosX[k]==j && tailPosY[k]==i){
					
					cout<<"o";
					printTail= true;
				
				
				
				}
				
				
			}
			
			if(!printTail){
				cout<<" ";
			}
		
			
	    }
		
		if(j==W-1)
			cout<<"#";
			
			
		
	}
	cout<<endl; 
}

for(int i=0;i<H+2; i++){
	
	cout<<"#";
		
} 

cout<<endl<<endl;	
cout<<"Puntuacion: "<<score<<endl;
	
}


// Metodo para ingresar los datos por teclado
void input(){
	
	if(_kbhit())
	//La funcion getch nos va a servir para capturar caracteres desde el teclado 
	switch (_getch())
	{
		case 'a':
			snakeDirection=LEFT;
			break;
		case 's':
			snakeDirection=DOWN;
			Sleep(8);
			break;
		case 'd':
			snakeDirection=RIGHT;
			break;
		case 'w':
			snakeDirection=UP;
			Sleep(8);
			break;
		case 'q':
			gameOver= true;
			break;
			
			
		
		
	}
	
	
	
	
}


//Metodo para indicar la logica del juego 
void gameLogic(){
	
	int prevTailPosX=tailPosX[0];
	int prevTailPosY=tailPosY[0];
	
	int prevTailPosX2,prevTailPosY2;
	
	tailPosX[0]=headPos[0];
	tailPosY[0]=headPos[1];
	
	for(int i=1; i<tailLenght; i++){
		prevTailPosX2= tailPosX[i];
		prevTailPosY2= tailPosY[i];
		
		tailPosX[i] = prevTailPosX;
		tailPosY[i] = prevTailPosY;	
		
		prevTailPosX=prevTailPosX2;
		prevTailPosY=prevTailPosY2;	
		
	}
	
	
	 
	
	switch(snakeDirection)
	{
		case STOP:
			break;
		case LEFT:
			headPos[0]--;
			break;
		case RIGHT:
			headPos[0]++;
			break;
		case UP:
			headPos[1]--;
			break;
		case DOWN:
			headPos[1]++;
			break;	
		
		
	}
	
	//Si la posicion de la cabeza coincide con los muros se pierde 
	
	if(headPos[0]>=W || headPos[0]<0 || headPos[1]>=H || headPos[1]<0){
		gameOver=true;
		
		
	}
	
	
	for(int i=0;i<tailLenght;i++){
		if (tailPosX[i]==headPos[0] && tailPosY[i]==headPos[1] ){
			gameOver=true;
			
			
		}
		
	}
	
	
	// Si la cabeza coincide con la comida se aumenta la puntucion ademas de generar mas comida
	if(headPos[0]==foodPos[0] && headPos[1]==foodPos[1] ){
		score = score + 10;
		foodPos[0]= rand() % W;
		foodPos[1]= rand () % H;
		tailLenght++; //Aumenta la longitud 
		
	
	}
	
	
	
	
	
	
}
	
int main()
{
	

srand(time(0));
//srand para que la secuaencia no sea la misma 
init();

// Mientras gameOver sea Verdadero 
while(! gameOver)
{
	
	//LLamamos los metodos 
    render();
	input();
	gameLogic();
	Sleep(65);
	
	
	
	
	
}
cout<<"SE ACABO EL JUEGO";

}
