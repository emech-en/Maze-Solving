#include <stdio.h>
#include <windows.h>
#include <string.h>

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8
#define CROSSED 16
#define DEAD 32
#define DEADEND 64

#define MarkazGaraFisaghores 0
#define MostaghimRastChap    1
#define MostaghimChapRast    2
#define MarkazGara 3

#define Divareha 0 //Baraye negahdari etelaate divare haye har khane va CROSS ya DEAD budane an.
#define Arzesh 2 //Neghadarie Arzeshe har khane dar floodfill.



unsigned char cell;
int jahat,My,Mx;
int cellbit[16][16][4];
FILE* f;
unsigned char alg;
unsigned char ways[256];
unsigned char masir[250];
unsigned char DirOlaviatDirection[4];
unsigned char LastGoodCrossedLocation[3];

void Crossed_Way_Show (unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir);
void alg4 ();
void drow4(unsigned char cell[3][16][16],unsigned char x, unsigned char y);
unsigned char floodthink (unsigned char cell[3][16][16], unsigned char dir, unsigned char x, unsigned char y, unsigned char alg1);
void Flood_fill (unsigned char cell[3][16][16]);
void Flood_fill1 (unsigned char cell[3][16][16]);
void flood_fill2 (unsigned char cell[3][16][16],unsigned char *x, unsigned char *y, unsigned char *dir, unsigned char Flood_Fill_counter);
void flood_fill3(unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir, unsigned char Flood_Fill_counter);
void dead1(unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir);
void F_P_4 (unsigned char cell[16][16]);
void finding_P_2 (unsigned char cell[16][16]);
void F_P_3 (unsigned char cell[16][16]);
unsigned char FisaGHores(unsigned char x, unsigned char y);
void cell_numbering(unsigned char cell[3][16][16]);
void drow1(unsigned char cell[3][16][16]);
void drow2(unsigned char cell[3][16][16]);

void GotoCellPosition(unsigned char Start_x,unsigned char Start_y,unsigned char x,unsigned char y);
void Drow_Maze_Raw(unsigned char Cell[3][16][16],unsigned char X_Start,unsigned char Y_Start);
void Drow_OneCell_Raw(unsigned char *Cell,unsigned char x, unsigned char y,unsigned char X_Start,unsigned char Y_Start);

void get_wall1(unsigned char cell[3][16][16],unsigned char x,unsigned char y,unsigned char dir);
void Deading(unsigned char cell[3][16][16]);
void drow();
void ReadMazFile();
void printInCell(int x, int y, unsigned char dir);
void clrCell();
void gotoxy(int, int);
void alg3();
void gotoCell(unsigned char i, unsigned char j);

void semu_go(unsigned char dir , unsigned char* x, unsigned char* y);
unsigned char semu_turnL(unsigned char dir);
unsigned char semu_turnR(unsigned char dir);
unsigned char semu_turnB(unsigned char dir);
unsigned char next_y(unsigned char dir, unsigned char y);
unsigned char next_x(unsigned char dir, unsigned char x);

unsigned char tedadrah (unsigned char cell[16][16], unsigned char dir , unsigned char x, unsigned char y) ;
unsigned char wich_ways (unsigned char cell[16][16], unsigned char dir , unsigned char x, unsigned char y);
unsigned char think(unsigned char cell[3][16][16], unsigned char dir , unsigned char x, unsigned char y);
unsigned char* LastGoodCrossed (unsigned char cell[3][16][16]);
void GoodWayNumbering (unsigned char cell[3][16][16],unsigned char end_x, unsigned char end_y , unsigned char dir, unsigned char x, unsigned char y, unsigned char start_num);
unsigned char* dir_olaviat (unsigned char cell[3][16][16], unsigned char dir, unsigned char x, unsigned char y, unsigned char alg);

unsigned char NoFrontWall(unsigned char *OneCell, unsigned char *dir);
unsigned char NoRightWall(unsigned char *OneCell, unsigned char *dir);
unsigned char NoLeftWall(unsigned char *OneCell, unsigned char *dir);
unsigned char NoBackWall(unsigned char *OneCell, unsigned char *dir);

unsigned char NoNorthWall(unsigned char *OneCell);
unsigned char NoEastWall(unsigned char *OneCell);
unsigned char NoWestWall(unsigned char *OneCell);
unsigned char NoSouthWall(unsigned char *OneCell);

unsigned char NeedToFloodFill(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y);

unsigned char IsDeadEnd(unsigned char *OneCell);

unsigned char NeedToExplore(unsigned char cell[3][16][16]);
void Flood_Fill_Prof(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y, unsigned char *dir, unsigned char Flood_Fill_counter,unsigned char StartX, unsigned char StartY);
unsigned char NeedToFloodFillProf(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y,unsigned char DestX,unsigned char DestY);
void First_Cell_Values_Prof (unsigned char cell[3][16][16],unsigned char DestX,unsigned char DestY);


int main (int argc,char *argv[]) {
    int i=1;
    char name[5];
    
    printf ("=============================================================================|| "
            "||  Micromouse Semulator        - - - - - - - - - - - - - - - - - - - - - - -|| "
            "||---------------------------------------------------------------------------|| ");
    
    for (i=3 ; i<47 ; i++)
        printf(
            "||                                                                           || ");
    
    printf ("||---------------------------------------------------------------------------|| "
            "||- - - - - - - - - - - - - - - - - - - - - - - -        By: M.H. Niroomand  || "
            "||=============================================================================");
    char name1[35] = "MicroMouseMaz (";
    gotoxy (4,5);
    
    argv++;
    if (*argv != '\0')
    {
        printf("%s\n",*argv);
        if (argv)
            f = fopen(*argv,"r");
    }
    if (!f)
    {
        printf ("Inter your Maz Number: ");
        gets(name);
        strcat(name1,name);
        strcat(name1,")");
        strcat(name1,".maz");
        f = fopen(name1,"r");
    }
    if (!f) {
        gotoxy (6,7);
        printf("hoooo");
        getch();
        exit(1);
    }
    gotoxy (6,7);
    printf ("which preferes:");
    gotoxy (7,8);
    printf ("0- MarkazGara + Fisaghores");
    gotoxy (7,9);
    printf ("1- Mostaghim - Rast - Chap");
    gotoxy (7,10);
    printf ("2- Mostaghim - Chap - Rast");
    gotoxy (7,11);
    printf ("4- MarkazGara");
    gotoxy (6,12);
    printf ("WichOne you want (ente the number 0-4):   ");            
    scanf("%d",&alg);
    ReadMazFile();
    drow();
    getch();
    
    alg4();
    getch();
    //  alg3();
    
    getch();
    return 0;
}

