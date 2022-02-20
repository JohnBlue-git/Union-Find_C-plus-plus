
/*
Auther: John Blue
Time: 2022/1
Platform: ATOM with MinGw and g++compiler
Object: Union_Find
*/

#include <iostream>
#include <stdlib.h> // include rand function
#include <time.h>   // time function

class Union_Find
{
private:
  // data
  int L;
  int* id;
  int* sz;

  // constructor and operator
  Union_Find(const Union_Find& copy);
  Union_Find& operator=(const Union_Find& copy);

public:
  // constructor
  Union_Find(int N): L(N) {
    id = new int[N];
    sz = new int[N];
    for (int i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
    }
  }
  ~Union_Find() { delete id; }

  // operator
  friend std::ostream& operator<<(std::ostream& os, const Union_Find& print);

  // function
  int find(int p);
  void m_union(int p, int q);
  bool connected(int p, int q) { return (find(p) == find(q)); }
};

std::ostream& operator<<(std::ostream& os, const Union_Find& print) {
  if (print.L == 0) {
    os << "empty";
    return os;
  }
  for (int i = 0; i < print.L; i++) {
    os << " " << print.id[i];
  }
  os << "\n";
  return os;
}

/*
// Method: quick find
// initialize: N
// find: 1
// union: N
// connected: 1
int Union_Find::find(int p) { return id[p]; }
//
void Union_Find::union(int p, int q) {
  int pid = id[p];
  int qid = id[q];
  for (int i = 0; i < L; i++) {
    if (id[i] == pid) {
      id[i] = qid;
    }
  }
}

// Method: quick union
// ... under worst case
// initialize: N
// find: N
// union: N
// connected: N
//
int Union_Find::find(int p) {
  while (p != id[p]) {
    p = id[p];
  }
  return p;
}
//
void Union_Find::union(int p, int q) {
  int pid = find(p);// root
  int qid = find(q);// root
  id[pid] = qid;// change root
}
*/


// Method: weighted UF
// initialize: N
// find: lg N
// union: lg N
// connected: lg N
//
int Union_Find::find(int p) {
  while (p != this->id[p]) {
    p = this->id[p];
  }
  return p;
}
//
void Union_Find::m_union(int p, int q) {
  // root
  int pid = this->find(p);
  int qid = this->find(q);
  // change root
  if (pid == qid) {
    return;
  }
  if (this->sz[p] < this->sz[q]) {
    this->id[pid] = qid;
    this->sz[qid] += this->sz[pid];
  }
  else {
    this->id[qid] = pid;
    this->sz[pid] += this->sz[qid];
  }
}

int main()
{
  // count time period: start
  clock_t start = clock();

  // setting random size
  srand(time(NULL));
  int N = rand() % 30 + 1;

  // setting
  Union_Find uf(N);
  std::cout << "uf: " << uf << std::endl;
  // union
  int half = N / 2;
  for (int i = 1; i < half; i++) {
    if (! uf.connected(uf.find(i - 1), uf.find(i))) {
      uf.m_union(i - 1, i);
    }
    std::cout << "uf: " << uf << std::endl;
  }
  for (int i = half + 1; i < N; i++) {
    if (! uf.connected(uf.find(i - 1), uf.find(i))) {
      uf.m_union(i - 1, i);
    }
    std::cout << "uf: " << uf << std::endl;
  }
  std::cout << "connected(0, N - 1): " << uf.connected(0, N - 1) << std::endl;
  std::cout << "last connecting ..." << std::endl;
  uf.m_union(0, half + 1);
  std::cout << "connected(0, N - 1): " << uf.connected(0, N - 1) << std::endl;

  // count time period: end
  clock_t end = clock();
  std::cout << "\nProcess period: " << (end - start) / CLOCKS_PER_SEC << std::endl;
}
