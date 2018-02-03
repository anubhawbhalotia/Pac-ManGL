#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#include<unistd.h> 

using namespace std;
#define HEIGHT 288
#define WIDTH 512
#define TILE 8
float frameRate=88;
float currTime;
float pacmanSpeed=(int)(0.8*frameRate);
int i,j,nextState,last[2],clearCounter=0;
float x,y;
int pacmanCentre[2],blinkyCentre[2],pinkyCentre[2],inkyCentre[2],clinkyCentre[2];
int board[][28]={
/* 00 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 01 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 02 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 03 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 04 */{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 05 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 06 */{0,3,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,3,0},
/* 07 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 08 */{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 09 */{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
/* 10 */{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
/* 11 */{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
/* 12 */{0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
/* 13 */{0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
/* 14 */{0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
/* 15 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 16 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 17 */{2,2,2,2,2,2,1,2,2,2,0,0,0,0,0,0,0,0,2,2,2,1,2,2,2,2,2,2},
/* 18 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 19 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 20 */{0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
/* 21 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 22 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 23 */{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 24 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 25 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 26 */{0,3,1,1,0,0,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,0,0,1,1,3,0},
/* 27 */{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
/* 28 */{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
/* 29 */{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
/* 30 */{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
/* 31 */{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
/* 32 */{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 33 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 34 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 35 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
queue <int> state;
int currState=1,pacmanShape=0;
int wallProgram, pacmanProgram,coinProgram,blinkyProgram,inkyProgram,pinkyProgram,clinkyProgram,referenceLineProgram,textProgram;
int currPacLoc[2],nextPacLoc[2],newPacCentre[2];
unsigned int vboReferenceLine[2][40],vaoReferenceLine[2][40],vaoWall,vboWall;
unsigned int vboPacmanStable,vaoPacmanStable,vaoPacmanRight,vboPacmanRight,vaoPacmanLeft,vboPacmanLeft;
unsigned int vaoGhost,vboGhost,vaoPacmanUp,vboPacmanUp,vaoPacmanDown,vboPacmanDown;
unsigned int vaoCoin[35][28],vboCoin[35][28];
unsigned int vaoCentreLine,vboCentreLine;
void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
	glViewport(0,0,width,height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(state.empty())
	{
		if(key==GLFW_KEY_UP&& action==GLFW_PRESS && currState!=0)
	{
		state.push(0);
	}
	else if(key==GLFW_KEY_LEFT&& action==GLFW_PRESS && currState!=1)
	{
		state.push(1);
	}
	else if(key==GLFW_KEY_DOWN&& action==GLFW_PRESS && currState!=2)
	{
		state.push(2);
	}
	else if(key==GLFW_KEY_RIGHT&& action==GLFW_PRESS && currState!=3)
	{
		state.push(3);
	}
	}
	else
	{
	
	if(key==GLFW_KEY_UP&& action==GLFW_PRESS && state.back()!=0)
	{
		state.push(0);
	}
	else if(key==GLFW_KEY_LEFT&& action==GLFW_PRESS && state.back()!=1)
	{
		state.push(1);
	}
	else if(key==GLFW_KEY_DOWN&& action==GLFW_PRESS && state.back()!=2)
	{
		state.push(2);
	}
	else if(key==GLFW_KEY_RIGHT&& action==GLFW_PRESS && state.back()!=3)
	{
		state.push(3);
	}
	}
	cout<<state.back()<<endl;

}
void attachPacman()
{
	//cout<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
	float vertices[]={
		
		-1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
		(-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,
		-1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
		(-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,
		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,
		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1])),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1])),0.0,
		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+1)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+1)),0.0,
		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+2)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+2)),0.0,
		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+3)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+3)),0.0,
		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,
		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,
		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,
		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
	};
	glBindVertexArray(vaoPacmanStable);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanStable);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanRight()
{
	
	float vertices[]={
		
		-1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
		(-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,

		-1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
		(-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,

		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-1)),0.0,

		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1])),0.0,
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1])),0.0,

		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+1)),0.0,
		-1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+1)),0.0,

		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+2)),0.0,
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+2)),0.0,

		-1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+3)),0.0,
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+3)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,

		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,

		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
	};

	glBindVertexArray(vaoPacmanRight);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanRight);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanLeft()
{
	cout<<"l"<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
	float vertices[]={
		
		-1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
		(-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,

		-1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
		(-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,
        
		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-1)),0.0,

		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1])),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1])),0.0,

		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+1)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+1)),0.0,

		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+2)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+2)),0.0,

		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+3)),0.0,
		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+3)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,

		-1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
		-1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,

		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,

		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
	};
	glBindVertexArray(vaoPacmanLeft);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanLeft);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanDown()
{
	//cout<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
	float vertices[]={
		
		-1+(x*(pacmanCentre[0]-6)),(1-(y*(pacmanCentre[1]-1))),0.0,
		(-1+(x*(pacmanCentre[0]-6))),(1-(y*(pacmanCentre[1]+2))),0.0,

		-1+(x*(pacmanCentre[0]-5)),(1-(y*(pacmanCentre[1]-3))),0.0,
		(-1+(x*(pacmanCentre[0]-5))),(1-(y*(pacmanCentre[1]+4))),0.0,

		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]-4)),0.0,
		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+5)),0.0,
//4
		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-4)),0.0,
		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+5)),0.0,
//5		
		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+3)),0.0,
//6
		-1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+1)),0.0,

//7		
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]-1)),0.0,
//8
		-1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]+1)),0.0,

	//9	
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+3)),0.0,

//10
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-4)),0.0,
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+5)),0.0,

		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]-4)),0.0,
		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+5)),0.0,

	
		-1+(x*(pacmanCentre[0]+5)),(1-(y*(pacmanCentre[1]-3))),0.0,
		(-1+(x*(pacmanCentre[0]+5))),(1-(y*(pacmanCentre[1]+4))),0.0,


		-1+(x*(pacmanCentre[0]+6)),(1-(y*(pacmanCentre[1]-1))),0.0,
		(-1+(x*(pacmanCentre[0]+6))),(1-(y*(pacmanCentre[1]+2))),0.0,
	};
	glBindVertexArray(vaoPacmanDown);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanDown);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanUp()
{
	float vertices[]={
		-1+(x*(pacmanCentre[0]-6)),(1-(y*(pacmanCentre[1]-1))),0.0,
		(-1+(x*(pacmanCentre[0]-6))),(1-(y*(pacmanCentre[1]+2))),0.0,

		-1+(x*(pacmanCentre[0]-5)),(1-(y*(pacmanCentre[1]-3))),0.0,
		(-1+(x*(pacmanCentre[0]-5))),(1-(y*(pacmanCentre[1]+4))),0.0,

		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+5)),0.0,
//4
		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+5)),0.0,
//5		
		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+5)),0.0,
//6
		-1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+5)),0.0,

//7		
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+1)),0.0,
		-1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+5)),0.0,
//8
		-1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]-1)),0.0,
		-1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]+5)),0.0,

	//9	
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]-3)),0.0,
		-1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+5)),0.0,  //edited a bit

//10
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+5)),0.0,

		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]-5)),0.0,
		-1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+4)),0.0,

	
		-1+(x*(pacmanCentre[0]+5)),(1-(y*(pacmanCentre[1]-4))),0.0,
		(-1+(x*(pacmanCentre[0]+5))),(1-(y*(pacmanCentre[1]+3))),0.0,


		-1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-2)),0.0,
		(-1+(x*(pacmanCentre[0]+6))),(1-(y*(pacmanCentre[1]+2))),0.0,
	};
	glBindVertexArray(vaoPacmanUp);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanUp);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}	

