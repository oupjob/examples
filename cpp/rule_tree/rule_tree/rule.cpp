#include "rule.h"

bool operator < ( const RuleInfo& a, const RuleInfo& b ) {
    return a.rule_->sParameter < b.rule_->sParameter;
}
