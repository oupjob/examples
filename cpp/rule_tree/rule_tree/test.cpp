#include "test.h"

int TestRules::number( const std::string& sect_name ) {
    NumberMap::iterator nm_it = number_map_.find( sect_name );
    return ( nm_it == number_map_.end() ) ? 0 : nm_it->second;
}

std::string TestRules::sect( const std::string &path, int i ) {
    int pos = std::string::npos, j = -1;
    do
        pos = path.find( ':', pos + 1 );
    while ( ++j != i );

    if ( pos == std::string::npos ) return "";
    int n = path.find( ':', pos + 1 );
    n = path.length() - n;

    return path.substr( pos, n - 1 );
}

std::string TestRules::addSect( const std::string &sect, int i ) {
    std::ostringstream os;
    os << sect << "_" << i;
    return os.str();
}

void TestRules::createAddPaths(
    const string&       path,
    const string&       sect,
    int                 from,
    int                 to,
    StrVec&             out
) {
    string s_add, p_add;
    for( int i = from; i <= to; ++i ) {
        s_add = addSect( sect, i );
        p_add = path;

        int pos = path.find( sect );
        if ( pos == std::string::npos ) return;
        p_add = p_add.replace( pos, sect.length(), s_add );

        out.push_back( p_add );
    }
}

void TestRules::buildAddRulesTree() {
    RuleInfoMSet::iterator r_it = rules_.begin();
    for(; r_it != rules_.end(); ++r_it )
        createAddRulesFor( &( *r_it ), rules_ );
}

void TestRules::createAddRulesFor( const RuleInfo *r, RuleInfoMSet &out ) {
    std::string sect;
    StrVec add_paths;
    int pos = -1, prev_pos = -1;
    bool stop = false;
    do {
        if ( stop ) break;

        pos = r->rule_->sParameter.find( ':', pos + 1 );
        int len_sect_name = ( ( pos != std::string::npos ) )
            ? pos - prev_pos - 1
            : r->rule_->sParameter.length() - prev_pos;

        sect = r->rule_->sParameter.substr( prev_pos + 1, len_sect_name );
        prev_pos = pos;

        int num = number( sect );
        createAddPaths( r->rule_->sParameter, sect, 0, num - 1, add_paths );
        cout << "path: '" << r->rule_->sParameter
             << "' sect: '" << sect << " [ " << number_map_[ sect ] <<  "] :\n";
        for ( int i = 0; i < num; ++i ) {
            RuleInfo rule_info;
            rule_info.rule_->sParameter = add_paths[ i ];
            rule_info.template_rule_ = const_cast<RuleInfo*>( r );
            out.insert( rule_info );

            cout << "|-> '" << rule_info.rule_->sParameter << "'\n";
        }
        cout << endl;

        stop = prev_pos == std::string::npos;
    } while ( true );
}

void TestRules::print() {
    cout << "Rules:\n";
    RuleInfoMSet::iterator r_it = rules_.begin();
    for(; r_it != rules_.end(); ++r_it ) {
        cout << r_it->rule_->sParameter;
        if ( r_it->template_rule_ )
            cout << " -->" << r_it->template_rule_->rule_->sParameter;
        cout << endl;
    }
    cout << endl;
}
