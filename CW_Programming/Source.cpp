#pragma warning(disable:4244)

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace sf;

float cellSize;
const int size = 4;
const int numBombs = 10;
int win = 0;
int m;
int n;
int m1 = 0;
int n1 = 0;
bool dragged = 0;

Texture texture1;
Texture texture2;
Texture texture3;
Texture texture4;
Texture texture5;
Texture texture6;
Texture texture7;
Texture texture8;
Texture texture9;
Texture texture10;
Texture texture11;
Texture texture12;
Texture texture13;
Texture texture14;
Texture texture15;
Texture textureclear;
Texture textureboarder;

int Grid[size + 2][size + 2];
int CheckGrid[size * size];

void drawGrid(RenderWindow& window, int grid[size + 2][size + 2], int Vertres) {
    Sprite cell;
    cell.setPosition(sf::Vector2f(cellSize, cellSize));
    cell.setScale(cellSize/32, cellSize/32);

    for (int x = 0; x < size + 2; x++) {
        for (int y = 0; y < size + 2; y++) {
            cell.setPosition(x * cellSize, y * cellSize);
            if (Grid[x][y] == -1) {
                cell.setTexture(textureboarder);
            }
            else if (Grid[x][y] == 0) {
                cell.setTexture(textureclear);
            }
            else if (Grid[x][y] == 1) {
                cell.setTexture(texture1);
            }
            else if (Grid[x][y] == 2) {
                cell.setTexture(texture2);
            }
            else if (Grid[x][y] == 3) {
                cell.setTexture(texture3);
            }
            else if (Grid[x][y] == 4) {
                cell.setTexture(texture4);
            }
            else if (Grid[x][y] == 5) {
                cell.setTexture(texture5);
            }
            else if (Grid[x][y] == 6) {
                cell.setTexture(texture6);
            }
            else if (Grid[x][y] == 7) {
                cell.setTexture(texture7);
            }
            else if (Grid[x][y] == 8) {
                cell.setTexture(texture8);
            }
            else if (Grid[x][y] == 9) {
                cell.setTexture(texture9);
            }
            else if (Grid[x][y] == 10) {
                cell.setTexture(texture10);
            }
            else if (Grid[x][y] == 11) {
                cell.setTexture(texture11);
            }
            else if (Grid[x][y] == 12) {
                cell.setTexture(texture12);
            }
            else if (Grid[x][y] == 13) {
                cell.setTexture(texture13);
            }
            else if (Grid[x][y] == 14) {
                cell.setTexture(texture14);
            }
            else if (Grid[x][y] == 15) {
                cell.setTexture(texture15);
            }
            window.draw(cell);
        }
    }
}