void ReadMazFile(){
    int i=0;
    int j=0;
    for (i=0 ; i<16 ; i++) {
        for (j=0 ; j<16 ; j++) {
            fscanf (f,"%d",&cell);
            cellbit[i][j][0] = cell%2;
            cell/=2;
            cellbit[i][j][1] = cell%2;
            cell/=2;
            cellbit[i][j][2] = cell%2;
            cell/=2;
            cellbit[i][j][3] = cell%2;
        }
    }
}


 
/*
*    tabe'e tagheere dastie mogheiate makan nama.
*/
void gotoxy(int x, int y)
{
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void gotoCell(unsigned char i, unsigned char j)
{
    gotoxy(0,0);
}


void get_wall_robot(unsigned char cell[3][16][16],unsigned char dir, unsigned char *x, unsigned char *y, unsigned char num)
{
    unsigned char i;
    unsigned char tF =  (num%16)%2;
    unsigned char tR = ((num%16)/2)%2;
    unsigned char tL = ((num%16)/8)%2;
    unsigned char celltemp = cell[Divareha][*x][*y];
    for (i=1 ; i<(num/16) ; i++)
    {
        semu_go(dir,x,y);
        switch (dir)
        {
            case NORTH: cell[Divareha][*x][*y] |= 10; cell[Divareha][*x][*y] |= CROSSED; if ((celltemp/DEAD)%2==1) cell[Divareha][*x][*y] |= DEAD;
            case EAST : cell[Divareha][*x][*y] |= 5 ; cell[Divareha][*x][*y] |= CROSSED; if ((celltemp/DEAD)%2==1) cell[Divareha][*x][*y] |= DEAD;
            case SOUTH: cell[Divareha][*x][*y] |= 10; cell[Divareha][*x][*y] |= CROSSED; if ((celltemp/DEAD)%2==1) cell[Divareha][*x][*y] |= DEAD;
            case WEST : cell[Divareha][*x][*y] |= 5 ; cell[Divareha][*x][*y] |= CROSSED; if ((celltemp/DEAD)%2==1) cell[Divareha][*x][*y] |= DEAD;
        }
    }
    semu_go(dir,x,y);
    switch (dir)
    {
        case NORTH: cell[Divareha][*x][*y] |= (tF)  +(tR*2)+(tL*8) ; cell[Divareha][*x][*y] |= CROSSED;
        case EAST : cell[Divareha][*x][*y] |= (tL)  +(tF*2)+(tR*4) ; cell[Divareha][*x][*y] |= CROSSED; 
        case SOUTH: cell[Divareha][*x][*y] |= (tL*2)+(tF*4)+(tR*8) ; cell[Divareha][*x][*y] |= CROSSED; 
        case WEST : cell[Divareha][*x][*y] |= (tR)  +(tF*8)+(tL*4) ; cell[Divareha][*x][*y] |= CROSSED;
    }
}


/*
*    arzesh gozarie avalie khune ha.
*    dar in tabe engar k hich divari vojud nadarad va halate ideal baraye 
*    baray e har khane dar nazar gerefte msihavad.
*    arzeshe ar khune dar cell[1][x][y] zakhire mishavad.
*/
void cell_numbering(unsigned char cell[3][16][16])
{
    unsigned char i=0, j=0;
    // arzesh gozarie khane haye maghsad.
    cell[1][7][7] = cell[1][8][7] = cell[1][7][8] = cell[1][8][8] = 0;

    /* arzesh gozari baraye khane haee k ba x neshane gozari shode and.
    *
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   X X X X X X X 1 1 X X X X X X X
    *   X X X X X X X 1 1 X X X X X X X
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0 
    *   0 0 0 0 0 0 0 X X 0 0 0 0 0 0 0
    */
    for (i=1 ; i<8 ; i++)
    {
        cell[1][7-i][7] = i;
        cell[1][8+i][7] = i;
        cell[1][7-i][8] = i;
        cell[1][8+i][8] = i;
        cell[1][7][7-i] = i;
        cell[1][7][8+i] = i;
        cell[1][8][7-i] = i;
        cell[1][8][8+i] = i;
    }
    
    /*
    *     arzesh gozarie baghie  khunehaye zamin
    */
    for (i=1;i<8;i++)
    {
        for (j=1 ; j<8 ; j++)
        {
            cell[1][7-i][7-j] = cell[1][7-i][7-(j-1)]+1;
            cell[1][7-i][8+j] = cell[1][7-i][8+(j-1)]+1;
            cell[1][8+i][7-j] = cell[1][8+i][7-(j-1)]+1;
            cell[1][8+i][8+j] = cell[1][8+i][8+(j-1)]+1;
        }
    }
}




/*
*    tabe'e chape zamin
*/
void drow() {
    gotoxy(6,7);
    int khat = 7;    
    int i=0;
    int j=0;
    for (i=0 ; i<16 ;i++){
        if (i==0){
           printf("+---+");
           for (j=1; j<16 ; j++)
               printf("---+");
        }
        khat++;
        gotoxy(6,khat);
        if (cellbit[i][0][1]==1)
            printf("|   |");
        else
            printf("|    ");
        for (j=1 ; j<16 ; j++) {
            if (cellbit[i][j][1]==1)
               printf("   |");
            else
                printf("    ");
        }
         khat++;
         gotoxy(6,khat);
         if (cellbit[i][0][2]==1)
             printf("+---+");
         else
             printf("+   +");
         for (j=1 ; j<16 ; j++){
             if (cellbit[i][j][2]==1)
                printf("---+");
             else
                 printf("   +");
         }
    }
}

/*
* tabe'e chape zamin dar algorithme CROSS_DEAD ke etelaate har khune
* ro ham moghe chap namayesh mide.
*/
void drow1(unsigned char cell[3][16][16]) {
    gotoxy(6,7);
    int khat = 7;    
    int i=0;
    int j=0;
    for (i=0 ; i<16 ;i++){
        if (i==0)
        {
           printf("+---+");
           for (j=1; j<16 ; j++)
               printf("---+");
        }
        khat++;
         gotoxy(6,khat);
        if ((cell[Divareha][0][15-i]/2)%2==1) 
        {    
            if ((cell[Divareha][0][15-i]/DEAD)%2==1)
                printf("| D |");
            else if ((cell[Divareha][0][15-i]/CROSSED)%2==1)
                printf("| C |");
            else
                printf("|   |");
        }
        else
        {    
            if ((cell[Divareha][0][15-i]/DEAD)%2==1)
                printf("| D  ");
            else if ((cell[Divareha][0][15-i]/CROSSED)%2==1)
                printf("| C  ");
            else
                printf("|    ");
        }
        for (j=1 ; j<16 ; j++) {
            if ((cell[Divareha][j][15-i]/2)%2==1)
            {    
                if ((cell[Divareha][j][15-i]/DEAD)%2==1)
                    printf(" D |");
                else if ((cell[Divareha][j][15-i]/CROSSED)%2==1)
                    printf(" C |");
                else
                    printf("   |");
            }
            else
            {    
                if ((cell[Divareha][j][15-i]/DEAD)%2==1)
                    printf(" D  ");
                else if ((cell[Divareha][j][15-i]/CROSSED)%2==1)
                    printf(" C  ");
                else
                    printf("    ");
            }
        }
    
        khat++;
         gotoxy(6,khat);
         if ((cell[Divareha][0][15-i]/4)%2==1)
             printf("+---+");
         else
             printf("+   +");
         for (j=1 ; j<16 ; j++){
             if ((cell[Divareha][j][15-i]/4)%2==1)
                printf("---+");
             else
                 printf("   +");
         }
    }
}

/*
*    hengame chape zamin , arzeshe har khune dar algorithm e foload fill
*    ra ham dar khane chap mikonad, 
*/
void drow2(unsigned char cell[3][16][16]) {
    gotoxy(6,7);
    int khat = 7;    
    int i=0;
    int j=0;
    for (i=0 ; i<16 ;i++){
        if (i==0)
        {
           printf("+---+");
           for (j=1; j<16 ; j++)
               printf("---+");
        }
        khat++;
         gotoxy(6,khat);
         
         printf ("|");
         //printf ("   ");
         if (cell[Arzesh][0][15-i]/10==0)
            printf (" %d ",cell[Arzesh][0][15-i]);
         else
         {
            if (cell[Arzesh][0][15-i]/100!=0)
                 printf ("%d",cell[Arzesh][0][15-i]);
            else
                printf ("%d ",cell[Arzesh][0][15-i]);
        }
 
       if ((cell[Divareha][0][15-i]/2)%2==1) 
            printf("|",cell[Arzesh][0][15-i]);
        else
            printf(" ",cell[Arzesh][0][15-i]);
            
        for (j=1 ; j<16 ; j++) {
            //printf ("   ");
            if (cell[Arzesh][j][15-i]/10==0)
                printf (" %d ",cell[Arzesh][j][15-i]);
            else
            {
                if (cell[Arzesh][j][15-i]/100!=0)
                    printf ("%d",cell[Arzesh][j][15-i]);
                else
                    printf ("%d ",cell[Arzesh][j][15-i]);
            }

            if ((cell[Divareha][j][15-i]/2)%2==1)
                printf("|",cell[Arzesh][j][15-i]);
            else
                printf(" ",cell[Arzesh][j][15-i]);
        }
        khat++;
        gotoxy(6,khat);
         if ((cell[Divareha][0][15-i]/4)%2==1)
             printf("+---+");
         else
             printf("+   +");
         for (j=1 ; j<16 ; j++){
             if ((cell[Divareha][j][15-i]/4)%2==1)
                printf("---+");
             else
                 printf("   +");
         }
    }
}

void GotoCellPosition(unsigned char Start_X,unsigned char Start_Y,unsigned char x,unsigned char y)
{
    COORD coord;
    coord.X = Start_X + (x*4);
    coord.Y = Start_Y - (y*2);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Drow_Maze_Raw(unsigned char Cell[3][16][16],unsigned char X_Start,unsigned char Y_Start) {    
    int i=0;
    int j=0;
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
        {
            GotoCellPosition(X_Start,Y_Start-2,i,j);
            if (!NoNorthWall(&Cell[Divareha][i][j]))
                printf("+---+");
            else 
                printf("+   +");
                
            GotoCellPosition(X_Start,Y_Start-1,i,j);
            if (!NoWestWall(&Cell[Divareha][i][j]))
                printf("|");
            else 
                printf(" ");
                
            GotoCellPosition(X_Start+4,Y_Start-1,i,j);
            if (!NoEastWall(&Cell[Divareha][i][j]))
                printf("|");
            else 
                printf(" ");
                
            GotoCellPosition(X_Start,Y_Start,i,j);
            if (!NoSouthWall(&Cell[Divareha][i][j]))
                printf("+---+");
            else 
                printf("+   +");
        }
}

void Drow_OneCell_Raw(unsigned char *Cell,unsigned char x, unsigned char y,unsigned char X_Start,unsigned char Y_Start) {    
            GotoCellPosition(X_Start,Y_Start-2,x,y);
            if (!NoNorthWall(Cell))
                printf("+---+");
            GotoCellPosition(X_Start,Y_Start-1,x,y);
            if (!NoWestWall(Cell))
                printf("|");
            GotoCellPosition(X_Start+4,Y_Start-1,x,y);
            if (!NoEastWall(Cell))
                printf("|");
            GotoCellPosition(X_Start,Y_Start,x,y);
            if (!NoSouthWall(Cell))
                printf("+---+");
}

/*
*    chape vaziate robot dar zamin. 
*/
void printInCell(int x, int y, unsigned char dir)
{
     gotoxy((4*x)+7,(2*(15-y))+8);
     switch (dir)
     {
            case 0     : printf("   ");break;
            case NORTH : printf("AAA");break;
            case EAST  : printf(">>>");break;
            case SOUTH : printf("VVV");break;
            case WEST  : printf("<<<");break;
     }
}

/*
*    pak kardane mohtaviate darun e khune ha
*/
void clrCell()
{
     int i=0;
     int j=0;
     for (i=0 ; i<16 ; i++)
         for (j=0 ; j<16 ; j++) {
             gotoxy((4*i)+7,(2*j)+8);
             printf("   ");
         }
}


// Faghat chape zamin
void drow4(unsigned char cell[3][16][16],unsigned char x, unsigned char y)
{
            if (cell[Divareha][x][y]%2==1)
            {
                gotoxy ((4*x)+7,(2*(15-y))+8-1);
                printf ("---");
            }
            if ((cell[Divareha][x][y]/2)%2==1)
            {
                gotoxy ((4*x)+7+3,(2*(15-y))+8);
                printf ("|");
            }
            if ((cell[Divareha][x][y]/4)%2==1)
            {
                gotoxy ((4*x)+7,(2*(15-y))+8+1);
                printf ("---");
            }
            if ((cell[Divareha][x][y]/8)%2==1)
            {
                gotoxy ((4*x)+7-1,(2*(15-y))+8);
                printf ("|");
            }
}
    


void alg3 () 
{
    unsigned char cell[3][16][16]={0};
    unsigned char dir=NORTH,x=0,y=0,end_x,end_y,end_dir;
    int counter=0;
    int i=0,j=0;
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            cell[Divareha][i][j]=0;
    for (i=0 ; i<16 ; i++)
    {
        cell[Divareha][i][0] |= SOUTH;
        cell[Divareha][i][15]|= NORTH;
        cell[Divareha][0][i] |= WEST ;
        cell[Divareha][15][i]|= EAST ;
    }
    cell_numbering(cell);
    cell[Divareha][0][0] |= CROSSED;
    while(!((x==7 || x==8)&&(y==7 || y==8))){
        Deading(cell);
        Deading(cell);
        Deading(cell);
        Deading(cell);
        Deading(cell);
        Deading(cell);
        finding_P_2 (cell[Divareha]);
        F_P_3 (cell[Divareha]);
        F_P_4 (cell[Divareha]);
        
        get_wall1(cell,x,y,dir);
        drow1(cell);
        printInCell(x,y,dir);
        //getch();
        sleep(200);
        dir = think(cell,dir,x,y);
        semu_go(dir,&x,&y);
        counter ++;
        gotoxy(4,41);
        printf ("MoveCounter : %d  " , counter);
        dead1(cell,x,y,dir);
    }
    
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++) 
        {
            if ((cell[Divareha][i][j]/CROSSED)%2!=1)
                cell[Divareha][i][j]-=DEAD;
            cell[1][i][j]=0;
        }
    dir = semu_turnB(dir);
    end_x = x;
    end_y = y;
    end_dir = dir;
    
    GoodWayNumbering(cell,end_x,end_y,NORTH,0,0,0);
    clrCell();
    
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            if (cell[1][i][j]!=0)
            {
                gotoxy((4*i)+7,(2*(15-j))+8);
                printf("%3d",cell[1][i][j]);
            }
    getch();
    
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            cell[1][i][j]=0;
    clrCell();
    GoodWayNumbering(cell,0,0,end_dir,end_x,end_y,0);
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            if (cell[1][i][j]!=0)
            {
                gotoxy((4*i)+7,(2*(15-j))+8);
                printf("%3d",cell[1][i][j]);
            }
    while(!(x==0 && y==0))
    {
        for (i=0 ; i<16 ; i++)
            for (j=0 ; j<16 ; j++)
        {
            if (cell[1][i][j]!=0)
            {
                gotoxy((4*i)+7,(2*(15-j))+8);
                printf("%3d",cell[1][i][j]);
            }
        }
        semu_go(dir,&x,&y);
        printInCell(x,y,dir);    
        sleep(200);
        if (tedadrah(cell[Divareha],dir,x,y)==1)
        {
            switch (wich_ways(cell[Divareha],dir,x,y))
            {
            case 1: continue;
            case 2: dir = semu_turnR(dir); continue;
            case 4: dir = semu_turnL(dir); continue;
            }
        }
        else if (tedadrah(cell[Divareha],dir,x,y)==2)
        {
            switch (wich_ways(cell[Divareha],dir,x,y))
            {
            case 3: 
                {
                    if (cell[1][x][y] - cell[1][next_x(dir,x)][next_y(dir,y)]==1)
                        continue;
                    else
                    {
                        dir = semu_turnR(dir);
                        continue;
                    }
                }
            case 5: 
                {
                    if (cell[1][x][y] - cell[1][next_x(dir,x)][next_y(dir,y)]==1)
                        continue;
                    else
                    {
                        dir = semu_turnL(dir);
                        continue;
                    }
                }
            case 6: 
                {
                    if (cell[1][x][y] - cell[1][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]==1) 
                    {
                        dir = semu_turnR(dir);
                        continue;
                    }
                    else
                    {
                        dir = semu_turnL(dir);
                        continue;
                    }
                }
            }
        }
        else if (tedadrah(cell[0],dir,x,y)==3)
        {
            if (cell[1][x][y] - cell[1][next_x(dir,x)][next_y(dir,y)]==1)
                continue;
            else if (cell[1][x][y] - cell[1][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]==1) 
            {
                dir = semu_turnR(dir);
                continue;
            }
            else
            {
                dir = semu_turnL(dir);
                continue;
            }
        }
    }
    
    
}




void get_wall1(unsigned char cell[3][16][16],unsigned char x,unsigned char y,unsigned char dir) 
{
    switch(dir)
    {
        case NORTH: cell[Divareha][x][y] |= cellbit[15-y][x][0]*NORTH+cellbit[15-y][x][1]*EAST+cellbit[15-y][x][3]*WEST;
        case EAST : cell[Divareha][x][y] |= cellbit[15-y][x][0]*NORTH+cellbit[15-y][x][1]*EAST+cellbit[15-y][x][2]*SOUTH;
        case SOUTH: cell[Divareha][x][y] |= cellbit[15-y][x][2]*SOUTH+cellbit[15-y][x][1]*EAST+cellbit[15-y][x][3]*WEST;
        case WEST : cell[Divareha][x][y] |= cellbit[15-y][x][0]*NORTH+cellbit[15-y][x][3]*WEST+cellbit[15-y][x][2]*SOUTH;
    }
    if (x>0)
        cell[Divareha][x-1][y] |= cellbit[15-y][x][3]*EAST;
    if (y>0)
        cell[Divareha][x][y-1] |= cellbit[15-y][x][2]*NORTH;
    if (x<15)
        cell[Divareha][x+1][y] |= cellbit[15-y][x][1]*WEST;
    if (y<15)
        cell[Divareha][x][y+1] |= cellbit[15-y][x][0]*SOUTH;
}


unsigned char think(unsigned char cell[3][16][16], unsigned char dir , unsigned char x, unsigned char y)  
{
    unsigned char lastx, lasty;
    unsigned char *direction;
    unsigned char j,i;
    direction = dir_olaviat(cell,dir,x,y,alg);
    
    
    if (tedadrah(cell[Divareha],dir,x,y)==0)
    { 
        cell[Divareha][x][y] |= DEAD;
        return semu_turnB(dir);
    }
    
    else if (tedadrah(cell[Divareha],dir,x,y)==1) 
    {
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 1 : if ((cell[Divareha][next_x(dir,x)][next_y(dir,y)]/DEAD)%2==0) return dir;
            case 2 : if ((cell[Divareha][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]/DEAD)%2==0) return semu_turnR(dir);
            case 4 : if ((cell[Divareha][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)]/DEAD)%2==0) return semu_turnL(dir);
        }
        cell[Divareha][x][y] |= DEAD;
        return semu_turnB(dir);
    }
    
    else if (tedadrah(cell[Divareha],dir,x,y)==2)
    {
        if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]/DEAD)%2==0)
        {
            if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]/CROSSED)%2 == 0)
                return dir_olaviat(cell,dir,x,y,alg)[0];
            else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/DEAD)%2==0)
            {
                if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/CROSSED)%2==0)
                    return dir_olaviat(cell,dir,x,y,alg)[1];
                else
                {
                    for(i=0;i<16;i++)
                        for(j=0;j<16;j++)
                            cell[1][i][j]=0;
                    printInCell(LastGoodCrossed(cell)[0],LastGoodCrossed(cell)[1],LastGoodCrossed(cell)[2]);
                    GoodWayNumbering(cell,x,y,LastGoodCrossed(cell)[2],LastGoodCrossed(cell)[0],LastGoodCrossed(cell)[1],0);
                    if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)] == 1)
                        return dir_olaviat(cell,dir,x,y,alg)[0];
                    else if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]==1)
                        return dir_olaviat(cell,dir,x,y,alg)[1];
                    else
                        return dir_olaviat(cell,dir,x,y,alg)[2];
                }
            }
        }
        else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/DEAD)%2==0)
            return dir_olaviat(cell,dir,x,y,alg)[1];
        cell[Divareha][x][y] |= DEAD;
        return dir_olaviat(cell,dir,x,y,alg)[2];
    }
    
    else if (tedadrah(cell[Divareha],dir,x,y)==3)
    {
        if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]/DEAD)%2==0)
        {
            if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]/CROSSED)%2==0)
                return dir_olaviat(cell,dir,x,y,alg)[0];
            else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/DEAD)%2==0)
            {
                if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/CROSSED)%2==0)
                    return dir_olaviat(cell,dir,x,y,alg)[1];
                else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/DEAD)%2==0)
                {
                    if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/CROSSED)%2==0)
                        return dir_olaviat(cell,dir,x,y,alg)[2];
                    else
                    {
                        for(i=0;i<16;i++)
                            for(j=0;j<16;j++)
                                cell[1][i][j]=0;
                                
                                
                         
   
                        GoodWayNumbering(cell,x,y,LastGoodCrossed(cell)[2],LastGoodCrossed(cell)[0],LastGoodCrossed(cell)[1],0);
                        if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[0];
                        else if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[1];
                        else if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[2];
                        else
                            return dir_olaviat(cell,dir,x,y,alg)[3];
                        }
                    }
                }
                else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/DEAD)%2==0)
                {
                    if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/CROSSED)%2==0)
                        return dir_olaviat(cell,dir,x,y,alg)[2];
                    else
                    {
                        for(i=0;i<16;i++)
                                for(j=0;j<16;j++)
                                    cell[1][i][j]=0;
                        GoodWayNumbering(cell,x,y,LastGoodCrossed(cell)[2],LastGoodCrossed(cell)[0],LastGoodCrossed(cell)[1],0);
                        if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[0],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[0];
                        else if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[2];
                        else
                            return dir_olaviat(cell,dir,x,y,alg)[3];    
                    }
                }
            }
            else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/DEAD)%2==0)
            {
                if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]/CROSSED)%2==0)
                    return dir_olaviat(cell,dir,x,y,alg)[1];
                else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/DEAD)%2==0)
                {
                    if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/CROSSED)%2==0)
                        return dir_olaviat(cell,dir,x,y,alg)[2];
                    else
                    {
                        for(i=0;i<16;i++)
                            for(j=0;j<16;j++)
                                cell[1][i][j]=0;
                                    
                        GoodWayNumbering(cell,x,y,LastGoodCrossed(cell)[2],LastGoodCrossed(cell)[0],LastGoodCrossed(cell)[1],0);
                        if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[1],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[1];
                        else if (cell[1][x][y] - cell[1][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]==1)
                            return dir_olaviat(cell,dir,x,y,alg)[2];
                        else
                            return dir_olaviat(cell,dir,x,y,alg)[3];
                    }
                }
                return dir_olaviat(cell,dir,x,y,alg)[1];
            }
            else if ((cell[Divareha][next_x(dir_olaviat(cell,dir,x,y,alg)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg)[2],y)]/DEAD)%2==0)
                return dir_olaviat(cell,dir,x,y,alg)[2];
            
            cell[Divareha][x][y] |= DEAD;
            return semu_turnB(dir);
        }
    }


