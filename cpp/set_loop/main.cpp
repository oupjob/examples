#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    std::string     id;
    Node*           parent;
    
    bool isParentOf( const Node& node ) { return node.id.find( id ) != string::npos; }
    bool isChildOf( const Node& node ) { return id.find( node.id ) != string::npos; }
};

struct NodeCmpLess {
//    Node    node;
//    NodeCmpLess( const Node& _node ) : node( _node ) {}
    bool operator()( const Node& a, const Node& b ) { return a.id < b.id; }
};

typedef multiset<Node, NodeCmpLess> S;

template <NodeContainer> void print( NodeContainer& c, std::string& prefix ) {
    typedef NodeContainer C;
    C::iterator it = c.begin();
    
    cout << endl << prefix << endl;
    for(; it != c.end(); ++it ) {
        cout << " id: " << c->id;
        if ( c->parent )
            cout << " parent_id: " << c->parent->id "\n";
        else 
            cout << " parent_id: NULL\n";
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
        { "q1", 0 }
    };
	S::iterator s_it = s.begin(), s_p_it;
	int n = s.size();

	std::vector<Node> v; //( s.begin(), s.end() );
	v.reserve( n );
	

//	std::copy( s.begin(), s.end(), back_inserter( v ) );

    print( s, "s before:" );

	for( s_p_it = s.begin(); s_p_it != s.end(); ++s_p_it ) {
        if ( IS_PARENT( s_p_it ) ) {
            for( s_it = s.begin(); s_it != s.end(); ++s_it ) {
                if ( s_it->isChildOf( *s_p_it ) ) {
                    Node node = { s_it->id, &( *s_p_it ) };
                    v.push_back( node );
                    s.erase( s_it );
                }
            }
        }
        
        std::vector<Node>::iterator v_it = v.begin();
        s.insert( v.begin(), v.end() );
        
        print<std::vector<Node> > ( v, "v of: " + s_p_it->id );
    }

	s.insert( v.begin(), v.end() );
	
	print( s, "s after:" );
    

	return 0;
}