int main() {

    HDC hDCScreen = GetDC(NULL);
    int Vertres = GetDeviceCaps(hDCScreen, VERTRES);
    ReleaseDC(NULL, hDCScreen);

    cellSize = Vertres / 33.75;

    RenderWindow window(VideoMode((size + 2) * (int)cellSize, (size + 2) * (int)cellSize), "15shki", Style::Titlebar | Style::Close);
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    window.setFramerateLimit(60);


    //Texture texture1;
    texture1.loadFromFile("../images/texture1.jpg");
    texture1.setSmooth(true);

    //Texture texture2;
    texture2.loadFromFile("../images/texture2.jpg");
    texture2.setSmooth(true);

    //Texture texture3;
    texture3.loadFromFile("../images/texture3.jpg");
    texture3.setSmooth(true);

    //Texture texture3;
    texture3.loadFromFile("../images/texture3.jpg");
    texture3.setSmooth(true);

    //Texture texture4;
    texture4.loadFromFile("../images/texture4.jpg");
    texture4.setSmooth(true);

    //Texture texture5;
    texture5.loadFromFile("../images/texture5.jpg");
    texture5.setSmooth(true);

    //Texture texture6;
    texture6.loadFromFile("../images/texture6.jpg");
    texture6.setSmooth(true);

    //Texture texture7;
    texture7.loadFromFile("../images/texture7.jpg");
    texture7.setSmooth(true);

    //Texture texture8;
    texture8.loadFromFile("../images/texture8.jpg");
    texture8.setSmooth(true);

    //Texture texture9;
    texture9.loadFromFile("../images/texture9.jpg");
    texture9.setSmooth(true);

    //Texture texture10;
    texture10.loadFromFile("../images/texture10.jpg");
    texture10.setSmooth(true);

    //Texture texture11;
    texture11.loadFromFile("../images/texture11.jpg");
    texture11.setSmooth(true);

    //Texture texture12;
    texture12.loadFromFile("../images/texture12.jpg");
    texture12.setSmooth(true);

    //Texture texture13;
    texture13.loadFromFile("../images/texture13.jpg");
    texture13.setSmooth(true);

    //Texture texture14;
    texture14.loadFromFile("../images/texture14.jpg");
    texture14.setSmooth(true);

    //Texture texture15;
    texture15.loadFromFile("../images/texture15.jpg");
    texture15.setSmooth(true);

    //Texture textureclear;
    textureclear.loadFromFile("../images/textureclear.jpg");
    textureclear.setSmooth(true);

    //Texture textureboarder;
    textureboarder.loadFromFile("../images/textureboarder.jpg");
    textureboarder.setSmooth(true);

    srand(time(NULL));

    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size + 1; j++) {
            Grid[i][j] = 0;
        }
    }

    bool regen = 0;

    while (regen == 0) {

        for (int i = 1; i < size + 1; i++) {
            for (int j = 1; j < size + 1; j++) {
                if (i == size && j == size) {  // Пропустить последний элемент
                    continue;
                }
                int num;
                bool found;
                do {
                    num = rand() % 15 + 1;  // Случайное число от 1 до 15
                    found = false;
                    for (int k = 1; k < i; k++) {
                        for (int l = 1; l < size + 1; l++) {
                            if (Grid[k][l] == num) {
                                found = true;
                                break;
                            }
                        }
                        if (found) {
                            break;
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        if (Grid[i][k] == num) {
                            found = true;
                            break;
                        }
                    }
                } while (found);
                Grid[i][j] = num;
            }
        }
        Grid[4][4] = 0;

        for (int i = 1, count = 0; i < size + 1; i++) {
            for (int j = 1; j < size + 1; j++, count++) {
                CheckGrid[count] = Grid[i][j];
            }
        }

        int inv = 0;
        for (int i = 0; i < size * size; i++) {
            if (CheckGrid[i] != 0) {
                for (int j = 0; j < i; j++) {
                    if (CheckGrid[j] > CheckGrid[i]) {
                        inv++;
                    }
                }
            }
        }
        for (int i = 0; i < size * size; i++) {
            if (CheckGrid[i] == 0) {
                inv += 1 + i / 4;
            }
        }
        if (inv & 1) {
            regen = 0;
        }
        else regen = 1;
    }

    for (int x = 0; x < size + 2; x++) {
        Grid[x][0] = -1;
        Grid[x][size + 1] = -1;
    }
    for (int y = 0; y < size + 2; y++) {
        Grid[0][y] = -1;
        Grid[size + 1][y] = -1;
    }


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left && event.mouseButton.x >= cellSize && event.mouseButton.x < (size + 1) * cellSize && event.mouseButton.y >= cellSize && event.mouseButton.y < (size + 1) * cellSize) {
                    if (dragged == 0) {
                        m = event.mouseButton.x / cellSize;
                        n = event.mouseButton.y / cellSize;
                        if (Grid[m][n] != -1 && Grid[m][n] != 0 && (Grid[m + 1][n] == 0 || Grid[m - 1][n] == 0 || Grid[m][n + 1] == 0 || Grid[m][n - 1] == 0)) {
                            dragged = 1;
                            m1 = m;
                            n1 = n;
                        }
                    }
                    if (dragged == 1) {
                        m = event.mouseButton.x / cellSize;
                        n = event.mouseButton.y / cellSize;
                        if (Grid[m][n] == 0 && ((m == m1 - 1 && n != n1 - 1 && n != n1 + 1) || (m == m1 + 1 && n != n1 - 1 && n != n1 + 1) || (n == n1 - 1 && m != m1 - 1 && m != m1 + 1) || (n == n1 + 1 && m != m1 - 1 && m != m1 + 1))) {
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

        /*if (win == numBombs && (openCells == (size*size-numBombs))) {
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.x >= 0 && event.mouseButton.x <= cellSize && event.mouseButton.y >= 0 && event.mouseButton.y <= cellSize) {
                    for (int x = 1; x < size + 1; x++) {
                        for (int y = 1; y < size + 1; y++) {
                            Grid[x][y] = 0;
                        }
                    }
                    for (int x = 0; x < size + 2; x++) {
                        Grid[x][0] = -3;
                        Grid[x][size + 1] = -3;
                    }
                    for (int y = 0; y < size + 2; y++) {
                        Grid[0][y] = -3;
                        Grid[size + 1][y] = -3;
                    }
                    for (int x = 1; x < size + 1; x++) {
                        for (int y = 1; y < size + 1; y++) {
                            RevealGrid[x][y] = 0;
                        }
                    }

                    Grid[0][0] = -4;
                    srand(time(NULL));
                    win = 0;
                    firstHit = 1;
                }
            }
        }*/

    }

    return 0;
}