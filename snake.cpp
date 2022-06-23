 #include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
void textcolor(int fc,int bc=-1){
	if(fc<0 || fc>15)
		return;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	if(bc>=0 && bc<16)
		SetConsoleTextAttribute(h,fc|bc*16);
	else
		SetConsoleTextAttribute(h,fc);
}                                            
void textcolor(char *fc,char *bc=""){
	int x,y=16;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(x,y);
}
void textcolor(char *fc,int bc){
	int x;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	textcolor(x,bc);
}
void textcolor(int fc,char *bc){
	int y;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(fc,y);
}
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//di chuyen con tro toi vi tri x y
} 
void getup(){
	HANDLE hout; 
	CONSOLE_CURSOR_INFO cursor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.dwSize=1;
	cursor.bVisible=false;
	SetConsoleCursorInfo(hout, &cursor);//chong lag
	system("mode con:cols=160 lines=45");
	system("title Snake Game - Made by Pham Duc");
	system("cls");
	textcolor("AQUA");
	printf("\n  %c",218);//goc trai tren
	int x;
	for(x=0;x<150;x++)
		printf("%c",196);//bien tren
	printf("%c  ",191);//goc phai tren
	for(x=0;x<34;x++){
		gotoxy(2,x+2);
		printf("%c",179);
		gotoxy(153,x+2);
		printf("%c ",179);
	}// ve hai bien trai phai
	gotoxy(0,36); 
	printf("  %c",192);//goc trai duoi
	for(x=0;x<150;x++)
		printf("%c",196);//bien duoi
	printf("%c  ",217);//goc phai duoi
    gotoxy(1,38);
	printf(" %c",218);
	

	for(x=0;x<21;x++)
	printf("%c",196);
	printf("%c\n",191);
	textcolor("WHITE");
	printf("  %c S N A K E   G A M E %c\n",179,179);
	textcolor("AQUA");
	printf("  %c",192);
	for(x=0;x<21;x++)
		printf("%c",196);
	printf("%c",217);
	// ve khung snake game
	gotoxy(59,38);
	printf("%c",218);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",191);
	gotoxy(59,39);
	printf("%c SCORE : 100      %c",179,179);
	gotoxy(59,40);
	printf("%c STATUS: Playing  %c",179,179);
	gotoxy(59,41);
	printf("%c",192);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",217);
	gotoxy(28,38);
	textcolor("RED");
	
	printf("Press 'x' to Exit");
	textcolor("YELLOW");
	gotoxy(28,39);
	printf("Press Space to Pause and Play");
	
    gotoxy(81,39);
    textcolor("Gray");
    printf(" %cMoves: %c");

	
}
void score(int sc){
	gotoxy(69,39);
	printf("%6d",sc*10);
}                                 // score

void countmoves(int moves){
	gotoxy(88,39);
	printf("%6d",moves);
}                       
void countspeed(int speed){
	gotoxy(110,39);

	printf( "SPEED: ");

	printf("%6d",200-speed);
}
    
