#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream in;
  std::vector<bool> pos(13, false);
  int player_points = 0;
  int spectators_points = 0;
  int temp_sector = 1;

  std::cout << "Welcome to the game "
               "What Where When"
               "!"
            << std::endl;
  std::cout << "Enter your answers in capital letters. ";
  std::cout << "If the answer consists of several words, "
               "enter it together in one word!"
            << std::endl;

  while (player_points != 6 && spectators_points != 6) {
    int offset;
    std::cout
        << "Enter the offset relative to the current sector on the reel: ";
    std::cin >> offset;

    temp_sector += offset;
    if (temp_sector > 13)
      temp_sector -= 13;
    while (pos[temp_sector - 1]) {
      temp_sector++;
    }
    pos[temp_sector - 1] = true;

    std::string sector = std::to_string(temp_sector);
    std::string q = "Question" + sector + "/";
    in.open(q + sector + ".txt" + "");
    if (in.is_open()) {
      std::string buffer;
      std::getline(in, buffer, '\0');
      std::cout << "Question " << temp_sector << ": " << std::endl;
      std::cout << buffer;
      std::cout << std::endl;
    } else
      std::cout << "Error! The path file is invalid!" << std::endl;
    in.close();

    std::string answer;
    std::cout << "Enter your answer: ";
    std::cin >> answer;
    in.open(q + "Answer" + sector + ".txt" + "");
    if (in.is_open()) {
      std::string current_answ;
      in >> current_answ;
      if (answer == current_answ) {
        player_points++;
        std::cout << "Correct answer! You get a point!" << std::endl;
      } else {
        spectators_points++;
        std::cout << "Incorrect answer! Correct answer is ";
        std::cout << current_answ << std::endl;
        std::cout << "Spectators get a point!" << std::endl;
      }
    } else
      std::cout << "Error! The path file is invalid!" << std::endl;
    in.close();
  }
  if (player_points == 6)
    std::cout << "Player won!" << std::endl;
  if (spectators_points == 6)
    std::cout << "Spectators won!" << std::endl;
  return 0;
}