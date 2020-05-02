cd "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
cmake -B BuildNinja -G Ninja .
cd BuildNinja
ninja