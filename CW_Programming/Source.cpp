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

Texture texturerecreate;
Texture texturemusic;

Music music;

int Grid[size + 2][size + 2];
int CheckGrid[size * size];

void drawGrid(RenderWindow& window, int grid[size + 2][size + 2]) 
{
    Sprite cell;
    cell.setPosition(sf::Vector2f(cellSize, cellSize));
    cell.setScale(cellSize/150, cellSize/150);

    for (int x = 0; x < size + 2; x++) 
    {
        for (int y = 0; y < size + 2; y++) 
        {
            cell.setPosition(x * cellSize, y * cellSize);

            if (Grid[x][y] == -1) 
            {
                cell.setTextureRect(IntRect(0, 0, 150, 150));
                cell.setTexture(textureboarder);
            }
            else if (Grid[x][y] == -5)
            {
                cell.setTexture(texturerecreate);
            }
            else if (Grid[x][y] == -6)
            {
                cell.setTexture(texturemusic);
            }
            else if (Grid[x][y] == 0) 
            {
                cell.setTextureRect(IntRect(0, 0, 150, 150));
                cell.setTexture(textureclear);
            }
            else if (Grid[x][y] == 1) 
            {
                cell.setTextureRect(IntRect(0, 0, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 2) 
            {
                cell.setTextureRect(IntRect(150, 0, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 3) 
            {
                cell.setTextureRect(IntRect(300, 0, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 4) 
            {
                cell.setTextureRect(IntRect(450, 0, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 5) 
            {
                cell.setTextureRect(IntRect(0, 150, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 6) 
            {
                cell.setTextureRect(IntRect(150, 150, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 7) 
            {
                cell.setTextureRect(IntRect(300, 150, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 8) 
            {
                cell.setTextureRect(IntRect(450, 150, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 9) 
            {
                cell.setTextureRect(IntRect(0, 300, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 10) 
            {
                cell.setTextureRect(IntRect(150, 300, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 11) 
            {
                cell.setTextureRect(IntRect(300, 300, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 12) 
            {
                cell.setTextureRect(IntRect(450, 300, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 13) 
            {
                cell.setTextureRect(IntRect(0, 450, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 14) 
            {
                cell.setTextureRect(IntRect(150, 450, 150, 150));
                cell.setTexture(girl1);
            }
            else if (Grid[x][y] == 15) 
            {
                cell.setTextureRect(IntRect(300, 450, 150, 150));
                cell.setTexture(girl1);
            }
            window.draw(cell);
        }
    }
}

void music_changer()
{
    srand(time(NULL) - 555);

    switch (rand() % 5)
    {
        case 0:
        {
            music.openFromFile("./musics/navalivaet_jesco.ogg");
            break;
        }
        case 1:
        {
            music.openFromFile("./musics/navalivaet_jesco1.ogg");
            break;
        }
        case 2:
        {
            music.openFromFile("./musics/navalivaet_jesco2.ogg");
            break;
        }
        case 3:
        {
            music.openFromFile("./musics/navalivaet_jesco3.ogg");
            break;
        }
        case 4:
        {
            music.openFromFile("./musics/navalivaet_jesco4.ogg");
            break;
        }
        default:
        {
            music.openFromFile("./musics/navalivaet_jesco.ogg");
            break;
        }
    }

    music.setVolume(10);
    music.play();
    music.setLoop(true);
}

void girl_generator()
{
    srand(time(NULL));

    switch (rand() % 7)
    {
        case 0:
        {
            girl1.loadFromFile("./images/girl.jpg");
            break;
        }
        case 1:
        {
            girl1.loadFromFile("./images/girl1.jpg");
            break;
        }
        case 2:
        {
            girl1.loadFromFile("./images/girl2.jpg");
            break;
        }
        case 3:
        {
            girl1.loadFromFile("./images/girl3.jpg");
            break;
        }
        case 4:
        {
            girl1.loadFromFile("./images/girl4.jpg");
            break;
        }
        case 5:
        {
            girl1.loadFromFile("./images/girl5.jpg");
            break;
        }
        case 6:
        {
            girl1.loadFromFile("./images/girl6.jpg");
            break;
        }

        default:
        {
            girl1.loadFromFile("./images/girl.jpg");
            break;
        }
    }
    girl1.setSmooth(true);

    for (int i = 1; i < size + 1; i++)
    {
        for (int j = 1; j < size + 1; j++)
        {
            Grid[i][j] = 0;
        }
    }

    bool regen = false;

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

    Grid[size][0] = - 5;
    Grid[size + 1][0] = - 6;
}

void init()
{
    girl_generator();

    //Texture textureclear;
    textureclear.loadFromFile("./images/textureclear.jpg");
    textureclear.setSmooth(true);

    //Texture textureboarder;
    textureboarder.loadFromFile("./images/textureboarder.jpg");
    textureboarder.setSmooth(true);

    texturerecreate.loadFromFile("./images/recreate.jpg");
    texturerecreate.setSmooth(true);

    texturemusic.loadFromFile("./images/musicico.jpg");
    texturerecreate.setSmooth(true);

    music_changer();
}

int main() 
{
    srand(time(NULL));
    HDC hDCScreen = GetDC(NULL);
    int Vertres = GetDeviceCaps(hDCScreen, VERTRES);
    ReleaseDC(NULL, hDCScreen);

    cellSize = Vertres / 7.2;

    init();

    RenderWindow window(VideoMode((size + 2) * (int)cellSize,
                                    (size + 2) * (int)cellSize),
                                    "15shki",
                                    Style::Titlebar | Style::Close);

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    window.setFramerateLimit(60);

    srand(time(NULL));

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == 36)
                {
                    window.close();
                }
            }

            if (event.type == Event::MouseButtonPressed && !LevelComplited) 
            {
                if (event.mouseButton.button == Mouse::Left 
                    && event.mouseButton.x >= cellSize 
                    && event.mouseButton.x < (size + 1) * cellSize 
                    && event.mouseButton.y >= cellSize 
                    && event.mouseButton.y < (size + 1) * cellSize) 
                {
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

                else if (event.mouseButton.button == Mouse::Left
                    && event.mouseButton.x >= (size + 1) * cellSize
                    && event.mouseButton.x < (size + 2) * cellSize
                    && event.mouseButton.y >= 0 * cellSize
                    && event.mouseButton.y < (size) * cellSize)
                {
                    music.stop();
                    music_changer();
                }

                else if (event.mouseButton.button == Mouse::Left
                    && event.mouseButton.x >= (size)*cellSize
                    && event.mouseButton.x < (size + 1) * cellSize
                    && event.mouseButton.y >= 0
                    && event.mouseButton.y < (size) * cellSize)
                {
                    girl_generator();
                }
            }
        }

        window.clear(Color::White);

        drawGrid(window, Grid);

        window.display();

        
    }

    return 0;
}