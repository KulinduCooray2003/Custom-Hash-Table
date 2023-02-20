#ifndef movie_class
#define movie_class

#include <string>
#include <vector>

class QUERY {
    public:
        QUERY(const std::string& title, const std::string& year, const std::string& runTime, const std::string& genreCount, 
        const std::string& actorCount, const std::string& roleCount, const std::vector<std::string>& glist, 
        const std::vector<std::string>& alist, const std::vector<std::string>& rlist) 
        : t(title), y(year), run(runTime), genre(genreCount), actor(actorCount), role(roleCount), genreList(glist), 
        actorList(alist), roleList(rlist) {}

        QUERY(); //default constructor

        //getters for private member variables
        const std::string& getTitle() const { return t; }
        const std::string& getYear() const { return y; }
        const std::string& getRunTime() const { return run; }
        const std::string& getGenreCount() const { return genre; }
        const std::string& getActorCount() const { return actor; }
        const std::string& getRoleCount() const { return role; }
        const std::vector<std::string>& getGenreList() const { return genreList; }
        const std::vector<std::string>& getActorList() const { return actorList; }
        const std::vector<std::string>& getRoleList() const { return roleList; }

        //a concatenate function
        const std::string combine() const;
        


    private:
        std::string t;
        std::string y;
        std::string run;
        std::string genre;
        std::string actor;
        std::string role;
        std::vector<std::string> genreList;
        std::vector<std::string> actorList;
        std::vector<std::string> roleList;
};

//function to return a query object by copy

const QUERY data(const std::string& t1,const std::string& y1,const std::string& r1,const std::string& gc,
const std::string& ac, const std::string& rc, const std::vector<std::string>& gl,
const std::vector<std::string> al, const std::vector<std::string> rl, const std::vector<int>& c);

#endif