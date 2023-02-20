#include "movie.h"


QUERY::QUERY() {}  

const QUERY data(const std::string& t1,const std::string& y1,const std::string& r1,const std::string& gc,
const std::string& ac, const std::string& rc, const std::vector<std::string>& gl,
const std::vector<std::string> al, const std::vector<std::string> rl, const std::vector<int>& c) {
    std::string title = t1;
    std::string year = y1;
    std::string run = r1;
    std::string genrec = gc;
    std::string actorc = ac;
    std::string rolec = rc;
    std::vector<std::string> genreVec = gl;
    std::vector<std::string> actorVec = al;
    std::vector<std::string> roleVec = rl;    
    for (unsigned int i = 0; i < c.size(); i++) {  //creates query objects from the 1s being the data and 0s being wildcards ("?" or "0")
        
        if (i == 0) {
            if (c[i] == 0) {
                title = "?";
            }
        }
        else if (i == 1) {
            if (c[i] == 0) {
                year = "?";
            }
        }
        else if (i == 2) {
            if (c[i] == 0) {
                run = "?";
            }
        }
        else if (i == 3) {
            if (c[i] == 0) {
                genrec = "0";
                genreVec.clear();
            }
        }
        else if (i == 4) {
            if (c[i] == 0) {
                actorc = "0";
                actorVec.clear();
            }
        }
        else if (i == 5) {
            if (c[i] == 0) {
                rolec = "0";
                roleVec.clear();
            }
        }
    }
    return QUERY(title, year, run, genrec, actorc, rolec, genreVec, actorVec, roleVec);
}

const std::string QUERY::combine() const { //return string by copy of all the private member string varialbes 
    std::string tmp = t+y+run+genre+actor+role;
    for (unsigned int i = 0; i < genreList.size(); i++) { //concats the strings in the lists as well
        tmp += genreList[i];
    }
    for (unsigned int i = 0; i < actorList.size(); i++) {
        tmp += actorList[i];
    }
    for (unsigned int i = 0; i < roleList.size(); i++) {
        tmp += roleList[i];
    }
    return tmp;
}
