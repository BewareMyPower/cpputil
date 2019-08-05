#include "char_sequence.h"

#include <iostream>
#include <string>
using namespace std;

// TODO: Replace it with CharSequence::copy() or operator<<
inline string toString(CharSequence seq) {
  if (!seq.empty()) return {seq.cbegin(), seq.cend()};
  return "(empty)";
}

int main(int argc, char* argv[]) {
  {
    CharSequence seq;
    // true: "(empty)"
    cout << boolalpha << seq.empty() << ": \"" << toString(seq) << "\"\n";
  }
  {
    CharSequence seq("hello");
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

    // CharSequence::at: pos (which is 6) >= this->size() (which is 5)
    try {
      cout << seq.at(6) << endl;
    } catch (const out_of_range& e) {
      cerr << e.what() << endl;
    }

    // front: h | back: o
    cout << "front: " << seq.front() << " | back: " << seq.back() << endl;

    // llo
    seq.remove_prefix(2);
    cout << "s[2:] = " << toString(seq) << endl;

    // ll
    seq.remove_suffix(1);
    cout << "s[2:-1] = " << toString(seq) << endl;

    CharSequence otherseq("hello");
    seq.swap(otherseq);
    // hello
    cout << toString(seq.substr()) << endl;
    // lo
    cout << toString(seq.substr(3)) << endl;
    // o
    cout << toString(seq.substr(4, 1)) << endl;
  }

  return 0;
}