void attachGhost(int ghostCentre[])
{
	float vertices[]={
		-1+(x*(ghostCentre[0]-6)),1-(y*(ghostCentre[1]-0)),0.0,-1+(x*(ghostCentre[0]-6)),1-(y*(ghostCentre[1]+7)),0.0,
		-1+(x*(ghostCentre[0]-5)),1-(y*(ghostCentre[1]-3)),0.0,-1+(x*(ghostCentre[0]-5)),1-(y*(ghostCentre[1]+6)),0.0,
		-1+(x*(ghostCentre[0]-4)),1-(y*(ghostCentre[1]-4)),0.0,-1+(x*(ghostCentre[0]-4)),1-(y*(ghostCentre[1]+5)),0.0,
		-1+(x*(ghostCentre[0]-3)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]-3)),1-(y*(ghostCentre[1]+6)),0.0,
		-1+(x*(ghostCentre[0]-2)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]-2)),1-(y*(ghostCentre[1]+7)),0.0,
		-1+(x*(ghostCentre[0]-1)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]-1)),1-(y*(ghostCentre[1]+7)),0.0,
		-1+(x*(ghostCentre[0]-0)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]-0)),1-(y*(ghostCentre[1]+5)),0.0,
		-1+(x*(ghostCentre[0]+1)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]+1)),1-(y*(ghostCentre[1]+5)),0.0,
		-1+(x*(ghostCentre[0]+2)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]+2)),1-(y*(ghostCentre[1]+7)),0.0,
		-1+(x*(ghostCentre[0]+3)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]+3)),1-(y*(ghostCentre[1]+7)),0.0,
		-1+(x*(ghostCentre[0]+4)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]+4)),1-(y*(ghostCentre[1]+6)),0.0,
		-1+(x*(ghostCentre[0]+5)),1-(y*(ghostCentre[1]-4)),0.0,-1+(x*(ghostCentre[0]+5)),1-(y*(ghostCentre[1]+5)),0.0,
		-1+(x*(ghostCentre[0]+6)),1-(y*(ghostCentre[1]-3)),0.0,-1+(x*(ghostCentre[0]+6)),1-(y*(ghostCentre[1]+6)),0.0,
		-1+(x*(ghostCentre[0]+7)),1-(y*(ghostCentre[1]-0)),0.0,-1+(x*(ghostCentre[0]+7)),1-(y*(ghostCentre[1]+7)),0.0,
	};
	glBindVertexArray(vaoGhost);
    glBindBuffer(GL_ARRAY_BUFFER,vboGhost);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void attachReferenceLines()
{ 
	for(i=0;i<288;i+=8)
    {
    	float vertices[]=
    	{
    		(-1+(x*144)),(1-(y*i)),0.0,
    		(-1+(x*368)),(1-(y*i)),0.0
    	};
    	glBindVertexArray(vaoReferenceLine[0][(i+1)/8]);
    	glBindBuffer(GL_ARRAY_BUFFER,vboReferenceLine[0][(i+1)/8]);
    	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
    	glBindVertexArray(0); 
    }
    for(i=144;i<368;i+=8)
    {
    	float vertices[]=
    	{
    		-1+(x*i),-1.0,0.0,
    		-1+(x*i),1.0,0.0
    	};
    	glBindVertexArray(vaoReferenceLine[1][(i-144)/8]);
    	glBindBuffer(GL_ARRAY_BUFFER,vboReferenceLine[1][(i-144)/8]);
    	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
    	glBindVertexArray(0); 
    }
}
void attachCoins()
{
	for(i=0;i<35;i++)
	{
		for(j=0;j<28;j++)
		{
			if(board[i][j]==1)
			{
				float vertices[]={
					-1+(x*((j*8)+144+3)),1-(y*((i*8)+5)),0.0,
					-1+(x*((j*8)+144+6)),1-(y*((i*8)+5)),0.0,
				};
				glBindVertexArray(vaoCoin[i][j]);
				glBindBuffer(GL_ARRAY_BUFFER,vboCoin[i][j]);
				glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    			glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0); 
    			glBindVertexArray(0);
			}
		}
	}
}

