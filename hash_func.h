#ifndef hashset
#define hashset

#include "movie.h"
#include <list>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>

typedef QUERY * MOVIE_DATA; //query pointers are MOVIE_DATAs


template <typename HashFunc> //hash table class 
class hash_func {
public:
    hash_func(unsigned int init_size = 100, float init_occupancy = 0.5)
    : m_table(init_size), m_size(0), m_occupancy(init_occupancy) {}
    
    // Copy constructor 
    hash_func(const hash_func<HashFunc>& old)
    : m_table(old.m_table), m_size(old.m_size), m_occupancy(old.m_occupancy) {}
    
    ~hash_func() {}
    
    // operator= constructor 
    hash_func& operator=(const hash_func<HashFunc>& old) {
        if (&old != this) {
            this->m_table = old.m_table;
            this->m_size = old.m_size;
            this->m_hash = old.m_hash;
            this->m_occupancy = old.m_occupancy;
        }
        return *this;
    }
    //getter for m_size
    unsigned int size() const { return m_size; }
    
    // Modifiers
    void setSize(unsigned int s) { m_size = s; resize(s); }
    void setOccupancy(float occup) { m_occupancy = occup; }
    
    // Insert the key and position into hash table
    void insert(const QUERY& key, const MOVIE_DATA& a) {
        //checks for needed resize
        unsigned int threshold = (unsigned int)floor(m_occupancy*m_table.size());
        if (m_size >= threshold) {
            this->resize(2 * m_table.size());
        }
        // Compute the index by hashing the key
        unsigned int index = m_hash(key) % m_table.size();
        // Find appropriate position
        if (m_table[index].first.combine() == "") {
            //creates a pair if therre is a space in the index
            m_table[index] = std::make_pair(key, empty);
            m_size++;
        } 
        else {
            //when there is collision use linear probing
            while (m_table[index].first.combine() != "" && m_table[index].first.combine() != key.combine()) {
                index++;
                
                //arrives at the end of the table so start from the beginning 
                if (index == m_table.size()) {
                    index = 0;
                }
            }
            
            // No collision so insert a pair at the index
            if (m_table[index].first.combine() == "") {
                m_table[index] = std::make_pair(key, empty);
                m_size++;
            }
        }
        //add the MOVIE_DATA object to the list of MOVIE_DATAS
        m_table[index].second.push_back(a); 
    }
    
    // Find key's position list and return a list of MOVIE_DATA
    const std::list<MOVIE_DATA>& getList(const QUERY& key) const {
        unsigned int index = m_hash(key) % m_table.size(); //calculates index through hashing
        const unsigned int const_index = index; 
        
        // Find using linear probing
        while (m_table[index].first.combine() != key.combine()) {
            index++;
            if (index == m_table.size()) {
                index = 0;
            }
            // Returning to start position means that we didnt find a matching key
            if (index == const_index) { 
                return empty;
            }
        }
        
        //found a matching key so we return the list 
        return m_table[index].second;
    }
    
private:
    std::vector<std::pair<QUERY,std::list<MOVIE_DATA> > > m_table;
    HashFunc m_hash;
    unsigned int m_size;
    float m_occupancy;
    std::list<MOVIE_DATA> empty;
    
    // Private helper functions
    void resize(unsigned int new_size) {
        //create a new table
        std::vector<std::pair<QUERY, std::list<MOVIE_DATA> > > new_table(new_size);
        
        // For each entry in old table
        for (unsigned int i = 0; i < m_table.size(); ++i) {
            if (m_table[i].first.combine() != "") {
                //Grab the key
                QUERY key = m_table[i].first;
                
                //Rehash the key to get a new index
                unsigned int index = m_hash(key) % new_size;
                
                // Insert into new position of new hash table
                while (new_table[index].first.combine() != "") {
                    index++;
                    if (index == new_table.size()) {
                        index = 0;
                    }
                }
                new_table[index] = m_table[i];
            }
        }
        //set m_table to new_table
        this->m_table = new_table;
    }
};
#endif