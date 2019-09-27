#ifndef TEST_H
#define TEST_H

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

#include "rule.h"

using namespace std;
typedef std::multiset<RuleInfo>         RuleInfoMSet;
typedef std::pair<std::string, int>     NumberPair;
typedef std::map<std::string, int>      NumberMap;
typedef std::vector<std::string>        StrVec;

#define S2NUM( s, num )\
    number_map_.insert( NumberPair( s, num ) )


class TestRules
{
public:
    RuleInfoMSet     rules_;
    NumberMap       number_map_;

    void        buildAddRulesTree();
    int         number( const std::string& sect_name );
    std::string sect( const std::string& path, int i );
    std::string addSect( const std::string& sect, int i );
    void createAddPaths(
        const string&       path,
        const string&       sect,
        int                 from,
        int                 to,
        StrVec&             out
    );
    void createAddRulesFor( const RuleInfo* r, RuleInfoMSet& out );
    void addOfTemplate( RuleInfo* r, RuleInfoMSet& out );

    void print();
    void run();

    TestRules() {
       rules_ = {
           RuleInfo( new check_rule_( "a:b:c" ), 0 )/*,
           RuleInfo( new check_rule_( "d:e:f" ), 0 ),
           RuleInfo( new check_rule_( "g:h:i" ), 0 ),
           RuleInfo( new check_rule_( "alpha:beta:gamma" ), 0 )*/
       };

       S2NUM( "a", 0 );
       S2NUM( "b", 3 );
       S2NUM( "c", 1 );
       S2NUM( "d", 2 );
       S2NUM( "e", 3 );
       S2NUM( "f", 2 );
       S2NUM( "g", 1 );
       S2NUM( "h", 0 );
       S2NUM( "i", 2 );

       S2NUM( "alpha", 1 );
       S2NUM( "beta", 2 );
       S2NUM( "gamma", 1 );
       S2NUM( "lambda", 2 );
       S2NUM( "theta", 1 );
    }
};

#endif // TEST_H
