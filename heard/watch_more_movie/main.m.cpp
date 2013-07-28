#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Interval
{
   int lower;
   int upper;
   Interval() : lower(0), upper(0) {}
   Interval(const int l, const int u) : lower(l), upper(u) {}
};

ostream& operator<<(ostream& os, const vector<Interval>& input)
{
   os << "[";
   for ( int i = 0, len = input.size(); i < len; ++i )
   {
      os << "[" << input[i].lower << "," << input[i].upper << "]";
      if ( i != len ) os << ", ";
   }
   os << "]";
   return os;
}

ostream& operator<<(ostream& os, const map<int, pair<int, vector<Interval> > >& input)
{
   os << "[\n";
   for ( map<int, pair<int, vector<Interval> > >::const_iterator it = input.begin();
         it != input.end(); ++it )
   {
      os << it->first << "(max = " << it->second.first << ") -> "
         << it->second.second << '\n';
   }
   os << "]";
   return os;
}

class Solution
{
public:
struct CompObj
{
   bool operator() (const Interval& a, const Interval& b) { return a.lower < b.lower; }
} compObj;

// Watching the most complete movies
vector<Interval> watch_movie(vector<Interval>& intervals)
{
   // map from the start time of the movie to (longest watching time, movies to watch)
   map<int, pair<int, vector<Interval> > > map_pos2max;

   // Sort accendingly by lower limit
   sort(intervals.begin(), intervals.end(), compObj);

   // Going backward, start from latest movie
   for ( vector<Interval>::reverse_iterator it = intervals.rbegin();
         it != intervals.rend(); ++it )
   {
      watch_movie_impl(map_pos2max, intervals, it);
   }

   // Return the longest watching time 
   cout << map_pos2max << endl;
   return map_pos2max.begin()->second.second;
}

void watch_movie_impl(
      map<int, pair<int, vector<Interval> > >& map_pos2max,
      const vector<Interval>&                  intervals,
      vector<Interval>::reverse_iterator&      it)
{
   // Find longest watching time if start watching during the current movie is played (not watch current)
   int totalTime(0);
   map<int, pair<int, vector<Interval> > >::iterator totalTimeIt;
   map<int, pair<int, vector<Interval> > >::iterator lowerIt = map_pos2max.lower_bound(it->lower);
   map<int, pair<int, vector<Interval> > >::iterator upperIt = map_pos2max.upper_bound(it->upper);
   if ( lowerIt != upperIt )
   {
      totalTimeIt = lowerIt;
      totalTime = lowerIt->second.first;
   }

   // Compare with the watching time if watching current movie
   vector<Interval> currMax;
   map<int, pair<int, vector<Interval> > >::iterator upperLowerIt = map_pos2max.lower_bound(it->upper);
   int currTotalTime = it->upper - it->lower 
      + (upperLowerIt != map_pos2max.end() ? upperLowerIt->second.first : 0);

   if ( currTotalTime > totalTime )
   {
      totalTime = currTotalTime;
      currMax.push_back(*it);
      if ( upperLowerIt != map_pos2max.end() )
      {
         currMax.insert(currMax.end(), 
               upperLowerIt->second.second.begin(), 
               upperLowerIt->second.second.end());
      }
   }
   else
   {
      currMax.assign(
            totalTimeIt->second.second.begin(), 
            totalTimeIt->second.second.end());
   }

   if ( lowerIt != map_pos2max.end()
     && it->lower == lowerIt->first )
   {
      lowerIt->second = make_pair(totalTime, currMax);
   }
   else
   {
      map_pos2max.insert(make_pair(it->lower, 
               make_pair(totalTime, currMax)));
   }
}
};


int main(int argc, const char *argv[])
{
   Solution sol;
   vector<Interval> intervals;
   intervals.push_back(Interval(2, 7));
   intervals.push_back(Interval(1, 9));
   intervals.push_back(Interval(7, 11));
   intervals.push_back(Interval(10, 12));
   intervals.push_back(Interval(2, 5));
   cout << "@@INPUT@@: " << intervals << endl;
   cout << "@@OUTPUT@@: " << sol.watch_movie(intervals) << endl;
   return 0;
}
