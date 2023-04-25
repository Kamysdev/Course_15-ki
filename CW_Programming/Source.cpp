#pragma warning(disable:4244)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace sf;

float cellSize;
const int size = 4;

bool LevelComplited = false;
int m;
int n;
int m1 = 0;
int n1 = 0;
bool dragged = 0;

Texture girl1;
Texture textureclear;
Texture textureboarder;
Music music;

int Grid[size + 2][size + 2];
int CheckGrid[size * size];

void drawGrid(RenderWindow& window, int grid[size + 2][size + 2], int Vertres) 
{
    Sprite cell;
    cell.setPosition(sf::Vector2f(cellSize, cellSize));
    cell.setScale(cellSize/96, cellSize/96);

    for (int x = 0; x < size + 2; x++) 
    {
        for (int y = 0; y < size + 2; y++) 
        {
            cell.setPosition(x * cellSize, y * cellSize);
            if (Grid[x][y] == -1) 
            {
                cell.setTexture(textureboarder);
            }
            else if (Grid[x][y] == 0) 
            {
                cell.setTexture(textureclear);
            }
            else if (Grid[x][y] == 1) 
            {
                cell.setTextureRect(IntRect(0, 0, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 2) 
            {
                cell.setTextureRect(IntRect(96, 0, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 3) 
            {
                cell.setTextureRect(IntRect(192, 0, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 4) 
            {
                cell.setTextureRect(IntRect(288, 0, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 5) 
            {
                cell.setTextureRect(IntRect(0, 96, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 6) 
            {
                cell.setTextureRect(IntRect(96, 96, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 7) 
            {
                cell.setTextureRect(IntRect(192, 96, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 8) 
            {
                cell.setTextureRect(IntRect(288, 96, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 9) 
            {
                cell.setTextureRect(IntRect(0, 192, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 10) 
            {
                cell.setTextureRect(IntRect(96, 192, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 11) 
            {
                cell.setTextureRect(IntRect(192, 192, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 12) 
            {
                cell.setTextureRect(IntRect(288, 192, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 13) 
            {
                cell.setTextureRect(IntRect(0, 288, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 14) 
            {
                cell.setTextureRect(IntRect(96, 288, 96, 96));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 15) 
            {
                cell.setTextureRect(IntRect(192, 288, 96, 96));
                cell.setTexture(girl1);
            }
            window.draw(cell);
        }
    }
}

void init()
{
    srand(time(NULL));
    
    
    switch (rand() % 2)
    {
        case 0:
        {
            girl1.loadFromFile("../images/girl.jpg");
            break;
        }
        case 1:
        {
            girl1.loadFromFile("../images/girl1.jpg");
            break;
        }
        default:
        {
            girl1.loadFromFile("../images/girl.jpg");
            break;
        }
    }
    girl1.setSmooth(true);


    //Texture textureclear;
    textureclear.loadFromFile("../images/textureclear.jpg");
    textureclear.setSmooth(true);

    //Texture textureboarder;
    textureboarder.loadFromFile("../images/textureboarder.jpg");
    textureboarder.setSmooth(true);

    if (rand() % 100 > 50)
    {
        music.openFromFile("../music/navalivaet_jesco.ogg");
    }
    else
    {
        music.openFromFile("../music/navalivaet_jesco2.ogg");
    }
        
    music.setVolume(10);
    music.play();
    music.setLoop(true);
}

int main() {

    srand(time(NULL));
    HDC hDCScreen = GetDC(NULL);
    int Vertres = GetDeviceCaps(hDCScreen, VERTRES);
    ReleaseDC(NULL, hDCScreen);

    cellSize = Vertres / 11.25 * 1.25;

    init();

    RenderWindow window(VideoMode((size + 2) * (int)cellSize,
                                    (size + 2) * (int)cellSize),
                                    "15shki",
                                    Style::Titlebar | Style::Close);

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    window.setFramerateLimit(60);

    srand(time(NULL));

    for (int i = 1; i < size + 1; i++) 
    {
        for (int j = 1; j < size + 1; j++) 
        {
            Grid[i][j] = 0;
        }
    }

    bool regen = 0;

    while (regen == 0) 
    {

        for (int i = 1; i < size + 1; i++) 
        {
            for (int j = 1; j < size + 1; j++) 
            {
                if (i == size && j == size) 
                {  // Пропустить последний элемент
                    continue;
                }
                int num;
                bool found;
                do 
                {
                    num = rand() % 15 + 1;  // Случайное число от 1 до 15
                    found = false;
                    for (int k = 1; k < i; k++) 
                    {
                        for (int l = 1; l < size + 1; l++) 
                        {
                            if (Grid[k][l] == num) 
                            {
                                found = true;
                                break;
                            }
                        }
                        if (found) 
                        {
                            break;
                        }
                    }
                    for (int k = 0; k < j; k++) 
                    {
                        if (Grid[i][k] == num) 
                        {
                            found = true;
                            break;
                        }
                    }
                } while (found);
                Grid[i][j] = num;
            }
        }
        Grid[4][4] = 0;

        for (int i = 1, count = 0; i < size + 1; i++) 
        {
            for (int j = 1; j < size + 1; j++, count++) 
            {
                CheckGrid[count] = Grid[i][j];
            }
        }

        int inv = 0;
        for (int i = 0; i < size * size; i++) 
        {
            if (CheckGrid[i] != 0) 
            {
                for (int j = 0; j < i; j++) 
                {
                    if (CheckGrid[j] > CheckGrid[i]) 
                    {
                        inv++;
                    }
                }
            }
        }
        for (int i = 0; i < size * size; i++) 
        {
            if (CheckGrid[i] == 0) 
            {
                inv += 1 + i / 4;
            }
        }
        if (inv & 1) 
        {
            regen = 0;
        }
        else
        {
            regen = 1;
        }
    }

    for (int x = 0; x < size + 2; x++) 
    {
        Grid[x][0] = -1;
        Grid[x][size + 1] = -1;
    }
    for (int y = 0; y < size + 2; y++) 
    {
        Grid[0][y] = -1;
        Grid[size + 1][y] = -1;
    }


    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && !LevelComplited) 
            {
                if (event.mouseButton.button == Mouse::Left 
                    && event.mouseButton.x >= cellSize 
                    && event.mouseButton.x < (size + 1) * cellSize 
                    && event.mouseButton.y >= cellSize 
                    && event.mouseButton.y < (size + 1) * cellSize) {
                    if (dragged == 0) 
                    {
                        m = event.mouseButton.x / cellSize;
                        n = event.mouseButton.y / cellSize;
                        if (Grid[m][n] != -1 
                            && Grid[m][n] != 0 
                            && (Grid[m + 1][n] == 0 
                                || Grid[m - 1][n] == 0 
                                || Grid[m][n + 1] == 0 
                                || Grid[m][n - 1] == 0)) 
                        {
                            dragged = 1;
                            m1 = m;
                            n1 = n;
                        }
                    }
                    if (dragged == 1) 
                    {
                        m = event.mouseButton.x / cellSize;
                        n = event.mouseButton.y / cellSize;
                        if (Grid[m][n] == 0 
                            && ((m == m1 - 1 
                                && n != n1 - 1 
                                && n != n1 + 1) 
                                || (m == m1 + 1 
                                    && n != n1 - 1 
                                    && n != n1 + 1) 
                                || (n == n1 - 1 
                                    && m != m1 - 1 
                                    && m != m1 + 1) 
                                || (n == n1 + 1 
                                    && m != m1 - 1 
                                    && m != m1 + 1))) 
                        {
                            int temp = Grid[m][n];
                            Grid[m][n] = Grid[m1][n1];
                            Grid[m1][n1] = temp;
                            dragged = 0;
                        }
                    }
                }
            }
        }

        window.clear(Color::White);

        drawGrid(window, Grid, Vertres);

        window.display();

        
    }

    return 0;
}