void drawCoins()
{
	for(i=0;i<35;i++)
	{
		for(j=0;j<28;j++)
		{
			if(board[i][j]==1)
			{
				glUseProgram(coinProgram);
				glBindVertexArray(vaoCoin[i][j]);
				glLineWidth(10);
				glDrawArrays(GL_LINES,0,100);
			}
		}
	}
}
void drawWall()
{
    glUseProgram(wallProgram);
    glBindVertexArray(vaoWall);
    glLineWidth(2.0);
    glDrawArrays(GL_LINES,0,2000);
    glUseProgram(pinkyProgram);
    glBindVertexArray(vaoCentreLine);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawReferenceLines()
{
	for(j=0;j<2;j++)
    	{
	    	for(i=0;i<36;i++)
	    	{
    			glUseProgram(referenceLineProgram);
    			glBindVertexArray(vaoReferenceLine[j][i]);
    			glLineWidth(0.5);
    			glDrawArrays(GL_LINES,0,4);
    			
    		}
    	}
}

void drawPacman()
{
	glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanStable);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanRight()
{
	glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanRight);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanLeft()
{
	glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanLeft);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanUp()
{
	glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanUp);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanDown()
{
	glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanDown);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawGhost(int shader)
{
	glUseProgram(shader);
    glBindVertexArray(vaoGhost);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
	
}
void attachWall()
{
    float vertices[] = {
                  -0.421875f, 0.833333f, 0.0f,  
         0.421875, 0.833333f, 0.0f, 
         -0.429688f, 0.826389f, 0.0f,  
         -0.421875, 0.826389f, 0.0f, 
          0.421875, 0.826389f, 0.0f,
            0.429688, 0.826389f, 0.0f, 
             -0.433594, 0.819444f, 0.0f,
              -0.433594, 0.805556f, 0.0f,
               0.433594, 0.819444f, 0.0f,
                0.433594,0.805556f, 0.0f, 
                 -0.421875,0.805556, 0.0f,
                 -0.421875,0.798611, 0.0f,
                 0.421875,0.805556, 0.0f, 
                 0.421875,0.798611, 0.0f, 
                 -0.4375,0.805556,   0.0f,
                 -0.4375,0.305556, 0.0f,  
 0.4375,0.805556,   0.0f,
                 0.4375,0.305556, 0.0f, 
                 -0.425781,0.798611,   0.0f,
                 -0.425781,0.3125, 0.0f,  
  0.425781,0.798611,   0.0f,
                 0.425781,0.3125, 0.0f,
                  -0.417969,0.8125  ,   0.0f,
                 -0.0195312,0.8125, 0.0f,  
0.417969,0.8125,   0.0f,
                 0.0195312,0.8125, 0.0f,  
                  -0.0195312,0.798611  ,   0.0f,
                 -0.0195312,0.805556, 0.0f,  

0.0195312,0.798611  ,   0.0f,
                 0.0195312,0.805556, 0.0f,  
                  -0.015625,0.798611  ,   0.0f,
                 -0.015625,0.597222, 0.0f,

                  0.015625,0.798611  ,   0.0f,
                 0.015625,0.597222, 0.0f,  
                    -0.351562,0.694444  ,   0.0f,
                 -0.273438,0.694444, 0.0f,
                 0.351562,0.694444  ,   0.0f,
                 0.273438,0.694444, 0.0f,
                 -0.195312,0.694444  ,   0.0f,
                 -0.0859375,0.694444, 0.0f,
                 0.195312,0.694444  ,   0.0f,
                 0.0859375,0.694444, 0.0f,
                -0.355469,0.6875  ,   0.0f,
                 -0.355469,0.680556, 0.0f,
0.355469,0.6875  ,   0.0f,
                 0.355469,0.680556, 0.0f,
                 -0.273438,0.6875  ,   0.0f,
                 -0.273438,0.680556, 0.0f,

                 0.273438,0.6875  ,   0.0f,
                 0.273438,0.680556, 0.0f,

                 -0.199219,0.6875  ,   0.0f,
                 -0.199219,0.680556, 0.0f,

                 0.199219,0.6875  ,   0.0f,
                 0.199219,0.680556, 0.0f,

                 -0.0859375,0.6875  ,   0.0f,
                 -0.0859375,0.680556, 0.0f,
                 0.0859375,0.6875  ,   0.0f,
                 0.0859375,0.680556, 0.0f,
-0.359375,0.680556  ,   0.0f,
                 -0.359375,0.597222, 0.0f,

0.359375,0.680556  ,   0.0f,
                 0.359375,0.597222, 0.0f,

-0.269531,0.680556  ,   0.0f,
                 -0.269531,0.597222, 0.0f,

0.269531,0.680556  ,   0.0f,
                 0.269531,0.597222, 0.0f,

-0.203125,0.680556  ,   0.0f,
                 -0.203125,0.597222, 0.0f,
0.203125,0.680556  ,   0.0f,
                 0.203125,0.597222, 0.0f,
                 -0.0820312,0.680556  ,   0.0f,
                 -0.0820312,0.597222, 0.0f,
                 0.203125,0.680556  ,   0.0f,
                 0.203125,0.597222, 0.0f,
                 -0.355469,0.597222  ,   0.0f,
                 -0.355469,0.590278, 0.0f,
                 0.355469,0.597222  ,   0.0f,
                 0.355469,0.590278, 0.0f,
                 -0.273438,0.597222  ,   0.0f,
                 -0.273438,0.590278, 0.0f,

                 0.273438,0.597222  ,   0.0f,
                 0.273438,0.590278, 0.0f,

                 -0.199219,0.597222  ,   0.0f,
                 -0.199219,0.590278, 0.0f,
0.199219,0.597222  ,   0.0f,
                 0.199219,0.590278, 0.0f,
                 -0.0859375,0.597222  ,   0.0f,
                 -0.0859375,0.590278, 0.0f,

                 0.0859375,0.597222  ,   0.0f,
                 0.0859375,0.590278, 0.0f,

                 -0.0117188,0.597222  ,   0.0f,
                 -0.0117188,0.590278, 0.0f,
0.0117188,0.597222  ,   0.0f,
                 0.0117188,0.590278, 0.0f,
-0.351562,0.590278  ,   0.0f,
                 -0.273438,0.590278, 0.0f,
                 0.0117188,0.597222  ,   0.0f,
                 0.0117188,0.590278, 0.0f,
-0.195312,0.590278  ,   0.0f,
                 -0.0859375,0.590278, 0.0f,
                 0.195312,0.590278  ,   0.0f,
                 0.0859375,0.590278, 0.0f,
                 -0.0859375,0.590278  ,   0.0f,
                 -0.0859375,0.583333, 0.0f,
                   0.0859375,0.590278  ,   0.0f,
                 0.0859375,0.583333, 0.0f,
  -0.351562 ,0.472222  ,   0.0f,
                 -0.273438,0.472222, 0.0f,

  0.351562 ,0.472222  ,   0.0f,
                 0.273438,0.472222, 0.0f,

  -0.195312 ,0.472222  ,   0.0f,
                 -0.179688,0.472222, 0.0f,

  0.195312 ,0.472222  ,   0.0f,
                 0.179688,0.472222, 0.0f,

  -0.101562 ,0.472222  ,   0.0f,
                 0.101562,0.472222, 0.0f,

  -0.355469 ,0.465278  ,   0.0f,
                 -0.355469,0.458333, 0.0f,
                 0.355469 ,0.465278  ,   0.0f,
                 0.355469,0.458333, 0.0f,
                 -0.273438 ,0.465278  ,   0.0f,
                 -0.273438,0.458333, 0.0f,

                 0.273438 ,0.465278  ,   0.0f,
                 0.273438,0.458333, 0.0f,

                 -0.199219 ,0.465278  ,   0.0f,
                 -0.199219,0.458333, 0.0f,

                 0.199219 ,0.465278  ,   0.0f,
                 0.199219,0.458333, 0.0f,

                 -0.179688 ,0.465278  ,   0.0f,
                 -0.179688,0.458333, 0.0f,

                 0.199219 ,0.465278  ,   0.0f,
                 0.199219,0.458333, 0.0f,

                 -0.105469 ,0.465278  ,   0.0f,
                 -0.105469,0.458333, 0.0f,
                 0.105469 ,0.465278  ,   0.0f,
                 0.105469,0.458333, 0.0f,
                 -0.359375 ,0.458333  ,   0.0f,
                 -0.359375,0.430556, 0.0f,

                 0.359375 ,0.458333  ,   0.0f,
                 0.359375,0.430556, 0.0f,

                 -0.269531 ,0.458333  ,   0.0f,
                 -0.269531,0.430556, 0.0f,

                 0.269531 ,0.458333  ,   0.0f,
                 0.269531,0.430556, 0.0f,

                 -0.203125 ,0.458333  ,   0.0f,
                 -0.203125,0.0972222, 0.0f,
                  0.203125 ,0.458333  ,   0.0f,
                 0.203125,0.0972222, 0.0f,
                  -0.175781 ,0.458333  ,   0.0f,
                 -0.175781,0.3125, 0.0f,
0.175781 ,0.458333  ,   0.0f,
                 0.175781,0.3125, 0.0f,
                 -0.109375 ,0.458333  ,   0.0f,
                 -0.109375,0.430556, 0.0f,
                 0.109375 ,0.458333  ,   0.0f,
                 0.109375,0.430556, 0.0f,
                 -0.355469 ,0.430556  ,   0.0f,
                 -0.355469,0.423611, 0.0f,
                  0.355469 ,0.430556  ,   0.0f,
                 0.355469,0.423611, 0.0f,
 -0.273438 ,0.430556  ,   0.0f,
                 -0.273438,0.423611, 0.0f,
                 0.273438 ,0.430556  ,   0.0f,
                 0.273438,0.423611, 0.0f,
                 -0.105469 ,0.430556  ,   0.0f,
                 -0.105469,0.423611, 0.0f,
                 0.105469 ,0.430556  ,   0.0f,
                 0.105469,0.423611, 0.0f,
-0.351562 ,0.423611  ,   0.0f,
                 -0.273438,0.423611, 0.0f,
                 0.351562 ,0.423611  ,   0.0f,
                 0.273438,0.423611, 0.0f,
                 -0.0195312 ,0.416667  ,   0.0f,
                 -0.0195312,0.409722, 0.0f,
0.0195312 ,0.416667  ,   0.0f,
                 0.0195312,0.409722, 0.0f,
                 -0.015625 ,0.409722  ,   0.0f,
                 -0.015625,0.263889, 0.0f,
 0.015625 ,0.409722  ,   0.0f,
                 0.015625,0.263889, 0.0f,
                  -0.421875 ,0.3125  ,   0.0f,
                 -0.421875,0.305556, 0.0f,
                 0.421875 ,0.3125  ,   0.0f,
                 0.421875,0.305556, 0.0f,
                 -0.171875 ,0.3125  ,   0.0f,
                 -0.171875,0.305556, 0.0f,
                 0.171875 ,0.3125  ,   0.0f,
                 0.171875,0.305556, 0.0f,
                 -0.433594 ,0.305556  ,   0.0f,
                 -0.433594,0.291667, 0.0f,
                 0.433594 ,0.305556  ,   0.0f,
                 0.433594,0.291667, 0.0f,
-0.417969 ,0.305556  ,   0.0f,
                 -0.273438,0.305556, 0.0f,
                 0.417969 ,0.305556  ,   0.0f,
                 0.273438,0.305556, 0.0f,
-0.167969 ,0.305556  ,   0.0f,
                 -0.0859375,0.305556, 0.0f,
                 0.167969 ,0.305556  ,   0.0f,
                 0.0859375,0.305556, 0.0f,
                 -0.273438 ,0.298611  ,   0.0f,
                 -0.273438,0.291667, 0.0f,
                  0.273438 ,0.298611  ,   0.0f,
                 0.273438,0.291667, 0.0f,
                  -0.0859375 ,0.298611  ,   0.0f,
                 -0.0859375,0.291667, 0.0f,
                  0.0859375 ,0.298611  ,   0.0f,
                 0.0859375,0.291667, 0.0f,
                  -0.0820312 ,0.298611  ,   0.0f,
                 -0.0820312,0.291667, 0.0f,
                        0.0820312 ,0.298611  ,   0.0f,
                 0.0820312,0.291667, 0.0f,
       -0.269531 ,0.298611  ,   0.0f,
                 -0.269531,0.291667, 0.0f,
                  0.269531 ,0.298611  ,   0.0f,
                 0.269531,0.291667, 0.0f,
 -0.429688 ,0.291667  ,   0.0f,
                 -0.421875,0.291667, 0.0f,
                 0.429688 ,0.291667  ,   0.0f,
                 0.421875,0.291667, 0.0f,
                 -0.269531 ,0.291667  ,   0.0f,
                 -0.269531,0.0972222, 0.0f,
0.269531 ,0.291667  ,   0.0f,
                 0.269531,0.0972222, 0.0f,
                 -0.0820312 ,0.291667  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
                    0.0820312 ,0.291667  ,   0.0f,
                 0.0820312,0.263889, 0.0f,
    -0.0820312 ,0.291667  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
                 0.0820312 ,0.291667  ,   0.0f,
                 0.0820312,0.263889, 0.0f,
                 -0.421875 ,0.284722  ,   0.0f,
                 -0.28125,0.284722, 0.0f,

                 0.421875 ,0.284722  ,   0.0f,
                 0.28125,0.284722, 0.0f,

                 -0.0859375 ,0.590278  ,   0.0f,
                 -0.0859375,0.583333, 0.0f,
                 0.0859375 ,0.590278  ,   0.0f,
                 0.0859375,0.583333, 0.0f,
                 
-0.0078125 ,0.590278  ,   0.0f,
                 0.0078125,0.590278, 0.0f,
                -0.101562 ,0.472222  ,   0.0f,
                 0.101562,0.472222, 0.0f,
                 0.0820312 ,0.680556  ,   0.0f,
                 0.0820312,0.597222, 0.0f,
 -0.351562 ,0.590278  ,   0.0f,
                 -0.273438,0.590278, 0.0f,
                 0.351562 ,0.590278  ,   0.0f,
                 0.273438,0.590278, 0.0f,
                 -0.101562 ,0.423611  ,   0.0f,
                 -0.0195312,0.423611, 0.0f,
                   0.101562 ,0.423611  ,   0.0f,
                 0.0195312,0.423611, 0.0f,
                 -0.28125 ,0.277778  ,   0.0f,
                 -0.28125,0.111111, 0.0f,
 
                 0.28125 ,0.277778  ,   0.0f,
                 0.28125,0.111111, 0.0f,
  
                 -0.0859375 ,0.263889  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
  
                 0.0859375 ,0.263889  ,   0.0f,
                 0.0820312,0.263889, 0.0f,

                 -0.0117188 ,0.263889  ,   0.0f,
                 -0.0078125,0.263889, 0.0f,
 
0.0117188 ,0.263889  ,   0.0f,
                 0.0078125,0.263889, 0.0f,
                 -0.167969 ,0.256944  ,   0.0f,
                 -0.0859375,0.256944, 0.0f,
                 0.167969 ,0.256944  ,   0.0f,
                 0.0859375,0.256944, 0.0f,
                 -0.0078125 ,0.256944  ,   0.0f,
                 0.0078125,0.256944, 0.0f,
                 -0.171875 ,0.25  ,   0.0f,
                 -0.167969,0.25, 0.0f,
                 0.171875 ,0.25  ,   0.0f,
                 0.167969,0.25, 0.0f, 
                                  -0.175781 ,0.243056  ,   0.0f,
                 -0.175781,0.0972222, 0.0f,
                  0.171875 ,0.25  ,   0.0f,
                 0.167969,0.25, 0.0f,
                   -0.109375 ,0.138889  ,   0.0f,
                 -0.109375,-0.0833333, 0.0f,
0.109375 ,0.138889  ,   0.0f,
                 0.109375,-0.0833333, 0.0f, 
-0.0976562 ,0.118056  ,   0.0f,
                 -0.03125,0.118056, 0.0f,

0.0976562 ,0.118056  ,   0.0f,
                 0.03125,0.118056, 0.0f,


-0.0351562 ,0.138889  ,   0.0f,
                 -0.0351562,0.111111, 0.0f,
                 0.0351562 ,0.138889  ,   0.0f,
                 0.0351562,0.111111, 0.0f,
-0.0976562 ,-0.0625  ,   0.0f,
                 0.0976562,-0.0625, 0.0f,
-0.109375 ,-0.0833333  ,   0.0f,
                 0.109375,-0.0833333, 0.0f,
                 -0.0976562 ,   0.118056  ,   0.0f,
                 -0.0976562,-0.0625, 0.0f,
 0.0976562 ,   0.118056  ,   0.0f,
                 0.0976562,-0.0625, 0.0f,
                 -0.109375 ,   0.138889  ,   0.0f,
                 -0.03125,0.138889, 0.0f,
0.109375 ,   0.138889  ,   0.0f,
                 0.03125,0.138889, 0.0f,
                 -0.4375 ,   0.111111  ,   0.0f,
                 -0.28125,0.111111, 0.0f,
                 0.4375 ,   0.111111  ,   0.0f,
                 0.28125,0.111111, 0.0f,
-0.273438 ,   0.0972222  ,   0.0f,
                 -0.269531,0.0972222, 0.0f,

0.273438 ,   0.0972222  ,   0.0f,
                 0.269531,0.0972222, 0.0f,
-0.199219 ,   0.0972222  ,   0.0f,
                 -0.195312,0.0972222, 0.0f,

0.199219 ,   0.0972222  ,   0.0f,
                 0.195312,0.0972222, 0.0f,

-0.179688 ,   0.0972222  ,   0.0f,
                 -0.175781,0.0972222, 0.0f,
                 0.179688 ,   0.0972222  ,   0.0f,
                 0.175781,0.0972222, 0.0f,
                 -0.4375 ,   0.0902778  ,   0.0f,
                 -0.273438,0.0902778, 0.0f,
                 0.4375 ,   0.0902778  ,   0.0f,
                 0.273438,0.0902778, 0.0f,
                 -0.195312 ,   0.0902778  ,   0.0f,
                 -0.179688,0.0902778, 0.0f, 
               0.195312 ,   0.0902778  ,   0.0f,
                 0.179688,0.0902778, 0.0f, 
                 -0.4375 ,   -0.0277778  ,   0.0f,
                 -0.273438,-0.0277778, 0.0f, 
0.4375 ,   -0.0277778  ,   0.0f,
                 0.273438,-0.0277778, 0.0f, 
               -0.195312 ,   -0.0277778  ,   0.0f,
                 -0.179688,-0.0277778, 0.0f, 

               0.195312 ,   -0.0277778  ,   0.0f,
                 0.179688,-0.0277778, 0.0f,

               -0.273438 ,   -0.0347222  ,   0.0f,
                 -0.269531,-0.0347222, 0.0f,

               0.273438 ,   -0.0347222  ,   0.0f,
                 0.269531,-0.0347222, 0.0f, 

               -0.199219 ,   -0.0347222  ,   0.0f,
                 -0.195312,-0.0347222, 0.0f,

               0.199219 ,   -0.0347222  ,   0.0f,
                 0.195312,-0.0347222, 0.0f,

               -0.179688 ,   -0.0347222  ,   0.0f,
                 -0.175781,-0.0347222, 0.0f,

               0.179688 ,   -0.0347222  ,   0.0f,
                 0.175781,-0.0347222, 0.0f,

               -0.269531 ,   -0.0416667  ,   0.0f,
                 -0.269531,-0.236111, 0.0f,
                   0.269531 ,   -0.0416667  ,   0.0f,
                 0.269531,-0.236111, 0.0f,              
  -0.203125 ,   -0.0416667  ,   0.0f,
                 -0.203125,-0.236111, 0.0f,
                 0.203125 ,   -0.0416667  ,   0.0f,
                 0.203125,-0.236111, 0.0f,
-0.175781 ,   -0.0416667  ,   0.0f,
                 -0.175781,-0.236111, 0.0f,
                 0.175781 ,   -0.0416667  ,   0.0f,
                 0.175781,-0.236111, 0.0f,
                 -0.4375 ,   -0.0416667  ,   0.0f,
                 -0.28125,-0.0416667, 0.0f,

                 0.4375 ,   -0.0416667  ,   0.0f,
                 0.28125,-0.0416667, 0.0f,

                 -0.28125 ,   -0.0555556  ,   0.0f,
                 -0.28125,-0.222222, 0.0f,

                 0.28125 ,   -0.0555556  ,   0.0f,
                 0.28125,-0.222222, 0.0f,

                 -0.421875 ,   -0.222222  ,   0.0f,
                 -0.28125,-0.222222, 0.0f,
                 0.421875 ,   -0.222222  ,   0.0f,
                 0.28125,-0.222222, 0.0f,
                 -0.429688 ,   -0.229167  ,   0.0f,
                 -0.421875,-0.229167, 0.0f,
                   0.429688 ,   -0.229167  ,   0.0f,
                 0.421875,-0.229167, 0.0f,
                   -0.433594 ,   -0.236111  ,   0.0f,
                 -0.433594,-0.25, 0.0f,

                   0.433594 ,   -0.236111  ,   0.0f,
                 0.433594,-0.25, 0.0f,

                   -0.273438 ,   -0.236111  ,   0.0f,
                 -0.273438,-0.243056, 0.0f,

                   0.273438 ,   -0.236111  ,   0.0f,
                 0.273438,-0.243056, 0.0f,

                   -0.199219 ,   -0.236111  ,   0.0f,
                 -0.199219,-0.243056, 0.0f,

                   0.199219 ,   -0.236111  ,   0.0f,
                 0.199219,-0.243056, 0.0f,

                   -0.179688 ,   -0.236111  ,   0.0f,
                 -0.179688,-0.243056, 0.0f,

                   0.179688 ,   -0.236111  ,   0.0f,
                 0.179688,-0.243056, 0.0f,

                   -0.417969 ,   -0.243056  ,   0.0f,
                 -0.273438,-0.243056, 0.0f,
                 0.417969 ,   -0.243056  ,   0.0f,
                 0.273438,-0.243056, 0.0f,
                 -0.195312 ,   -0.243056  ,   0.0f,
                 -0.179688,-0.243056, 0.0f,
 0.195312 ,   -0.243056  ,   0.0f,
                 0.179688,-0.243056, 0.0f,
                  -0.101562 ,   -0.194444  ,   0.0f,
                 -0.0,-0.194444, 0.0f,
                 0.101562 ,   -0.194444  ,   0.0f,
                 0.0,-0.194444, 0.0f,
-0.105469 ,   -0.201389  ,   0.0f,
                 -0.105469,-0.208333, 0.0f,
                 0.105469 ,   -0.201389  ,   0.0f,
                 0.105469,-0.208333, 0.0f,
                 -0.109375 ,   -0.208333  ,   0.0f,
                 -0.109375,-0.236111, 0.0f,
0.109375 ,   -0.208333  ,   0.0f,
                 0.109375,-0.236111, 0.0f,
-0.105469 ,   -0.236111  ,   0.0f,
                 -0.101562,-0.236111, 0.0f,
                 0.105469 ,   -0.236111  ,   0.0f,
                 0.101562,-0.236111, 0.0f,
                 -0.101562 ,   -0.243056  ,   0.0f,
                 -0.0195312,-0.243056, 0.0f,
       0.101562 ,   -0.243056  ,   0.0f,
                 0.0195312,-0.243056, 0.0f,
                 -0.0195312 ,   -0.25  ,   0.0f,
                 -0.0195312,-0.25, 0.0f,
                  0.0195312 ,   -0.25  ,   0.0f,
                 0.0195312,-0.25, 0.0f,
                            -0.015625 ,   -0.256944  ,   0.0f,
                 -0.015625,-0.402778, 0.0f,
 0.015625 ,   -0.256944  ,   0.0f,
                 0.015625,-0.402778, 0.0f,
                  -0.0117188 ,   -0.402778  ,   0.0f,
                 -0.0078125,-0.402778, 0.0f,
                  0.015625 ,   -0.256944  ,   0.0f,
                 0.015625,-0.402778, 0.0f,
                  -0.0078125 ,   -0.409722  ,   0.0f,
                 -0.0,-0.409722, 0.0f,
                0.0078125 ,   -0.409722  ,   0.0f,
                 0.0,-0.409722, 0.0f,
                 -0.4375 ,   -0.25  ,   0.0f,
                 -0.4375,-0.861111, 0.0f,
                 0.4375 ,   -0.25  ,   0.0f,
                 0.4375,-0.861111, 0.0f,
                 -0.425781 ,   -0.256944  ,   0.0f,
                 -0.425781,-0.520833, 0.0f,
                 0.425781 ,   -0.256944  ,   0.0f,
                 0.425781,-0.520833, 0.0f,
-0.351562  , -0.361111,0.0f,
                 -0.273438,-0.361111, 0.0f,
                 0.351562  , -0.361111,0.0f,
                 0.273438,-0.361111, 0.0f,
-0.195312 ,  -0.361111,0.0f,
                 -0.0859375,-0.361111, 0.0f,
                 0.195312  , -0.361111,0.0f,
                 0.0859375,-0.361111, 0.0f,
                 -0.355469 ,  -0.368056,0.0f,
                 -0.351562,-0.368056, 0.0f,
                 0.355469 ,  -0.368056,0.0f,
                 0.351562,-0.368056, 0.0f,
                 -0.273438 ,  -0.368056,0.0f,
                 -0.269531,-0.368056, 0.0f,

                 0.273438 ,  -0.368056,0.0f,
                 0.269531,-0.368056, 0.0f,

                 -0.199219  , -0.368056,0.0f,
                 -0.195312,-0.368056, 0.0f,
                 0.199219 ,  -0.368056,0.0f,
                 0.195312,-0.368056, 0.0f,
                 -0.0859375  , -0.368056,0.0f,
                 -0.0820312,-0.368056, 0.0f, 
                 0.0859375  , -0.368056,0.0f,
                 0.0820312,-0.368056, 0.0f,
                                  -0.359375  , -0.375,0.0f,
                 -0.359375,-0.402778, 0.0f, 
 0.359375 ,  -0.375,0.0f,
                 0.359375,-0.402778, 0.0f,  
 -0.269531  , -0.375,0.0f,
                 -0.269531,-0.569444, 0.0f,

 0.269531  , -0.375,0.0f,
                 0.269531,-0.569444, 0.0f,

 -0.203125  , -0.375,0.0f,
                 -0.203125,-0.402778, 0.0f, 

 0.203125  , -0.375,0.0f,
                 0.203125,-0.402778, 0.0f,

 -0.0820312  , -0.375,0.0f,
                 -0.0820312,-0.402778, 0.0f,
                  0.0820312 ,  -0.375,0.0f,
                 0.0820312,-0.402778, 0.0f,
                  -0.355469  , -0.402778,0.0f,
                 -0.351562,-0.402778, 0.0f,
0.355469  , -0.402778,0.0f,
                 0.351562,-0.402778, 0.0f,
-0.199219  , -0.402778,0.0f,
                 -0.195312,-0.402778, 0.0f,
                 0.199219  , -0.402778,0.0f,
                 0.195312,-0.402778, 0.0f,
                 -0.0859375  , -0.402778,0.0f,
                 -0.0820312,-0.402778, 0.0f,
                 0.0859375  , -0.402778,0.0f,
                 0.0820312,-0.402778, 0.0f,
-0.351562  , -0.409722,0.0f,
                 -0.300781,-0.409722, 0.0f,
                 0.351562  , -0.409722,0.0f,
                 0.300781,-0.409722, 0.0f,
                 -0.195312  , -0.409722,0.0f,
                 -0.0859375,-0.409722, 0.0f,
 0.195312  , -0.409722,0.0f,
                 0.0859375,-0.409722, 0.0f,
 -0.300781  , -0.416667,0.0f,
                 -0.296875,-0.409722, 0.0f,
                 0.300781  , -0.416667,0.0f,
                 0.296875,-0.409722, 0.0f,
                 -0.296875  , -0.423611,0.0f,
                 -0.296875,-0.569444, 0.0f,
                 0.296875  , -0.423611,0.0f,
                 0.296875,-0.569444, 0.0f,
-0.421875  , -0.520833,0.0f,
                 -0.417969,-0.520833, 0.0f,
                 0.296875  , -0.423611,0.0f,
                 0.296875,-0.569444, 0.0f,
                 -0.417969  , -0.527778,0.0f,
                 -0.367188,-0.527778, 0.0f,
                 0.417969  , -0.527778,0.0f,
                 0.367188,-0.527778, 0.0f,  
                 -0.195312  , -0.527778,0.0f,
                 -0.179688,-0.527778, 0.0f,

                 0.195312  , -0.527778,0.0f,
                 0.179688,-0.527778, 0.0f,

                 -0.101562  , -0.527778,0.0f,
                 -0.0,-0.527778, 0.0f, 
                 0.101562  , -0.527778,0.0f,
                 0.0,-0.527778, 0.0f, 
                 -0.367188  , -0.534722,0.0f,
                 -0.363281,-0.534722, 0.0f,              

                 0.367188  , -0.534722,0.0f,
                 0.363281,-0.534722, 0.0f,

                 -0.199219  , -0.534722,0.0f,
                 -0.195312,-0.534722, 0.0f,
                 0.199219  , -0.534722,0.0f,
                 0.195312,-0.534722, 0.0f,
                 -0.179688  , -0.534722,0.0f,
                 -0.175781,-0.534722, 0.0f,
                 0.179688  , -0.534722,0.0f,
                 0.175781,-0.534722, 0.0f,
                 -0.105469  , -0.534722,0.0f,
                 -0.101562,-0.534722, 0.0f,
                 0.105469  , -0.534722,0.0f,
                 0.101562,-0.534722, 0.0f,
                 -0.363281  , -0.541667,0.0f,
                 -0.363281,-0.569444, 0.0f,
                 0.363281  , -0.541667,0.0f,
                 0.363281,-0.569444, 0.0f,
                 -0.203125  , -0.541667,0.0f,
                 -0.203125,-0.6875, 0.0f,
                 0.203125  , -0.541667,0.0f,
                 0.203125,-0.6875, 0.0f,
-0.175781  , -0.541667,0.0f,
                 -0.175781,-0.6875, 0.0f,

0.175781  , -0.541667,0.0f,
                 0.175781,-0.6875, 0.0f,
  
-0.175781  , -0.541667,0.0f,
                 -0.175781,-0.6875, 0.0f,



                 -0.109375 , -0.541667 , 0.0 , 
-0.109375 , -0.569444 , 0.0 , 
-0.367188 , -0.569444 , 0.0 , 
-0.363281 , -0.569444 , 0.0 , 
-0.292969 , -0.569444 , 0.0 , 
-0.289062 , -0.569444 , 0.0 , 
-0.273438 , -0.569444 , 0.0 , 
-0.269531 , -0.569444 , 0.0 , 
-0.105469 , -0.569444 , 0.0 , 
-0.101562 , -0.569444 , 0.0 ,                
                 
                
                 0.109375 , -0.541667 , 0.0 , 
0.109375 , -0.569444 , 0.0 , 
0.367188 , -0.569444 , 0.0 , 
0.363281 , -0.569444 , 0.0 , 
0.292969 , -0.569444 , 0.0 , 
0.289062 , -0.569444 , 0.0 , 
0.273438 , -0.569444 , 0.0 , 
0.269531 , -0.569444 , 0.0 , 
0.105469 , -0.569444 , 0.0 , 
0.101562 , -0.569444 , 0.0 , 
                 
                 

                 -0.417969 , -0.576389 , 0.0 , 
-0.367188 , -0.576389 , 0.0 , 
-0.289062 , -0.576389 , 0.0 , 
-0.273438 , -0.576389 , 0.0 , 
-0.101562 , -0.576389 , 0.0 , 
-0.0195312 , -0.576389 , 0.0 , 
-0.421875 , -0.583333 , 0.0 , 
-0.417969 , -0.583333 , 0.0 , 
-0.0195312 , -0.583333 , 0.0 , 
-0.015625 , -0.583333 , 0.0 , 
-0.425781 , -0.590278 , 0.0 , 
-0.425781 , -0.854167 , 0.0 , 
-0.015625 , -0.590278 , 0.0 , 
-0.015625 , -0.736111 , 0.0 , 
-0.207031 , -0.6875 , 0.0 , 
-0.203125 , -0.6875 , 0.0 , 
-0.1875 , -0.6875 , 0.0 , 
-0.183594 , -0.6875 , 0.0 , 
-0.351562 , -0.694444 , 0.0 , 
-0.207031 , -0.694444 , 0.0 , 
-0.167969 , -0.694444 , 0.0 , 
-0.0859375 , -0.694444 , 0.0 , 
-0.355469 , -0.701389 , 0.0 , 
-0.351562 , -0.701389 , 0.0 , 
-0.0859375 , -0.701389 , 0.0 , 
-0.0820312 , -0.701389 , 0.0 , 
-0.359375 , -0.708333 , 0.0 , 
-0.359375 , -0.736111 , 0.0 , 
-0.0820312 , -0.708333 , 0.0 , 
-0.0820312 , -0.736111 , 0.0 , 
-0.355469 , -0.736111 , 0.0 , 
-0.351562 , -0.736111 , 0.0 , 
-0.0859375 , -0.736111 , 0.0 , 
-0.0820312 , -0.736111 , 0.0 , 
-0.0117188 , -0.736111 , 0.0 , 
-0.0078125 , -0.736111 , 0.0 , 
-0.351562 , -0.743056 , 0.0 , 
-0.0859375 , -0.743056 , 0.0 , 
-0.0078125 , -0.743056 , 0.0 , 
0 , -0.743056 , 0.0 , 


 0.417969 , -0.576389 , 0.0 , 
0.367188 , -0.576389 , 0.0 , 
0.289062 , -0.576389 , 0.0 , 
0.273438 , -0.576389 , 0.0 , 
0.101562 , -0.576389 , 0.0 , 
0.0195312 , -0.576389 , 0.0 , 
0.421875 , -0.583333 , 0.0 , 
0.417969 , -0.583333 , 0.0 , 
0.0195312 , -0.583333 , 0.0 , 
0.015625 , -0.583333 , 0.0 , 
0.425781 , -0.590278 , 0.0 , 
0.425781 , -0.854167 , 0.0 , 
0.015625 , -0.590278 , 0.0 , 
0.015625 , -0.736111 , 0.0 , 
0.207031 , -0.6875 , 0.0 , 
0.203125 , -0.6875 , 0.0 , 
0.1875 , -0.6875 , 0.0 , 
0.183594 , -0.6875 , 0.0 , 
0.351562 , -0.694444 , 0.0 , 
0.207031 , -0.694444 , 0.0 , 
0.167969 , -0.694444 , 0.0 , 
0.0859375 , -0.694444 , 0.0 , 
0.355469 , -0.701389 , 0.0 , 
0.351562 , -0.701389 , 0.0 , 
0.0859375 , -0.701389 , 0.0 , 
0.0820312 , -0.701389 , 0.0 , 
0.359375 , -0.708333 , 0.0 , 
0.359375 , -0.736111 , 0.0 , 
0.0820312 , -0.708333 , 0.0 , 
0.0820312 , -0.736111 , 0.0 , 
0.355469 , -0.736111 , 0.0 , 
0.351562 , -0.736111 , 0.0 , 
0.0859375 , -0.736111 , 0.0 , 
0.0820312 , -0.736111 , 0.0 , 
0.0117188 , -0.736111 , 0.0 , 
0.0078125 , -0.736111 , 0.0 , 
0.351562 , -0.743056 , 0.0 , 
0.0859375 , -0.743056 , 0.0 , 
0.0078125 , -0.743056 , 0.0 , 
0 , -0.743056 , 0.0 , 

-0.421875 , -0.854167 , 0.0 , 
-0.417969 , -0.854167 , 0.0 , 
-0.417969 , -0.861111 , 0.0 , 
0 , -0.861111 , 0.0 , 
-0.433594 , -0.861111 , 0.0 , 
-0.433594 , -0.875 , 0.0 , 
-0.429688 , -0.875 , 0.0 , 
-0.421875 , -0.875 , 0.0 , 
-0.421875 , -0.881944 , 0.0 , 
0 , -0.881944 , 0.0 , 


0.421875 , -0.854167 , 0.0 , 
0.417969 , -0.854167 , 0.0 , 
0.417969 , -0.861111 , 0.0 , 
0 , -0.861111 , 0.0 , 
0.433594 , -0.861111 , 0.0 , 
0.433594 , -0.875 , 0.0 , 
0.429688 , -0.875 , 0.0 , 
0.421875 , -0.875 , 0.0 , 
0.421875 , -0.881944 , 0.0 , 
0 , -0.881944 , 0.0 , 
0.171875 , 0.243056 , 0.0 , 
0.171875 , 0.0972222 , 0.0


   
 

        
    }; 
    glBindVertexArray(vaoWall);
    glBindBuffer(GL_ARRAY_BUFFER,vboWall);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

        float vertices1[]={
		-0.03125,0.131944,0.0,
		0.03125,0.131944,0.0
	};
	glBindVertexArray(vaoCentreLine);
	glBindBuffer(GL_ARRAY_BUFFER,vboCentreLine);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}
void movePacman()
{
	last[0]=pacmanCentre[0];
	last[1]=pacmanCentre[1];
	pacmanShape=!pacmanShape;
	currPacLoc[0]=(((pacmanCentre[0]))/8)-18;
	currPacLoc[1]=(pacmanCentre[1])/8;
	cout<<currPacLoc[0]<<" "<<currPacLoc[1]<<endl;;
	if(!state.empty())
	{
		nextState=state.front();
		switch(nextState)
		{
			case 0:
				if(currPacLoc[1]>4)
				{
					if(board[currPacLoc[1]-1][currPacLoc[0]]!=0)
					{
						currState=nextState;
						state.pop();
						pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
						pacmanCentre[1]=(((currPacLoc[1])*8)+4);
					}	
					break;
				}
				state.pop();
				break;
			case 1:
				if(currPacLoc[0]>1)
				{
					if(board[currPacLoc[1]][currPacLoc[0]-1]!=0)
					{
						currState=nextState;
						state.pop();
						pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
						pacmanCentre[1]=(((currPacLoc[1])*8)+4);
					}	
					break;
				}
				state.pop();	
				break;
			case 2:
				if(currPacLoc[0]<32)
				{
					if(board[currPacLoc[1]+1][currPacLoc[0]]!=0)
					{
						currState=nextState;
						state.pop();
						pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
						pacmanCentre[1]=(((currPacLoc[1])*8)+4);
					}	
					break;
				}
				state.pop();
				break;
			case 3:
				if(currPacLoc[0]<26)
				{
					if(board[currPacLoc[1]][currPacLoc[0]+1]!=0)
					{
						currState=nextState;
						state.pop();
						pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
						pacmanCentre[1]=(((currPacLoc[1])*8)+4);
					}	
					break;
				}
				state.pop();
				break;
		}
		cout<<"a"<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
	}


		switch(currState)
		{
			case 0:	
				newPacCentre[0]=pacmanCentre[0];
				newPacCentre[1]=pacmanCentre[1]-1;
				nextPacLoc[0]=currPacLoc[0];
				nextPacLoc[1]=((pacmanCentre[1]-1)/8);
				break;
			case 1:
				newPacCentre[0]=(pacmanCentre[0]-1);
				newPacCentre[1]=pacmanCentre[1];
				nextPacLoc[0]=((pacmanCentre[0]-1)/8)-18;
				nextPacLoc[1]=currPacLoc[1];
				break;
			case 2:
				newPacCentre[0]=pacmanCentre[0];
				newPacCentre[1]=pacmanCentre[1]+1;
				nextPacLoc[0]=currPacLoc[0];
				nextPacLoc[1]=(pacmanCentre[1]+1)/8;
				break;
			case 3:
				newPacCentre[0]=pacmanCentre[0]+1;
				newPacCentre[1]=pacmanCentre[1];
				nextPacLoc[0]=((pacmanCentre[0]+1)/8)-18;
				nextPacLoc[1]=currPacLoc[1];
		}
		cout<<"currState "<<currState<<endl;
		cout<<"npc "<<newPacCentre[0]<<" "<<newPacCentre[1]<<endl;
		cout<<"pc "<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
		if(newPacCentre[0]>=156 && newPacCentre[0]<364 && board[nextPacLoc[1]][nextPacLoc[0]]!=0)
		{
			cout<<"c1"<<endl;
			pacmanCentre[0]=newPacCentre[0];
			currPacLoc[0]=nextPacLoc[0];
		}
		if(newPacCentre[1]>=36 && newPacCentre[1]<264 && board[nextPacLoc[1]][nextPacLoc[0]]!=0)
		{
			cout<<"c2"<<endl;
			pacmanCentre[1]=newPacCentre[1];
			currPacLoc[1]=nextPacLoc[1];
		}
		cout<<"pc "<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
		if(pacmanShape)
		{
			switch(currState)
			{
				case 0:
					attachPacmanUp();
					drawPacmanUp();
					break;
				case 1:
					attachPacmanLeft();
					drawPacmanLeft();
					break;
				case 2:
					attachPacmanDown();
					drawPacmanDown();
					break;
				case 3:
					attachPacmanRight();
					drawPacmanRight();
					break;
			}
		}
		else
		{
			attachPacman();
			drawPacman();
		}
		if(last[0]==pacmanCentre[0] && last[1]==pacmanCentre[1])
		{
			clearCounter++;
		}
		else
		{
			clearCounter=0;
		}
		if(clearCounter>=2)
		{
			while(!state.empty())
			{
				state.pop();
			}
			clearCounter=0;
		}
}

void displayStablePacman()
{
	if(pacmanShape)
	{
		switch(currState)
		{
			case 0:
				attachPacmanUp();
				drawPacmanUp();
				break;
			case 1:
				attachPacmanLeft();
				drawPacmanLeft();
				break;
			case 2:
				attachPacmanDown();
				drawPacmanDown();
				break;
			case 3:
				attachPacmanRight();
				drawPacmanRight();
				break;
		}
	}
	else
	{
		attachPacman();
		drawPacman();
	}
}
void attachCentre()
{}

/*
void splashScreen()
{

}
void pause()
{

}
void gameOver()
{

}
void levelWon()
{

}
*/
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *referenceLineShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *wallShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *pacmanShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";
const char *coinShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.8f, 0.6f, 1.0f);\n"
    "}\n\0";
