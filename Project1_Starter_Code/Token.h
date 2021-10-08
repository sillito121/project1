#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_FILE
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    std::string description;
    TokenType type;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    Token(){};

    // TODO: add other needed methods
    std::string tokenToString(TokenType type);
    void toString();
    TokenType getType();
    std::string getDescrip();

};

#endif // TOKEN_H

