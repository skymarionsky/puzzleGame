#include<iostream>
using namespace std;

enum Etile{ W,E,G,O };

void initGame();
void getInput();
void updateGame();
void draw();
void checkMove(char c);

struct characterPosition{
	int x;
	int y;
}player;

int stage[5][8]={
	{W,W,W,W,W,W,W,W},
	{W,E,G,G,E,E,E,W},
	{W,E,O,E,E,O,E,W},
	{W,E,E,E,E,E,E,W},
	{W,W,W,W,W,W,W,W}};

const int stagesize_x = 8, stagesize_y = 5;
int objectLeft = 2;

int main(){

	initGame();

	//cout << "player.x=" << player.x << endl;


	while(1){
		getInput();
		updateGame();
		draw();
	}

	return 0;
}

void initGame()
{
	player.x = 4;
	player.y = 1;
	draw();
	return;
}

void getInput()
{
	char c;
	cout << "(w)(a)(s)(d)?" << endl;
	cin >> c;
	checkMove(c);
	//cout << "Input Character is " << c << endl;
	return;
}

void checkMove(char c)
{
	int mx=0,my=0;

	if(c=='w'){
		//move up
		my=-1;
	}else if(c=='a'){
		//move left
		mx=-1;
	}else if(c=='s'){
		//move down
		my=1;
	}else if(c=='d'){
		//move right
		mx=1;
	}

	int x = player.x + mx,
		y = player.y + my;
	
	switch(stage[y][x]){
	case W:
	case G:
		//cannot move to wall or goal
		break;
	case E:
		//move player
		player.x = x;
		player.y = y;
		break;
	case O:
		//move object
		int ox = x + mx;
		int oy = y + my;
		switch(stage[oy][ox]){
		case W:
			//cannot move object to wall
			break;
		case E:
			//move object to empty space
			player.x = x;
			player.y = y;
			stage[oy][ox] = O;
			stage[y][x] = E;
			break;
		case G:
			//move object to goal
			player.x = x;
			player.y = y;
			stage[oy][ox] = E;
			stage[y][x] = E;
			objectLeft--;
		}
	}

}

void updateGame()
{
	if(objectLeft==0){
		//game clear
		cout << "GAME COMPLETED!!";
	}
	return;
}

void draw()
{
	for( int y=0; y<stagesize_y; y++ ){
		for( int x=0; x<stagesize_x; x++ ){
			if(x==player.x && y == player.y){
				cout << "P";
			}else{
				cout << stage[y][x];
			}
		}
		cout << endl;
	}
	return;
}
