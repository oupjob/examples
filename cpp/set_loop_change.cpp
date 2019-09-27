#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    std::string     id;
    Node*           parent;
    
    bool isParentOf( const Node& node ) const { 
		return 
			node.id.find( id ) != string::npos 
				&& 
			id.size() == 1
				&&
			id != node.id;
	}

    bool isChildOf( const Node& node ) const { 
		return 
			id.find( node.id ) != string::npos 
				&& 
			node.id.size() == 1
				&&
			id != node.id;
	}
};

struct NodeCmpLess {
//    Node    node;
//    NodeCmpLess( const Node& _node ) : node( _node ) {}
    bool operator() ( const Node& a, const Node& b ) const { return a.id < b.id; }
};

typedef multiset<Node, NodeCmpLess> S;

template <class NodeContainer> void print( NodeContainer& c, const std::string& prefix ) {
    typedef NodeContainer C;
	typename C::iterator it = c.begin();
    
    cout << endl << prefix << endl;
    for(; it != c.end(); ++it ) {
        cout << " id: " << it->id;
        if ( it->parent )
            cout << ", parent_id: " << it->parent->id << "\n";
        else
            cout << ", parent_id: NULL\n";
    }
    cout << endl;
} 

#define IS_PARENT( iter )\
iter->id.size() == 1

int main() {
	S s = { 
        { "s",  0 }, 
        { "s0", 0 },
        { "s1", 0 },
        { "s2", 0 },
        { "q",  0 },
        { "q0", 0 },
        { "q1", 0 },
		{ "x", 0 },
		{ "y", 0 },
		{ "y0", 0 },
		{ "y1", 0 },
		{ "y3", 0 }
	//	{ "z", 0 },
	//	{ "z1", 0 }
    };
	S::iterator s_it = s.begin(), s_p_it;
	int n = s.size();

	std::vector<Node> v; //( s.begin(), s.end() );
	v.reserve( n );

    print( s, "s before:" );

	for( s_p_it = s.begin(); s_p_it != s.end(); ++s_p_it ) {
        if ( IS_PARENT( s_p_it ) ) {
			v.clear();
			cout << endl;
            for( s_it = s.begin(); s_it != s.end(); ) {
				cout << ">s_it: " << s_it->id << " ";
				if ( s_it->isChildOf( *s_p_it ) ) {
                    Node node = { s_it->id, const_cast<Node*>( &( *s_p_it ) ) };
                    v.push_back( node );
	                s.erase( s_it++ );
					
					cout << "( c: " << node.id << " p: " << node.parent->id << " ) ";
                } else 
					++s_it;
			}
			
       		s.insert( v.begin(), v.end() ); 
       		print< std::vector<Node> > ( v, "v of: " + s_p_it->id );
//			print( s, "s: p( " + s_p_it->id + " )" ); 
        }
    }

	print( s, "s after:" );

	return 0;
}