unsigned char tedadrah (unsigned char cell[16][16], unsigned char dir , unsigned char x, unsigned char y) 
{
    unsigned char tedad = 0; 
    if ((cell[x][y]/dir)%2 == 0)
        if ((cell[next_x(dir,x)][next_y(dir,y)]/DEAD)%2==0)
            tedad++;
    if (dir == WEST)
    {
        if (cell[x][y]%2==0)
            if ((cell[next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]/DEAD)%2==0)
                tedad++;
    }
    else if ((cell[x][y]/(2*dir))%2==0)
        if ((cell[next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]/DEAD)%2==0)
                tedad++;
    if (dir == NORTH) 
    {
        if ((cell[x][y]/8)%2==0)
            if ((cell[next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)]/DEAD)%2==0)
                tedad++;
    }
    else if ((cell[x][y]/(dir/2))%2==0)
        if ((cell[next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)]/DEAD)%2==0)
            tedad++;
    
    return tedad;
}



/*
*   a function that return us how many ways the robot can go. exepting the backward.
*/
unsigned char wich_ways (unsigned char cell[16][16], unsigned char dir , unsigned char x, unsigned char y)
{
    unsigned char tedad = 0; 
    // check kardane divare ruberu
    if ((cell[x][y]/dir)%2 == 0)
        if ((cell[next_x(dir,x)][next_y(dir,y)]/DEAD)%2==0)
            tedad++;
    // check kardane divare samte rast
    if (dir == WEST)
    {
        if (cell[x][y]%2==0)
            if ((cell[next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]/DEAD)%2==0)
                tedad+=2;
    }
    else if ((cell[x][y]/(2*dir))%2==0)
        if ((cell[next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)]/DEAD)%2==0)
            tedad+=2;
            
    // check kardane divare samte chap.
    if (dir == NORTH) 
    {
        if ((cell[x][y]/8)%2==0)
            if ((cell[next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)]/DEAD)%2==0)
                tedad+=4;
    }
    else if ((cell[x][y]/(dir/2))%2==0)
        if ((cell[next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)]/DEAD)%2==0)
            tedad+=4;
    
    return tedad;
}




/* tavabe shabih sazie harakate robot.
*/
void semu_go(unsigned char dir , unsigned char* x, unsigned char* y)
{
    switch(dir)
        {
            case NORTH: *y=*y+1;break;
            case EAST : *x=*x+1;break;
            case SOUTH: *y=*y-1;break;
            case WEST : *x=*x-1;break;
        }
}

unsigned char semu_turnL(unsigned char dir)
{
    switch(dir)
        {
            case NORTH: return WEST ;
            case EAST : return NORTH;
            case SOUTH: return EAST ;
            case WEST : return SOUTH;
        }
}


