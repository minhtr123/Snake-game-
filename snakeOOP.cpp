#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

const int WIDTH = 30;
const int HEIGHT = 20;
bool gameOver = false;

int score;


using namespace std;

class Snake {
    private:
        int xHead, yHead;
        int length;
        char direction;
        vector<int> tailX;
        vector<int> tailY;
    public:
        Snake (int xHead, int yHead){
            this -> xHead = xHead;
            this -> yHead = yHead;
            length=1;
            direction = 'n';
        }
        
        vector<int> get_tail_x(){
            return tailX;
        }
        
        vector<int> get_tail_y(){
            return tailY;
        }
        
        void change_dir(char dir){
            direction = dir;
        }

        void snake_moving(){
            switch(direction){
                case 'w':
                    yHead--;
                    break;
                case 's':
                    yHead++;
                    break; 
                case 'a':
                    xHead--;
                    break;
                case 'd':
                    xHead++;
                    break;
                default:
                    break;                                                   
            }

            tailX.push_back(xHead);
            if(tailX.size()>length) tailX.erase(tailX.begin());
            
            tailY.push_back(yHead);
            if(tailY.size()>length) tailY.erase(tailY.begin());
        }
        int getX(){
            return xHead;
        }
        int getY(){
            return yHead;
        }
        bool eaten(int foodX, int foodY){
            if (foodX == xHead && foodY == yHead){
                score += 10;
                return true;
            } else {
                return false;
            }
        }
        void grow(){
            length++;
        }
        void checkOutofmap(){
            if (xHead>=WIDTH-1){
                xHead=0;
            } else if (xHead<=0){
                xHead=WIDTH-2;
            }

            if (yHead>=HEIGHT){
                yHead=0;
            } else if (yHead<0){
                yHead=HEIGHT-1;
        }
        }
        void checkCollision(){
            for (int i=0; i<tailX.size()-1;i++){
            if (xHead == tailX[i] && yHead == tailY[i]){
                gameOver = true;
                break;
            }
            }
        }
};

class Food {
    private:
        int foodX, foodY;
    public:
        int getFoodX() {
            return foodX;           
        }
        int getFoodY() {
            return foodY;           
        }
        void getSeed(){
            srand(time(0));
        }
        void spawn_fruit(){
            foodX = rand() % WIDTH;
            if (foodX == 0 || foodX == WIDTH-1){
            foodX = rand() % WIDTH;
            }
            foodY = rand() % HEIGHT;
            if (foodY == 0 || foodY == WIDTH-1){
            foodY = rand() % HEIGHT;
            }
        }

};

Snake snake (WIDTH/2, HEIGHT/2);
Food fruit;

void Draw(int foodX, int foodY){
    int headX = snake.getX();
    int headY = snake.getY();

    vector<int> bodyX = snake.get_tail_x();
    vector<int> bodyY = snake.get_tail_y();

    for(int i=0; i< WIDTH; i++){
        cout << "#";
    } cout << endl; // first row

    for (int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if (j==0 || j==WIDTH-1){
                cout << "#";
            } else if (i == headY && j == headX) {
                cout << "O";
            } else if (i == foodY && j == foodX) { 
                cout << "@";
            } else {
                bool isBodyPart = false;
                for (int k = 0; k < bodyX.size()-1; k++){

                if (j == bodyX[k] && i == bodyY[k]){
                    cout << 'x';
                    isBodyPart = true;
                }
                } if (!isBodyPart){
                    cout << " ";
                }
            }
        } cout << endl;
    }

    for(int i=0; i< WIDTH; i++){
        cout << "#";
    } cout << endl;
    cout << "Score: "<< score << endl; // last row
        
}


void Control(){
    if(_kbhit()){
        switch (_getch())
        {
        case 'w':
            snake.change_dir('w');
            break;
        case 'a':
            snake.change_dir('a');
            break;
        case 's':
            snake.change_dir('s');
            break;
        case 'd':
            snake.change_dir('d');
            break;                    
        default:
            break;
        }
    }
}



int main(){
    fruit.getSeed();
    fruit.spawn_fruit();
    int foodX = fruit.getFoodX();
    int foodY = fruit.getFoodY();

    while(!gameOver){
        system("CLS");
        Control();
        snake.snake_moving();
        Draw(foodX, foodY);
        
        if(snake.eaten(foodX, foodY)){
            fruit.spawn_fruit();
            foodX = fruit.getFoodX();
            foodY = fruit.getFoodY();
            snake.grow();
        }
        
        snake.checkOutofmap();
        snake.checkCollision();
        Sleep(100);
    }
    cout << "Game Over!" << endl;
    return 0;
}