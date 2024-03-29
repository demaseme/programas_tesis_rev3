#ifndef THRACKLE_H
#define THRACKLE_H

#include "point.h"
//Thrackle object. A collection of edges.
//An edge is a pair of Point objects.
//Each element of edges is a vector of size 2.
class Thrackle{
public:
    int set_size;
    int thrackle_size;
    int ot;
    int tag;
    vector<bool> edge_bool;
    vector<Edge> edges;
};


// Edge operations (line segment operations)

//Returns true if line segments e_1 and e_2 cross.
int crossing(Edge e_1, Edge e_2);
//Returns true if line segments e_1 and e_2 share an endpoint.
bool share_ep(Edge e_1, Edge e_2);
//Thrackle operations.

//Finds all thrackles of size k, this is thrackles with k edges
//stores it on vector of Thrackle objects thrackles
void findThrackle(unsigned int k, vector<Point> points, vector<Thrackle> & thrackles);
//Returns true if the collection of edges 'edges' is a thackle and false otherwise.
bool isThrackle(vector<Edge> & edges);

bool edge_in(Edge a, vector<Edge> A);

void edge_set_intersection(const vector<Edge> A, const Thrackle B, vector<Edge> & C);
void thrackle_intersection(const Thrackle A, const Thrackle B, vector<int> & result );
void thrackle_intersection_all(const vector<Thrackle> T, int & result);
void minimal_thrackle_intersection(const vector<Thrackle> thrackles,int &result);
void bool_thrackle_intersection(const Thrackle A, const Thrackle B, vector<bool> & res);

void int_thrackle_intersection(vector<int> A, vector<int>B, vector<int> & C);
void int_thrackle_union(vector<int> A, vector<int> B, vector<int> & C);
void int_thrackle_diff(vector<int>A,vector<int>B, vector<int> & C);
void int_thrackle_complement(vector<int> A, int maxVal, vector<int> & C);

bool int_thrackle_areDifferent(vector<int>A, vector<int> B);

void bool_thrackle_union(Thrackle A, Thrackle B, vector<bool> & res);
bool union_covers(const vector<Thrackle> t);

void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations,
  int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles);
void combinationUtil(vector<Edge> arr, int r,int index, vector<Edge> data, int i,
  vector<vector<Edge>> & combinations, int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles);
void printThrackle(Thrackle t);
void printThrackleVector(vector<Thrackle> T);
void writeThrackles(vector<Thrackle> & thrackles, vector<Point> & points, int set_size, int thrackle_size, int ot_number,
int minimal_intersection_counter );

void thrackle_real_intersection_wrt(const vector<Thrackle> T, int current_ot, int set_size, int t_size);
void writeThrackles_bin(const vector<Thrackle> T, const vector<Point> points,
  const int set_size, const int t_size, const int ot, const int min_inter_count);
void writeOne4All_bin(ofstream& myfile, const vector<Thrackle> T, const vector<Point> points, const int set_size,
  const int t_size, const int ot, const int min_inter_count);
void writeOne4All_bin_bool(ofstream & myfile, const vector<Thrackle> T,
    const int t_size,const int ot_number );
//void drawThrackles(vector<Thrackle> thrackles, vector<vector<Point>> puntos);
void dibuja();
void procesa_puntos(vector<vector<Point>> points);
void findThrackles_size(const vector<Edge> edges, int k, long & comboCtr, vector<Thrackle> & foundThrackles);
#endif