unsigned char semu_turnR(unsigned char dir)
{
    switch(dir)
        {
            case NORTH: return EAST ;
            case EAST : return SOUTH;
            case SOUTH: return WEST ;
            case WEST : return NORTH;
        }
}

unsigned char semu_turnB(unsigned char dir)
{
    switch(dir)
        {
            case NORTH: return SOUTH;
            case EAST : return WEST ;
            case SOUTH: return NORTH;
            case WEST : return EAST ;
        }
}

unsigned char next_x(unsigned char dir, unsigned char x)
{
    switch (dir)
    {
        case NORTH: return x;
        case EAST : return x+1;
        case SOUTH: return x;
        case WEST : return x-1;
    }
}

unsigned char next_y(unsigned char dir, unsigned char y)
{
    switch (dir)
    {
        case NORTH: return y+1;
        case EAST : return y;
        case SOUTH: return y-1;
        case WEST : return y;
    }
}





unsigned char* LastGoodCrossed (unsigned char cell[3][16][16]) 
{
   
    unsigned char n,i,j;

    for (n=1;n<=14;n++)
        for (i = 0 ; i<16 ; i++)
            for (j=0 ; j<16 ; j++) 
                if ((cell[Divareha][i][j]/CROSSED)%2==1)
                    if (cell[1][i][j] == n || 1==1) 
                    {
                        if (cell[Divareha][i][j]%2==0)       if ((cell[Divareha][i][j+1]/CROSSED)  %2==0 && (cell[Divareha][i][j+1]/DEAD)  %2==0) {LastGoodCrossedLocation[0]=i; LastGoodCrossedLocation[1]=j; LastGoodCrossedLocation[2]=SOUTH; return LastGoodCrossedLocation;}
                        if ((cell[Divareha][i][j]/2)%2==0)   if ((cell[Divareha][i+1][j]/CROSSED)  %2==0 && (cell[Divareha][i+1][j]/DEAD)  %2==0) {LastGoodCrossedLocation[0]=i; LastGoodCrossedLocation[1]=j; LastGoodCrossedLocation[2]=WEST ; return LastGoodCrossedLocation;}
                        if ((cell[Divareha][i][j]/4)%2==0)   if ((cell[Divareha][i][j-1]/CROSSED)  %2==0 && (cell[Divareha][i][j-1]/DEAD)  %2==0) {LastGoodCrossedLocation[0]=i; LastGoodCrossedLocation[1]=j; LastGoodCrossedLocation[2]=NORTH; return LastGoodCrossedLocation;}
                        if ((cell[Divareha][i][j]/8)%2==0)   if ((cell[Divareha][i-1][j]/CROSSED)  %2==0 && (cell[Divareha][i-1][j]/DEAD)  %2==0) {LastGoodCrossedLocation[0]=i; LastGoodCrossedLocation[1]=j; LastGoodCrossedLocation[2]=EAST ; return LastGoodCrossedLocation;}
                    }
}


void GoodWayNumbering (unsigned char cell[3][16][16],unsigned char end_x, unsigned char end_y , unsigned char dir, unsigned char x, unsigned char y, unsigned char start_num) 
{    
    if ((cell[1][x][y]!=0 && cell[1][x][y]<start_num) || (cell[Divareha][x][y]/CROSSED)%2==0)
        return;
    else if(tedadrah(cell[Divareha],dir,x,y)==0 || ((x==end_x && y==end_y) && cell[1][x][y]>start_num))
    {
        start_num+=1;
        cell[1][x][y]=start_num;
        return;
    }
    else if (tedadrah(cell[Divareha],dir,x,y)==1)
    {
        start_num+=1;
        cell[1][x][y]=start_num;
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 1: GoodWayNumbering(cell,end_x,end_y,dir,next_x(dir,x),next_y(dir,y),start_num); return;
            case 2: GoodWayNumbering(cell,end_x,end_y,semu_turnR(dir),next_x(semu_turnR(dir),x),next_y(semu_turnR(dir),y),start_num); return;
            case 4: GoodWayNumbering(cell,end_x,end_y,semu_turnL(dir),next_x(semu_turnL(dir),x),next_y(semu_turnL(dir),y),start_num); return;
        }
        
    }
    else if (tedadrah(cell[Divareha],dir,x,y)==2)
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 3 : 
                {
                    start_num+=1;
                    cell[1][x][y]=start_num;
                    GoodWayNumbering(cell,end_x,end_y,dir,next_x(dir,x),next_y(dir,y),start_num);
                    GoodWayNumbering(cell,end_x,end_y,semu_turnR(dir),next_x(semu_turnR(dir),x),next_y(semu_turnR(dir),y),start_num); return;
                }
            case 5 : 
                {
                    start_num+=1;
                    cell[1][x][y]=start_num;
                    GoodWayNumbering(cell,end_x,end_y,dir,next_x(dir,x),next_y(dir,y),start_num);
                    GoodWayNumbering(cell,end_x,end_y,semu_turnL(dir),next_x(semu_turnL(dir),x),next_y(semu_turnL(dir),y),start_num);return;
                }
            case 6 : 
                {
                    start_num+=1;
                    cell[1][x][y]=start_num;
                    GoodWayNumbering(cell,end_x,end_y,semu_turnR(dir),next_x(semu_turnR(dir),x),next_y(semu_turnR(dir),y),start_num);
                    GoodWayNumbering(cell,end_x,end_y,semu_turnL(dir),next_x(semu_turnL(dir),x),next_y(semu_turnL(dir),y),start_num);return;
                }
        }
    else if (tedadrah(cell[Divareha],dir,x,y)==3)
    {
        start_num+=1;
        cell[1][x][y]=start_num;
        GoodWayNumbering(cell,end_x,end_y,dir,next_x(dir,x),next_y(dir,y),start_num);
        GoodWayNumbering(cell,end_x,end_y,semu_turnR(dir),next_x(semu_turnR(dir),x),next_y(semu_turnR(dir),y),start_num);
        GoodWayNumbering(cell,end_x,end_y,semu_turnL(dir),next_x(semu_turnL(dir),x),next_y(semu_turnL(dir),y),start_num);return;
    }
}





