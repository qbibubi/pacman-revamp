#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <string_view>
#include <unordered_map>

class Entity;

enum class Direction : uint8_t
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};

struct Vector2
{
    size_t x, y;
};

class Map
{
private:
    constexpr static Vector2 m_DefaultMapDimension = { 20, 20 };
    Vector2 m_MapDimensions;

    enum class Characters : uint8_t
    {
        ESCAPE = 27,
        WALL = 32,
        M = 178,
        PLAYER = 153,
        GHOST = 148,
        POINT = 46,
        BUFF = 175
    };

    std::vector<std::string_view> m_MapFilenames;
    std::vector<std::vector<uint8_t>> m_Map;
    std::vector<Entity> m_Entities;


public:
    Map() {}
    ~Map() = default;

    void SaveMapTo(std::string_view filename) 
    {
        m_MapFile.open(filename, std::ios::out);
        if (!m_MapFile.is_open())
        {
            std::cout << "File missing";
            return;
        }

        m_MapFile << DefaultMapMaxY << '\n';
        m_MapFile << DefaultMapMaxY << '\n';
        for (size_t i = 0; i < MAP_SIZE_Y; i++) 
        {
            for (size_t j = 0; j < MAP_SIZE_X; j++) 
            {
                m_MapFile << m_Map[i][j] << " ";
            }
            m_MapFile << '\n';
        }
        
        m_MapFile.close();
    }

    void Draw()
    {
        for (size_t x = 0; x < m_MapDimensions.x; ++x) 
        {
            for (size_t y = 0; y < m_MapDimensions.y; ++y)
            {
                iMapFromFile[i][j] = iMap[i][j];
                std::cout << iMapFromFile[i][j];
            }
            std::cout << '\n';
        }
    }

    void LoadMapFrom(std::string_view filename) 
    {
        m_MapFile.open(filename.data(), std::ios::in);
        if (!m_MapFile.is_open())
        {
            std::cout << "File missing";
            return;
        }
       
        m_MapFile >> iMapSizeX;
        m_MapFile >> iMapSizeY;
        for (int i = 0; i < iMapSizeY; i++) 
        {
            for (int j = 0; j < iMapSizeX; j++) 
            {
                m_MapFile >> iMapFromFile[i][j];
            } 
        } 
    }
};

class Game
{
private:
    bool m_bRunning;
    bool m_bUpdated;

    // clock_t CurrentFrame;
    // clock_t PrevFrame;
    // clock_t deltaTime;

public:
    Game()
        : m_bRunning(true), m_bUpdated(false)
    {}

    ~Game() = default;

    void Draw();
    void Update();
};


std::vector<std::vector<uint8_t>> MAP = {
    {M, M, M, M, M, M, M, M, M, W, M, M, M, M, M, M, M, M, M, M}, // LINE 1
    {M,  P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P2, M},                           // LINE 2
    {M, P1, M, M, M, M, P1, M, M, M, P1, M, M, P1, M, M, M, M, P1, M}, // LINE 3
    {M, P1, M, M, M, M, P1, M, M, M, P1, M, M, P1, M, M, M, M, P1, M}, // LINE 4
    {M,  P1, M,  P1, P1, P1, P1, P1, M,  M, P1, M,  P1, P1, P1, P1, P1, M,  P1, M}, // LINE 5
    {M,  P1, M,  P1, M, M, M,  P1, M,  M, P1, M,  P1, M,  M, M, P1, M,  P1, M}, // LINE 6
    {M,  P1, M,  P1, M, M, M,  P1, M,  M, P1, M,  P1, M,  M, M, P1, M,  P1, M}, // LINE 7
    {M,  P1, M,  P1, M, M, P1, P1, P1, P1, P1, P1, P1, P1, M, M, P1, M,  P1, M}, // LINE 8
    {M, P1, M, P1, M, M, P1, M, M,  W, M, M,  M, P1, M, M, P1, M, P1, M}, // LINE 9
    {W, P1, P1, P1, P1, P1, P1, M,  W,  W, W, W,  M,  P1, P1, P1, P1, P1, P1, W}, // LINE 10
    {M, P1, M, P1, M, M, P1, M, M,  M, M, M,  M, P1, M, M, P1, M, P1, M}, // LINE 11
    {M,  P1, M,  P1, M, M, P1, P1, P1, P1, P1, P1, P1, P1, M, M, P1, M,  P1, M}, // LINE 12
    {M, P1, M,  P1, M, M, M,  P1, M,  P1, M, M,  P1, M,  M, M, P1, M,  P1, M}, // LINE 13
    {M, P1, M,  P1, M, M, M,  P1, M,  P1, M, M,  P1, M,  M, M, P1, M,  P1, M}, // LINE 14
    {M, P1, M,  P1, P1, P1, P1, P1, M,  P1, M, M,  P1, P1, P1, P1, P1, M,  P1, M}, // LINE 15
    {M, P1, M, M,  M, M, P1, M, M,  P1, M, M,  M, P1, M, M, M,  M, P1, M}, // LINE 16
    {M, P1, M, M,  M, M, P1, M, M,  P1, M, M,  M, P1, M, M, M,  M, P1, M}, // LINE 17
    {M,  P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, M},                     // LINE 18
    {M, M, M, M, M, M, M, M, M, M, M, W, M, M, M, M, M, M, M, M} // LINE 19
};

