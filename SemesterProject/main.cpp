#include <iostream>
#include<iomanip>
#include<conio.h>
#include <string>
#include <windows.h>
#include <cstdlib>
#include<fstream>
#include<chrono>
#include<cstring>

const int SCREEN_WIDTH=90;
const int SCREEN_HEIGHT=26;
const int WIN_WIDTH=70;

using namespace std;


class user{//abstract class
protected:
    char username[15];
    char password[10];
    int score; 

public:
    user(){} 
    user(char uname[15], char pword[10]):score(0){
        strcpy(username,uname);
        strcpy(password,pword);

    }

    string getusername() {
        return username;
    }

    char* getpassword() {
        return password;
    }
    int getscore(){
        return score;
    }
    void setscore(int s){
        score=s;
    }
    void display(){
        cout<<"Username: "<<std::setw(15)<<std::left<<username<<"\t\t"<<
              "Score   : "<<score<<endl;
    }

};

void display() {
    user usr;
    ifstream fin;
    fin.open("database.txt", ios::binary|ios::in);

    fin.seekg(0,ios::end); //to check emptyness of file
 int a = fin.tellg();
 fin.seekg(0);
 if(a!=0){
 while(fin.read((char*)&usr,sizeof usr)){
usr.display(); }
 }
    getch();
    fin.close();
}


    void adduser(user& u){
        //users.push_back(u);
        ofstream fout;
        fout.open("database.txt",ios::binary|ios::app);
        fout.write((char*) & u, sizeof(u));
        
        cout<<"Congratulations! you have signed up for the application."<<endl;
        fout.close();
        getch();
        system("cls");
    }





    bool authorize(string usrname, string pswrd){
        user usr;
        ifstream fin;
        fin.open("database.txt");

        if (!fin) {
        std::cerr << "Error opening file.\n";
        return false;
    }
        fin.seekg(0);
        fin.read((char*) &usr,sizeof(usr));
        
        while(!fin.eof()){
            
            if(usr.getusername()==usrname && usr.getpassword()==pswrd){
                return true;
            }
            else{
                fin.read((char*) &usr,sizeof(usr));
            }  
        }
        fin.close();
        return false;
    }
 

user getuser(){
    char uname[15], pword[10];

    cout<<"Type your username: ";
    cin>>uname;
    cout<<"Type your password: ";
    cin>>pword;

    user u(uname, pword);
    return u;
}

void writescore(user usr, int score){
    user usrvar;
    fstream ffile;
        ffile.open("database.txt",ios::in|ios::out|ios::binary);

        if (!ffile) {
        std::cerr << "Error opening file.\n";
    }
        ffile.seekg(0);
        ffile.read((char*) &usrvar,sizeof(usrvar));
        
        while(!ffile.eof()){
            
            if(usrvar.getusername()==usr.getusername()){
                usr.setscore(score);
                int pos = -1 * static_cast<int>(sizeof(usr));
            ffile.seekp(pos, ios::cur);
            ffile.write((char*)&usr, sizeof(usr));
            break;
            }
            ffile.read((char*) &usrvar,sizeof(usrvar));
        }
        ffile.close();
        
}


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
int car[4][4] = {{' ', 219, 219, ' '},
                 {219, 219, 219, 219},
                 {' ', 219, 219, ' '},
                 {219, 219, 219, 219}};

int carPos = WIN_WIDTH / 2;



void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(j, i);
            cout << "www";
            gotoxy(WIN_WIDTH - j, i);
            cout << "www";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        cout << "www";
    }
}

void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "mmmm";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << " mm ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "mmmm";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << " mm ";
    }
}

void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}

void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << static_cast<char>(car[i][j]);
        }
    }
}

void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << ' ';
        }
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}

void gameover()
{
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl
         << endl;
    cout << "\t\tPress any key to go back to menu.";
    system("cls");
    cin.ignore();
}

void updateScore(int score)
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

void instructions()
{
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Avoid Cars by moving left or right. ";
    cout << "\n\n Press leftarrow to move left";
    cout << "\n Press rightarrow to move right";
    cout << "\n Press 'escape' to exit";
    cout << "\n\nPress any key to go back to menu";
    getch();
}

void showscores(){
    user usr;
    ifstream fin;
    fin.open("database.txt");
    fin.read((char*)&usr, sizeof(usr));
    while(!fin.eof()){
        usr.display();
        fin.read((char*)&usr, sizeof(usr));
    }
    getch();
    fin.close();
}

void play(user usr, int score)
{
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore(score);
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    cout << "Car Game";
    gotoxy(WIN_WIDTH + 6, 4);
    cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6);
    cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12);
    cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13);
    cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14);
    cout << " left Key - Left";
    gotoxy(WIN_WIDTH + 2, 15);
    cout << " right Key - Right";

    gotoxy(18, 5);
    cout << "Press any key to start";
    cin.ignore();
    gotoxy(18, 5);
    cout << "                      ";

    while (1)
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (carPos > 18)
                carPos -= 4;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            if (carPos < 50)
                carPos += 4;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1)
        {
            writescore(usr, score);
            gameover();
            return;
        }
        Sleep(20);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
        {
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;
        }

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore(score);
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(1);
            score++;
            updateScore(score);
        }
    }
}

void playgame(user u1, int score){
    {
                srand(time(NULL));

                do
                {
                    system("cls");
                    gotoxy(10, 5);
                    cout << " -------------------------- ";
                    gotoxy(10, 6);
                    cout << " |        Car Game        | ";
                    gotoxy(10, 7);
                    cout << " --------------------------";
                    gotoxy(10, 9);
                    cout << "1. Start Game";
                    gotoxy(10, 10);
                    cout << "2. Instructions";
                    gotoxy(10, 11);
                    cout<< "3. Show Score";
                    gotoxy(10,12);
                    cout << "4. Quit";
                    gotoxy(10, 13);
                    cout << "Select option: ";
                    char op;
                    cin >> op;

                    if (op == '1')
                        play(u1,score);
                    else if (op == '2')
                        instructions();
                    else if (op == '3')
                        display();
                    else if(op == '4'){
                    system("cls");
                        exit(0);
                    }
                        

    } while (1);

            }
}


int main()
{
    
    char c;
    system("cls");
    

    do{
    cout<<"\nAre you an 'Returning User' or a 'New User'(r/n): ";
    c=getch();
    cout<<endl;
    c=tolower(c);
    if(c=='r'){

        user thisuser=getuser();
        bool userFlag=authorize(thisuser.getusername(), thisuser.getpassword());
        if(userFlag ==true){

            cout<<"Welcome again, "<<thisuser.getusername()<<endl;
            getch();
            int score=0;
            playgame(thisuser,score);
        }
        else{
            cout<<"Sorry, invalid username or password !"<<endl;
            getch();
            system("cls");
            exit(1);
        }

    }
    else if(c=='n'){

        user thisuser=getuser();
        adduser(thisuser);
    }
    else if(c=='d'){
        display();
    }
    else {
        cout<<"sorry the character you typed was invalid !"<<endl;
        getch();
        system("cls");
        exit(1);
    }

    
    }while(true);
    return 0;
}
