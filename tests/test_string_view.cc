#include "string_view.h"
using cpputil::cxx17::string_view;

#include <iostream>
#include <string>
using namespace std;

// TODO: Replace it with string_view::copy() or operator<<
inline string toString(string_view seq) {
  if (!seq.empty()) return {seq.cbegin(), seq.cend()};
  return "(empty)";
}

int main(int argc, char* argv[]) {
  {
    string_view seq;
    // true: "(empty)"
    cout << boolalpha << seq.empty() << ": \"" << toString(seq) << "\"\n";
  }
  {
    string_view seq("hello");
    // [5] hello
    cout << "[" << seq.size() << "] " << toString(seq) << endl;

    // h, e, l, l, o
    for (size_t i = 0; i < seq.size(); i++) {
      if (i > 0) cout << ", ";
      cout << seq[i];
    }
    cout << endl;

    // h,e,l,l,o,
    for (const auto& c : seq) cout << c << ",";
    cout << endl;

    // string_view::at: pos (which is 6) >= this->size() (which is 5)
    try {
      cout << seq.at(6) << endl;
    } catch (const out_of_range& e) {
      cerr << e.what() << endl;
    }

    // front: h | back: o
    cout << "front: " << seq.front() << " | back: " << seq.back() << endl;

    // s[2:] = llo
    seq.remove_prefix(2);
    cout << "s[2:] = " << toString(seq) << endl;

    // s[2:-1] = ll
    seq.remove_suffix(1);
    cout << "s[2:-1] = " << toString(seq) << endl;

    string_view otherseq("hello");
    seq.swap(otherseq);
    // hello
    cout << toString(seq.substr()) << endl;
    // hello
    cout << toString(seq.substr(0, 1111)) << endl;
    // lo
    cout << toString(seq.substr(3)) << endl;
    // o
    cout << toString(seq.substr(4, 1)) << endl;

    // string_view::substr: pos (which is 5) >= this->size() (which is 5)
    try {
      cout << toString(seq.substr(seq.size())) << endl;
    } catch (const out_of_range& e) {
      cerr << e.what() << endl;
    }
  }

  return 0;
}
