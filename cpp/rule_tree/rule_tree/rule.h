#ifndef RULE_H
#define RULE_H

#include <QString>

struct check_rule_ {
    std::string     sParameter;
    std::string     sOperator;
    std::string     sValue;

    check_rule_() {}
    check_rule_( const std::string& parameter ) : sParameter( parameter ) {}
};

class check_rule_parameter_eq :
    public std::unary_function<check_rule_, bool> {
private:
    std::string _name;
public:
    check_rule_parameter_eq(const std::string & name) : _name(name) {}
    bool operator () (const check_rule_& d) const {
        return d.sParameter == _name;
    }
};

struct RuleInfo {
    check_rule_*        rule_;
    RuleInfo*           template_rule_;

    RuleInfo(
        check_rule_*    rule,
        RuleInfo*       template_rule
    ) :
        rule_( new check_rule_( *rule ) ),
        template_rule_( template_rule )
    {}

    RuleInfo( const RuleInfo& source ) :
        template_rule_( source.template_rule_ ),
        rule_( new check_rule_( *( source.rule_ ) ) )
    {}

    RuleInfo() :
        rule_( new check_rule_ ), template_rule_( 0 )
    {}

    ~RuleInfo() {
        delete rule_;
    }
};

bool operator < ( const RuleInfo& a, const RuleInfo& b );

#endif // RULE_H
