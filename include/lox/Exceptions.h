#include "Lox.h"

namespace lox {
struct LoxException : std::exception {};
struct ScannerException : LoxException {};
struct EmptySrcString : ScannerException {};
} // namespace lox