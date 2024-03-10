#include <iostream>
#include <ostream>

// proizvoljna velicina ploce
// metod za zavrsenu igru (pobjeda, nerijeseno, ...)
// sigurnosne mjere (da li su i, j validni i da li je polje slobodno)

class Board
{
  public:
    Board()
    {
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          data_[i][j] = ' ';
    }

    void set(int x, int y, char c)
    {
      data_[x][y] = c;
    }

    bool free(int x, int y) const
    {
      return data_[x][y] == ' ';
    }

    char get(int x, int y) const
    {
      return data_[x][y];
    }

  private:
    char data_[3][3];
};

class Player
{
  public:
    virtual void play(Board& board) = 0;
    virtual ~Player() = default;
};

class HumanPlayer : public Player
{
  public:
    HumanPlayer(char c) : symbol_ { c } { }

    void play(Board& board) override
    {
      int i, j;

      std::cout << "Unesite poziciju: " << std::endl;
      std::cin >> i >> j;

      board.set(i, j, symbol_);
    }

  private:
    char symbol_;
};

class MachinePlayer : public Player
{
  public:
    MachinePlayer(char c) : symbol_ { c } { }

    void play(Board& board) override
    {
      int i = rand() % 3;
      int j = rand() % 3;
      board.set(i, j, symbol_);
    }

  private:
    char symbol_;
};

std::ostream& operator<<(std::ostream& out, const Board& board)
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
      out << board.get(i, j) << '|';
    out << std::endl
        << "------"
        << std::endl;
  }

  return out;
}

int main(int argc, char* argv[])
{
  Board board;
  Player* p1;
  Player* p2;
  int izbor;

  std::cout << "1 - Human vs Human\n"
            << "2 - Human vs Machine\n\n"
            << "Izbor: ";
  std::cin >> izbor;

  if (izbor == 1)
  {
    p1 = new HumanPlayer('x');
    p2 = new HumanPlayer('o');
  }
  else if (izbor == 2)
  {
    p1 = new HumanPlayer('x');
    p2 = new MachinePlayer('o');
  }

  while (1)
  {
    std::cout << board << std::endl;
    p1->play(board);
    // if (board.fin()) break; // za DZ

    std::cout << board << std::endl;
    p2->play(board);
    // if (board.fin()) break; // za DZ
  }

  delete p1;
  delete p2;

  return 0;
}
