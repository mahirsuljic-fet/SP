#include <iostream>
#include <stack>
#include <string>

std::string get_input();
bool check_input(const std::string&);

int main()
{
  std::string input = get_input();
  std::cout << (check_input(input) ? "dobar" : "pogresan") << std::endl;
  return 0;
}

std::string get_input()
{
  char c;
  std::string input;
  while (std::cin >> c)
  {
    switch (c)
    {
    case '<':
    case '>':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
      input += c;
    }
  }
  return input;
}

bool check_input(const std::string& input)
{
  std::stack<char> brackets;

  for (char c : input)
  {
    if (brackets.empty())
    {
      switch (c)
      {
      case '>':
      case ')':
      case ']':
      case '}':
        return false;
      }
      brackets.push(c);
      continue;
    }

    switch (c)
    {
    case '{':
      if (brackets.top() == '[') return false;
    case '[':
      if (brackets.top() == '(') return false;
    case '(':
      if (brackets.top() == '<') return false;
    case '<':
      brackets.push(c);
      break;
    case '>':
      if (brackets.top() != '<') return false;
      brackets.pop();
      break;
    case ')':
      if (brackets.top() != '(') return false;
      brackets.pop();
      break;
    case ']':
      if (brackets.top() != '[') return false;
      brackets.pop();
      break;
    case '}':
      if (brackets.top() != '{') return false;
      brackets.pop();
      break;
    }
  }

  return brackets.empty();
}