void Deading (unsigned char cell[3][16][16])
{
    unsigned i=0, j=0, Total;
    for (i=0; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            if ((cell[Divareha][i][j]/CROSSED)%2==0)
            {
                Total=0;
                if (cell[Divareha][i][j]%2==1)
                    Total++;
                else if ((cell[Divareha][i][j+1]/DEAD)%2==1)
                    Total++;
                if ((cell[Divareha][i][j]/2)%2==1)
                    Total++;
                else if ((cell[Divareha][i+1][j]/DEAD)%2==1)
                    Total++;
                if ((cell[Divareha][i][j]/4)%2==1)
                    Total++;
                else if ((cell[Divareha][i][j-1]/DEAD)%2==1)
                    Total++;
                if ((cell[Divareha][i][j]/8)%2==1)
                    Total++;
                else if ((cell[Divareha][i-1][j]/DEAD)%2==1)
                    Total++;
                if (Total>=3)
                    cell[Divareha][i][j] |= DEAD;
            }
}



unsigned char* dir_olaviat (unsigned char cell[3][16][16], unsigned char dir, unsigned char x, unsigned char y, unsigned char olaviatMode)
{
    DirOlaviatDirection[0]=semu_turnB(dir);
    DirOlaviatDirection[1]=semu_turnB(dir);
    DirOlaviatDirection[2]=semu_turnB(dir);
    DirOlaviatDirection[3]=semu_turnB(dir);
    
    if (olaviatMode==MarkazGaraFisaghores)   
    {
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 3:
                {
                    if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        DirOlaviatDirection[0]=semu_turnR(dir);
                        DirOlaviatDirection[1]=dir;
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] == cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        if (FisaGHores(next_x(semu_turnR(dir),x), next_y(semu_turnR(dir),y)) < FisaGHores(next_x(dir,x), next_y(dir,y)))
                        {
                            DirOlaviatDirection[0]=semu_turnR(dir);
                            DirOlaviatDirection[1]=dir;
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                        else
                        {
                            DirOlaviatDirection[0]=dir;
                            DirOlaviatDirection[1]=semu_turnR(dir);
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                    }
                    else 
                    {
                        DirOlaviatDirection[0]=dir;
                        DirOlaviatDirection[1]=semu_turnR(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 5:
                {
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[1]=dir;
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        if (FisaGHores(next_x(semu_turnL(dir),x), next_y(semu_turnL(dir),y)) < FisaGHores(next_x(dir,x), next_y(dir,y)))
                        {
                            DirOlaviatDirection[0]=semu_turnL(dir);
                            DirOlaviatDirection[1]=dir;
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                        else 
                        {
                            DirOlaviatDirection[0]=dir;
                            DirOlaviatDirection[1]=semu_turnL(dir);
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                    }
                    else
                    {
                        DirOlaviatDirection[0]=dir;
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 6:
                {
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)])
                    {
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[1]=semu_turnR(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)])
                    {
                        if (FisaGHores(next_x(semu_turnL(dir),x), next_y(semu_turnL(dir),y)) < FisaGHores(next_x(semu_turnR(dir),x), next_y(semu_turnR(dir),y)))
                        {
                            DirOlaviatDirection[0]=semu_turnL(dir);
                            DirOlaviatDirection[1]=semu_turnR(dir);
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                        else
                        {
                            DirOlaviatDirection[0]=semu_turnR(dir);
                            DirOlaviatDirection[1]=semu_turnL(dir);
                            DirOlaviatDirection[2]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                    }
                    else
                    {
                        DirOlaviatDirection[0]=semu_turnR(dir);
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 7:
                {
                    DirOlaviatDirection[0] = dir;
                    if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        DirOlaviatDirection[1]=DirOlaviatDirection[0];
                        DirOlaviatDirection[0]=semu_turnR(dir);
                    }
                    else if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] == cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        if (FisaGHores(next_x(semu_turnR(dir),x), next_y(semu_turnR(dir),y)) < FisaGHores(next_x(DirOlaviatDirection[0],x), next_y(DirOlaviatDirection[0],y)))
                        {
                            DirOlaviatDirection[1]=DirOlaviatDirection[0];
                            DirOlaviatDirection[0]=semu_turnR(dir);   
                        }
                        else
                            DirOlaviatDirection[1]=semu_turnR(dir);
                    }
                    else 
                        DirOlaviatDirection[1]=semu_turnR(dir);
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        DirOlaviatDirection[2]=DirOlaviatDirection[1];
                        DirOlaviatDirection[1]=DirOlaviatDirection[0];
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        if (FisaGHores(next_x(semu_turnL(dir),x), next_y(semu_turnL(dir),y)) < FisaGHores(next_x(DirOlaviatDirection[0],x), next_y(DirOlaviatDirection[0],y)))
                        {
                            DirOlaviatDirection[2]=DirOlaviatDirection[1];
                            DirOlaviatDirection[1]=DirOlaviatDirection[0];
                            DirOlaviatDirection[0]=semu_turnL(dir);
                            DirOlaviatDirection[3]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                        else 
                        {
                            if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[1],x)][next_y(DirOlaviatDirection[1],y)])
                            {
                                DirOlaviatDirection[2]=DirOlaviatDirection[1];
                                DirOlaviatDirection[1]=semu_turnL(dir);
                                DirOlaviatDirection[3]=semu_turnB(dir);
                                return DirOlaviatDirection;
                            }
                            else if(cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][next_x(DirOlaviatDirection[1],x)][next_y(DirOlaviatDirection[1],y)])
                            {
                                if (FisaGHores(next_x(semu_turnL(dir),x), next_y(semu_turnL(dir),y)) < FisaGHores(next_x(DirOlaviatDirection[1],x), next_y(DirOlaviatDirection[1],y)))
                                {
                                    DirOlaviatDirection[2]=DirOlaviatDirection[1];
                                    DirOlaviatDirection[1]=semu_turnL(dir);
                                    DirOlaviatDirection[3]=semu_turnB(dir);
                                    return DirOlaviatDirection;   
                                }
                                else
                                {
                                    DirOlaviatDirection[2]=semu_turnL(dir);
                                    DirOlaviatDirection[3]=semu_turnB(dir);
                                    return DirOlaviatDirection;
                                }
                            }
                        }
                    }
                    else if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[1],x)][next_y(DirOlaviatDirection[1],y)])
                    {
                        DirOlaviatDirection[2]=DirOlaviatDirection[1];
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if(cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][next_x(DirOlaviatDirection[1],x)][next_y(DirOlaviatDirection[1],y)])
                    {
                        if (FisaGHores(next_x(semu_turnL(dir),x), next_y(semu_turnL(dir),y)) < FisaGHores(next_x(DirOlaviatDirection[1],x), next_y(DirOlaviatDirection[1],y)))
                        {
                            DirOlaviatDirection[2]=DirOlaviatDirection[1];
                            DirOlaviatDirection[1]=semu_turnL(dir);
                            DirOlaviatDirection[3]=semu_turnB(dir);
                            return DirOlaviatDirection;   
                        }
                        else
                        {
                            DirOlaviatDirection[2]=semu_turnL(dir);
                            DirOlaviatDirection[3]=semu_turnB(dir);
                            return DirOlaviatDirection;
                        }
                    }
                    else 
                    {
                        DirOlaviatDirection[2]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
        }
    }
    else if (olaviatMode == MostaghimRastChap)
    {
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 3:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnR(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 5:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnL(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 6:
                {
                    DirOlaviatDirection[0]=semu_turnR(dir);
                    DirOlaviatDirection[1]=semu_turnL(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 7:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnR(dir);
                    DirOlaviatDirection[2]=semu_turnL(dir);
                    DirOlaviatDirection[3]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
        }
    }
    else if (olaviatMode == MostaghimChapRast)
    {
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 3:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnR(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 5:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnL(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 6:
                {
                    DirOlaviatDirection[0]=semu_turnL(dir);
                    DirOlaviatDirection[1]=semu_turnR(dir);
                    DirOlaviatDirection[2]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
            case 7:
                {
                    DirOlaviatDirection[0]=dir;
                    DirOlaviatDirection[1]=semu_turnL(dir);
                    DirOlaviatDirection[2]=semu_turnR(dir);
                    DirOlaviatDirection[3]=semu_turnB(dir);
                    return DirOlaviatDirection;
                }
        }
    }
    if (olaviatMode == MarkazGara)
    {
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 3:
                {
                    if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        DirOlaviatDirection[0]=semu_turnR(dir);
                        DirOlaviatDirection[1]=dir;
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    
                    }
                    else 
                    {
                        DirOlaviatDirection[0]=dir;
                        DirOlaviatDirection[1]=semu_turnR(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 5:
                {
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(dir,x)][next_y(dir,y)])
                    {
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[1]=dir;
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else
                    {
                        DirOlaviatDirection[0]=dir;
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 6:
                {
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)])
                    {
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[1]=semu_turnR(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else
                    {
                        DirOlaviatDirection[0]=semu_turnR(dir);
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[2]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
            case 7:
                {
                    DirOlaviatDirection[0] = dir;
                    if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        DirOlaviatDirection[1]=DirOlaviatDirection[0];
                        DirOlaviatDirection[0]=semu_turnR(dir);
                    }
                    else 
                        DirOlaviatDirection[1]=semu_turnR(dir);
                    if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[0],x)][next_y(DirOlaviatDirection[0],y)])
                    {
                        DirOlaviatDirection[2]=DirOlaviatDirection[1];
                        DirOlaviatDirection[1]=DirOlaviatDirection[0];
                        DirOlaviatDirection[0]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(DirOlaviatDirection[1],x)][next_y(DirOlaviatDirection[1],y)])
                    {
                        DirOlaviatDirection[2]=DirOlaviatDirection[1];
                        DirOlaviatDirection[1]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                    else
                    {
                        DirOlaviatDirection[2]=semu_turnL(dir);
                        DirOlaviatDirection[3]=semu_turnB(dir);
                        return DirOlaviatDirection;
                    }
                }
        }
    }
}


unsigned char FisaGHores(unsigned char x, unsigned char y)
{
    unsigned char   x1,y1;
    if (x<7)        x1=7-x;
    else if(x>8)    x1=x-8;
    else            x1=0;
    if (y<7)        y1=7-y;
    else if(y>8)    y1=y-8;
    else            y1=0;
    return          ((x1*x1)+(y1*y1));
}

  

void finding_P_2 (unsigned char cell[16][16])
{
    unsigned char i,j,m,k,bog=0;
    for (i=0; i<16 ;i++)
        for (j=0 ; j<16 ; j++)
        {
            if (j<7)
            {
                bog = 0;
                for (k=0 ; k<i ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=0 ; k<j ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=0 ; k<i ; k++)
                        for (m=0 ; m<j ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
                //|||||||||||||||||||\\
                
                bog = 0;
                for (k=i+1 ; k<16 ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=0 ; k<j ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=i+1 ; k<16 ; k++)
                        for (m=0 ; m<j ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
            } 
        }
        
    
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
        {
            if (i<7)
            {
                bog = 0;
                for (k=0 ; k<i ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=j+1 ; k<16 ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=0 ; k<i ; k++)
                        for (m=j+1 ; m<16 ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
                //---------------\\
                
                bog = 0;
                for (k=0 ; k<i ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=0 ; k<j ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=0 ; k<i ; k++)
                        for (m=0 ; m<j ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
            }
        }
        
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
        {
            if (i>8)
            {
                bog = 0;
                for (k=i+1 ; k<16 ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=j+1 ; k<16 ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=i+1 ; k<16 ; k++)
                        for (m=j+1 ; m<16 ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
                //---------------\\
                
                bog = 0;
                for (k=i+1 ; k<16 ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=0 ; k<j ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=i+1 ; k<16 ; k++)
                        for (m=0 ; m<j ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
            }
        }
    
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
        {
            if (j>8)
            {
                bog = 0;
                for (k=i+1 ; k<16 ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=j+1 ; k<16 ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=i+1 ; k<16 ; k++)
                        for (m=j+1 ; m<16 ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
                //---------------\\
                
                bog = 0;
                for (k=0 ; k<i ; k++)
                    if ((cell[k][j]/CROSSED)%2 != 1 && (cell[k][j]/DEAD)%2 != 1)
                    {
                        bog=1;
                        break;
                    }
                for (k=j+1 ; k<16 ; k++)
                    if ((cell[i][k]/CROSSED)%2 != 1 && (cell[i][k]/DEAD)%2 != 3)
                    {
                        bog=1;
                        break;
                    }
                
                if (bog == 0)
                {
                    for (k=0 ; k<i ; k++)
                        for (m=j+1 ; m<16 ; m++)
                            if ((cell[k][m]/CROSSED)%2!=1)
                                cell[k][m]|=DEAD;
                }
                
            }
        }
}




void F_P_3 (unsigned char cell[16][16])
{
    unsigned char i,j,m,k,l,bog;
    for (i=0 ; i<7 ; i++)
        for (j=0 ; j<16 ; j++)
            for (m=j+1 ; m<16 ; m++)
            {
                bog=0;
                for (k=j+1 ; k<m ; k++)
                {
                    if ((cell[i][k]/CROSSED)%2!=1 && (cell[i][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                
                for (k=0 ; k<i ; k++)
                {
                    if ((cell[k][j]/CROSSED)%2!=1 && (cell[k][j]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                    
                    if ((cell[k][m]/CROSSED)%2!=1 && (cell[k][m]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                if (bog == 0)
                {
                    for (k=0 ; k<i ; k++)
                        for (l= j+1 ; l<m ; l++)
                            if ((cell[k][l]/CROSSED)%2!=1)
                                cell[k][l]|=DEAD;
                }
            }
            
    for (i=9 ; i<16; i++)
        for (j=0 ; j<16 ; j++)
            for (m=j+1 ; m<16 ; m++)
            {
                bog=0;
                for (k=j+1 ; k<m ; k++)
                {
                    if ((cell[i][k]/CROSSED)%2!=1 && (cell[i][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                
                for (k=i+1; k<16 ; k++)
                {
                    if ((cell[k][j]/CROSSED)%2!=1 && (cell[k][j]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                    
                    if ((cell[k][m]/CROSSED)%2!=1 && (cell[k][m]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                if (bog == 0)
                {
                    for (k=i+1 ; k<16 ; k++)
                        for (l= j+1 ; l<m ; l++)
                            if ((cell[k][l]/CROSSED)%2!=1)
                                cell[k][l]|=DEAD;
                }
            }
            
    for (j=0 ; j<7 ; j++)
        for (i=0 ; i<16 ; i++)
            for (m=i+1 ; m<16 ; m++)
            {
                bog=0;
                for (k=i+1 ; k<m ; k++)
                {
                    if ((cell[k][j]/CROSSED)%2!=1 && (cell[k][j]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                for (k=0; k<j ; k++)
                {
                    if ((cell[i][k]/CROSSED)%2!=1 && (cell[i][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                    
                    if ((cell[m][k]/CROSSED)%2!=1 && (cell[m][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                if (bog == 0)
                {
                    for (k=0 ; k<j ; k++)
                        for (l= i+1 ; l<m ; l++)
                            if ((cell[l][k]/CROSSED)%2!=1)
                                cell[l][k]|=DEAD;
                }
            }
    
    for (j=9 ; j<16 ; j++)
        for (i=0 ; i<16 ; i++)
            for (m=i+1 ; m<16 ; m++)
            {
                bog=0;
                for (k=i+1 ; k<m ; k++)
                {
                    if ((cell[k][j]/CROSSED)%2!=1 && (cell[k][j]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                for (k=j+1; k<16 ; k++)
                {
                    if ((cell[i][k]/CROSSED)%2!=1 && (cell[i][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                    
                    if ((cell[m][k]/CROSSED)%2!=1 && (cell[m][k]/DEAD)%2!=1)
                    {
                        bog = 1;
                        break;
                    }
                }
                if (bog == 0)
                {
                    for (k=j+1 ; k<16 ; k++)
                        for (l= i+1 ; l<m ; l++)
                            if ((cell[l][k]/CROSSED)%2!=1)
                                cell[l][k]|=DEAD;
                }
            }
}


void F_P_4 (unsigned char cell[16][16])
{
    unsigned char i,j,k,m,n,l,bog=0;
    for (i=0 ; i<7 ; i++)
        for (j=0 ; j<16 ; j++)
            for (k=i+1 ; k<7 ; k++)
                for (m=j+1 ; m<16 ; m++)
                {
                    bog=0;
                    for (n=i+1 ; n<k ; n++)
                    {
                        if ((cell[n][j]/CROSSED)%2 != 1 && (cell[n][j]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[n][m]/CROSSED)%2 != 1 && (cell[n][m]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    for (n=j+1 ; n<m ; n++)
                    {
                        if ((cell[i][n]/CROSSED)%2 != 1 && (cell[i][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[k][n]/CROSSED)%2 != 1 && (cell[k][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    if (bog == 0)
                    {
                        for (n = i+1 ; n<k ; n++)
                            for (l = j+1 ; l<m ; l++)
                                if ((cell[n][l]/CROSSED)%2!=1)
                                    cell[n][l]|=DEAD;
                    }
                }
    
    for (i=9 ; i<16 ; i++)
        for (j=0 ; j<16 ; j++)
            for (k=i+1 ; k<16 ; k++)
                for (m=j+1 ; m<16 ; m++)
                {
                    bog=0;
                    for (n=i+1 ; n<k ; n++)
                    {
                        if ((cell[n][j]/CROSSED)%2 != 1 && (cell[n][j]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[n][m]/CROSSED)%2 != 1 && (cell[n][m]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    for (n=j+1 ; n<m ; n++)
                    {
                        if ((cell[i][n]/CROSSED)%2 != 1 && (cell[i][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[k][n]/CROSSED)%2 != 1 && (cell[k][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    if (bog == 0)
                    {
                        for (n = i+1 ; n<k ; n++)
                            for (l = j+1 ; l<m ; l++)
                                if ((cell[n][l]/CROSSED)%2!=1)
                                    cell[n][l]|=DEAD;
                    }
                }
                
    for (i=0 ; i<16 ; i++)
        for (j=0 ; j<7 ; j++)
            for (k=i+1 ; k<16 ; k++)
                for (m=j+1 ; m<7 ; m++)
                {
                    bog=0;
                    for (n=i+1 ; n<k ; n++)
                    {
                        if ((cell[n][j]/CROSSED)%2 != 1 && (cell[n][j]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[n][m]/CROSSED)%2 != 1 && (cell[n][m]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    for (n=j+1 ; n<m ; n++)
                    {
                        if ((cell[i][n]/CROSSED)%2 != 1 && (cell[i][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[k][n]/CROSSED)%2 != 1 && (cell[k][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    if (bog == 0)
                    {
                        for (n = i+1 ; n<k ; n++)
                            for (l = j+1 ; l<m ; l++)
                                if ((cell[n][l]/CROSSED)%2!=1)
                                    cell[n][l]|=DEAD;
                    }
                }
                
    for (i=0 ; i<16 ; i++)
        for (j=9 ; j<16 ; j++)
            for (k=i+1 ; k<16 ; k++)
                for (m=j+1 ; m<16 ; m++)
                {
                    bog=0;
                    for (n=i+1 ; n<k ; n++)
                    {
                        if ((cell[n][j]/CROSSED)%2 != 1 && (cell[n][j]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[n][m]/CROSSED)%2 != 1 && (cell[n][m]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    for (n=j+1 ; n<m ; n++)
                    {
                        if ((cell[i][n]/CROSSED)%2 != 1 && (cell[i][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                        if ((cell[k][n]/CROSSED)%2 != 1 && (cell[k][n]/DEAD)%2 != 1)
                        {
                            bog = 1;
                            break;
                        }
                    }
                    if (bog == 0)
                    {
                        for (n = i+1 ; n<k ; n++)
                            for (l = j+1 ; l<m ; l++)
                                if ((cell[n][l]/CROSSED)%2!=1)
                                    cell[n][l]|=DEAD;
                    }
                }
}


void dead1(unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir)
{
    if ((cell[Divareha][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)]/DEAD)%2==1)
    {
        if (tedadrah (cell[Divareha],dir,x,y)==1) 
        {
            cell[Divareha][x][y] |= CROSSED;
            cell[Divareha][x][y] |= DEAD;
        }
        else
            cell[Divareha][x][y] |= CROSSED;
    }
    else
        cell[Divareha][x][y] |= CROSSED;
}



/*
*    tabe flood_fill  be etbedaee tarin shekele momken
*    255 bar kolle khune ha ro check mikone k age meghdareshun bashe
*    (koochektarin meghdare khune haye mojaver i k rah dare + 1)
*/
void Flood_fill (unsigned char cell[3][16][16])
{
    unsigned char i,j,n;
    for (i=0 ; i< 16 ; i++)
        for (j=0 ; j<16 ; j++)
            cell[Arzesh][i][j] = 255;
    cell[Arzesh][7][7] = 0;
    cell[Arzesh][7][8] = 0;
    cell[Arzesh][8][7] = 0;
    cell[Arzesh][8][8] = 0;
    
    for (n=0 ; n<255 ; n++)
        for (i=0 ; i<16 ; i++)
            for (j=0 ; j<16 ; j++)
            {
                if (cell[Divareha][i][j]%2==0)
                    if ((cell[Divareha][i][j+1]/DEAD)%2==0)
                        if(cell[Arzesh][i][j+1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j+1]+1;
                if ((cell[Divareha][i][j]/2)%2==0)
                    if ((cell[Divareha][i+1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i+1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i+1][j]+1;
                if ((cell[Divareha][i][j]/4)%2==0)
                    if ((cell[Divareha][i][j-1]/DEAD)%2==0)
                        if (cell[Arzesh][i][j-1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j-1]+1;
                if ((cell[Divareha][i][j]/8)%2==0)
                    if ((cell[Divareha][i-1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i-1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i-1][j]+1;
            }
    
} 


void flood_fill2(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y, unsigned char *dir, unsigned char Flood_Fill_counter)
{   
    unsigned char min = 255;
    unsigned char temp = 0;   
    
    if (NoEastWall(&cell[Divareha][*x][*y]))
        min = cell[Arzesh][*x + 1][*y];
    if (NoNorthWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x][*y+1])
            min = cell[Arzesh][*x][*y+1];
    if (NoSouthWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x][*y-1])
            min = cell[Arzesh][*x][*y-1];
    if (NoWestWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x-1][*y])
            min = cell[Arzesh][*x-1][*y];
    cell[Arzesh][*x][*y] = min + 1;            

    if (*x<15)
    {
        temp = *x+1;
        if (NeedToFloodFill(cell,&temp,y))
            flood_fill2(cell, &temp, y, dir, Flood_Fill_counter+1);
    }
    if (*y<15)
    {
        temp = *y+1;
        if (NeedToFloodFill(cell,x,&temp))
            flood_fill2(cell, x, &temp, dir, Flood_Fill_counter+1);
    }
    if (*x>0)
    {
        temp = *x-1;
        if (NeedToFloodFill(cell,&temp,y))
            flood_fill2(cell, &temp, y, dir, Flood_Fill_counter+1);
    }
    if (*y>0)
    {   
        temp = *y-1;
        if (NeedToFloodFill(cell,x,&temp))
            flood_fill2(cell, x, &temp, dir, Flood_Fill_counter+1);
    }
    
    if (Flood_Fill_counter == 0)
    {
        unsigned char i,j;
        for (i=0 ; i<16 ; i++)
           for (j=0 ; j<16 ; j++)
                if(NeedToFloodFill(cell,&i,&j)) 
                    flood_fill2(cell,&i,&j,dir,0);
    }
}


/*
* tabe' bazghashte flood_fill ke kamtarin rah ra baraye residan b khuneye aval hesab mikonad
*/
void flood_fill3(unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir, unsigned char Flood_Fill_counter)
{   
    
    unsigned char i,j;
    cell[Arzesh][0][0] = 0;
    unsigned char min = 255;
    
    
    /* dar surati k khuneye x , y be khune ee dar atrafeshun rah dashte bashan ke
    *  ke az meghdare khunee ye x ,y 1 khune kamtar bashe return mikonim. 
    *  digar niazi b jolotar raftan nist.
    */
    if ((cell[Divareha][x][y]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x)][next_y(dir,y)] == cell[Arzesh][x][y] - 1)
        return;
    if ((cell[Divareha][x][y]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] == cell[Arzesh][x][y] - 1)
        return;
    if ((cell[Divareha][x][y]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][x][y] - 1)
        return;
    /*
    * agar avalin shorue tabe' nabashad khuneye poshte sarash ra ham check mikonad.
    */
    if (Flood_Fill_counter > 0)
        if ((cell[Divareha][x][y]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)] == cell[Arzesh][x][y] - 1)
            return;
    
   // if(Flood_Fill_counter==255)
    //    return;
    
    /*
    * ager khuneye x ,y b khuneyee kochektar az khodash rah nadasht meghdare jadidash mishavad 
    * koochektarin meghdare khane haye atarafash k b anha rah darad + 1.
    */
    if ((cell[Divareha][x][y]/dir)%2 == 0)
        min = cell[Arzesh][next_x(dir,x)][next_y(dir,y)];
    if ((cell[Divareha][x][y]/semu_turnR(dir))%2 == 0)
        if (min > cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)])
            min = cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)];
    if ((cell[Divareha][x][y]/semu_turnL(dir))%2 == 0)
        if (min > cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)])
            min = cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)];
    if ((cell[Divareha][x][y]/semu_turnB(dir))%2 == 0)
        if (min > cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)])
            min = cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)];
    cell[Arzesh][x][y] = min+1;
    

    /*
    *  hal check check mikonam va agar niaz bud flood fill ra baraye khune haye atrafash ejra mikonad.
    */
        if (x < 14)
            if (!((cell[Divareha][x+1][y]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x+1)][next_y(dir,y)] == cell[Arzesh][x+1][y] - 1))
                if (!((cell[Divareha][x+1][y]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x+1)][next_y(semu_turnR(dir),y)] == cell[Arzesh][x+1][y] - 1))
                    if (!((cell[Divareha][x+1][y]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x+1)][next_y(semu_turnL(dir),y)] == cell[Arzesh][x+1][y] - 1))
                        if (!((cell[Divareha][x+1][y]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x+1)][next_y(semu_turnB(dir),y)] == cell[Arzesh][x+1][y] - 1))
                            flood_fill3(cell, x+1, y, dir, Flood_Fill_counter+1);
        if (y < 14)
            if (!((cell[Divareha][x][y+1]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x)][next_y(dir,y+1)] == cell[Arzesh][x][y+1] - 1))
                if (!((cell[Divareha][x][y+1]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y+1)] == cell[Arzesh][x][y+1] - 1))
                    if (!((cell[Divareha][x][y+1]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y+1)] == cell[Arzesh][x][y+1] - 1))
                        if (!((cell[Divareha][x][y+1]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y+1)] == cell[Arzesh][x][y+1] - 1))
                            flood_fill3(cell, x, y+1, dir, Flood_Fill_counter+1); 
        if (x > 0 && (x != 1 || y!=0))
            if (!((cell[Divareha][x-1][y]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x-1)][next_y(dir,y)] == cell[Arzesh][x-1][y] - 1))
                if (!((cell[Divareha][x-1][y]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x-1)][next_y(semu_turnR(dir),y)] == cell[Arzesh][x-1][y] - 1))
                    if (!((cell[Divareha][x-1][y]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x-1)][next_y(semu_turnL(dir),y)] == cell[Arzesh][x-1][y] - 1))
                        if (!((cell[Divareha][x-1][y]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x-1)][next_y(semu_turnB(dir),y)] == cell[Arzesh][x-1][y] - 1))
                            flood_fill3(cell, x-1, y, dir, Flood_Fill_counter+1);
        if (y > 0 && (y != 1 || x!=0))
            if (!((cell[Divareha][x][y-1]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x)][next_y(dir,y-1)] == cell[Arzesh][x][y-1] - 1))
                if (!((cell[Divareha][x][y-1]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y-1)] == cell[Arzesh][x][y-1] - 1))
                    if (!((cell[Divareha][x][y-1]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y-1)] == cell[Arzesh][x][y-1] - 1))
                        if (!((cell[Divareha][x][y-1]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y-1)] == cell[Arzesh][x][y-1] - 1))
                            flood_fill3(cell, x, y-1, dir, Flood_Fill_counter+1);

        /*
        * dar payan agar lazem bud flood fill ra baray e khodash dobare ejra mikonad.
        */
        if (!((cell[Divareha][x][y]/dir)%2 == 0 && cell[Arzesh][next_x(dir,x)][next_y(dir,y)] == cell[Arzesh][x][y] - 1))
                if (!((cell[Divareha][x][y]/semu_turnR(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] == cell[Arzesh][x][y] - 1))
                    if (!((cell[Divareha][x][y]/semu_turnL(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] == cell[Arzesh][x][y] - 1))
                        if (!((cell[Divareha][x][y]/semu_turnB(dir))%2 == 0 && cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)] == cell[Arzesh][x][y] - 1))
                            flood_fill3(cell, x, y, dir, Flood_Fill_counter+1);
}


/*
* ebtedaee tarin ravesh flood fill ke har khune ro 255 bar check mikonad,
* yani har bar ejra 255*16*16 bar halghe ro tekrar mikonad.
*/
void Flood_fill1 (unsigned char cell[3][16][16])
{
    unsigned char i,j,n;
    for (i=0 ; i< 16 ; i++)
        for (j=0 ; j<16 ; j++)
            cell[Arzesh][i][j] = 255;
             
    cell[Arzesh][0][0] = 0;
    
    for (n=0 ; n<255 ; n++)
        for (i=0 ; i<16 ; i++)
            for (j=0 ; j<16 ; j++)
            {
                if (cell[Divareha][i][j]%2==0)
                    //if ((cell[Divareha][i][j+1]/DEAD)%2==0)
                        if(cell[Arzesh][i][j+1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j+1]+1;
                if ((cell[Divareha][i][j]/2)%2==0)
                    //if ((cell[Divareha][i+1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i+1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i+1][j]+1;
                if ((cell[Divareha][i][j]/4)%2==0)
                    //if ((cell[Divareha][i][j-1]/DEAD)%2==0)
                        if (cell[Arzesh][i][j-1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j-1]+1;
                if ((cell[Divareha][i][j]/8)%2==0)
                    //if ((cell[Divareha][i-1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i-1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i-1][j]+1;
            }
}      



/*
*    algoorithm aslie barname. ba estefade az flood fill.
*    
*
*
*/
void alg4 ()
{
     // baraye zakhire etelaate mokhtalef e har khune.
    unsigned char cell[3][16][16]={0};
    // moteghayer haye morede niaz dar toole tabe'
    unsigned char dir=NORTH , x=0, y=0, end_x ,end_y ,end_dir;
    int counter=0;
    int i=0,j=0;

    unsigned char lastx=0;
    unsigned char lasty=0;

    
    // sakhtane divare haye khane haye kenari
    for (i=0 ; i<16 ; i++)
    {
        cell[Divareha][i][0] |= SOUTH; // 0100 adade 4 baraye divare haye paeeni.
        cell[Divareha][i][15]|= NORTH; // 0001 adade 1 baraye divare haye balaee.
        cell[Divareha][0][i] |= WEST ; // 1000 adade 8 baraye divare haye chap.
        cell[Divareha][15][i]|= EAST ; // 0010 adade 2 baraye divare haye samte rast.
    }
    
    // arzesh gozarie avalie khane ha. (ba pishfarze nabudane hich divare ee)
    cell_numbering(cell);
    
    // meghdar dehie avalie khune shoru.
    //cell[Divareha][0][0] |= CROSSED; // alamat gozari baraye rafte she 
    //cell[Divareha][0][0] |= EAST + WEST + SOUTH; // moshakhas shodane divare haye shoru
    //cell[Divareha][1][0] |= WEST + SOUTH; // gozashtane divare haye khune samte raste shoru k divare chap darad.

    Flood_fill(cell); // fara khunie algorithme flood_fill
    //drow2(cell); // rasm e zamin
    
    /*
    *     halgheye aslie tabe baraye k ta residan e be khuneye 
    *     hadaf tekrar mishavad
    */
    
    gotoxy(0,7);
    for (i=0 ; i<33 ; i++)
        printf("||                                                                           || ");
    
    Drow_Maze_Raw(cell,6,39);
    
    while(!((x==7 || x==8)&&(y==7 || y==8))) 
    {
        get_wall1(cell,x,y,dir); // divare haye khune jadid ra migirad.
        cell[Divareha][x][y] |= CROSSED;  // moshakhas kardane khune ee k tush hastim b onvane CROSSED
        
        Drow_OneCell_Raw(&cell[Divareha][x][y],x, y,6,39);
        
        printInCell(lastx,lasty,0);
        printInCell(x,y,dir); // rasme robat.
        lastx = x;
        lasty = y;
        
        sleep(50);
        getch();
        
        if (NeedToFloodFill(cell,&x,&y))
            flood_fill2(cell, &x, &y, &dir, 0); // ba fara khanie tabe'e fool_fill2 arzesh gozarie jadid ra anjam midahad.
        dir = floodthink (cell, dir, x, y, alg);  // moshakhas kardane harkat badi
        semu_go(dir,&x,&y); // ye khane dar masire jadid harkat mikonad. x va y ra tagheer midahad.

        counter++;
        gotoxy (4,41);
        printf ("MoveCounter : %d  ",counter);
    }
    printInCell(lastx,lasty,0);
    printInCell(x,y,dir); 
    lastx = x;
    lasty = y;
    
    gotoxy (4,42);
    unsigned char k = NeedToExplore(cell);
    printf ("NeedtoGo : x: %d y: %d  ", k/16,k%16);
        
    getch();
    
    //First_Cell_Values_Prof(cell,k/16,k%16);
    while (k!= 119 && k!= 120 && k!= 135 && k!= 136)
    {
        Flood_fill(cell);    
        k = NeedToExplore(cell);
        if (k==0)
            break;
        First_Cell_Values_Prof(cell,k/16,k%16);
        
        gotoxy (4,42);
        printf ("NeedtoGo : x: %d y: %d  new K", k/16,k%16);
        getch();
        while(!(x==k/16 && y==k%16))
        {
            
                get_wall1(cell,x,y,dir);
                cell[Divareha][x][y] |= CROSSED;
                Flood_fill(cell);    
                k = NeedToExplore(cell);
                if (k==0)
                    break;
                First_Cell_Values_Prof(cell,k/16,k%16);
            
            Flood_Fill_Prof(cell,&x,&y,&dir,0,(unsigned char)k/16,(unsigned char)k%16);
            drow2(cell);
            
            printInCell(x,y,dir);
            gotoxy(0,0);
            
            dir = floodthink (cell, dir, x, y,3);
            //cell[Divareha][x][y] |= CROSSED;
            semu_go(dir,&x,&y);
            counter++;
            gotoxy (4,41);
            
            printf ("MoveCounter : %d  ",counter);
            
            
            gotoxy (4,42);
            printf ("NeedtoGo : x: %d y: %d                ", k/16,k%16);
            getch();
        }
        cell[Divareha][x][y] |= CROSSED; 
    }
    getch();
    First_Cell_Values_Prof(cell,0,0);
    while(!(x==0&&y==0))
    {
        get_wall1(cell,x,y,dir);
        Flood_fill1(cell);
        drow2(cell);
        
        
        printInCell(x,y,dir);
        sleep(100);
        dir = floodthink (cell, dir, x, y,alg);
        cell[Divareha][x][y] |= CROSSED;
        semu_go(dir,&x,&y);
        counter++;
        gotoxy (4,41);
        printf ("MoveCounter : %d  ",counter);
    }
    Flood_fill(cell);
    while(!((x==7 || x==8)&&(y==7 || y==8)))
    {
        get_wall1(cell,x,y,dir);
        flood_fill2(cell,&x,&y,&dir,0);
        getch();
        drow2(cell);    
        printInCell(x,y,dir);
        
        dir = floodthink (cell, dir, x, y,alg);
        cell[Divareha][x][y] |= CROSSED;
        semu_go(dir,&x,&y);
        getch();
        counter++;
        gotoxy (4,41);
        printf ("MoveCounter : %d  ",counter);
    }   
    
    
    
    getch();
    semu_turnB(dir);
    while(!(x==0 && y==0))
    {
        
        get_wall1(cell,x,y,dir);
        Flood_fill1(cell);
        drow2(cell);
        
        
        printInCell(x,y,dir);
        sleep(100);
        dir = floodthink (cell, dir, x, y,3);
        cell[Divareha][x][y] |= CROSSED;
        semu_go(dir,&x,&y);
        counter++;
        gotoxy (4,41);
        printf ("MoveCounter : %d  ",counter);
    }    
}


/*
* in tabe baraye taeen jahate badi ba tavajoh b mohasebate tabe flood fill va
* adde nesbat dade shode be khune Not.
*/
unsigned char floodthink (unsigned char cell[3][16][16], unsigned char dir, unsigned char x, unsigned char y,unsigned char alg1)
{
    if (tedadrah(cell[Divareha],dir,x,y) == 0)
        return semu_turnB(dir);
    else if (tedadrah(cell[Divareha],dir,x,y) == 1)
        switch (wich_ways(cell[Divareha],dir,x,y))
        {
            case 1: if (cell[Arzesh][next_x(dir,x)][next_y(dir,y)] < cell[Arzesh][x][y] || (cell[Arzesh][next_x(dir,x)][next_y(dir,y)] < cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)])) return dir; else return semu_turnB(dir); break;
            case 2: if (cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][x][y] || cell[Arzesh][next_x(semu_turnR(dir),x)][next_y(semu_turnR(dir),y)] < cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)]) return semu_turnR(dir); else return semu_turnB(dir); break;
            case 4: if (cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][x][y] || cell[Arzesh][next_x(semu_turnL(dir),x)][next_y(semu_turnL(dir),y)] < cell[Arzesh][next_x(semu_turnB(dir),x)][next_y(semu_turnB(dir),y)]) return semu_turnL(dir); else return semu_turnB(dir); break;
        }
    else if (tedadrah(cell[Divareha],dir,x,y) == 2)
    {
        if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[0],y)]+1 == cell[Arzesh][x][y])
            return dir_olaviat(cell,dir,x,y,alg1)[0];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[1],y)]+1 == cell[Arzesh][x][y])
            return dir_olaviat(cell,dir,x,y,alg1)[1];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[0],y)]+1 == cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[2],y)])
            return dir_olaviat(cell,dir,x,y,alg1)[0];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[1],y)]+1 == cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[2],y)])
            return dir_olaviat(cell,dir,x,y,alg1)[1];
        else 
            return dir_olaviat(cell,dir,x,y,alg1)[2];
    }
    else if (tedadrah(cell[Divareha],dir,x,y) == 3)
    {
        if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[0],y)]+1 == cell[Arzesh][x][y])
            return dir_olaviat(cell,dir,x,y,alg1)[0];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[1],y)]+1 == cell[Arzesh][x][y])
            return dir_olaviat(cell,dir,x,y,alg1)[1];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[2],y)]+1 == cell[Arzesh][x][y])
            return dir_olaviat(cell,dir,x,y,alg1)[2];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[0],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[0],y)]+1 == cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[3],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[3],y)])
            return dir_olaviat(cell,dir,x,y,alg1)[0];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[1],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[1],y)]+1 == cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[3],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[3],y)])
            return dir_olaviat(cell,dir,x,y,alg1)[1];
        else if (cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[2],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[2],y)]+1 == cell[Arzesh][next_x(dir_olaviat(cell,dir,x,y,alg1)[3],x)][next_y(dir_olaviat(cell,dir,x,y,alg1)[3],y)])
            return dir_olaviat(cell,dir,x,y,alg1)[2];
        else 
            return dir_olaviat(cell,dir,x,y,alg1)[3];
    }   
}

void Crossed_Way_Show (unsigned char cell[3][16][16],unsigned char x, unsigned char y, unsigned char dir)
{
    unsigned char dirTemp=dir;
    unsigned char counter,flag;
    unsigned char x1=x;
    unsigned char y1=y;
    unsigned char i=0,j=0;  
    
    ways[0] = '\0';
    dir = floodthink (cell, dir, x, y,alg);
    semu_go(dir,&x,&y);
    while ((cell[Divareha][x][y]/CROSSED)%2==1)
    {
        ways[i] = x*16+y;
        dir = floodthink (cell, dir, x, y,alg);
        semu_go(dir,&x,&y);
        i++;
    }
    
    ways[i] = x*16+y;
    ways[++i]='\0';
    i=0;
    
    for (i=0 ; i<255 ; i++)
        masir[i] = '\0';
    i=0;
    j=0;
    x = ways[0]/16;
    y = ways[0]%16;
    while (ways[i]!='\0')
   {
        counter = 0;
        while (next_y(dirTemp,y1) == y && next_x(dirTemp,x1) == x && ways[i]!='\0')
        {
                counter ++;            
                x1 = x;
                y1 = y;
                i++;
                x = ways[i]/16;
                y = ways[i]%16;
        }
        if (counter > 0)
        {
            masir[j]=counter;
            j++;
            continue;
            
        }
        if (next_y(semu_turnR(dirTemp),y1) == y && next_x(semu_turnR(dirTemp),x1) == x)
        {
            masir[j]=254;
            dirTemp=semu_turnR(dirTemp);
            j++;
            continue;
        }
        if (next_y(semu_turnL(dirTemp),y1) == y && next_x(semu_turnL(dirTemp),x1) == x)
        {
            masir[j]=253;
            dirTemp=semu_turnL(dirTemp);
            j++;
            continue;
        }
        if (next_y(semu_turnB(dirTemp),y1) == y && next_x(semu_turnB(dirTemp),x1) == x)
        {
            masir[j]=252;
            dirTemp=semu_turnB(dirTemp);
            j++;
            continue;
        }
    }
    masir[j]=1;
    masir[j]='\0';
}


unsigned char NoFrontWall(unsigned char *OneCell, unsigned char *dir)
{
    return (*OneCell / *dir)%2 == 0;
}
unsigned char NoRightWall(unsigned char *OneCell, unsigned char *dir)
{
    return (*OneCell / semu_turnR(*dir))%2 == 0;
}
unsigned char NoLeftWall(unsigned char *OneCell, unsigned char *dir)
{
    return (*OneCell / semu_turnL(*dir))%2 == 0;
}
unsigned char NoBackWall(unsigned char *OneCell, unsigned char *dir)
{
    return (*OneCell / semu_turnB(*dir))%2 == 0;
}


unsigned char NoNorthWall(unsigned char *OneCell)
{
    return *OneCell%2 == 0;
}
unsigned char NoEastWall(unsigned char *OneCell)
{
    return (*OneCell/EAST)%2 == 0;
}
unsigned char NoWestWall(unsigned char *OneCell)
{   
    return (*OneCell/WEST)%2 == 0;
}
unsigned char NoSouthWall(unsigned char *OneCell)
{
    return (*OneCell/SOUTH)%2 == 0;
}


unsigned char NeedToFloodFill(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y)
{
    if ((*x==7||*x==8)&&(*y==7||*y==8))
        return 0;
    
    if (NoEastWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x+1][*y])
            return 0;

    if (NoWestWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x-1][*y])
            return 0;

    if (NoNorthWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x][*y+1])
            return 0;

    if (NoSouthWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x][*y-1])
            return 0;
    
    if (cell[Divareha][*x][*y] != 15)
        return 1;
    else
        return 0;
}


unsigned char NeedToFloodFillProf(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y,unsigned char DestX,unsigned char DestY)
{
    if (*x==DestX&&*y==DestY)
        return 0;
    
    if (NoEastWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x+1][*y])
            return 0;

    if (NoWestWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x-1][*y])
            return 0;

    if (NoNorthWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x][*y+1])
            return 0;

    if (NoSouthWall(&cell[Divareha][*x][*y]))
        if (cell[Arzesh][*x][*y] > cell[Arzesh][*x][*y-1])
            return 0;
    
    if (cell[Divareha][*x][*y] != 15)
        return 1;
    else
        return 0;
}


