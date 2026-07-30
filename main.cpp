#include "Tries.hpp"
#include <iostream>
#include <string>
#include <vector>





int main()
{
    std::vector<std::string> strs = {"ilyass" , "imane" , "maroua" , "meryem"};
    tries t;

    for (std::string str : strs)
        t.insert(str);
    std::string s = s;
    if (t.search(s) == false)
        std::cout << s << " is Not a word in our database" << std::endl;
    else
        std::cout << s << " is a word in our database" << std::endl;

    if (t.startwith(s))
        std::cout << s << " is a prefix in our database" << std::endl;
    else
        std::cout << s << " is Not a prefix in our database" << std::endl;

    t.remove(s, t.get_root(), 0);
    if (t.search(s) == false)
        std::cout << s << " is been removed from our database" << std::endl;

    return 0;

    




}