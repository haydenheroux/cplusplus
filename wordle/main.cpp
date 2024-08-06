#include <iostream>
#include <vector>

struct constraint {
  int position;
  char character;

  constraint(int position, char character)
      : position(position), character(character) {}
};

class engine {
public:
  engine();
  inline void greens(std::string s);
  inline void yellows(std::string s);
  inline void grays(std::string s);
  void solve();

private:
  void add_constraints(std::vector<constraint> &destination, std::string &s);

  std::vector<constraint> m_greens;
  std::vector<constraint> m_yellows;
  std::vector<constraint> m_grays;
};

engine::engine() {}

void engine::add_constraints(std::vector<constraint> &destination,
                             std::string &s) {
  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];

    if (c == '_')
      continue;

    destination.emplace_back(i, c);
  }
}

inline void engine::greens(std::string s) { add_constraints(m_greens, s); }

inline void engine::yellows(std::string s) { add_constraints(m_yellows, s); }

inline void engine::grays(std::string s) { add_constraints(m_grays, s); }

void engine::solve() {
  std::string s = "_____";

  for (auto constraint : m_greens) {
    s[constraint.position] = constraint.character;
  }

  std::cout << s << '\n';
}

int main() {
  engine engine;

  engine.greens("____L");
  engine.greens("ANV__");
  engine.greens("___I_");

  engine.solve();

  return 0;
}