void Flood_Fill_Prof(unsigned char cell[3][16][16],unsigned char *x, unsigned char *y, unsigned char *dir, unsigned char Flood_Fill_counter,unsigned char StartX, unsigned char StartY)
{   
    unsigned char min = 255;
    unsigned char temp = 0;   
    
    if (NoEastWall(&cell[Divareha][*x][*y]))
        min = cell[Arzesh][*x + 1][*y];
    if (NoNorthWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x][*y+1])
            min = cell[Arzesh][*x][*y+1];
    if (NoSouthWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x][*y-1])
            min = cell[Arzesh][*x][*y-1];
    if (NoWestWall(&cell[Divareha][*x][*y]))
        if (min > cell[Arzesh][*x-1][*y])
            min = cell[Arzesh][*x-1][*y];
    cell[Arzesh][*x][*y] = min + 1;            

    if (*x<15)
    {
        temp = *x+1;
        if (NeedToFloodFillProf(cell,&temp,y,StartX,StartY))
            Flood_Fill_Prof(cell, &temp, y, dir, Flood_Fill_counter+1,StartX,StartY);
    }
    if (*y<15)
    {
        temp = *y+1;
        if (NeedToFloodFillProf(cell,x,&temp,StartX,StartY))
            Flood_Fill_Prof(cell, x, &temp, dir, Flood_Fill_counter+1,StartX,StartY);
    }
    if (*x>0)
    {
        temp = *x-1;
        if (NeedToFloodFillProf(cell,&temp,y,StartX,StartY))
            Flood_Fill_Prof(cell, &temp, y, dir, Flood_Fill_counter+1,StartX,StartY);
    }
    if (*y>0)
    {   
        temp = *y-1;
        if (NeedToFloodFillProf(cell,x,&temp,StartX,StartY))
            Flood_Fill_Prof(cell, x, &temp, dir, Flood_Fill_counter+1,StartX,StartY);
    }
    
    if (Flood_Fill_counter == 0)
    {
        unsigned char i,j;
        for (i=0 ; i<16 ; i++)
           for (j=0 ; j<16 ; j++)
                if(NeedToFloodFillProf(cell,&i,&j,StartX,StartY)) 
                    Flood_Fill_Prof(cell,&i,&j,dir,0,StartX,StartY);
    }
}

