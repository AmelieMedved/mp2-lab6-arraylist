#include <iostream>
#include "arraylist.h"

int main()
{
  //TArrayList<char> d(10);

  //d.InsFirst('a');
  //d.InsLast('b');
  //d.InsFirst('c');

  //TArrayListIterator<char> i = d.begin();
  //// варианты обхода
  //while (i.IsGoNext()) // 1
  //{
  //  std::cout << i.GetData() << "\n";
  //  i.GoNext();
  //}
  //
  //std::cout << "\n";

  //for (auto& elem : d) // 2
  //  std::cout << elem << "\n";

  //std::cout << d << "\n";

  //for (TArrayListIterator<char> j = d.begin(); j != d.end(); ++j)
  //  std::cout << *j << "\n";

  TArrayList<int> al(5);
 
  al.InsFirst(0);
  al.InsFirst(1);
  al.InsFirst(3);
  al.InsFirst(4);
  al.InsFirst(5);

  TArrayListIterator<int> it((al.begin()));
 

  for (it; it != al.end(); ++it)
    cout << it.GetData() << '\n';

  return 0;
}
