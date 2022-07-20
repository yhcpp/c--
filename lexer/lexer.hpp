#pragma one

enum class LexerStage
{
    Start,
    // abcd
    InId,
    //1234
    InNumber,
    // /
    InDivide,
    // /*
    InComment,
    // */
    EndComment,
    // <
    InLess,
    // >
    InGreater,
    // =
    InAssign,
    // !
    InNot,

    Done,

};

