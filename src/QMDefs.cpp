#include "QMDefs.h"

namespace QuickMath {
    std::string OpTypeToString(QMOpType op) {
        switch(op)
        {
            case QMOpType::LT: return "<";
            case QMOpType::LTE: return "<=";
            case QMOpType::GT: return ">";
            case QMOpType::GTE: return "<=";
            case QMOpType::NE: return "!=";
            case QMOpType::EQ: return "==";
            case QMOpType::BICOND: return "<->";
            case QMOpType::IMPL: return "->";
            case QMOpType::LAND: return "&&";
            case QMOpType::LOR: return "||";
            case QMOpType::LNOT: return "!";
            case QMOpType::BAND: return "&";
            case QMOpType::BOR: return "|";
            case QMOpType::BNOT: return "~";
            case QMOpType::UKNWN:
            default: return "?";
        }
        return "?";
    }
}