const char *blinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";
const char *pinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.6f, 0.8f, 1.0f);\n"
    "}\n\0";
const char *inkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.4f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *clinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.8f, 0.4f, 1.0f);\n"
    "}\n\0";
const char *textShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
int main()
{
	int success,i,j;
	char infoLog[512];
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window=glfwCreateWindow(WIDTH,HEIGHT,"SnakeGL",NULL,NULL);
	if(window==NULL)
	{
		cout<<"Failed to create GLFW window"<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout<<"Failed to initialize GLAD"<<endl;
		return -1;
	}
	glViewport(0,0,WIDTH,HEIGHT);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	int vertexShader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int referenceLineShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(referenceLineShader, 1, &referenceLineShaderSource, NULL);
    glCompileShader(referenceLineShader);
    glGetShaderiv(referenceLineShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(referenceLineShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::referenceLine::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int wallShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(wallShader, 1, &wallShaderSource, NULL);
    glCompileShader(wallShader);
    glGetShaderiv(wallShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(wallShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::wall::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int pacmanShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pacmanShader, 1, &pacmanShaderSource, NULL);
    glCompileShader(pacmanShader);
    glGetShaderiv(pacmanShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(pacmanShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::pacman::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    

    int coinShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(coinShader, 1, &coinShaderSource, NULL);
    glCompileShader(coinShader);
    glGetShaderiv(coinShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(coinShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::coin::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int blinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(blinkyShader, 1, &blinkyShaderSource, NULL);
    glCompileShader(blinkyShader);
    glGetShaderiv(blinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(blinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::blinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int pinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pinkyShader, 1, &pinkyShaderSource, NULL);
    glCompileShader(pinkyShader);
    glGetShaderiv(pinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(pinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::pinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int inkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(inkyShader, 1, &inkyShaderSource, NULL);
    glCompileShader(inkyShader);
    glGetShaderiv(inkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(inkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::inky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int clinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(clinkyShader, 1, &clinkyShaderSource, NULL);
    glCompileShader(clinkyShader);
    glGetShaderiv(clinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(clinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::clinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int textShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(textShader, 1, &textShaderSource, NULL);
    glCompileShader(textShader);
    glGetShaderiv(textShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(textShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::text::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    wallProgram=glCreateProgram();
    glAttachShader(wallProgram,vertexShader);
    glAttachShader(wallProgram,wallShader);
    glLinkProgram(wallProgram);
    glGetProgramiv(wallProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(wallProgram, 512, NULL, infoLog);
        std::cout << "ERROR::wall::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    referenceLineProgram=glCreateProgram();
    glAttachShader(referenceLineProgram,vertexShader);
    glAttachShader(referenceLineProgram,referenceLineShader);
    glLinkProgram(referenceLineProgram);
    glGetProgramiv(referenceLineProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(referenceLineProgram, 512, NULL, infoLog);
        std::cout << "ERROR::referenceLine::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    pacmanProgram=glCreateProgram();
    glAttachShader(pacmanProgram,vertexShader);
    glAttachShader(pacmanProgram,pacmanShader);
    glLinkProgram(pacmanProgram);
    glGetProgramiv(pacmanProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(pacmanProgram, 512, NULL, infoLog);
        std::cout << "ERROR::pacman::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    coinProgram=glCreateProgram();
    glAttachShader(coinProgram,vertexShader);
    glAttachShader(coinProgram,coinShader);
    glLinkProgram(coinProgram);
    glGetProgramiv(coinProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(coinProgram, 512, NULL, infoLog);
        std::cout << "ERROR::coin::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    blinkyProgram=glCreateProgram();
    glAttachShader(blinkyProgram,vertexShader);
    glAttachShader(blinkyProgram,blinkyShader);
    glLinkProgram(blinkyProgram);
    glGetProgramiv(blinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(blinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::blinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    pinkyProgram=glCreateProgram();
    glAttachShader(pinkyProgram,vertexShader);
    glAttachShader(pinkyProgram,pinkyShader);
    glLinkProgram(pinkyProgram);
    glGetProgramiv(pinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(pinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::pinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    inkyProgram=glCreateProgram();
    glAttachShader(inkyProgram,vertexShader);
    glAttachShader(inkyProgram,inkyShader);
    glLinkProgram(inkyProgram);
    glGetProgramiv(inkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(inkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::inky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    clinkyProgram=glCreateProgram();
    glAttachShader(clinkyProgram,vertexShader);
    glAttachShader(clinkyProgram,clinkyShader);
    glLinkProgram(clinkyProgram);
    glGetProgramiv(clinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(clinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::clinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    textProgram=glCreateProgram();
    glAttachShader(textProgram,vertexShader);
    glAttachShader(textProgram,textShader);
    glLinkProgram(textProgram);
    glGetProgramiv(textProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(textProgram, 512, NULL, infoLog);
        std::cout << "ERROR::text::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(referenceLineShader);
    glDeleteShader(wallShader);
    glDeleteShader(coinShader);
    glDeleteShader(blinkyShader);
    glDeleteShader(pinkyShader);
    glDeleteShader(inkyShader);
    glDeleteShader(clinkyShader);
    glDeleteShader(textShader);

    glfwSetKeyCallback(window, key_callback);

    glGenVertexArrays(2*40,&vaoReferenceLine[0][0]);
    glGenBuffers(2*40,&vboReferenceLine[0][0]);
    glGenVertexArrays(1,&vaoWall);
    glGenBuffers(1,&vboWall);
    glGenVertexArrays(1,&vaoPacmanStable);
    glGenBuffers(1,&vboPacmanStable);
    glGenVertexArrays(1,&vaoPacmanRight);
    glGenBuffers(1,&vboPacmanRight);
    glGenVertexArrays(1,&vaoPacmanLeft);
    glGenBuffers(1,&vboPacmanLeft);
    glGenVertexArrays(1,&vaoPacmanUp);
    glGenBuffers(1,&vboPacmanUp);
    glGenVertexArrays(1,&vaoPacmanDown);
    glGenBuffers(1,&vboPacmanDown);
    glGenVertexArrays(1,&vaoGhost);
    glGenBuffers(1,&vboGhost);
    glGenVertexArrays(35*28,&vaoCoin[0][0]);
    glGenBuffers(35*28,&vboCoin[0][0]);
    glGenVertexArrays(1,&vaoCentreLine);
    glGenBuffers(1,&vboCentreLine);
    x=(2.0/WIDTH),y=(2.0/HEIGHT);
    attachReferenceLines();
    attachWall();
    
    long long xx=0;
    pacmanCentre[0]=256;
	pacmanCentre[1]=((26*8)+4);
	blinkyCentre[0]=256;
	blinkyCentre[1]=(14*8)+4;
	pinkyCentre[0]=256;
	pinkyCentre[1]=(17*8)+4;
	inkyCentre[0]=240;
	inkyCentre[1]=(17*8)+4;
	clinkyCentre[0]=272;
	clinkyCentre[1]=(17*8)+4;
	attachCoins();
	float startTime=glfwGetTime();
	float lastPacmanMoveTime=glfwGetTime();
	while(!glfwWindowShouldClose(window))
    {
    	glClearColor(0.0f,0.0f,0.0f,1.0f);
    	glClear(GL_COLOR_BUFFER_BIT);
    	currTime=glfwGetTime();
		if((currTime-lastPacmanMoveTime)>(1.0/pacmanSpeed))
    	{
    		lastPacmanMoveTime=currTime;
    		cout<<"movePacman"<<endl;
			movePacman();

		}
		else
		{
			displayStablePacman();
		}
    	
    	drawCoins();

    	attachGhost(blinkyCentre);
    	drawGhost(blinkyProgram);
    	attachGhost(pinkyCentre);
    	drawGhost(pinkyProgram);
    	attachGhost(inkyCentre);
    	drawGhost(inkyProgram);
    	attachGhost(clinkyCentre);
    	drawGhost(clinkyProgram);
    	//drawReferenceLines();
        drawWall();
        
        
        
    	glfwSwapBuffers(window);
    	glfwPollEvents();
    }
    glDeleteVertexArrays(1,&vaoReferenceLine[0][0]);
    glDeleteBuffers(1,&vboReferenceLine[0][0]);
    glfwTerminate();


    

}