void status(char *s,int c){
	gotoxy(69,40);
	textcolor(c);
	int x;
	for(x=0;x<strlen(s);x++)
		printf("%c",s[x]);
	for(;x<8;x++)
		printf(" ");
	textcolor(7);// in status
}
int main(){
	getup();
	register int flow,size,i,xb,yb,xc,yc,xd,yd,X[100],Y[100],moves,check;
	int speed,restart=1,tmp,xpos[100],ypos[100],scr;

	while(true){
		if(restart){
			status("Playing",10);
			for(int k=1;k<150;k++)
				for(int j=0;j<34;j++){
					gotoxy(k+3,j+2);
					printf(" ");// xoa man hinh
				}
				
			size=5;	
			speed=200;
			scr=0;
			moves=1 ;
		    
			score(scr);
			
			flow=RIGHT;
			xpos[0]=20;
			for(i=0;i<size;i++){
				xpos[i]=xpos[0]-i*2;
				ypos[i]=10;
			}// ran de ngang
			for(i=0;i<size;i++){
				gotoxy(xpos[i],ypos[i]);
				printf("o");
			} 
			//
			for(tmp=1;true;){
				do{
					xb=rand()%150+3;
				}while(xb%2!=0);
				yb=rand()%34+2;
				for(i=0;i<size;i++)
					if(xb==xpos[i] && yb==ypos[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(xb,yb);
			textcolor("lightgreen");
			 printf("%c", 235);//ve qua1
			textcolor(7);
			restart=0;
			// 
			
			
			
			
				for(tmp=1;true;){
				do{
					xc=rand()%150+3;
				}while(xc%2!=0);
				yc=rand()%34+2;
				for(i=0;i<size;i++)
					if(xc==xpos[i] && yc==ypos[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(xc,yc);
			textcolor("lightgreen");
			 printf("%c", 235);//ve qua2
			textcolor(7);
			restart=0;
			//
			
			
			
			
				for(tmp=1;true;){
				do{
					xd=rand()%150+3;
				}while(xd%2!=0);
				yd=rand()%34+2;
				for(i=0;i<size;i++)
					if(xd==xpos[i] && yd==ypos[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(xd,yd);
			textcolor("lightgreen");
			 printf("%c", 235);//ve qua3
			textcolor(7);
			restart=0;  
			  
			
			  if(check=1){
			  //ve vat can ngau nhien
			  for(int q=0;q<20;q=q+1)
			  
			{ 
					for(int u=1;true;){
				do{
					X[q]=rand()%150+3;
				}while(X[q]%2!=0);
				Y[q]=rand()%34+2;
				for(i=0;i<size;i++)
					if((X[q]==xpos[i] && Y[q]==ypos[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(X[q],Y[q]);
			textcolor("RED");
			 printf("%c",254);
			textcolor(7);
			restart=0;  
			}
			
			
			
			//ve vatpham  
		
			  //tang toc
			  for(int q=21;q<23;q=q+1)
			  
			{ 
					for(int u=1;true;){
				do{
					X[q]=rand()%150+3;
				}while(X[q]%2!=0);
				Y[q]=rand()%34+2;
				for(i=0;i<size;i++)
					if((X[q]==xpos[i] && Y[q]==ypos[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}
				for(i=0;i<20;i++)
					if((X[q]==X[i] && Y[q]==Y[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}	
					
				if(u)
					break;
			}
			gotoxy(X[q],Y[q]);
			textcolor("BLUE");
			 printf("%c",30);
			textcolor(7);
			restart=0;  
			}
			// lam cham
			 
			
			
			 for(int q=23;q<25;q=q+1)
			  
			{ 
					for(int u=1;true;){
				do{
					X[q]=rand()%150+3;
				}while(X[q]%2!=0);
				Y[q]=rand()%34+2;
				for(i=0;i<size;i++)
					if((X[q]==xpos[i] && Y[q]==ypos[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}
				for(i=0;i<23;i++)
					if((X[q]==X[i] && Y[q]==Y[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}	
					
				if(u)
					break;
			}
			gotoxy(X[q],Y[q]);
			textcolor("YELLOW");
			 printf("%c",31);
			textcolor(7);
			restart=0;  
			}
		    
		    
		  
			   
			   
			   
			   
	}
		  
		}
		while(!kbhit() && !restart)	                  //phat hien khong nhap phim 
		{//
				if(xpos[0]==xb && ypos[0]==yb){       // an duoc qua 1
				for(tmp=1;true;){
					do{
						xb=rand()%150+3;
					}while(xb%2!=0);
					yb=rand()%34+2;
					
					for(i=0;i<size;i++)
						if((xb==xpos[i] && yb==ypos[i]) || (xb==xc &&yb==yc) || (xb==xd &&yb==yd) ){
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				gotoxy(xb,yb);
				textcolor("lightgreen");
				 printf ("%c", 235);
				textcolor(7);
				size++;
				scr++;
				speed-=15;
				if(speed<35 ) speed+=15;
				score(scr);
			}
			//
			 
			 if(xpos[0]==xc && ypos[0]==yc){       // an duoc qua 2
				for(tmp=1;true;){
					do{
						xc=rand()%150+3;
					}while(xc%2!=0);
					yc=rand()%34+2;
					for(i=0;i<size;i++)
						if((xc==xpos[i] && yc==ypos[i]) || (xc==xb && yc==yb) || (xd==xc &&yd==yc))
						{
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				gotoxy(xc,yc);
				textcolor("lightgreen");
				 printf ("%c", 235);
				textcolor(7);
				size++;
				scr++;
				speed-=15;
				if(speed<35 ) speed+=15;
				score(scr);
			}
			 
			//
			 if(xpos[0]==xd && ypos[0]==yd){       // an duoc qua 3
				for(tmp=1;true;){
					do{
						xd=rand()%150+3;
					}while(xd%2!=0);
					yd=rand()%34+2;
					for(i=0;i<size;i++)
						if((xd==xpos[i] && yd==ypos[i]) || (xd==xb && yd==yb) || (xd==xc &&yd==yc))
						{
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				gotoxy(xd,yd);
				textcolor("lightgreen");
				 printf ("%c", 235);
				textcolor(7);
				size++;
				scr++;
				speed-=15;
				if(speed<35 ) speed+=15;
				score(scr);
			}
			
			// an duoc tang toc
			for(int q=21;q<23;q++)
			{
			
			
			if(xpos[0]==X[q] && ypos[0]==Y[q]){       
				for(tmp=1;true;){
					do{
						X[q]=rand()%150+3;
					}while(X[q]%2!=0);
					Y[q]=rand()%34+2;
					for(i=0;i<size;i++)
						if((X[q]==xpos[i] && Y[q]==ypos[i]) || (Y[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc) || (X[q]==xd &&Y[q]==yd))
						{
							tmp=0; break;
						}
					for(i=0;i<20;i++)
						if((X[q]==X[i] && Y[q]==Y[i]) || (Y[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc) || (X[q]==xd &&Y[q]==yd))
						{
							tmp=0; break;
						}	
					if(tmp)
						break;
				}
				gotoxy(X[q],Y[q]);
				textcolor("BLUE");
				 printf ("%c", 30);
				textcolor(7);
				size++;
				scr++;
			
				  speed-=30;
				if(speed<35 ) speed+=15;
				score(scr);
			}
			
		}
			// an dc lam cham
			
			
			
			for(int q=23;q<25;q++)
			{
			
			
			if(xpos[0]==X[q] && ypos[0]==Y[q]){       
				for(tmp=1;true;){
					do{
						X[q]=rand()%150+3;
					}while(X[q]%2!=0);
					Y[q]=rand()%34+2;
					for(i=0;i<size;i++)
						if((X[q]==xpos[i] && Y[q]==ypos[i]) || (Y[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc) || (X[q]==xd &&Y[q]==yd))
						{
							tmp=0; break;
						}
					for(i=0;i<23;i++)
						if((X[q]==X[i] && Y[q]==Y[i]) || (Y[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc) || (X[q]==xd &&Y[q]==yd))
						{
							tmp=0; break;
						}	
					if(tmp)
						break;
				}
				gotoxy(X[q],Y[q]);
				textcolor("YELLOW");
				 printf ("%c", 31);
				textcolor(7);
				size++;
				scr++;
			speed+=10;
			   
			
				if(speed<35 ) speed+=15;
				score(scr);
			}
			
		}
			
			
			   
			  //xoa va ve lai vat can ngau nhien sau 100 buoc
			  if (moves%100==0) 
			  {for(int k=0;k<20;k++)
			    
			   { 
				gotoxy(X[k],Y[k]);
			    printf(" ");
			   }
			   //xoa
			   
			   check=1;
		        //
		        	  if(check=1){
			  
			  for(int q=0;q<20;q=q+1)
			  
			{ 
					for(int u=1;true;){
				do{
					X[q]=rand()%150+3;
				}while(X[q]%2!=0);
				Y[q]=rand()%34+2;
				for(i=0;i<size;i++)
					if((X[q]==xpos[i] && Y[q]==ypos[i]) || (X[q]==xd && Y[q]==yd) || (X[q]==xb && Y[q]==yb) || (X[q]==xc &&Y[q]==yc)){
						u=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(X[q],Y[q]);
			textcolor("RED");
			 printf("%c",254);//ve vat can
			textcolor(7);
			restart=0;  
			
			  
		    }
			   
	                        }
			  }
			check=0;
			gotoxy(xpos[size-1],ypos[size-1]);
			for(i=size-1;i>0;i--){				
				xpos[i]=xpos[i-1];
				ypos[i]=ypos[i-1]; //truyen vi tri cho dot
			}
			switch(flow){
				case RIGHT :xpos[i]+=2; break;
				case LEFT :	xpos[i]-=2; break;
				case UP :	ypos[i]-=1; break;
				case DOWN :	ypos[i]+=1; 
			}
			tmp=1;
			for(i=1;i<size;i++)//dam vao than
				if(xpos[i]==xpos[0] && ypos[i]==ypos[0]){
					tmp=0;
					break;
				}
				//dam vao vat can 	
			for(int c=0;c<20;c++)
			    if(X[c]==xpos[0] && Y[c]==ypos[0]){
					tmp=0;
					break;
				}
				
			
				
			if(xpos[0]>152 || xpos[0]<4 || ypos[0]<2 ||ypos[0]>35)
				tmp=0;
			if(tmp){
				printf(" ");
				gotoxy(xpos[0],ypos[0]);
				printf("O");	                      //dau ran
				gotoxy(xpos[1],ypos[1]);
				printf("o");	                      //than ran
			}
			else{
				textcolor("LIGHTRED");
				printf("o");
				gotoxy(xpos[1],ypos[1]);
				printf("O");
				for(i=2;i<size;i++){
					gotoxy(xpos[i],ypos[i]);
					printf("o");
				}
				textcolor(7);
				status("GameOver",12);
				restart=1;
				getch();
			}
			//delay(speed);
			Sleep(speed);
			moves+=1;
			countmoves(moves);
			countspeed(speed);
		}
		char ch=getch();// nut cong cu
		switch(tolower(ch)){
			case 'x' : 	system("cls");                   // close
						return 0;
			case ' ' : status("Paused",4); 
						while(true){
							char z=getch();
							if(z=='x')
								return 0;
							if(z==' ')
								break;
						}
						status("Playing",10);
						break;
			case -32: {
				char chh=getch();
				if(chh==72 && flow!=DOWN)
					flow=UP;
				else if(chh==80 && flow!=UP)
					flow=DOWN;
				else if(chh==75 && flow!=RIGHT)
					flow=LEFT;
				else if(chh==77 && flow!=LEFT)
					flow=RIGHT;
				break;// chong quay dau
			}
		}
	}
}