class Entity 
{
private:
    Vector2 m_Position;
    uint8_t m_Character;
    uint32_t m_nLives;
    float m_fVelocity;

public:
    Entity(Vector2 const& startingPosition, uint8_t character) 
        : m_Position(startingPosition), m_Character(character), m_fVelocity(1.0f), m_nLives(1)
    {}

    void SetX(size_t value) { m_Position.x = value; }
    void SetY(size_t value) { m_Position.y = value; }
    void SetVelocity(float velocity) { m_fVelocity = velocity; }

    size_t GetX() const { return m_Position.x; }
    size_t GetY() const { return m_Position.y; } 
    Vector2 GetPosition() const { return m_Position; }
    float GetVelocity() const { return m_fVelocity; }
    
    void ShiftPositionBy(Vector2 const& shiftVector)
    {
        m_Position.x += shiftVector.x * m_fVelocity;
        m_Position.y += shiftVector.y * m_fVelocity;
    }

    void Move(Direction direction)
    {
        switch (direction)
        {
        case Direction::DOWN: ShiftPositionBy({}); break;
        case Direction::LEFT: ShiftPositionBy({});  break;
        case Direction::RIGHT: ShiftPositionBy({});  break;
        case Direction::UP: ShiftPositionBy({});  break;
        default: break;
        }
    }
};

class Player : public Entity 
{
private:
  int iScore = 0;
  int iLifes = 3;

public:
  // Score
  void setScore(int value) { iScore = value; }

  int getScore() { return iScore; }

  void setLifes(int value) { iLifes = value; }

  int getLifes() { return iLifes; }

  void substractLife() { iLifes--; }
};

class Ghost : public Entity 
{
private:
  int iCharacterSign = G;
  float fVelocity = 1.2;
};

// Class Objects definition
Entity Entity1;
Player Player1;
Map mainMap;
Ghost Ghost1;

void setStartingPositions() {
  // Setting up positions
  Player1.setX(9);
  Player1.setY(11);

  Ghost1.setX(9);
  Ghost1.setY(9);

  // Setting up velocities
  Player1.setVelocity(1.0);
  Ghost1.setVelocity(1.2);
}

void ghostMovementSystem() {
  srand(time(NULL));
  int iLastMove = rand() % 4 + 1;

  if (iLastMove != 2 && iLastMove != 4) {
    if (iLastMove == 1) {
      // If the block under is not a wall - move there
      if (iMap[Ghost1.getY() - 1][Ghost1.getX()] != M) {
        Ghost1.addY(-1);
        ifGame = true;
      }
    } else if (iLastMove == 3) {
      // If the block above is not a wall - move there
      if (iMap[Ghost1.getY() + 1][Ghost1.getX()] != M) {
        Ghost1.addY(1);
        ifGame = true;
      }
    }
  } else if (iLastMove != 1 && iLastMove != 3) {
    if (iLastMove == 2) {
      // If the block on the right is not a wall - move there
      if (iMap[Ghost1.getY()][Ghost1.getX() + 1] != M) {
        Ghost1.addX(1);
        ifGame = true;
      }
    } else if (iLastMove == 4) {
      // If the block on the left is not a wall - move there
      if (iMap[Ghost1.getY()][Ghost1.getX() - 1] != M) {
        Ghost1.addX(-1);
        ifGame = true;
      }
    }
  }
}

void mapOutput() {
  // Drawing map
  if (ifChange) {
    system("cls");
    std::string sMapa = "";
    for (int i = 0; i < MAP_SIZE_Y; i++) {
      for (int j = 0; j < MAP_SIZE_X; j++) {
        if (Player1.getX() == j && Player1.getY() == i) {
          sMapa += char(PLAYER);
        } // endif Player1.getX() == j && Player1.getY() == i
        else if (Ghost1.getX() == j && Ghost1.getY() == i) {
          sMapa += char(G);
        } // endif Ghost1.getX() == j && Ghost1.getY() == i
        else {
          sMapa += char(iMap[i][j]);
        }
      } // endfor j < MAP_SIZE_X
      sMapa += '\n';
    } // endfor i < MAP_SIZE_Y

    // Outputing score, velocity, SpeedBuff timer to check if everything is
    // working properly.
    if (Player1.getScore() != mainMap.iMaxScore) {
      sMapa += "Score: " + std::to_string(Player1.getScore());
      sMapa += "\nLifes: " + std::to_string(Player1.getLifes());
      sMapa += "\nPlayer Velocity: " + std::to_string(Player1.getVelocity());
      sMapa += "\nGhost Velocity: " + std::to_string(Ghost1.getVelocity());
    } else if (Player1.getScore() == mainMap.iMaxScore) {
      std::cout << "YOU WON!";
      Sleep(10000);
    }
    std::cout << sMapa;
  }
  Sleep(120);
}