void First_Cell_Values_Prof (unsigned char cell[3][16][16],unsigned char DestX,unsigned char DestY)
{
    unsigned char i,j,n;
    for (i=0 ; i< 16 ; i++)
        for (j=0 ; j<16 ; j++)
            cell[Arzesh][i][j] = 255;
             
    cell[Arzesh][DestX][DestY] = 0;
    
    for (n=0 ; n<255 ; n++)
        for (i=0 ; i<16 ; i++)
            for (j=0 ; j<16 ; j++)
            {
                if (cell[Divareha][i][j]%2==0)
                    //if ((cell[Divareha][i][j+1]/DEAD)%2==0)
                        if(cell[Arzesh][i][j+1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j+1]+1;
                if ((cell[Divareha][i][j]/2)%2==0)
                    //if ((cell[Divareha][i+1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i+1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i+1][j]+1;
                if ((cell[Divareha][i][j]/4)%2==0)
                    //if ((cell[Divareha][i][j-1]/DEAD)%2==0)
                        if (cell[Arzesh][i][j-1] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i][j-1]+1;
                if ((cell[Divareha][i][j]/8)%2==0)
                    //if ((cell[Divareha][i-1][j]/DEAD)%2==0)
                        if (cell[Arzesh][i-1][j] < cell[Arzesh][i][j])
                            cell[Arzesh][i][j] = cell[Arzesh][i-1][j]+1;
            }
}


unsigned char IsDeadEnd(unsigned char *OneCell)
{
    unsigned char wallCounter = 0;
    if (NoEastWall(OneCell))
        wallCounter++;
    if (NoWestWall(OneCell))
        wallCounter++;
    if (NoNorthWall(OneCell))
        wallCounter++;
    if (NoSouthWall(OneCell))
        wallCounter++;
    
    if (wallCounter >= 3) 
        return 1;
    else 
        return 0;
}

unsigned char NeedToExplore(unsigned char cell[3][16][16])
{
    unsigned char x=0, y=0, dir = NORTH;
    while ((cell[Divareha][x][y]/CROSSED)%2==1)
    {
        dir =  floodthink(cell,dir,x,y,alg);
        semu_go(dir,&x,&y);
        if ((x==7 || x==8) && (y==8 || y==7))
        return 0;
    
    }
    return (x*16+y);
}
