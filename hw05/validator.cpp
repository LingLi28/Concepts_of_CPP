#include "validator.h"

#include <variant>
#include <vector>

#include "token.h"

namespace sql {

bool SqlValidator::is_valid() const {
    // TODO: Implement this

    if (std::holds_alternative<state::Valid>(this->state_)){
            return true;
        }

    return false;
};
    

void SqlValidator::handle(const Token &token) {

    if (std::holds_alternative<state::Start>(this->state_)){
        this->state_ = transition(std::get<state::Start>(this->state_), token);
    } else if (std::holds_alternative<state::Valid> (this->state_)) {
        this->state_ = transition(std::get<state::Valid>(this->state_), token);
    } else if (std::holds_alternative<state::Invalid>(this->state_)) {
        this->state_ = transition(std::get<state::Invalid>(this->state_), token);
    } else if (std::holds_alternative<state::SelectStmt>(this->state_)) {
        this->state_ = transition(std::get<state::SelectStmt>(this->state_), token);
    } else if (std::holds_alternative<state::AllColumns>(this->state_)) {
        this->state_ = transition(std::get<state::AllColumns>(this->state_), token);
    } else if (std::holds_alternative<state::NamedColumn>(this->state_)) {
        this->state_ = transition(std::get<state::NamedColumn>(this->state_), token);
    } else if (std::holds_alternative<state::MoreColumns>(this->state_)) {
        this->state_ = transition(std::get<state::MoreColumns>(this->state_), token);
    } else if (std::holds_alternative<state::FromClause>(this->state_)) {
        this->state_ = transition(std::get<state::FromClause>(this->state_), token);
    } else if (std::holds_alternative<state::TableName>(this->state_)) {
        this->state_ = transition(std::get<state::TableName>(this->state_), token);
    } 

    // TODO: Implement this

}

struct TransitionFromStartVisitor {
    // Only the `Select` token advances the FSM from the `Start` state
    // TODO: Correct the behaviour
    State operator()(token::Select) const { return state::SelectStmt{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};


struct TransitionFromValidVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }

    // Still return Valid
    State operator()(token::Semicolon) const { return state::Valid{}; }
};

struct TransitionFromInvalidVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

struct TransitionFromSelectStmtVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }

    State operator()(token::Asterisks) const { return state::AllColumns{}; }
    State operator()(token::Identifier) const { return state::NamedColumn{}; }
};

struct TransitionFromAllColumnsVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }

    State operator()(token::From) const { return state::FromClause{}; }
};

struct TransitionFromNamedColumnVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }

    State operator()(token::From) const { return state::FromClause{}; }
    State operator()(token::Comma) const { return state::MoreColumns{}; }
};

struct TransitionFromMoreColumnsVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }

    State operator()(token::Identifier) const { return state::NamedColumn{}; }
};

struct TransitionFromFromClauseVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }

    State operator()(token::Identifier) const { return state::TableName{}; }

};

struct TransitionFromTableNameVisitor {
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }

    State operator()(token::Semicolon) const { return state::Valid{}; }
    
};



State transition(state::Start, const Token &token) {
    return std::visit(TransitionFromStartVisitor{}, token.value());
}

State transition(state::Valid, const Token &token) {
    // TODO: Implement
    return std::visit(TransitionFromValidVisitor{}, token.value());
}

State transition(state::Invalid, const Token &token) {
    // TODO: Implement
    return std::visit(TransitionFromInvalidVisitor{}, token.value());
}

State transition(state::SelectStmt, const Token &token) {
    return std::visit(TransitionFromSelectStmtVisitor{}, token.value());
}


State transition(state::AllColumns, const Token &token) {
    return std::visit(TransitionFromAllColumnsVisitor{}, token.value());
}


State transition(state::NamedColumn, const Token &token) {
    return std::visit(TransitionFromNamedColumnVisitor{}, token.value());
}


State transition(state::MoreColumns, const Token &token) {
    return std::visit(TransitionFromMoreColumnsVisitor{}, token.value());
}


State transition(state::FromClause, const Token &token) {
    return std::visit(TransitionFromFromClauseVisitor{}, token.value());
}


State transition(state::TableName, const Token &token) {
    return std::visit(TransitionFromTableNameVisitor{}, token.value());

}

bool is_valid_sql_query(const std::vector<Token> &tokens) {
    SqlValidator validator = SqlValidator();

    if (tokens.empty()) {
        return false;
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        validator.handle(tokens[i]);

    }

    return validator.is_valid();

}



} // namespace sql
