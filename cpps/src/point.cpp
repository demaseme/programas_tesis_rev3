#include "../include/point.h"
int setSize;

double cross(const Point &O, const Point &A, const Point &B){
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool lexcmp(const Point &p, const Point &q){
     return  ( (p.x < q.x) || ( (p.x == q.x) && (p.y < q.y))  );
}
//Sorts vector of points P lexicographically. Uses C++ sort function.
void sortPoints(vector<Point> & P){
    sort(P.begin(),P.end(),lexcmp);
}
//Prints a vector of edges
void printEdges(vector<Edge> vE){
    for(unsigned int i = 0; i < vE.size(); i++){
        printEdge(vE[i]);
    }
}
//Prints an edge
void printEdge(Edge e){
    printf("[(%d %d), (%d %d)]\n",e.v1.x,e.v1.y,e.v2.x,e.v2.y);
}
//Returns the index of the next edge on the list given a current edge.
//Used to find the next edge on a cycle.
//If no edge is found, -1 is returned.
int findNext(vector<Edge> edges, Edge current){
    for(int i = 0; i < (int)edges.size(); i++){
        if( ( (edges[i].v1 == current.v2) || (edges[i].v2 == current.v2)) && edges[i] != current) return i;
    }
    return -1;
}
//Returns true if the list of edges is a cycle and false o.w.
bool isCycle(vector<Edge> edges){
    int size = (int) edges.size();
    int state = findNext(edges, edges[0]);
    int i = 1;
    while(state >= 0 ){
        if(i==size) return true;
        state = findNext(edges,edges[state]);
        i++;
        //printf("State:%d \n",state);

    }
    return false;
}


//Given a vector of n points, it generates the edges
//of the complete graph with n vertices, stores them on vEdges.
void generateAllEdges(const vector<Point> vec,vector<Edge> & vEdges){
    Edge tmp;
    unsigned char tag;
    tag = 0;
    //cout << "Generating all edges!\n";

    for(unsigned int i = 0; i < vec.size(); i++){
        for(unsigned int j = i+1; j < vec.size(); j++){
            tmp.v1 = vec[i];
            tmp.v2 = vec[j];
            tmp.tag = tag;
            vEdges.push_back(tmp);
            tag++;
        }
    }
    //printEdges(vEdges);
}
//Generates the powerset of a set of edges, stores it in result.
//Could be optimized by receiving a const value ¿?
void pwrset_edges(vector<Edge> edges,vector<vector<Edge>> & result){
    int n = edges.size();
    unsigned int size = pow(2,n);
    vector<Edge> temp;
    for(unsigned int count = 0; count < size; count ++){
        for(int j = 0; j < n ; j++){
            if(count & (1<<j)){
                temp.push_back(edges[j]);
            }
        }
        result.push_back(temp);
        temp.clear();
    }
}
//Given an integer n, stores the elements of the power set of the set {0,1,2,..n-1}}
//which size is higher or equal than 3, in buff.
void pwrsetn(int n, vector<vector<int>> & buff ){
    vector<int> set;
    vector<int> temp;
    //Populate the set with {0,1,2,3...n-1}
    for(int i=0; i < n ; i++){
        set.push_back(i);
    }
    unsigned int size = pow(2,n);
    for(unsigned int count = 0; count < size; count ++){
        for(int j=0; j < n; j++){
            if(count & (1<<j)){
                temp.push_back(set[j]);
            }
        }
        if(temp.size() >= 3 ) buff.push_back(temp);
        temp.clear();
    }
}
void pwrsetk(int k, vector<Edge> input,vector<vector<Edge>> & output){
    //Calculate all subsets of size k.

    vector<Edge> temp;
    int n = (int)input.size();
    unsigned int size = pow(2,n);
    for(unsigned int count = 0; count < size; count ++){
        for(int j=0; j < n; j++){
            if(count & (1<<j)){
                temp.push_back(input[j]);
            }
        }
        if((int)temp.size() == k ) output.push_back(temp);
        temp.clear();
    }
}


// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2){
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r){
    long val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    printf("%ld\n", val);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

/*
    Returns how many points are inside the convex hull (not on it) of the
    given point set.
*/
int pointsInsideConvex(vector<Point> & points){
    int n = (int) points.size();
    printf(" Convex : working with %d points\n",n);
    // There must be at least 3 points
    if (n < 3) return -1;
    // Initialize Result
    vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    printf("First point is %d\n",l );
    do
    {
        // Add current point to result
        hull.push_back(points[p]);
        //printf("Current hull size %d\n", (int)hull.size());
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        p = q;

    } while (p != l);  // While we don't come to first point
    return (int)(n - hull.size());
}
//Returns true if v contains a set of points in convex position and false otherwise.
bool isConvex(vector<Point> points){
    int n = setSize;
    // There must be at least 3 points
    if (n < 3) return false;

    // Initialize Result
    vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x,
        // q) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then
           // update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }

        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;

    } while (p != l);  // While we don't come to first point

    // Print Result
    // for (unsigned int i = 0; i < hull.size(); i++)
    //     cout << "(" << hull[i].x << ", "
    //           << hull[i].y << ")\n";
    if(hull.size() == points.size()) return true;
    return false;
}


// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
	size_t n = P.size(), k = 0;
	if (n <= 3) return P;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (size_t i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (size_t i = n-1, t = k+1; i > 0; --i) {
		while (k >= t && cross(H[k-2], H[k-1], P[i-1]) <= 0) k--;
		H[k++] = P[i-1];
	}

	H.resize(k-1);
	return H;
}
//Prints all content of vector v.
void printVectorInt(vector<int> v){
    for(unsigned int i = 0; i < v.size(); i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}
//Prints all content of vector v.
void printVectorPoint(vector<Point> v){
    for(unsigned int i = 0; i < v.size(); i++){
        printf("%d %d\n",v[i].x ,v[i].y);
    }
}
//Prints the set of points, use when you want to see the whole set.
//For printing only the points in one vector use printVector.
void printPoints(vector<Point> v){
    cout << "Printing " << v.size() << " points.\nPoint set size: "<<setSize<<endl;
    for(unsigned int i = 0; i < v.size(); i++){
        printf("%d %d\n",v[i].x,v[i].y);
        if((i+1)%setSize==0) printf("\n");
    }
}
int readPoints2(int n, string file_name, vector<Point> & vPoints, int otypes){
    FILE * file = fopen(file_name.c_str(), "rb");
    if (file == NULL) {
        return 1;
    }
    int npuntos,err,bytes,i;
    npuntos = otypes*n;
    uint16_t a, b;
    bytes = 1;
    if (n > 8) bytes = 2;
    //Point *points = (Point*)malloc(sizeof(Point)*npuntos);
    vPoints.resize(npuntos);
    for(i = 0; i < npuntos;){
		err = fread(&a, bytes, 1, file);
        if ( err != 1 ){
            cout << err << " " << bytes << endl;
            fprintf(stderr,"Read error\n");
            exit(3);
        }
		err = fread(&b, bytes, 1, file);
        if ( err != 1 ){
            fprintf(stderr,"Read error\n");
            exit(3);
        }
        // points[i].x = a;
        // points[i].y = b;
        vPoints[i].x = a;
        vPoints[i].y = b;
        i++;
    }
    fclose(file);
    return 0;
}
int readPoints_bin2(int n, string file_name, Point *vPoints, int otypes, int npuntos){
    printf("Reading %d points\n",npuntos);
    size_t read_size;
    ifstream myfile(file_name, ios::binary);
    if(myfile.fail()) return 0;
    if (n > 8 ){
        read_size = sizeof(uint16_t);
    } else {
        read_size = sizeof(char);
    }
    Point pointtmp;
    for ( int i = 0; i < npuntos; i++){
        myfile.read( (char*) &pointtmp.x, read_size);
        myfile.read( (char*) &pointtmp.y, read_size);
        vPoints[i] = pointtmp;
        //cout << pointtmp.x << " " << pointtmp.y << endl;

    }
    myfile.close();
    return 1;
}
int readPoints_bin_arr(int n,string file_name, Point vA[],int npuntos){
	//Reads a binary file.

    int i;
    ifstream myfile(file_name, ios::binary);
    if(myfile.fail()) return 0;
    Point pointtmp;
    cout << "Reading points...\n";
    if(n>8){
        for(i = 0 ; i < npuntos; i++){

            myfile.read( (char*) &pointtmp.x, sizeof(uint16_t));
            myfile.read( (char*) &pointtmp.y, sizeof(uint16_t));
            vA[i].x = pointtmp.x;
			vA[i].y = pointtmp.y;
        }
    }else
        {
            for(i = 0 ; i < npuntos; i++){
                myfile.read( (char*) &pointtmp.x, sizeof(char));
                myfile.read( (char*) &pointtmp.y, sizeof(char));
				vA[i].x = pointtmp.x;
				vA[i].y = pointtmp.y;
            }
        }
    myfile.close();
    return 1;
}

int readPoints_bin(int n, string file_name, vector<Point> & vPoints, int otypes){
    //Reads a binary file.
    streampos size;
    int i;
    ifstream myfile(file_name, ios::binary|ios::ate);
    if(myfile.fail()) return 0;
    Point pointtmp;
    size = myfile.tellg();
    myfile.seekg(0,ios::beg);
    cout << "Reading points?\n";
    cout << "Size " << size << endl;
    if(n>8){
        for(i = 0 ; i < size; i++){

            myfile.read( (char*) &pointtmp.x, sizeof(uint16_t));
            myfile.read( (char*) &pointtmp.y, sizeof(uint16_t));
            vPoints.push_back(pointtmp);
        }
    }else
        {
            for(i = 0 ; i < size; i++){
                myfile.read( (char*) &pointtmp.x, sizeof(char));
                myfile.read( (char*) &pointtmp.y, sizeof(char));
                vPoints.push_back(pointtmp);
            }
        }
    myfile.close();
    return 1;
}
//Reads a file of binary points and stores it on vector vPoints.
int readPoints(int n, string file_name, vector<Point> & vPoints){
    ifstream input(file_name, std::ios::binary);
    if(input.fail()) return 1;
    // copies all data into buffer
    //Stored as unsigned int. Arithmetic operations (+-*/) can be used! :)
    //Can be treated as signed int or unsigned int.
    vector< unsigned char> buffer (std::istreambuf_iterator<char>(input), {});
    //Copying each pair of binary points to a vector of Point objects
    Point temp;
    cout << "Buffer size: " << buffer.size() << endl;
    if (n>8){
      for( long i=0;i < (long)buffer.size();i+=4){
          //cout << i << " ";
          temp.x = (unsigned short) buffer[i+0] | (((unsigned short) buffer[i+1]) << 8);
          temp.y = (unsigned short) buffer[i+2] | (((unsigned short) buffer[i+3]) << 8);
          vPoints.push_back(temp);

      }
    } else{
      for( unsigned int i=0;i< buffer.size();i+=2){
          temp.x = buffer[i+0];
          temp.y =  buffer[i+1];
          vPoints.push_back(temp);

      }
    }
    setSize = n;
    // cout << "Buffer size: " << buffer.size() << endl;
    // cout << "Total number of points: " << buffer.size()/2 << endl;
    // cout << "Number of sets: " << (buffer.size()/2)/n << endl;
    // cout << "Number of points on each set: " << n << endl;
    // for(unsigned int i = 0; i < buffer.size();i+=2){
    //     printf("%u %u ... %d\n",buffer[i],buffer[i+1],buffer[i]-buffer[i+1]);
    // }
    return 0;
}
