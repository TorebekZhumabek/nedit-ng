
#include "parse.h"
#include <string>
#include <QString>

Program *ParseMacro(const std::string &expr, std::string *msg, int *stoppedAt);

/**
 * @brief ParseMacroEx
 * @param expr
 * @param message
 * @param stoppedAt
 * @return
 */
Program *ParseMacroEx(const QString &expr, QString *message, int *stoppedAt) {

    auto str = expr.toStdString();

    std::string msg;
    Program *p = ParseMacro(str, &msg, stoppedAt);

    *message = QString::fromStdString(msg);
    return p;
}
