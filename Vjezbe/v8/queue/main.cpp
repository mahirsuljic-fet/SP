#include "queue.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  Queue<std::string> moj_queue;

  try {
    std::cout << moj_queue.top() << std::endl;
  } catch (std::runtime_error& err) {
    std::cout << "Error: " << err.what() << std::endl;
  }

  std::cout << moj_queue.size() << std::endl;
  moj_queue.push("Hello");
  std::cout << moj_queue.size() << std::endl;

  moj_queue.top() += ", world!";
  std::cout << moj_queue.top() << std::endl;

  {
    const auto& moj_queue2 = moj_queue;
    std::cout << moj_queue2.top() << std::endl;
  }

  std::string lorem_ipsum = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris mollis "
    "ante in neque condimentum rhoncus. Phasellus nec quam ornare, commodo "
    "massa in, rutrum dui. Nullam arcu turpis, bibendum non dolor placerat, "
    "auctor posuere libero. Pellentesque quam dolor, rutrum at nunc in, "
    "convallis condimentum purus. Vivamus nec mattis arcu. Aenean eleifend, "
    "nunc at rhoncus rhoncus, justo sapien aliquam turpis, eu viverra ligula "
    "ipsum vel velit. Vestibulum id interdum lacus, nec finibus velit. Sed "
    "et dignissim velit. Sed eu ipsum sagittis nulla ultricies condimentum "
    "eget quis libero. Ut volutpat massa sit amet luctus ultrices. Etiam "
    "pulvinar tincidunt lorem sit amet condimentum. Morbi ultrices vitae "
    "enim in imperdiet. Maecenas vitae arcu placerat augue dignissim congue. "
    "Duis tempus in odio quis convallis. Proin volutpat lectus at tortor "
    "malesuada dapibus. Mauris fringilla fermentum dapibus. Maecenas rhoncus "
    "tincidunt tellus id porta. Aenean dapibus vestibulum lacus in "
    "fermentum. Praesent cras amet."};

  moj_queue.push(std::move(lorem_ipsum));
  moj_queue.pop();
  std::cout << "Top: " << std::endl << moj_queue.top() << std::endl;
  std::cout << "Orginalni string: " << std::endl << lorem_ipsum << std::endl;

  return 0;
}
