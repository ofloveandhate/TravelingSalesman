/* Travelling Salesman Project
 * ACMS 60212
 * Reader.hpp
 * class will have functionality to read json file so that Graph class can make boost
 * graph...necessary because number of vertices is needed when boost graph is constructed
 */

#ifndef READER_HPP
#define READER_HPP

#include "Node.hpp"
#include <cctype>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Reader {
 
   public:
      Reader();
      Reader(const std::string &);
      std::vector<Node> getCities();

   private:
      std::ifstream fp;
};

Reader::Reader() {};

// non-default constructor will take a file name and read it
Reader::Reader(const std::string &filename) {

   fp.open(filename);
   assert(fp);
}

std::vector<Node> Reader::getCities() {
   // return vector of Nodes for city info
   // not necessary to hold info as a member var, hold it in Graph class
   std::vector<Node> cities;
   std::string line, key, value;
   std::string city, state;
   double lon, lat;
   int i = 0;

   // this parsing is kinda janky...but it gets the job done
   while (getline(fp,line)) {

      std::cout << line << std::endl;

      // do all of this for each line in the JSON file
      key.clear();
      value.clear();
      auto s_itr = line.begin();
      // increment string pointer until it hits first character
      while (!isalpha(*s_itr) && s_itr != line.end()) {
         ++s_itr;
      }
      // if line is garbage then move on to the next one
      if (s_itr == line.end())
         continue;
      // add alpha characters to key (see what json key for line is)
      while (isalpha(*s_itr))
         key += *(s_itr++);
      // move on to next line if it is not one we want
      if (key != "city" && key!= "state" && key != "latitude" && key != "longitude")
         continue;
      // increment string pointer until it hits next alpha character
      while (!isalnum(*s_itr) && *s_itr != '-')
         ++s_itr;
      // add alpha characters to key (see what json key for line is)
      while (isalnum(*s_itr) || isspace(*s_itr) || *s_itr == '-' || *s_itr == '.' || *s_itr == '\'')
         value += *(s_itr++);

      // insert found info into node in cities set
      if (key == "city") {
         city = value;
      } else if (key == "state") {
         state = value;
      } else if (key == "latitude") {
         lat = std::stod(value);
      } else if (key == "longitude") {
         lon = std::stod(value);
      }

      ++i;
      if (i%4 == 0) {
         Node temp(city,state,lat,lon);
         cities.push_back(temp);
         i = 0;
      }
   }

/*   for (auto it = cities.begin(); it != cities.end(); ++it) {
      std::cout << it-cities.begin() << '\t' << it->getName() << '\t' << it->getState() << '\t' << it->getLat() << '\t' << it->getLon() << std::endl;
   }
*/
   return cities;
}

#endif