#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

bool push_unique(std::vector<int>& elements, int element)
{
  auto it = std::find(elements.begin(), elements.end(), element);
  if (it == elements.end())
  {
    elements.push_back(element);
    return true;
  }
  return false;
}

class Field
{
  private:
    int val_ = 0;
    bool covered_ = true;

  public:
    void uncover()
    {
      covered_ = false;
    }
    bool is_bomb() const
    {
      return val_ >= 100;
    }
    void increment()
    {
      val_ += 1;
    }
    bool covered() const
    {
      return covered_;
    }
    void set_bomb()
    {
      val_ = 100;
    }
    int value() const
    {
      return val_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Field& f);
};

std::ostream& operator<<(std::ostream& out, const Field& f)
{
  if (f.covered())
    return out << " ▣";
  if (f.val_ >= 100)
    out << " ☀";
  else if (f.val_ == 0)
    out << " ◻";
  else
    out << " ";
  switch (f.val_)
  {
  case 1:
    std::cout << "①";
    break;
  case 2:
    std::cout << "②";
    break;
  case 3:
    std::cout << "③";
    break;
  case 4:
    std::cout << "④";
    break;
  case 5:
    std::cout << "⑤";
    break;
  case 6:
    std::cout << "⑥";
    break;
  case 7:
    std::cout << "⑦";
    break;
  case 8:
    std::cout << "⑧";
    break;
  }
  return out;
}

class Playground
{
  private:
    std::vector<std::vector<Field>> terrain_;
    size_t height, length;

    void place_bomb(int bomb_x, int bomb_y)
    {
      terrain_[bomb_x][bomb_y].set_bomb();
      if (bomb_x > 0 && bomb_y > 0)
        terrain_[bomb_x - 1][bomb_y - 1].increment();
      if (bomb_x < height - 1 && bomb_y < length - 1)
        terrain_[bomb_x + 1][bomb_y + 1].increment();
      if (bomb_x > 0 && bomb_y < length - 1)
        terrain_[bomb_x - 1][bomb_y + 1].increment();
      if (bomb_x < height - 1 && bomb_y > 0)
        terrain_[bomb_x + 1][bomb_y - 1].increment();
      if (bomb_x > 0)
        terrain_[bomb_x - 1][bomb_y].increment();
      if (bomb_x < height - 1)
        terrain_[bomb_x + 1][bomb_y].increment();
      if (bomb_y < length - 1)
        terrain_[bomb_x][bomb_y + 1].increment();
      if (bomb_y > 0)
        terrain_[bomb_x][bomb_y - 1].increment();
    }

  public:
    Playground(size_t h, size_t l, size_t d)
    {
      double dif;
      switch (d)
      {
      case 1:
        dif = 0.1;
        break;
      case 2:
        dif = 0.3;
        break;
      case 3:
        dif = 0.6;
        break;
      default:
        dif = 0.1;
        break;
      }
      height = h;
      length = l;
      terrain_.resize(h);
      for (auto& row : terrain_)
        row.resize(l);
      // set bombs randomly
      std::vector<int> bombs;
      while (bombs.size() < l * h * dif)
        push_unique(bombs, rand() % (h * l));
      for (const auto& bomb : bombs)
        place_bomb(bomb / l, bomb % l);
    }

    bool open_field(int x, int y)
    {
      auto& f = terrain_[x][y];
      if (f.is_bomb())
      {
        for (int i = 0; i < height; ++i)
          for (int j = 0; j < height; ++j)
            if (terrain_[i][j].is_bomb())
              terrain_[i][j].uncover();
        return true;
      }
      if (f.value() != 0)
      {
        f.uncover();
        return false;
      }
      reveal(x, y);
      return false;
    }

    void reveal(int x, int y)
    {
      std::queue<std::pair<int, int>> to_open;
      to_open.push({ x, y });
      while (!to_open.empty())
      {
        auto top = to_open.front();
        to_open.pop();
        x = top.first;
        y = top.second;

        if (x >= height || y >= length) continue;

        if (terrain_[x][y].covered())
        {
          terrain_[x][y].uncover();
          if (terrain_[x][y].value() == 0)
          {
            to_open.push({ x + 1, y });
            to_open.push({ x - 1, y });
            to_open.push({ x, y + 1 });
            to_open.push({ x, y - 1 });
            to_open.push({ x + 1, y + 1 });
            to_open.push({ x - 1, y + 1 });
            to_open.push({ x + 1, y - 1 });
            to_open.push({ x - 1, y - 1 });
          }
        }
      }
    }

    friend std::ostream& operator<<(std::ostream& out,
      const Playground& playground);
};

std::ostream& operator<<(std::ostream& out, const Playground& playground)
{
  int c = 1;
  for (const auto& row : playground.terrain_)
  {
    std::string border = (c >= 10) ? "" : " ";
    out << c++;

    out << border;
    for (const auto& column : row)
      out << column;
    out << std::endl;
  }
  return out;
}

int main()
{
  srand(clock());
  size_t h, l, d;
  std::cout << "Height of the playboard is:";
  std::cin >> h;
  std::cout << "Length of the playboard is:";
  std::cin >> l;
  std::cout << "Difficulty: \n1-easy\n2-hard\n3-extreme\n";
  std::cin >> d;
  Playground playground(h, l, d);
  std::cout << std::string(20, '\n');
  std::cout << playground << std::endl;

  int x;
  int y;
  std::cout << "Open field(x,y):";
  while (std::cin >> x >> y)
  {
    std::cout << std::string(20, '\n');
    if (x <= 0 || y <= 0 || x > h || y > l)
    {
      std::cout << "Invalid entry" << std::endl;
      std::cout << "Open field(x,y):";
    }
    else
    {
      std::cout << "Opening " << x << ", " << y << std::endl;
      auto bomb = playground.open_field(x - 1, y - 1);
      std::cout << playground << std::endl;
      if (bomb)
      {
        std::cout << "You lose!" << std::endl;
        break;
      }
      std::cout << "Open field(x,y):";
    }
  }
}