void playerMovement() {
  // Move down
  if (GetAsyncKeyState(VK_DOWN)) {
    if (iMap[Player1.getY() + 1][Player1.getX()] != M) {
      Player1.addY(1);
      ifChange = true;
    } // endif iMap[Player1.getY() + 1][Player1.getX()] != M

    // Warp to the up side of the map
    if (Player1.getY() == 18 && Player1.getX() == 11) {
      Player1.setX(9);
      Player1.setY(0);
    } // endif Player1.getY() == 18 && Player1.getX() == 11

  } // endif (GetAsyncKeyState(VK_DOWN))

  // Move up
  if (GetAsyncKeyState(VK_UP)) {
    if (iMap[Player1.getY() - 1][Player1.getX()] != M) {
      Player1.addY(-1);
      ifChange = true;
    } // endif (iMap[Player1.getY() - 1][Player1.getX()] != M)

    // Warp to the down side of the map
    if (Player1.getY() == 0 && Player1.getX() == 9) {
      Player1.setX(11);
      Player1.setY(18);
    } // endif (Player1.getY() == 0 && Player1.getX() == 9)

  } // endif GetAsyncKeyState(VK_UP)

  // Move to the left
  if (GetAsyncKeyState(VK_LEFT)) {
    if (iMap[Player1.getY()][Player1.getX() - 1] != M) {
      Player1.addX(-1);
      ifChange = true;
    } // endif (iMap[Player1.getY()][Player1.getX() - 1] != M)

    // Warp to the right side of the map
    if (Player1.getY() == 9 && Player1.getX() == 0) {
      Player1.setX(19);
      Player1.setY(9);
    } // endif (Player1.getY() == 9 && Player1.getX() == 0)

  } // endif GetAsyncKeyState(VK_LEFT)

  // Move to the right
  if (GetAsyncKeyState(VK_RIGHT)) {
    if (iMap[Player1.getY()][Player1.getX() + 1] != M) {
      Player1.addX(1);
      ifChange = true;
    } // endif (iMap[Player1.getY()][Player1.getX() + 1] != M)

    // Warp to the left side of the map
    if (Player1.getY() == 9 && Player1.getX() == 19) {
      Player1.setX(0);
      Player1.setY(9);
    } // endif (Player1.getY() == 9 && Player1.getX() == 19)
  } // endif GetAsyncKeyState(VK_RIGHT)
}

void scoreSystem() {
  // Score +1 for P1
  if (iMap[Player1.getY()][Player1.getX()] == P1) {
    iMap[Player1.getY()][Player1.getX()] = W;

    Player1.setScore(Player1.getScore() + 1);
    ifChange = true;
  }

  // Score +2 for P2
  if (iMap[Player1.getY()][Player1.getX()] == P2) {
    iMap[Player1.getY()][Player1.getX()] = W;
    Player1.setScore(Player1.getScore() + 2);

    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC != 5) {
      Player1.setVelocity(21.37);
      Ghost1.setVelocity(5.2);
    }
    Player1.setVelocity(1.0);
    Ghost1.setVelocity(1.2);

    ifChange = true;
  }
}

int main() 
{

    bool ifGame = true;

    setStartingPositions();

    while (ifGame) {
        // Velocity related variables
        CurrentFrame = clock();
        PrevFrame = clock();

        // Time and velocity related variables
        PrevFrame = CurrentFrame;
        CurrentFrame = clock();
        deltaTime = CurrentFrame - PrevFrame;
        float Movement = deltaTime / 1000.0 * Player1.getVelocity();

        for (int i = 0; i <= Movement; i++) {
            playerMovement();
            scoreSystem();
        }

        if (GetAsyncKeyState(VK_ESCAPE)) {
            ifGame = false;
        }

        // Player - Ghost collision
        if (Player1.getX() == Ghost1.getX()) {
            if (Player1.getY() == Ghost1.getY()) {
                Player1.substractLife();
                setStartingPositions();
                Sleep(100);

                if (Player1.getLifes() <= 0) {
                    ifGame = false;
                    system("cls");
                    std::cout << "GAME OVER!";
                    Sleep(200);
                    exit(0);
                }
            }
        }

        ghostMovementSystem();
        mapOutput();
    } // endwhile (ifGame)    return 0;
}
