#include<map>
#include<iterator>
#include<iostream>

int main() {
    // std::map<std::string, std::string>::iterator it;
    // std::map<std::string, std::string> num_map;
    // num_map["one"] = "onehere";
    // num_map["two"] = "twohere";
    // num_map["three"] = "threehere";

    // it  = num_map.begin();
    // while (it != num_map.end())
    // {
    //     std::cout<< it->first << " " << num_map[it->first] <<std::endl;
    //     it++;
    // }
    
    // calls a_map.begin() and a_map.end()
    // std::cout<< num_map["one"] << std::endl;
    // std::cout<< num_map["two"] << std::endl;
    // it = num_map.find("thrdee");

    // if (it == num_map.end())
    //     std::cout<<"not fournd"<<"\n";
    std::string link = "/one/two/three/four/five";
    std::cout<<link<<"\n";
    while(link.size())
    {
        link = link.substr(0, link.find_last_of("/"));
        std::cout<<link<<"\n";
        std::cout<< "size: " <<link.size()<<"\n";
    }
}