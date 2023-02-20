#include <list>
#include <vector>
#include <string>
#include "movie.h"
#include <iostream> 
#include <fstream>
#include <map>
#include "hash_func.h"
#include <cassert>
#include <cstdlib>


class hash_string_obj { //functor for hash function 
public:

  unsigned int operator() (const QUERY& key) const {
    unsigned int hash = 1315423911;
    std::string temp = key.combine(); //hashes based on the concatenated string of the QUERY object
    for(unsigned int i = 0; i < temp.length(); i++) {
      hash ^= ((hash << 5) + temp[i] + (hash >> 2));
    }
    return hash;
  }  
};

//code given to create a vector of vector of ints to fill all 64 permutations

void permute_filters(int pos, std::vector<int> filter, std::vector<std::vector<int> >& a){
	if(pos == 6){
		a.push_back(filter);
		return;
	}

	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new, a);
	permute_filters(pos+1, filter, a);
}

//Driver function, feel free to modify to pass more arguments
void permute_filters(std::vector<std::vector<int> >& a){
	permute_filters(0, std::vector<int>(), a);
}

typedef hash_func<hash_string_obj> ds_hashset_type;


int main() {
    std::vector<std::vector<int> > a;
	permute_filters(a); //has 64 vectors of 1s and 0s inside
    std::map<std::string, std::string> actors; //map to store actor data
    ds_hashset_type table;
    std::string command;
    std::string text;
    std::list<QUERY> Movies;
    while (std::cin >> command) {
        if (command == "movies") { //movie command
            std::cin >> text;
            std::ifstream input(text);
            if (!input.good()) { //sees if opening the file was successful
                std::cerr << "Can't open " << text << " to read." << std::endl;
                exit(1);
            } 
            if (input.is_open()) { //parses file data and creates a QUERY object to be push_backed to the Movies list
                std::string title;
                std::string year;
                std::string time;
                std::string gnum;
                std::string anum;
                std::string rnum;

                while (input >> title >> year >> time) {
                    std::vector<std::string> glist;
                    std::vector<std::string> alist;
                    std::vector<std::string> rlist;
                    std::string holder;
                    input >> gnum;
                    for (int i = 0; i < std::stoi(gnum); i++) {
                        input >> holder;
                        glist.push_back(holder);
                    }
                    input >> anum;
                    for (int j = 0; j < std::stoi(anum); j++) {
                        input >> holder;
                        alist.push_back(holder);
                    }
                    input >> rnum;
                    for (int l = 0; l < std::stoi(rnum); l++) {
                        input >> holder;
                        rlist.push_back(holder);
                    }
                    QUERY m(title, year, time, gnum, anum, rnum, glist, alist, rlist);
                    Movies.push_back(m);
                    MOVIE_DATA mstar = &Movies.back(); //creates a pointer to the QUERY object
                    for (unsigned int i = 0; i < a.size(); i++) { 
                        QUERY p = data(title,year,time,gnum,anum, rnum, glist, alist, rlist, a[i]); //creates 64 possible QUERY objects from the starting QUERY object
                        table.insert(p, mstar); //creates the hash table by inserting the object and pointer
                    }
                }
            }
            input.close();
        }
        else if (command == "actors") { //actor command
            std::cin >> text;
            std::ifstream input2(text);
            if (!input2.good()) { 
                std::cerr << "Can't open " << text << " to read." << std::endl;
            exit(1);
            }
            std::string key, value;    
            if (input2.is_open()) { //parses actor data and makes the nconst the key and the actor name as the value
                while(input2 >> key >> value) {
                    actors[key] = value;
                }
            }
            input2.close();
        }
        else if (command == "query") { //query command 
            std::string t2;
            std::string y2;
            std::string run2;
            std::string g2;
            std::string a2;
            std::string r2;
            std::vector<std::string> g2Vect;
            std::vector<std::string> a2Vect;
            std::vector<std::string> r2Vect;
            std::string holder2;
            for (unsigned int i = 0; i < 6; i++) {
                if (i == 0) {
                    std::cin >> t2;
                }
                else if (i == 1) {
                    std::cin >> y2;
                }
                else if (i == 2) {
                    std::cin >> run2;
                }
                else if (i == 3) {
                    std::cin >> g2;
                    if (g2 == "0") {
                            continue;
                        }
                    for (int p = 0; p < std::stoi(g2); p++) {
                        std::cin >> holder2;
                        g2Vect.push_back(holder2); 
                    }
                }
                else if (i == 4) {
                    std::cin >> a2;
                    if (a2 == "0") {
                            continue;
                        }
                    for (int o = 0; o < std::stoi(a2); o++) {
                        std::cin >> holder2;
                        a2Vect.push_back(holder2); 
                    }
                }
                else if (i == 5) {
                    std::cin >> r2;
                    if (r2 == "0") {
                            continue;
                        }
                    for (int u = 0; u < std::stoi(r2); u++) {
                        std::cin >> holder2;
                        r2Vect.push_back(holder2);
                    }
                }
            }
            QUERY temp(t2,y2,run2,g2,a2,r2,g2Vect,a2Vect,r2Vect); //creates a query object from the user input 
            std::list<MOVIE_DATA> movie_list = table.getList(temp); //grabs the list of MOVIE_DATA by using the QUERY temp as the key to get the index
            if (movie_list.size() == 0) {
                std::cout << "No results for query." << std::endl;
            }
            else {
                std::cout << "Printing " << movie_list.size() << " result(s):" << std::endl;
                std::list<MOVIE_DATA>::const_iterator it;
                for (it = movie_list.begin(); it != movie_list.end(); it++) { //dereferences the iterator and then the pointer to access the movies member variables
                    std::cout << (*it)->getTitle() << std::endl;
                    std::cout << (*it)->getYear() << std::endl;
                    std::cout << (*it)->getRunTime() << std::endl;
                    g2 = (*it)->getGenreCount();
                    std::cout << g2;
                    for (int j = 0; j < std::stoi(g2); j++) {
                        std::cout << " " << (*it)->getGenreList()[j];
                    }
                    std::cout << std::endl;
                    a2 = (*it)->getActorCount();
                    r2 = (*it)->getRoleCount();
                    assert(a2 == r2);
                    std::cout << a2;
                    for (int l = 0; l < std::stoi(a2); l++) {
                        std::cout << " " << actors[(*it)->getActorList()[l]] << " (" << (*it)->getRoleList()[l] << ")";
                    }
                    std::cout << std::endl;
                }
            }
        }
        else if (command == "table_size") { //sets table size
            std::cin >> text;
            unsigned int size = (unsigned int)atoi(text.c_str());
            table.setSize(size);
        }
        else if (command == "occupancy") { //sets the occupancy of the hash table
            std::cin >> text;
            float occupany = (float)atof(text.c_str());
            table.setOccupancy(occupany);   
        }
        else if (command == "quit") { //quits the program
            break;
        }
    }
    return 0;
}