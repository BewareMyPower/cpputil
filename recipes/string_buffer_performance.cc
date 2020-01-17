#include "cpputil/range.h"
#include "cpputil/string_buffer.h"
#include "cpputil/string_format.h"
#include "cpputil/timer.h"

#include <time.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  default_random_engine e;
  e.seed(time(nullptr));
  uniform_int_distribution<int> ui;
  uniform_real_distribution<double> ud;

  constexpr int N = 10000;
  vector<int> vi(N);
  vector<double> vd(N);
  vector<string> vs(N);

  using cpputil::Range;

  for (int i : Range(0, N)) {
    vi[i] = ui(e);
    vd[i] = ud(e);
    vs[i] = to_string(ui(e));
  }

  cpputil::Timer timer;

  timer.start();
  std::ostringstream oss;
  for (int i : Range(0, N)) {
    oss << vi[i] << ',' << vd[i] << ',' << vs[i] << '\n';
  }
  auto s1 = oss.str();
  auto t1 = timer.stop();

  timer.start();
  cpputil::StringBuffer buffer;
  for (int i : Range(0, N)) {
    buffer << vi[i] << ',' << vd[i] << ',' << vs[i] << '\n';
  }
  auto s2 = buffer.str();
  auto t2 = timer.stop();

  timer.start();
  string s3 = "";
  for (int i : Range(0, N)) {
    s3 += to_string(vi[i]);
    s3.push_back(',');
    s3 += to_string(vd[i]);
    s3.push_back(',');
    s3 += vs[i];
    s3.push_back('\n');
  }
  auto t3 = timer.stop();

  cout << "stringstream: " << t1 << " us (" << s1.size() << " bytes)" << endl;
  cout << "StringBuffer: " << t2 << " us (" << s2.size() << " bytes)" << endl;
  cout << "string:       " << t3 << " us (" << s3.size() << " bytes)" << endl;

  return 0;
}
